/*	NSGeometry.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <AvailabilityMacros.h>
#import <Foundation/NSValue.h>
#import <Foundation/NSCoder.h>

#import <CoreFoundation/CoreFoundation.h>
#import <CoreFoundation/CFCGTypes.h>

#if TARGET_OS_OSX
#ifndef __swift__
#import <CoreGraphics/CGBase.h>
#import <CoreGraphics/CGGeometry.h>
#endif
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if __LP64__ || TARGET_OS_IPHONE || NS_BUILD_32_LIKE_64

/// A point in a Cartesian coordinate system.
///
/// Prior to OS X v10.5 the coordinates were represented by `float` values rather than `CGFloat` values.
///
/// When building for 64 bit systems, or building 32 bit like 64 bit, `NSPoint` is typedef'd to `CGPoint`.
typedef CGPoint NSPoint;

/// Type indicating a parameter is a pointer to an `NSPoint` structure.
typedef NSPoint *NSPointPointer;
/// Type indicating a parameter is array of `NSPoint` structures.
typedef NSPoint *NSPointArray;

/// A two-dimensional size.
///
/// Normally, the values of `width` and `height` are non-negative. The functions that create an `NSSize` structure do not prevent you from setting a negative value for these attributes. If the value of `width` or `height` is negative, however, the behavior of some methods may be undefined.
///
/// Prior to OS X v10.5 the width and height were represented by `float` values rather than `CGFloat` values.
///
/// When building for 64 bit systems, or building 32 bit like 64 bit, `NSSize` is typedef'd to `CGSize`.
typedef CGSize NSSize;

/// Type indicating parameter is a pointer to an `NSSize` structure.
typedef NSSize *NSSizePointer;
/// Type indicating a parameter is an array of `NSSize` structures.
typedef NSSize *NSSizeArray;

/// A rectangle.
///
/// When building for 64 bit systems, or building 32 bit like 64 bit, `NSRect` is typedef'd to `CGRect`.
typedef CGRect NSRect;

/// Type indicating a parameter is a pointer to an `NSRect` structure.
typedef NSRect *NSRectPointer;
/// Type indicating a parameter is array of `NSRect` structures.
typedef NSRect *NSRectArray;

typedef NS_ENUM(NSUInteger, NSRectEdge) {
    NSRectEdgeMinX = CGRectMinXEdge,
    NSRectEdgeMinY = CGRectMinYEdge,
    NSRectEdgeMaxX = CGRectMaxXEdge,
    NSRectEdgeMaxY = CGRectMaxYEdge,
    
    NSMinXEdge NS_SWIFT_UNAVAILABLE("Use NSRectEdge.MinX instead") = NSRectEdgeMinX,
    NSMinYEdge NS_SWIFT_UNAVAILABLE("Use NSRectEdge.MinY instead") = NSRectEdgeMinY,
    NSMaxXEdge NS_SWIFT_UNAVAILABLE("Use NSRectEdge.MaxX instead") = NSRectEdgeMaxX,
    NSMaxYEdge NS_SWIFT_UNAVAILABLE("Use NSRectEdge.MaxY instead") = NSRectEdgeMaxY,
};

#define NSGEOMETRY_TYPES_SAME_AS_CGGEOMETRY_TYPES 1

#else

/// A point in a Cartesian coordinate system.
///
/// Prior to OS X v10.5 the coordinates were represented by `float` values rather than `CGFloat` values.
///
/// When building for 64 bit systems, or building 32 bit like 64 bit, `NSPoint` is typedef'd to `CGPoint`.
typedef struct NS_SWIFT_SENDABLE _NSPoint {
    CGFloat x;
    CGFloat y;
} NSPoint;

/// Type indicating a parameter is a pointer to an `NSPoint` structure.
typedef NSPoint *NSPointPointer;
/// Type indicating a parameter is array of `NSPoint` structures.
typedef NSPoint *NSPointArray;

/// A two-dimensional size.
///
/// Normally, the values of `width` and `height` are non-negative. The functions that create an `NSSize` structure do not prevent you from setting a negative value for these attributes. If the value of `width` or `height` is negative, however, the behavior of some methods may be undefined.
///
/// Prior to OS X v10.5 the width and height were represented by `float` values rather than `CGFloat` values.
///
/// When building for 64 bit systems, or building 32 bit like 64 bit, `NSSize` is typedef'd to `CGSize`.
typedef struct NS_SWIFT_SENDABLE _NSSize {
    CGFloat width;		/* should never be negative */
    CGFloat height;		/* should never be negative */
} NSSize;

