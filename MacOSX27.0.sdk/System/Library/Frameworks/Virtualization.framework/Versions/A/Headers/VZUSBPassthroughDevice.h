//
//  VZUSBPassthroughDevice.h
//  Virtualization
//
//  Copyright © 2024-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZUSBDevice.h>

@class VZUSBPassthroughDeviceConfiguration;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a USB passthrough device.
 @discussion
    This device is created through either instantiating it directly and passing
    VZUSBPassthroughDeviceConfiguration to its initializer or instantiating a
    VZUSBPassthroughDeviceConfiguration in a VZVirtualMachineConfiguration. Direct
    instantiation will create an object that can be passed to -[VZUSBController
    attachDevice:completionHandler:] method. Instantiation via
    VZUSBPassthroughDeviceConfiguration will make the device available in the
    usbDevices property of VZUSBController.

 @see VZUSBController
 @see VZUSBPassthroughDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZUSBPassthroughDevice : NSObject <VZUSBDevice>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the USB passthrough device.
 @param configuration The configuration of the USB passthrough device.
 @param error If not nil, used to report errors if initialization fails.
 @return An initialized VZUSBPassthroughDevice on success, or nil on failure.
 */
- (nullable instancetype)initWithConfiguration:(VZUSBPassthroughDeviceConfiguration *)configuration error:(NSError **)error NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

