//
/*
        NSViewCornerRadii.h
        Application Kit
        Copyright (c) 2026, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

///  Provides a structured way to define custom corner radii for each corner of a view, along with a corner curve.
APPKIT_FINAL API_AVAILABLE(macos(27.0))
@interface NSViewCornerRadii : NSObject <NSCopying>

/// Radius of the top left corner of the view.
@property (readonly) CGFloat topLeft;

/// Radius of the top right corner of the view.
@property (readonly) CGFloat topRight;

/// Radius of the bottom left corner of the view.
@property (readonly) CGFloat bottomLeft;

/// Radius of the bottom right corner of the view.
@property (readonly) CGFloat bottomRight;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
