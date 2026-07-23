/*
	NSUserScriptTask.h
	Copyright (c) 2012-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSAppleEventDescriptor, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSError, NSFileHandle, NSString, NSURL, NSXPCConnection;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*
    These classes are intended to execute user-supplied scripts, and will execute them outside of the application's sandbox, if any.  (They are *not* intended to execute scripts built into an application; for that, use NSTask, NSAppleScript, or AMWorkflow.)  If the application is sandboxed, then the script must be in the "application scripts" folder, which you can get using +[NSFileManager URLForDirectory:NSApplicationScriptsDirectory ...].  A sandboxed application may read from, but not write to, this folder.

    If you simply need to execute scripts without regard to input or output, use NSUserScriptTask, which can execute any of the specific types.  If you need specific control over the input to or output from the script, use one of the sub-classes, which have more detailed "execute" methods.
*/

/* NSUserScriptTask: An abstract "user script".
*/

/// An object that executes scripts.
///
/// The ``NSUserScriptTask`` class is able to run all the scripts normally run by the one of its subclasses, however it ignores the results. It is intended to execute user-supplied scripts and will execute them outside of the application's sandbox, if any.
///
/// If you need to execute scripts and get the input and output information use the ``NSUserUnixTask``, ``NSUserAppleScriptTask``, and ``NSUserAutomatorTask`` sub classes.
API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserScriptTask : NSObject {
    @protected
    NSURL *_scriptURL;
    NSXPCConnection *_connection;
    BOOL _hasExeced;
    BOOL _hasTerminated;
    NSFileHandle *_stdin;
    NSFileHandle *_stdout;
    NSFileHandle *_stderr;
}

/// Initializes a script task with the given URL for a script file.
///
/// The returned object will be of one of the specific sub-classes (``NSUserUnixTask``, ``NSUserAppleScriptTask``, or ``NSUserAutomatorTask``), or `nil` if the file does not appear to match any of the known types.
///
/// If invoked from a subclass, the result will be that class or `nil`.
///
/// - Parameters:
///   - url: The URL for the script file.
///   - error: On return, an error object if an error occurred, otherwise `nil`.
/// - Returns: An initialized script task, or `nil` if the file does not match a known type.
- (nullable instancetype)initWithURL:(NSURL *)url error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/// The URL of the script file.
@property (readonly, copy) NSURL *scriptURL;

/// Executes the script with no input and ignoring any result.
///
/// This method should be invoked no more than once for a given instance of the class. If the script completed normally, the completion handler's `error` parameter will be `nil`.
///
/// - Parameters:
///   - handler: The completion handler Block that returns the error, or `nil` if no error occurred.
/// Implement this block to retrieve the error of the script executed by `executeWithCompletionHandler:`.
typedef void (NS_SWIFT_SENDABLE ^NSUserScriptTaskCompletionHandler)(NSError * _Nullable error);
- (void)executeWithCompletionHandler:(nullable NSUserScriptTaskCompletionHandler)handler;

@end


/// An object that executes unix applications.
///
/// The ``NSUserUnixTask`` class is intended to run unix applications, typically a shell script, from your application. It is intended to execute user-supplied scripts, and will execute them outside of the application's sandbox, if any.
///
/// The class is not intended to execute scripts built into an application; for that, use one of the ``Process``, ``NSAppleScript``, or <doc://com.apple.documentation/documentation/automator/amworkflow> classes.  If the application is sandboxed, then the script must be in the ``FileManager/SearchPathDirectory/applicationScriptsDirectory`` folder.  A sandboxed application may read from, but not write to, this folder.
///
/// If you simply need to execute unix scripts without regard to input or output, use ``NSUserScriptTask``, which can execute any of the specific types.  If you need specific control over the input to, or output from, or the error stream of the script, use this class.
API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserUnixTask : NSUserScriptTask

/// The standard input stream.
///
/// Setting to `nil` will bind the stream to `/dev/null`. The default is `nil`.
@property (nullable, retain) NSFileHandle *standardInput;

/// The standard output stream.
///
/// Setting to `nil` will bind the stream to `/dev/null`. The default is `nil`.
@property (nullable, retain) NSFileHandle *standardOutput;

/// The standard error stream.
///
/// Setting to `nil` will bind the stream to `/dev/null`. The default is `nil`.
@property (nullable, retain) NSFileHandle *standardError;

