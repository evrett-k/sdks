//
//  accessory_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef accessory_tracking_h
#define accessory_tracking_h

#import <ARKitCore/anchor.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/error.h>
#import <ARKitCore/object.h>
#import <ARKitCore/session.h>
#import <ARKitCore/strings_collection.h>
#import <ARKitCore/transform_correction.h>

#import <simd/types.h>

#import <CoreFoundation/CFBundle.h>
#import <CoreFoundation/CFURL.h>

#ifdef __OBJC__


@protocol GCDevice;

#endif // __OBJC__

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 The chirality of an accessory.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_accessory_chirality, intptr_t,
    /// Unspecified (non-handed accessory, not associated with a hand).
    ar_accessory_chirality_unspecified = 0,
    /// Left-handed accessory, or non-handed accessory held in left hand.
    ar_accessory_chirality_left,
    /// Right-handed accessory, or non-handed accessory held in right hand.
    ar_accessory_chirality_right)
AR_REFINED_FOR_SWIFT;

/**
 Error codes specific to accessory tracking.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_accessory_tracking_error_code, ar_error_code_t,
    /// Error code indicating that an accessory failed to load.
    ar_accessory_tracking_error_code_accessory_loading_failed = 1200,
    /// Error code indicating that updating accessories failed.
    ar_accessory_tracking_error_code_update_accessories_failed API_AVAILABLE(visionos(27.0)) = 1201
) AR_REFINED_FOR_SWIFT;

/**
 Tracking status for accessory anchors.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_accessory_anchor_tracking_state, intptr_t,
    // The anchor is not tracked.
    ar_accessory_anchor_tracking_state_untracked = 0,
    // Only orientation is currently tracked.
    ar_accessory_anchor_tracking_state_orientation_tracked,
    // Both position and orientation are currently tracked.
    ar_accessory_anchor_tracking_state_position_orientation_tracked,
    // Both position and orientation are currently tracked, but with low accuracy.
    ar_accessory_anchor_tracking_state_position_orientation_tracked_low_accuracy,
) AR_REFINED_FOR_SWIFT;

/**
 The type of input that was used to initialize an `ar_accessory_t`.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_accessory_source_type,
        intptr_t,
        /// Accessory was initialized from a `GCDevice`.
        ar_accessory_source_type_device = 1, )
AR_REFINED_FOR_SWIFT;

/**
 An accessory that can be tracked in the physical environment, such as a game controller or stylus.
 */
AR_OBJECT_DECL(ar_accessory)
AR_REFINED_FOR_SWIFT
AR_SWIFT_SENDABLE
API_AVAILABLE(visionos(26.0));

/**
 A collection of accessories.
 */
AR_OBJECT_DECL(ar_accessories)
AR_REFINED_FOR_SWIFT
AR_SWIFT_SENDABLE
API_AVAILABLE(visionos(26.0));

/**
 An anchor that represents an accessory.
 */
