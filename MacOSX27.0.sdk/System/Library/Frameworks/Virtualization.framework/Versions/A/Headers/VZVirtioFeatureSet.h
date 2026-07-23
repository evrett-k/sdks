//
//  VZVirtioFeatureSet.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Values that represent a set of Virtio feature bits.

 A `VZVirtioFeatureSet` encapsulates the 64-bit Virtio feature set as two 32-bit subsets.
 The Virtio specification currently supports up to 64 feature bits, where subset0 represents
 bits 0 through 31 and subset1 represents bits 32 through 63.

 Don't instantiate `VZVirtioFeatureSet` directly. It's provided through the
 `VZCustomVirtioDeviceConfiguration.mandatoryFeatures` and
 `VZCustomVirtioDeviceConfiguration.optionalFeatures` properties.

 ## See Also

  - ``VZNegotiatedVirtioFeatureSet``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZVirtioFeatureSet : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
An unsigned 32-bit integer that represents Virtio feature bits 0 through 31.
 */
@property (readwrite) uint32_t subset0;

/**
 An unsigned 32-bit integer that represents Virtio feature bits 32 through 63.
 */
@property (readwrite) uint32_t subset1;

@end

NS_ASSUME_NONNULL_END
