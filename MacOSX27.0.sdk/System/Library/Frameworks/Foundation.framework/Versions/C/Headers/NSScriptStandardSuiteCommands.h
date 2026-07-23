/*
	NSScriptStandardSuiteCommands.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSScriptCommand.h>

@class NSDictionary<KeyType, ObjectType>;
@class NSScriptObjectSpecifier;
@class NSScriptClassDescription;
@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that specify whether a document should be saved before being closed.
///
/// The ``NSCloseCommand/saveOptions`` method returns one of these constants to indicate how to deal with saving any modified documents.
typedef NS_ENUM(NSUInteger, NSSaveOptions) {
    /// The document should be saved.
    NSSaveOptionsYes = 0,
    /// The document should not be saved.
    NSSaveOptionsNo,
    /// The user should be asked whether to save the document.
    NSSaveOptionsAsk
};

/// A command that clones one or more scriptable objects.
///
/// An instance of `NSCloneCommand` clones the specified scriptable object or objects (such as words, paragraphs, images, and so on) and inserts them in the specified location, or the default location if no location is specified. The cloned scriptable objects typically correspond to objects in the application, but aren't required to. This command corresponds to AppleScript's `duplicate` command.
///
/// `NSCloneCommand` is part of Cocoa's built-in scripting support. It works automatically to support the `duplicate` command through key-value coding. Most applications don't need to subclass `NSCloneCommand` or invoke its methods.
///
/// When an instance of `NSCloneCommand` is executed, it clones the specified objects by sending them <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/copywithzone:> messages.
@interface NSCloneCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

/// Splits off the inner-most child specifier from the receivers specifier.
- (void)setReceiversSpecifier:(nullable NSScriptObjectSpecifier *)receiversRef;

/// The key specifier for the clone operation.
@property (readonly, retain) NSScriptObjectSpecifier *keySpecifier;

@end


/// A command that closes one or more scriptable objects.
///
/// An instance of `NSCloseCommand` closes the specified scriptable object or objects—typically a document or window (and its associated document, if any). The command may optionally specify a location to save in and how to handle modified documents (by automatically saving changes, not saving them, or asking the user).
///
/// `NSCloseCommand` is part of Cocoa's built-in scripting support. It works automatically to support the `close` command through key-value coding. Most applications don't need to subclass `NSCloseCommand` or call its methods.
@interface NSCloseCommand : NSScriptCommand {}

/// The save options specified by the command.
@property (readonly) NSSaveOptions saveOptions;

@end


/// A command that counts the number of objects of a specified class in the specified object container.
///
/// An instance of `NSCountCommand` counts the number of objects of a specified class in the specified object container (such as the number of words in a paragraph or document) and returns the result.
///
/// `NSCountCommand` is part of Cocoa's built-in scripting support. It works automatically to support the `count` command through key-value coding. Most applications don't need to subclass `NSCountCommand` or call its methods.
///
/// ## See Also
///
/// - [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164)
@interface NSCountCommand : NSScriptCommand {}

@end


/// A command that creates a scriptable object.
///
/// An instance of `NSCreateCommand` creates the specified scriptable object (such as a document), optionally supplying the new object with the specified attributes. This command corresponds to AppleScript's `make` command.
///
/// `NSCreateCommand` is part of Cocoa's built-in scripting support. Most applications don't need to subclass `NSCreateCommand` or invoke its methods.
///
/// When an instance of `NSCreateCommand` is executed, it creates a new object using `[[theClassToBeCreated allocWithZone:NULL] init]` (where `theClassToBeCreated` is the class of the object to be created), unless the command has a `with data` argument. In the latter case, the new object is created by invoking `[[NSScriptCoercionHandler sharedCoercionHandler] coerceValue:theDataAsAnObject toClass:theClassToBeCreated]`.  Any properties specified by a `with properties` argument are then set in the new object using `-setScriptingProperties:`.
///
/// If an `NSCreateCommand` object with no argument corresponding to the `at` parameter is executed (for example, `tell application "Mail" to make new mailbox with properties {name:"testFolder"}`), and the receiver of the command (not necessarily the application object) has a to-many relationship to objects of the class to be instantiated, and the class description for the receiving class returns <doc://com.apple.documentation/documentation/swift/false> when sent an `isLocationRequiredToCreateForKey:` message, the `NSCreateCommand` object creates a new object and sends the receiver an <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/insertvalue(_:at:inpropertywithkey:)> message to place the new object in the container. This is part of Cocoa's scripting support for inserting newly-created objects into containers without explicitly specifying a location.
@interface NSCreateCommand : NSScriptCommand {
    @private
    id _moreVars2;
}

/// The class description for the class that is to be created.
@property (readonly, retain) NSScriptClassDescription *createClassDescription;

/// The key dictionary with Apple event codes resolved to actual key names.
@property (readonly, copy) NSDictionary<NSString *, id> *resolvedKeyDictionary;

@end


/// A command that deletes a scriptable object.
///
/// An instance of `NSDeleteCommand` deletes the specified scriptable object or objects (such as words, paragraphs, and so on).
///
/// Suppose, for example, a user executes a script that sends the command `delete the third rectangle in the first document` to the Sketch sample application (located in `/Developer/Examples/AppKit`). Cocoa creates an `NSDeleteCommand` object to perform the operation. When the command is executed, it uses the key-value coding mechanism (by invoking `removeValueAtIndex:fromPropertyWithKey:`) to remove the specified object or objects from their container. See the description for <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/removevalue(at:frompropertywithkey:)> for related information.
///
/// `NSDeleteCommand` is part of Cocoa's built-in scripting support. Most applications don't need to subclass `NSDeleteCommand` or call its methods.
@interface NSDeleteCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

/// Splits off the inner-most child specifier from the receivers specifier.
- (void)setReceiversSpecifier:(nullable NSScriptObjectSpecifier *)receiversRef;

/// The key specifier for the delete operation.
@property (readonly, retain) NSScriptObjectSpecifier *keySpecifier;

@end


/// A command that determines whether a scriptable object exists.
///
/// An instance of `NSExistsCommand` determines whether a specified scriptable object, such as a word, paragraph, or image, exists.
///
/// When an instance of `NSExistsCommand` is executed, it evaluates the receiver specifier for the command to determine if it specifies any objects.
///
/// `NSExistsCommand` is part of Cocoa's built-in scripting support. Most applications don't need to subclass `NSExistsCommand`.
///
/// ## See Also
///
/// - [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164)
@interface NSExistsCommand : NSScriptCommand {}

@end


/// A command that retrieves a value or object from a scriptable object.
///
/// An instance of `NSGetCommand` gets the specified value or object from the specified scriptable object: for example, the words from a paragraph or the name of a document.
///
/// When an instance of `NSGetCommand` is executed, it evaluates the specified receivers, gathers the specified data, if any, and packages it in a return Apple event.
///
/// `NSGetCommand` is part of Cocoa's built-in scripting support. It works automatically to support the `get` command through key-value coding. Most applications don't need to subclass `NSGetCommand` or call its methods.
///
/// For information on working with `get` commands, see [Getting and Setting Properties and Elements](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_get_set/SAppsGetSet.html#//apple_ref/doc/uid/TP40002164-CH18) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
///
/// ## See Also
///
/// - [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164)
@interface NSGetCommand : NSScriptCommand {}

@end


/// A command that moves one or more scriptable objects.
///
/// An instance of `NSMoveCommand` moves the specified scriptable object or objects; for example, it may move words to a new location in a document or a file to a new directory.
///
/// `NSMoveCommand` is part of Cocoa's built-in scripting support. It works automatically to support the `move` AppleScript command through key-value coding. Most applications don't need to subclass `NSMoveCommand` or invoke its methods. However, for circumstances where you might choose to subclass this command, see "Modifying a Standard Command" in [Script Commands](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_script_cmds/SAppsScriptCmds.html#//apple_ref/doc/uid/20001242) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
///
/// When an instance of `NSMoveCommand` is executed, it does not make copies of moved objects. It removes objects from the source container or containers, then inserts them into the destination container.
@interface NSMoveCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

/// Splits off the inner-most child specifier from the receivers specifier.
- (void)setReceiversSpecifier:(nullable NSScriptObjectSpecifier *)receiversRef;

/// The key specifier for the move operation.
@property (readonly, retain) NSScriptObjectSpecifier *keySpecifier;

@end


/// A command that quits the specified app.
///
/// The quit command may optionally specify how to handle modified documents (automatically save changes, don't save them, or ask the user). For details, see the description for the `quit` command in "Apple Events Sent By the Mac OS" in [How Cocoa Applications Handle Apple Events](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_handle_AEs/SAppsHandleAEs.html#//apple_ref/doc/uid/20001239) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
///
/// `NSQuitCommand` is part of Cocoa's built-in scripting support. Most applications don't need to subclass `NSQuitCommand` or call its methods.
@interface NSQuitCommand : NSScriptCommand {}

/// The save options specified by the command.
@property (readonly) NSSaveOptions saveOptions;

@end


/// A command that sets one or more attributes or relationships to one or more values.
///
/// An instance of `NSSetCommand` sets one or more attributes or relationships to one or more values; for example, it may set the (x, y) coordinates for a window's position or set the name of a document.
///
/// `NSSetCommand` is part of Cocoa's built-in scripting support. It works automatically to support the `set` command through key-value coding. Most applications don't need to subclass `NSSetCommand` or call its methods.
///
/// `NSSetCommand` uses available scripting class descriptions to determine whether it should set a value for an attribute (or property), or set a value for all elements (to-many objects). For the latter, it invokes <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/replacevalue(at:inpropertywithkey:withvalue:)>; for the former, it invokes <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/setvalue(_:forkey:)> (or, if the receiver overrides <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/takevalue(_:forkey:)>, it invokes that method, to support backward binary compatibility.)
///
/// For information on working with `set` commands, see [Getting and Setting Properties and Elements](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_get_set/SAppsGetSet.html#//apple_ref/doc/uid/TP40002164-CH18) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
@interface NSSetCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

/// Splits off the inner-most child specifier from the receivers specifier.
- (void)setReceiversSpecifier:(nullable NSScriptObjectSpecifier *)receiversRef;

/// The key specifier for the set operation.
@property (readonly, retain) NSScriptObjectSpecifier *keySpecifier;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
