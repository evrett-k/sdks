/*	NSAffineTransform.h
        Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <CoreFoundation/CFCGTypes.h>

#if TARGET_OS_OSX
#ifndef __swift__
#import <CoreGraphics/CGAffineTransform.h>
#endif
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A structure that defines the three-by-three matrix that performs an affine transform between two coordinate systems.
typedef struct NS_SWIFT_SENDABLE {
    /// An element of the transform matrix that contributes scaling, rotation, and shear.
    CGFloat m11,
    /// An element of the transform matrix that contributes scaling, rotation, and shear.
    m12,
    /// An element of the transform matrix that contributes scaling, rotation, and shear.
    m21,
    /// An element of the transform matrix that contributes scaling, rotation, and shear.
    m22;
    /// An element of the transform matrix that contributes translation along the x axis.
    CGFloat tX,
    /// An element of the transform matrix that contributes translation along the y axis.
    tY;
} NSAffineTransformStruct;

/// A graphics coordinate transformation.
///
/// In Swift, this object bridges to ``AffineTransform``; use ``NSAffineTransform`` when you need reference semantics or other Foundation-specific behavior.
///
/// A transformation specifies how points in one coordinate system are transformed to points in another coordinate system. An affine transformation is a special type of transformation that preserves parallel lines in a path but does not necessarily preserve lengths or angles. Scaling, rotation, and translation are the most commonly used manipulations supported by affine transforms, but shearing is also possible.
///
/// > Note:
/// > In OS X 10.3 and earlier the ``NSAffineTransform`` class was declared and implemented entirely in the Application Kit framework. As of macOS 10.4 the ``NSAffineTransform`` class has been split across the Foundation and Application Kit frameworks.
///
/// Methods for applying affine transformations to the current graphics context and a method for applying an affine transformation to an <doc://com.apple.documentation/documentation/appkit/nsbezierpath> object are described in NSAffineTransform Additions Reference in the Application Kit.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``AffineTransform`` structure, which bridges to the ``NSAffineTransform`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSAffineTransform : NSObject <NSCopying, NSSecureCoding>

// Creation
/// Creates a new affine transform initialized to the identity matrix.
///
/// - Returns: A new identity transform object. This matrix transforms any point to the same point.
+ (NSAffineTransform *)transform;

// Initialization
/// Initializes the receiver's matrix using another transform object.
///
/// - Parameter transform: The transform object whose matrix values should be copied to this object.
/// - Returns: A new transform object initialized with the matrix values of `transform`.
- (instancetype)initWithTransform:(NSAffineTransform *)transform;
/// Initializes an affine transform matrix to the identity matrix.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Translating
/// Applies the specified translation factors to the receiver's transformation matrix.
///
/// Subsequent transformations cause coordinates to be shifted by `deltaX` units along the x axis and by `deltaY` units along the y axis. Translation factors do not affect `NSSize` values, which specify a differential between points.
///
/// - Parameter deltaX: The number of units to move along the x axis.
/// - Parameter deltaY: The number of units to move along the y axis.
- (void)translateXBy:(CGFloat)deltaX yBy:(CGFloat)deltaY;

// Rotating
/// Applies a rotation factor (measured in degrees) to the receiver's transformation matrix.
///
/// After invoking this method, applying the receiver's matrix turns the axes counterclockwise about the current origin by `angle` degrees, in addition to performing all previous transformations.
///
/// - Parameter angle: The rotation angle, measured in degrees.
- (void)rotateByDegrees:(CGFloat)angle;
/// Applies a rotation factor (measured in radians) to the receiver's transformation matrix.
///
/// After invoking this method, applying the receiver's matrix turns the axes counterclockwise about the current origin by `angle` radians, in addition to performing all previous transformations.
///
/// - Parameter angle: The rotation angle, measured in radians.
- (void)rotateByRadians:(CGFloat)angle;

// Scaling
/// Applies the specified scaling factor along both x and y axes to the receiver's transformation matrix.
///
/// After invoking this method, applying the receiver's matrix modifies the unit lengths along the current x and y axes by a factor of `scale`, in addition to performing all previous transformations.
///
/// - Parameter scale: The scaling factor to apply to both axes. Specifying a negative value has the effect of inverting the direction of the axes in addition to scaling them. A scaling factor of 1.0 scales the content to exactly the same size.
- (void)scaleBy:(CGFloat)scale;
/// Applies scaling factors to each axis of the receiver's transformation matrix.
///
/// After invoking this method, applying the receiver's matrix modifies the unit length on the x axis by a factor of `scaleX` and the y axis by a factor of `scaleY`, in addition to performing all previous transformations. A value of 1.0 for either axis scales the content on that axis to the same size.
///
/// - Parameter scaleX: The scaling factor to apply to the x axis.
/// - Parameter scaleY: The scaling factor to apply to the y axis.
- (void)scaleXBy:(CGFloat)scaleX yBy:(CGFloat)scaleY;

// Inverting
/// Replaces the receiver's matrix with its inverse matrix.
///
/// Inverse matrices are useful for undoing the effects of a matrix. If a previous point (x,y) was transformed to (x',y'), inverting the matrix and applying it to point (x',y') yields the point (x,y).
///
/// You can also use inverse matrices in conjunction with the `concat()` method to remove the effects of concatenating the matrix to the current transformation matrix of the current graphic context.
- (void)invert;

// Transforming with transform
/// Appends the specified matrix to the receiver's matrix.
///
/// This method multiplies the receiver's matrix by the matrix in `transform` and replaces the receiver's matrix with the results. This type of operation is the same as applying the transformations in the receiver followed by the transformations in `transform`.
///
/// - Parameter transform: The matrix to append to the receiver.
- (void)appendTransform:(NSAffineTransform *)transform;
/// Prepends the specified matrix to the receiver's matrix.
///
/// This method multiplies the matrix in `transform` by the receiver's matrix and replaces the receiver's matrix with the result. This type of operation is the same as applying the transformations in `transform` followed by the transformations in the receiver.
///
/// - Parameter transform: The matrix to prepend to the receiver.
- (void)prependTransform:(NSAffineTransform *)transform;

// Transforming points and sizes
/// Applies the receiver's transform to the specified point and returns the result.
///
/// - Parameter aPoint: The point in the current coordinate system to which you want to apply the matrix.
/// - Returns: The resulting point after applying the receiver's transformations.
- (NSPoint)transformPoint:(NSPoint)aPoint;
/// Applies the receiver's transform to the specified size and returns the results.
///
/// This method applies the current rotation and scaling factors to `aSize`; it does not apply translation factors. You can think of this method as transforming a vector whose origin is (0, 0) and whose end point is specified by the value in `aSize`. After the rotation and scaling factors are applied, this method effectively returns the end point of the new vector.
///
/// This method is useful for transforming delta or distance values when you need to take scaling and rotation factors into account.
///
/// - Parameter aSize: The size data to which you want to apply the matrix.
/// - Returns: The resulting size after applying the receiver's transformations.
- (NSSize)transformSize:(NSSize)aSize;

// Transform Struct
/// The matrix coefficients stored as the transformation matrix.
///
/// The ``NSAffineTransformStruct`` structure is an alternate representation of a transformation matrix that can be used to specify matrix values directly. The six-element structure is of the form `{m11, m12, m21, m22, tX, tY}`.
@property NSAffineTransformStruct transformStruct;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
