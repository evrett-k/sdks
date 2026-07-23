/*	
     NSUserNotification.h
     Copyright (c) 2011-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary<KeyType, ObjectType>, NSArray<ObjectType>, NSDateComponents, NSDate, NSTimeZone, NSImage, NSAttributedString, NSUserNotificationAction;
@protocol NSUserNotificationCenterDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* All NSUserNotifications API are deprecated. Please switch to the UserNotifications.framework for all notifications work. */
/// These constants describe how the user notification was activated.
typedef NS_ENUM(NSInteger, NSUserNotificationActivationType) {
    /// The user did not interact with the notification.
    NSUserNotificationActivationTypeNone = 0,
    /// The user clicked on the body of the notification.
    NSUserNotificationActivationTypeContentsClicked = 1,
    /// The user clicked the action button of the notification.
    NSUserNotificationActivationTypeActionButtonClicked = 2,
    /// The user replied to the notification.
    NSUserNotificationActivationTypeReplied API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos) = 3,
    /// The user clicked an additional action of the notification.
    NSUserNotificationActivationTypeAdditionalActionClicked API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos) = 4,
  } API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// A notification that can be scheduled for display in the notification center.
///
/// @DeprecationSummary {
/// Use the <doc://com.apple.documentation/documentation/usernotifications> framework instead.
/// }
///
/// When the system delivers a notification, information about when the notification was actually presented to the user (if at all) and other details are provided in the notification object. User applications can create ``NSUserNotification`` objects and register them with the ``NSUserNotificationCenter`` object to notify the user when an application requires attention.
///
/// ### Threading Information
///
/// The ``NSUserNotificationCenter`` class and the `NSUserNotification` class are both thread safe.
API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserNotification : NSObject <NSCopying> {
@private
    id _internal;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;

// -----------------------
// These properties are used to configure the notification before it is scheduled.

/// Specifies the title of the notification.
///
/// This value should be localized because it is presented to the user. The string is truncated to a length appropriate for display and the property is modified to reflect the truncation.
@property (nullable, copy) NSString *title;

/// Specifies the subtitle of the notification.
///
/// This value should be localized as it is presented to the user. The string is truncated to a length appropriate for display and the property is modified to reflect the truncation.
@property (nullable, copy) NSString *subtitle;

/// The body text of the notification.
///
/// This value should be localized as it is presented to the user. The string is truncated to a length appropriate for display and the property is modified to reflect the truncation.
@property (nullable, copy) NSString *informativeText;

/// Specifies the title of the action button displayed in the notification.
///
/// This value should be localized as it is presented to the user. The string is truncated to a length appropriate for display and the property is modified to reflect the truncation.
@property (copy) NSString *actionButtonTitle;

/// Application-specific user info that can be attached to the notification.
///
/// All items must be property list types or an exception is thrown.
///
/// The `userInfo` content must be of reasonable serialized size (less than 1KB) or an exception is thrown.
@property (nullable, copy) NSDictionary<NSString *, id> *userInfo;

/// Specifies when the notification should be delivered.
///
/// The delivery date is specified in an absolute time.
///
/// After a notification is delivered, it may be presented to the user.
@property (nullable, copy) NSDate *deliveryDate;

/// Specify the time zone to interpret the delivery date in.
///
/// If this value is `nil` and the user switches time zones, the notification center will adjust the time of presentation to account for the time zone change.
///
/// If a notification should be delivered at a time in a specific time zone (regardless of whether the user switches time zones), set this value to the specific time zone, for example the current time zone.
@property (nullable, copy) NSTimeZone *deliveryTimeZone;

/// Specifies the date components that control how often a user notification is repeated.
///
/// This value may be `nil` if the notification should not repeat.
///
/// The date component values are relative to the date the notification was delivered.
///
/// If the calendar value of the `deliveryRepeatInterval` is `nil`, the current calendar is used to calculate the repeat interval. For example, if a notification should repeat every hour, set the `hour` property of the `deliveryRepeatInterval` to `1`.
///
/// This value is ignored unless the user notification is scheduled with the `NSUserNotificationCenter` object.
@property (nullable, copy) NSDateComponents *deliveryRepeatInterval;

/// The date this notification was actually delivered.
///
/// The notification center will set this value if a notification is put in the scheduled list and the delivery time arrives.
///
/// If the notification is delivered directly using the `deliverNotification:` method of the `NSUserNotificationCenter` class, this value is set to the `deliveryDate` value. If the `deliveryDate` value is `nil`, this value is set to the current date.
///
/// This value is used to sort the list of notifications in the user interface.
@property (nullable, readonly, copy) NSDate *actualDeliveryDate;

/// Specifies whether the user notification has been presented.
///
/// In some cases, for example when your application is frontmost, the notification center may decide not to actually present a delivered notification. In that case, the value of this property is `NO`. It is set to `YES` if the notification was presented according to user preferences.
@property (readonly, getter=isPresented) BOOL presented;

/// Specifies whether the notification was generated by a push notification.
///
/// If this property is `YES` then the user notification was generated by a push notification (that is, remotely); if `NO` it was generated locally.
@property (readonly, getter=isRemote) BOOL remote;

/// Specifies the name of the sound to play when the notification is delivered.
///
/// Passing the `NSUserNotificationDefaultSoundName` constant causes the default notification center sound to be played.
///
/// A value of `nil` means no sound is played.
@property (nullable, copy) NSString *soundName;

/// A Boolean value that specifies whether the notification displays an action button.
///
/// Set to `NO` if the notification has no action button. This is the case for notifications that are purely for information and have no user action. The default value is `YES`.
@property BOOL hasActionButton;

/// Specifies what caused a user notification to occur.
///
/// This property specifies why the user notification was sent to the `NSUserNotificationCenterDelegate` method `userNotificationCenter:didActivateNotification:`. The supported values are described in `NSUserNotificationActivationType`.
@property (readonly) NSUserNotificationActivationType activationType;

/// Specifies a custom title for the close button in an alert-style notification.
///
/// This value should be localized as it is presented to the user. The string is truncated to a length appropriate for display and the property is modified to reflect the truncation.
///
/// An empty string will cause the default localized text to be used. A `nil` value is invalid.
@property (copy) NSString *otherButtonTitle;

/// A string that uniquely identifies a notification.
///
/// The identifier is unique to a notification. A notification delivered with the same identifier as an existing notification replaces the existing notification rather than causing the display of a new notification.
@property (nullable, copy) NSString *identifier API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// Image shown in the content of the notification.
@property (nullable, copy) NSImage *contentImage API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// A Boolean value that specifies whether the notification displays a reply button.
///
/// Set to `YES` if the notification has a reply button. The default value is `NO`. If this property and `hasActionButton` are both `YES`, the reply button is shown.
@property BOOL hasReplyButton API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// Optional placeholder string for inline reply field.
@property (nullable, copy) NSString *responsePlaceholder API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// The response with which the user responded to a notification.
///
/// When the user responds to a notification, the `NSUserNotificationCenterDelegate` method `userNotificationCenter:didActivateNotification:` is called with the notification, the `activationType` property set to `NSUserNotificationActivationTypeReplied`, and this property is set with the user's response.
@property (nullable, readonly, copy) NSAttributedString *response API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// The actions that can be taken on a notification in addition to the default action.
///
/// This array contains `NSUserNotificationAction` objects that describe the different actions for a notification in addition to the default action described by `actionButtonTitle`.
@property (nullable, copy) NSArray<NSUserNotificationAction *> *additionalActions API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);
/// An additional action selected by the user.
///
/// This property specifies an additional action selected by the user when the user notification is sent to the `NSUserNotificationCenterDelegate` method `userNotificationCenter:didActivateNotification:`.
@property (nullable, readonly, copy) NSUserNotificationAction *additionalActivationAction API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/// An action that the user can take in response to receiving a notification.
///
/// @DeprecationSummary {
/// Use the <doc://com.apple.documentation/documentation/usernotifications> framework instead.
/// }
///
/// User notifications can specify one or more actions to show to the user by using the ``NSUserNotification/additionalActivationAction`` or ``NSUserNotification/additionalActions`` properties. ``NSUserNotificationAction`` objects contain the localized title shown to the user and an identifier used to differentiate between presented actions.
API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.10, 11.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserNotificationAction : NSObject <NSCopying>