/// Type indicating parameter is a pointer to an `NSSize` structure.
typedef NSSize *NSSizePointer;
/// Type indicating a parameter is an array of `NSSize` structures.
typedef NSSize *NSSizeArray;

/// A rectangle.
///
/// When building for 64 bit systems, or building 32 bit like 64 bit, `NSRect` is typedef'd to `CGRect`.
typedef struct NS_SWIFT_SENDABLE _NSRect {
    NSPoint origin;
    NSSize size;
} NSRect;

/// Type indicating a parameter is a pointer to an `NSRect` structure.
typedef NSRect *NSRectPointer;
/// Type indicating a parameter is array of `NSRect` structures.
typedef NSRect *NSRectArray;

typedef enum {
    NSRectEdgeMinX = 0,
    NSRectEdgeMinY = 1,
    NSRectEdgeMaxX = 2,
    NSRectEdgeMaxY = 3,
    
    NSMinXEdge = NSRectEdgeMinX,
    NSMinYEdge = NSRectEdgeMinY,
    NSMaxXEdge = NSRectEdgeMaxX,
    NSMaxYEdge = NSRectEdgeMaxY,
} NSRectEdge;

#endif

#define NSEDGEINSETS_DEFINED 1

/// A description of the distance between the edges of two rectangles.
///
/// Edge insets describe the distance between the edges of one rectangle to a related rectangle that can be described by measuring a constant but edge-specific distance from each edge.
///
/// A common use for this structure is to describe the relationship between a view's frame and its alignment rectangle.
typedef struct NS_SWIFT_SENDABLE NSEdgeInsets {
    /// The top edge inset value.
    CGFloat top;
    /// The left edge inset value.
    CGFloat left;
    /// The bottom edge inset value.
    CGFloat bottom;
    /// The right edge inset value.
    CGFloat right;
} NSEdgeInsets;

