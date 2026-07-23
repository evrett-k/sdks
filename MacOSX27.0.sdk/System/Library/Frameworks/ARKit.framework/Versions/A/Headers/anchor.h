#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/anchor.h>)
//
//  anchor.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef anchor_h
#define anchor_h

#import <ARKit/object.h>

#import <CoreFoundation/CFDate.h>
#import <os/availability.h>
#import <simd/types.h>
#import <uuid/uuid.h>



AR_ASSUME_NONNULL_BEGIN

#pragma mark - Anchor

/**
 Represents the identity, location, and orientation of an object in world space.
 */
AR_OBJECT_DECL(ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))

AR_EXTERN simd_float4x4 ar_anchor_get_origin_from_anchor_transform(ar_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))

AR_EXTERN void ar_anchor_get_identifier(ar_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))

AR_EXTERN CFTimeInterval ar_anchor_get_timestamp(ar_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Trackable Anchor

/**
 An anchor that can be tracked over time.
 */
AR_OBJECT_DECL_SUBCLASS(ar_trackable_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

/**
 Determine whether an anchor is tracked.

 - Parameter anchor: The anchor.

 - Returns: `true` if the anchor is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))

AR_EXTERN bool ar_trackable_anchor_is_tracked(ar_trackable_anchor_t anchor) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // anchor_h
#else
#import <ARKitCore/anchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/anchor.h>)