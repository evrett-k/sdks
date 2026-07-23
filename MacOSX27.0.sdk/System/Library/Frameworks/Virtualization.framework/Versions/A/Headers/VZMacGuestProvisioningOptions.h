//
//  VZMacGuestProvisioningOptions.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGuestProvisioningOptions.h>

#ifdef __arm64__

NS_ASSUME_NONNULL_BEGIN


/// The configuration for guest setup during macOS virtual machine startup.
///
/// > Note: This configuration requires guest macOS 27 or later to function properly. Earlier versions
///    of macOS don't support the automated guest configuration protocol and ignore these settings.
///
/// This configuration class provides automated setup capabilities for macOS virtual machines
/// that allow hosts to configure a user account and initial setup workflows without
/// manual intervention during the guest boot process.
///
/// The configuration enables automated macOS installation and setup workflows by providing user
/// credentials and setup preferences to the guest system during startup.
///
/// macOS only evaluates these options on the first boot after restore. The Virtualization framework can't use them
/// to reconfigure macOS once the framework has already provisioned it.
///
/// Changes to the properties after starting the virtual machine have no effect.
///
/// ## See Also
///
///  - ``VZGuestProvisioningOptions``
///  - ``VZMacOSVirtualMachineStartOptions``
///
VZ_EXPORT API_AVAILABLE(macos(27.0))
NS_REQUIRES_PROPERTY_DEFINITIONS
NS_SWIFT_SENDABLE
@interface VZMacGuestProvisioningOptions : VZGuestProvisioningOptions <NSCopying>

- (instancetype)init;

///
/// A person's full name to configure for the macOS virtual machine.
///
@property (readwrite, copy) NSString *fullName;

///
/// The username for logging into the macOS virtual machine.
///
@property (readwrite, copy) NSString *username;

///
/// The password to configure for the macOS virtual machine.
///
@property (readwrite, copy) NSString *password;

///
/// A Boolean value that indicates whether to automatically log in the person at startup.
///
@property (readwrite) BOOL logsInAutomatically;

/// A Boolean value that indicates whether to enable Remote Login (using SSH) for the macOS virtual machine.
///
/// Defaults to `NO`.
@property (readwrite) BOOL enablesRemoteLogin;

@end

NS_ASSUME_NONNULL_END

#endif