/// Values representing alignment operations.
///
/// These constants are used by ``NSIntegralRectWithOptions(_:_:)`` and other related methods.
typedef NS_OPTIONS(unsigned long long, NSAlignmentOptions) {
    /// Specifies that alignment of the minimum X coordinate should be to the nearest inward integral value.
    NSAlignMinXInward   = 1ULL << 0,
    /// Specifies that alignment of the minimum Y coordinate should be to the nearest inward integral value.
    NSAlignMinYInward   = 1ULL << 1,
    /// Specifies that alignment of the maximum X coordinate should be to the nearest inward integral value.
    NSAlignMaxXInward   = 1ULL << 2,
    /// Specifies that alignment of the maximum Y coordinate should be to the nearest inward integral value.
    NSAlignMaxYInward   = 1ULL << 3,
    /// Specifies that alignment of the width should be to the nearest inward integral value.
    NSAlignWidthInward  = 1ULL << 4,
    /// Specifies that alignment of the height should be to the nearest inward integral value.
    NSAlignHeightInward = 1ULL << 5,

    /// Specifies that alignment of the minimum X coordinate should be to the nearest outward integral value.
    NSAlignMinXOutward   = 1ULL << 8,
    /// Specifies that alignment of the minimum Y coordinate should be to the nearest outward integral value.
    NSAlignMinYOutward   = 1ULL << 9,
    /// Specifies that alignment of the maximum X coordinate should be to the nearest outward integral value.
    NSAlignMaxXOutward   = 1ULL << 10,
    /// Specifies that alignment of the maximum Y coordinate should be to the nearest outward integral value.
    NSAlignMaxYOutward   = 1ULL << 11,
    /// Specifies that alignment of the width should be to the nearest outward integral value.
    NSAlignWidthOutward  = 1ULL << 12,
    /// Specifies that alignment of the height should be to the nearest outward integral value.
    NSAlignHeightOutward = 1ULL << 13,

    /// Specifies that alignment of the minimum X coordinate should be to the nearest integral value.
    NSAlignMinXNearest   = 1ULL << 16,
    /// Specifies that alignment of the minimum Y coordinate should be to the nearest integral value.
    NSAlignMinYNearest   = 1ULL << 17,
    /// Specifies that alignment of the maximum X coordinate should be to the nearest integral value.
    NSAlignMaxXNearest   = 1ULL << 18,
    /// Specifies that alignment of the maximum Y coordinate should be to the nearest integral value.
    NSAlignMaxYNearest   = 1ULL << 19,
    /// Specifies that alignment of the width should be to the nearest integral value.
    NSAlignWidthNearest  = 1ULL << 20,
    /// Specifies that alignment of the height should be to the nearest integral value.
    NSAlignHeightNearest = 1ULL << 21,

    /// This option should be included if the rectangle is in a flipped coordinate system. This allows 0.5 to be treated in a visually consistent way.
    NSAlignRectFlipped = 1ULL << 63,

    // convenience combinations
    /// Aligns all edges inward. This is the same as `NSAlignMinXInward|NSAlignMaxXInward|NSAlignMinYInward|NSAlignMaxYInward`.
    NSAlignAllEdgesInward = NSAlignMinXInward|NSAlignMaxXInward|NSAlignMinYInward|NSAlignMaxYInward,
    /// Aligns all edges outward. This is the same as `NSAlignMinXOutward|NSAlignMaxXOutward|NSAlignMinYOutward|NSAlignMaxYOutward`.
    NSAlignAllEdgesOutward = NSAlignMinXOutward|NSAlignMaxXOutward|NSAlignMinYOutward|NSAlignMaxYOutward,
    /// Aligns all edges to the nearest integral value. This is the same as `NSAlignMinXNearest|NSAlignMaxXNearest|NSAlignMinYNearest|NSAlignMaxYNearest`.
    NSAlignAllEdgesNearest = NSAlignMinXNearest|NSAlignMaxXNearest|NSAlignMinYNearest|NSAlignMaxYNearest,
};

@class NSString;

/// A point with both coordinates set to `0`.
FOUNDATION_EXPORT const NSPoint NSZeroPoint;
/// A size with both dimensions set to `0`.
FOUNDATION_EXPORT const NSSize NSZeroSize;
/// A rectangle with origin and size set to `0`.
FOUNDATION_EXPORT const NSRect NSZeroRect;
/// Edge insets with all values set to `0`.
FOUNDATION_EXPORT const NSEdgeInsets NSEdgeInsetsZero API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Creates a new `NSPoint` from the specified values.
///
/// - Parameters:
///   - x: The x coordinate.
///   - y: The y coordinate.
/// - Returns: An `NSPoint` having the coordinates `x` and `y`.
NS_INLINE NSPoint NSMakePoint(CGFloat x, CGFloat y) {
    NSPoint p;
    p.x = x;
    p.y = y;
    return p;
}

/// Creates a new `NSSize` from the specified values.
///
/// - Parameters:
///   - w: The width.
///   - h: The height.
/// - Returns: An `NSSize` having the specified `width` and `height`.
NS_INLINE NSSize NSMakeSize(CGFloat w, CGFloat h) {
    NSSize s;
    s.width = w;
    s.height = h;
    return s;
}

/// Creates a new `NSRect` from the specified values.
///
/// - Parameters:
///   - x: The x coordinate of the origin.
///   - y: The y coordinate of the origin.
///   - w: The width.
///   - h: The height.
/// - Returns: An `NSRect` having the specified origin of [`x`, `y`] and size of [`w`, `h`].
NS_INLINE NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
    NSRect r;
    r.origin.x = x;
    r.origin.y = y;
    r.size.width = w;
    r.size.height = h;
    return r;
}

/// Returns the largest x coordinate of a given rectangle.
///
/// - Returns: The largest x coordinate value within `aRect`.
NS_INLINE CGFloat NSMaxX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width);
}

