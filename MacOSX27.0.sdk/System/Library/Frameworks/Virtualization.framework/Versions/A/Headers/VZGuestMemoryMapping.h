//
//  VZGuestMemoryMapping.h
//  Virtualization
//
//  Copyright © 2021-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object that represents a chunk of the guest operating system's dynamic random access memory (DRAM).

 A `VZGuestMemoryMapping` object provides read and write access to guest's DRAM for a ``VZCustomVirtioDevice``
 for Virtio devices that need to directly interact with the guest's DRAM.

 Don't instantiate a`VZGuestMemoryMapping` objects directly. Instead, call the
 ``VZCustomVirtioDevice/guestMemoryMappingAtPhysicalAddress:length:`` method
    and the framework creates a `VZGuestMemoryMapping` object for you.

 Throughout its lifetime, a `VZGuestMemoryMapping` object holds a reference to the all of the host memory allocated for the guest's DRAM.
 When the virtual machine is rebooted or shutdown, the allocated host memory becomes invalidated and remapped. As such, an instance of
  `VZGuestMemoryMapping` can't be used across a reboot or shutdown of the virtual machine.

 ## See Also

 - ``VZCustomVirtioDevice``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZGuestMemoryMapping : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 A pointer to the data this guest memory mapping object contains.
 */
@property (readonly) void *mutableBytes;

/**
 The guest's physical memory base address of this guest memory mapping object.
*/
@property (readonly) uint64_t physicalAddress;

/**
 The number of bytes contained by this guest memory mapping object.
 */
@property (readonly) NSUInteger length;

@end

NS_ASSUME_NONNULL_END
