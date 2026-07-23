//
//  VZVirtioSharedMemoryRegion.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A class that represents a Virtio shared memory region for a custom Virtio device in a virtual machine.

    Don't instantiate a `VZVirtioSharedMemoryRegion` directly.

    Virtio shared memory regions are first configured on the ``VZCustomVirtioDeviceConfiguration`` through ``VZVirtioSharedMemoryRegionConfiguration``.
    When you create a ``VZCustomVirtioDevice``, the shared memory region is available through the ``VZCustomVirtioDevice/sharedMemoryRegions`` property.

    Use this class to manage the shared memory region during virtual machine runtime to map and unmap host memory into and from the shared memory region.

 ## See Also

  - ``VZVirtioSharedMemoryRegionConfiguration``
  - ``VZCustomVirtioDevice``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZVirtioSharedMemoryRegion : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 The shared memory region ID.
 */
@property (readonly) uint8_t regionID;

/**
 The size of the shared memory region.
 */
@property (readonly) uint64_t size;

/**
 Maps a chunk of host memory into the shared memory region.

  - Parameters:
    - memory: A pointer to host memory to map into the shared memory region.
    - offset: The offset from the start of the shared memory region where the memory should map to.
    - size: The size of the memory to map into the shared memory region.
    - completionHandler: A block the framework calls after successfully mapping the memory, or on an error.
        The error parameter passed to the block is `nil` if the map operation is successful.
        The framework invokes the block on ``VZCustomVirtioDevice/deviceQueue``.

    The memory, offset, and size must be aligned to the host page size.
 */
- (void)mapMemory:(void*)memory atOffset:(uint64_t)offset size:(uint64_t)size completionHandler:(void (^)(NSError * _Nullable))completionHandler;

/**
 Unmaps a chunk of host memory from the shared memory region.

 - Parameters:
    - offset: The offset from the start of the shared memory region where the memory should be unmapped.
    - size: The size of the memory to be unmapped from the shared memory region.
    - completionHandler: Block called after memory has been successfully unmapped or on error.
        The error parameter passed to the block is `nil` if the unmap operation is successful.
        The framework invokes the block on ``VZCustomVirtioDevice/deviceQueue``.

    The offset and size must be aligned to the host page size.
 */
- (void)unmapMemoryAtOffset:(uint64_t)offset size:(uint64_t)size completionHandler:(void (^)(NSError * _Nullable))completionHandler;

@end

NS_ASSUME_NONNULL_END
