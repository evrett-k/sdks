//
//  Copyright (c) 2024 Apple Inc.  All rights reserved.
//
//  FSKitError.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An error domain for FSKit errors.
///
/// See <doc://com.apple.documentation/documentation/Foundation/NSError> for more information on error domains.
FSKIT_API_AVAILABILITY_V1
FOUNDATION_EXPORT NSErrorDomain const FSKitErrorDomain;

/// A code that indicates a specific FSKit error.
typedef NS_ERROR_ENUM(FSKitErrorDomain, FSErrorCode) {
    /// The module failed to load.
    FSErrorModuleLoadFailed          = 4500,

    /// FSKit didn't recognize the resource, and probing failed to find a match.
    FSErrorResourceUnrecognized      = 4501,

    /// The resource is damaged.
    ///
    /// This error indicates the resource needs a repair operation, or that a repair operation failed.
    /// > Note: The status in this error applies to the resource. A failing repair operation reports a more specific error status.
    FSErrorResourceDamaged           = 4502,

    /// FSKit recognizes the resource, but the resource isn't usable.
    ///
    /// For example, this error occurs when a resource uses a file system's internal feature flags.
    /// If the only modules that support the file system don't support those feature flags, this code indicates an unusable resource.
    /// The error tells the person using the module why the resource isn't usable.
    FSErrorResourceUnusable          = 4503,

    /// An operation is in progress.
    FSErrorStatusOperationInProgress = 4504,

    /// An operation is paused.
    FSErrorStatusOperationPaused     = 4505,

    /// While enumerating a directory, the given cookie didn't resolve to a valid directory entry.
    FSErrorInvalidDirectoryCookie    = 4506,
};

/// Error codes specific to data cache operations.
FSKIT_API_AVAILABILITY_V3
typedef NS_ERROR_ENUM(FSKitErrorDomain, FSDataCacheErrorCode) {
    /// The requested cache mode and coherency type combination is invalid.
    FSErrorInvalidCacheModeCoherency        = 4510,

    /// The cache transition is not allowed.
    ///
    /// This error occurs when attempting an invalid transition, such as using an upgrade
    /// method for a downgrade operation, or vice versa.
    FSErrorInvalidCacheTransition           = 4511,

    /// Failed to flush dirty cached data to storage.
    FSErrorCacheFlushFailed                 = 4512,

    /// Failed to invalidate (clear) cached data.
    FSErrorCacheInvalidationFailed          = 4513,

    /// A conflicting cache operation is in progress.
    ///
    /// This error occurs when multiple cache operations on the same item conflict,
    /// such as attempting to change cache mode while I/O is active.
    FSErrorCacheOperationConflict           = 4514,
};

NS_ASSUME_NONNULL_END
