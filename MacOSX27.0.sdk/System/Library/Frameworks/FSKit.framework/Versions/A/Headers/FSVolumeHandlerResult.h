//
//  FSVolumeHandlerResult.h
//  FSKit
//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>
#import <FSKit/FSItem.h>
#import <FSKit/FSFileName.h>
#import <FSKit/FSFreeSpace.h>

// Forward declaration to avoid circular dependency. Originally declared in `FSVolume.h`.
typedef uint64_t FSDirectoryVerifier;

/// Redeclaration to avoid circular dependency. Originally declared in ``FSVolumeDataCacheHandler.h``.
typedef NS_ENUM(NSInteger, FSKernelCacheCoherencyType);

NS_ASSUME_NONNULL_BEGIN

/// An abstract base class for all result objects in FSKit handler-style protocols.
///
/// This class provides the common functionality needed for all result objects. All specialized result classes inherit from this base class.
FSKIT_API_AVAILABILITY_V3
@interface FSVolumeHandlerResult : NSObject

/// A set of attributes to populate.
///
/// Your module populates these attributes in ``FSItem/Attributes`` instances.
///
/// Different operations may require different attribute sets. Access this property through the relevant result subclass, such as ``FSLookupItemResult.requestedAttributes`.
///
/// > Important: Be sure to populate all requested attributes. FSKit caches all populated attributes and may use them in subsequent operations, even if not explicitly requested.
@property (nonatomic, class, strong, readonly) FSItemGetAttributesRequest *requestedAttributes;

@end

#pragma mark - FSVolumeHandler Result Classes

/// The result of an activate call.
///
/// Use this type in your implementation of ``FSVolume/Handler/activate(options:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSActivateResult : FSVolumeHandlerResult

/// Creates an activate result instance.
///
/// - Parameters:
///   - rootItem: The root ``FSItem`` of the volume.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithRootItem:(FSItem *)rootItem
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(rootItem:));

/// Unavailable - use ``init(rootItem:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of an item lookup call.
///
///  Use this type in your implementation of ``FSVolume/Handler/lookupItem(named:in:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSLookupItemResult : FSVolumeHandlerResult

/// Creates a result for an item-lookup operation.
///
/// - Parameters:
///   - foundItem: The ``FSItem`` found by the directory lookup.
///   - itemName: The item's name as it exists within the file system. The value may differ from the requested name in order to handle case-insensitive file systems or Unicode normalization.
///   - itemAttributes: The ``FSItemAttributes`` of the found item.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithFoundItem:(FSItem *)foundItem
                                   itemName:(FSFileName *)itemName
                             itemAttributes:(FSItemAttributes *)itemAttributes
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(foundItem:itemName:itemAttributes:));

/// Unavailable - use ``init(foundItem:itemName:itemAttributes:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a create-item call.
///
/// Use this type in your implementation of ``FSVolume/Handler/createItem(named:type:in:attributes:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSCreateItemResult : FSVolumeHandlerResult

/// Creates a result for an item-creation operation.
///
/// - Parameters:
///   - newItem: The newly-created ``FSItem``.
///   - newItemName: The name of the newly-created item as it exists within the file system.
///   - newItemAttributes: The ``FSItemAttributes`` of the newly-created item.
///   - directoryAttributes: The updated ``FSItemAttributes`` of the parent directory.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation completes, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithNewItem:(FSItem *)newItem
                              newItemName:(FSFileName *)newItemName
                        newItemAttributes:(FSItemAttributes *)newItemAttributes
                      directoryAttributes:(FSItemAttributes *)directoryAttributes
                                freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(newItem:newItemName:newItemAttributes:directoryAttributes:freeSpace:));

/// Unavailable - use ``init(newItem:newItemName:newItemAttributes:directoryAttributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a create-symlink call.
///
/// Use this type in your implementation of  ``FSVolume/Handler/createSymbolicLink(named:in:attributes:linkContents:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSCreateSymlinkResult : FSCreateItemResult
@end

/// The result of a create-link call.
///
/// Use this type in your implementation of ``FSVolume/Handler/createLink(to:named:in:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSCreateLinkResult : FSVolumeHandlerResult

/// Creates a result for a link-creation operation.
///
/// - Parameters:
///   - linkName: The name of the newly-created hard link.
///   - linkAttributes: The ``FSItemAttributes`` of the linked item (the target of the hard link).
///   - directoryAttributes: The updated ``FSItemAttributes`` of the parent directory.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithLinkName:(FSFileName *)linkName
                            linkAttributes:(FSItemAttributes *)linkAttributes
                       directoryAttributes:(FSItemAttributes *)directoryAttributes
                                 freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(linkName:linkAttributes:directoryAttributes:freeSpace:));