/// Creates a user notification action with a specified identifier and title.
///
/// - Parameters:
///   - identifier: The identifier for the action.
///   - title: A localized string suitable for display to the user.
+ (instancetype)actionWithIdentifier:(nullable NSString *)identifier title:(nullable NSString *)title;

/// The identifier for the user notification action.
@property (nullable, readonly, copy) NSString *identifier;

/// The localized title shown to the user.
@property (nullable, readonly, copy) NSString *title;

@end

/// The default notification sound.
FOUNDATION_EXPORT NSString * const NSUserNotificationDefaultSoundName API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// An object that delivers notifications from apps to the user.
///
/// @DeprecationSummary {
/// Use the <doc://com.apple.documentation/documentation/usernotifications> framework instead.
/// }
///
/// When a user notification's delivery date has been reached, or it's manually delivered, the notification center may display the notification to the user. The user notification center reserves the right to decide if a delivered user notification is presented to the user. For example, it may suppress the notification if the application is already frontmost (the delegate can override this action). The application can check the result of this decision by examining the ``NSUserNotification/isPresented`` property of a delivered user notification.
///
/// ``NSUserNotification`` instances the `NSUserNotificationCenter` are tracking will be in one of two states: scheduled or delivered. A scheduled user notification has a ``NSUserNotification/deliveryDate``. On that delivery date, the notification will move from being scheduled to being delivered. Note that the user notification may be displayed later than the delivery date depending on many factors.
///
/// A delivered user notification has an ``NSUserNotification/actualDeliveryDate``. That's the date when it moved from being scheduled to delivered, or when it was manually delivered using the ``deliver(_:)`` method.
///
/// The application and the user notification center are both ultimately subject to the user's preferences. If the user decides to hide all alerts from your application, the `presented` property will still behave as above, but the user won't see any animation or hear any sound.
///
/// The ``NSUserNotificationCenterDelegate`` provides more information about the delivered user notification and allows forcing the display of a user notification even if the application is frontmost.
///
/// > Note:
/// > It the user wakes more than 15 minutes after a scheduled notification is scheduled to fire, it's discarded. If the notification repeats with an interval less than 15 minutes, then it expires in 1 minute. Expired notifications are just discarded, unless they repeat, in which case, they stay in the scheduled list and just fire again later.
///
/// > Important:
/// > Many of the NSUserNotificationCenter class's methods involve talking to a server process, so calling them repeatedly can have a negative effect on performance.
///
/// ### Threading Information
///
/// The `NSUserNotificationCenter` class and the ``NSUserNotification`` class are both thread safe.
API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserNotificationCenter : NSObject {
@private
    id _internal;
}

