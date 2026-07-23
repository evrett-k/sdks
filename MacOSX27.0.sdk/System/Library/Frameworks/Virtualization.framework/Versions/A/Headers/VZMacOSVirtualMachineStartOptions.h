//
//  VZMacOSVirtualMachineStartOptions.h
//  Virtualization
//
//  Copyright © 2022-2026 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZVirtualMachineStartOptions.h>

@class VZGuestProvisioningOptions;
@class VZMacGuestProvisioningOptions;

NS_ASSUME_NONNULL_BEGIN

///
/// Options that control startup behavior of a virtual machine using the macOS boot loader.
///
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZMacOSVirtualMachineStartOptions : VZVirtualMachineStartOptions

///
/// A Boolean value that indicates whether to start up from macOS Recovery.
///
@property BOOL startUpFromMacOSRecovery;

/// A value that controls provisioning a macOS guest.
///
/// This property allows someone to provision a macOS guest by setting ``VZMacGuestProvisioningOptions``.
///
@property (readonly, nullable, copy) VZMacGuestProvisioningOptions *guestProvisioningOptions API_AVAILABLE(macos(27.0));

/// Sets guest provisioning options with validation.
///
/// This method validates the provisioning options before setting them. If validation fails, the current options remain unchanged.
///
/// - Parameters:
///    - guestProvisioningOptions: The guest provisioning options to set, or `nil` to remove.
///    - error: On input, a pointer to an error object. If an error occurs, the framework sets this pointer to an actual error object containing the error.
/// - Returns: `YES` if the options were set successfully (or `nil` was passed), `NO` if validation failed.
///
/// ## See Also
/// 
///   - ``VZMacGuestProvisioningOptions``
///
- (BOOL)setGuestProvisioningOptions:(VZMacGuestProvisioningOptions * _Nullable)guestProvisioningOptions error:(NSError **)error API_AVAILABLE(macos(27.0));

@end

NS_ASSUME_NONNULL_END

#endif
