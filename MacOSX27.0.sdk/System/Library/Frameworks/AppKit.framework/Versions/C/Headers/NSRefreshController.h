/*
        NSRefreshController.h
        Application Kit
        Copyright (c) 2026, Apple Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSColor;
@class NSAttributedString;

/// A controller that provides pull-to-refresh functionality for scroll views.
///
/// `NSRefreshController` enables users to trigger refresh operations by pulling down
/// on scrollable content. Add a refresh controller to an `NSScrollView` to provide
/// this functionality. Configure the target and action to handle refresh events.
API_AVAILABLE(macos(27.0))
NS_SWIFT_UI_ACTOR
@interface NSRefreshController : NSObject

/// A Boolean value indicating whether a refresh operation is in progress.
///
/// The default value of this property is `NO`. When the user triggers a refresh,
/// this property automatically becomes `YES`. Call ``endRefreshing`` when your
/// refresh operation completes to reset this property to `NO`.
@property (readonly) BOOL isRefreshing;

/// The tint color for the refresh controller.
///
/// This color is used for the refresh indicator.
@property (nullable, strong) NSColor *tintColor;

/// The styled text to display in the refresh controller.
///
/// Use this property to provide additional context about the refresh operation.
@property (nullable, copy) NSAttributedString *attributedTitle;

/// The target object that receives action messages.
@property (nullable, weak) id target;

/// The action method to call when refresh is triggered.
@property (nullable) SEL action;

/// Tells the refresh controller that a refresh operation has begun.
///
/// Call this method to programmatically start a refresh operation. The refresh controller
/// enters the refreshing state and displays its activity indicator. This is typically used
/// when you want to show a refresh initiated by something other than user interaction.
- (void)beginRefreshing;

/// Tells the refresh controller that a refresh operation has ended.
///
/// Call this method when your refresh operation completes. The refresh controller
/// returns to its default appearance and exits the refreshing state.
- (void)endRefreshing;
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
