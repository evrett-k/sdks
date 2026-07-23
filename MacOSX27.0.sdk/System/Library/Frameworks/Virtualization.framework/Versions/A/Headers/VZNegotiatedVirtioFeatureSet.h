//
//  VZNegotiatedVirtioFeatureSet.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Values that represent a set of negotiated Virtio feature bits.

  A ``VZNegotiatedVirtioFeatureSet`` represents the set of Virtio features the device and the driver have negotiated.

 ``VZNegotiatedVirtioFeatureSet`` encapsulates the 64-bit Virtio feature set as two 32-bit subsets.
  The Virtio specification currently supports up to 64 feature bits, where subset0 represents
  bits 0 through 31 and subset1 represents bits 32 through 63.

 Don't instantiate ``VZNegotiatedVirtioFeatureSet`` directly. Instead, first configure the device feature
 set through the ``VZCustomVirtioDeviceConfiguration/mandatoryFeatures`` and
  ``VZCustomVirtioDeviceConfiguration/optionalFeatures`` properties. Virtio negotiation then
 takes place when the guest boots and, after Virtio negotiation completes, the set of negotiated features is
 available in the ``VZCustomVirtioDevice/negotiatedFeatures`` property.
 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZNegotiatedVirtioFeatureSet : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 The values that represent feature bits 0 through 31.
 */
@property (readonly) uint32_t subset0;

/**
 The value that represent feature bits 32 through 63.
 */
@property (readonly) uint32_t subset1;

@end

NS_ASSUME_NONNULL_END
