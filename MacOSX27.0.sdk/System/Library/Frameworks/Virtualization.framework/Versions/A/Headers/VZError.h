//
//  VZError.h
//  Virtualization
//
//  Copyright © 2019-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

VZ_EXPORT NSErrorDomain const VZErrorDomain API_AVAILABLE(macos(11.0));

/// Error types the Virtualization framework returns.
///
/// The `NSError` domain is ``VZErrorDomain``; the code is one of the ``VZErrorCode`` constants.
/// The Virtualization framework can also report errors from other domains when the error originates from a lower level component.
///
typedef NS_ERROR_ENUM(VZErrorDomain, VZErrorCode) {
    /// An error that indicates there was an internal error, such as the virtual machine unexpectedly stopping.
    ///
    /// The framework reports this error when the virtual machine unexpectedly stops.
    VZErrorInternal NS_SWIFT_NAME(internalError) = 1,
    /// An error that indicates the machine configuration was invalid.
    ///
    /// This error indicates that your ``VZVirtualMachineConfiguration`` object contains invalid data.
    VZErrorInvalidVirtualMachineConfiguration = 2,
    /// An error that indicates the app used the API with a machine in the wrong state.
    ///
    /// This error occurs when the virtual machine is in the wrong state for the current operation. For example,
    /// you might receive this error when you attempt to interact with a stopped or paused virtual machine.
    VZErrorInvalidVirtualMachineState = 3,
    /// An error that indicates there was an invalid change of state.
    ///
    /// This error occurs when you attempt to change the state of the virtual machine in an invalid way.
    /// For example, it occurs when you attempt to start a virtual machine when its
    /// ``VZVirtualMachine/canStart`` property is `false`.
    VZErrorInvalidVirtualMachineStateTransition = 4,
    /// An error that indicates an unrecognized disk image format or invalid disk image.
    ///
    /// This error occurs when you supply a disk image in an unrecognized format, when there’s damage
    /// to the disk image, or the disk image is invalid.
    VZErrorInvalidDiskImage = 5,
    /// An error that indicates an attempt to start a virtual machine (VM) exceeded the limit of the number of running VMs the framework allows.
    ///
    /// This error occurs when starting a VM would exceed the system’s limit on the number of simultaneously running virtual machines.
    VZErrorVirtualMachineLimitExceeded API_AVAILABLE(macos(12.0)) = 6,
    /// An error that indicates a network issue, such as a failed connection error, occurred.
    VZErrorNetworkError API_AVAILABLE(macos(13.0)) = 7,
    /// An error that indicates the host ran out of disk space, such as while attempting to install Rosetta.
    VZErrorOutOfDiskSpace API_AVAILABLE(macos(13.0)) = 8,
    /// An error that indicates the framework cancelled the operation.
    VZErrorOperationCancelled API_AVAILABLE(macos(13.0)) = 9,
    /// An error that indicates the framework doesn't support the operation.
    VZErrorNotSupported API_AVAILABLE(macos(13.0)) = 10,
    /// An error that indicates the VM failed to save to the save file.
    VZErrorSave API_AVAILABLE(macos(14.0)) = 11,
    /// An error that indicates the restore operation failed.
    VZErrorRestore API_AVAILABLE(macos(14.0)) = 12,

    /* macOS installation errors. */
    /// An error that indicates the restore image catalog failed to load.
    VZErrorRestoreImageCatalogLoadFailed API_AVAILABLE(macos(13.0)) = 10001,
    /// An error that indicates the restore image catalog is invalid.
    VZErrorInvalidRestoreImageCatalog API_AVAILABLE(macos(13.0)) = 10002,
    /// An error that indicates the restore image catalog has no supported restore images.
    VZErrorNoSupportedRestoreImagesInCatalog API_AVAILABLE(macos(13.0)) = 10003,
    /// An error that indicates the restore image failed to load.
    VZErrorRestoreImageLoadFailed API_AVAILABLE(macos(13.0)) = 10004,
    /// An error that indicates the restore image is invalid.
    VZErrorInvalidRestoreImage API_AVAILABLE(macos(13.0)) = 10005,
    /// An error that indicates the installation requires a software update in order to complete.
    VZErrorInstallationRequiresUpdate API_AVAILABLE(macos(13.0)) = 10006,
    /// An error that indicates that an error occurred during installation.
    VZErrorInstallationFailed API_AVAILABLE(macos(13.0)) = 10007,

    /* Network Block Device errors. */
    /// An error that indicates the connection or the negotiation with the Network Block Device (NBD) server failed.
    VZErrorNetworkBlockDeviceNegotiationFailed API_AVAILABLE(macos(14.0)) = 20001,
    /// An error that indicates the Network Block Device (NBD) client disconnected from the server.
    VZErrorNetworkBlockDeviceDisconnected API_AVAILABLE(macos(14.0)) = 20002,

    /* USB device hot-plug errors. */
    /// An error that indicates the framework wasn't able to find the controller.
    VZErrorUSBControllerNotFound API_AVAILABLE(macos(15.0)) = 30001,
    /// An error that indicates the device is already attached.
    VZErrorDeviceAlreadyAttached API_AVAILABLE(macos(15.0)) = 30002,
    /// An error that indicates the device failed to initialize.
    VZErrorDeviceInitializationFailure API_AVAILABLE(macos(15.0)) = 30003,
    /// An error that indicates the framework wasn't able to find the specified device.
    VZErrorDeviceNotFound API_AVAILABLE(macos(15.0)) = 30004,

    /* Guest provisioning errors. */
    /// An error that indicates the full name for guest provisioning is invalid.
    VZErrorGuestProvisioningInvalidFullName API_AVAILABLE(macos(27.0)) = 40001,
    /// An error that indicates the username for guest provisioning is invalid.
    VZErrorGuestProvisioningInvalidUsername API_AVAILABLE(macos(27.0)) = 40002,
    /// An error that indicates the password for guest provisioning is invalid.
    VZErrorGuestProvisioningInvalidPassword API_AVAILABLE(macos(27.0)) = 40003,

    /* EFI Variable Store errors. */
    /// An error that indicates the Secure Boot signatures failed to enroll.
    VZErrorEFISecureBootEnrollmentFailed API_AVAILABLE(macos(27.0)) = 50001,
    /// An error that indicates the framework can't access the EFI variable store.
    VZErrorEFIVariableInaccessible API_AVAILABLE(macos(27.0)) = 50002,
} API_AVAILABLE(macos(11.0));
