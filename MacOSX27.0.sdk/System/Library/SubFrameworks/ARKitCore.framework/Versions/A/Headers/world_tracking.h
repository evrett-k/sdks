//
//  world_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef world_tracking_h
#define world_tracking_h

#import <ARKitCore/anchor.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/object.h>
#import <ARKitCore/session.h>
#import <ARKitCore/transform_correction.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>
#import <uuid/uuid.h>

AR_ASSUME_NONNULL_BEGIN

/**
 An anchor that can be placed at a location in the real world.
 */
AR_OBJECT_DECL_SUBCLASS(ar_world_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos);

/**
 A collection of world anchors.
 */
AR_OBJECT_DECL(ar_world_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos);

/**
 Configuration for world tracking.
 */
AR_OBJECT_DECL(ar_world_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

/**
 A data provider for world tracking.
 */
AR_OBJECT_DECL_SUBCLASS(ar_world_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

#pragma mark - World Anchor

/**
 Returns a bool value that indicates whether the two world anchors are equal.

 - Parameters:
   - anchor: A world anchor to be compared.
   - other_anchor: The other world anchor to be compared to.

 - Returns: `YES` if the world anchors are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_world_anchor_is_equal_to_world_anchor(ar_world_anchor_t _Nullable anchor,
                                                        ar_world_anchor_t _Nullable other_anchor) AR_REFINED_FOR_SWIFT;

/**
 Create a world anchor initialized with a transform from the anchor to the origin coordinate system.

 - Parameter origin_from_anchor_transform: The origin from anchor transform.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_world_anchor_t`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_anchor_t
ar_world_anchor_create_with_origin_from_anchor_transform(simd_float4x4 origin_from_anchor_transform) AR_REFINED_FOR_SWIFT;

#pragma mark - World Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_anchor_get_identifier(ar_world_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_world_anchor_get_origin_from_anchor_transform(ar_world_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(27.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_world_anchor_get_origin_from_anchor_transform_with_correction(
    ar_world_anchor_t anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN CFTimeInterval ar_world_anchor_get_timestamp(ar_world_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 - Parameter anchor: The anchor.

 - Returns: `true` if the anchor is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_world_anchor_is_tracked(ar_world_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - World Anchors Collection

/**
 Get the count of world anchors in a collection.

 - Parameter world_anchors: The collection of world anchors.

 - Returns: The number of world anchors in the collection.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN size_t ar_world_anchors_get_count(ar_world_anchors_t world_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of world anchors.

 - Parameter world_anchor: The world anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef bool (^ar_world_anchors_enumerator_t)(ar_world_anchor_t world_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of world anchors.

 - Parameters:
   - world_anchors: The collection of world anchors.
   - world_anchors_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_anchors_enumerate_anchors(ar_world_anchors_t world_anchors,
                                                  ar_world_anchors_enumerator_t world_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of world anchors.

 - Parameters:
   - context: The application-defined context.
   - world_anchor: The world anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef bool (*ar_world_anchors_enumerator_function_t)(void *_Nullable context, ar_world_anchor_t world_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of world anchors using a function.

 - Parameters:
   - world_anchors: The collection of world anchors.
   - context: The application-defined context parameter to pass to the function.
   - world_anchors_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_anchors_enumerate_anchors_f(ar_world_anchors_t world_anchors,
                                                    void *_Nullable context,
                                                    ar_world_anchors_enumerator_function_t world_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - World Tracking Configuration

/**
 Create a world tracking configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_world_tracking_configuration_t`.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_tracking_configuration_t ar_world_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - World Tracking Provider

/**
 Create a world tracking provider.

 - Parameter world_tracking_configuration: The configuration for world tracking.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_world_tracking_provider_t`.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_tracking_provider_t
ar_world_tracking_provider_create(ar_world_tracking_configuration_t world_tracking_configuration) AR_REFINED_FOR_SWIFT;

/**
 Function called when a request to copy all known world anchors has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - all_anchors: The nullable collection of known world anchors. Passes `null` if data provider is not running and for other errors.

 - Note: The results will be accurate at the time of callback, but not necessarily at the time of the request.
 - Note: The returned anchors support ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the anchors.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (*ar_world_tracking_provider_copy_all_world_anchors_completion_function_t)(
    void *_Nullable context, ar_world_anchors_t _Nullable all_anchors) AR_REFINED_FOR_SWIFT;

/**
 Copies all known world anchors from the world tracking provider asynchronously.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - context: The application-defined context parameter to pass to the function.
   - copy_all_anchors_completion_handler_function: The function to be called with the result of the request for all known world anchors.

 - Note: This is not a blocking call. It will return all anchors that have been added successfully before the completion handler is called.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_copy_all_world_anchors_f(
    ar_world_tracking_provider_t world_tracking_provider,
    void *_Nullable context,
    ar_world_tracking_provider_copy_all_world_anchors_completion_function_t _Nullable copy_all_anchors_completion_handler_function)
    AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 A handler that the provider calls when a request to copy all known world anchors has completed (successfully or not).

 - Parameter all_anchors: The nullable collection of known world anchors. Passes `null` if data provider is not running and for other errors.

 - Note: The results will be accurate at the time of callback, but not necessarily at the time of the request.
 - Note: The returned anchors support ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the anchors.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_tracking_provider_copy_all_world_anchors_completion_handler_t)(ar_world_anchors_t _Nullable all_anchors) AR_REFINED_FOR_SWIFT;

/**
 Copies all known world anchors from the world tracking provider asynchronously.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - copy_all_anchors_completion_handler: The handler to be called with the result of the request for all known world anchors.

 - Note: This is not a blocking call. It will return all anchors that have been added successfully before the completion handler is called.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_copy_all_world_anchors(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_tracking_provider_copy_all_world_anchors_completion_handler_t copy_all_anchors_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

#ifdef __BLOCKS__
/**
 A handler that the provider calls when there are updates to world anchors. This includes updates to persisted world anchors from previous runs of the
 app.

 - Parameters:
   - added_anchors: The collection of world anchors that were added.
   - updated_anchors: The collection of world anchors that were updated.
   - removed_anchors: The collection of world anchors that were removed.

 - Note: This handler will also be called for persisted world anchors from previous runs of the app, after the world tracking provider has been
 started. World anchors persist across device restarts until they are explicitly removed. Identify the anchors you want to react to using
 `ar_anchor_get_identifier`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_tracking_anchor_update_handler_t)(ar_world_anchors_t added_anchors,
                                                          ar_world_anchors_t updated_anchors,
                                                          ar_world_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving world tracking anchor updates.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_tracking_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - world_tracking_anchor_update_handler: The handler to be called when new world anchor data arrives.

 - Note: Setting this handler will override the function set using `ar_world_tracking_provider_set_anchor_update_handler_f`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_set_anchor_update_handler(
    ar_world_tracking_provider_t world_tracking_provider,
    dispatch_queue_t _Nullable world_tracking_updates_queue,
    ar_world_tracking_anchor_update_handler_t _Nullable world_tracking_anchor_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to world anchors. This includes updates to persisted world anchors from previous runs of the app.

 - Parameters:
   - context: The application-defined context.
   - added_anchors: The collection of world anchors that were added.
   - updated_anchors: The collection of world anchors that were updated.
   - removed_anchors: The collection of world anchors that were removed.

 - Note: This function will also be called for persisted world anchors from previous runs of the app, after the world tracking provider has been
 started. World anchors persist across device restarts until they are explicitly removed. Identify the anchors you want to react to using
 `ar_anchor_get_identifier`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (*ar_world_tracking_anchor_update_handler_function_t)(void *_Nullable context,
                                                                   ar_world_anchors_t added_anchors,
                                                                   ar_world_anchors_t updated_anchors,
                                                                   ar_world_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving world tracking anchor updates.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_tracking_updates_queue: The queue on which the function will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - world_tracking_anchor_update_handler_function: The function to be called when new world anchor data arrives.

 - Note: Setting this function will override the handler set using `ar_world_tracking_provider_set_anchor_update_handler`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_set_anchor_update_handler_f(
    ar_world_tracking_provider_t world_tracking_provider,
    dispatch_queue_t _Nullable world_tracking_updates_queue,
    void *_Nullable context,
    ar_world_tracking_anchor_update_handler_function_t _Nullable world_tracking_anchor_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Error codes specific to world tracking.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
OS_ENUM(ar_world_tracking_error_code, ar_error_code_t,
    /// Error code indicating that a world anchor failed to be added.
    ar_world_tracking_error_code_add_anchor_failed = 200,
    /// Error code indicating that the maximum amount of world anchors have been added.
    ar_world_tracking_error_code_anchor_max_limit_reached = 201,
    /// Error code indicating that a world anchor failed to be removed.
    ar_world_tracking_error_code_remove_anchor_failed = 202
) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the world tracking provider.

 - Returns: `true` if the world tracking provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN bool ar_world_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 A handler that the provider calls when a request to add a world anchor has completed (successfully or not).

 - Parameters:
   - world_anchor: The world anchor to be added to the world tracking provider.
   - successful: `true` if the world anchor was successfully added to the world tracking provider, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_tracking_add_anchor_completion_handler_t)(ar_world_anchor_t world_anchor,
                                                                  bool successful,
                                                                  ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Add a world anchor to the world tracking provider. This anchor will be persisted across device restarts unless explicitly removed.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_anchor: The world anchor to add.
   - add_anchor_completion_handler: The handler to be called after the request to add the world anchor to the world tracking provider completes.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void
ar_world_tracking_provider_add_anchor(ar_world_tracking_provider_t world_tracking_provider,
                                      ar_world_anchor_t world_anchor,
                                      ar_world_tracking_add_anchor_completion_handler_t add_anchor_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when a request to add a world anchor has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - world_anchor: The world anchor to be added to the world tracking provider.
   - successful: `true` if the world anchor was successfully added to the world tracking provider, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (*ar_world_tracking_add_anchor_completion_handler_function_t)(void *_Nullable context,
                                                                           ar_world_anchor_t world_anchor,
                                                                           bool successful,
                                                                           ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Add a world anchor to the world tracking provider. This anchor will be persisted across device restarts unless explicitly removed.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_anchor: The world anchor to add.
   - context: The application-defined context parameter to pass to the function.
   - add_anchor_completion_handler_function: The function to be called after the request to add the world anchor to the world tracking provider
 completes.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_add_anchor_f(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_anchor_t world_anchor,
    void *_Nullable context,
    ar_world_tracking_add_anchor_completion_handler_function_t add_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 A handler that the provider calls when a request to remove a world anchor has completed (successfully or not).

 - Parameters:
   - world_anchor: The world anchor to be removed from the world tracking provider.
   - successful: `true` if the world anchor was successfully removed from the world tracking provider, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_tracking_remove_anchor_completion_handler_t)(ar_world_anchor_t world_anchor,
                                                                     bool successful,
                                                                     ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_anchor: The world anchor to remove.
   - remove_anchor_completion_handler: The handler to be called after the request to remove the world anchor from the world tracking provider
     completes.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void
ar_world_tracking_provider_remove_anchor(ar_world_tracking_provider_t world_tracking_provider,
                                         ar_world_anchor_t world_anchor,
                                         ar_world_tracking_remove_anchor_completion_handler_t remove_anchor_completion_handler) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider using its identifier.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - anchor_identifier: The identifier of the world anchor to remove.
   - remove_anchor_completion_handler: The handler to be called after the request to remove the world anchor from the world tracking provider
 completes.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_remove_anchor_with_identifier(
    ar_world_tracking_provider_t world_tracking_provider,
    uuid_t _Nonnull anchor_identifier,
    ar_world_tracking_remove_anchor_completion_handler_t remove_anchor_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when a request to remove a world anchor has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - world_anchor: The world anchor to be removed from the world tracking provider.
   - successful: `true` if the world anchor was successfully removed from the world tracking provider, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (*ar_world_tracking_remove_anchor_completion_handler_function_t)(void *_Nullable context,
                                                                              ar_world_anchor_t world_anchor,
                                                                              bool successful,
                                                                              ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_anchor: The world anchor to remove.
   - context: The application-defined context parameter to pass to the function.
   - remove_anchor_completion_handler_function: The function to be called after the request to remove the world anchor from the world tracking
 provider completes.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_remove_anchor_f(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_anchor_t world_anchor,
    void *_Nullable context,
    ar_world_tracking_remove_anchor_completion_handler_function_t remove_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider using its identifier.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - anchor_identifier: The identifier of the world anchor to remove.
   - context: The application-defined context parameter to pass to the function.
   - remove_anchor_completion_handler_function: The function to be called after the request to remove the world anchor from the world tracking
 provider completes.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_remove_anchor_with_identifier_f(
    ar_world_tracking_provider_t world_tracking_provider,
    uuid_t _Nonnull anchor_identifier,
    void *_Nullable context,
    ar_world_tracking_remove_anchor_completion_handler_function_t remove_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Function called when a request to remove all known world anchors has completed (successfully or not).

 - Parameters:
   - successful: `true` if all anchors were successfully removed from the world tracking provider, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_tracking_remove_all_anchors_completion_handler_t)(bool successful, ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Removes all known world anchors from the world tracking provider asynchronously.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - remove_all_anchors_completion_handler: The handler to be called after the request to remove all known world anchors from
     the world tracking provider completes.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_remove_all_anchors(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_tracking_remove_all_anchors_completion_handler_t remove_all_anchors_completion_handler) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function called when a request to remove all known world anchors has completed (successfully or not).

 - Parameters:
   - context: The application-defined context.
   - successful: `true` if all anchors were successfully removed from the world tracking provider, `false` otherwise.
   - error: The error that occurred, if any.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_tracking_remove_all_anchors_completion_handler_function_t)(void *_Nullable context,
                                                                                   bool successful,
                                                                                   ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Removes all known world anchors from the world tracking provider asynchronously.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - context: The application-defined context parameter to pass to the function.
   - remove_all_anchors_completion_handler_function: The handler to be called after the request to remove all known world anchors from
     the world tracking provider completes.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_remove_all_anchors_f(
    ar_world_tracking_provider_t world_tracking_provider,
    void *_Nullable context,
    ar_world_tracking_remove_all_anchors_completion_handler_function_t remove_all_anchors_completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Initialize a world anchor that should be shared with nearby participants.

 :
 -  Nearby participants refer to participants that are nearby to the local participant in a SharePlay session.
 - World anchors that are marked for sharing do not get persisted across reboots and their lifetime is limited to that of the SharePlay session.

 - Parameter origin_from_anchor_transform: The transform from the world anchor to the origin coordinate system.

 - Returns: An instance of `ar_world_anchor_t` which is marked to be shared with nearby participants.
 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_anchor_t
ar_world_anchor_shared_with_nearby_participants_create(simd_float4x4 origin_from_anchor_transform) AR_REFINED_FOR_SWIFT;

/**
 Check if a world anchor is marked to be shared with nearby participants.

 - Parameter world_anchor: The world anchor.

 - Returns: `true` if the world anchor is marked to be shared with nearby participants, `false` otherwise.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_world_anchor_is_shared_with_nearby_participants(ar_world_anchor_t world_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumeration indicating the availability of world anchor sharing.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
OS_ENUM(ar_world_anchor_sharing_availability, intptr_t,
    // World anchors can be shared with nearby participants.
    // Indicates that the device is in a SharePlay session with nearby participants.
    ar_world_anchor_sharing_availability_available,
    // World anchors cannot be shared with nearby participants.
    // This indicates that either there’s no SharePlay session or the session has ended.
    ar_world_anchor_sharing_availability_unavailable
) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 A handler that the provider calls when there is a change in world anchor sharing availability.

 - Parameter sharing_availability: World anchor sharing availability.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (^ar_world_anchor_sharing_availability_update_handler_t)(ar_world_anchor_sharing_availability_t sharing_availability)
    AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving world anchor sharing availability updates.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_tracking_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - world_anchor_sharing_availability_update_handler: The handler to be called when there is a change in world anchor sharing availability.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_set_world_anchor_sharing_availability_update_handler(
    ar_world_tracking_provider_t world_tracking_provider,
    dispatch_queue_t _Nullable world_tracking_updates_queue,
    ar_world_anchor_sharing_availability_update_handler_t _Nullable world_anchor_sharing_availability_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function pointer called when there is a change in world anchor sharing availability.

 - Parameters:
   - context: The application-defined context.
   - sharing_availability: World anchor sharing availability.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef void (*ar_world_anchor_sharing_availability_update_handler_function_t)(
    void *_Nullable context, ar_world_anchor_sharing_availability_t sharing_availability) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving world anchor sharing availability updates

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - world_tracking_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - world_anchor_sharing_availability_update_handler_function: The function to be called when there is a change in world anchor sharing availability.
*/
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_world_tracking_provider_set_world_anchor_sharing_availability_update_handler_f(
    ar_world_tracking_provider_t world_tracking_provider,
    dispatch_queue_t _Nullable world_tracking_updates_queue,
    void *_Nullable context,
    ar_world_anchor_sharing_availability_update_handler_function_t _Nullable world_anchor_sharing_availability_update_handler_function)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Device Anchor

/**
 An anchor representing the device's position and orientation.
 */
AR_OBJECT_DECL_SUBCLASS(ar_device_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

/**
 Return status enum values for getting the device anchor at a specified timestamp from the world tracking provider.
 */
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
OS_ENUM(ar_device_anchor_query_status, intptr_t,
    // The device anchor at the specified timestamp was successfully obtained.
    ar_device_anchor_query_status_success = 0,
    // The device anchor at the specified timestamp failed to be obtained.
    ar_device_anchor_query_status_failure)
AR_REFINED_FOR_SWIFT;

/**
 Tracking states of a device anchor.
 */
API_AVAILABLE(visionos(2.0), macos(26.0), macCatalyst(26.0))
OS_ENUM(ar_device_anchor_tracking_state, intptr_t,
    // The anchor is not tracked.
    ar_device_anchor_tracking_state_untracked = 0,
    // Only orientation is currently tracked.
    ar_device_anchor_tracking_state_orientation_tracked,
    // Both position and orientation are currently tracked.
    ar_device_anchor_tracking_state_tracked)
AR_REFINED_FOR_SWIFT;

/**
 Create a device anchor.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_device_anchor_t`.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_device_anchor_t ar_device_anchor_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - Device Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(2.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN void ar_device_anchor_get_identifier(ar_device_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(2.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN simd_float4x4 ar_device_anchor_get_origin_from_anchor_transform(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameters:
   - anchor: The anchor.
   - transform_correction: The transform correction that should be applied.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(27.0), macos(27.0), macCatalyst(27.0))
AR_EXTERN simd_float4x4 ar_device_anchor_get_origin_from_anchor_transform_with_correction(
    ar_device_anchor_t anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(2.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN CFTimeInterval ar_device_anchor_get_timestamp(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 - Parameter anchor: The anchor.

 - Returns: `true` if the anchor is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN bool ar_device_anchor_is_tracked(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the tracking state of the device anchor.

 - Parameter anchor: The anchor.

 - Returns: Tracking state of this anchor.
*/
API_AVAILABLE(visionos(2.0), macos(26.0), macCatalyst(26.0))

AR_EXTERN ar_device_anchor_tracking_state_t ar_device_anchor_get_tracking_state(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - World Tracking Prediction

/**
 Query a device anchor at the given timestamp.

 The origin is a right-handed coordinate system and is defined such that X points to the right, Y points up, and Z points backward.

 Example usage:
 ```
 auto timing_info = cp_drawable_get_frame_timing(drawable);
 auto time = cp_time_to_cf_time_interval(cp_frame_timing_get_presentation_time(timing_info));
 const ar_device_anchor_query_status_t status = ar_world_tracking_provider_query_device_anchor_at_timestamp(_provider, time, &device_anchor);
 ```

 - Note: This API is not thread safe.

 - Parameters:
   - world_tracking_provider: The world tracking provider.
   - timestamp: The timestamp to get the device anchor at. The timestamp should be provided as mach absolute time in seconds.
   - device_anchor: The output device anchor.

 - Returns: An `ar_device_anchor_query_status_t` value indicating whether the device anchor was successfully retrieved at the given timestamp or not.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN ar_device_anchor_query_status_t
ar_world_tracking_provider_query_device_anchor_at_timestamp(ar_world_tracking_provider_t world_tracking_provider,
                                                            CFTimeInterval timestamp,
                                                            ar_device_anchor_t device_anchor) AR_REFINED_FOR_SWIFT AR_MT_UNSAFE;

/**
 Get the authorization type required by the world tracking provider.

 - Returns: The required authorization type.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN ar_authorization_type_t ar_world_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // world_tracking_h
