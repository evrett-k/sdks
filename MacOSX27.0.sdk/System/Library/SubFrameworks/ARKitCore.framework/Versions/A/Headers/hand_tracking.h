//
//  hand_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef hand_tracking_h
#define hand_tracking_h

#import <ARKitCore/anchor.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/hand_skeleton.h>
#import <ARKitCore/object.h>
#import <ARKitCore/session.h>
#import <ARKitCore/transform_correction.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

/**
 Status enum values for the hand anchor at a specified timestamp from the provider.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
OS_ENUM(ar_hand_anchor_query_status, intptr_t,
    // The hand anchor at the specified timestamp was successfully obtained.
    ar_hand_anchor_query_status_success = 0,
    // The hand anchor at the specified timestamp failed to be obtained.
    ar_hand_anchor_query_status_failure)
AR_REFINED_FOR_SWIFT;

/**
 An anchor that tracks a hand's position and skeleton.
 */
AR_OBJECT_DECL_SUBCLASS(ar_hand_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst);

/**
 Configuration for hand tracking.
 */
AR_OBJECT_DECL(ar_hand_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst);

/**
 A data provider for hand tracking.
 */
AR_OBJECT_DECL_SUBCLASS(ar_hand_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst);

#pragma mark - Hand Anchor

/**
 Enum for the chirality of a hand.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
OS_ENUM(ar_hand_chirality, intptr_t,
        ar_hand_chirality_right,
        ar_hand_chirality_left
) AR_REFINED_FOR_SWIFT;

/**
 Enum for hand fidelity.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
OS_ENUM(ar_hand_fidelity, intptr_t,
        ar_hand_fidelity_nominal,
        ar_hand_fidelity_high
) AR_REFINED_FOR_SWIFT;

/**
 Create a hand anchor.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_hand_anchor_t`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_hand_anchor_t ar_hand_anchor_create(void) AR_REFINED_FOR_SWIFT;

/**
 Returns a bool value that indicates whether the two hand anchors are equal.

 - Parameters:
   - anchor: A hand anchor to be compared.
   - other_anchor: The other hand anchor to be compared to.

 - Returns: `YES` if the hand anchors are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_hand_anchor_is_equal_to_hand_anchor(ar_hand_anchor_t _Nullable anchor,
                                                      ar_hand_anchor_t _Nullable other_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the hand skeleton of a hand anchor.

 - Parameter hand_anchor: The hand anchor.

 - Returns: The skeleton.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN ar_hand_skeleton_t _Nullable ar_hand_anchor_get_hand_skeleton(ar_hand_anchor_t hand_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the chirality of the hand tracked by a hand anchor.

 - Parameter hand_anchor: The hand anchor.

 - Returns: The chirality of the hand.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN ar_hand_chirality_t ar_hand_anchor_get_chirality(ar_hand_anchor_t hand_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the fidelity of the hand anchor.

 - Parameter hand_anchor: The hand anchor.

 - Returns: The fidelity of the anchor.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN ar_hand_fidelity_t ar_hand_anchor_get_fidelity(ar_hand_anchor_t hand_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Hand Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_hand_anchor_get_identifier(ar_hand_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Note: This function will return a rendering-corrected transform and is equal to calling
 `ar_hand_anchor_get_origin_from_anchor_transform_with_correction` with `ar_transform_correction_rendered`.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_hand_anchor_get_origin_from_anchor_transform(ar_hand_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - hand_anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(27.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_hand_anchor_get_origin_from_anchor_transform_with_correction(
    ar_hand_anchor_t hand_anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN CFTimeInterval ar_hand_anchor_get_timestamp(ar_hand_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 - Parameter anchor: The anchor.

 - Returns: `true` if the anchor is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_hand_anchor_is_tracked(ar_hand_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Hand Tracking Configuration

#ifdef __BLOCKS__
/**
 Handler called when there are updates to hand tracking.

 - Parameters:
   - hand_anchor_left: The latest left hand anchor.
   - hand_anchor_right: The latest right hand anchor.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_hand_tracking_update_handler_t)(ar_hand_anchor_t hand_anchor_left, ar_hand_anchor_t hand_anchor_right) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function to be called when there are updates to hand tracking.

 - Parameters:
   - context: The application-defined context.
   - hand_anchor_left: The latest left hand anchor.
   - hand_anchor_right: The latest right hand anchor.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (*ar_hand_tracking_update_handler_function_t)(void *_Nullable context,
                                                           ar_hand_anchor_t hand_anchor_left,
                                                           ar_hand_anchor_t hand_anchor_right) AR_REFINED_FOR_SWIFT;

/**
 Create a hand tracking configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_hand_tracking_configuration_t`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_hand_tracking_configuration_t ar_hand_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - Hand Tracking Provider

/**
 Create a hand tracking provider.

 - Parameter hand_tracking_configuration: The configuration for hand tracking.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_hand_tracking_provider_t`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_hand_tracking_provider_t
ar_hand_tracking_provider_create(ar_hand_tracking_configuration_t hand_tracking_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving hand tracking updates.

 - Parameters:
   - hand_tracking_provider: The hand tracking provider.
   - hand_anchor_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - hand_tracking_update_handler: The handler to be called when new data arrives.

 - Note: Setting this handler will override the function set using `ar_hand_tracking_provider_set_update_handler_f`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void
ar_hand_tracking_provider_set_update_handler(ar_hand_tracking_provider_t hand_tracking_provider,
                                             dispatch_queue_t _Nullable hand_anchor_updates_queue,
                                             ar_hand_tracking_update_handler_t _Nullable hand_tracking_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving hand tracking updates.

 - Parameters:
   - hand_tracking_provider: The hand tracking provider.
   - hand_anchor_updates_queue: The queue on which the function will be called. Passing NULL will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - hand_tracking_update_handler_function: The function to be called when new data arrives.

 - Note: Setting this function will override the handler set using `ar_hand_tracking_provider_set_update_handler`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_hand_tracking_provider_set_update_handler_f(
    ar_hand_tracking_provider_t hand_tracking_provider,
    dispatch_queue_t _Nullable hand_anchor_updates_queue,
    void *_Nullable context,
    ar_hand_tracking_update_handler_function_t _Nullable hand_tracking_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the hand tracking provider.

 - Returns: `true` if the hand tracking provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_hand_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Fill the given `ar_hand_anchor_t` instances with the latest hand tracking data. Subsequent calls will continue returning the latest hand tracking

 data. New anchor data will be returned when the hand tracking data is updated.

 - Note: For apps compiled with a visionOS 1.0 SDK, subsequent calls to this function will not update the given `ar_hand_anchor_t` instances, and will
 return `false` until the latest hand tracking data has arrived.

 - Parameters:
   - hand_tracking_provider: The hand tracking provider.
   - hand_anchor_left: The `ar_hand_anchor_t` instance for the left hand to be updated.
   - hand_anchor_right: The `ar_hand_anchor_t` instance for the right hand to be updated.

 - Returns: `true` on success while the `hand_tracking_provider` is running, `false` otherwise.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_hand_tracking_provider_get_latest_anchors(ar_hand_tracking_provider_t hand_tracking_provider,
                                                            ar_hand_anchor_t hand_anchor_left,
                                                            ar_hand_anchor_t hand_anchor_right) AR_REFINED_FOR_SWIFT;

/**

 The provided `timestamp`when rendering should be obtained from `cp_frame_timing_get_trackable_anchor_time`.

 ```objc
 cp_time_t anchor_prediction_time = cp_frame_timing_get_trackable_anchor_time(timing);
 CFTimeInterval anchor_prediction_time_seconds = cp_time_to_cf_time_interval(anchor_prediction_time);

 ar_hand_tracking_provider_query_anchors_at_timestamp(provider, hand_anchor_left, hand_anchor_right);

 if (ar_trackable_anchor_is_tracked(hand_anchor_left)) {
    ...
 }

 if (ar_trackable_anchor_is_tracked(hand_anchor_right)) {
    ...
 }
 ```

 - Parameters:
   - hand_tracking_provider: The hand tracking provider.
   - timestamp: Target timestamp, mach absolute time in seconds.
   - hand_anchor_left: The anchor instance for the left hand to be updated.
   - hand_anchor_right: The anchor instance for the right hand to be updated.

 - Returns: Whether the query was successful or not.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN
ar_hand_anchor_query_status_t ar_hand_tracking_provider_query_anchors_at_timestamp(ar_hand_tracking_provider_t hand_tracking_provider,
                                                                                   CFTimeInterval timestamp,
                                                                                   ar_hand_anchor_t hand_anchor_left,
                                                                                   ar_hand_anchor_t hand_anchor_right) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the hand tracking provider.

 - Returns: The required authorization type.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN ar_authorization_type_t ar_hand_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // hand_tracking_h
