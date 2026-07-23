//
//  VZCustomVirtioDeviceDelegateProvider.h
//  Virtualization
//
//  Copyright © 2024-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZCustomVirtioDeviceProvider.h>

NS_ASSUME_NONNULL_BEGIN

@protocol VZCustomVirtioDeviceConfigurationDelegate;

/**
A custom Virtio Device provider for devices that implement a custom Virtio device configuration delegate.

 The delegate runs in the same process as the guest's `VZVirtualMachine` instance.
 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZCustomVirtioDeviceDelegateProvider : VZCustomVirtioDeviceProvider

/**
 Creates a custom Virtio device delegate provider.

 - Parameters:
    - deviceQueue: The dispatch queue on which the framework synchronizes all device operations.
    - delegate: The delegate object that implements the device.
 */
- (instancetype)initWithDeviceQueue:(dispatch_queue_t)deviceQueue delegate:(id <VZCustomVirtioDeviceConfigurationDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/**
The queue the framework uses to synchronize operations for this device.
 */
@property (readonly) dispatch_queue_t deviceQueue;

/**
The delegate object that implements the device.
 */
@property (readonly, weak) id <VZCustomVirtioDeviceConfigurationDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