/// Executes the unix script with the specified arguments.
///
/// This method should be invoked no more than once for a given instance of the class. If the script completed normally, the completion handler's `error` parameter will be `nil`.
///
/// - Parameters:
///   - arguments: An array of `NSString` objects containing the script arguments. The arguments do not undergo shell expansion, so you do not need to do special quoting, and shell variables are not resolved.
///   - handler: The completion handler Block that returns the error, or `nil` if no error occurred.
/// Implement this block to retrieve an error from the Unix script executed by `executeWithArguments:completionHandler:`.
typedef void (NS_SWIFT_SENDABLE ^NSUserUnixTaskCompletionHandler)(NSError *_Nullable error);
- (void)executeWithArguments:(nullable NSArray<NSString *> *)arguments completionHandler:(nullable NSUserUnixTaskCompletionHandler)handler;

@end


/// An object that executes AppleScript scripts.
///
/// The ``NSUserAppleScriptTask`` class is intended to run AppleScript scripts from your application. It is intended to execute user-supplied scripts and will execute them outside of the application's sandbox, if any.
///
/// The class is not intended to execute scripts built into an application; for that, use one of the ``Process`` classes. If the application is sandboxed, then the script must be in the ``FileManager/SearchPathDirectory/applicationScriptsDirectory`` folder. A sandboxed application may read from, but not write to, this folder.
///
/// If you simply need to execute scripts without regard to input or output, use ``NSUserScriptTask``, which can execute any of the specific types. If you need specific control over the input to or output from the script, use this class.
API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserAppleScriptTask : NSUserScriptTask {
    @private
    BOOL _isParentDefaultTarget;
}

/// Executes the AppleScript script by sending it the given Apple event.
///
/// Pass `nil` as `event` to execute the script's default "run" handler. This method should be invoked no more than once for a given instance of the class. If the script completed normally, the completion handler's `error` parameter will be `nil`.
///
/// - Parameters:
///   - event: The Apple event to send to the script. Pass `nil` to execute the script's default "run" handler.
///   - handler: The completion handler Block that returns the result or an error.
/// Implement this block to retrieve the result of the AppleScript executed by `executeWithAppleEvent:completionHandler:`.
typedef void (NS_SWIFT_SENDABLE ^NSUserAppleScriptTaskCompletionHandler)(NSAppleEventDescriptor * _Nullable result, NSError * _Nullable error);
- (void)executeWithAppleEvent:(nullable NSAppleEventDescriptor *)event completionHandler:(nullable NSUserAppleScriptTaskCompletionHandler)handler;

@end


/// An object that executes Automator workflows.
///
/// The ``NSUserAutomatorTask`` class is intended to run Automator workflows from your application. It is intended to execute user-supplied workflows, and will execute them outside of the application's sandbox, if any.
///
/// The class is not intended to execute scripts built into an application; for that, use one of the ``Process`` or <doc://com.apple.documentation/documentation/automator/amworkflow> classes.  If the application is sandboxed, then the script must be in the ``FileManager/SearchPathDirectory/applicationScriptsDirectory`` folder.  A sandboxed application may read from, but not write to, this folder.
///
/// If you simply need to execute scripts without regard to input or output, use ``NSUserScriptTask``, which can execute any of the specific types.  If you need specific control over the input to or output from the workflow, use this class.
API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSUserAutomatorTask : NSUserScriptTask {
    @private
    NSDictionary *_variables;
}

/// The variables required by the Automator workflow.
@property (nullable, copy) NSDictionary<NSString *, id> *variables;

/// Executes the Automator workflow, passing it the given input.
///
/// The Automator workflow will execute using the ``variables`` property values. This method should be invoked no more than once for a given instance of the class. If the script completed normally, the completion handler's `error` parameter will be `nil`.
///
/// - Parameters:
///   - input: The input to pass to the Automator workflow.
///   - handler: The completion handler Block that returns the result or an error.
/// Implement this block to retrieve the output of the Automator workflow executed by `executeWithInput:completionHandler:`.
typedef void (NS_SWIFT_SENDABLE ^NSUserAutomatorTaskCompletionHandler)(id _Nullable result, NSError * _Nullable error);
- (void)executeWithInput:(nullable id <NSSecureCoding>)input completionHandler:(nullable NSUserAutomatorTaskCompletionHandler)handler;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
