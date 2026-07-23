#if (defined(USE_APPKIT_PUBLIC_HEADERS) && USE_APPKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextTable.h>)
#import <TargetConditionals.h>

#if !TARGET_OS_IPHONE
//
//  NSTextTable.h
//  Text Kit
//
//  Copyright (c) 2004-2025, Apple Inc. All rights reserved.
//

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSText.h>
#import <CoreFoundation/CFCGTypes.h>
#import <Foundation/NSGeometry.h>

@class NSTextTable;
@class NSLayoutManager;
@class NSTextContainer;
@class NSColor;

@class NSView;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* Values for NSTextBlockValueType */
typedef NS_ENUM(NSInteger, NSTextBlockValueType) {
    NSTextBlockValueTypeAbsolute = 0,    // Absolute value in points
    NSTextBlockValueTypePercentage = 1, // Percentage value (out of 100)
    
// Deprecated
    NSTextBlockAbsoluteValueType NS_SWIFT_NAME(absoluteValueType) API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockValueTypeAbsolute", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockValueTypeAbsolute,    // Absolute value in points

    NSTextBlockPercentageValueType NS_SWIFT_NAME(percentageValueType)  API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockValueTypePercentage", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos)  = NSTextBlockValueTypePercentage     // Percentage value (out of 100)
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.ValueType);

/* Values for NSTextBlockDimension */
typedef NS_ENUM(NSInteger, NSTextBlockDimension) {
    NSTextBlockDimensionWidth = 0,
    NSTextBlockDimensionMinimumWidth = 1,
    NSTextBlockDimensionMaximumWidth = 2,
    NSTextBlockDimensionHeight = 4,
    NSTextBlockDimensionMinimumHeight = 5,
    NSTextBlockDimensionMaximumHeight = 6,
    
    
#if !TARGET_OS_IPHONE && !__swift__
// Deprecated
    NSTextBlockWidth API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockDimensionWidth", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockDimensionWidth,

    NSTextBlockMinimumWidth API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockDimensionMinimumWidth", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockDimensionMinimumWidth,

    NSTextBlockMaximumWidth API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockDimensionMaximumWidth", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockDimensionMaximumWidth,

    NSTextBlockHeight API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockDimensionHeight", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockDimensionHeight,

    NSTextBlockMinimumHeight API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockDimensionMinimumHeight", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockDimensionMinimumHeight,

    NSTextBlockMaximumHeight API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockDimensionMaximumHeight", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockDimensionMaximumHeight
#endif // !TARGET_OS_IPHONE && !__swift__
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.Dimension);

/* Values for NSTextBlockLayer */
typedef NS_ENUM(NSInteger, NSTextBlockLayer) {
    NSTextBlockLayerPadding = -1,
    NSTextBlockLayerBorder  =  0,
    NSTextBlockLayerMargin  =  1,
    
#if !TARGET_OS_IPHONE && !__swift__
// Deprecated
    NSTextBlockPadding API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockLayerPadding", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos)  = NSTextBlockLayerPadding,
    NSTextBlockBorder API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockLayerBorder", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) =  NSTextBlockLayerBorder,
    NSTextBlockMargin API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockLayerMargin", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) =  NSTextBlockLayerMargin
#endif // !TARGET_OS_IPHONE && !__swift__
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.Layer);

/* Values for NSTextBlockVerticalAlignment */
typedef NS_ENUM(NSInteger, NSTextBlockVerticalAlignment) {
    NSTextBlockVerticalAlignmentTop = 0,
    NSTextBlockVerticalAlignmentMiddle = 1,
    NSTextBlockVerticalAlignmentBottom = 2,
    NSTextBlockVerticalAlignmentBaseline = 3,

// Deprecated
    NSTextBlockTopAlignment NS_SWIFT_NAME(topAlignment) API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockVerticalAlignmentTop", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockVerticalAlignmentTop,

    NSTextBlockMiddleAlignment NS_SWIFT_NAME(middleAlignment) API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockVerticalAlignmentMiddle", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockVerticalAlignmentMiddle,

    NSTextBlockBottomAlignment NS_SWIFT_NAME(bottomAlignment) API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockVerticalAlignmentBottom", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockVerticalAlignmentBottom,

    NSTextBlockBaselineAlignment NS_SWIFT_NAME(baselineAlignment) API_DEPRECATED_WITH_REPLACEMENT("NSTextBlockVerticalAlignmentBaseline", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextBlockVerticalAlignmentBaseline
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0)) NS_SWIFT_NAME(NSTextBlock.VerticalAlignment);

/* Values for NSTextTableLayoutAlgorithm */
typedef NS_ENUM(NSInteger, NSTextTableLayoutAlgorithm) {
    NSTextTableLayoutAlgorithmAutomatic = 0,
    NSTextTableLayoutAlgorithmFixed = 1,
    
// Deprecated
    NSTextTableAutomaticLayoutAlgorithm NS_SWIFT_NAME(automaticLayoutAlgorithm) API_DEPRECATED_WITH_REPLACEMENT("NSTextTableLayoutAlgorithmAutomatic", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextTableLayoutAlgorithmAutomatic,

    NSTextTableFixedLayoutAlgorithm NS_SWIFT_NAME(fixedLayoutAlgorithm) API_DEPRECATED_WITH_REPLACEMENT("NSTextTableLayoutAlgorithmFixed", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos) = NSTextTableLayoutAlgorithmFixed
} API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))  NS_SWIFT_NAME(NSTextTable.LayoutAlgorithm);

