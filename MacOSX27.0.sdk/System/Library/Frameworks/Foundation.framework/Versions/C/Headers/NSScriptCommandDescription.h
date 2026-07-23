/*
	NSScriptCommandDescription.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSDictionary, NSScriptCommand, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A script command that a macOS app supports.
///
/// A scriptable application provides scriptability information that describes the commands and objects scripters can use in scripts that target the application. An application's scripting information is collected automatically by an instance of ``NSScriptSuiteRegistry``, which creates an `NSScriptCommandDescription` for each command it finds, caches these objects in memory, and installs a command handler for each command.
///
/// A script command instance stores the name, class, argument types, and return type of a command. For example, commands in AppleScript's Core suite include `clone`, `count`, `create`, `delete`, `exists`, and `move`.
///
/// The public methods of `NSScriptCommandDescription` are used primarily by Cocoa's built-in scripting support in responding to Apple events that target the application. Although you can subclass the `NSScriptCommandDescription` class, it is unlikely that you would need to do so, or to create instances of it.
@interface NSScriptCommandDescription : NSObject<NSCoding> {
    @private
    NSString *_suiteName;
    NSString *_plistCommandName;
    FourCharCode _classAppleEventCode;
    FourCharCode _idAppleEventCode;
    NSString *_objcClassName;
    NSObject *_resultTypeNameOrDescription;
    FourCharCode _plistResultTypeAppleEventCode;
    id _moreVars;
}

- (id)init NS_UNAVAILABLE;

/// Initializes and returns a newly allocated instance of `NSScriptCommandDescription`.
///
/// This method registers `self` with the application's global instance of ``NSScriptSuiteRegistry`` and also registers all command arguments with the registry.
///
/// - Parameters:
///   - suiteName: The name of the suite (in the application's scriptability information) that the command belongs to. For example, `"AppName Suite"`.
///   - commandName: The name of the script command that this instance describes.
///   - commandDeclaration: A command declaration dictionary of the sort that is valid in script suite property list files. This dictionary provides information about the command such as its argument names and types and return type (if any).
/// - Returns: The initialized command description instance. Returns `nil` if the event constant or class name for the command description is missing; also returns `nil` if the return type or argument values are of the wrong type.
- (nullable instancetype)initWithSuiteName:(NSString *)suiteName commandName:(NSString *)commandName dictionary:(nullable NSDictionary *)commandDeclaration NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

/// The name of the suite that contains the command described by the receiver.
///
/// Within an application's scriptability information, named suites contain related sets of information.
@property (readonly, copy) NSString *suiteName;

/// The name of the command.
///
/// The command name as it appears in the application's scriptability information; may be different from what is displayed to the scripter.
@property (readonly, copy) NSString *commandName;

/// The four-character code for the Apple event class of the receiver's command.
///
/// In an Apple event that specifies a script command, two four character codes -- the event class and event ID -- together identify the command. You use this property to obtain the event class. You use ``NSScriptCommandDescription/appleEventCode`` to obtain the event ID.
///
/// For example, commands in AppleScript's Core suite, such as `clone`, `count`, and `create`, have an event class code of `'core'`. This code and the event ID code returned by ``appleEventCode`` together specify the necessary information for identifying and dispatching an Apple event.
@property (readonly) FourCharCode appleEventClassCode;

/// The four-character code for the Apple event ID of the receiver's command.
///
/// This value, together with the event class code returned by ``NSScriptCommandDescription/appleEventClassCode``, specifies the necessary information for identifying and dispatching an Apple event.
@property (readonly) FourCharCode appleEventCode;

/// The name of the class that will be instantiated to handle the command.
///
/// The Objective-C class name (for example, `"NSGetCommand"`). This is always ``NSScriptCommand`` or a subclass.
@property (readonly, copy) NSString *commandClassName;

/// The return type of the command.
///
/// The receiver's command return type (for example, `"NSNumber"` or `"NSDictionary"`), or `nil` if the described command is not declared to return a result.
@property (nullable, readonly, copy) NSString *returnType;

/// The Apple event code that identifies the command's return type.
@property (readonly) FourCharCode appleEventCodeForReturnType;

/// The names (or keys) for all arguments of the receiver's command.
///
/// If there are no arguments for the command, returns an empty array.
@property (readonly, copy) NSArray<NSString *> *argumentNames;

/// Returns the type of the command argument identified by the specified key.
///
/// - Parameter argumentName: Argument name (used as a key) that identifies the command argument to examine.
/// - Returns: The type of the specified command argument. Returns `nil` if there is no such argument.
- (nullable NSString *)typeForArgumentWithName:(NSString *)argumentName;

/// Returns the Apple event code for the specified command argument of the receiver.
///
/// - Parameter argumentName: The argument name (used as a key) for which to obtain the corresponding Apple event code.
/// - Returns: The code for the specified argument.
- (FourCharCode)appleEventCodeForArgumentWithName:(NSString *)argumentName;

/// Returns a Boolean value that indicates whether the command argument identified by the specified argument key is an optional argument.
///
/// - Parameter argumentName: Argument name (used as a key) that identifies the command argument to examine.
/// - Returns: `true` if the specified argument exists and is optional; otherwise, `false`.
- (BOOL)isOptionalArgumentWithName:(NSString *)argumentName;

/// Creates and returns an instance of the command object described by the receiver.
///
/// - Returns: The command object, instantiated from ``NSScriptCommand`` or a subclass.
- (NSScriptCommand *)createCommandInstance;
/// Creates and returns an instance of the command object described by the receiver in the specified memory zone.
///
/// - Parameter zone: The memory zone from which to allocate the command.
/// - Returns: The command object, instantiated from ``NSScriptCommand`` or a subclass.
- (NSScriptCommand *)createCommandInstanceWithZone:(nullable NSZone *)zone;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
