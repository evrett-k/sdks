//
//  VZCustomVirtioDeviceDelegate.h
//  Virtualization
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZCustomVirtioDevice;
@class VZVirtioQueue;

/**
 A delegate protocol that defines the methods you implement to respond to the life cycle events of a custom Virtio device.

 When you define these methods and set the delegate on your ``VZCustomVirtioDevice`` instance, the Virtualization
 framework notifies you when the Virtio device stops, pauses, resumes, or resets by the invocation of the respective methods defined
 here, and you can provide code to handle each of these situations.

 The framework considers the device to be ready when the guest driver sets `DRIVER_OK`, indicated by the invocation of
 ``VZCustomVirtioDeviceDelegate/customVirtioDeviceDidAcceptDriverOk:``, this means that the guest
 driver is set up and ready to drive the device, and the device is ready to process any device operations.

 Virtqueue (Virtio queue) notifications trigger device operations, then the framework invokes the ``VZCustomVirtioDeviceDelegate/customVirtioDevice:didReceiveNotificationForQueue:``
 method when the guest driver sends the device a virtqueue notification, and you can provide code to handle the
    notification.

 ## See Also

  - ``VZCustomVirtioDevice``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@protocol VZCustomVirtioDeviceDelegate <NSObject>

@optional

/**
 The method the framework calls when the device receives a virtqueue (Virtio queue) notification from the guest.

 - Parameters:
    - device: The device invoking the delegate method.
    - queue: The queue that received the notification.
 */
- (void)customVirtioDevice:(VZCustomVirtioDevice *)device didReceiveNotificationForQueue:(VZVirtioQueue *)queue;

/**
 The method the framework calls when the device and driver successfully complete Virtio negotiation.

 The guest driver sets the status to the value `DRIVER_OK`.

 - Parameter device: The device invoking the delegate method.
 */
- (void)customVirtioDeviceDidAcceptDriverOk:(VZCustomVirtioDevice *)device;

/**
    The method the framework calls when a device will be stopped.

    A device is in a stopped state when its corresponding ``VZVirtualMachine`` has stopped. This can happen when the guest performs a shutdown operation itself,  or when you call ``VZVirtualMachine/requestStopWithError:``.

    - Parameter device: The device invoking the delegate method.
 */
- (void)customVirtioDeviceWillStop:(VZCustomVirtioDevice *)device;

/**
    The method the framework calls when a device pauses.

    A device is in a paused state when its corresponding ``VZVirtualMachine`` is in a paused state. This happens when you call ``VZVirtualMachine/pauseWithCompletionHandler:``.

    - Parameter device: The device invoking the delegate method.
 */
- (void)customVirtioDeviceWillPause:(VZCustomVirtioDevice *)device;

/**
    The method the framework calls when a device resumes.

    A device is in a resumed state when its corresponding ``VZVirtualMachine`` resumes from the paused state.
    This happens when you call ``VZVirtualMachine/resumeWithCompletionHandler:``.

    - Parameter device: The device invoking the delegate method.
 */
- (void)customVirtioDeviceWillResume:(VZCustomVirtioDevice *)device;

/**
 The method the framework calls when a device resets.

 You can initiate a reset by calling the ``VZCustomVirtioDevice/requestDeviceReset`` method, and the guest driver can also initiate the reset by itself. The framework calls this method when the reset completes for either scenario.

 - Parameter device: The device invoking the delegate method.
 */
- (void)customVirtioDeviceWillReset:(VZCustomVirtioDevice *)device;

/**
 The method the framework calls when a device needs to save its state.

 Return the state data to save in an <doc://com.apple.documentation/documentation/foundation/nsdata> object.
 If there is no state to save, return an empty NSData object ([NSData data]).

 If you return `nil` from this method, the save operation fails.

 - Parameter device: The device invoking the delegate method.
 */
- (nullable NSData *)customVirtioDeviceSaveStateForRestore:(VZCustomVirtioDevice *)device;

/**
 The method the framework calls when a device restores its state.

 This method should return `NO` if restore operation failed.

 - Parameters:
    - device: The device invoking the delegate method.
    - saveState: The data that the delegate returned from ``VZCustomVirtioDeviceDelegate/customVirtioDeviceSaveStateForRestore:``.
 */
- (BOOL)customVirtioDeviceShouldRestore:(VZCustomVirtioDevice *)device saveState:(NSData *)saveState;

@end

NS_ASSUME_NONNULL_END
