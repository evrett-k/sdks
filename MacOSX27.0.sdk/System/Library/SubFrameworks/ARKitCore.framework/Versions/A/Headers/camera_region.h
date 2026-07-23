//
//  camera_region.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef camera_region_h
#define camera_region_h

#import <ARKitCore/anchor.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/error.h>
#import <ARKitCore/object.h>
#import <ARKitCore/transform_correction.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <simd/simd.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 An anchor representing a camera region with enhanced image processing.
 */
AR_OBJECT_DECL_SUBCLASS(ar_camera_region_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 A collection of camera region anchors.
 */
AR_OBJECT_DECL(ar_camera_region_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 Configuration for camera region processing.
 */
AR_OBJECT_DECL(ar_camera_region_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 A data provider for camera region processing.
 */
AR_OBJECT_DECL_SUBCLASS(ar_camera_region_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 Error codes specific to the camera region provider.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_camera_region_error_code,
        ar_error_code_t,
        /// Error code indicating that a camera region anchor failed to be added.
        ar_camera_region_error_code_add_anchor_failed = 1300,
        /// Error code indicating that the maximum amount of camera region anchors for its respective camera enhancement have been added.
        ar_camera_region_error_code_anchor_max_limit_reached = 1301,
        /// Error code indicating that a camera region anchor failed to be removed.
        ar_camera_region_error_code_remove_anchor_failed = 1302)
AR_REFINED_FOR_SWIFT;

/**
 Enum describing camera enhancement types.
 - Note: These will affect the frame rate of the output.
*/
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_camera_region_camera_enhancement,
        intptr_t,
        /** Solely camera stabilization. Implicitly included in other enhancements. */
        ar_camera_region_stabilization = 0,
        /** Contrast & Vibrancy enhancement. */
        ar_camera_region_contrast_and_vibrancy = 1, )
AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Region Anchor

/**
 Returns a bool value that indicates whether the two camera region anchors are equal.

 - Parameters:
   - camera_region_anchor: A camera region anchor to be compared.
   - other_camera_region_anchor: The other camera region anchor to be compared to.

 - Returns: `true` if the camera region anchors are equal, `false` otherwise.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool
    ar_camera_region_anchor_is_equal_to_camera_region_anchor(ar_camera_region_anchor_t _Nullable camera_region_anchor,
                                                             ar_camera_region_anchor_t _Nullable other_camera_region_anchor) AR_REFINED_FOR_SWIFT;

/**
 Create a camera region anchor using a transform from the anchor to the origin coordinate system, a specified size, and a camera enhancement.

 - Parameters:
   - origin_from_anchor_transform: The origin from anchor transform.
   - width: The width of the anchor (along the X-axis), in meters.
   - height: The height of the anchor (along the Y-axis), in meters.
   - camera_enhancement: The desired camera enhancement.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_camera_region_anchor_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_camera_region_anchor_t
ar_camera_region_anchor_create_with_parameters(simd_float4x4 origin_from_anchor_transform,
                                               float width,
                                               float height,
                                               ar_camera_region_camera_enhancement_t camera_enhancement) AR_REFINED_FOR_SWIFT;

/**
 Get the width of a given anchor.

 - Parameter camera_region_anchor: The anchor.

 - Returns: The width of the anchor.
 - Note: The width of the anchor is the length along the X-axis, in meters. This is [-width/2, width/2] from the center.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN float ar_camera_region_anchor_get_width(ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the height of a given anchor.

 - Parameter camera_region_anchor: The anchor.

 - Returns: The height of the anchor.
 - Note: The height of the anchor is the length along the Y-axis, in meters. This is [-height/2, height/2] from the center.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN float ar_camera_region_anchor_get_height(ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the camera enhancement type for a given anchor.

 - Parameter camera_region_anchor: The anchor.

 - Returns: The anchor's camera enhancement.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_camera_region_camera_enhancement_t ar_camera_region_anchor_get_camera_enhancement(ar_camera_region_anchor_t camera_region_anchor)
    AR_REFINED_FOR_SWIFT;

/**
 Get the `CVPixelBufferRef` for this anchor.

 - Parameter camera_region_anchor: The anchor.

 - Returns: The pixel buffer, or NULL if not set. Retain and release as necessary.
 - Note: Retaining too many pixel buffers may lead to memory issues.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN CVPixelBufferRef _Nullable ar_camera_region_anchor_get_pixel_buffer(ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Region Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - camera_region_anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_anchor_get_identifier(ar_camera_region_anchor_t camera_region_anchor,
                                                      uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter camera_region_anchor: The anchor.

 - Returns: The transform of the anchor.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN simd_float4x4 ar_camera_region_anchor_get_origin_from_anchor_transform(ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - camera_region_anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The transform of the anchor.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN simd_float4x4 ar_camera_region_anchor_get_origin_from_anchor_transform_with_correction(
    ar_camera_region_anchor_t camera_region_anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter camera_region_anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN CFTimeInterval ar_camera_region_anchor_get_timestamp(ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Region Anchors Collection

/**
 Get the count of camera region anchors in a collection.

 - Parameter camera_region_anchors: The collection of camera region anchors.

 - Returns: The number of camera region anchors in the collection.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN size_t ar_camera_region_anchors_get_count(ar_camera_region_anchors_t camera_region_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of camera region anchors.

 - Parameter camera_region_anchor: The camera region anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (^ar_camera_region_anchors_enumerator_t)(ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of camera region anchors.

 - Parameters:
   - camera_region_anchors: The collection of camera region anchors.
   - camera_region_anchors_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void
ar_camera_region_anchors_enumerate_anchors(ar_camera_region_anchors_t camera_region_anchors,
                                           ar_camera_region_anchors_enumerator_t camera_region_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of camera region anchors.

 - Parameters:
   - context: The application-defined context.
   - camera_region_anchor: The camera region anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (*ar_camera_region_anchors_enumerator_function_t)(void *_Nullable context,
                                                               ar_camera_region_anchor_t camera_region_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of camera region anchors using a function.

 - Parameters:
   - camera_region_anchors: The collection of camera region anchors.
   - context: The application-defined context parameter to pass to the function.
   - camera_region_anchors_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_anchors_enumerate_anchors_f(ar_camera_region_anchors_t camera_region_anchors,
                                                            void *_Nullable context,
                                                            ar_camera_region_anchors_enumerator_function_t camera_region_anchors_enumerator_function)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Region Configuration

/**
 Create a camera region configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_camera_region_configuration_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_camera_region_configuration_t ar_camera_region_configuration_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Region Provider

/**
 Create a camera region provider.

 - Parameter camera_region_configuration: Camera Region configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_camera_region_provider_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_camera_region_provider_t
ar_camera_region_provider_create(ar_camera_region_configuration_t camera_region_configuration) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the camera region provider.

 - Returns: `true` if the camera region provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_camera_region_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the camera region provider.

 - Returns: The required authorization type.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_authorization_type_t ar_camera_region_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when there are updates to a specific camera region anchor.

 - Parameters:
   - added_anchor: The anchor that was added.
   - updated_anchor: The anchor that was updated.
   - removed_anchor: The anchor that was removed.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_camera_region_anchor_update_handler_t)(_Nullable ar_camera_region_anchor_t added_anchor,
                                                         _Nullable ar_camera_region_anchor_t updated_anchor,
                                                         _Nullable ar_camera_region_anchor_t removed_anchor) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving camera region updates for a specific anchor identifier.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor_identifier: The camera region anchor identifier to get updates for.
   - camera_region_anchor_updates_queue: The queue on which the handler will be called. Passing NULL will default to the main queue.
   - camera_region_anchor_update_handler: The handler to be called when new camera region anchor data arrives.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_set_update_handler_for_anchor_with_identifier(
    ar_camera_region_provider_t camera_region_provider,
    uuid_t _Nonnull camera_region_anchor_identifier,
    dispatch_queue_t _Nullable camera_region_anchor_updates_queue,
    ar_camera_region_anchor_update_handler_t _Nullable camera_region_anchor_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to a specific camera region anchor.

 - Parameters:
   - context: The application-defined context.
   - added_anchor: The anchor that was added.
   - updated_anchor: The anchor that was updated.
   - removed_anchor: The anchor that was removed.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_camera_region_anchor_update_handler_function_t)(void *_Nullable context,
                                                                  ar_camera_region_anchor_t added_anchor,
                                                                  ar_camera_region_anchor_t updated_anchor,
                                                                  ar_camera_region_anchor_t removed_anchor) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving camera region updates for a specific anchor identifier.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor_identifier: The camera region anchor identifier to get updates for.
   - camera_region_anchor_updates_queue: The queue on which the function will be called. Passing NULL will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - camera_region_anchor_update_handler_function: The function to be called when new camera region anchor data arrives.

 - Note: Setting this function will override the handler set using `ar_camera_region_provider_set_update_handler_for_anchor_with_identifier`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_set_update_handler_for_anchor_with_identifier_f(
    ar_camera_region_provider_t camera_region_provider,
    uuid_t _Nonnull camera_region_anchor_identifier,
    dispatch_queue_t _Nullable camera_region_anchor_updates_queue,
    void *_Nullable context,
    ar_camera_region_anchor_update_handler_function_t _Nullable camera_region_anchor_update_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when a request to add a camera region anchor has completed (successfully or not).

 - Parameters:
   - camera_region_anchor: The camera region anchor to be added.
   - successful: `true` if the camera region anchor was successfully added, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_camera_region_add_anchor_completion_handler_t)(ar_camera_region_anchor_t camera_region_anchor,
                                                                 bool successful,
                                                                 ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Add a camera region anchor to a camera region provider.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor: The camera region anchor to add.
   - add_anchor_completion_handler: The handler to be called after the request to add the camera region anchor completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_add_camera_region_anchor(ar_camera_region_provider_t camera_region_provider,
                                                                  ar_camera_region_anchor_t camera_region_anchor,
                                                                  ar_camera_region_add_anchor_completion_handler_t add_anchor_completion_handler)
    AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when a request to add a camera region anchor has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - camera_region_anchor: The camera region anchor to be added.
   - successful: `true` if the camera region anchor was successfully added, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_camera_region_add_anchor_completion_handler_function_t)(void *_Nullable context,
                                                                          ar_camera_region_anchor_t camera_region_anchor,
                                                                          bool successful,
                                                                          ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Add a camera region anchor to an camera region provider using a function.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor: The camera region anchor to add.
   - context: The application-defined context parameter to pass to the function.
   - add_anchor_completion_handler_function: The function to be called after the request to add the camera region anchor completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_add_camera_region_anchor_f(
    ar_camera_region_provider_t camera_region_provider,
    ar_camera_region_anchor_t camera_region_anchor,
    void *_Nullable context,
    ar_camera_region_add_anchor_completion_handler_function_t add_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when a request to remove a camera region anchor has completed (successfully or not).

 - Parameters:
   - camera_region_anchor: The camera region anchor to be removed.
   - successful: `true` if the camera region anchor was successfully removed, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_camera_region_remove_anchor_completion_handler_t)(ar_camera_region_anchor_t camera_region_anchor,
                                                                    bool successful,
                                                                    ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a camera region anchor from a camera region provider.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor: The camera region anchor.
   - remove_anchor_completion_handler: The handler to be called after the request to remove the camera region anchor completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_remove_camera_region_anchor(
    ar_camera_region_provider_t camera_region_provider,
    ar_camera_region_anchor_t camera_region_anchor,
    ar_camera_region_remove_anchor_completion_handler_t remove_anchor_completion_handler) AR_REFINED_FOR_SWIFT;

/**
 Handler called when a request to remove a camera region anchor by its identifier has completed (successfully or not).

 - Parameters:
   - camera_region_anchor_identifier: The identifier of the camera region anchor requested to be removed.
   - successful: `true` if the camera region anchor was successfully removed, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_camera_region_remove_anchor_with_identifier_completion_handler_t)(uuid_t _Nonnull camera_region_anchor_identifier,
                                                                                    bool successful,
                                                                                    ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a camera region anchor from a camera region provider by its identifier.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor_identifier: The identifier of the camera region anchor to remove.
   - remove_anchor_with_identifier_completion_handler: The handler to be called after the request to remove the camera region anchor by its
     identifier completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_remove_camera_region_anchor_with_identifier(
    ar_camera_region_provider_t camera_region_provider,
    uuid_t _Nonnull camera_region_anchor_identifier,
    ar_camera_region_remove_anchor_with_identifier_completion_handler_t remove_anchor_with_identifier_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when a request to remove a camera region anchor has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - camera_region_anchor: The camera region anchor to be removed.
   - successful: `true` if the camera region anchor was successfully removed, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_camera_region_remove_anchor_completion_handler_function_t)(void *_Nullable context,
                                                                             ar_camera_region_anchor_t camera_region_anchor,
                                                                             bool successful,
                                                                             ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a camera region anchor from a camera region provider using a function.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor: The camera region anchor to remove.
   - context: The application-defined context parameter to pass to the function.
   - remove_anchor_completion_handler_function: The function to be called after the request to remove the camera region anchor completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_remove_camera_region_anchor_f(
    ar_camera_region_provider_t camera_region_provider,
    ar_camera_region_anchor_t camera_region_anchor,
    void *_Nullable context,
    ar_camera_region_remove_anchor_completion_handler_function_t remove_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Function called when a request to remove a camera region anchor by its identifier has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - camera_region_anchor_identifier: The identifier of the camera region anchor requested to be removed.
   - successful: `true` if the camera region anchor was successfully removed, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_camera_region_remove_anchor_with_identifier_completion_handler_function_t)(void *_Nullable context,
                                                                                             uuid_t _Nonnull camera_region_anchor_identifier,
                                                                                             bool successful,
                                                                                             ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a camera region anchor from a camera region provider by its identifier using a function.

 - Parameters:
   - camera_region_provider: The camera region provider.
   - camera_region_anchor_identifier: The identifier of the camera region anchor to remove.
   - context: The application-defined context parameter to pass to the function.
   - remove_anchor_with_identifier_completion_handler_function: The function to be called after the request to remove the camera region anchor by
     its identifier completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_region_provider_remove_camera_region_anchor_with_identifier_f(
    ar_camera_region_provider_t camera_region_provider,
    uuid_t _Nonnull camera_region_anchor_identifier,
    void *_Nullable context,
    ar_camera_region_remove_anchor_with_identifier_completion_handler_function_t remove_anchor_with_identifier_completion_handler_function)
    AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // camera_region_h