/// Returns the largest y coordinate of a given rectangle.
///
/// - Returns: The largest y coordinate value within `aRect`.
NS_INLINE CGFloat NSMaxY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height);
}

/// Returns the x coordinate of a given rectangle's midpoint.
///
/// - Returns: The x coordinate of the center of `aRect`.
NS_INLINE CGFloat NSMidX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width * (CGFloat)0.5);
}

/// Returns the y coordinate of a given rectangle's midpoint.
///
/// - Returns: The y coordinate of `aRect`'s center point.
NS_INLINE CGFloat NSMidY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height * (CGFloat)0.5);
}

/// Returns the smallest x coordinate of a given rectangle.
///
/// - Returns: The smallest x coordinate value within `aRect`.
NS_INLINE CGFloat NSMinX(NSRect aRect) {
    return (aRect.origin.x);
}

/// Returns the smallest y coordinate of a given rectangle.
///
/// - Returns: The smallest y coordinate value within `aRect`.
NS_INLINE CGFloat NSMinY(NSRect aRect) {
    return (aRect.origin.y);
}

/// Returns the width of the specified rectangle.
///
/// - Returns: The width of `aRect`.
NS_INLINE CGFloat NSWidth(NSRect aRect) {
    return (aRect.size.width);
}

/// Returns the height of a given rectangle.
///
/// - Returns: The height of `aRect`.
NS_INLINE CGFloat NSHeight(NSRect aRect) {
    return (aRect.size.height);
}

/// Returns an `NSRect` typecast from a `CGRect`.
///
/// - Returns: An `NSRect` typecast from a `CGRect`.
NS_INLINE NSRect NSRectFromCGRect(CGRect cgrect) {
    union _ {NSRect ns; CGRect cg;};
    return ((union _ *)&cgrect)->ns;
}

/// Returns a `CGRect` typecast from an `NSRect`.
///
/// - Returns: A `CGRect` typecast from an `NSRect`.
NS_INLINE CGRect NSRectToCGRect(NSRect nsrect) {
    union _ {NSRect ns; CGRect cg;};
    return ((union _ *)&nsrect)->cg;
}

/// Returns an `NSPoint` typecast from a `CGPoint`.
///
/// - Returns: An `NSPoint` typecast from a `CGPoint`.
NS_INLINE NSPoint NSPointFromCGPoint(CGPoint cgpoint) {
    union _ {NSPoint ns; CGPoint cg;};
    return ((union _ *)&cgpoint)->ns;
}

/// Returns a `CGPoint` typecast from an `NSPoint`.
///
/// - Returns: A `CGPoint` typecast from an `NSPoint`.
NS_INLINE CGPoint NSPointToCGPoint(NSPoint nspoint) {
    union _ {NSPoint ns; CGPoint cg;};
    return ((union _ *)&nspoint)->cg;
}

/// Returns an `NSSize` typecast from a `CGSize`.
///
/// - Returns: An `NSSize` typecast from a `CGSize`.
NS_INLINE NSSize NSSizeFromCGSize(CGSize cgsize) {
    union _ {NSSize ns; CGSize cg;};
    return ((union _ *)&cgsize)->ns;
}

/// Returns a `CGSize` typecast from an `NSSize`.
///
/// - Returns: A `CGSize` typecast from an `NSSize`.
NS_INLINE CGSize NSSizeToCGSize(NSSize nssize) {
    union _ {NSSize ns; CGSize cg;};
    return ((union _ *)&nssize)->cg;
}

/// Creates an edge insets structure with the specified inset values.
///
/// - Parameters:
///   - top: The top edge inset value.
///   - left: The left edge inset value.
///   - bottom: The bottom edge inset value.
///   - right: The right edge inset value.
/// - Returns: A new `NSEdgeInsets` with the specified values.
NS_INLINE NSEdgeInsets NSEdgeInsetsMake(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
    NSEdgeInsets e;
    e.top = top;
    e.left = left;
    e.bottom = bottom;
    e.right = right;
    return e;
}

