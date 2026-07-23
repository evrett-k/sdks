//
//  camera_frame_provider.h
//  ARKit
//
//  An enterprise license and/or entitlement is required to receive camera frames, and will otherwise be a no-op.
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef camera_frame_provider_h
#define camera_frame_provider_h

#import <ARKitCore/data_provider.h>
#import <ARKitCore/object.h>
#import <ARKitCore/session.h>

#import <CoreVideo/CVPixelBuffer.h>
#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 Describes a camera video format with frame rate, size, and pixel format.
 */
AR_OBJECT_DECL(ar_camera_video_format)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A collection of camera video formats.
 */
AR_OBJECT_DECL(ar_camera_video_formats)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A camera frame containing one or more camera frame samples.
 */
AR_OBJECT_DECL(ar_camera_frame)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A single camera frame sample with pixel buffer and metadata.
 */
AR_OBJECT_DECL(ar_camera_frame_sample)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A collection of camera frame samples.
 */
AR_OBJECT_DECL(ar_camera_frame_samples)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/**
 Parameters for a camera frame including intrinsics, extrinsics, and timestamps.
 */
AR_OBJECT_DECL(ar_camera_frame_parameters)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 A data provider that delivers camera frames.
 */
AR_OBJECT_DECL_SUBCLASS(ar_camera_frame_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

/**
 Option set describing physical position of a camera sensor on the device relative to the user.
 */
API_AVAILABLE(visionos(2.0))
OS_OPTIONS(ar_camera_position, uint16_t,
  
  /** Camera position on the left side of the device. */
  ar_camera_position_left                               = (1 << 0),
           
  /** Camera position on the right side of the device. */
  ar_camera_position_right API_AVAILABLE(visionos(26.0)) = (1 << 1),

) AR_REFINED_FOR_SWIFT;

/**
 A value describing a type of camera.
 */
API_AVAILABLE(visionos(2.0))
OS_ENUM(ar_camera_type, intptr_t,

    /** The main camera. */
    ar_camera_type_main = 0,

) AR_REFINED_FOR_SWIFT;

/**
 A value describing the type of rectification applied to a video format.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_camera_rectification_type, intptr_t,

    /** Mono camera rectification. */
    ar_camera_rectification_type_mono = 0,

    /** Stereo corrected camera rectification. */
    ar_camera_rectification_type_stereo_corrected,

) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Video Format

