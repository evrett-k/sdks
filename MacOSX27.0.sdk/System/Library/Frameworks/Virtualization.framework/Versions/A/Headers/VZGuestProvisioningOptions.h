//
//  VZGuestProvisioningOptions.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// The base class for guest provisioning options.
///
/// Don't instantiate `VZGuestProvisioningOptions` directly; instead, use one of its subclasses, such as ``VZMacGuestProvisioningOptions``.
///
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZGuestProvisioningOptions : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;


/// Validates the provisioning options.
///
/// If validation fails, the error parameter contains a ``VZError`` with a guest provisioning error code.
///
/// - Parameter error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error.
/// - Returns: `YES` if validation succeeds, `NO` otherwise.
///
/// ## See Also
///
///  - ``VZErrorCode``
///
- (BOOL)validateWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