/// Unavailable - use ``init(linkName:linkAttributes:directoryAttributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a rename-item call.
///
/// Use this type in your implementation of  ``FSVolume/Handler/renameItem(_:inDirectory:named:to:inDirectory:overItem:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSRenameItemResult : FSVolumeHandlerResult

/// Creates a result for an item-renaming operation.
///
/// - Parameters:
///   - newName: The updated item name as it exists within the destination directory.
///   - renamedItemAttributes: The ``FSItemAttributes`` of the renamed item.
///   - sourceDirectoryAttributes: The updated ``FSItemAttributes`` of the source directory.
///   - destinationDirectoryAttributes: The updated ``FSItemAttributes`` of the destination directory.
///   - overItemAttributes: The ``FSItemAttributes`` of the overwritten item, if any. Pass `nil` if the action didn't overwrite any item.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithNewName:(FSFileName *)newName
                    renamedItemAttributes:(FSItemAttributes *)renamedItemAttributes
                sourceDirectoryAttributes:(FSItemAttributes *)sourceDirectoryAttributes
           destinationDirectoryAttributes:(FSItemAttributes *)destinationDirectoryAttributes
                       overItemAttributes:(FSItemAttributes * _Nullable)overItemAttributes
                                freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(newName:renamedItemAttributes:sourceDirectoryAttributes:destinationDirectoryAttributes:overItemAttributes:freeSpace:));

/// Unavailable - use ``init(newName:renamedItemAttributes:sourceDirectoryAttributes:destinationDirectoryAttributes:overItemAttributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a remove-item call.
///
/// Use this type in your implementation of``FSVolume/Handler/removeItem(_:named:from:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSRemoveItemResult : FSVolumeHandlerResult

/// Creates a result for an item-removal operation.
///
/// - Parameters:
///   - itemAttributes: The ``FSItemAttributes`` of the removed item.
///   - directoryAttributes: The updated ``FSItemAttributes`` of the parent directory.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation finishes, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithItemAttributes:(FSItemAttributes *)itemAttributes
                             directoryAttributes:(FSItemAttributes *)directoryAttributes
                                       freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(itemAttributes:directoryAttributes:freeSpace:));

/// Unavailable - use ``init(itemAttributes:directoryAttributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a get-attributes call.
///
/// Use this type in your implementation of ``FSVolume/Handler/getAttributes(_:of:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSGetAttributesResult : FSVolumeHandlerResult

/// Creates a result for an attribute-getting operation.
///
/// - Parameters:
///   - attributes: The requested ``FSItemAttributes`` for the item.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithAttributes:(FSItemAttributes *)attributes
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(attributes:));

/// Unavailable - use ``init(attributes:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The restlt of a set-attributes call.
///
/// Use this type in your implementation of ``FSVolume/Handler/setAttributes(_:on:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSSetAttributesResult : FSVolumeHandlerResult

/// Creates a result for an attribute-setting operation.
///
/// - Parameters:
///   - attributes: The updated ``FSItemAttributes`` for the item.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithAttributes:(FSItemAttributes *)attributes
                                   freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(attributes:freeSpace:));

/// Unavailable - use ``init(attributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of an enumerate-directory call.
///
/// Use this type in your implementation of ``FSVolume/Handler/enumerateDirectory(_:startingAt:verifier:attributes:packer:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSEnumerateDirectoryResult : FSVolumeHandlerResult

/// Creates a result for an directory enumeration operation.
///
/// - Parameters:
///   - currentVerifier: An `FSDirectoryVerifier` value that reflects the directory's current version. FSKit uses this value to detect whether the directory contents changed since the last enumeration call.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithVerifier:(FSDirectoryVerifier)currentVerifier
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(verifier:));

/// Unavailable - use ``init(verifier:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a read-symlink call.
///
/// Use this type in your implementation of ``FSVolume/Handler/readSymbolicLink(_:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSReadSymlinkResult : FSVolumeHandlerResult

/// Creates a result for a symlink-reading operation.
///
/// - Parameters:
///   - contents: The contents of the symbolic link.
///   - attributes: The ``FSItemAttributes`` of the symbolic link.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithContents:(FSFileName *)contents
                         symlinkAttributes:(FSItemAttributes *)attributes
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(contents:symlinkAttributes:));

/// Unavailable - use ``init(contents:symlinkAttributes:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeXattrHandler Result Classes

/// The result of a get-extended-attributes call.
///
/// Use this type in your implementation ``FSVolume/XattrHandler/getXattr(named:of:context:replyHandler:)``
FSKIT_API_AVAILABILITY_V3
@interface FSGetXattrResult : FSVolumeHandlerResult

