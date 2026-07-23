//
//  error.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef error_h
#define error_h

#import <ARKitCore/object.h>

#import <CoreFoundation/CFBase.h>
#import <CoreFoundation/CFError.h>
#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Error

/**
 Represents an error in ARKit.
 */
AR_OBJECT_DECL(ar_error)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

/**
 The error domain for ARKit errors.
 */
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0)) AR_EXTERN const CFStringRef ar_error_domain AR_REFINED_FOR_SWIFT;
/**
 Error code type for ARKit errors.
 */
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0)) typedef intptr_t ar_error_code_t AR_REFINED_FOR_SWIFT;

/**
 Get the error code associated with an error.

 - Parameter error: The `ar_error_t` instance.

 - Returns: The error code.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN ar_error_code_t ar_error_get_error_code(ar_error_t error) AR_REFINED_FOR_SWIFT;

/**
 Copy out a `CFErrorRef` that represents an `ar_error_t`.

 - Parameter error: The `ar_error_t` instance.

 - Returns: The `CFErrorRef`. The caller is responsible for calling `CFRelease` on the returned pointer.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN CF_RETURNS_RETAINED CFErrorRef ar_error_copy_cf_error(ar_error_t error) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // error_h
