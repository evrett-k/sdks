/*
	NSAppleEventManager.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreServices/CoreServices.h>
#import <Foundation/NSNotification.h>

@class NSAppleEventDescriptor;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Identifies an Apple event whose handling has been suspended. Can be used to resume handling of the Apple event.
typedef const struct __NSAppleEventManagerSuspension* NSAppleEventManagerSuspensionID;

/// A timeout constant indicating that the default timeout should be used.
extern const double NSAppleEventTimeOutDefault;
/// A timeout constant indicating that there is no timeout.
extern const double NSAppleEventTimeOutNone;

/// Posted by `NSAppleEventManager` before it first dispatches an Apple event.
extern NSNotificationName const NSAppleEventManagerWillProcessFirstEventNotification;

/// A mechanism for registering handler routines for specific types of Apple events and dispatching events to those handlers.
///
/// Cocoa provides built-in scriptability support that uses scriptability information supplied by an application to automatically convert Apple events into script command objects that perform the desired operation. However, some applications may want to perform more basic Apple event handling, in which an application registers handlers for the Apple events it can process, then calls on the Apple Event Manager to dispatch received Apple events to the appropriate handler. `NSAppleEventManager` supports these mechanisms by providing methods to register and remove handlers and to dispatch Apple events to the appropriate handler, if one exists. For related information, see [How Cocoa Applications Handle Apple Events](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_handle_AEs/SAppsHandleAEs.html#//apple_ref/doc/uid/20001239)
///
/// Each application has at most one instance of `NSAppleEventManager`. To obtain a reference to it, you call the class method ``shared()``, which creates the instance if it doesn't already exist.
///
/// For information about the Apple Event Manager, see <doc://com.apple.documentation/documentation/applicationservices/apple_event_manager> and Apple Events Programming Guide.
@interface NSAppleEventManager : NSObject {
    @private
    BOOL _isPreparedForDispatch;
    char _padding[3];
}

/// Returns the single instance of `NSAppleEventManager`, creating it first if it doesn't exist.
+ (NSAppleEventManager *)sharedAppleEventManager;

/// Registers the Apple event handler specified by `handler` for the event specified by `eventClass` and `eventID`.
///
/// If an event handler is already registered for the specified event class and event ID, removes it. The signature for `handler` should match the following:
///
/// ```objc
/// - (void)handleAppleEvent:(NSAppleEventDescriptor *)event withReplyEvent:(NSAppleEventDescriptor *)replyEvent;
/// ```
///
/// When it is invoked, the value of the first parameter will be the event to be handled. The value of the second parameter will be the reply event to fill in. A reply event object will always be passed in (replyEvent will never be nil), but it should not be touched if the event sender has not requested a reply, which is indicated by `[replyEvent descriptorType]==typeNull`.
- (void)setEventHandler:(id)handler andSelector:(SEL)handleEventSelector forEventClass:(AEEventClass)eventClass andEventID:(AEEventID)eventID;

/// If an Apple event handler has been registered for the event specified by `eventClass` and `eventID`, removes it.
///
/// Otherwise does nothing.
- (void)removeEventHandlerForEventClass:(AEEventClass)eventClass andEventID:(AEEventID)eventID;

/// Causes the Apple event specified by `theAppleEvent` to be dispatched to the appropriate Apple event handler, if one has been registered by calling `-setEventHandler:andSelector:forEventClass:andEventID:`.
///
/// The `theReply` parameter always specifies a reply Apple event, never `nil`. However, the handler should not fill out the reply if the descriptor type for the reply event is `typeNull`, indicating the sender does not want a reply.
///
/// The `handlerRefcon` parameter provides 4 bytes of data to the handler; a common use for this parameter is to pass a pointer to additional data.
///
/// This method is primarily intended for Cocoa's internal use. Note that _dispatching_ an event means routing an event to an appropriate handler in the current application. You cannot use this method to _send_ events to other applications.
- (OSErr)dispatchRawAppleEvent:(const AppleEvent *)theAppleEvent withRawReply:(AppleEvent *)theReply handlerRefCon:(SRefCon)handlerRefCon;

/// Returns the descriptor for `currentAppleEvent` if an Apple event is being handled on the current thread.
///
/// An Apple event is being handled on the current thread if a handler that was registered with `-setEventHandler:andSelector:forEventClass:andEventID:` is being messaged at this instant or `-setCurrentAppleEventAndReplyEventWithSuspensionID:` has just been invoked. Returns `nil` otherwise. The effects of mutating or retaining the returned descriptor are undefined, although it may be copied.
@property (nullable, readonly, retain) NSAppleEventDescriptor *currentAppleEvent;

/// Returns the corresponding reply event descriptor if an Apple event is being handled on the current thread.
///
/// An Apple event is being handled on the current thread if `currentAppleEvent` does not return `nil`. Returns `nil` otherwise. This descriptor, including any mutations, will be returned to the sender of the current event when all handling of the event has been completed, if the sender has requested a reply. The effects of retaining the descriptor are undefined; it may be copied, but mutations of the copy are not returned to the sender of the current event.
@property (nullable, readonly, retain) NSAppleEventDescriptor *currentReplyAppleEvent;

/// Suspends the handling of the current event and returns an ID that must be used to resume the handling of the event if an Apple event is being handled on the current thread.
///
/// An Apple event is being handled on the current thread if `currentAppleEvent` does not return `nil`. Returns zero otherwise. The suspended event is no longer the current event after this method returns.
- (nullable NSAppleEventManagerSuspensionID)suspendCurrentAppleEvent NS_RETURNS_INNER_POINTER;

/// Given a nonzero suspension ID returned by an invocation of `-suspendCurrentAppleEvent`, returns the descriptor for the event whose handling was suspended.
///
/// The effects of mutating or retaining the returned descriptor are undefined, although it may be copied. This method may be invoked in any thread, not just the one in which the corresponding invocation of `-suspendCurrentAppleEvent` occurred.
- (NSAppleEventDescriptor *)appleEventForSuspensionID:(NSAppleEventManagerSuspensionID)suspensionID;

/// Given a nonzero suspension ID returned by an invocation of `-suspendCurrentAppleEvent`, returns the corresponding reply event descriptor.
///
/// This descriptor, including any mutations, will be returned to the sender of the suspended event when handling of the event is resumed, if the sender has requested a reply. The effects of retaining the descriptor are undefined; it may be copied, but mutations of the copy will not be returned to the sender of the suspended event. This method may be invoked in any thread, not just the one in which the corresponding invocation of `-suspendCurrentAppleEvent` occurred.
- (NSAppleEventDescriptor *)replyAppleEventForSuspensionID:(NSAppleEventManagerSuspensionID)suspensionID;

/// Given a nonzero suspension ID returned by an invocation of `-suspendCurrentAppleEvent`, sets the values that will be returned by subsequent invocations of `currentAppleEvent` and `currentReplyAppleEvent` to be the event whose handling was suspended and its corresponding reply event, respectively.
///
/// Redundant invocations of this method will be ignored.
- (void)setCurrentAppleEventAndReplyEventWithSuspensionID:(NSAppleEventManagerSuspensionID)suspensionID;

/// Given a nonzero suspension ID returned by an invocation of `-suspendCurrentAppleEvent`, signal that handling of the suspended event may now continue.
///
/// This may result in the immediate sending of the reply event to the sender of the suspended event, if the sender has requested a reply. If the suspension ID has been used in a previous invocation of `-setCurrentAppleEventAndReplyEventWithSuspensionID:` the effects of that invocation will be completely undone. Subsequent invocations of other `NSAppleEventManager` methods using the same suspension ID are invalid. This method may be invoked in any thread, not just the one in which the corresponding invocation of `-suspendCurrentAppleEvent` occurred.
- (void)resumeWithSuspensionID:(NSAppleEventManagerSuspensionID)suspensionID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
