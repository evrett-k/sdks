#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/object_tracking.h>)
//
//  object_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef object_tracking_h
#define object_tracking_h

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/error.h>
#import <ARKit/object.h>
#import <ARKit/transform_correction.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/** An axis-aligned bounding box for the extent of an object. */
AR_OBJECT_DECL(ar_object_axis_aligned_bounding_box)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/** An object that was detected in the environment. */
AR_OBJECT_DECL_SUBCLASS(ar_object_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/** A collection of object anchors. */
AR_OBJECT_DECL(ar_object_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/** Defines a physical object to detect in the environment. */
AR_OBJECT_DECL(ar_reference_object)
AR_REFINED_FOR_SWIFT
AR_SWIFT_SENDABLE
API_AVAILABLE(visionos(2.0));

/** Defines a configuration for an individual reference object. */
AR_OBJECT_DECL(ar_reference_object_configuration)
AR_REFINED_FOR_SWIFT
AR_SWIFT_SENDABLE
API_AVAILABLE(visionos(27.0));

/** A collection of reference objects. */
AR_OBJECT_DECL(ar_reference_objects)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/** Object tracking configuration. */
AR_OBJECT_DECL(ar_object_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/** Object tracking provider. */
AR_OBJECT_DECL_SUBCLASS(ar_object_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

#pragma mark - Object Bounding Box

/**
 Returns a bool value that indicates whether the two bounding boxes are equal.

 - Parameters:
   - bounding_box: A bounding box to be compared.
   - other_bounding_box: The other bounding box to be compared to.

 - Returns: `YES` if the bounding boxes are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_object_axis_aligned_bounding_box_is_equal_to_bounding_box(ar_object_axis_aligned_bounding_box_t _Nullable bounding_box,
                                                                            ar_object_axis_aligned_bounding_box_t _Nullable other_bounding_box)
    AR_REFINED_FOR_SWIFT;

/**
 Get minimum X, Y, Z coordinates for the bounding box.

 - Parameter bounding_box: The bounding box.

 - Returns: Minimum X, Y, and Z.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float3 ar_object_axis_aligned_bounding_box_get_min(ar_object_axis_aligned_bounding_box_t bounding_box) AR_REFINED_FOR_SWIFT;

/**
 Get maximum X, Y, Z coordinates for the bounding box.

 - Parameter bounding_box: The bounding box.

 - Returns: Maximum X, Y, and Z.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float3 ar_object_axis_aligned_bounding_box_get_max(ar_object_axis_aligned_bounding_box_t bounding_box) AR_REFINED_FOR_SWIFT;

/**
 Get center coordinates for the bounding box.

 - Parameter bounding_box: The bounding box.

 - Returns: The center coordinates.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float3 ar_object_axis_aligned_bounding_box_get_center(ar_object_axis_aligned_bounding_box_t bounding_box) AR_REFINED_FOR_SWIFT;

/**
 Get extent for the bounding box.

 - Parameter bounding_box: The bounding box.

 - Returns: The extent.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float3 ar_object_axis_aligned_bounding_box_get_extent(ar_object_axis_aligned_bounding_box_t bounding_box) AR_REFINED_FOR_SWIFT;

#pragma mark - Object anchor

/**
 Returns a bool value that indicates whether the two object anchors are equal.

 - Parameters:
   - object_anchor: An object anchor to be compared.
   - other_object_anchor: The other object anchor to be compared to.

 - Returns: `YES` if the object anchors are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_object_anchor_is_equal_to_object_anchor(ar_object_anchor_t _Nullable object_anchor,
                                                          ar_object_anchor_t _Nullable other_object_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get bounding box for the object. Aligned with frame defining object's center and axes.

 - Parameter object_anchor: The object anchor.

 - Returns: The bounding box.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_object_axis_aligned_bounding_box_t ar_object_anchor_get_bounding_box(ar_object_anchor_t object_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the underlying tracked reference object from an object anchor.

 - Parameter object_anchor: The object anchor used for getting the reference object.

 - Returns: The `ar_reference_object_t` from the anchor.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_reference_object_t AR_SWIFT_SENDABLE ar_object_anchor_get_reference_object(ar_object_anchor_t object_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Object anchors collection

/**
 Get the count of object anchors in a collection.

 - Parameter object_anchors: The collection of object anchors.

 - Returns: The number of object anchors in the collection.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_object_anchors_get_count(ar_object_anchors_t object_anchors) AR_REFINED_FOR_SWIFT;

#pragma mark - Object Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_anchor_get_identifier(ar_object_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_object_anchor_get_origin_from_anchor_transform(ar_object_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - object_anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN simd_float4x4 ar_object_anchor_get_origin_from_anchor_transform_with_correction(
    ar_object_anchor_t object_anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_object_anchor_get_timestamp(ar_object_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 - Parameter anchor: The anchor.

 - Returns: `true` if the anchor is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_object_anchor_is_tracked(ar_object_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating a collection of object anchors.

 - Parameter object_anchor: The object anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_object_anchors_enumerator_t)(ar_object_anchor_t object_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of object anchors.

 - Parameters:
   - object_anchors: The collection of object anchors.
   - object_anchors_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_anchors_enumerate_anchors(ar_object_anchors_t object_anchors,
                                                   ar_object_anchors_enumerator_t object_anchors_enumerator) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of object anchors.

 - Parameters:
   - context: The application-defined context.
   - object_anchor: The object anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_object_anchors_enumerator_function_t)(void *_Nullable context, ar_object_anchor_t object_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of object anchors.

 - Parameters:
   - object_anchors: The collection of object anchors.
   - context: The application-defined context parameter to pass to the function.
   - object_anchors_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_anchors_enumerate_anchors_f(ar_object_anchors_t object_anchors,
                                                     void *_Nullable context,
                                                     ar_object_anchors_enumerator_function_t object_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Reference Object

/**
 Returns a bool value that indicates whether the two reference objects are equal.

 - Parameters:
   - reference_object: A reference object to be compared.
   - other_reference_object: The other reference object to be compared to.

 - Returns: `YES` if the reference objects are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_reference_object_is_equal_to_reference_object(ar_reference_object_t _Nullable reference_object,
                                                                ar_reference_object_t _Nullable other_reference_object) AR_REFINED_FOR_SWIFT;

/**
 Get identifier for the reference object.

 - Parameters:
   - reference_object: Reference object.
   - out_uuid: Object to fill with UUID.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_reference_object_get_identifier(ar_reference_object_t reference_object, uuid_t _Nonnull out_uuid) AR_REFINED_FOR_SWIFT;

/**
 Get the input file path used to load the reference object.

 - Parameter reference_object: Reference object.

 - Note: The returned value will have the same lifetime as the `ar_reference_object_t`.
 - Returns: The input file path.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN
CF_RETURNS_NOT_RETAINED CFURLRef _Nullable ar_reference_object_get_input_file_path(ar_reference_object_t reference_object) AR_REFINED_FOR_SWIFT;

/**
 Get path to a copy of the USDZ file for the object, if the object has one.

 - Parameter reference_object: Reference object.

 - Note: The returned value will have the same lifetime as the `ar_reference_object_t`.
 - Returns: The path to the USDZ file.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN
CF_RETURNS_NOT_RETAINED CFURLRef _Nullable ar_reference_object_get_usdz_file_path(ar_reference_object_t reference_object) AR_REFINED_FOR_SWIFT;

/**
 Get a reference object's name.

 - Parameter reference_object: The reference object.

 - Note: The returned value will have the same lifetime as the input `ar_reference_object_t`.

 - Returns: The name of the reference object, or `NULL` if no name is set.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN const char *ar_reference_object_get_name(ar_reference_object_t reference_object) AR_REFINED_FOR_SWIFT;

#pragma mark - Reference Object Configuration

/**
 Create a reference object configuration.

 - Note: Default values are set as follows: - `is_high_frame_rate_tracking_enabled`: `false`
 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_reference_object_configuration_t`.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_reference_object_configuration_t ar_reference_object_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Returns a bool value that indicates whether the two reference object configurations are equal.

 - Parameters:
   - reference_object_configuration: A reference object configuration to be compared.
   - other_reference_object_configuration: The other reference object configuration to be compared to.

 - Returns: `YES` if the reference object configurations are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN bool ar_reference_object_configuration_is_equal_to_reference_object_configuration(
    ar_reference_object_configuration_t _Nullable reference_object_configuration,
    ar_reference_object_configuration_t _Nullable other_reference_object_configuration) AR_REFINED_FOR_SWIFT;

/**
 Sets whether high-frame-rate tracking is enabled on this configuration.

 - Parameters:
   - reference_object_configuration: The configuration.
   - high_frame_rate_tracking_enabled: Whether to enable high frame rate tracking.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void ar_reference_object_configuration_enable_high_frame_rate_tracking(ar_reference_object_configuration_t reference_object_configuration,
                                                                                 bool high_frame_rate_tracking_enabled) AR_REFINED_FOR_SWIFT;

/**
 Checks whether high-frame-rate tracking is enabled on this configuration.

 - Parameter reference_object_configuration: The configuration.

 - Returns: The enablement status.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN bool ar_reference_object_configuration_is_high_frame_rate_tracking_enabled(
    ar_reference_object_configuration_t reference_object_configuration) AR_REFINED_FOR_SWIFT;

#pragma mark - Reference Object Loading

#ifdef __BLOCKS__

/**
 Handler triggered when a request to load a reference object from a URL has completed.

 - Parameters:
   - url: The URL for the reference object that was being loaded.
   - success: `true` if loading succeeded, `false` otherwise.
   - error: The error that occurred, if any.
   - reference_object: An instance of `ar_reference_object_t` (`NULL` if loading failed). The returned object supports ARC. In non-ARC files, use
     `ar_release()` to release it.
*/
API_AVAILABLE(visionos(2.0))
typedef void (^ar_reference_object_url_load_completion_handler_t)(CFURLRef url,
                                                                  bool success,
                                                                  ar_error_t _Nullable error,
                                                                  ar_reference_object_t _Nullable reference_object) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a URL.

 - Parameters:
   - url: The URL pointing to the reference object to load on the file system.
   - completion_handler: Handler triggered after the request to load an object completes.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_reference_object_load_from_url(CFURLRef url,
                                                 ar_reference_object_url_load_completion_handler_t completion_handler) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a URL.

 - Parameters:
   - url: The URL pointing to the reference object to load on the file system.
   - configuration: Reference object configuration to use.
   - completion_handler: Handler triggered after the request to load an object completes.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void
ar_reference_object_load_from_url_with_configuration(CFURLRef url,
                                                     ar_reference_object_configuration_t configuration,
                                                     ar_reference_object_url_load_completion_handler_t completion_handler) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function called when a request to load a reference object from a URL has completed.

 - Parameters:
   - context: The application-defined context.
   - url: The URL for the reference object that was being loaded.
   - success: `true` if loading succeeded, `false` otherwise.
   - error: The error that occurred, if any.
   - reference_object: An instance of `ar_reference_object_t` (NULL if loading failed). The returned object supports ARC. In non-ARC files, use
     `ar_release()` to release it.
*/
API_AVAILABLE(visionos(2.0))
typedef void (*ar_reference_object_url_load_completion_handler_function_t)(void *_Nullable context,
                                                                           CFURLRef url,
                                                                           bool success,
                                                                           ar_error_t _Nullable error,
                                                                           ar_reference_object_t _Nullable reference_object) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a URL.

 - Parameters:
   - url: The URL pointing to the reference object to load on the file system.
   - context: The application-defined context.
   - completion_handler_function: The function to be called after the request to load an object completes.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_reference_object_load_from_url_f(CFURLRef url,
                                    void *_Nullable context,
                                    ar_reference_object_url_load_completion_handler_function_t completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a URL.

 - Parameters:
   - url: The URL pointing to the reference object to load on the file system.
   - configuration: Reference object configuration to use.
   - context: The application-defined context.
   - completion_handler_function: Handler triggered after the request to load an object completes.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void ar_reference_object_load_from_url_with_configuration_f(
    CFURLRef url,
    ar_reference_object_configuration_t configuration,
    void *_Nullable context,
    ar_reference_object_url_load_completion_handler_function_t completion_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler triggered when a request to load a reference object from a bundle has completed.

 - Parameters:
   - name: The name of reference object that was being loaded from bundle.
   - bundle: The bundle used for loading the reference object.
   - success: `true` if loading succeeded, `false` otherwise.
   - error: The error that occurred, if any.
   - reference_object: An instance of `ar_reference_object_t` (`NULL` if loading failed). The returned object supports ARC. In non-ARC files, use
     `ar_release()` to release it.
*/
API_AVAILABLE(visionos(2.0))
typedef void (^ar_reference_object_bundle_load_completion_handler_t)(const char *name,
                                                                     CFBundleRef _Nullable bundle,
                                                                     bool success,
                                                                     ar_error_t _Nullable error,
                                                                     ar_reference_object_t _Nullable reference_object) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a bundle.

 - Parameters:
   - name: The name of reference object to load from bundle.
   - bundle: The bundle used for loading the reference object. The main bundle is used if `NULL`.
   - completion_handler: Handler triggered after the request to load an object completes.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_reference_object_load_with_name(const char *name,
                                                  CFBundleRef _Nullable bundle,
                                                  ar_reference_object_bundle_load_completion_handler_t completion_handler) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a bundle.

 - Parameters:
   - name: The name of reference object to load from bundle.
   - bundle: Bundle used for loading the reference object. The main bundle is used if NULL.
   - configuration: Reference object configuration to use.
   - completion_handler: Handler triggered after the request to load an object completes.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void
ar_reference_object_load_with_name_and_configuration(const char *name,
                                                     CFBundleRef _Nullable bundle,
                                                     ar_reference_object_configuration_t configuration,
                                                     ar_reference_object_bundle_load_completion_handler_t completion_handler) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function called when a request to load a reference object from a bundle has completed.

 - Parameters:
   - context: The application-defined context.
   - name: The name of reference object that was being loaded from bundle.
   - bundle: The bundle used for loading the reference object.
   - success: `true` if loading succeeded, `false` otherwise.
   - error: The error that occurred, if any.
   - reference_object: An instance of `ar_reference_object_t` (`NULL` if loading failed). The returned object supports ARC. In non-ARC files, use
     `ar_release()` to release it.
*/
API_AVAILABLE(visionos(2.0))
typedef void (*ar_reference_object_bundle_load_completion_handler_function_t)(void *_Nullable context,
                                                                              const char *name,
                                                                              CFBundleRef _Nullable bundle,
                                                                              bool success,
                                                                              ar_error_t _Nullable error,
                                                                              ar_reference_object_t _Nullable reference_object) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a bundle.

 - Parameters:
   - name: The name of reference object to load from bundle.
   - bundle: The bundle used for loading the reference object. The main bundle is used if `NULL`.
   - context: The application-defined context parameter to pass to the function.
   - completion_handler_function: The function to be called after the request to load an object completes.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_reference_object_load_with_name_f(const char *name,
                                     CFBundleRef _Nullable bundle,
                                     void *_Nullable context,
                                     ar_reference_object_bundle_load_completion_handler_function_t completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Load a reference object from a bundle.

 - Parameters:
   - name: The name of reference object to load from bundle.
   - bundle: Bundle used for loading the reference object. The main bundle is used if NULL.
   - configuration: Reference object configuration to use.
   - context: The application-defined context.
   - completion_handler_function: Handler triggered after the request to load an object completes.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void ar_reference_object_load_with_name_and_configuration_f(
    const char *name,
    CFBundleRef _Nullable bundle,
    ar_reference_object_configuration_t configuration,
    void *_Nullable context,
    ar_reference_object_bundle_load_completion_handler_function_t completion_handler_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Reference objects collection

/**
 Create an empty collection of reference objects.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_reference_objects_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_reference_objects_t ar_reference_objects_create(void) AR_REFINED_FOR_SWIFT;

/**
 Add a reference object to a collection.

 The object must be unique. A duplicate of any existing object in the collection will not be added.

 - Parameters:
   - reference_objects: The collection of reference objects to expand.
   - object_to_add: The reference object to add.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_reference_objects_add_object(ar_reference_objects_t reference_objects, ar_reference_object_t object_to_add) AR_REFINED_FOR_SWIFT;

/**
 Add reference objects to a collection.

 The objects must be unique. Duplicates of any existing object in the collection will not be added.

 - Parameters:
   - reference_objects: The collection of reference objects to expand.
   - objects_to_add: The collection of reference objects to add.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_reference_objects_add_objects(ar_reference_objects_t reference_objects, ar_reference_objects_t objects_to_add) AR_REFINED_FOR_SWIFT;

/**
 Get the count of reference objects in the collection.

 - Parameter reference_objects: The collection of reference objects.

 - Returns: The number of reference objects in the collection.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_reference_objects_get_count(ar_reference_objects_t reference_objects) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating a collection of reference objects.

 - Parameter reference_object: The reference object.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_reference_objects_enumerator_t)(ar_reference_object_t reference_object) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of reference objects.

 - Parameters:
   - reference_objects: The collection of reference objects.
   - reference_objects_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_reference_objects_enumerate_objects(ar_reference_objects_t reference_objects,
                                                      ar_reference_objects_enumerator_t reference_objects_enumerator) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of reference objects.

 - Parameters:
   - context: The application-defined context.
   - reference_object: The reference object.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_reference_objects_enumerator_function_t)(void *_Nullable context, ar_reference_object_t reference_object) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of reference objects.

 - Parameters:
   - reference_objects: The collection of reference objects.
   - context: The application-defined context parameter to pass to the function.
   - reference_objects_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_reference_objects_enumerate_objects_f(ar_reference_objects_t reference_objects,
                                         void *_Nullable context,
                                         ar_reference_objects_enumerator_function_t reference_objects_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Object tracking configuration

/**
 Create an object tracking configuration.

 - Note: Default values are set for configuration parameters as follows:
 - `maximum_trackable_instances`: 10
 - `maximum_instances_per_reference_object`: 1
 - `detection_rate`: 2 Hz
 - `stationary_object_tracking_rate`: 5 Hz
 - `moving_object_tracking_rate`: 5 Hz
 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_object_tracking_configuration_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_object_tracking_configuration_t ar_object_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Add reference objects to the set of objects to be tracked. Object tracking will run without any reference objects, but will detect nothing.

 - Parameters:
   - object_tracking_configuration: The configuration for object tracking.
   - reference_objects: The reference objects to add.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_tracking_configuration_add_reference_objects(ar_object_tracking_configuration_t object_tracking_configuration,
                                                                      ar_reference_objects_t reference_objects) AR_REFINED_FOR_SWIFT;

/**
 Set the total number of instances of reference objects that can be tracked at one time.

 An enterprise license is required to modify the tracking configuration, and will be otherwise be a no-op.
 The app must include the following entitlement:
  com.apple.developer.arkit.object-tracking-parameter-adjustment.allow

 - Parameters:
   - object_tracking_configuration: The object tracking configuration.
   - maximum_trackable_instances: The number to set.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_tracking_configuration_set_maximum_trackable_instances(ar_object_tracking_configuration_t object_tracking_configuration,
                                                                                int maximum_trackable_instances) AR_REFINED_FOR_SWIFT;

/**
 Get the number to be configured for the maximum number of reference object instances to track.

 - Parameter object_tracking_configuration: The object tracking configuration.

 - Returns: The configured number.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN int ar_object_tracking_configuration_get_maximum_trackable_instances(ar_object_tracking_configuration_t object_tracking_configuration)
    AR_REFINED_FOR_SWIFT;

/**
 Set the maximum number of instances of any one reference object type that can be tracked.

 An enterprise license is required to modify the tracking configuration, and will be otherwise be a no-op.
 The app must include the following entitlement:
  com.apple.developer.arkit.object-tracking-parameter-adjustment.allow

 - Parameters:
   - object_tracking_configuration: The object tracking configuration.
   - maximum_instances_per_reference_object: The number to set.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_object_tracking_configuration_set_maximum_instances_per_reference_object(ar_object_tracking_configuration_t object_tracking_configuration,
                                                                            int maximum_instances_per_reference_object) AR_REFINED_FOR_SWIFT;

/**
 Get the number to be configured for the maximum number of instances of each reference object type to track.

 - Parameter object_tracking_configuration: The object tracking configuration.

 - Returns: The configured number.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN int ar_object_tracking_configuration_get_maximum_instances_per_reference_object(
    ar_object_tracking_configuration_t object_tracking_configuration) AR_REFINED_FOR_SWIFT;

/**
 Set the frequency at which object detection runs until it starts to track an object.

 An enterprise license is required to modify the tracking configuration, and will be otherwise be a no-op.
 The app must include the following entitlement:
  com.apple.developer.arkit.object-tracking-parameter-adjustment.allow.

 - Parameters:
   - object_tracking_configuration: The object tracking configuration.
   - detection_rate: The frequency to set, in Hz. Clamped between 0 and 30 Hz.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_tracking_configuration_set_detection_rate(ar_object_tracking_configuration_t object_tracking_configuration,
                                                                   float detection_rate) AR_REFINED_FOR_SWIFT;

/**
 Get the frequency to be configured for running object detection.

 - Parameter object_tracking_configuration: The object tracking configuration.

 - Returns: The frequency, in Hz.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN float
ar_object_tracking_configuration_get_detection_rate(ar_object_tracking_configuration_t object_tracking_configuration) AR_REFINED_FOR_SWIFT;

/**
 Set the frequency at which object tracking runs for a stationary object that is detected.

 An enterprise license is required to modify the tracking configuration, and will be otherwise be a no-op.
 The app must include the following entitlement:
  com.apple.developer.arkit.object-tracking-parameter-adjustment.allow

 - Parameters:
   - object_tracking_configuration: The object tracking configuration.
   - stationary_object_tracking_rate: The frequency to set, in Hz. Clamped between 0 and 30 Hz.
*/
API_DEPRECATED("Use ar_reference_object_configuration_enable_high_frame_rate_tracking.", visionos(2.0, 27.0))
AR_EXTERN void ar_object_tracking_configuration_set_stationary_object_tracking_rate(ar_object_tracking_configuration_t object_tracking_configuration,
                                                                                    float stationary_object_tracking_rate) AR_REFINED_FOR_SWIFT;

/**
 Get the frequency to be configured for object tracking to run for a stationary object.

 - Parameter object_tracking_configuration: The object tracking configuration.

 - Returns: The frequency, in Hz.
*/
API_DEPRECATED("Use ar_reference_object_configuration_is_high_frame_rate_tracking_enabled.", visionos(2.0, 27.0))
AR_EXTERN float ar_object_tracking_configuration_get_stationary_object_tracking_rate(ar_object_tracking_configuration_t object_tracking_configuration)
    AR_REFINED_FOR_SWIFT;

/**
 Set the frequency at which object tracking runs for a moving object that is detected.

 An enterprise license is required to modify the tracking configuration, and will be otherwise be a no-op.
 The app must include the following entitlement:
  com.apple.developer.arkit.object-tracking-parameter-adjustment.allow.

 - Parameters:
   - object_tracking_configuration: The object tracking configuration.
   - moving_object_tracking_rate: The frequency to set, in Hz. Clamped between 0 and 30 Hz.
*/
API_DEPRECATED("Use ar_reference_object_configuration_enable_high_frame_rate_tracking.", visionos(2.0, 27.0))
AR_EXTERN void ar_object_tracking_configuration_set_moving_object_tracking_rate(ar_object_tracking_configuration_t object_tracking_configuration,
                                                                                float moving_object_tracking_rate) AR_REFINED_FOR_SWIFT;

/**
 Get the frequency to be configured for object tracking to run for a moving object.

 - Parameter object_tracking_configuration: The object tracking configuration.

 - Returns: The frequency, in Hz.
*/
API_DEPRECATED("Use ar_reference_object_configuration_is_high_frame_rate_tracking_enabled.", visionos(2.0, 27.0))
AR_EXTERN float ar_object_tracking_configuration_get_moving_object_tracking_rate(ar_object_tracking_configuration_t object_tracking_configuration)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Object tracking provider

/**
 Error codes specific to object tracking.
 */
API_AVAILABLE(visionos(2.0))
OS_ENUM(ar_object_tracking_error_code, ar_error_code_t,
        /// Error code indicating that a reference object failed to load.
        ar_object_tracking_error_code_reference_object_loading_failed = 1101,
)
AR_REFINED_FOR_SWIFT;

/**
 Create an object tracking provider.

 - Parameter object_tracking_configuration: The configuration for object tracking.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_object_tracking_provider_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_object_tracking_provider_t
ar_object_tracking_provider_create(ar_object_tracking_configuration_t object_tracking_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler called when there are updates to object anchors.

 - Parameters:
   - added_anchors: The collection of anchors that were added.
   - updated_anchors: The collection of anchors that were updated.
   - removed_anchors: The collection of anchors that were removed.
*/
API_AVAILABLE(visionos(2.0))
typedef void (^ar_object_tracking_update_handler_t)(ar_object_anchors_t added_anchors,
                                                    ar_object_anchors_t updated_anchors,
                                                    ar_object_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving object tracking updates.

 - Parameters:
   - object_tracking_provider: The object tracking provider.
   - object_tracking_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - object_tracking_update_handler: The handler to be called when new object tracking data arrives.

 - Note: Setting this handler will override the function set using `ar_object_tracking_provider_set_update_handler_f`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_object_tracking_provider_set_update_handler(ar_object_tracking_provider_t object_tracking_provider,
                                               dispatch_queue_t _Nullable object_tracking_updates_queue,
                                               ar_object_tracking_update_handler_t _Nullable object_tracking_update_handler) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function called when there are updates to object anchors.

 - Parameters:
   - context: The application-defined context.
   - added_anchors: The collection of anchors that were added.
   - updated_anchors: The collection of anchors that were updated.
   - removed_anchors: The collection of anchors that were removed.
*/
API_AVAILABLE(visionos(2.0))
typedef void (*ar_object_tracking_update_handler_function_t)(void *_Nullable context,
                                                             ar_object_anchors_t added_anchors,
                                                             ar_object_anchors_t updated_anchors,
                                                             ar_object_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving object tracking updates.

 - Parameters:
   - object_tracking_provider: The object tracking provider.
   - object_tracking_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - object_tracking_update_handler_function: The function to be called when new object tracking data arrives.

 - Note: Setting this handler will override the function set using `ar_object_tracking_provider_set_update_handler`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_object_tracking_provider_set_update_handler_f(
    ar_object_tracking_provider_t object_tracking_provider,
    dispatch_queue_t _Nullable object_tracking_updates_queue,
    void *_Nullable context,
    ar_object_tracking_update_handler_function_t _Nullable object_tracking_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Copy all object anchors.

 - Parameter object_tracking_provider: The object tracking provider.

 - Returns: The collection of all object anchors. This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release
 the object.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_object_anchors_t
ar_object_tracking_provider_copy_all_object_anchors(ar_object_tracking_provider_t object_tracking_provider) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the object tracking provider.

 - Returns: `true` if the object tracking provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_object_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the object tracking provider.

 - Returns: The required authorization type.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_authorization_type_t ar_object_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // object_tracking_h
#else
#import <ARKitCore/object_tracking.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/object_tracking.h>)