/**
 Returns a bool value that indicates whether the two camera video formats are equal.

 - Parameters:
   - camera_video_format: A camera video format to be compared.
   - other_camera_video_format: The other camera video format to be compared to.

 - Returns: `YES` if the camera video formats are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool
    ar_camera_video_format_is_equal_to_camera_video_format(ar_camera_video_format_t _Nullable camera_video_format,
                                                           ar_camera_video_format_t _Nullable other_camera_video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the minimum frame duration for this video format.

 - Parameter video_format: The video format.

 - Returns: The minimum frame duration.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN float ar_camera_video_format_get_minimum_frame_duration(ar_camera_video_format_t video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the maximum frame duration for this video format.

 - Parameter video_format: The video format.

 - Returns: The maximum frame duration.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN float ar_camera_video_format_get_maximum_frame_duration(ar_camera_video_format_t video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the frame size for this video format in pixels.

 - Parameter video_format: The video format.

 - Returns: The frame size in pixels.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CGSize ar_camera_video_format_get_frame_size(ar_camera_video_format_t video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the pixel format for this video format.

 - Parameter video_format: The video format.

 - Returns: The pixel format.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN OSType ar_camera_video_format_get_pixel_format(ar_camera_video_format_t video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the camera type for this video format.

 - Parameter video_format: The video format.

 - Returns: The camera type.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_type_t ar_camera_video_format_get_camera_type(ar_camera_video_format_t video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the camera position for this video format.

 - Parameter video_format: The video format.

 - Returns: The camera position.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_position_t ar_camera_video_format_get_camera_position(ar_camera_video_format_t video_format) AR_REFINED_FOR_SWIFT;

/**
 Get the camera rectification type for this video format.

 - Parameter video_format: The video format.

 - Returns: The camera rectification type.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_camera_rectification_type_t ar_camera_video_format_get_camera_rectification_type(ar_camera_video_format_t video_format)
    AR_REFINED_FOR_SWIFT;

/**
 Returns a collection of supported video formats for a given camera type and position.

 - Parameters:
   - camera_type: The camera type.
   - camera_position: The inclusive set of camera positions that the video formats must match.

 - Note: This type supports ARC. In non-ARC files, use ar_retain() and ar_release() to retain and release the object.

 - Returns: An instance of `ar_camera_video_formats_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_camera_video_formats_t
ar_camera_video_format_copy_supported_video_formats(ar_camera_type_t camera_type, ar_camera_position_t camera_position) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Video Formats Collection

/**
 Get the count of camera video formats in the collection.

 - Parameter camera_video_formats: The camera video formats collection.

 - Returns: The number of camera video formats in the collection.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_camera_video_formats_get_count(ar_camera_video_formats_t camera_video_formats) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating camera video formats.

 - Parameter camera_video_format: The camera video format.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_camera_video_format_enumerator_t)(ar_camera_video_format_t camera_video_format) AR_REFINED_FOR_SWIFT;

/**
 Enumerate all supported video formats for this configuration.

 - Parameters:
   - camera_video_formats: The camera video formats collection.
   - camera_video_formats_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_camera_video_formats_enumerate_video_formats(ar_camera_video_formats_t camera_video_formats,
                                                ar_camera_video_format_enumerator_t camera_video_formats_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating camera video formats.

 - Parameters:
   - context: The application-defined context.
   - camera_video_format: The camera video format.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_camera_video_format_enumerator_function_t)(void *_Nullable context,
                                                             ar_camera_video_format_t camera_video_format) AR_REFINED_FOR_SWIFT;

/**
 Enumerate all supported camera video formats for this configuration using a function.

 - Parameters:
   - camera_video_formats: The camera video formats collection.
   - context: The application-defined context parameter to pass to the function.
   - camera_video_formats_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_camera_video_formats_enumerate_video_formats_f(
    ar_camera_video_formats_t camera_video_formats,
    void *_Nullable context,
    ar_camera_video_format_enumerator_function_t camera_video_formats_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Frame

/**
 Returns a bool value that indicates whether the two camera frames are equal.

 - Parameters:
   - camera_frame: A camera frame to be compared.
   - other_camera_frame: The other camera frame to be compared to.

 - Returns: `YES` if the camera frames are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_camera_frame_is_equal_to_camera_frame(ar_camera_frame_t _Nullable camera_frame,
                                                        ar_camera_frame_t _Nullable other_camera_frame) AR_REFINED_FOR_SWIFT;

/**
 Get the camera frame sample for a given camera position.

 - Parameters:
   - camera_frame: The camera frame.
   - camera_position: The camera position.

 - Returns: An instance of `ar_camera_frame_sample_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_frame_sample_t _Nullable ar_camera_frame_get_frame_sample(ar_camera_frame_t camera_frame,
                                                                              ar_camera_position_t camera_position) AR_REFINED_FOR_SWIFT;

/**
 Get the primary frame sample for this camera frame.

 - Parameter camera_frame: The camera frame.

 - Returns: An instance of `ar_camera_frame_sample_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_frame_sample_t ar_camera_frame_get_primary_frame_sample(ar_camera_frame_t camera_frame) AR_REFINED_FOR_SWIFT;

/**
 Get the collection of camera frame samples for this camera frame.

 - Parameter camera_frame: The camera frame.

 - Returns: An instance of `ar_camera_frame_samples_t`.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_camera_frame_samples_t ar_camera_frame_get_frame_samples(ar_camera_frame_t camera_frame) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Frame Samples

#ifdef __BLOCKS__
/**
 Handler for enumerating camera frame samples.

 - Parameter camera_frame_sample: The camera frame sample.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (^ar_camera_frame_sample_enumerator_t)(ar_camera_frame_sample_t camera_frame_sample) AR_REFINED_FOR_SWIFT;

/**
 Enumerate all camera frame samples in this collection.

 - Parameters:
   - camera_frame_samples: The collection of frame samples.
   - camera_frame_sample_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void
ar_camera_frame_samples_enumerate_frame_samples(ar_camera_frame_samples_t camera_frame_samples,
                                                ar_camera_frame_sample_enumerator_t camera_frame_sample_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating camera frame samples.

 - Parameters:
   - context: The application-defined context.
   - camera_frame_sample: The camera frame sample.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (*ar_camera_frame_sample_enumerator_function_t)(void *_Nullable context,
                                                             ar_camera_frame_sample_t camera_frame_sample) AR_REFINED_FOR_SWIFT;

/**
 Enumerate all supported camera frame samples for this configuration using a function.

 - Parameters:
   - camera_frame_samples: The collection of frame samples.
   - context: The application-defined context parameter to pass to the function.
   - camera_frame_sample_enumerator_function: The enumerator function.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_camera_frame_samples_enumerate_frame_samples_f(ar_camera_frame_samples_t camera_frame_samples,
                                                                 void *_Nullable context,
                                                                 ar_camera_frame_sample_enumerator_function_t camera_frame_sample_enumerator_function)
    AR_REFINED_FOR_SWIFT;

/**
 Get the count of camera frame samples in the collection.

 - Parameter camera_frame_samples: The collection of camera frame samples.

 - Returns: The number of camera frame samples in the collection.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN size_t ar_camera_frame_samples_get_count(ar_camera_frame_samples_t camera_frame_samples) AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Frame Sample

/**
 Returns a bool value that indicates whether the two camera frame samples are equal.

 - Parameters:
   - camera_frame_sample: A camera frame sample to be compared.
   - other_camera_frame_sample: The other camera frame sample to be compared to.

 - Returns: `YES` if the camera frame samples are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool
    ar_camera_frame_sample_is_equal_to_camera_frame_sample(ar_camera_frame_sample_t _Nullable camera_frame_sample,
                                                           ar_camera_frame_sample_t _Nullable other_camera_frame_sample) AR_REFINED_FOR_SWIFT;

/**
 Get the `CVPixelBufferRef` for this frame buffer.

 - Parameter camera_frame_sample: The camera frame sample.

 - Returns: The pixel buffer.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CVPixelBufferRef ar_camera_frame_sample_get_pixel_buffer(ar_camera_frame_sample_t camera_frame_sample) AR_REFINED_FOR_SWIFT;

/**
 Get the camera frame parameters for this camera frame sample.

 - Parameter camera_frame_sample: The camera frame sample.

 - Returns: The camera frame parameters.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_frame_parameters_t ar_camera_frame_sample_get_camera_frame_parameters(ar_camera_frame_sample_t camera_frame_sample)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Frame Parameters

/**
 Returns a bool value that indicates whether the two camera frame parameters are equal.

 - Parameters:
   - camera_frame_parameters: Camera frame parameters to be compared.
   - other_camera_frame_parameters: The other camera frame parameters to be compared to.

 - Returns: `YES` if the camera frame parameters are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_camera_frame_parameters_is_equal_to_camera_frame_parameters(ar_camera_frame_parameters_t _Nullable camera_frame_parameters,
                                                                              ar_camera_frame_parameters_t _Nullable other_camera_frame_parameters)
    AR_REFINED_FOR_SWIFT;

/**
 Get the camera intrinsics.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The camera intrinsics.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float3x3 ar_camera_frame_parameters_get_intrinsics(ar_camera_frame_parameters_t camera_frame_parameters) AR_REFINED_FOR_SWIFT;

/**
 Get the camera extrinsics.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The camera extrinsics.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_camera_frame_parameters_get_extrinsics(ar_camera_frame_parameters_t camera_frame_parameters) AR_REFINED_FOR_SWIFT;

/**
 Get the frame capture timestamp.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The frame capture timestamp as mach absolute time in seconds.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_camera_frame_parameters_get_capture_timestamp(ar_camera_frame_parameters_t camera_frame_parameters) AR_REFINED_FOR_SWIFT;

/**
 Get the frame mid exposure timestamp.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The frame mid exposure timestamp as mach absolute time in seconds.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_camera_frame_parameters_get_mid_exposure_timestamp(ar_camera_frame_parameters_t camera_frame_parameters)
    AR_REFINED_FOR_SWIFT;

/**
 Get the white balance correlated color temperature in kelvin.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The color temperature in kelvin.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN uint32_t ar_camera_frame_parameters_get_color_temperature(ar_camera_frame_parameters_t camera_frame_parameters) AR_REFINED_FOR_SWIFT;

/**
 Get the frame exposure duration.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The exposure duration time in seconds.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_camera_frame_parameters_get_exposure_duration(ar_camera_frame_parameters_t camera_frame_parameters) AR_REFINED_FOR_SWIFT;

/**
 Get the camera type.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The camera type.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_type_t ar_camera_frame_parameters_get_camera_type(ar_camera_frame_parameters_t camera_frame_parameters) AR_REFINED_FOR_SWIFT;

/**
 Get the camera position.

 - Parameter camera_frame_parameters: The camera frame parameters.

 - Returns: The camera position.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_camera_position_t ar_camera_frame_parameters_get_camera_position(ar_camera_frame_parameters_t camera_frame_parameters)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Camera Frame Provider

/**
 Create a camera frame provider.

 An enterprise license and/or entitlement is required to receive camera frames, and will otherwise be a no-op.

 - Note: This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.

 - Returns: An instance of `ar_camera_frame_provider_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_camera_frame_provider_t ar_camera_frame_provider_create(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for observing an updated camera frame.

 - Parameter camera_frame: The camera frame.
*/
API_AVAILABLE(visionos(2.0))
typedef void (^ar_camera_frame_update_handler_t)(ar_camera_frame_t camera_frame) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving camera frame updates for the given video format.

 An enterprise license and/or entitlement is required to receive camera frames, and will otherwise be a no-op.

 - Parameters:
   - camera_frame_provider: The camera frame provider.
   - camera_video_format: The camera video format.
   - camera_frame_update_queue: The camera frame update queue. Passing `NULL` will default to the main queue.
   - camera_frame_update_handler: The camera frame update handler.

 - Note: Setting this handler will override the function set using `ar_camera_frame_provider_set_update_handler_f` for given
 `ar_camera_video_format_t`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_camera_frame_provider_set_update_handler(ar_camera_frame_provider_t camera_frame_provider,
                                            ar_camera_video_format_t camera_video_format,
                                            dispatch_queue_t _Nullable camera_frame_update_queue,
                                            ar_camera_frame_update_handler_t _Nullable camera_frame_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for observing an updated camera frame.

 - Parameters:
   - context: The application-defined context.
   - camera_frame: The camera frame.
*/
API_AVAILABLE(visionos(2.0))
typedef void (*ar_camera_frame_update_handler_function_t)(void *_Nullable context, ar_camera_frame_t camera_frame) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving camera frame updates for the given video format.

 An enterprise license and/or entitlement is required to receive camera frames, and will otherwise be a no-op.

 - Parameters:
   - camera_frame_provider: The camera frame provider.
   - camera_video_format: The camera video format.
   - camera_frame_update_queue: The camera frame update queue. Passing `NULL` will default to the main queue.
   - context: The application-defined context parameter to pass to the function.
   - camera_frame_update_handler_function: The camera frame update handler function.

 - Note: Setting this function will override the handler set using `ar_camera_frame_provider_set_update_handler`.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_camera_frame_provider_set_update_handler_f(ar_camera_frame_provider_t camera_frame_provider,
                                                             ar_camera_video_format_t camera_video_format,
                                                             dispatch_queue_t _Nullable camera_frame_update_queue,
                                                             void *_Nullable context,
                                                             ar_camera_frame_update_handler_function_t _Nullable camera_frame_update_handler_function)
    AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the camera frame provider.

 - Returns: `true` if the camera frame provider is supported on this device, `false` otherwise.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_camera_frame_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the camera frame provider.

 - Returns: The required authorization type.
*/
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_authorization_type_t ar_camera_frame_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // camera_frame_provider_h
