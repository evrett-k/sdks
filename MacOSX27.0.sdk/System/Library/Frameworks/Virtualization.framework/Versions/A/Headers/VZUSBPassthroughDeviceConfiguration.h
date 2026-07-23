//
//  VZUSBPassthroughDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2024-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZUSBDeviceConfiguration.h>

@class AAUSBAccessory;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration of a VZUSBPassthroughDevice.
 @discussion
    This device configuration creates a VZUSBPassthroughDevice. A VZUSBPassthroughDeviceConfiguration
    is an abstraction of a USB device that is connected to the system and makes the USB device
    accessible to a VZVirtualMachine by capturing it.

    The USB device is captured when the VZVirtualMachine is started with a
    VZUSBPassthroughDeviceConfiguration added to a VZUSBControllerConfiguration. The USB device is
    also captured by a running VZVirtualMachine when -[VZUSBController attachDevice:completionHandler:]
    is called.

 @see VZUSBController
 @see VZUSBControllerConfiguration
 @see VZUSBPassthroughDevice
 @see VZVirtualMachineConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZUSBPassthroughDeviceConfiguration : NSObject <NSCopying, VZUSBDeviceConfiguration>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize a passthrough USB device configuration.
 @discussion
    Initialize a passthrough USB device configuration from an AccessoryAccess framework device.

 @param device The AccessoryAccess framework object to be captured by the virtual machine.
 @return An initialized VZUSBPassthroughDeviceConfiguration.
 */
- (instancetype)initWithDevice:(AAUSBAccessory *)device NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