/// Returns a Boolean value that indicates whether two points are equal.
///
/// - Returns: `true` if the two points `aPoint` and `bPoint` are identical, otherwise `false`.
FOUNDATION_EXPORT BOOL NSEqualPoints(NSPoint aPoint, NSPoint bPoint);
/// Returns a Boolean value that indicates whether two size values are equal.
///
/// - Returns: `true` if `aSize` and `bSize` are identical, otherwise `false`.
FOUNDATION_EXPORT BOOL NSEqualSizes(NSSize aSize, NSSize bSize);
/// Returns a Boolean value that indicates whether the two rectangles are equal.
///
/// - Returns: `true` if `aRect` and `bRect` are identical, otherwise `false`.
FOUNDATION_EXPORT BOOL NSEqualRects(NSRect aRect, NSRect bRect);
/// Returns a Boolean value that indicates whether a given rectangle is empty.
///
/// - Returns: `true` if `aRect` encloses no area at all -- that is, if its width or height is 0 or negative, otherwise `false`.
FOUNDATION_EXPORT BOOL NSIsEmptyRect(NSRect aRect);
/// Returns a Boolean value that indicates whether two edge insets structures are equal.
FOUNDATION_EXPORT BOOL NSEdgeInsetsEqual(NSEdgeInsets aInsets, NSEdgeInsets bInsets) API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Insets a rectangle by a specified amount.
///
/// - Returns: A copy of `aRect`, altered by moving the two sides that are parallel to the y axis inward by `dX`, and the two sides parallel to the x axis inwards by `dY`.
FOUNDATION_EXPORT NSRect NSInsetRect(NSRect aRect, CGFloat dX, CGFloat dY);
/// Adjusts the sides of a rectangle to integer values.
///
/// - Returns: A copy of `aRect`, expanded outward just enough to ensure that none of its four defining values (x, y, width, and height) have fractional parts. If the width or height of `aRect` is `0` or negative, this function returns a rectangle with origin at (0.0, 0.0) and with zero width and height.
FOUNDATION_EXPORT NSRect NSIntegralRect(NSRect aRect);
/// Adjusts the sides of a rectangle to integral values using the specified options.
///
/// - Returns: A copy of `aRect`, modified based on the options. The options are defined in `NSAlignmentOptions`.
FOUNDATION_EXPORT NSRect NSIntegralRectWithOptions(NSRect aRect, NSAlignmentOptions opts) API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Calculates the union of two rectangles.
///
/// Returns the smallest rectangle that completely encloses both `aRect` and `bRect`. If one of the rectangles has 0 (or negative) width or height, a copy of the other rectangle is returned; but if both have 0 (or negative) width or height, the returned rectangle has its origin at (0.0, 0.0) and has 0 width and height.
FOUNDATION_EXPORT NSRect NSUnionRect(NSRect aRect, NSRect bRect);
/// Calculates the intersection of two rectangles.
///
/// - Returns: The graphic intersection of `aRect` and `bRect`. If the two rectangles don't overlap, the returned rectangle has its origin at (0.0, 0.0) and zero width and height (including situations where the intersection is a point or a line segment).
FOUNDATION_EXPORT NSRect NSIntersectionRect(NSRect aRect, NSRect bRect);
/// Offsets the rectangle by the specified amount.
///
/// - Returns: A copy of `aRect`, with its location shifted by `dX` along the x axis and by `dY` along the y axis.
FOUNDATION_EXPORT NSRect NSOffsetRect(NSRect aRect, CGFloat dX, CGFloat dY);
/// Divides a rectangle into two new rectangles.
///
/// Creates two rectangles -- `slice` and `rem` -- from `inRect`, by dividing `inRect` with a line that's parallel to the side of `inRect` specified by `edge`. The size of `slice` is determined by `amount`, which specifies the distance from `edge`.
///
/// `slice` and `rem` must not be `NULL`.
FOUNDATION_EXPORT void NSDivideRect(NSRect inRect, NSRect *slice, NSRect *rem, CGFloat amount, NSRectEdge edge);
/// Returns a Boolean value that indicates whether a given point is in a given rectangle.
///
/// Point-in-rectangle functions generally assume that the "upper" and "left" edges of a rectangle are inside the rectangle boundaries, while the "lower" and "right" edges are outside the boundaries. This method treats the "upper" and "left" edges of the rectangle as the ones containing the origin of the rectangle.
///
/// > The meanings of "upper" and "lower" (and "left" and "right") are relative to the current coordinate system and the location of the rectangle. For a rectangle of positive height located in positive x and y coordinates:
/// > - In the default macOS desktop coordinate system -- where the origin is at the bottom left -- the rectangle edge closest to the bottom of the screen is the "upper" edge (and is considered inside the rectangle).
/// > - On iOS and in a flipped coordinate system in macOS desktop -- where the origin is at the top left -- the rectangle edge closest to the bottom of the screen is the "lower" edge (and is considered outside the rectangle).
///
/// - Returns: `true` if `aPoint` is located within the rectangle represented by `aRect`, otherwise `false`.
FOUNDATION_EXPORT BOOL NSPointInRect(NSPoint aPoint, NSRect aRect);
/// Returns a Boolean value that indicates whether the point is in the specified rectangle.
///
/// This method assumes an unscaled and unrotated coordinate system. Specify `true` for `flipped` if the underlying view uses a flipped coordinate system.
///
/// Point-in-rectangle functions generally assume that the bottom edge of a rectangle is outside of the rectangle boundaries, while the upper edge is inside the boundaries. This method views `aRect` from the point of view of the user -- that is, this method always treats the bottom edge of the rectangle as the one closest to the bottom edge of the user's screen. By making this adjustment, this function ensures consistent mouse-detection behavior from the user's perspective.
///
/// - Returns: `true` if the hot spot of the cursor lies inside a given rectangle, otherwise `false`.
FOUNDATION_EXPORT BOOL NSMouseInRect(NSPoint aPoint, NSRect aRect, BOOL flipped);
/// Returns a Boolean value that indicates whether one rectangle completely encloses another.
///
/// - Returns: `true` if `aRect` completely encloses `bRect`. For this condition to be true, `bRect` cannot be empty, and must not extend beyond `aRect` in any direction.
FOUNDATION_EXPORT BOOL NSContainsRect(NSRect aRect, NSRect bRect);
/// Returns a Boolean value that indicates whether two rectangles intersect.
///
/// - Returns: `true` if `aRect` intersects `bRect`, otherwise `false`. Returns `false` if either `aRect` or `bRect` has a width or height that is 0.
FOUNDATION_EXPORT BOOL NSIntersectsRect(NSRect aRect, NSRect bRect);

