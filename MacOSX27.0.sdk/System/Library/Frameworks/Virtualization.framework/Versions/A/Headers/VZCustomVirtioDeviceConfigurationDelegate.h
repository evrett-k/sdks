//
//  VZCustomVirtioDeviceConfigurationDelegate.h
//  Virtualization
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZCustomVirtioDevice;
@class VZCustomVirtioDeviceConfiguration;
@class VZVirtualMachine;

/**
A class that conforms to the custom Virtio device configuration delegate protocol that can provide methods
    for tracking the state of a custom Virtio device configuration object.
 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@protocol VZCustomVirtioDeviceConfigurationDelegate <NSObject>

@optional

/**
 A method the framework calls when it creates a custom Virtio device from a custom Virtio device configuration.

  The Virtualization framework creates a ``VZCustomVirtioDevice`` when you call ``VZVirtualMachine/initWithConfiguration:``
  and calls this method on the serial queue of the guest's ``VZVirtualMachine`` instance.

 - Parameters:
    - deviceConfiguration: The configuration calling the delegate method.
    - device: The ``VZCustomVirtioDevice`` that the framework created.
 */
- (void)customVirtioConfiguration:(VZCustomVirtioDeviceConfiguration *)deviceConfiguration didCreateDevice:(VZCustomVirtioDevice *)device;

@end

NS_ASSUME_NONNULL_END