/// Creates a result for an extended-attribute-getting operation.
///
/// - Parameters:
///   - value: The extended attribute value for the requested attribute name.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithXattrValue:(NSData *)value
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(xattrValue:));

/// Unavailable - use ``init(xattrValue:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a set-extended-attributes call.
///
/// Use this type in your implementation of  ``FSVolume/XattrHandler/setXattr(named:to:on:policy:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSSetXattrResult : FSVolumeHandlerResult

/// Creates a result for an extended-attribute-setting operation.
///
/// - Parameters:
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithFreeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(freeSpace:));

/// Unavailable - use ``init(freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a list-extended-attributes call.
///
/// Use this type in your implementation of ``FSVolume/XattrHandler/supportedXattrNames(for:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSListXattrsResult : FSVolumeHandlerResult

/// Creates a result instance with all required properties populated.
///
/// - Parameters:
///   - xattrNames: An array of ``FSFileName`` instances representing the names of all extended attributes currently set on the item.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithXattrNames:(NSArray<FSFileName *> *)xattrNames
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(xattrNames:));

/// Unavailable - use ``init(xattrNames:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeReadWriteHandler Result Classes

/// The result of a read-file call.
///
/// Use this type in your implementation of ``FSVolume/ReadWriteHandler/read(from:at:length:into:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSReadFileResult : FSVolumeHandlerResult

/// Creates a result for a file-reading operation.
///
/// - Parameters:
///   - actuallyRead: The number of bytes actually read from the file. This may be less than the requested length if the end of file was reached.
///   - attributes: The updated ``FSItemAttributes`` of the file after the read operation (e.g., updated access time).
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithBytesRead:(size_t)actuallyRead
                             itemAttributes:(FSItemAttributes *)attributes
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(bytesRead:itemAttributes:));

/// Unavailable - use ``init(bytesRead:itemAttributes:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a read-file call.
///
/// Use this type in your implementation of ``FSVolume/ReadWriteHandler/write(contents:to:at:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSWriteFileResult : FSVolumeHandlerResult

/// Creates a result for a file-writing operation.
///
/// - Parameters:
///   - actuallyWritten: The number of bytes actually written to the file. This should match the requested write length unless an error occurred.
///   - attributes: The updated ``FSItemAttributes`` of the file after the write operation. Examples of attributes you might need to update are the updated file size and modification time.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithBytesWritten:(size_t)actuallyWritten
                                itemAttributes:(FSItemAttributes *)attributes
                                     freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(bytesWritten:itemAttributes:freeSpace:));

/// Unavailable - use ``init(bytesWritten:itemAttributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeAccessCheckHandler Result Classes

/// The result of a check-access call.
///
/// Use this type in your implementation of ``FSVolume/AccessCheckHandler/checkAccess(to:requestedAccess:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSCheckAccessResult : FSVolumeHandlerResult

/// Creates a result for an access-checking operation.
///
/// - Parameters:
///   - accessAllowed: A Boolean value indicating whether the file system grants the requested access to the item. Pass `true` (Swift) or `YES` (Obj-C) to allow access, `false` (Swift) or `NO` (Obj-C) to deny access.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithAccessAllowed:(BOOL)accessAllowed
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(accessAllowed:));

/// Unavailable - use ``init(accessAllowed:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeRenameHandler Result Classes

/// The result of a rename-volume call.
///
///  Use this type in your implementation of ``FSVolume/RenameHandler/setVolumeName(_:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSVolumeRenameResult : FSVolumeHandlerResult

/// Creates a result for a volume-renaming operation.
///
/// - Parameters:
///   - newName: The new volume name.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithNewName:(FSFileName *)newName
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(newName:));

/// Unavailable - use ``init(newName:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumePreallocateHandler Result Classes

/// The result of a preallocate call.
///
/// Use this type in your implementation of  ``FSVolume/PreallocateHandler/preallocateSpace(for:at:length:flags:context:replyHandler:)``
FSKIT_API_AVAILABILITY_V3
@interface FSPreallocateResult : FSVolumeHandlerResult

/// Creates a result for a preallocate operation.
///
/// - Parameters:
///   - bytesAllocated: The number of bytes actually allocated for the file during the preallocation operation.
///   - attributes: The updated ``FSItemAttributes`` of the file after the preallocation operation.
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithBytesAllocated:(size_t)bytesAllocated
                                  itemAttributes:(FSItemAttributes *)attributes
                                       freeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(bytesAllocated:itemAttributes:freeSpace:));

/// Unavailable - use ``init(bytesAllocated:itemAttributes:freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeItemDeactivationHandler Result Classes