/// Returns a string representation of a point.
///
/// - Parameters:
///   - aPoint: A point structure.
/// - Returns: A string of the form "\{a, b\}", where a and b are the x and y coordinates of `aPoint`.
FOUNDATION_EXPORT NSString *NSStringFromPoint(NSPoint aPoint);
/// Returns a string representation of a size.
///
/// - Returns: A string of the form "\{a, b\}", where a and b are the width and height, respectively, of `aSize`.
FOUNDATION_EXPORT NSString *NSStringFromSize(NSSize aSize);
/// Returns a string representation of a rectangle.
///
/// Returns a string of the form "\{\{a, b\}, \{c, d\}\}", where a, b, c, and d are the x and y coordinates and the width and height, respectively, of `aRect`.
FOUNDATION_EXPORT NSString *NSStringFromRect(NSRect aRect);
/// Returns a point from a text-based representation.
///
/// - Parameters:
///   - aString: A string of the form "\{x, y\}".
/// - Returns: If `aString` is of the form "\{x, y\}" an `NSPoint` structure that uses x and y as the x and y coordinates, in that order.
///
/// If `aString` only contains a single number, it is used as the x coordinate. If `aString` does not contain any numbers, returns an `NSPoint` object whose x and y coordinates are both 0.
FOUNDATION_EXPORT NSPoint NSPointFromString(NSString *aString);
/// Returns a size from a text-based representation.
///
/// Scans `aString` for two numbers which are used as the width and height, in that order, to create an `NSSize` struct. If `aString` only contains a single number, it is used as the width. The `aString` argument should be formatted like the output of ``NSStringFromSize``, for example, `@"\{10,20\}"`. If `aString` does not contain any numbers, this function returns an `NSSize` struct whose width and height are both `0`.
FOUNDATION_EXPORT NSSize NSSizeFromString(NSString *aString);
/// Returns a rectangle from a text-based representation.
///
/// Scans `aString` for four numbers which are used as the x and y coordinates and the width and height, in that order, to create an `NSRect` object. If `aString` does not contain four numbers, those numbers that were scanned are used, and 0 is used for the remaining values. If `aString` does not contain any numbers, this function returns an `NSRect` object with a rectangle whose origin is (0, 0) and width and height are both 0.
FOUNDATION_EXPORT NSRect NSRectFromString(NSString *aString);

