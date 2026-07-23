/*
        NSTextSelectionManager.h
        Application Kit
        Copyright (c) 2026, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKit.h>
#import <AppKit/NSTextSelection.h>
#import <AppKit/NSTextSelectionNavigation.h>

@protocol NSTextSelectionDataSource;
@protocol NSTextLocation;
@class NSTextSelection;

@protocol NSTextSelectionManagerDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST


/// Values for text selection interaction modes.
///
/// These modes determine how the text selection manager handles user interaction with text content.
typedef NS_ENUM (NSInteger, NSTextSelectionMode) {
    /// Text is editable and selectable.
    NSTextSelectionModeEditable,
    /// Text is selectable but not editable.
    NSTextSelectionModeSelectable,
    /// Text is neither selectable nor editable.
    NSTextSelectionModeNonInteractive,
} NS_SWIFT_NAME(NSTextSelectionManager.Mode) API_AVAILABLE(macos(27.0));

/// An object that coordinates text selection behavior for custom text views.
///
/// ``NSTextSelectionManager`` provides a centralized way to manage text selection interactions using a set of gesture recognizers. For keyboard-based selection, integrate ``NSTextSelectionNavigation`` with your view. The selection manager works with a delegate to update and respond to selection changes, and with a data source to query the text layout system.
API_AVAILABLE(macos(27.0))
NS_SWIFT_UI_ACTOR
@interface NSTextSelectionManager : NSObject

/// The interaction mode for text selection.
///
/// Determines whether text is editable, selectable only, or non-interactive. The default value is `NSTextSelectionModeEditable`.
@property NSTextSelectionMode textSelectionMode;

/// The delegate of the text selection manager.
///
/// The delegate is responsible for storing the current text selection and responding to selection-related events.
@property (nullable, weak) id <NSTextSelectionManagerDelegate> delegate;

/// The data source that provides text layout information to the selection manager.
///
/// The data source is typically an `NSTextLayoutManager` or similar text layout object.
@property (nullable, weak) id <NSTextSelectionDataSource> textSelectionDataSource;

/// The gesture recognizers managed by the selection manager.
///
/// Other gesture recognizers in the view hierarchy can declare dependencies on these gestures using `requireGestureRecognizerToFail:` to ensure proper gesture recognition precedence.
@property (readonly) NSArray <NSGestureRecognizer *> *gesturesForFailureRequirements;

@end

/// A set of methods that manage text selection state and let you customize selection behavior.
///
/// Delegates are responsible for managing the text selection state and can customize selection behavior by implementing optional methods.
API_AVAILABLE(macos(27.0)) NS_SWIFT_NAME(NSTextSelectionManager.Delegate)
@protocol NSTextSelectionManagerDelegate <NSObject>
@required
/// The current text selection.
///
/// The text selection manager updates this property in response to user interactions. The delegate is responsible for storing and providing access to the current selection. The ``NSTextLocation`` values that make up the ``NSTextRange`` objects can be any object that can describe a location in your text.
@property (nullable, strong) NSTextSelection *textSelection;

@optional
/// Asks the delegate whether a selection can begin at the specified point.
///
/// Return `YES` to allow a text selection to begin at the specified point, `NO` to prevent it. If the delegate doesn't implement this method, selection is always allowed. The selection manager calls this method when the user initiates a selection gesture at the given point in the coordinate system of the view containing the selection manager.
///
/// - Parameters:
///   - selectionManager: The selection manager requesting permission.
///   - point: The point in the view's coordinate system where the selection gesture began.
/// - Returns: `YES` if selection can begin at the point; otherwise, `NO`.
- (BOOL)selectionManager:(NSTextSelectionManager *)selectionManager shouldBeginSelectionAtPoint:(NSPoint)point;

/// Tells the delegate that a selection gesture is about to begin.
///
/// The selection manager calls this method after ``selectionManager:shouldBeginSelectionAtPoint:`` returns `YES` (or if that method isn't implemented) and before any selection changes are made.
///
/// - Parameter selectionManager: The selection manager that is about to begin selection.
- (void)selectionManagerWillBeginSelection:(NSTextSelectionManager *)selectionManager;

/// Tells the delegate that a selection gesture has ended.
///
/// The selection manager calls this method after finishing processing a selection gesture, such as when the user releases the mouse button.
///
/// - Parameter selectionManager: The selection manager that ended selection.
- (void)selectionManagerDidEndSelection:(NSTextSelectionManager *)selectionManager;

/// Returns the text location of the text container at the specified point.
///
/// Implement this method when your view hosts multiple text containers, such as multi-column or paginated layouts, so the selection manager can identify which container a gesture targets. Also implement ``selectionManager:frameOfTextContainerAtPoint:`` so the selection manager can convert gesture points into the correct container's local coordinates.
///
/// - Parameters:
///   - selectionManager: The selection manager requesting the text location.
///   - point: The point in the view's coordinate system.
/// - Returns: The text location for the text container at the point, or `nil` if no container exists there.
- (nullable id <NSTextLocation>)selectionManager:(NSTextSelectionManager *)selectionManager locationOfTextContainerAtPoint:(NSPoint)point;

/// Returns the frame of the text container at the specified point.
///
/// Implement this method whenever your text container is not positioned at the view's origin (0, 0), or whenever your view hosts multiple text containers. The selection manager uses the returned frame to convert gesture points from view coordinates into container-local coordinates before forwarding them to ``NSTextSelectionDataSource``. Without this method the selection manager assumes the container fills the view starting at the origin, which produces incorrect points for any other layout.
///
/// For multi-container layouts, also implement ``selectionManager:locationOfTextContainerAtPoint:`` so the selection manager can identify which container a gesture targets.
///
/// - Parameters:
///   - selectionManager: The selection manager requesting the frame.
///   - point: The point in the view's coordinate system.
/// - Returns: The frame of the text container at the point, in the view's coordinate system, or `NSZeroRect` if no container exists there.
- (NSRect)selectionManager:(NSTextSelectionManager *)selectionManager frameOfTextContainerAtPoint:(NSPoint)point;

/// Creates and returns a dragging session for the specified gesture recognizer.
///
/// The selection manager calls this method when the user attempts to drag the current text selection. Use this method to customize the dragging behavior, including setting drag data and drag images.
///
/// - Parameters:
///   - selectionManager: The selection manager requesting the dragging session.
///   - gesture: The gesture recognizer that detected the drag attempt.
/// - Returns: A new dragging session, or `nil` to prevent dragging.
- (nullable NSDraggingSession*)selectionManager:(NSTextSelectionManager *)selectionManager makeDraggingSessionWithGesture:(NSGestureRecognizer *)gesture NS_SWIFT_NAME(selectionManager(_:makeDraggingSession:));
@end


@interface NSView (TextSelectionManager)
/// The text selection manager for this view.
///
/// Setting this property installs gesture recognizers and configures the view to handle text selection interactions. Setting it to `nil` removes text selection support. The default value is `nil`.
@property (nullable, strong) NSTextSelectionManager *textSelectionManager API_AVAILABLE(macos(27.0));
@end


API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
