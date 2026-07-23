//
//  ARObjectAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARReferenceObject;

/**
 An anchor representing an object in the world.
 */
API_AVAILABLE(ios(12.0))
NS_SWIFT_SENDABLE
@interface ARObjectAnchor : ARAnchor <ARTrackable>

/**
 Reference to the detected object.
 */
@property (nonatomic, strong, readonly) ARReferenceObject *referenceObject;

/**
 A Boolean value indicating whether the anchor is currently being tracked.
 */
@property (nonatomic, readonly) BOOL isTracked API_AVAILABLE(ios(27.0));

/**
 Unavailable.

 - Parameter transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;

/**
 Unavailable.

 - Parameters:
   - name: The anchor name.
   - transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
