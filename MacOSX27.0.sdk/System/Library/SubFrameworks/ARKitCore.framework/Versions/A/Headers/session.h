//
//  session.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef session_h
#define session_h

#import <ARKitCore/authorization.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/error.h>
#import <ARKitCore/object.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Device

/**
 Represents a physical device that a session can be run on.
 */
AR_OBJECT_DECL(ar_device)
API_UNAVAILABLE(visionos)
API_AVAILABLE(macos(26.0), macCatalyst(26.0));

#pragma mark - Session

/**
 An ARKit session that manages data providers and authorization.
 */
AR_OBJECT_DECL(ar_session)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0));

/**
 Create an ARKit session.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_session_t`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_session_t ar_session_create(void) AR_REFINED_FOR_SWIFT;

/**
 Create a session connected to the specified device.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Parameter device: The device to connect to.

 - Returns: An instance of `ar_session_t`.
*/
API_AVAILABLE(macos(26.0), macCatalyst(26.0))
API_UNAVAILABLE(visionos)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_session_t ar_session_create_with_device(ar_device_t device) AR_REFINED_FOR_SWIFT;

/**
 Session error codes.
 */
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
OS_ENUM(ar_session_error_code, ar_error_code_t,
    /// Error code indicating that a data provider requires an authorization that has not been granted by the user.
    ar_session_error_code_data_provider_not_authorized = 100,
    /// Error code indicating a data provider has failed to run.
    ar_session_error_code_data_provider_failed_to_run = 101
) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 A handler that the session calls when one or more data providers associated with it change state.

 - Parameters:
   - data_providers: The collection of data providers that changed state.
   - new_state: The data provider state that triggered the event.
   - error: An error associated with the state change, if any. Also see `ar_session_error_code_t`.
   - failed_data_provider: The data provider that failed and caused the error, if any.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
typedef void (^ar_session_data_provider_state_change_handler_t)(ar_data_providers_t data_providers,
                                                                ar_data_provider_state_t new_state,
                                                                ar_error_t _Nullable error,
                                                                ar_data_provider_t _Nullable failed_data_provider) AR_REFINED_FOR_SWIFT;

