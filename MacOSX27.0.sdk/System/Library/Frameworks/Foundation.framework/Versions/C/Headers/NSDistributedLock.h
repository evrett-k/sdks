/*	NSDistributedLock.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A lock that multiple applications on multiple hosts can use to restrict access to some shared resource, such as a file.
NS_SWIFT_SENDABLE
@interface NSDistributedLock : NSObject

/// Returns an ``NSDistributedLock`` object initialized with the specified path.
+ (nullable NSDistributedLock *)lockWithPath:(NSString *)path;

- (instancetype)init NS_UNAVAILABLE;

/// Initializes an ``NSDistributedLock`` object to use the specified path for its lock.
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

/// Attempts to acquire the lock and immediately returns a Boolean value that indicates whether the attempt was successful.
- (BOOL)tryLock;

/// Relinquishes the receiver.
- (void)unlock;

/// Forces the lock to be relinquished.
- (void)breakLock;

/// The time the lock was acquired.
@property (readonly, copy) NSDate *lockDate;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
