//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//
//  FSContext.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A context object that provides information about the initiator of a file system operation.
///
/// This object contains the user ID and group ID of the process that initiated the file system operation, allowing file systems to make authorization decisions based on the caller's identity.
/// Use this context in handler methods that provide the context as a parameter.
FSKIT_API_AVAILABILITY_V3
@interface FSContext : NSObject

/// The caller's real user ID.
@property (readonly) NSInteger realUserID;
/// The caller's effective user ID.
@property (readonly) NSInteger effectiveUserID;
/// The caller's real group ID.
@property (readonly) NSInteger realGroupID;
/// The caller's effective group ID.
@property (readonly) NSInteger effectiveGroupID;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
