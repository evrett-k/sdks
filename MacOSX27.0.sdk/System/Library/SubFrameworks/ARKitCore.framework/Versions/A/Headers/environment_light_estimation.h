//
//  environment_light_estimation.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef environment_light_estimation_h
#define environment_light_estimation_h

#ifdef __OBJC__
#import <Metal/Metal.h>
#endif // __OBJC__

#import <ARKitCore/anchor.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/object.h>
#import <ARKitCore/session.h>
#import <ARKitCore/transform_correction.h>

#import <dispatch/dispatch.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 An anchor providing environment lighting information for realistic rendering.
 */
AR_OBJECT_DECL_SUBCLASS(ar_environment_probe_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A collection of environment probe anchors.
 */
AR_OBJECT_DECL(ar_environment_probe_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 Configuration for environment light estimation.
 */
AR_OBJECT_DECL(ar_environment_light_estimation_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A data provider for environment light estimation.
 */
AR_OBJECT_DECL_SUBCLASS(ar_environment_light_estimation_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

#pragma mark - Environment Probe Anchor

/**
 Returns a bool value that indicates whether the two environment probe anchors are equal.

 - Parameters:
   - environment_probe_anchor: A environment probe anchor to be compared.
   - other_environment_probe_anchor: The other environment probe anchor to be compared to.

 - Returns: `YES` if the environment probe anchors are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_environment_probe_anchor_is_equal_to_environment_probe_anchor(
    ar_environment_probe_anchor_t _Nullable environment_probe_anchor,
    ar_environment_probe_anchor_t _Nullable other_environment_probe_anchor) AR_REFINED_FOR_SWIFT;

#ifdef __OBJC__
/**
 Get the environment texture of an environment probe anchor.

 The texture is provided as a cube using MTLTextureTypeCube,
             containing rgb floating point linear high-dynamic range values in P3 color space.

 - Parameter environment_probe: An environment probe anchor.

 - Note: Textures could be `nil` if the person is not in a well-lit environment. The lifetime of this texture is tied to the lifetime of the
 `ar_environment_probe_anchor_t`.

 - Returns: Returns a `MTLTextureTypeCube`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN id<MTLTexture> _Nullable ar_environment_probe_anchor_get_environment_texture(ar_environment_probe_anchor_t environment_probe)
    AR_REFINED_FOR_SWIFT;
#endif // __OBJC__

/**
 Get the camera scale reference of an environment probe anchor.

 The environment texture stores floating point linear high-dynamic range rgb values in P3 color space.
 In order to have a consistent brightness between texture updates, the cameraScaleReference allows you to translate the local brightness from the
 current environment texture to the absolute brightness range from the camera.

 - Parameter environment_probe: An environment probe anchor.

 - Returns: Returns the camera scale reference of a pixel with rgb value [1,1,1] in the environment texture.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN float ar_environment_probe_anchor_get_camera_scale_reference(ar_environment_probe_anchor_t environment_probe) AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Probe Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_probe_anchor_get_identifier(ar_environment_probe_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_environment_probe_anchor_get_origin_from_anchor_transform(ar_environment_probe_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN simd_float4x4 ar_environment_probe_anchor_get_origin_from_anchor_transform_with_correction(
    ar_environment_probe_anchor_t anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_environment_probe_anchor_get_timestamp(ar_environment_probe_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Probe Anchors Collection

/**
 Get the count of environment probe anchors in the collection.

 - Parameter environment_probe_anchors: The collection of environment probe anchors.

 - Returns: The number of environment probe anchors in the collection.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_environment_probe_anchors_get_count(ar_environment_probe_anchors_t environment_probe_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of environment probe anchors.

 - Parameter environment_probe_anchor: The environment probe anchor.

 - Returns: Return `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_environment_probe_anchors_enumerator_t)(ar_environment_probe_anchor_t environment_probe_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of environment probe anchors.

 - Parameters:
   - environment_probe_anchors: The collection of environment probe anchors.
   - environment_probe_anchors_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_environment_probe_anchors_enumerate_anchors(ar_environment_probe_anchors_t environment_probe_anchors,
                                               ar_environment_probe_anchors_enumerator_t environment_probe_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of environment probe anchors.

 - Parameters:
   - context: The application-defined context.
   - environment_probe_anchor: The environment probe anchor.

 - Returns: Return `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_environment_probe_anchors_enumerator_function_t)(void *_Nullable context,
                                                                   ar_environment_probe_anchor_t environment_probe_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of environment probe anchors.

 - Parameters:
   - environment_probe_anchors: The collection of environment probe anchors.
   - context: The application-defined context parameter to pass to the function.
   - environment_probe_anchors_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_probe_anchors_enumerate_anchors_f(
    ar_environment_probe_anchors_t environment_probe_anchors,
    void *_Nullable context,
    ar_environment_probe_anchors_enumerator_function_t environment_probe_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Light Estimation Configuration

/**
 Create an environment light estimation configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_environment_light_estimation_configuration_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_environment_light_estimation_configuration_t ar_environment_light_estimation_configuration_create(void)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Light Estimation Provider

#ifdef __BLOCKS__
/**
 Handler triggered when there are updates to environment probe anchors.

 - Parameters:
   - added_anchors: Collection of anchors that are added.
   - updated_anchors: Collection of anchors that are updated.
   - removed_anchors: Collection of anchors that are removed.
*/
API_AVAILABLE(visionos(2.0))
typedef void (^ar_environment_light_estimation_update_handler_t)(ar_environment_probe_anchors_t added_anchors,
                                                                 ar_environment_probe_anchors_t updated_anchors,
                                                                 ar_environment_probe_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function to be called when there are updates to environment probe anchors.

 - Parameters:
   - context: The application-defined context.
   - added_anchors: Collection of anchors that are added.
   - updated_anchors: Collection of anchors that are updated.
   - removed_anchors: Collection of anchors that are removed.
*/
API_AVAILABLE(visionos(2.0))
typedef void (*ar_environment_light_estimation_update_handler_function_t)(void *_Nullable context,
                                                                          ar_environment_probe_anchors_t added_anchors,
                                                                          ar_environment_probe_anchors_t updated_anchors,
                                                                          ar_environment_probe_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Create an environment light estimation provider.

 - Parameter environment_light_estimation_configuration: Environment light estimation configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_environment_light_estimation_provider_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_environment_light_estimation_provider_t ar_environment_light_estimation_provider_create(
    ar_environment_light_estimation_configuration_t environment_light_estimation_configuration) AR_REFINED_FOR_SWIFT;

/**
 Determines whether this device supports the environment light estimation provider.

 - Returns: Returns `true` if the environment light estimation provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_environment_light_estimation_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving environment light estimation updates.

 - Parameters:
   - environment_light_estimation_provider: Environment light estimation provider.
   - environment_light_estimation_anchor_updates_queue: Queue on which the handler will be executed,
     sending `NULL` will default to the main queue.
   - environment_light_estimation_update_handler: Handler to be triggered when new data
     arrives.

 - Note: Setting this function will override the handler set using `ar_environment_light_estimation_provider_set_probe_update_handler_f`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_light_estimation_provider_set_update_handler(
    ar_environment_light_estimation_provider_t environment_light_estimation_provider,
    dispatch_queue_t _Nullable environment_light_estimation_anchor_updates_queue,
    ar_environment_light_estimation_update_handler_t _Nullable environment_light_estimation_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving environment light estimation updates.

 - Parameters:
   - environment_light_estimation_provider: The environment light estimation provider.
   - environment_light_estimation_anchor_updates_queue: the queue on which the function will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - environment_light_estimation_update_handler_function: The function to be called when new data arrives.

 - Note: Setting this function will override the handler set using `ar_environment_light_estimation_provider_set_probe_update_handler`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_light_estimation_provider_set_update_handler_f(
    ar_environment_light_estimation_provider_t environment_light_estimation_provider,
    dispatch_queue_t _Nullable environment_light_estimation_anchor_updates_queue,
    void *_Nullable context,
    ar_environment_light_estimation_update_handler_function_t _Nullable environment_light_estimation_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the environment light estimation provider.

 - Returns: An authorization type.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_authorization_type_t ar_environment_light_estimation_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // environment_light_estimation_h