@interface NSValue (NSValueGeometryExtensions)

/// Creates a new value object containing the specified Foundation point structure.
///
/// - Parameters:
///   - point: The value for the new object.
/// - Returns: A new value object that contains the point information.
+ (NSValue *)valueWithPoint:(NSPoint)point;
/// Creates a new value object containing the specified Foundation size structure.
///
/// - Parameters:
///   - size: The value for the new object.
/// - Returns: A new value object that contains the size information.
+ (NSValue *)valueWithSize:(NSSize)size;
/// Creates a new value object containing the specified Foundation rectangle structure.
///
/// - Parameters:
///   - rect: The value for the new object.
/// - Returns: A new value object that contains the data in the `rect` structure.
+ (NSValue *)valueWithRect:(NSRect)rect;
/// Creates a new value object containing the specified edge insets structure.
+ (NSValue *)valueWithEdgeInsets:(NSEdgeInsets)insets API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The Foundation point structure representation of the value.
@property (readonly) NSPoint pointValue;
/// The Foundation size structure representation of the value.
@property (readonly) NSSize sizeValue;
/// The Foundation rectangle structure representation of the value.
@property (readonly) NSRect rectValue;
/// The edge insets structure representation of the value.
@property (readonly) NSEdgeInsets edgeInsetsValue API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

@end

@interface NSCoder (NSGeometryCoding)

/// Encodes a point.
///
/// `NSCoder`'s implementation invokes ``encodeValue(ofObjCType:at:)`` to encode `point`.
/// This method must be matched by a subsequent ``decodePoint`` message.
- (void)encodePoint:(NSPoint)point;
/// Decodes and returns an `NSPoint` structure that was previously encoded with ``encodePoint:``.
- (NSPoint)decodePoint;

/// Encodes a size structure.
///
/// `NSCoder`'s implementation invokes ``encodeValue(ofObjCType:at:)`` to encode `size`.
/// This method must be matched by a subsequent ``decodeSize`` message.
- (void)encodeSize:(NSSize)size;
/// Decodes and returns an `NSSize` structure that was previously encoded with ``encodeSize:``.
- (NSSize)decodeSize;

/// Encodes a rectangle structure.
///
/// `NSCoder`'s implementation invokes ``encodeValue(ofObjCType:at:)`` to encode `rect`.
/// This method must be matched by a subsequent ``decodeRect`` message.
- (void)encodeRect:(NSRect)rect;
/// Decodes and returns an `NSRect` structure that was previously encoded with ``encodeRect:``.
- (NSRect)decodeRect;

@end

@interface NSCoder (NSGeometryKeyedCoding)

/// Encodes a point and associates it with the string key.
- (void)encodePoint:(NSPoint)point forKey:(NSString *)key;
/// Encodes a size structure and associates it with the given string key.
- (void)encodeSize:(NSSize)size forKey:(NSString *)key;
/// Encodes a rectangle structure and associates it with the string key.
- (void)encodeRect:(NSRect)rect forKey:(NSString *)key;

/// Decodes and returns an `NSPoint` structure that was previously encoded with ``encodePoint:forKey:``.
- (NSPoint)decodePointForKey:(NSString *)key;
/// Decodes and returns an `NSSize` structure that was previously encoded with ``encodeSize:forKey:``.
- (NSSize)decodeSizeForKey:(NSString *)key;
/// Decodes and returns an `NSRect` structure that was previously encoded with ``encodeRect:forKey:``.
- (NSRect)decodeRectForKey:(NSString *)key;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
