//
/*
        NSViewCornerConfiguration.h
        Application Kit
        Copyright (c) 2026, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSViewCornerRadius.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// A configuration object that defines the corner styles of a view’s overall shape.
API_AVAILABLE(macos(27.0))
@interface NSViewCornerConfiguration : NSObject

/// A configuration that applies the given radius independently to all corners.
///
/// When used with a container concentric radius, this allows each individual
/// corner to resolve to different radii.
+ (NSViewCornerConfiguration *)configurationWithRadius:(NSViewCornerRadius *)radius NS_SWIFT_NAME(corners(radius:));

/// A configuration with independent radii for each corner.
/// - Parameters:
///   - topLeftRadius: Radius of top left corner.
///   - topRightRadius: Radius of top right corner.
///   - bottomLeftRadius: Radius of bottom left corner.
///   - bottomRightRadius: Radius of bottom right corner.
+ (NSViewCornerConfiguration *)configurationWithTopLeftRadius:(nullable NSViewCornerRadius *)topLeftRadius
                                               topRightRadius:(nullable NSViewCornerRadius *)topRightRadius
                                             bottomLeftRadius:(nullable NSViewCornerRadius *)bottomLeftRadius
                                            bottomRightRadius:(nullable NSViewCornerRadius *)bottomRightRadius
NS_SWIFT_NAME(corners(topLeftRadius:topRightRadius:bottomLeftRadius:bottomRightRadius:));

/// A configuration where the container is to take on a capsule shape, scaling with the view’s size.
@property (class, copy, readonly) NSViewCornerConfiguration *capsuleCornerConfiguration NS_SWIFT_NAME(capsule);

/// A configuration where the container is to take on a capsule shape, scaling with the view’s size.
/// and clamped to the `maximumRadius`.
/// - Parameters maximumRadius: Maximum radius for the capsule.
+ (NSViewCornerConfiguration *)capsuleCornerConfigurationWithMaximumRadius:(CGFloat)maximumRadius NS_SWIFT_NAME(capsule(maximumRadius:));

/// A configuration that applies the given radius uniformly to all corners, using the largest of the resolved corner radii when they differ.
/// - Parameters radius: Radius for all corners.
+ (NSViewCornerConfiguration *)configurationWithUniformRadius:(NSViewCornerRadius *)radius NS_SWIFT_NAME(uniformCorners(radius:));

/// A configuration that applies the given uniform radius uniformly to all corners that are otherwise unspecified. Any specified corner is independent of the others.
/// - Parameters:
///   - radius: Uniform radius for all unspecified corners.
///   - topLeftRadius: Radius of top left corner.
///   - topRightRadius: Radius of top right corner.
///   - bottomLeftRadius: Radius of bottom left corner.
///   - bottomRightRadius: Radius of bottom right corner.
+ (NSViewCornerConfiguration *)configurationWithUniformRadius:(NSViewCornerRadius *)radius
                                                topLeftRadius:(nullable NSViewCornerRadius *)topLeftRadius
                                               topRightRadius:(nullable NSViewCornerRadius *)topRightRadius
                                             bottomLeftRadius:(nullable NSViewCornerRadius *)bottomLeftRadius
                                            bottomRightRadius:(nullable NSViewCornerRadius *)bottomRightRadius
NS_SWIFT_NAME(uniformCorners(radius:topLeftRadius:topRightRadius:bottomLeftRadius:bottomRightRadius:));

/// A configuration that applies the `topRadius` uniformly to the top-left and top-right corners, and the `bottomRadius` uniformly to the
/// bottom-left and bottom-right corners. When the uniform corners differ, it uses the largest of the resolved corner radii.
/// - Parameters:
///   - topRadius: Radius for top edge.
///   - bottomRadius: Radius for the bottom edge.
+ (NSViewCornerConfiguration *)configurationWithUniformTopRadius:(NSViewCornerRadius *)topRadius
                                                    bottomRadius:(NSViewCornerRadius *)bottomRadius
NS_SWIFT_NAME(uniformEdges(topRadius:bottomRadius:));

/// A configuration that applies the `leftRadius` uniformly to the top-left and bottom-left corners, and the `rightRadius` uniformly to the top-right
/// and bottom-right corners. When the uniform corners differ, it uses the largest of the resolved corner radii.
/// - Parameters:
///   - leftRadius: Radius for left edge.
///   - rightRadius: Radius for the right edge.
+ (NSViewCornerConfiguration *)configurationWithUniformLeftRadius:(NSViewCornerRadius *)leftRadius
                                                      rightRadius:(NSViewCornerRadius *)rightRadius
NS_SWIFT_NAME(uniformEdges(leftRadius:rightRadius:));


/// A configuration that applies the `topRadius` uniformly to the top-left
/// and top-right corners, with optional independent radii for the bottom-left
/// and bottom-right corners. When the uniform corners differ, it uses the largest of the resolved corner radii.
/// - Parameters:
///   - topRadius: Radius for top edge.
///   - bottomLeftRadius: Radius for the bottom left corner.
///   - bottomRightRadius: Radius for the bottom right corner.
+ (NSViewCornerConfiguration *)configurationWithUniformTopRadius:(NSViewCornerRadius *)topRadius
                                                bottomLeftRadius:(nullable NSViewCornerRadius *)bottomLeftRadius
                                               bottomRightRadius:(nullable NSViewCornerRadius *)bottomRightRadius
NS_SWIFT_NAME(uniformTopRadius(_:bottomLeftRadius:bottomRightRadius:));

/// A configuration that applies the `bottomRadius` uniformly to the bottom-left
/// and bottom-right corners, with optional independent radii for the top-left
/// and top-right corners. When the uniform corners differ, it uses the largest of the resolved corner radii.
/// - Parameters:
///   - bottomRadius: Radius for bottom edge.
///   - topLeftRadius: Radius for the top left corner.
///   - topRightRadius: Radius for the top right corner.
+ (NSViewCornerConfiguration *)configurationWithUniformBottomRadius:(NSViewCornerRadius *)bottomRadius
                                                      topLeftRadius:(nullable NSViewCornerRadius *)topLeftRadius
                                                     topRightRadius:(nullable NSViewCornerRadius *)topRightRadius
NS_SWIFT_NAME(uniformBottomRadius(_:topLeftRadius:topRightRadius:));

/// A configuration that applies the `leftRadius` uniformly to the top-left
/// and bottom-left corners, with optional independent radii for the top-right
/// and bottom-right corners. When the uniform corners differ, it uses the largest of the resolved corner radii.
/// - Parameters:
///   - leftRadius: Radius for left edge.
///   - topRightRadius: Radius for the top right corner.
///   - bottomRightRadius: Radius for the bottom right corner.
+ (NSViewCornerConfiguration *)configurationWithUniformLeftRadius:(NSViewCornerRadius *)leftRadius
                                                   topRightRadius:(nullable NSViewCornerRadius *)topRightRadius
                                                bottomRightRadius:(nullable NSViewCornerRadius *)bottomRightRadius
NS_SWIFT_NAME(uniformLeftRadius(_:topRightRadius:bottomRightRadius:));

/// A configuration that applies the `rightRadius` uniformly to the top-right
/// and bottom-right corners, with optional independent radii for the top-left
/// and bottom-left corners. When the uniform corners differ, it uses the largest of the resolved corner radii.
/// - Parameters:
///   - rightRadius: Radius for right edge.
///   - topLeftRadius: Radius for the top left corner.
///   - bottomLeftRadius: Radius for the bottom left corner.
+ (NSViewCornerConfiguration *)configurationWithUniformRightRadius:(NSViewCornerRadius *)rightRadius
                                                     topLeftRadius:(nullable NSViewCornerRadius *)topLeftRadius
                                                  bottomLeftRadius:(nullable NSViewCornerRadius *)bottomLeftRadius
NS_SWIFT_NAME(uniformRightRadius(_:topLeftRadius:bottomLeftRadius:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
