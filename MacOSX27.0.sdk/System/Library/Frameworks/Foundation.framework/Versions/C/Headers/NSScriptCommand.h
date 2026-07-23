/*
	NSScriptCommand.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSAppleEventDescriptor, NSDictionary<KeyType, ObjectType>, NSMutableDictionary, NSScriptObjectSpecifier, NSScriptCommandDescription, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Error codes for general command execution problems.
///
/// Subclasses may define their own values.
NS_ENUM(NSInteger) {
    /// No error encountered.
    NSNoScriptError = 0,
    /// A problem occurred evaluating the receiver specifier.
    NSReceiverEvaluationScriptError,
    /// The object or objects specified by a key could not be found.
    NSKeySpecifierEvaluationScriptError,
    /// A problem occurred evaluating an argument specifier.
    NSArgumentEvaluationScriptError,
    /// The receivers don't support the command.
    NSReceiversCantHandleCommandScriptError,
    /// One or more required arguments are missing.
    NSRequiredArgumentsMissingScriptError,
    /// One or more arguments are of the wrong type or are otherwise invalid.
    NSArgumentsWrongScriptError,
    /// The key is not recognized.
    NSUnknownKeyScriptError,
    /// Other miscellaneous internal error.
    NSInternalScriptError,
    /// The implementation of a scripting command signaled an error.
    NSOperationNotSupportedForKeyScriptError,
    /// The script command could not be created.
    NSCannotCreateScriptCommandError
};

/// A self-contained scripting statement.
///
/// An instance of ``NSScriptCommand`` represents a scripting statement, such as `set word 5 of the front document to word 1 of the second document`, and contains the information needed to perform the operation specified by the statement.
///
/// When an Apple event reaches a Cocoa application, Cocoa's built-in scripting support transforms it into a script command (that is, an instance of `NSScriptCommand` or one of the subclasses provided by Cocoa scripting or by your application) and executes the command in the context of the application. Executing a command means either invoking the selector associated with the command on the object or objects designated to receive the command, or having the command perform its default implementation method (``performDefaultImplementation()``).
///
/// Your application most likely calls methods of `NSScriptCommand` to extract the command arguments. You do this either in the `performDefaultImplementation` method of a command subclass you have created, or in an object method designated as the selector to handle a particular command.
///
/// As part of Cocoa's standard scripting implementation, `NSScriptCommand` and its subclasses can handle the default command set for AppleScript's Standard suite for most applications without any subclassing. The Standard suite includes commands such as `copy`, `count`, `create`, `delete`, `exists`, and `move`, as well as common object classes such as `application`, `document`, and `window`.
///
/// For more information on working with script commands, see [Script Commands](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_script_cmds/SAppsScriptCmds.html#//apple_ref/doc/uid/20001242) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
@interface NSScriptCommand : NSObject <NSCoding> {

    // All instance variables are private.
    @private
    NSScriptCommandDescription *_commandDescription;
    id _directParameter;
    NSScriptObjectSpecifier *_receiversSpecifier;
    id _evaluatedReceivers;
    NSDictionary *_arguments;
    NSMutableDictionary *_evaluatedArguments;
    struct {
        unsigned int hasEvaluatedReceivers:1;
        unsigned int hasEvaluatedArguments:1;
        unsigned int RESERVED:30;
    } _flags;
    id _moreVars;
    void *_reserved;

}

/// Initializes a script command from a command description.
- (instancetype)initWithCommandDescription:(NSScriptCommandDescription *)commandDef NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder;

/// The description of this script command.
@property (readonly, retain) NSScriptCommandDescription *commandDescription;

/// The object that corresponds to the direct parameter of the Apple event from which this command derives.
@property (nullable, retain) id directParameter;

/// The object specifier for the object or objects that will be given a chance to handle the command.
///
/// If the direct parameter of the original event was an object specifier, `setDirectParameter:` sends a `setReceiversSpecifier:` message.
@property (nullable, retain) NSScriptObjectSpecifier *receiversSpecifier;

/// If the direct parameter of the original event was an object specifier, returns the specified object or objects.
///
/// Returns `nil` if the direct parameter was not an object specifier or could not be evaluated.
@property (nullable, readonly, retain) id evaluatedReceivers;

/// The arguments of the command.
@property (nullable, copy) NSDictionary<NSString *, id> *arguments;
/// The arguments of the command, with any object specifiers already evaluated.
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *evaluatedArguments;

/// A Boolean value that indicates whether the command is well-formed according to its command description.
@property (getter=isWellFormed, readonly) BOOL wellFormed;

/// Overridden by subclasses to perform the default action for a command when no receivers explicitly handle it.
///
/// If `suspend` is invoked during the invocation of this method, its return value is ignored by Cocoa Scripting's built-in Apple event handling.
- (nullable id)performDefaultImplementation;

/// Evaluates the receiver specifier and arguments, validates the command, and executes it.
///
/// If the command is valid and there are receivers, the command handler method for the receivers' class is invoked. If the command is valid but there are no receivers, `performDefaultImplementation` is invoked.
- (nullable id)executeCommand;

/// The error number associated with this command, if any.
@property NSInteger scriptErrorNumber;
/// An `NSAppleEventDescriptor` that identifies the offending object when an error occurs.
@property (nullable, retain) NSAppleEventDescriptor *scriptErrorOffendingObjectDescriptor API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// An `NSAppleEventDescriptor` that identifies the expected type when a type mismatch error occurs.
@property (nullable, retain) NSAppleEventDescriptor *scriptErrorExpectedTypeDescriptor API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// The error string associated with this command, if any.
@property (nullable, copy) NSString *scriptErrorString;

/// Returns the currently executing script command, if any.
///
/// If a command is being executed in the current thread by Cocoa Scripting's built-in Apple event handling, return the command. Return `nil` otherwise.
+ (nullable NSScriptCommand *)currentCommand;

/// The Apple event descriptor from which this command was constructed.
///
/// Only available if the receiver was constructed by Cocoa Scripting's built-in Apple event handling.
@property (nullable, readonly, copy) NSAppleEventDescriptor *appleEvent;

/// Suspends execution of this command.
///
/// If the receiver is being executed in the current thread by Cocoa Scripting's built-in Apple event handling, suspend the execution of the command. A matching invocation of `resumeExecutionWithResult:` must be made.
- (void)suspendExecution;

/// Resumes execution of a previously suspended command with a result.
///
/// This method may be invoked in any thread, not just the one in which the corresponding invocation of `suspendExecution` occurred.
- (void)resumeExecutionWithResult:(nullable id)result;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