/// Returns the default user notification center.
@property (class, readonly, strong) NSUserNotificationCenter *defaultUserNotificationCenter;

/// Specifies the notification center delegate.
///
/// The delegate must conform to the `NSUserNotificationCenterDelegate` protocol.
@property (nullable, assign) id <NSUserNotificationCenterDelegate> delegate;

/*
    Notifications that the NSUserNotificationCenter is tracking will be in one of two states: scheduled or delivered.
    A scheduled notification has a deliveryDate. On that delivery date, the notification will move from being scheduled to being delivered.
    A delivered notification has an actualDeliveryDate. That is the date when it moved from being scheduled to delivered, or when it was manually delivered (using the deliverNotification: method).
    The notification center reserves the right to decide if a delivered notification is presented on screen to the user. For example, it may supress the notification if the application is already frontmost. The application may check the result of this decision by examining the 'presented' property of a delivered notification.
    The application and the notification center are both ultimately subject to user preferences. If the user decides to hide all alerts from your application, the presented property will still behave as above, but the user will not see any animation or hear any sound.
*/

/// Specifies an array of scheduled user notifications that have not yet been delivered.
///
/// Newly scheduled notifications are added to the end of the array. You may also bulk-schedule notifications by setting this array. Bulk setting new scheduled notifications unschedules existing notifications.
@property (copy) NSArray<NSUserNotification *> *scheduledNotifications;

