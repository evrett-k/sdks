//
//  AAUSBAccessoryListener.h
//  AccessoryAccess
//
//  Copyright © 2023-2026 Apple Inc. All rights reserved.
//

#import <AccessoryAccess/AADefines.h>

@class AAUSBAccessory;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract `AAUSBAccessoryListener` listens to the USB accessory events.
 @discussion
    A class conforming to the `AAUSBAccessoryListener` protocol can provide methods that notify when a USB accessory is connected to or
    disconnected from the system.

    All the methods for a listener will be invoked on the internal serial queue of `AAUSBAccessoryManager`.
 @note
    When a fast user switch occurs or when the console user logs out (even with active remote sessions),
    all connected USB accessories will be automatically disconnected from client applications. If your
    application has registered listeners, they will receive `usbAccessoryDidDisconnect:` notifications
    for accessories that match their registered criteria. When the user returns to the console session,
    accessories will be automatically restored and reconnection notifications will be sent through
    `usbAccessoryDidConnect:`.
 */
AA_EXPORT API_AVAILABLE(macos(27.0)) NS_SWIFT_SENDABLE
@protocol AAUSBAccessoryListener <NSObject>
@optional

/*!
 @abstract Invoked when a USB accessory connects to the system.
 @discussion
    This method is invoked every time a USB accessory, that satisfies the matching criteria this listener registered with `AAUSBAccessoryManager`
    with, is connected to the system.

    This method will be invoked on an arbitrary thread.
 @param usbAccessory The USB accessory that connected to the system.
 @see AAUSBAccessoryMatchingCriteria
 @see AAUSBAccessoryManager
 */
- (void)usbAccessoryDidConnect:(AAUSBAccessory *)usbAccessory;

/*!
 @abstract Invoked when a USB accessory disconnects from the system.
 @discussion
    This method is invoked every time a USB accessory, for which the listener received the connect notification or was already connected at the
    time of listener registration, is disconnected from the system.

    This method will be invoked on an arbitrary thread.
 @param usbAccessory The USB accessory that disconnected from the system.
 @see AAUSBAccessoryMatchingCriteria
 @see AAUSBAccessoryManager
 */
- (void)usbAccessoryDidDisconnect:(AAUSBAccessory *)usbAccessory;

@end

NS_ASSUME_NONNULL_END
