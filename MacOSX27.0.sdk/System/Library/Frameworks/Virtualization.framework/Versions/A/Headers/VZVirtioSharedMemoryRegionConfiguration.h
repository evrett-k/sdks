//
//  VZVirtioSharedMemoryRegionConfiguration.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The configuration of a Virtio shared memory region.

 A `VZVirtioSharedMemoryRegionConfiguration` represents a memory region that's continuously shared between the custom Virtio device
 implementation and the guest. A shared memory region is identified by an ID, whose meaning is specific to the device.

 After configuration,  the framework advertises the shared memory region to the guest. During runtime, you can use the
    ``VZVirtioSharedMemoryRegion/mapMemory:atOffset:size:completionHandler:`` and
    ``VZVirtioSharedMemoryRegion/unmapMemoryAtOffset:size:completionHandler:`` APIs to map and unmap host memory into the shared memory region. How a device uses a shared memory region is specific to the device.

 ## See Also

  -  ``VZCustomVirtioDeviceConfiguration``
  -  ``VZCustomVirtioDevice``
  -  ``VZVirtioSharedMemoryRegion``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZVirtioSharedMemoryRegionConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initializes a shared memory region with a shared memory region ID and size.

 - Parameters:
    - regionID: Shared memory region ID.
    - size: Shared memory region size.

 - Returns: An initialized ``VZVirtioSharedMemoryRegionConfiguration``.
 */
- (instancetype)initWithRegionID:(uint8_t)regionID size:(uint64_t)size NS_DESIGNATED_INITIALIZER;

/**
The shared memory region ID.
 */
@property (readonly) uint8_t regionID;

/**
 The size of the shared memory region.
 */
@property (readonly) uint64_t size;

@end

NS_ASSUME_NONNULL_END
