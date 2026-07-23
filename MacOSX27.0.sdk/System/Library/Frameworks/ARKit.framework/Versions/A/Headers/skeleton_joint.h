#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/skeleton_joint.h>)
//
//  skeleton_joint.h
//  ARKit
//
//  Created by Nathaniel Pohl on 8/18/22.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef skeleton_joint_h
#define skeleton_joint_h

#import <ARKit/object.h>
#import <ARKit/transform_correction.h>

#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

/**
 Represents a joint in a skeleton with its transform and tracking state.
 */
AR_OBJECT_DECL(ar_skeleton_joint)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst);

/**
 Returns a bool value that indicates whether the two skeleton joints are equal.

 - Parameters:
   - skeleton_joint: A skeleton joint to be compared.
   - other_skeleton_joint: The other skeleton joint to be compared to.

 - Returns: `YES` if the skeleton joints are equal, otherwise `NO`.
*/
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_skeleton_joint_is_equal_to_skeleton_joint(ar_skeleton_joint_t _Nullable skeleton_joint,
                                                            ar_skeleton_joint_t _Nullable other_skeleton_joint) AR_REFINED_FOR_SWIFT;

/**
 Get a joint's index.

 - Parameter joint: The joint.

 - Returns: The index of the joint.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN uint64_t ar_skeleton_joint_get_index(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get a joint's parent joint.

 - Parameter joint: The joint.

 - Returns: Parent joint. This function will return `null` for the root node.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN ar_skeleton_joint_t _Nullable ar_skeleton_joint_get_parent(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from the joint to its parent joint's coordinate system.

 - Parameter joint: The joint.

 - Note: For a hand skeleton, the root of all these transforms starts at the wrist, then the next joint out (metacarpals and forearm) are relative to
 the wrist, then all knuckles are relative to the metacarpals and so on until the finger tips.
 - Note: This function will return a rendering-corrected transform and is equal to calling
 `ar_skeleton_joint_get_parent_from_joint_transform_with_correction` with `ar_transform_correction_rendered`.

 - Returns: The transform from the joint to its parent joint's coordinate system. This function will return an identity matrix when called for the
 root joint.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_skeleton_joint_get_parent_from_joint_transform(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from the joint to its parent joint's coordinate system.

 - Parameters:
   - joint: The joint.
   - transform_correction: The transform correction that should be applied.

 - Note: For a hand skeleton, the root of all these transforms starts at the wrist, then the next joint out (metacarpals and forearm) are relative to
 the wrist, then all knuckles are relative to the metacarpals and so on until the finger tips.

 - Returns: The transform from the joint to its parent joint's coordinate system. This function will return an identity matrix when called for the
 root joint.
*/
API_AVAILABLE(visionos(27.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_skeleton_joint_get_parent_from_joint_transform_with_correction(
    ar_skeleton_joint_t joint, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from the joint to the anchor's coordinate system.

 - Parameter joint: The joint.

 - Note: This function will return a rendering-corrected transform and is equal to calling
 `ar_skeleton_joint_get_anchor_from_joint_transform_with_correction` with `ar_transform_correction_rendered`.

 - Returns: The transform from the joint to the anchor's coordinate system.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_skeleton_joint_get_anchor_from_joint_transform(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from the joint to the anchor's coordinate system.

 - Parameters:
   - joint: The joint.
   - transform_correction: The transform correction that should be applied.

 - Returns: The transform from the joint to the anchor's coordinate system.
*/
API_AVAILABLE(visionos(27.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN simd_float4x4 ar_skeleton_joint_get_anchor_from_joint_transform_with_correction(
    ar_skeleton_joint_t joint, ar_transform_correction_t transform_correction) AR_REFINED_FOR_SWIFT;

/**
 Determine whether a joint is tracked.

 - Parameter joint: The joint.

 - Returns: `true` if the joint is tracked, `false` otherwise.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
AR_EXTERN bool ar_skeleton_joint_is_tracked(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating skeleton joints.

 - Parameter joint: The joint.

 - Returns: `true` to continue enumerating to the next joint name, `false` to stop enumerating.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef bool (^ar_skeleton_joint_enumerator_t)(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating skeleton joints.

 - Parameters:
   - context: The application-defined context.
   - joint: The joint.

 - Returns: `true` to continue enumerating to the next joint, `false` to stop enumerating.
*/
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos, macCatalyst)
typedef bool (*ar_skeleton_joint_enumerator_function_t)(void *_Nullable context, ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // skeleton_joint_h
#else
#import <ARKitCore/skeleton_joint.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/skeleton_joint.h>)