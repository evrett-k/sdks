//
//  VZCustomVirtioDeviceProvider.h
//  Virtualization
//
//  Copyright © 2024-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A base class that describes the provider of a custom Virtio device.

 A Custom Virtio device provider describes how the custom Virtio device is implemented.
 Don't instantiate `VZCustomVirtioDeviceProvider` directly. use one of its subclasses such as ``VZCustomVirtioDeviceDelegateProvider`` instead.

 ## See Also

  - ``VZCustomVirtioDeviceDelegateProvider``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZCustomVirtioDeviceProvider : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
