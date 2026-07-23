/*
    NSStatusItem.h
    Application Kit
    Copyright (c) 1997-2024, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSEvent.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

typedef NSString * NSStatusItemAutosaveName NS_SWIFT_BRIDGED_TYPEDEF;

@class NSAttributedString;
@class NSStatusBarButton;
@class NSStatusBar;
@class NSStatusItem;
@class NSStatusItemExpandedInterfaceSession;
@class NSWindow;
@class NSImage;
@class NSMenu;
@class NSView;

API_AVAILABLE(macos(27.0))
@protocol NSStatusItemExpandedInterfaceDelegate <NSObject>
@required

/*  Status items which do not use an NSMenu but instead position other windows ("expanded interface") relative to the item should begin showing their expanded interface upon receipt of this message. This method should be used instead of manually toggling your interface by target/action handling on the button or item. The expanded interface should be closed upon receipt of -statusItemDidEndExpandedInterfaceSession:animated:. This allows the status item to participate in keyboard navigation and menu tracking behaviors. If the expanded interface is closed through other user action, -cancel should be invoked on statusItem.expandedInterfaceSession. Other user action could be the user clicking an action which should dismiss the interface, or the app detecting a click in another window or app (see NSEvent.addGlobalMonitorForEventsMatchingMask:handler: and NSEvent.addLocalMonitorForEventsMatchingMask:handler:).
 */
- (void)statusItem:(NSStatusItem *)statusItem didBeginExpandedInterfaceSession:(NSStatusItemExpandedInterfaceSession *)expandedInterfaceSession;
- (void)statusItemDidEndExpandedInterfaceSession:(NSStatusItem *)statusItem animated:(BOOL)animated;

@end

typedef NS_OPTIONS(NSUInteger, NSStatusItemBehavior) {
    /* Allow the user to remove the item. By default, an item is not removable. To provide consistency with system status items, RemovalAllowed should be set if your application remains usable without the status item. It is the application's responsibility to allow the user to re-add the item. Upon removal, -visible is set to NO. This is observable through KVO.
     */
    NSStatusItemBehaviorRemovalAllowed = (1 << 1),
    
    /* The application terminates when the user removes the item. Implies NSStatusItemBehaviorRemovalAllowed.
     */
    NSStatusItemBehaviorTerminationOnRemoval = (1 << 2),
} API_AVAILABLE(macos(10.12));

@interface NSStatusItem : NSObject

/*  The status bar that the receiver is displayed in.
 */
@property (readonly, weak) NSStatusBar *statusBar;

/*  The amount of space in the status bar that should be allocated to the receiver. \c NSVariableStatusItemLength will adjust the length to the size of the status item's contents and \c NSSquareStatusItemLength will keep the length the same as the status bar's height.
 */
@property CGFloat length;

/*  The drop down menu that is displayed when the status item is pressed or clicked.
 */
@property (nullable, strong) NSMenu *menu;

/*  The button that is displayed in the status bar. This is created automatically on the creation of the StatusItem. Behavior customization for the button, such as image, target/action, tooltip, can be set with this property.
 */
@property (nullable, readonly, strong) NSStatusBarButton *button API_AVAILABLE(macos(10.10));

/*  Specifies the behavior of the status item.
 */
@property (assign) NSStatusItemBehavior behavior API_AVAILABLE(macos(10.12));

/*  Specifies if the status item is currently visible in the status bar, even if it is obscured by the application menu. Defaults to YES. Persisted based on the -autosaveName. This is observable through KVO.
 */
@property (assign, getter=isVisible) BOOL visible API_AVAILABLE(macos(10.12));

/*  Specifies a unique name for persisting visibility information. If none is specified, one is automatically chosen. Apps with multiple status bar items should set an autosave after creation. Setting to nil resets the automatically chosen name and clears saved information.
 */
@property (null_resettable, copy) NSStatusItemAutosaveName autosaveName API_AVAILABLE(macos(10.12));

/*  A delegate which handles the lifecycle of a status item's expanded interface, if any. Status items which assign an NSMenu to their button will not receive these callouts, as the expanded menu interface will be handled automatically. The delegate is responsible for showing any expanded interface such as an NSWindow positioned beneath the item upon receipt of -statusItem:didBeginExpandedInterfaceSession:, and then dismissing that interface when the delegate receives the -statusItemDidEndExpandedInterfaceSession:animated: message.
 */
@property (nullable, weak) id<NSStatusItemExpandedInterfaceDelegate> expandedInterfaceDelegate API_AVAILABLE(macos(27.0));

/*  A session object tracking the lifecycle of a currently showing expanded interface, if any. Will be set to a valid session object before invocation of -statusItem:didBeginExpandedInterfaceSession:, and cleared to nil before invocation of -statusItemDidEndExpandedInterfaceSession:animated: on the expandedInterfaceDelegate.
 */
@property (nullable, readonly, strong) NSStatusItemExpandedInterfaceSession *expandedInterfaceSession API_AVAILABLE(macos(27.0));

/*  An optional view to display in the status bar instead of -button. -button is preferred in most cases as it can alter its appearance automatically.
 */
@property (nullable, strong) NSView *view API_AVAILABLE(macos(10.0));

/*  An optional target/action to be invoked when using a custom view rather than -button. Status items with no -expandedInterfaceDelegate and which use -view will receive this when interacted with.
 */
@property (nullable, weak) id target API_AVAILABLE(macos(10.0));
@property (nullable) SEL action API_AVAILABLE(macos(10.0));

@end


@interface NSStatusItem (NSStatusItemDeprecated)
/* These methods simply forward their calls onto the button property. */
@property (nullable) SEL doubleAction API_DEPRECATED("Use the receiver's button.doubleAction instead", macos(10.0,10.14));
@property (nullable, copy) NSString *title API_DEPRECATED("Use the receiver's button.title instead", macos(10.0,10.14));
@property (nullable, copy) NSAttributedString *attributedTitle API_DEPRECATED("Use the receiver's button.attributedTitle instead", macos(10.0,10.14));
@property (nullable, strong) NSImage *image API_DEPRECATED("Use the receiver's button.image instead", macos(10.0,10.14));
@property (nullable, strong) NSImage *alternateImage API_DEPRECATED("Use the receiver's button.alternateImage instead", macos(10.0,10.14));
@property (getter=isEnabled) BOOL enabled API_DEPRECATED("Use the receiver's button.enabled instead", macos(10.0,10.14));
@property BOOL highlightMode API_DEPRECATED("Use the receiver's button.cell.highlightsBy instead", macos(10.0,10.14));
@property (nullable, copy) NSString *toolTip API_DEPRECATED("Use the receiver's button.toolTip instead", macos(10.0,10.14));

- (NSInteger)sendActionOn:(NSEventMask)mask API_DEPRECATED("Use the receiver's button's -sendActionOn: instead", macos(10.0,10.14));

- (void)drawStatusBarBackgroundInRect:(NSRect)rect withHighlight:(BOOL)highlight API_DEPRECATED("Use the standard button instead which handles highlight drawing, making this method obsolete", macos(10.0,10.14));
- (void)popUpStatusItemMenu:(NSMenu *)menu API_DEPRECATED("Use the menu property instead", macos(10.0,10.14));

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)