/// An object that defines the size, spacing, and appearance of a block of text in an attributed string.
APPKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))
@interface NSTextBlock : NSObject <NSSecureCoding, NSCopying>
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* Content size */
- (void)setValue:(CGFloat)value type:(NSTextBlockValueType)type forDimension:(NSTextBlockDimension)dimension;
- (CGFloat)valueForDimension:(NSTextBlockDimension)dimension;
- (NSTextBlockValueType)valueTypeForDimension:(NSTextBlockDimension)dimension;

/* Convenience methods for content width in particular, using the above methods with dimension == NSTextBlockWidth */
- (void)setContentWidth:(CGFloat)contentWidth type:(NSTextBlockValueType)type;
@property (readonly) CGFloat contentWidth;
@property (readonly) NSTextBlockValueType contentWidthValueType;

/* Margin, border, and padding */
- (void)setWidth:(CGFloat)width type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer;     // Convenience method sets all edges at once
- (void)setWidth:(CGFloat)width type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (CGFloat)widthForLayer:(NSTextBlockLayer)layer rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (NSTextBlockValueType)widthValueTypeForLayer:(NSTextBlockLayer)layer rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (CGFloat)widthForLayer:(NSTextBlockLayer)layer edge:(NSRectEdge)edge API_DEPRECATED_WITH_REPLACEMENT("-widthForLayer:rectEdge:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos);
- (void)setWidth:(CGFloat)val type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer edge:(NSRectEdge)edge API_DEPRECATED_WITH_REPLACEMENT("-setWidth:type:forLayer:rectEdge:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos);
- (NSTextBlockValueType)widthValueTypeForLayer:(NSTextBlockLayer)layer edge:(NSRectEdge)edge API_DEPRECATED_WITH_REPLACEMENT("-widthValueTypeForLayer:rectEdge:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/* Alignment */
@property NSTextBlockVerticalAlignment verticalAlignment;

/* Colors */
@property (nullable, copy) NSColor *backgroundColor;
- (void)setBorderColor:(nullable NSColor *)color;        // Convenience method sets all edges at once
- (void)setBorderColor:(nullable NSColor *)borderColor rectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (nullable NSColor *)borderColorForRectEdge:(CGRectEdge)rectEdge API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0), watchos(27.0));
- (void)setBorderColor:(nullable NSColor *)color forEdge:(NSRectEdge)edge API_DEPRECATED_WITH_REPLACEMENT("-setBorderColor:rectEdge:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos);
- (nullable NSColor *)borderColorForEdge:(NSRectEdge)edge API_DEPRECATED_WITH_REPLACEMENT("-borderColorForRectEdge:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/* These methods will be called during layout to determine the size and position of the block.  The first will be called before the block is laid out to determine the rect within which glyphs should be laid.  The second will be called after the block is laid out to determine the rect the block occupies with borders and margins. */
- (NSRect)rectForLayoutAtPoint:(NSPoint)startingPoint inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;
- (NSRect)boundsRectForContentRect:(NSRect)contentRect inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;

/* This method will be called during drawing to draw any colors and other decorations before the text is drawn. */
- (void)drawBackgroundWithFrame:(NSRect)frameRect inView:(nullable NSView *)controlView characterRange:(NSRange)charRange layoutManager:(NSLayoutManager *)layoutManager;
@end

/// An object that represents a single cell in a text table.
APPKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))
@interface NSTextTableBlock : NSTextBlock
- (instancetype)initWithTable:(NSTextTable *)table startingRow:(NSInteger)row rowSpan:(NSInteger)rowSpan startingColumn:(NSInteger)column columnSpan:(NSInteger)columnSpan NS_DESIGNATED_INITIALIZER;     // Designated initializer
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* These methods determine the block's role in its enclosing table. */
@property (readonly, strong) NSTextTable * table;
@property (readonly) NSInteger startingRow;
@property (readonly) NSInteger rowSpan;
@property (readonly) NSInteger startingColumn;
@property (readonly) NSInteger columnSpan;

@end

/// An object that represents a table of rows and columns in an attributed string.
APPKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0))
@interface NSTextTable : NSTextBlock
/* These methods control the basic parameters of the table. */
@property NSInteger numberOfColumns;
@property NSTextTableLayoutAlgorithm layoutAlgorithm;
@property BOOL collapsesBorders;
@property BOOL hidesEmptyCells;
/* An NSTextTableBlock delegates its layout and drawing operations to its enclosing table, using the following NSTextTable methods. */
- (NSRect)rectForBlock:(NSTextTableBlock *)block layoutAtPoint:(NSPoint)startingPoint inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;
- (NSRect)boundsRectForBlock:(NSTextTableBlock *)block contentRect:(NSRect)contentRect inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;
- (void)drawBackgroundForBlock:(NSTextTableBlock *)block withFrame:(NSRect)frameRect inView:(NSView *)controlView characterRange:(NSRange)charRange layoutManager:(NSLayoutManager *)layoutManager;
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#endif // !TARGET_OS_IPHONE
#else
#import <UIFoundation/NSTextTable.h>
#endif