/// The result of a deactivate-item call.
///
/// Use this type in your implementation of ``FSVolume/ItemDeactivationHandler/deactivateItem(_:context:replyHandler:)``
FSKIT_API_AVAILABILITY_V3
@interface FSDeactivateItemResult : FSVolumeHandlerResult

/// Creates a result for an item-deactivation operation.
///
/// - Parameters:
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithFreeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(freeSpace:));

/// Unavailable - use ``init(freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeSeekRegionHandler Result Classes

/// A seek-region result.
///
/// Use this type in your implementation of ``FSVolume/SeekRegionHandler/seek(within:from:region:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSSeekRegionResult : FSVolumeHandlerResult

/// Creates a result for a region-seeking operation.
///
/// - Parameters:
///   - returnedOffset: The offset of the requested region, greater than or equal to the supplied offset.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype)initWithReturnedOffset:(off_t)returnedOffset
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(returnedOffset:));

/// Unavailable - use ``init(returnedOffset:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - FSVolumeKernelOffloadedIOHandler Result Classes

/// The result of a blockmap call.
///
/// Use this type in your implementation of ``FSVolume/KernelOffloadedIOHandler/blockmapFile(_:offset:length:flags:operationID:packer:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSBlockmapResult : FSVolumeHandlerResult

/// Creates a result for a blockmap operation.
///
/// - Parameters:
///   - freeSpace: An ``FSFreeSpace`` instance populated with the volume's updated free space. Passing a `nil` free space causes FSKit to calculate the free space when the operation is done, based on the volume's ``FSVolume/Handler/volumeStatistics`` property. This behavior may lead to degraded performance.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithFreeSpace:(FSFreeSpace * _Nullable)freeSpace
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(freeSpace:));

/// Unavailable - use ``init(freeSpace:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a complete-I/O call.
///
/// Use this type in your implementation of  ``FSVolume/KernelOffloadedIOHandler/completeIO(for:offset:length:status:flags:operationID:replyHandler:)``
FSKIT_API_AVAILABILITY_V3
@interface FSCompleteIOResult : FSVolumeHandlerResult

/// Creates a result for an I/O-completion operation.
///
/// - Parameters:
///   - attributes: The updated ``FSItemAttributes`` of the file after the I/O completion operation (e.g., updated size, modification time).
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype _Nullable)initWithAttributes:(FSItemAttributes *)attributes
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(itemAttributes:));

/// Unavailable - use ``init(itemAttributes:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of a kernel-offloaded create-file call.
///
/// Use this type in your implementation of ``FSVolume/KernelOffloadedIOHandler/createFile(named:in:attributes:packer:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSCreateFileKOIOResult : FSCreateItemResult
@end

/// The result of a kernel-offloaded lookup-item call.
///
/// Use this type in your implementation of ``FSVolume/KernelOffloadedIOHandler/lookupItem(named:in:packer:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSLookupItemKOIOResult : FSLookupItemResult
@end

/// The result of a kernel-offloaded preallocate call.
///
/// Use this type in your implementation of ``FSVolume/KernelOffloadedIOHandler/preallocateSpace(for:at:length:flags:packer:context:replyHandler:)``
FSKIT_API_AVAILABILITY_V3
@interface FSPreallocateKOIOResult : FSPreallocateResult
@end

#pragma mark - FSVolumeDataCacheHandler Result Classes

/// The result of an open-item call.
///
/// Use this type in your implementation of ``FSVolume/DataCacheHandler/open(_:modes:cacheMode:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSOpenItemResult : FSVolumeHandlerResult

/// Creates an open-item result.
///
/// - Parameters:
///   - grantedCoherency: The ``FSKernelCacheCoherencyType`` granted by the module for this item.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype)initWithGrantedCoherency:(FSKernelCacheCoherencyType)grantedCoherency
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(grantedCoherency:));

/// Unavailable - use ``init(grantedCoherency:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

/// The result of an upgrade-item call.
///
/// Use this type in your implementation of ``FSVolume/DataCacheHandler/upgrade(_:cacheMode:context:replyHandler:)``.
FSKIT_API_AVAILABILITY_V3
@interface FSUpgradeItemResult : FSVolumeHandlerResult

/// Creates an upgrade-item result.
///
/// - Parameters:
///   - grantedCoherency: The ``FSKernelCacheCoherencyType`` granted by the module after the upgrade.
/// - Returns: A populated result instance, or `nil` if validation fails.
- (instancetype)initWithGrantedCoherency:(FSKernelCacheCoherencyType)grantedCoherency
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(grantedCoherency:));

/// Unavailable - use ``init(grantedCoherency:)`` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
