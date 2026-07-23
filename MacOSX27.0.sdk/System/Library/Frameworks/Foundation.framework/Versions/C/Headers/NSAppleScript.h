/*
	NSAppleScript.h
	Copyright (c) 2002-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>


@class NSAppleEventDescriptor, NSDictionary<KeyType, ObjectType>, NSString, NSURL;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// If the result of -initWithContentsOfURL:error:, -compileAndReturnError:, -executeAndReturnError:, or -executeAppleEvent:error:, signals failure (nil, NO, nil, or nil, respectively), a pointer to an autoreleased dictionary is put at the location pointed to by the error parameter.  The error info dictionary may contain entries that use any combination of the following keys, including no entries at all.

/// An `NSString` that supplies a detailed description of the error condition.
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorMessage API_AVAILABLE(macos(10.2)) API_UNAVAILABLE(ios, watchos, tvos); // NSString

/// An `NSNumber` that specifies the error number.
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorNumber API_AVAILABLE(macos(10.2)) API_UNAVAILABLE(ios, watchos, tvos); // NSNumber

/// An `NSString` that specifies the name of the application that generated the error.
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorAppName API_AVAILABLE(macos(10.2)) API_UNAVAILABLE(ios, watchos, tvos); // NSString

/// An `NSString` that provides a brief description of the error.
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorBriefMessage API_AVAILABLE(macos(10.2)) API_UNAVAILABLE(ios, watchos, tvos); // NSString

/// An `NSValue` that specifies a range.
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorRange API_AVAILABLE(macos(10.2)) API_UNAVAILABLE(ios, watchos, tvos); // NSValue containing an NSRange

/// An object that provides the ability to load, compile, and execute scripts.
///
/// This class provides applications with the ability to
///
/// - load a script from a URL or from a text string
/// - compile or execute a script or an individual Apple event
/// - obtain an `NSAppleEventDescriptor` containing the reply from an executed script or event
/// - obtain an attributed string for a compiled script, suitable for display in a script editor
/// - obtain various kinds of information about any errors that may occur
///
/// > Important:
/// > `NSAppleScript` provides the ``executeAppleEvent(_:error:)`` method so that you can send an Apple event to invoke a handler in a script. (In an AppleScript script, a handler is the equivalent of a function.) However, you cannot use this method to send Apple events to other applications.
///
/// When you create an instance of `NSAppleScript` object, you can use a URL to specify a script that can be in either text or compiled form, or you can supply the script as a string. Should an error occur when compiling or executing the script, several of the methods return a dictionary containing error information. The keys for obtaining error information, such as ``errorMessage``, are described in the Constants section.
///
/// See also NSAppleScript Additions Reference in the Application Kit framework, which defines a method that returns the syntax-highlighted source code for a script.
@interface NSAppleScript : NSObject<NSCopying> {
    @private
    NSString *_source;
    unsigned int _compiledScriptID;
    void *_reserved1;
    void *_reserved2;
}

/// Initializes a newly allocated script instance from the source identified by the passed URL.
///
/// - Parameters:
///   - url: A URL that locates a script, in either text or compiled form.
///   - errorInfo: On return, if an error occurs, a pointer to an error information dictionary.
/// - Returns: The initialized script object, `nil` if an error occurs.
///
/// This method is a designated initializer for `NSAppleScript`.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url error:(NSDictionary<NSString *, id> * _Nullable * _Nullable)errorInfo NS_DESIGNATED_INITIALIZER;

/// Initializes a newly allocated script instance from the passed source.
///
/// - Parameter source: A string containing the source code of a script.
/// - Returns: The initialized script object, `nil` if an error occurs.
///
/// This method is a designated initializer for `NSAppleScript`.
- (nullable instancetype)initWithSource:(NSString *)source NS_DESIGNATED_INITIALIZER;

/// The script source for the receiver.
///
/// It is possible for an `NSAppleScript` that has been instantiated with `-initWithContentsOfURL:error:` to be a script for which the source code is not available but is nonetheless executable.
@property (nullable, readonly, copy) NSString *source;

/// A Boolean value that indicates whether the receiver's script has been compiled.
@property (readonly, getter=isCompiled) BOOL compiled;

/// Compiles the receiver, if it is not already compiled.
///
/// - Parameter errorInfo: On return, if an error occurs, a pointer to an error information dictionary.
/// - Returns: `YES` for success or if the script was already compiled, `NO` otherwise.
- (BOOL)compileAndReturnError:(NSDictionary<NSString *, id> * _Nullable * _Nullable)errorInfo;

/// Executes the receiver, compiling it first if it is not already compiled.
///
/// - Parameter errorInfo: On return, if an error occurs, a pointer to an error information dictionary.
/// - Returns: The result of executing the event, or `nil` if an error occurs.
///
/// Any changes to property values caused by executing the script do not persist.
- (NSAppleEventDescriptor *)executeAndReturnError:(NSDictionary<NSString *, id> * _Nullable * _Nullable)errorInfo;

/// Executes an Apple event in the context of the receiver, as a means of allowing the application to invoke a handler in the script.
///
/// - Parameters:
///   - event: The Apple event to execute.
///   - errorInfo: On return, if an error occurs, a pointer to an error information dictionary.
/// - Returns: The result of executing the event, or `nil` if an error occurs.
///
/// Compiles the receiver before executing it if it is not already compiled.
///
/// > Important: You cannot use this method to send Apple events to other applications.
- (NSAppleEventDescriptor *)executeAppleEvent:(NSAppleEventDescriptor *)event error:(NSDictionary<NSString *, id> * _Nullable * _Nullable)errorInfo;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
