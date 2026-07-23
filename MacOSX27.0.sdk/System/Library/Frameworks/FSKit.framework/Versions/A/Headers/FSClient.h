//
//  Copyright (c) 2022 Apple Inc. All rights reserved.
//
//  FSClient.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSModuleIdentity.h>
#import <FSKit/FSResource.h>

NS_ASSUME_NONNULL_BEGIN

/// An interface for apps and daemons to interact with FSKit.
///
/// FSClient is the primary management interface for FSKit.
/// Use this class to discover FSKit extensions installed on the system, including your own.
///
/// > Important: Don't subclass `FSClient`.
FSKIT_API_AVAILABILITY_V1
@interface FSClient : NSObject

-(instancetype)init NS_UNAVAILABLE;

/// The shared instance of the FSKit client class.
@property (class, readonly) FSClient *sharedInstance NS_SWIFT_NAME(shared);

/// Asynchronously retrieves an list of installed file system modules.
///
/// In Swift, you can either call this method and pass a completion handler closure, or get the value of the `installedExtensions` property with the `async` keyword.
///
/// - Parameter completionHandler: A block or closure that executes when FSKit finishes its fetch process. If the fetch succeeds, the first parameter contains an array of ``FSModuleIdentity`` instances that identify installed modules. If the fetch fails, the second parameter contains an error detailing the failure.
-(void)fetchInstalledExtensionsWithCompletionHandler:(void(^)(NSArray<FSModuleIdentity *> *_Nullable,
                                                              NSError *_Nullable))completionHandler FSKIT_API_AVAILABILITY_V1 NS_SWIFT_ASYNC_NAME(getter:installedExtensions());

/// Asynchronously mounts a single volume file system with a given resource.
///
/// This method allows a client with the `com.apple.developer.fskit.mount` entitlement to mount a single-volume file system.
/// Calling this method performs the complete workflow of resource loading, volume activation, mount point creation, and actual mounting.
/// The system mounts the volume within the `/Volumes/` directory.
///
/// The caller can only mount modules that are visible to them.
///
/// - Parameters:
///   - resource: The resource to mount.
///   - bundleID: The bundle identifier of the file system extension.
///   - options: An array of strings containing the `mount_XXX` mount options
///   - completionHandler: A block or closure to indicate success or failure. If mount fails, the first parameter is nil and second parameter contains an error. If mount succeeds, the first parameter contains the URL of the mount path, and second parameter is `nil`.
- (void)mountSingleVolumeForResource:(FSResource *)resource
                            bundleID:(NSString *)bundleID
                             options:(NSArray <NSString *> *)options
                   completionHandler:(void (^)(NSURL * _Nullable mountPath,
                                               NSError * _Nullable error))FSKIT_CALLED_ONCE completionHandler FSKIT_API_AVAILABILITY_V3 NS_SWIFT_NAME(mountSingleVolume(resource:bundleID:options:completionHandler:));

/// Opens the File System Extensions settings in System Settings.
///
/// Calling this method allows someone using your app to navigate to the File System Extensions pane in System Settings.
/// From this pane, they can view, enable, and disable file system extensions.
///
/// - Returns: `true` (Swift) or `YES` (Obj-C) if the settings were successfully opened; otherwise, `false` (Swift) or `NO`(Obj-C).
-(BOOL)openFileSystemExtensionsSettings FSKIT_API_AVAILABILITY_V3;

@end

NS_ASSUME_NONNULL_END