/// Schedules the specified user notification.
///
/// - Parameters:
///   - notification: The user notification.
///
/// Scheduled notifications are added to the end of the notification queue.
- (void)scheduleNotification:(NSUserNotification *)notification;

/// Removes the specified user notification from the scheduled notifications.
///
/// - Parameters:
///   - notification: The user notification.
///
/// If the user notification's `deliveryDate` occurs before the cancellation finishes, the notification may still be delivered.
///
/// If the notification is not in the scheduled list, nothing happens.
- (void)removeScheduledNotification:(NSUserNotification *)notification;



/// An array of all user notifications delivered to the notification center.
///
/// The number of notifications the user actually sees in the user interface may be less than the size of this array.
///
/// Note that these may or may not have been actually presented to the user. See the `presented` property in the `NSUserNotification` class.
@property (readonly, copy) NSArray<NSUserNotification *> *deliveredNotifications;

/// Deliver the specified user notification.
///
/// - Parameters:
///   - notification: The user notification.
///
/// The notification will be presented to the user (subject to the user's preferences). The `presented` property of the `NSUserNotification` object will always be set to `YES` if a notification is delivered using this method.
- (void)deliverNotification:(NSUserNotification *)notification;

/// Remove a delivered user notification from the user notification center.
///
/// - Parameters:
///   - notification: The user notification.
///
/// If the user notification is not in the delivered notifications list, nothing happens.
- (void)removeDeliveredNotification:(NSUserNotification *)notification;

/// Remove all delivered user notifications from the user notification center.
- (void)removeAllDeliveredNotifications;

@end

/* All NSUserNotifications API are deprecated. Please switch to the UserNotifications.framework for all notifications work. */
/// An interface that enables customizing the behavior of the default notification center.
@protocol NSUserNotificationCenterDelegate <NSObject>
@optional

/// Sent to the delegate when a notification delivery date has arrived.
///
/// - Parameters:
///   - center: The user notification center.
///   - notification: The user notification object.
///
/// This method is always called, regardless of your application state and even if you deliver the user notification yourself using `deliverNotification:`.
///
/// This delegate method is invoked before the `userNotificationCenter:shouldPresentNotification:` delegate method.
- (void)userNotificationCenter:(NSUserNotificationCenter *)center didDeliverNotification:(NSUserNotification *)notification API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sent to the delegate when a user clicks on a user notification presented by the user notification center.
///
/// - Parameters:
///   - center: The user notification center.
///   - notification: The user notification object.
///
/// This would be a good time to take action in response to user interacting with a specific notification.
///
/// To take an action when your application is launched as a result of a user clicking on a notification, be sure to implement the `applicationDidFinishLaunching:` method in the application class that implements the `NSApplicationDelegate` protocol. The notification parameter to that method has a `userInfo` dictionary, and if that dictionary has the `NSApplicationLaunchUserNotificationKey` key, the value of that key is the `NSUserNotification` object that caused the application to launch.
- (void)userNotificationCenter:(NSUserNotificationCenter *)center didActivateNotification:(NSUserNotification *)notification API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sent to the delegate when the user notification center has decided not to present your notification.
///
/// - Parameters:
///   - center: The user notification center.
///   - notification: The user notification object.
/// - Returns: `YES` if the user notification should be displayed regardless; `NO` otherwise.
- (BOOL)userNotificationCenter:(NSUserNotificationCenter *)center shouldPresentNotification:(NSUserNotification *)notification API_DEPRECATED("All NSUserNotifications API should be replaced with UserNotifications.frameworks API", macos(10.8, 11.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
