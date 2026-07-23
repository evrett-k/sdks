//
//  FSFreeSpace.h
//  FSKit
//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A free space object that pairs free space values with atomic sequence numbers.
FSKIT_API_AVAILABILITY_V3
@interface FSFreeSpace : NSObject

/// Creates an unpopulated free space instance.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Populates this instance with the given free space value and atomically assigns a sequence number.
///
/// > Important: FSKit uses internal sequencing technology within this method to determine the most up-to-date free space of the volume. To ensure correctness, call this method within an isolation context covering the volume's free space.
- (void)populateWithBytes:(uint64_t)freeSpaceBytes
NS_SWIFT_NAME(populate(bytes:));

/// A sentinel instance that indicates no free space update occurred.
@property (class, readonly) FSFreeSpace *noUpdate;

@end

NS_ASSUME_NONNULL_END
