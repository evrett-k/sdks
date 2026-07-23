//
//  shared_coordinate_space.h
//  ARKit
//
//  An enterprise license is required to use shared coordinate space, and will be otherwise be a no-op.
//  The app must include the following entitlement:
//    com.apple.developer.arkit.shared-coordinate-space.allow
//
//  Created by Jae Lee on 12/11/24.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef shared_coordinate_space_h
#define shared_coordinate_space_h

#import <ARKitCore/data_provider.h>
#import <ARKitCore/identifiers.h>
#import <ARKitCore/object.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 Data for sharing coordinate space information between participants.
 */
AR_OBJECT_DECL(ar_coordinate_space_data)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 Configuration for the shared coordinate space provider.
 */
AR_OBJECT_DECL(ar_shared_coordinate_space_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 A data provider for shared coordinate spaces across participants.
 */
AR_OBJECT_DECL_SUBCLASS(ar_shared_coordinate_space_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

#ifdef __BLOCKS__
/**
 A handler that the provider calls when there is an update to the shared coordinate space connected participants.

 - Parameter connected_participant_identifiers: List of all participant identifiers that have established a shared coordinate space.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_shared_coordinate_space_connected_participants_update_handler_t)(ar_identifiers_t connected_participant_identifiers)
    AR_REFINED_FOR_SWIFT;

/**
 A handler that the provider calls when there is an update to the shared coordinate space sharing status.

 - Parameter is_sharing_enabled: Whether coordinate space sharing is enabled.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_shared_coordinate_space_sharing_status_update_handler_t)(bool is_sharing_enabled) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function called when there are updates to the shared coordinate space participant status.

 - Parameters:
   - context: The application-defined context.
   - connected_participant_identifiers: List of participant identifiers that have established a shared coordinate space.
*/
API_AVAILABLE(visionos(26.0))
typedef void (*ar_shared_coordinate_space_connected_participants_update_handler_function_t)(
    void *_Nullable context, ar_identifiers_t connected_participant_identifiers) AR_REFINED_FOR_SWIFT;

/**
 Function called when there is an update to the shared coordinate space sharing status.

 - Parameters:
   - context: The application-defined context.
   - is_sharing_enabled: Whether coordinate space sharing is enabled.
*/
API_AVAILABLE(visionos(26.0))
typedef void (^ar_shared_coordinate_space_sharing_status_update_handler_function_t)(void *_Nullable context,
                                                                                    bool is_sharing_enabled) AR_REFINED_FOR_SWIFT;

#pragma mark - Shared coordinate space data

/**
 Copy the list of participant identifiers of the intended recipient for this data. Data should be broadcast if the list is empty.

 - Parameter shared_coordinate_space_data: Shared coordinate space data.

 - Returns: List the participant identifiers to which the data should be sent. Data should be broadcast to all participants if the list is empty.
 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
*/
API_DEPRECATED_WITH_REPLACEMENT("ar_coordinate_space_data_copy_recipient_identifiers", visionos(26.0, 27.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_identifiers_t
ar_coordinate_space_data_copy_recipient_identifers(ar_coordinate_space_data_t shared_coordinate_space_data) AR_REFINED_FOR_SWIFT;

/**
 Copy the list of participant identifiers of the intended recipient for this data. Data should be broadcast if the list is empty.

 - Parameter shared_coordinate_space_data: Shared coordinate space data.

 - Returns: List the participant identifiers to which the data should be sent. Data should be broadcast to all participants if the list is empty.
 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_identifiers_t
ar_coordinate_space_data_copy_recipient_identifiers(ar_coordinate_space_data_t shared_coordinate_space_data) AR_REFINED_FOR_SWIFT;

/**
 Create and initialize an `ar_coordinate_space_data_t` object from a `CFDataRef`.

 - Parameter cfData: The `CFDataRef` object to set for the `ar_coordinate_space_data_t`.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_coordinate_space_data_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED _Nullable ar_coordinate_space_data_t
ar_coordinate_space_data_create_from_cfdata(CFDataRef cfData) AR_REFINED_FOR_SWIFT;

/**
 Copy out a `CFDataRef` that archives the coordinate space data.

 - Parameter data: Coordinate space data.

 - Returns: The `CFDataRef`. The caller is responsible for calling `CFRelease` on the returned pointer.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN CF_RETURNS_RETAINED CFDataRef ar_coordinate_space_data_copy_cfdata(ar_coordinate_space_data_t data) AR_REFINED_FOR_SWIFT;

#pragma mark - Shared Coordinate Space Configuration

/**
 Create a shared coordinate space configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_shared_coordinate_space_configuration_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_shared_coordinate_space_configuration_t ar_shared_coordinate_space_configuration_create(void)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Shared Coordinate Space Provider
/**
 Create a shared coordinate space provider.

 - Parameter shared_coordinate_space_configuration: shared coordinate space configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_shared_coordinate_space_provider_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_shared_coordinate_space_provider_t
ar_shared_coordinate_space_provider_create(ar_shared_coordinate_space_configuration_t shared_coordinate_space_configuration) AR_REFINED_FOR_SWIFT;

/**
 Get the identifier used to identify the participant in the shared coordinate space.

 - Parameters:
   - shared_coordinate_space_provider: Shared coordinate space provider.
   - out_identifier: A pointer to a UUID to fill out with the identifier of the participant. Must be non-null.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_shared_coordinate_space_provider_get_participant_identifier(ar_shared_coordinate_space_provider_t shared_coordinate_space_provider,
                                                                              uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the latest sharing status.

 - Parameter shared_coordinate_space_provider: Shared coordinate space provider.

 - Returns: `true` if coordinate space sharing is enabled, `false` otherwise.
*/
API_AVAILABLE(visionos(26.4))
AR_EXTERN bool
ar_shared_coordinate_space_provider_is_sharing_enabled(ar_shared_coordinate_space_provider_t shared_coordinate_space_provider) AR_REFINED_FOR_SWIFT;

/**
 Push data to the shared coordinate space provider.

 - Parameters:
   - shared_coordinate_space_provider: The shared coordinate space provider.
   - coordinate_space_data: Coordinate space data.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_shared_coordinate_space_provider_push_data(ar_shared_coordinate_space_provider_t shared_coordinate_space_provider,
                                                             ar_coordinate_space_data_t coordinate_space_data) AR_REFINED_FOR_SWIFT;

/**
 Determines whether this device supports the shared coordinate space provider.

 - Returns: Returns `true` if provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN bool ar_shared_coordinate_space_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Copy the next collaboration data.

 - Parameter shared_coordinate_space_provider: The shared coordinate space provider.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: Coordinate space data if available, `nil` otherwise.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_coordinate_space_data_t _Nullable ar_shared_coordinate_space_provider_copy_next_coordinate_space_data(
    ar_shared_coordinate_space_provider_t shared_coordinate_space_provider) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving shared coordinate space connected participants updates.

 - Parameters:
   - shared_coordinate_space_provider: The shared coordinate space provider.
   - connected_participants_update_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - connected_participants_update_handler: The handler to be called when there is an update to shared coordinate space connected participants.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_shared_coordinate_space_provider_set_connected_participants_update_handler(
    ar_shared_coordinate_space_provider_t shared_coordinate_space_provider,
    dispatch_queue_t _Nullable connected_participants_update_queue,
    ar_shared_coordinate_space_connected_participants_update_handler_t _Nullable connected_participants_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving shared coordinate space connected participants updates.

 - Parameters:
   - shared_coordinate_space_provider: Shared coordinate space provider.
   - connected_participants_update_queue: Queue on which the function will be executed. Defaults to main queue when NULL is passed in.
   - context: The application-defined context parameter to pass to the function.
   - connected_participants_update_handler_function: Function to be called when there is an update to shared coordinate space connected
     participants. Refer to `ar_shared_coordinate_space_connected_participants_update_handler_function_t` for function signature.

 - Note: Setting this function will override the handler set using `ar_shared_coordinate_space_provider_set_connected_participants_update_handler`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_shared_coordinate_provider_set_connected_participants_update_handler_f(
    ar_shared_coordinate_space_provider_t shared_coordinate_space_provider,
    dispatch_queue_t _Nullable connected_participants_update_queue,
    void *_Nullable context,
    ar_shared_coordinate_space_connected_participants_update_handler_function_t _Nullable connected_participants_update_handler_function)
    AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving sharing status updates.

 Set the sharing status update handler to be informed when the provider starts producing data and when the user can push data.

 - Parameters:
   - shared_coordinate_space_provider: The shared coordinate space provider.
   - status_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - sharing_status_update_handler: The handler to be called when there is an update to shared coordinate space sharing status.

 - Note: Setting this function will override the handler set using `ar_shared_coordinate_space_provider_set_sharing_status_update_handler_f`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_shared_coordinate_space_provider_set_sharing_status_update_handler(
    ar_shared_coordinate_space_provider_t shared_coordinate_space_provider,
    dispatch_queue_t _Nullable status_updates_queue,
    ar_shared_coordinate_space_sharing_status_update_handler_t _Nullable sharing_status_update_handler) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving sharing status updates.

 Set the sharing status update handler to be informed when the provider starts producing data and when the user can push data.

 - Parameters:
   - shared_coordinate_space_provider: The shared coordinate space provider.
   - status_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - sharing_status_update_handler_function: The handler to be called when there is an update to shared coordinate space sharing status.

 - Note: Setting this function will override the handler set using `ar_shared_coordinate_space_provider_set_sharing_status_update_handler`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_shared_coordinate_space_provider_set_sharing_status_update_handler_f(
    ar_shared_coordinate_space_provider_t shared_coordinate_space_provider,
    dispatch_queue_t _Nullable status_updates_queue,
    void *_Nullable context,
    ar_shared_coordinate_space_sharing_status_update_handler_function_t _Nullable sharing_status_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the shared coordinate space provider.

 - Returns: An authorization type.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_authorization_type_t ar_shared_coordinate_space_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif /* shared_coordinate_space_h */
