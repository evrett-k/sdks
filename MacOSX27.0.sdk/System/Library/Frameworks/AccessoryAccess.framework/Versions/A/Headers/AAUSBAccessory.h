//
//  AAUSBAccessory.h
//  AccessoryAccess
//
//  Copyright © 2023-2026 Apple Inc. All rights reserved.
//

#import <AccessoryAccess/AADefines.h>

NS_ASSUME_NONNULL_BEGIN

@class IOUSBHostDevice;

/*!
 @abstract Class representing a USB accessory.
 @discussion
    A USB accessory can either be obtained from the `[AAUSBAccessoryListener usbAccessoryDidConnect:]` method, or
    instantiated from an XPC representation representing an already existing USB accessory.
 @see AAUSBAccessoryListener
 */
AA_EXPORT API_AVAILABLE(macos(27.0)) NS_SWIFT_SENDABLE
@interface AAUSBAccessory : NSObject<NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Creates a USB accessory from an XPC representation.
 @param xpcRepresentation The XPC representation of an `AAUSBAccessory` object received via XPC.
 @return An `AAUSBAccessory` object if the given `xpc_object_t` is decoded successfully, or nil if it is invalid.
 */
- (nullable instancetype)initWithXPCRepresentation:(xpc_object_t)xpcRepresentation NS_DESIGNATED_INITIALIZER;

/*! @abstract Returns the IORegistry ID for the USB accessory. */
@property (readonly) uint64_t registryID;

/*!
 @abstract Returns the device descriptor data.
 @discussion
    The underlying bytes can be cast to `IOUSBDeviceDescriptor`.
 @see IOUSBDeviceDescriptor
 */
@property (readonly) NSData *deviceDescriptorData;

/*!
 @abstract Returns the currently selected configuration descriptor data.
 @discussion
    The underlying bytes can be cast to `IOUSBConfigurationDescriptor*` and passed to USB descriptor parsing API
    to parse other descriptors. If the USB accessory is not configured, this returns `nil`.
 @see IOUSBConfigurationDescriptor
 */
@property (readonly, nullable) NSData *configurationDescriptorData;

/*!
 @abstract Creates an encoded representation of the USB accessory.
 @discussion
    A USB accessory can be encoded to `xpc_object_t`, and passed to an XPC service over an XPC connection.
 */
- (xpc_object_t)createXPCRepresentation;

/*!
 @abstract Opens a connection to the USB accessory for this process to access it exclusively.
 @discussion
    This operation opens a connection to the USB accessory for exclusive access and returns its `IOUSBHostDevice` object.
    Multiple connections can be opened to the accessory from a process, each represented by a different `IOUSBHostDevice` object.

    If the accessory was already opened by another worker process of this client application then this operation will
    fail with the `AAErrorCodeAccessoryNotAccessible` error. If the accessory is not in a state to be opened for exclusive access,
    then this operation fails with the `AAErrorCodeInvalidAccessoryState` error.

    When the process no longer needs exclusive access to this accessory, call `closeWithCompletionHandler:` to close the
    accessory. This will close all open connections to the accessory and invalidate all the `IOUSBHostDevice` objects.
 @param serviceQueue A serial queue that should be used to service all the asynchronous requests submitted to the default control endpoint.
    By default an internal serial queue will be created for the client process.
 @param completionHandler Block called after the client has successfully opened the USB accessory.
    The error parameter passed to the block is nil if the operation was successful.
    The block will be invoked on an arbitrary thread.
 @see IOUSBHostDevice
 */
- (void)openWithServiceQueue:(nullable dispatch_queue_t)serviceQueue completionHandler:(void (NS_SWIFT_SENDABLE ^)(IOUSBHostDevice * _Nullable_on_error, NSError * _Nullable))completionHandler NS_SWIFT_NAME(open(serviceQueue:completionHandler:));

/*!
 @abstract Closes all connections to the USB accessory for this process.
 @discussion
    This operation closes the USB accessory, that was previously opened through `openWithServiceQueue:completionHandler:`.
    Once this operation is completed, any `IOUSBHostDevice` object that was returned previously is invalidated and cannot be
    used for USB transfers. This operation has the same effect as calling `-[IOUSBHostDevice destroy]`.

    Once the accessory is closed, the accessory can be reopened by this process or any other worker process of this client
    application for exclusive access using `openWithServiceQueue:completionHandler:`.
 @warning
    Closing an accessory via `-[IOUSBHostDevice destroy]` is a blocking operation. Such an operation
    will cause deadlock, if executed from a completion handler.
 @param completionHandler Block called after the client has successfully closed the USB accessory.
    The error parameter passed to the block is nil if the operation was successful.
    The block will be invoked on an arbitrary thread.
 @see IOUSBHostDevice
 */
- (void)closeWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable))completionHandler NS_SWIFT_NAME(close(completionHandler:));

@end

NS_ASSUME_NONNULL_END
