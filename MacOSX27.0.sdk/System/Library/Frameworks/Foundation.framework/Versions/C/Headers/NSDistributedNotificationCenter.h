/*	NSDistributedNotificationCenter.h
	Copyright (c) 1996-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSNotification.h>

@class NSString, NSDictionary;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// This constant specifies the notification center type.
typedef NSString * NSDistributedNotificationCenterType NS_TYPED_EXTENSIBLE_ENUM;

/// Distributes notifications to all tasks on the sender's computer.
FOUNDATION_EXPORT NSDistributedNotificationCenterType const NSLocalNotificationCenterType;

/// Constants that specify the types of notification delivery suspension behaviors.
typedef NS_ENUM(NSUInteger, NSNotificationSuspensionBehavior) {
    /// The server doesn't queue any notifications with this name and object until the notification center resumes notification delivery.
    NSNotificationSuspensionBehaviorDrop = 1,
    /// The server only queues the last notification of the specified name and object; earlier notifications are dropped.
    ///
    /// In cover methods for which suspension behavior is not an explicit argument, `NSNotificationSuspensionBehaviorCoalesce` is the default.
    NSNotificationSuspensionBehaviorCoalesce = 2,
    /// The server holds all matching notifications until the queue has been filled (queue size determined by the server), at which point the server may flush queued notifications.
    NSNotificationSuspensionBehaviorHold = 3,
    /// The server will deliver notifications matching this registration irrespective of whether setSuspended:YES has been called. When a notification with this suspension behavior is matched, it has the effect of first flushing any queued notifications. The effect is somewhat as if setSuspended:NO were first called if the app is suspended, followed by the notification in question being delivered, followed by a transition back to the previous suspended or unsuspended state.
    NSNotificationSuspensionBehaviorDeliverImmediately = 4
};

/// These constants specify the behavior of notifications posted using the ``DistributedNotificationCenter/postNotificationName(_:object:userInfo:options:)`` method.
typedef NS_OPTIONS(NSUInteger, NSDistributedNotificationOptions) {
    /// When set, the notification is delivered immediately to all observers, regardless of their suspension behavior or suspension state.
    NSDistributedNotificationDeliverImmediately = (1UL << 0),
    /// When set, the notification is posted to all sessions. When not set, the notification is sent only to applications within the same login session as the posting task.
    NSDistributedNotificationPostToAllSessions = (1UL << 1)
};
/// When set, the notification is delivered immediately to all observers, regardless of their suspension behavior or suspension state. When not set, allows the normal suspension behavior of notification observers to take place.
static const NSDistributedNotificationOptions NSNotificationDeliverImmediately = NSDistributedNotificationDeliverImmediately;
/// When set, the notification is posted to all sessions. When not set, the notification is sent only to applications within the same login session as the posting task.
static const NSDistributedNotificationOptions NSNotificationPostToAllSessions = NSDistributedNotificationPostToAllSessions;

/// A notification dispatch mechanism that enables the broadcast of notifications across task boundaries.
///
/// A ``DistributedNotificationCenter`` instance broadcasts ``NSNotification`` objects to objects in other tasks that have registered for the notification with their task's default distributed notification center.
///
/// ### Principal Attributes
///
/// - Notification dispatch table. See "Class at a Glance" > "Principal Attributes" in ``NotificationCenter`` for information about the dispatch table.
///
/// In addition to the notification name and sender, dispatch table entries for distributed notification centers specify when the notification center delivers notifications to its observers. See the ``postNotificationName(_:object:userInfo:deliverImmediately:)`` method, Suspending and Resuming Notification Delivery, and ``SuspensionBehavior`` for details.
///
/// ### Commonly Used Methods
///
/// - term ``default()``: Accesses the default distributed notification center.
/// - term ``addObserver(_:selector:name:object:suspensionBehavior:)``: Registers an object to receive a notification with a specified behavior when notification delivery is suspended.
/// - term ``postNotificationName(_:object:userInfo:deliverImmediately:)``: Creates and posts a notification.
/// - term ``removeObserver(_:name:object:)``: Specifies that an object no longer wants to receive certain notifications.
///
/// ### Overview
///
/// Each task has a default distributed notification center that you access with the ``default()`` class method. There may be different types of distributed notification centers. Currently there is a single type—`NSLocalNotificationCenterType`. This type of distributed notification center handles notifications that can be sent between tasks on a single computer. For communication between tasks on different computers, use [Distributed Objects Programming Topics](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DistrObjects/DistrObjects.html#//apple_ref/doc/uid/10000102i).
///
/// Posting a _distributed notification_ is an expensive operation. The notification gets sent to a system-wide server that distributes it to all the tasks that have objects registered for distributed notifications. The latency between posting the notification and the notification's arrival in another task is unbounded. In fact, when too many notifications are posted and the server's queue fills up, notifications may be dropped.
///
/// Distributed notifications are delivered via a task's run loop. A task must be running a run loop in one of the "common" modes, such as `NSDefaultRunLoopMode`, to receive a distributed notification. For multithreaded applications running in macOS 10.3 and later, distributed notifications are always delivered to the main thread. For multithreaded applications running in OS X v10.2.8 and earlier, notifications are delivered to the thread that first used the distributed notifications API, which in most cases is the main thread.
///
/// > Important:
/// > `NSDistributedNotificationCenter` does not implement a secure communications protocol. When using distributed notifications, your app should treat any data passed in the notification as untrusted. See [Security Overview](https://developer.apple.com/library/archive/documentation/Security/Conceptual/Security_Overview/Introduction/Introduction.html#//apple_ref/doc/uid/TP30000976) for general guidance on secure coding practices.
///
/// > Note:
/// > `NSDistributedNotificationCenter` objects should not be used to send notifications between threads within the same task. Use [Distributed Objects Programming Topics](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DistrObjects/DistrObjects.html#//apple_ref/doc/uid/10000102i) or the <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class> method <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/performselector(onmainthread:with:waituntildone:)>, instead. You can also setup an ``Port`` object to receive and distribute messages from other threads.
@interface NSDistributedNotificationCenter : NSNotificationCenter

/// Returns the distributed notification center for a particular notification center type.
///
/// Currently only one type, `NSLocalNotificationCenterType`, is supported.
///
/// - Parameter notificationCenterType: Notification center type being inquired about.
/// - Returns: Distributed notification center for `notificationCenterType`.
+ (NSDistributedNotificationCenter *)notificationCenterForType:(NSDistributedNotificationCenterType)notificationCenterType;

/// Returns the default distributed notification center, representing the local notification center for the computer.
///
/// This method calls ``DistributedNotificationCenter/forType(_:)`` with an argument of `NSLocalNotificationCenterType`.
///
/// - Returns: Default distributed notification center for the computer.
+ (NSDistributedNotificationCenter *)defaultCenter;

/// Adds an entry to the receiver's dispatch table with a specific observer and suspended-notifications behavior, and optional notification name and sender.
///
/// The receiver does not retain `observer`. Therefore, you should always send `removeObserver:` or `removeObserver:name:object:` to the receiver before releasing the observer.
///
/// - Parameters:
///   - observer: Object registering as an observer. Must not be `nil`.
///   - selector: Selector that specifies the message the receiver sends the observer to notify it of the notification posting. Must not be `0`.
///   - name: The name of the notification for which to register the observer; that is, only notifications with this name are delivered to the observer. When `nil`, the notification center doesn't use a notification's name to decide whether to deliver it to the observer.
///   - object: The object whose notifications the observer wants to receive; that is, only notifications sent by this sender are delivered to the observer. When `nil`, the notification center doesn't use a notification's sender to decide whether to deliver it to the observer.
///   - suspensionBehavior: Notification posting behavior when notification delivery is suspended.
- (void)addObserver:(id)observer selector:(SEL)selector name:(nullable NSNotificationName)name object:(nullable NSString *)object suspensionBehavior:(NSNotificationSuspensionBehavior)suspensionBehavior;

/// Creates a notification with information and an immediate-delivery specifier, and posts it to the receiver.
///
/// This is the preferred method for posting notifications. The `userInfo` dictionary is serialized as a property list, so it can be passed to another task. In the receiving task, it is deserialized back into a dictionary.
///
/// - Parameters:
///   - name: Name of the notification to post. Must not be `nil`.
///   - object: Sender of the notification. May be `nil`.
///   - userInfo: Dictionary containing additional information. May be `nil`.
///   - deliverImmediately: When `NO`, the receiver delivers notifications to their observers according to the suspended-notification behavior specified in the corresponding dispatch table entry. When `YES`, the receiver delivers the notification immediately to its observers.
- (void)postNotificationName:(NSNotificationName)name object:(nullable NSString *)object userInfo:(nullable NSDictionary *)userInfo deliverImmediately:(BOOL)deliverImmediately;

/// Creates a notification with information, and posts it to the receiver.
///
/// The `userInfo` dictionary is serialized as a property list, so it can be passed to another task. In the receiving task, it is deserialized back into a dictionary.
///
/// - Parameters:
///   - name: Name of the notification to post. Must not be `nil`.
///   - object: Sender of the notification. May be `nil`.
///   - userInfo: Dictionary containing additional information. May be `nil`.
///   - options: Specifies how the notification is posted to the task and when to deliver it to its observers.
- (void)postNotificationName:(NSNotificationName)name object:(nullable NSString *)object userInfo:(nullable NSDictionary *)userInfo options:(NSDistributedNotificationOptions)options;


/// Suspends or resumes notification delivery.
///
/// Setting this to `true` suspends notification delivery, enabling the variety of suspension behaviors enumerated in ``DistributedNotificationCenter/SuspensionBehavior``. Setting this to `false` resumes immediate delivery of notifications.
///
/// `NSApplication` automatically suspends distributed notification delivery when the application is not active. Applications based on the Application Kit framework should let AppKit manage the suspension of notification delivery. Foundation-only programs may have occasional need to use this property.
@property BOOL suspended;

/// Adds an entry to the notification center's dispatch table with an observer, a selector, and an optional notification name and sender.
///
/// This method calls ``addObserver(_:selector:name:object:suspensionBehavior:)`` passing `NSNotificationSuspensionBehaviorCoalesce` for `suspensionBehavior`.
///
/// - Parameters:
///   - observer: An object registering as an observer.
///   - aSelector: A selector that the notification center sends the observer to notify when posting the notification.
///   - aName: The name of the notification for which to register the observer. When `nil`, the notification center doesn't use a notification's name to decide whether to deliver it to the observer.
///   - anObject: The object whose notifications the observer wants to receive. When `nil`, the notification center doesn't use a notification's sender to decide whether to deliver it to the observer.
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(nullable NSNotificationName)aName object:(nullable NSString *)anObject;

/// Creates a notification, and posts it to the receiver.
///
/// This method invokes ``postNotificationName(_:object:userInfo:deliverImmediately:)`` with `userInfo:nil deliverImmediately:NO`.
///
/// - Parameters:
///   - aName: Name of the notification to post. Must not be `nil`.
///   - anObject: Sender of the notification. May be `nil`.
- (void)postNotificationName:(NSNotificationName)aName object:(nullable NSString *)anObject;
/// Creates a notification with information, and posts it to the receiver.
///
/// This method invokes ``postNotificationName(_:object:userInfo:deliverImmediately:)`` with `deliverImmediately:NO`.
///
/// - Parameters:
///   - aName: Name of the notification to post. Must not be `nil`.
///   - anObject: Sender of the notification. May be `nil`.
///   - aUserInfo: Dictionary containing additional information. May be `nil`.
- (void)postNotificationName:(NSNotificationName)aName object:(nullable NSString *)anObject userInfo:(nullable NSDictionary *)aUserInfo;
/// Removes matching entries from the receiver's dispatch table.
///
/// Be sure to invoke this method before deallocating the observer object.
///
/// - Parameters:
///   - observer: Observer to remove from the dispatch table. Specify an observer to remove only entries for this observer. When `nil`, the receiver does not use notification observers as criteria for removal.
///   - aName: Name of the notification to remove from dispatch table. Specify a notification name to remove only entries that specify this notification name. When `nil`, the receiver does not use notification names as criteria for removal.
///   - anObject: Sender to remove from the dispatch table. Specify a notification sender to remove only entries that specify this sender. When `nil`, the receiver does not use notification senders as criteria for removal.
- (void)removeObserver:(id)observer name:(nullable NSNotificationName)aName object:(nullable NSString *)anObject;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
