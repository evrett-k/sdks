//
//  AAUSBAccessoryManager.h
//  AccessoryAccess
//
//  Copyright © 2023-2026 Apple Inc. All rights reserved.
//

#import <AccessoryAccess/AAUSBAccessoryListener.h>

@class AAUSBAccessoryMatchingCriteria;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract `AAUSBAccessoryManager` manages the USB accessories.
 @discussion
    `AAUSBAccessoryManager` class manages the USB accessories, as well as the listeners of these accessories.

    A listener of USB accessories receives notifications when a USB accessory connects to or disconnects from the system. The listener
    can be registered or unregistered with the USB accessory manager object. The accessory manager will notify the listener about the USB accessories
    as long as it remains registered with the manager. All the notifications will be delivered to the listener on the internal serial queue
    of the accessory manager.

    When a USB accessory connects to the system, the USB accessory manager notifies the listener and provides it an `AAUSBAccessory` object that
    represents this accessory. This `AAUSBAccessory` object can be opened exclusively, and used for performing USB transfers to
    the connected accessory.

    `AAUSBAccessoryManager` should not be instantiated directly. It should be obtained through the class property `[AAUSBAccessoryManager sharedManager]`.

    As `AAUSBAccessoryManager` presents UI on behalf of your application, only use it from an ordinary application, that is, one that appears in the Dock.

    Sign your application with the `com.apple.developer.accessory-access.usb` entitlement.
 @see AAUSBAccessoryListener
 */
AA_EXPORT API_AVAILABLE(macos(27.0)) NS_SWIFT_SENDABLE
@interface AAUSBAccessoryManager : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Returns the shared USB accessory manager object for this process.
 */
@property (class, readonly, strong) AAUSBAccessoryManager *sharedManager;

/*!
 @abstract Register a listener of USB accessories.
 @discussion
    Register a listener of USB accessories that satisfy one of the given criteria. The listener is
    notified when a USB accessory, that satisfies the criteria, connects to or disconnects from the system.

    If the listener is already registered, this operation will fail with the `AAErrorCodeAccessoryListenerAlreadyRegistered` error.

    If any accessories matching the criteria are already connected, they are passed to the completion handler.
 @param listener The listener of USB accessories.
 @param matchingCriteria Matching criteria for filtering USB accessories.
    AAUSBAccessoryManager will notify the listener of the USB accessory events if the accessory satisfies any of the
    AAUSBAccessoryMatchingCriteria objects. Passing an empty array will match any USB accessory.
 @param completionHandler Block called after the listener is successfully registered.
    The first parameter passed to the block is an array containing accessories that are already connected and match the provided criteria. The array is empty if there are none.
    The second parameter passed to the block is nil if the listener was successfully registered.
    The block will be invoked on an arbitrary thread.
 @see AAUSBAccessoryMatchingCriteria
 */
- (void)registerListener:(id <AAUSBAccessoryListener>)listener withMatchingCriteria:(NSArray<AAUSBAccessoryMatchingCriteria *> *)matchingCriteria completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<AAUSBAccessory *> *, NSError * _Nullable))completionHandler NS_SWIFT_NAME(registerListener(_:matchingCriteria:completionHandler:));

/*!
 @abstract Unregister a previously registered listener.
 @discussion
    Unregister a listener of USB accessories that was previously registered.
 @param listener The listener of USB accessories.
 @param completionHandler Block called after the listener is successfully unregistered.
    The block will be invoked on an arbitrary thread.
 */
- (void)unregisterListener:(id <AAUSBAccessoryListener>)listener completionHandler:(void (NS_SWIFT_SENDABLE ^)(void))completionHandler NS_SWIFT_NAME(unregisterListener(_:completionHandler:));

@end

NS_ASSUME_NONNULL_END
