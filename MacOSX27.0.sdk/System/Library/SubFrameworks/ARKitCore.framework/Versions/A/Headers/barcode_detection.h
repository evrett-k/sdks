//
//  barcode_detection.h
//  ARKit
//
//  An enterprise license is required to use barcode detection, and will be otherwise be a no-op.
//  The app must include the following entitlement:
//    com.apple.developer.arkit.barcode-detection.allow
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef barcode_detection_h
#define barcode_detection_h

#import <ARKitCore/anchor.h>
#import <ARKitCore/authorization.h>
#import <ARKitCore/data.h>
#import <ARKitCore/data_provider.h>
#import <ARKitCore/object.h>
#import <ARKitCore/transform_correction.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 An anchor that tracks a barcode's position and orientation in the physical environment.
 */
AR_OBJECT_DECL_SUBCLASS(ar_barcode_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A collection of barcode anchors.
 */
AR_OBJECT_DECL(ar_barcode_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 Configuration for barcode detection.
 */
AR_OBJECT_DECL(ar_barcode_detection_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 Callbacks for barcode detection events.
 */
AR_OBJECT_DECL(ar_barcode_detection_callbacks)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A data provider for barcode detection.
 */
AR_OBJECT_DECL_SUBCLASS(ar_barcode_detection_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 Option set describing possible symbologies of a detected barcode.

 - Note: An `ar_barcode_anchor_t` has exactly one symbology. Multiple bits may be set to configure the `ar_barcode_detection_provider_t` to detect multiple symbologies.
*/
API_AVAILABLE(visionos(2.0))
OS_OPTIONS(ar_barcode_detection_symbology, uint64_t,
    ar_barcode_detection_symbology_none                        = 0,

    /// Aztec symbology. Decodable at 40 cm distance when greater than 2.0 cm wide.
    ar_barcode_detection_symbology_aztec                       = (1 << 0),

    /// Codabar symbology. Decodable at 40 cm distance when greater than 5.5 cm wide.
    ar_barcode_detection_symbology_codabar                     = (1 << 1),

    /// Code 39 symbology. Decodable at 40 cm distance when greater than 6.5 cm wide.
    ar_barcode_detection_symbology_code_39                     = (1 << 2),

    /// Code 39 Checksum symbology. Decodable at 40 cm distance when greater than 6.5 cm wide.
    ar_barcode_detection_symbology_code_39_checksum            = (1 << 3),

    /// Code 39 Full ASCII symbology. Decodable at 40 cm distance when greater than 3.0 cm wide.
    ar_barcode_detection_symbology_code_39_full_ascii          = (1 << 4),

    /// Code 39 Full ASCII Checksum symbology. Decodable at 40 cm distance when greater than 4.5 cm wide.
    ar_barcode_detection_symbology_code_39_full_ascii_checksum = (1 << 5),

    /// Code 93 symbology. Decodable at 40 cm distance when greater than 5.0 cm wide.
    ar_barcode_detection_symbology_code_93                     = (1 << 6),

    /// Code 93i symbology. Decodable at 40 cm distance when greater than 5.0 cm wide.
    ar_barcode_detection_symbology_code_93i                    = (1 << 7),

    /// Code 128 symbology. Decodable at 40 cm distance when greater than 2.5 cm wide.
    ar_barcode_detection_symbology_code_128                    = (1 << 8),

    /// Data Matrix symbology. Decodable at 40 cm distance when greater than 1.0 cm wide.
    ar_barcode_detection_symbology_data_matrix                 = (1 << 9),

    /// EAN-8 symbology. Decodable at 40 cm distance when greater than 3.0 cm wide.
    ar_barcode_detection_symbology_ean_8                       = (1 << 10),

    /// EAN-13 symbology. Decodable at 40 cm distance when greater than 4.0 cm wide.
    ar_barcode_detection_symbology_ean_13                      = (1 << 11),

    /// GS1 Databar symbology. Decodable at 40 cm distance when greater than 3.0 cm wide.
    ar_barcode_detection_symbology_gs1_databar                 = (1 << 12),

    /// GS1 Databar Expanded symbology. Decodable at 40 cm distance when greater than 6.5 cm wide.
    ar_barcode_detection_symbology_gs1_databar_expanded        = (1 << 13),

    /// GS1 Databar Limited symbology. Decodable at 40 cm distance when greater than 3.0 cm wide.
    ar_barcode_detection_symbology_gs1_databar_limited         = (1 << 14),

    /// ITF symbology. Decodable at 40 cm distance when greater than 3.5 cm wide.
    ar_barcode_detection_symbology_itf                         = (1 << 15),

    /// ITF-14 symbology. Decodable at 40 cm distance when greater than 5.0 cm wide.
    ar_barcode_detection_symbology_itf_14                      = (1 << 16),

    /// ITF Checksum symbology. Decodable at 40 cm distance when greater than 3.5 cm wide.
    ar_barcode_detection_symbology_itf_checksum                = (1 << 17),

    /// MicroPDF417 symbology. Decodable at 40 cm distance when greater than 6.5 cm wide.
    ar_barcode_detection_symbology_micropdf417                 = (1 << 18),

    /// MicroQR symbology. Decodable at 40 cm distance when greater than 2.0 cm wide.
    ar_barcode_detection_symbology_microqr                     = (1 << 19),

    /// MSIPlessey symbology. Decodable at 40 cm distance when greater than 4.5 cm wide.
    ar_barcode_detection_symbology_msi_plessey                 = (1 << 20),

    /// PDF417 symbology. Decodable at 40 cm distance when greater than 6.0 cm wide.
    ar_barcode_detection_symbology_pdf417                      = (1 << 21),

    /// QR symbology. Decodable at 40 cm distance when greater than 1.5 cm wide.
    ar_barcode_detection_symbology_qr                          = (1 << 22),

    /// UPC-E symbology. Decodable at 40 cm distance when greater than 2.5 cm wide.
    ar_barcode_detection_symbology_upce                        = (1 << 23),
) AR_REFINED_FOR_SWIFT;

#pragma mark - Barcode Anchor

/**
 Get the symbology of a barcode anchor.

 - Parameter barcode_anchor: The barcode anchor.

 - Returns: The barcode anchor's symbology.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_barcode_detection_symbology_t ar_barcode_anchor_get_symbology(ar_barcode_anchor_t barcode_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the payload string value of a barcode anchor.

 - Parameter barcode_anchor: The barcode anchor.

 - Note: The returned value will have the same lifetime as the input barcode anchor.

 - Returns: The string representation of the barcode anchor's payload.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN const char *_Nullable ar_barcode_anchor_get_payload_string_value(ar_barcode_anchor_t barcode_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get a copy of a barcode anchor's payload data.

 - Parameter barcode_anchor: The barcode anchor.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: A copy of the barcode anchor's payload data.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_data_t ar_barcode_anchor_copy_payload_data(ar_barcode_anchor_t barcode_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the extent of a detected barcode's bounding box.

 - Parameter barcode_anchor: The barcode anchor.

 - Note: The width of the detected barcode is the length along the X-axis, prior to rotation about the Y-axis. The height of the detected barcode is
 the length along the Z-axis, prior to rotation about the Y-axis.

 - Returns: The extent of the detected barcode's bounding box.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float3 ar_barcode_anchor_get_extent(ar_barcode_anchor_t barcode_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Barcode Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 - Parameters:
   - anchor: The anchor.
   - out_identifier: A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_barcode_anchor_get_identifier(ar_barcode_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 - Parameter anchor: The anchor.

 - Returns: The origin from anchor transform.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_barcode_anchor_get_origin_from_anchor_transform(ar_barcode_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system with a transform correction option.

 - Parameters:
   - anchor: The anchor.
   - transform_correction: The transform correction to apply.

 - Returns: The origin from anchor transform with the specified correction.
*/
API_AVAILABLE(visionos(27.0))
AR_EXTERN simd_float4x4 ar_barcode_anchor_get_origin_from_anchor_transform_with_correction(
    ar_barcode_anchor_t anchor, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 - Parameter anchor: The anchor.

 - Returns: The timestamp associated with the anchor.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_barcode_anchor_get_timestamp(ar_barcode_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Barcode Anchors Collection

/**
 Get the count of barcode anchors in a collection.

 - Parameter barcode_anchors: The collection of barcode anchors.

 - Returns: The number of barcode anchors in the collection.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_barcode_anchors_get_count(ar_barcode_anchors_t barcode_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of barcode anchors.

 - Parameter barcode_anchor: The barcode anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_barcode_anchors_enumerator_t)(ar_barcode_anchor_t barcode_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of barcode anchors.

 - Parameters:
   - barcode_anchors: The collection of barcode anchors.
   - barcode_anchors_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_barcode_anchors_enumerate_anchors(ar_barcode_anchors_t barcode_anchors,
                                                    ar_barcode_anchors_enumerator_t barcode_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of barcode anchors.

 - Parameters:
   - context: The application-defined context.
   - barcode_anchor: The barcode anchor.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_barcode_anchors_enumerator_function_t)(void *_Nullable context, ar_barcode_anchor_t barcode_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of barcode anchors using a function.

 - Parameters:
   - barcode_anchors: The collection of barcode anchors.
   - context: The application-defined context parameter to pass to the function.
   - barcode_anchors_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_barcode_anchors_enumerate_anchors_f(ar_barcode_anchors_t barcode_anchors,
                                       void *_Nullable context,
                                       ar_barcode_anchors_enumerator_function_t barcode_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Barcode Detection Configuration

/**
 Create a barcode detection configuration.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_barcode_detection_configuration_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_barcode_detection_configuration_t ar_barcode_detection_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Set the desired symbologies to detect.

 - Parameters:
   - barcode_detection_configuration: The barcode detection configuration.
   - symbology: The symbologies to detect.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_barcode_detection_configuration_set_detection_symbology(ar_barcode_detection_configuration_t barcode_detection_configuration,
                                                                          ar_barcode_detection_symbology_t symbology) AR_REFINED_FOR_SWIFT;

#pragma mark - Barcode Detection Provider

/**
 Create a barcode detection provider.

 - Parameter barcode_detection_configuration: An instance of `ar_barcode_detection_configuration_t`.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_barcode_detection_provider_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_barcode_detection_provider_t
ar_barcode_detection_provider_create(ar_barcode_detection_configuration_t barcode_detection_configuration) AR_REFINED_FOR_SWIFT;

/**
 Determines whether this device supports the barcode detection provider.

 - Returns: Returns `true` if the barcode detection provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_barcode_detection_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when there are updates to barcode anchors.

 - Parameters:
   - added_anchors: The collection of anchors that were added.
   - updated_anchors: The collection of anchors that were updated.
   - removed_anchors: The collection of anchors that were removed.
*/
API_AVAILABLE(visionos(2.0))
typedef void (^ar_barcode_detection_update_handler_t)(ar_barcode_anchors_t added_anchors,
                                                      ar_barcode_anchors_t updated_anchors,
                                                      ar_barcode_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to barcode anchors.

 - Parameters:
   - context: The application-defined context.
   - added_anchors: The collection of anchors that were added.
   - updated_anchors: The collection of anchors that were updated.
   - removed_anchors: The collection of anchors that were removed.
*/
API_AVAILABLE(visionos(2.0))
typedef void (*ar_barcode_detection_update_handler_function_t)(void *_Nullable context,
                                                               ar_barcode_anchors_t added_anchors,
                                                               ar_barcode_anchors_t updated_anchors,
                                                               ar_barcode_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving barcode detection updates.

 - Parameters:
   - barcode_detection_provider: The barcode detection provider.
   - barcode_detection_updates_queue: The queue on which the handler will be called. Passing NULL will default to the main queue.
   - barcode_detection_update_handler: Handler to be called when new anchor data arrives. Refer to `ar_barcode_detection_update_handler_t` for
     handler signature.

 - Note: Setting this handler will override the function set using `ar_barcode_detection_provider_set_update_handler_f`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_barcode_detection_provider_set_update_handler(ar_barcode_detection_provider_t barcode_detection_provider,
                                                                dispatch_queue_t _Nullable barcode_detection_updates_queue,
                                                                ar_barcode_detection_update_handler_t _Nullable barcode_detection_update_handler)
    AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving barcode detection updates.

 - Parameters:
   - barcode_detection_provider: The barcode detection provider.
   - barcode_detection_updates_queue: The queue on which the handler will be called. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - barcode_detection_update_handler_function: The function to be called when new barcode detection updates arrive.

 - Note: Setting this function will override the handler set using `ar_barcode_detection_provider_set_update_handler`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_barcode_detection_provider_set_update_handler_f(
    ar_barcode_detection_provider_t barcode_detection_provider,
    dispatch_queue_t _Nullable barcode_detection_updates_queue,
    void *_Nullable context,
    ar_barcode_detection_update_handler_function_t _Nullable barcode_detection_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the barcode detection provider.

 - Returns: The required authorization type.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_authorization_type_t ar_barcode_detection_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // barcode_detection_h
