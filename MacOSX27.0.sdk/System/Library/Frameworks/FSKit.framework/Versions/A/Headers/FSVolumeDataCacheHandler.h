//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//
//  FSVolumeDataCacheHandler.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitError.h>
#import <FSKit/FSVolume.h>
#import <FSKit/FSVolumeHandlerResult.h>

NS_ASSUME_NONNULL_BEGIN

@class FSItem;

/// A type that defines the cache mode requested by the kernel for data operations.
FSKIT_API_AVAILABILITY_V3
typedef NS_ENUM(NSInteger, FSDataCacheMode) {
    /// A mode that indicates no active caching.
    FSDataCacheModeNone = 0,
    /// A mode that indicates read access with caching enabled.
    FSDataCacheModeReadWithCache,
    /// A mode that indicates read-write access with caching enabled.
    FSDataCacheModeReadWriteWithCache
} NS_SWIFT_NAME(FSVolume.DataCacheMode);

/// A type that defines how the kernel caches data.
FSKIT_API_AVAILABILITY_V3
typedef NS_ENUM(NSInteger, FSKernelCacheCoherencyType) {
    /// A type that indicates all I/O goes directly to storage, without caching.
    FSKernelCacheCoherencyTypeNoCache = 0,
    /// A type that indicates that writes bypass the cache and go directly to storage.
    FSKernelCacheCoherencyTypeReadCache,
    /// A type that indicates writes update cache and storage synchronously.
    FSKernelCacheCoherencyTypeWriteThrough,
    /// A type that indicates writes immediately update the cache only, followed by a deferred write to storage.
    FSKernelCacheCoherencyTypeWriteBack
} NS_SWIFT_NAME(FSVolume.KernelCacheCoherencyType);

/// A type that defines actions for cache state changes.
FSKIT_API_AVAILABILITY_V3
typedef NS_ENUM(NSInteger, FSKernelCacheCoherencyAction) {
    /// An action to flush dirty data from cache to storage, preserving cache contents.
    FSKernelCacheCoherencyActionPush = 0,
    /// An action to flush dirty data to storage and invalidate (clear) the cache.
    FSKernelCacheCoherencyActionPushInvalidate,
    /// An action to invalidate (clear) the cache, discarding any dirty data without writing to storage.
    FSKernelCacheCoherencyActionInvalidate,
    /// An action to update the coherency mode while keeping the cache valid, requiring no push or invalidation.
    FSKernelCacheCoherencyActionUpdate,
    /// An action to invalidate all caches, revoke all access to the item, and trigger vnode reclamation.
    ///
    /// Use this action when the module determines that an item no longer exists or
    /// is no longer accessible. Common scenarios include:
    /// - Another client deleted the item, as detected via server notification.
    /// - The module received a server callback indicating the file's absence.
    FSKernelCacheCoherencyActionRevoke
} NS_SWIFT_NAME(FSVolume.KernelCacheCoherencyAction);

/// Methods and properties implemented by volumes that coordinate kernel-level data caching.
///
/// A volume that conforms to this protocol enables kernel data caching for improved I/O performance.
/// This protocol allows filesystem modules to negotiate cache modes with the kernel and manage cache coherency.
///
/// When a file opens, the module receives the requested ``FSVolume/DataCacheMode`` and returns a
/// ``FSVolume/KernelCacheCoherencyType`` indicating the kind of caching behavior it can support. The kernel then
/// caches data according to the granted coherency type. The module can dynamically upgrade or
/// downgrade cache modes as conditions change.
///
/// The kernel requests a caching mode expressed as a ``FSVolume/DataCacheMode`` value, which indicates
/// what the kernel would like to cache (read-only data, read-write data, or no caching). The module
/// then replies with a specific ``FSVolume/KernelCacheCoherencyType`` value, which defines how the kernel
/// should cache the data (no caching, read-only caching, write-through caching, or write-back caching).
/// When the module detects an asynchronous condition requiring a change in caching mode (such as an
/// lease break), the module uses a value from ``FSVolume/KernelCacheCoherencyAction`` to instruct the kernel
/// how to handle any cached data (push dirty pages, invalidate cache, or update coherency mode).
///
/// The protocol supports deferred closing, where the kernel maintains cache state even after a file
/// is closed, enabling improved performance for frequently accessed files. The ``FSVolume/KernelCacheCoherencyType/readCache``,
/// ``FSVolume/KernelCacheCoherencyType/writeThrough``, and ``FSVolume/KernelCacheCoherencyType/writeBack`` modes
/// support deferred closing.
///
/// The following table shows the mapping of cache modes to supported coherency types.
///
/// | Cache mode | Coherency type |
/// |------------|-----------------|
/// | ``FSVolume/DataCacheMode/none`` | ``FSVolume/KernelCacheCoherencyType/noCache`` |
/// | ``FSVolume/DataCacheMode/readWithCache`` | ``FSVolume/KernelCacheCoherencyType/noCache`` or ``FSVolume/KernelCacheCoherencyType/readCache`` |
/// | ``FSVolume/DataCacheMode/readWriteWithCache`` | ``FSVolume/KernelCacheCoherencyType/noCache``, ``FSVolume/KernelCacheCoherencyType/readCache``, ``FSVolume/KernelCacheCoherencyType/writeBack`` or ``FSVolume/KernelCacheCoherencyType/writeThrough`` |
///
/// ### Supporting coherency transitions
///
/// Transitioning between coherency types requires different behaviors from your volume implementation, depending on whether the new type is more or less permissive than its current value.
/// The following table expresses the permissiveness of the coherency types.
///
/// | Coherency type | Permissiveness |
/// |----------------|----------------|
/// | ``FSVolume/KernelCacheCoherencyType/noCache`` | Least permissive |
/// | ``FSVolume/KernelCacheCoherencyType/readCache`` |  |
/// | ``FSVolume/KernelCacheCoherencyType/writeBack`` |  |
/// | ``FSVolume/KernelCacheCoherencyType/writeThrough`` | Most permissive |
///
/// When transitioning to more permissive caching, kernel performs an "upgrade" by calling ``upgrade(_:cacheMode:context:replyHandler:)``.
/// Your volume doesn't need to perform a flush or purge when upgrading to a more permissive coherency type.
///
/// Transitioning to a less permissive coherency type is considered a "downgrade".
/// Your module initiates this process by calling ``FSVolume/setCacheState(for:cacheMode:coherencyType:action:)`` when conditions change.
/// In this scenario, set the `action` to ``FSVolume/KernelCacheCoherencyAction/push``, ``FSVolume/KernelCacheCoherencyAction/pushInvalidate``, or ``FSVolume/KernelCacheCoherencyAction/invalidate``.
/// Handle any dirty data by flushing or purging it before downgrading with this method call.
///
/// > Important: If a file system doesn't conform to this protocol, the kernel may still cache it.
/// However, such a file system has no control over caching behavior; the kernel caches data as it sees fit.
FSKIT_API_AVAILABILITY_V3
NS_SWIFT_NAME(FSVolume.DataCacheHandler)
@protocol FSVolumeDataCacheHandler <NSObject>