AR_OBJECT_DECL_SUBCLASS(ar_accessory_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 A collection of accessory anchors.
 */
AR_OBJECT_DECL(ar_accessory_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 Configuration for accessory tracking.
 */
AR_OBJECT_DECL(ar_accessory_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 A data provider for accessory tracking.
 */
AR_OBJECT_DECL_SUBCLASS(ar_accessory_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

#pragma mark - Accessory

/**
 Pre-defined accessory location name for spatial gamepad grip surface.
 */
API_AVAILABLE(visionos(26.0)) AR_EXTERN const char *const ar_accessory_location_name_grip_surface AR_REFINED_FOR_SWIFT;

/**
 Pre-defined accessory location name for spatial gamepad grip.
 */
API_AVAILABLE(visionos(26.0)) AR_EXTERN const char *const ar_accessory_location_name_grip AR_REFINED_FOR_SWIFT;

/**
 Pre-defined accessory location name for spatial gamepad and stylus aim point.
 */
API_AVAILABLE(visionos(26.0)) AR_EXTERN const char *const ar_accessory_location_name_aim AR_REFINED_FOR_SWIFT;

/**
 Indicates whether two accessories are equal.

 - Parameters:
   - accessory: An accessory to be compared.
   - other_accessory: The other accessory to be compared to.

 - Returns: `true` if the accessories are equal, otherwise `false`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_accessory_is_equal_to_accessory(ar_accessory_t _Nullable accessory, ar_accessory_t _Nullable other_accessory) AR_REFINED_FOR_SWIFT;

/**
 Get identifier for the accessory.

 - Parameters:
   - accessory: The accessory.
   - out_identifier: Object to fill with UUID.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN void ar_accessory_get_identifier(ar_accessory_t accessory, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get inherent chirality for the accessory (what hand it is designed to be held in).

 - Parameter accessory: The accessory.

 - Returns: The chirality.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN ar_accessory_chirality_t ar_accessory_get_inherent_chirality(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

/**
 Get an accessory's name.

 - Parameter accessory: The accessory.

 - Note: The returned value will have the same lifetime as the input `ar_accessory_t`.

 - Returns: The name of the accessory, or `NULL` if no name is set.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN const char *ar_accessory_get_name(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

/**
 Gets the names of locations with pre-defined coordinate systems available for this accessory.

 - Parameter accessory: The accessory.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An `ar_strings_t` with the location names.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_strings_t ar_accessory_copy_location_names(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

/**
 Get path to a USDZ file for the accessory, if it has one.

 - Parameter accessory: The accessory.

 - Note: The returned value will have the same lifetime as the `ar_accessory_t`.

 - Returns: The path to the USDZ file.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN CF_RETURNS_NOT_RETAINED CFURLRef _Nullable ar_accessory_get_usdz_file_path(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

#pragma mark - Accessory (Loaders)

#ifdef __OBJC__

#ifdef __BLOCKS__

/**
 Handler triggered when a request to load an accessory from a `GCDevice` has completed.

 - Parameters:
   - device: The `GCDevice` for the accessory that was being loaded.
   - successful: `true` if loading succeeded, `false` otherwise.
   - error: The error that occurred, if any.
   - accessory: An instance of `ar_accessory_t` (NULL if loading failed). The accessory supports ARC.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_accessory_device_load_completion_handler_t)(id<GCDevice> device,
                                                              bool successful,
                                                              ar_error_t _Nullable error,
                                                              ar_accessory_t _Nullable accessory) AR_REFINED_FOR_SWIFT;

/**
 Load an accessory from a `GCDevice`.

 - Parameters:
   - device: The `GCDevice` for which to load the accessory.
   - completion_handler: A handler triggered after the request to load an accessory completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessory_load_from_device(id<GCDevice> device,
                                             ar_accessory_device_load_completion_handler_t completion_handler) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function triggered when a request to load an accessory from a `GCDevice` has completed.

 - Parameters:
   - context: The application-defined context.
   - device: The `GCDevice` for the accessory that was being loaded.
   - successful: `true` if loading succeeded, `false` otherwise.
   - error: The error that occurred, if any.
   - accessory: An instance of `ar_accessory_t` (`NULL` if loading failed). The accessory supports ARC.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_accessory_device_load_completion_handler_function_t)(void *_Nullable context,
                                                                       id<GCDevice> device,
                                                                       bool successful,
                                                                       ar_error_t _Nullable error,
                                                                       ar_accessory_t _Nullable accessory) AR_REFINED_FOR_SWIFT;

/**
 Load an accessory from a `GCDevice`.

 - Parameters:
   - device: The `GCDevice` for which to load the accessory.
   - context: The application-defined context.
   - completion_handler_function: Function triggered after the request to load an accessory completes.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void
ar_accessory_load_from_device_f(id<GCDevice> device,
                                void *_Nullable context,
                                ar_accessory_device_load_completion_handler_function_t completion_handler_function) AR_REFINED_FOR_SWIFT;

#endif // __OBJC__

#pragma mark - Accessory (Source)

/**
 Gets type of source that was used to load an accessory.

 - Parameter accessory: The accessory.

 - Returns: The source type.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_accessory_source_type_t ar_accessory_get_source_type(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

#ifdef __OBJC__

/**
 Gets the `GCDevice` that was used to initialize the accessory.

 - Parameter accessory: The accessory.

 - Returns: The `GCDevice`, or `NULL` if not used to initialize the accessory.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN id<GCDevice> _Nullable ar_accessory_get_source_device(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

#endif // __OBJC__

#pragma mark - Accessories

/**
 Create an empty collection of accessories.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_accessories_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_accessories_t AR_SWIFT_SENDABLE ar_accessories_create(void) AR_REFINED_FOR_SWIFT;

/**
 Add an accessory to a collection.

 The accessory must be unique. A duplicate of any existing object in the collection will not be added.

 - Parameters:
   - accessories: The collection of accessories to alter.
   - accessory_to_add: The accessory to add.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessories_add_accessory(ar_accessories_t accessories, ar_accessory_t accessory_to_add) AR_REFINED_FOR_SWIFT;

/**
 Add accessories to a collection.

 The accessories must be unique. Duplicates of any existing object in the collection will not be added.

 - Parameters:
   - accessories: The collection of accessories to alter.
   - accessories_to_add: The accessories to add.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessories_add_accessories(ar_accessories_t accessories, ar_accessories_t accessories_to_add) AR_REFINED_FOR_SWIFT;

/**
 Remove an accessory from a collection.

 No action is taken if the accessory is not found.

 - Parameters:
   - accessories: The collection of accessories to alter.
   - accessory_to_remove: The accessory to remove.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessories_remove_accessory(ar_accessories_t accessories, ar_accessory_t accessory_to_remove) AR_REFINED_FOR_SWIFT;

/**
 Remove accessories from a collection.

 - Parameters:
   - accessories: The collection of accessories to alter.
   - accessories_to_remove: The accessories to remove.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessories_remove_accessories(ar_accessories_t accessories, ar_accessories_t accessories_to_remove) AR_REFINED_FOR_SWIFT;

/**
 Get the count of accessories in the collection.

 - Parameter accessories: The collection of accessories.

 - Returns: The number of accessories in the collection.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN size_t ar_accessories_get_count(ar_accessories_t accessories) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating a collection of accessories.

 - Parameter accessory: The accessory.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (^ar_accessories_enumerator_t)(ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of accessories.

 - Parameters:
   - accessories: The collection of accessories.
   - accessories_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessories_enumerate_accessories(ar_accessories_t accessories,
                                                    ar_accessories_enumerator_t accessories_enumerator) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of accessories.

 - Parameters:
   - context: The application-defined context.
   - accessory: The accessory.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (*ar_accessories_enumerator_function_t)(void *_Nullable context, ar_accessory_t accessory) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of reference objects.

 - Parameters:
   - accessories: The collection of accessories.
   - context: The application-defined context parameter to pass to the function.
   - accessories_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessories_enumerate_accessories_f(ar_accessories_t accessories,
                                                      void *_Nullable context,
                                                      ar_accessories_enumerator_function_t accessories_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Accessory Anchor

/**
 Create an uninitialized accessory anchor.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_accessory_anchor_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_accessory_anchor_t ar_accessory_anchor_create(void) AR_REFINED_FOR_SWIFT;

/**
 Returns a Boolean value that indicates whether the two accessory anchors are equal.

 - Parameters:
   - anchor: The accessory anchor to be compared.
   - other_anchor: The other accessory anchor to be compared to.

 - Returns: `true` if the accessory anchors are equal, otherwise `false`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_accessory_anchor_is_equal_to_accessory_anchor(ar_accessory_anchor_t _Nullable anchor,
                                                                ar_accessory_anchor_t _Nullable other_anchor) AR_REFINED_FOR_SWIFT;

/**
 Returns the accessory that is being tracked by the anchor.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: The accessory.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN ar_accessory_t AR_SWIFT_SENDABLE ar_accessory_anchor_get_accessory(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the tracking state of the accessory anchor.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: Tracking state for this anchor.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_accessory_anchor_tracking_state_t ar_accessory_anchor_get_tracking_state(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Returns a Boolean value that indicates whether the accessory is held.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: `true` if the accessory is currently held, otherwise `false`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_accessory_anchor_is_held(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the held state of this accessory anchor.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: Which hand the accessory is being held in, or unknown.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_accessory_chirality_t ar_accessory_anchor_get_held_chirality(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the estimated velocity of the accessory in the local coordinate system.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: The velocity of the accessory in `m/s`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN simd_float3 ar_accessory_anchor_get_velocity(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the estimated angular velocity of the accessory in the local coordinate system.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: Angular velocity of the accessory in `rad/s`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN simd_float3 ar_accessory_anchor_get_angular_velocity(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark Accessory Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - accessory_anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessory_anchor_get_identifier(ar_accessory_anchor_t accessory_anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter accessory_anchor: The anchor.

 - Note: This function will return a rendering-corrected transform and is equal to calling
 `ar_accessory_anchor_get_origin_from_anchor_transform_with_correction` with `ar_transform_correction_rendered`.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN simd_float4x4 ar_accessory_anchor_get_origin_from_anchor_transform(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - accessory_anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN simd_float4x4 ar_accessory_anchor_get_origin_from_anchor_transform_with_correction(
    ar_accessory_anchor_t accessory_anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the coordinate system of a location on the accessory.

 - Parameters:
   - accessory_anchor: The anchor.
   - location_name: The name of a location on the accessory.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN simd_float4x4 ar_accessory_anchor_get_anchor_from_location_transform_with_correction(
    ar_accessory_anchor_t accessory_anchor, const char *location_name, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to the accessory anchor.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: The timestamp associated with the accessory anchor.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN CFTimeInterval ar_accessory_anchor_get_timestamp(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an accessory anchor is tracked.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: `true` if the anchor is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_accessory_anchor_is_tracked(ar_accessory_anchor_t accessory_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Accessory Anchors Collection

/**
 Get the count of accessory anchors in the collection.

 - Parameter accessory_anchors: The collection of accessory anchors.

 - Returns: The number of accessory anchors in the collection.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN size_t ar_accessory_anchors_get_count(ar_accessory_anchors_t accessory_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating a collection of accessory anchors.

 - Parameter accessory_anchor: The accessory anchor.

 - Returns: `true` to continue enumerating to the next accessory anchor in the collection, `false` to stop enumerating.
 - Note: Enumeration is not thread-safe. The enumerator must not retain or release objects.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (^ar_accessory_anchors_enumerator_t)(ar_accessory_anchor_t accessory_anchor) AR_MT_UNSAFE AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of accessory anchors.

 - Parameters:
   - accessory_anchors: A collection of accessory anchors.
   - accessory_anchors_enumerator: Enumeration handler.

 - Note: Enumeration is not thread-safe. The enumerator must not retain or release objects.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN void
ar_accessory_anchors_enumerate_anchors(ar_accessory_anchors_t accessory_anchors,
                                       ar_accessory_anchors_enumerator_t accessory_anchors_enumerator) AR_MT_UNSAFE AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of accessory anchors.

 - Parameters:
   - context: The application-defined context.
   - accessory_anchor: The accessory anchor.

 - Returns: `true` to continue enumerating to the next accessory anchor in the collection, `false` to stop enumerating.
 - Note: Enumeration is not thread-safe. The enumerator must not retain or release objects.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (*ar_accessory_anchors_enumerator_function_t)(void *_Nullable context,
                                                           ar_accessory_anchor_t accessory_anchor) AR_MT_UNSAFE AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of acessory anchors.

 - Parameters:
   - accessory_anchors: A collection of accessory anchors.
   - context: The application-defined context parameter to pass to the function.
   - accessory_anchors_enumerator_function: Enumeration function.

 - Note: Enumeration is not thread-safe. The enumerator must not retain or release objects.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN void ar_accessory_anchors_enumerate_anchors_f(ar_accessory_anchors_t accessory_anchors,
                                                        void *_Nullable context,
                                                        ar_accessory_anchors_enumerator_function_t accessory_anchors_enumerator_function)
    AR_MT_UNSAFE AR_REFINED_FOR_SWIFT;

#pragma mark - Accessory Tracking Configuration

/**
 Create an accessory tracking configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_accessory_tracking_configuration_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN
AR_OBJECT_RETURNS_RETAINED
ar_accessory_tracking_configuration_t ar_accessory_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Set accessories to track for the configuration.

 - Parameters:
   - configuration: The configuration to set accessories for.
   - accessories: The accessories to add to the configuration.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN
void ar_accessory_tracking_configuration_set_accessories(ar_accessory_tracking_configuration_t configuration,
                                                         ar_accessories_t accessories) AR_REFINED_FOR_SWIFT;

#pragma mark - Accessory Tracking Provider

/**
 Create an accessory tracking provider.

 - Parameter accessory_tracking_configuration: accessory tracking configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_accessory_tracking_provider_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_accessory_tracking_provider_t
ar_accessory_tracking_provider_create(ar_accessory_tracking_configuration_t accessory_tracking_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler called when there are updates to accessory anchors.

 - Parameters:
   - added_anchors: The collection of anchors that were added.
   - updated_anchors: The collection of anchors that were updated.
   - removed_anchors: The collection of anchors that were removed.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_accessory_tracking_update_handler_t)(ar_accessory_anchors_t added_anchors,
                                                       ar_accessory_anchors_t updated_anchors,
                                                       ar_accessory_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving accessory anchor updates.
 - Note: Routine anchor updates will be disabled unless a handler is provided to this method. This is done to save CPU time for applications which do
 not need an anchor stream.
 - Note: Setting this handler will override the function set using `ar_accessory_tracking_provider_set_update_handler_f`.
 - Parameters:
   - accessory_tracking_provider: The accessory tracking provider.
   - accessory_tracking_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - accessory_tracking_update_handler: The handler to be called when new accessory tracking data arrives.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessory_tracking_provider_set_update_handler(ar_accessory_tracking_provider_t accessory_tracking_provider,
                                                                 dispatch_queue_t _Nullable accessory_tracking_updates_queue,
                                                                 ar_accessory_tracking_update_handler_t _Nullable accessory_tracking_update_handler)
    AR_REFINED_FOR_SWIFT;

/**
 Handler triggered when a request to update accessories has completed.

 - Parameters:
   - success: `true` if the update succeeded, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(27.0))
typedef void (^ar_accessory_tracking_update_accessories_completion_handler_t)(bool success, ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Update the accessories being tracked by a provider.

 Updates are atomic: if any accessory fails to be added, the entire request fails and
 the provider continues tracking the original set of accessories.

 Update requests are processed sequentially. If multiple requests are made while an
 update is in progress, only the most recent request is retained and will be processed
 next; intermediate requests are superseded and their completion handlers are called
 with an error.

 The completion handler will be called with an error when one or more accessories
 cannot be added or the request is superseded by a more recent request.

 - Parameters:
   - accessory_tracking_provider: The accessory tracking provider.
   - accessories: The new set of accessories to track.
   - completion_handler: Handler triggered after the update completes.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void ar_accessory_tracking_provider_update_accessories(ar_accessory_tracking_provider_t accessory_tracking_provider,
                                                                 ar_accessories_t accessories,
                                                                 ar_accessory_tracking_update_accessories_completion_handler_t completion_handler)
    AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function called when there are updates to accessory anchors.

 - Parameters:
   - context: The application-defined context.
   - added_anchors: The collection of anchors that were added.
   - updated_anchors: The collection of anchors that were updated.
   - removed_anchors: The collection of anchors that were removed.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_accessory_tracking_update_handler_function_t)(void *_Nullable context,
                                                                ar_accessory_anchors_t added_anchors,
                                                                ar_accessory_anchors_t updated_anchors,
                                                                ar_accessory_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving accessory tracking updates.

 - Parameters:
   - accessory_tracking_provider: The accessory tracking provider.
   - accessory_tracking_updates_queue: The queue on which the function will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - accessory_tracking_update_handler_function: The function to be called when new accessory tracking data arrives.

 - Note: Setting this function will override the handler set using `ar_accessory_tracking_provider_set_update_handler`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_accessory_tracking_provider_set_update_handler_f(
    ar_accessory_tracking_provider_t accessory_tracking_provider,
    dispatch_queue_t _Nullable accessory_tracking_updates_queue,
    void *_Nullable context,
    ar_accessory_tracking_update_handler_function_t _Nullable accessory_tracking_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Function triggered when a request to update accessories has completed.

 - Parameters:
   - context: The application-defined context.
   - success: `true` if the update succeeded, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(27.0))
typedef void (*ar_accessory_tracking_update_accessories_completion_handler_function_t)(void *_Nullable context,
                                                                                       bool success,
                                                                                       ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Update the accessories being tracked by a provider.

 Updates are atomic: if any accessory fails to be added, the entire request fails and
 the provider continues tracking the original set of accessories.

 Update requests are processed sequentially. If multiple requests are made while an
 update is in progress, only the most recent request is retained and will be processed
 next; intermediate requests are superseded and their completion handlers are called
 with an error.

 The completion handler function will be called with an error when one or more accessories
 cannot be added or the request is superseded by a more recent request.

 - Parameters:
   - accessory_tracking_provider: The accessory tracking provider.
   - accessories: The new set of accessories to track.
   - context: The application-defined context parameter to pass to the function.
   - completion_handler_function: Function triggered after the update completes.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN void ar_accessory_tracking_provider_update_accessories_f(
    ar_accessory_tracking_provider_t accessory_tracking_provider,
    ar_accessories_t accessories,
    void *_Nullable context,
    ar_accessory_tracking_update_accessories_completion_handler_function_t completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Determines whether this device supports the accessory tracking provider.

 - Returns: Returns `true` if the accessory tracking provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_accessory_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the accessory tracking provider.

 - Returns: The authorization type.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_authorization_type_t ar_accessory_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

#pragma mark - Accessory Tracking Prediction

/**
 Retrieves the latest anchors updated with the most recent inertial data.

 These anchors provide higher frequency, lower latency and slightly lower accuracy than the anchors from the update handler.
 Use them directly or in combination with `ar_accessory_tracking_provider_predict_anchor_at_timestamp`.

 - Parameter accessory_tracking_provider: An accessory tracking provider.

 - Note: This collection is managed by the provider and is not safe for the caller to release. It has the same lifetime as this
 `accessory_tracking_provider`. This collection is not thread safe.

 - Returns: An `ar_accessory_anchors_t` collection of latest anchors.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN ar_accessory_anchors_t ar_accessory_tracking_provider_get_latest_anchors(ar_accessory_tracking_provider_t accessory_tracking_provider)
    AR_REFINED_FOR_SWIFT AR_MT_UNSAFE;

/**
 Predict an accessory anchor to a target timestamp.

 Example usage:
 ```
 auto timing_info = cp_drawable_get_frame_timing(drawable);
 auto time = cp_time_to_cf_time_interval(cp_frame_timing_get_trackable_anchor_time(timing_info));
 const BOOL success = ar_accessory_tracking_provider_predict_anchor_at_timestamp(_provider, anchor_id, timestamp, accessory_anchor);
 ```

 - Parameters:
   - accessory_tracking_provider: An accessory tracking provider.
   - anchor: An anchor to predict. Use `ar_accessory_tracking_provider_get_latest_anchors` to get latest anchors. Use tracked
     anchors to predict.
   - timestamp: The timestamp to get the accessory anchor at. The timestamp should be provided as mach absolute time in seconds.
   - predicted_anchor: The output predicted accessory anchor.

 - Note: A large time offset from latest anchor timestamp could degrade accuracy. For accuracy sensitive use cases like drawing, use a small offset or
 the latest anchor. Use a prediction timestamp smaller than the latest anchor timestamp for interpolation.

 - Returns: Whether accessory anchor prediction was successful.
*/
API_AVAILABLE(visionos(26.0))

AR_EXTERN bool ar_accessory_tracking_provider_predict_anchor_at_timestamp(ar_accessory_tracking_provider_t accessory_tracking_provider,
                                                                          ar_accessory_anchor_t anchor,
                                                                          CFTimeInterval timestamp,
                                                                          ar_accessory_anchor_t predicted_anchor) AR_REFINED_FOR_SWIFT AR_MT_UNSAFE;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif /* accessory_tracking_h */
