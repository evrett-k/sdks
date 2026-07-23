//
//  data.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef data_h
#define data_h

#import <ARKitCore/object.h>

#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

/**
 A container for binary data.
 */
AR_OBJECT_DECL(ar_data)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst);

#pragma mark - Data

/**
 Get a pointer to the data's bytes.

 - Returns: A pointer to the data's bytes.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN const void *ar_data_get_bytes(ar_data_t data) AR_REFINED_FOR_SWIFT;

/**
 Get the length of the data, in bytes.

 - Parameter data: The data.

 - Returns: The length of the data, in bytes.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN size_t ar_data_get_length(ar_data_t data) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // data_h
