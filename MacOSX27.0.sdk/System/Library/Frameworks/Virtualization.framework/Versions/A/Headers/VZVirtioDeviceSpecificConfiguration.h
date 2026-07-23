//
//  VZVirtioDeviceSpecificConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
The device-specific configuration for a Virtio device

 This class represents a Virtio device's device-specific configuration.

 For more details about device-specific configuration for different Virtio devices, see the [Virtio specification](https://docs.oasis-open.org/virtio/virtio/v1.3/csd01/virtio-v1.3-csd01.html).

 Serialize any device-specific configuration structure into an
 <doc://com.apple.documentation/documentation/foundation/nsdata> object, and instantiate a
 ``VZVirtioDeviceSpecificConfiguration`` object with it, and set this object on the
 ``VZCustomVirtioDeviceConfiguration/deviceSpecificConfiguration`` property.
 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZVirtioDeviceSpecificConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initializes a Virtio device specific configuration object with the configuration data you provide

 - Parameter configurationData: The device-specific configuration that you provide serialized into an <doc://com.apple.documentation/documentation/foundation/nsdata> object.
 */
- (instancetype)initWithConfigurationData:(NSData *)configurationData NS_DESIGNATED_INITIALIZER;

/**
 The serialized device-specific configuration.
 */
@property (readonly, copy) NSData *configurationData;

@end

NS_ASSUME_NONNULL_END