/**
 Sets the handler for responding to a state change of one or more data providers.

 - Parameters:
   - session: The `ar_session_t` instance.
   - queue: The queue on which the handler will be called. Passing NULL will default to the main queue.
   - data_provider_state_change_handler: The data provider state change handler.

 - Note: Setting this will override the function set using `ar_session_set_data_provider_state_change_handler_f`.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN void ar_session_set_data_provider_state_change_handler(
    ar_session_t session,
    dispatch_queue_t _Nullable queue,
    ar_session_data_provider_state_change_handler_t _Nullable data_provider_state_change_handler) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 A handler function that the session calls when one or more data providers associated with it change state.

 - Parameters:
   - context: The application-defined context.
   - data_providers: The collection of data providers that changed state.
   - new_state: The data provider state that triggered the event.
   - error: An error associated with the state change, if any. Also see `ar_session_error_code_t`.
   - failed_data_provider: The data provider that failed and caused the error, if any.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
typedef void (*ar_session_data_provider_state_change_handler_function_t)(void *_Nullable context,
                                                                         ar_data_providers_t data_providers,
                                                                         ar_data_provider_state_t new_state,
                                                                         ar_error_t _Nullable error,
                                                                         ar_data_provider_t _Nullable failed_data_provider) AR_REFINED_FOR_SWIFT;

/**
 Sets the handler function for responding to a state change of one or more data providers.

 - Parameters:
   - session: The `ar_session_t` instance.
   - queue: The queue on which the function will be called. Passing NULL will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - data_provider_state_change_handler_function: The data provider state change handler function.

 - Note: Setting this will override the handler set using `ar_session_set_data_provider_state_change_handler`.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN void ar_session_set_data_provider_state_change_handler_f(
    ar_session_t session,
    dispatch_queue_t _Nullable queue,
    void *_Nullable context,
    ar_session_data_provider_state_change_handler_function_t _Nullable data_provider_state_change_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Run data providers on a session.

 - Parameters:
   - session: The session.
   - data_providers: The collection of data providers to run.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN void ar_session_run(ar_session_t session, ar_data_providers_t data_providers) AR_REFINED_FOR_SWIFT;

/**
 Stop all running data providers on a session.

 - Parameter session: The session.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN void ar_session_stop(ar_session_t session) AR_REFINED_FOR_SWIFT;

/**
 Get a copy of the collection of all data providers on this session.

 - Parameter session: The session.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 - Returns: The collection of data providers.
*/
API_AVAILABLE(visionos(26.0), macos(26.0), macCatalyst(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_data_providers_t ar_session_copy_data_providers(ar_session_t session) AR_REFINED_FOR_SWIFT;

#pragma mark - Session Authorization

#ifdef __BLOCKS__
/**
 Handler to be called when there are updates to authorization.

 - Parameter authorization_result: The authorization result.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
typedef void (^ar_authorization_update_handler_t)(ar_authorization_result_t authorization_result) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving authorization status updates.

 - Parameters:
   - session: The session.
   - authorization_update_queue: The queue on which the handler will be called. Passing NULL will default to the main queue.
   - authorization_update_handler: The handler to be called when there is an update to authorization status.

 - Note: Setting this handler will override the function set using `ar_session_set_authorization_update_handler_f`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void
ar_session_set_authorization_update_handler(ar_session_t session,
                                            dispatch_queue_t _Nullable authorization_update_queue,
                                            ar_authorization_update_handler_t _Nullable authorization_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function to be called when there are updates to authorization.

 - Parameters:
   - context: The application-defined context.
   - authorization_result: The authorization result.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
typedef void (*ar_authorization_update_handler_function_t)(void *_Nullable context,
                                                           ar_authorization_result_t authorization_result) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving authorization status updates.

 - Parameters:
   - session: The session.
   - authorization_update_queue: The queue on which the function will be called. Passing NULL will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - authorization_update_handler_function: The function to be called when there is an update to authorization status.

 - Note: Setting this function will override the handler set using `ar_session_set_authorization_update_handler`.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_session_set_authorization_update_handler_f(
    ar_session_t session,
    dispatch_queue_t _Nullable authorization_update_queue,
    void *_Nullable context,
    ar_authorization_update_handler_function_t _Nullable authorization_update_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler to be called upon completion of an authorization request.

 - Parameters:
   - authorization_results: The collection of authorization results.
   - error: The error that occurred during the authorization request, if any.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
typedef void (^ar_authorization_results_handler_t)(ar_authorization_results_t authorization_results, ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Query the status of different authorization types.

 - Parameters:
   - session: The session.
   - authorization_types: The authorization types to query.
   - results_handler: The handler to be called upon completion of the request. This handler will be called on an arbitrary queue.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_session_query_authorization_results(ar_session_t session,
                                                      ar_authorization_type_t authorization_types,
                                                      ar_authorization_results_handler_t results_handler) AR_REFINED_FOR_SWIFT;

/**
 Request authorization for accessing ARKit data.

 This will asynchronously prompt users for permission to access their data. If the authorization is already allowed or denied by the user,
 the handler will be called without prompting the user for permission again.

 - Parameters:
   - session: The session.
   - authorization_types: The authorization types to request.
   - results_handler: The handler to be called upon completion of the request. This handler will be called on an arbitrary queue.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_session_request_authorization(ar_session_t session,
                                                ar_authorization_type_t authorization_types,
                                                ar_authorization_results_handler_t results_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function to be called upon completion of an authorization request.

 - Parameters:
   - context: The application-defined context.
   - authorization_results: The collection of authorization results.
   - error: The error that occurred during the authorization request, if any.
*/
API_AVAILABLE(visionos(1.0), macos(26.0), macCatalyst(26.0))
typedef void (*ar_authorization_results_handler_function_t)(void *_Nullable context,
                                                            ar_authorization_results_t authorization_results,
                                                            ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Query the status of different authorization types.

 - Parameters:
   - session: The session.
   - authorization_types: The authorization types to query.
   - context: The application-defined context parameter to pass to the function.
   - results_handler_function: The function to be called upon completion of the request. This function will be called on an arbitrary queue.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_session_query_authorization_results_f(ar_session_t session,
                                                        ar_authorization_type_t authorization_types,
                                                        void *_Nullable context,
                                                        ar_authorization_results_handler_function_t results_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Request authorization for accessing ARKit data.

 This will asynchronously prompt users for permission to access their data. If the authorization is already allowed or denied by the user,
 the function will be called without prompting the user for permission again.

 - Parameters:
   - session: The session.
   - authorization_types: The authorization types to request.
   - context: The application-defined context parameter to pass to the function.
   - results_handler_function: The function to be called upon completion of the request. This function will be called on an arbitrary queue.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN void ar_session_request_authorization_f(ar_session_t session,
                                                  ar_authorization_type_t authorization_types,
                                                  void *_Nullable context,
                                                  ar_authorization_results_handler_function_t results_handler_function) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // session_h