@optional
/// A Boolean value that instructs FSKit not to call this protocol's methods, even if the volume conforms to it.
///
/// FSKit reads this value after the file system replies to the `loadResource` message.
/// Changing the returned value during the runtime of the volume has no effect.
@property (readonly, getter = isDataCacheInhibited) BOOL dataCacheInhibited FSKIT_API_AVAILABILITY_V3;

@required

/// Opens an item with cache mode negotiation.
///
/// FSKit calls this method when opening a file, providing the requested cache mode.
/// The module implementation determines what level of caching it can support for this item,
/// considering factors such as server lease availability, file locking state, or other coherency requirements.
///
/// The granted coherency type must be compatible with the requested cache mode, as defined
/// by the cache-mode-to-coherency-type mappings documented in the discussion of the ``FSVolume/DataCacheHandler`` protocol. If the module grants
/// a coherency type that exceeds the cache mode's permissions, the kernel downgrades to a valid coherency type.
///
/// - Parameters:
///   - item: The item to open.
///   - modes: The open modes, such as read and write.
///   - cacheMode: The requested cache mode, indicating what data is eligible for caching.
///   - context: An object that enables context-aware file system decisions throughout the operation.
///   - reply: A block or closure to indicate success or failure. If opening succeeds, pass an instance of ``FSOpenItemResult`` containing the granted ``FSVolume/KernelCacheCoherencyType``, along with a `nil` error. If opening fails, pass the relevant error as the second parameter; FSKit ignores the ``FSOpenItemResult`` instance in this case. For an `async` Swift implementation, there's no reply handler; simply return the result instance or throw an error.
- (void)openItem:(FSItem *)item
           modes:(FSVolumeOpenModes)modes
       cacheMode:(FSDataCacheMode)cacheMode
         context:(FSContext *)context
    replyHandler:(void (^)(FSOpenItemResult * _Nullable result,
                           NSError * _Nullable error))FSKIT_CALLED_ONCE reply
NS_SWIFT_NAME(open(_:modes:cacheMode:context:replyHandler:))
FSKIT_API_AVAILABILITY_V3;

/// Closes an item and releases associated cache resources.
///
/// FSKit calls this method when fully closing a file, and after the kernel finalizes all caching for the item.
///
/// Your module receives this call once per item when all references are released and the kernel
/// has completed its cache management. The module performs any necessary cleanup
/// operations for the item.
///
/// > Note: This method doesn't return or throw an error because the OS considers the file closed regardless
/// of whether the module encounters any issues during cleanup.
///
/// - Parameters:
///   - item: The item to close.
///   - context: An object that enables context-aware file system decisions throughout the operation.
///   - reply: A block or closure to call when the close operation completes.
- (void)closeItem:(FSItem *)item
          context:(FSContext *)context
     replyHandler:(void (^)(void))FSKIT_CALLED_ONCE reply
NS_SWIFT_NAME(close(_:context:replyHandler:))
FSKIT_API_AVAILABILITY_V3;

/// Upgrades the item cache mode to a less restrictive level, allowing more caching.
///
/// FSKit calls this method when transitioning to a cache mode that allows more aggressive caching.
///
/// - Parameters:
///   - item: The item for which to upgrade the cache mode.
///   - cacheMode: The new (more permissive) cache mode being requested.
///   - context: An object that enables context-aware file system decisions throughout the operation.
///   - reply: A block or closure to indicate success or failure. If successful, pass an instance of ``FSUpgradeItemResult`` containing the granted ``FSVolume/KernelCacheCoherencyType``, along with a `nil` error. If upgrading fails, pass the relevant error as the second parameter; FSKit ignores the ``FSUpgradeItemResult`` instance in this case. For an `async` Swift implementation, there's no reply handler; simply return the result instance or throw an error.
- (void)upgradeItem:(FSItem *)item
          cacheMode:(FSDataCacheMode)cacheMode
            context:(FSContext *)context
       replyHandler:(void (^)(FSUpgradeItemResult * _Nullable result,
                              NSError * _Nullable error))FSKIT_CALLED_ONCE reply
NS_SWIFT_NAME(upgrade(_:cacheMode:context:replyHandler:))
FSKIT_API_AVAILABILITY_V3;

@end

NS_ASSUME_NONNULL_END
