/*	NSTask.h
	Copyright (c) 1996-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that specify the termination reason values that the system returns.
typedef NS_ENUM(NSInteger, NSTaskTerminationReason) {
    /// The task exited normally.
    NSTaskTerminationReasonExit = 1,
    /// The task exited due to an uncaught signal.
    NSTaskTerminationReasonUncaughtSignal = 2
} API_AVAILABLE(macos(10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/// An object that represents a subprocess of the current process.
///
/// Using this class, your program can run another program as a subprocess and monitor that program's execution. Unlike ``Thread``, it doesn't share memory space with the process that creates it.
///
/// A process operates within an environment defined by the current values for several items: the current directory, standard input, standard output, standard error, and the values of any environment variables, inheriting its environment from the process that launches it.
/// If there are any environment variables that should be different for the subprocess (for example, if the current directory needs to change), change it in the instance after initialization, before your app launches it. Your app can't change a process's environment while it's running.
///
/// You can only run the subprocess once per instance. Subsequent attempts raise an error.
///
/// > Important:
/// > In a sandboxed app, child processes you create with this class inherit the sandbox of the parent app. Instead, write helper apps as XPC Services because it allows you to specify different sandbox entitlements for helper apps. For more information, see [Daemons and Services Programming Guide](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPSystemStartup/Chapters/Introduction.html#//apple_ref/doc/uid/10000172i) and <doc://com.apple.documentation/documentation/xpc>.
NS_SWIFT_SENDABLE
@interface NSTask : NSObject

/// Returns an initialized process object with the environment of the current process.
///
/// If you need to modify the environment of a process, use alloc and init, and then set up the environment before launching the new process. Otherwise, use the class method ``NSTask/launchedProcess(launchPath:arguments:)`` to create and run the process.
///
/// - Returns: An initialized process object with the environment of the current process.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// The receiver's executable.
@property (nullable, copy) NSURL *executableURL API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, watchos, tvos);

/// The command arguments that the system uses to launch the executable.
///
/// The `NSTask` object converts both `path` and the strings in `arguments` to appropriate C-style strings (using `fileSystemRepresentation`) before passing them to the task through `argv[]`. The strings in `arguments` don't undergo shell expansion, so you don't need to do special quoting, and shell variables, such as `$PWD`, aren't resolved.
@property (nullable, copy) NSArray<NSString *> *arguments;

/// The environment for the receiver.
///
/// If this method isn't used, the environment is inherited from the process that created the receiver. This method raises an `NSInvalidArgumentException` if the system has launched the receiver.
@property (nullable, copy) NSDictionary<NSString *, NSString *> *environment;

/// The current directory for the receiver.
@property (nullable, copy) NSURL *currentDirectoryURL API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, watchos, tvos);

/// The launch requirement data for the receiver.
@property (nullable, copy) NSData *launchRequirementData API_AVAILABLE(macos(14.4)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/// The standard input for the receiver.
///
/// If this is an `NSPipe` object, launching the receiver automatically closes the read end of the pipe in the current task. Don't create a handle for the pipe and pass that as the argument, or the read end of the pipe won't be closed automatically.
///
/// If this method isn't used, the standard input is inherited from the process that created the receiver. This method raises an `NSInvalidArgumentException` if the system has launched the receiver.
@property (nullable, retain) id standardInput;

/// The standard output for the receiver.
///
/// If this is an `NSPipe` object, launching the receiver automatically closes the write end of the pipe in the current task. Don't create a handle for the pipe and pass that as the argument, or the write end of the pipe won't be closed automatically.
///
/// If this method isn't used, the standard output is inherited from the process that created the receiver. This method raises an `NSInvalidArgumentException` if the system has launched the receiver.
@property (nullable, retain) id standardOutput;

/// The standard error for the receiver.
///
/// If this is an `NSPipe` object, launching the receiver automatically closes the write end of the pipe in the current task. Don't create a handle for the pipe and pass that as the argument, or the system won't automatically close the write end of the pipe.
///
/// If this method isn't used, the standard error is inherited from the process that created the receiver. This method raises an `NSInvalidArgumentException` if the system has launched the receiver.
@property (nullable, retain) id standardError;

/// Runs the process with the current environment.
- (BOOL)launchAndReturnError:(out NSError **_Nullable)error API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sends an interrupt signal to the receiver and all of its subtasks.
///
/// If the task terminates as a result, which is the default behavior, an `NSTaskDidTerminateNotification` gets sent to the default notification center. This method has no effect if the receiver was already launched and has already finished executing. If the system hasn't launched the receiver, this method raises an `NSInvalidArgumentException`.
///
/// It isn't always possible to interrupt the receiver because it might be ignoring the interrupt signal. This method sends `SIGINT`.
- (void)interrupt;

/// Sends a terminate signal to the receiver and all of its subtasks.
///
/// If the task terminates as a result, which is the default behavior, an `NSTaskDidTerminateNotification` gets sent to the default notification center. This method has no effect if the receiver was already launched and has already finished executing. If the receiver hasn't been launched yet, this method raises an `NSInvalidArgumentException`.
///
/// It's not always possible to terminate the receiver because it might be ignoring the terminate signal. This method sends `SIGTERM`.
- (void)terminate;

/// Suspends execution of the receiver task.
///
/// Multiple `suspend` messages can be sent, but they must be balanced with an equal number of `resume` messages before the task resumes execution.
///
/// - Returns: `YES` if the receiver was successfully suspended, `NO` otherwise.
- (BOOL)suspend;

/// Resumes execution of a suspended task.
///
/// If the system sent multiple `suspend` messages to the receiver, an equal number of `resume` messages must be sent before the task resumes execution.
///
/// - Returns: `YES` if the receiver was able to resume execution, `NO` otherwise.
- (BOOL)resume;

/// The receiver's process identifier.
@property (readonly) int processIdentifier;

/// A status that indicates whether the receiver is still running.
@property (readonly, getter=isRunning) BOOL running;

/// The exit status the receiver's executable returns.
///
/// Each task defines and documents how your app should interpret the return value. For example, many commands return 0 if they complete successfully or an error code if they don't. You'll need to look at the documentation for that task to learn what values it returns under what circumstances.
///
/// This method raises an `NSInvalidArgumentException` if the receiver is still running. Verify that the receiver isn't running before you use it.
@property (readonly) int terminationStatus;

/// The reason the system terminated the task.
///
/// The possible values are described in `NSTaskTerminationReason`.
@property (readonly) NSTaskTerminationReason terminationReason API_AVAILABLE(macos(10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/// A completion block the system invokes when the task completes.
///
/// The system passes the task object to the block to allow access to the task parameters, for example to determine if the task completed successfully.
///
/// This block isn't guaranteed to be fully executed prior to `waitUntilExit` returning.
///
/// Setting the block to nil is valid, and stops the previous block from being invoked, as long as it hasn't started in any way. Only one termination handler block can be set at any time. If a terminationHandler is set on an NSTask, the NSTaskDidTerminateNotification notification is not posted for that task.
@property (nullable, copy) void (NS_SWIFT_SENDABLE ^terminationHandler)(NSTask *) API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos);

/// The default quality of service level the system applies to operations the task executes.
@property NSQualityOfService qualityOfService API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)); // read-only after the task is launched

@end

@interface NSTask (NSTaskConveniences)

/// Creates and runs a task with a specified executable and arguments.
///
/// - Parameter url: The URL for the executable.
/// - Parameter arguments: An array of `NSString` objects that supplies the arguments to the task.
/// - Parameter error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Parameter terminationHandler: The system invokes this completion block when the task has completed.
/// - Returns: An initialized `NSTask` object with the environment of the current process.
+ (nullable NSTask *)launchedTaskWithExecutableURL:(NSURL *)url arguments:(NSArray<NSString *> *)arguments error:(out NSError ** _Nullable)error terminationHandler:(void (NS_SWIFT_SENDABLE ^_Nullable)(NSTask *))terminationHandler API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, watchos, tvos);

/// Blocks the process until the receiver is finished.
///
/// This method first checks to see if the receiver is still running using `isRunning`. Then it polls the current run loop using `NSDefaultRunLoopMode` until the task completes.
///
/// @TabNavigator {
///     @Tab("Swift") {
///         ```swift
///         let task: NSTask = // Create and initialize a task
///             task.launch()
///         task.waitUntilExit()
///         let status = task.terminationStatus
///
///         if status == 0 {
///             print("Task succeeded.")
///         } else {
///             print("Task failed.")
///         }
///         ```
///     }
///     @Tab("Objective-C") {
///         ```objc
///         NSTask *task = // Create and initialize a task
///         [task launch];
///         [task waitUntilExit];
///         int status = [task terminationStatus];
///
///         if (status == 0) {
///             NSLog(@"Task succeeded.");
///         } else {
///             NSLog(@"Task failed.");
///         }
///         ```
///     }
/// }
///
/// `waitUntilExit` does not guarantee that the `terminationHandler` block has been fully executed before `waitUntilExit` returns.
- (void)waitUntilExit;

@end

@interface NSTask (NSDeprecated)

/// Sets the receiver's executable.
///
/// @deprecated Use `executableURL` instead.
@property (nullable, copy) NSString *launchPath API_DEPRECATED_WITH_REPLACEMENT("executableURL", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sets the current directory for the receiver.
///
/// @deprecated Use `currentDirectoryURL` instead.
///
/// If this method isn't used, the current directory is inherited from the process that created the receiver. This method raises an `NSInvalidArgumentException` if the receiver has already been launched.
@property (copy) NSString *currentDirectoryPath API_DEPRECATED_WITH_REPLACEMENT("currentDirectoryURL", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);

/// Launches the task represented by the receiver.
///
/// @DeprecationSummary {
///     Use ``run()`` instead.
/// }
///
/// Raises an `NSInvalidArgumentException` if the launch path has not been set or is invalid or if it fails to create a process.
- (void)launch API_DEPRECATED_WITH_REPLACEMENT("launchAndReturnError:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);

/// Creates and launches a task with a specified executable and arguments.
///
/// @deprecated Use `launchedTaskWithExecutableURL:arguments:error:terminationHandler:` instead.
///
/// The task inherits its environment from the process that invokes this method.
///
/// The `NSTask` object converts both `path` and the strings in `arguments` to appropriate C-style strings (using `fileSystemRepresentation`) before passing them to the task via `argv[]`. The strings in `arguments` don't undergo shell expansion, so you don't need to do special quoting, and shell variables, such as `$PWD`, aren't resolved.
///
/// - Parameter path: The path to the executable.
/// - Parameter arguments: An array of `NSString` objects that supplies the arguments to the task.
/// - Returns: An initialized `NSTask` object with the supplied `arguments`.
+ (NSTask *)launchedTaskWithLaunchPath:(NSString *)path arguments:(NSArray<NSString *> *)arguments API_DEPRECATED_WITH_REPLACEMENT("launchedTaskWithExecutableURL:arguments:error:", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/// Posted when the task has stopped execution.
///
/// The notification object is the `NSTask` object that the system terminated. This notification doesn't contain a `userInfo` dictionary.
///
/// The system posts this notification from the thread in which the `NSTask` object called `launch`. When launching a task from a secondary thread or background queue, you can use the `terminationHandler` property instead for greater control over the execution context of any operations to be performed after the task finishes.
///
/// This notification can be posted either when the task has exited normally or as a result of `terminate` being sent to the `NSTask` object. If the `NSTask` object gets released, however, this notification won't get sent, as the port the message would have been sent on was released as part of the task release. The observer method can use `terminationStatus` to determine why the task died.
FOUNDATION_EXPORT NSNotificationName const NSTaskDidTerminateNotification;

NS_HEADER_AUDIT_END(nullability, sendability)
