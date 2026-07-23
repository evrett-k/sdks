//
/*
        NSViewCornerRadius.h
        Application Kit
        Copyright (c) 2026, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Represents a radius used to round a corner. It supports fixed and adaptive configurations.
API_AVAILABLE(macos(27.0))
@interface NSViewCornerRadius : NSObject <NSCopying>

/// Shorthand initializer for a configuration where all four corners are using a fixed corner radius in points.
/// - Parameter radius: Radius for all the corners.
+ (NSViewCornerRadius *)fixedRadius:(CGFloat)radius NS_SWIFT_NAME(fixed(_:));

/// A dynamic corner radius calculated based on the view’s container shape and limited to the provided minimum radius.
/// - Parameter minimumRadius: Corner radius that’s applied when a corner of the view’s container is smaller than the specified radius.
+ (NSViewCornerRadius *)containerConcentricRadiusWithMinimum:(CGFloat)minimumRadius NS_SWIFT_NAME(containerConcentric(_:));

/// A dynamic corner radius calculated based on the view’s container shape.
@property (class, copy, readonly) NSViewCornerRadius *containerConcentricRadius NS_SWIFT_NAME(containerConcentric);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
