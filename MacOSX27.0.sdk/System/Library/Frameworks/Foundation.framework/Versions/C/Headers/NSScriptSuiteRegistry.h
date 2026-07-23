/*
	NSScriptSuiteRegistry.h
	Copyright (c) 1997-2019, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSBundle, NSData, NSDictionary<KeyType, ObjectType>, NSMutableArray, NSMutableDictionary, NSMutableSet, NSScriptClassDescription, NSScriptCommandDescription;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The top-level repository of scriptability information for an app at runtime.
///
/// Scriptability information specifies the terminology available for use in scripts that target an application. It also provides information, used by AppleScript and by Cocoa, about how support for that terminology is implemented in the application. This information includes descriptions of the scriptable object classes in an application and of the commands the application supports.
///
/// There are two standard formats for supplying scriptability information: the older script suite format, consisting of a script suite file and one or more script terminology files, and the newer scripting definition (or sdef) format, consisting of a single sdef file.
///
/// There is one instance of `NSScriptSuiteRegistry` per scriptable application. This registry object collects scriptability information when the application first needs to respond to an Apple event for which Cocoa hasn't installed a default event handler. It then creates one instance of  ``NSScriptClassDescription`` for each object class and one instance of ``NSScriptCommandDescription`` for each command class, and installs a command handler for each command.
///
/// When a user executes an AppleScript script, Apple events are sent to the targeted application. Using the information stored in the registry object, Cocoa automatically converts incoming Apple events into script commands (based on ``NSScriptCommand`` or a subclass) that manipulate objects in the application.
///
/// The public methods of `NSScriptSuiteRegistry` are used primarily by Cocoa's built-in scripting support. You should not need to create a subclass of `NSScriptSuiteRegistry`.
///
/// For information on scriptability information formats, loading of scriptability information, and related topics, see "Scriptability Information" in [Overview of Cocoa Support for Scriptable Applications](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_about_apps/SAppsAboutApps.html#//apple_ref/doc/uid/TP40001976) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
@interface NSScriptSuiteRegistry : NSObject {
    @private
    BOOL _isLoadingSDEFFiles;
    BOOL _isLoadingSecurityOverride;
    BOOL _hasLoadedIntrinsics;
    char _reserved1[1];
    NSMutableSet *_seenBundles;
    NSMutableArray *_suiteDescriptionsBeingCollected;
    NSScriptClassDescription *_classDescriptionNeedingRegistration;
    NSMutableArray *_suiteDescriptions;
    NSScriptCommandDescription *_commandDescriptionNeedingRegistration;
    NSMutableDictionary *_cachedClassDescriptionsByAppleEventCode;
    NSMutableDictionary *_cachedCommandDescriptionsByAppleEventCodes;
    NSDictionary *_cachedSuiteDescriptionsByName;
    NSMutableDictionary *_complexTypeDescriptionsByName;
    NSMutableDictionary *_listTypeDescriptionsByName;
    unsigned int _nextComplexTypeAppleEventCode;
    void *_reserved2[4];
}

/// Returns the single, shared instance of `NSScriptSuiteRegistry`, creating it first if it doesn't exist.
///
/// If it creates an instance, and if the application provides scriptability information in the script suite format, the method loads suite definitions in all frameworks and other bundles that the application currently imports or includes; if information is provided in the sdef format, the method loads information only from the specified sdef file. If in reading scriptability information an exception is raised because of parsing errors, it handles the exception by printing a line of information to the console.
+ (NSScriptSuiteRegistry *)sharedScriptSuiteRegistry;
/// Sets the single, shared instance of `NSScriptSuiteRegistry` to `registry`.
+ (void)setSharedScriptSuiteRegistry:(NSScriptSuiteRegistry *)registry;

/// Loads the suite definitions in the specified bundle, invoking ``NSScriptSuiteRegistry/loadSuite(with:from:)`` for each suite found.
///
/// If errors occur while the method is parsing a suite-definition file, the method logs error messages to the console. Redundant invocations of this method are ignored.
///
/// - Parameter bundle: The bundle from which to load `.scriptSuite`/`.scriptTerminology` resource files.
- (void)loadSuitesFromBundle:(NSBundle *)bundle;

/// Loads the suite definition encapsulated in `suiteDeclaration`; previously, this suite definition was parsed from a `.scriptSuite` property list contained in a framework or in `bundle`.
///
/// The method extracts information from the dictionary and caches it in various internal collection objects. If keys are missing or values are of the wrong type, it logs messages to the console. It also registers class descriptions and command descriptions. In registering a class description, it invokes the ``NSClassDescription`` class method ``NSClassDescription/register(_:for:)``. In registering a command description, it arranges for the Apple event translator to handle incoming Apple events that represent the defined commands.
///
/// This method is invoked when the shared instance is initialized and when bundles are loaded at runtime. Prior to invoking it, `NSScriptSuiteRegistry` creates the dictionary argument from the `.scriptSuite` property list. If you invoke this method in your code, you should try to do it before the application receives its first Apple event.
///
/// - Parameters:
///   - suiteDeclaration: A scripting suite declaration dictionary of the sort that is valid in `.scriptSuite` property list files.
///   - bundle: The bundle that contains the code that implements the suite.
- (void)loadSuiteWithDictionary:(NSDictionary *)suiteDeclaration fromBundle:(NSBundle *)bundle;

/// Registers class description `classDescription` for use by Cocoa's built-in scripting support by storing it in a per-suite internal dictionary under the class name.
///
/// - Parameter classDescription: The scripting class description to register.
- (void)registerClassDescription:(NSScriptClassDescription *)classDescription;
/// Registers command description `commandDescription` for use by Cocoa's built-in scripting support by storing it in a per-suite internal dictionary under the command name.
///
/// Also registers with the single, shared instance of ``NSAppleEventManager`` to handle incoming Apple events that should be handled by the command.
///
/// - Parameter commandDescription: The scripting command description to register.
- (void)registerCommandDescription:(NSScriptCommandDescription *)commandDescription;

/// The names of the suite definitions currently loaded by the application.
@property (readonly, copy) NSArray<NSString *> *suiteNames;

/// Returns the Apple event code associated with the suite named `suiteName`, such as `'core'` for the Core suite.
///
/// - Parameter suiteName: The name of a scripting suite.
/// - Returns: The four-character code used to identify the named suite.
- (FourCharCode)appleEventCodeForSuite:(NSString *)suiteName;

/// Returns the bundle containing the suite-definition property list (extension `.scriptSuite`) identified by `suiteName`.
///
/// - Parameter suiteName: The name of a scripting suite.
/// - Returns: The bundle that contains the code that implements the named suite.
- (nullable NSBundle *)bundleForSuite:(NSString *)suiteName;

/// Returns the class descriptions contained in the suite identified by `suiteName`.
///
/// Each class description (instance of ``NSScriptClassDescription``) in the returned dictionary is identified by class name.
///
/// - Parameter suiteName: The name of a scripting suite.
/// - Returns: A dictionary containing the descriptions of all of the classes in the named suite, keyed by class name.
- (nullable NSDictionary<NSString *, NSScriptClassDescription *> *)classDescriptionsInSuite:(NSString *)suiteName;
/// Returns the command descriptions contained in the suite identified by `suiteName`.
///
/// Each command description (instance of ``NSScriptCommandDescription``) in the returned dictionary is identified by command name.
///
/// - Parameter suiteName: The name of a scripting suite.
/// - Returns: A dictionary containing the descriptions of all of the commands in the named suite, keyed by command name.
- (nullable NSDictionary<NSString *, NSScriptCommandDescription *> *)commandDescriptionsInSuite:(NSString *)suiteName;

/// Returns the name of the suite definition associated with the given four-character Apple event code, `appleEventCode`.
///
/// - Parameter appleEventCode: A four-character code used to identify a scripting suite.
/// - Returns: The name of the suite, or `nil` if no suite matches.
- (nullable NSString *)suiteForAppleEventCode:(FourCharCode)appleEventCode;

/// Returns the class description associated with the given four-character Apple event code, `appleEventCode`.
///
/// Overriding behavior is important here. Multiple classes can have the same code if the classes have an uninterrupted linear inheritance from one another. For example, if class B is a subclass of A and class C is a subclass of B, and all three classes have the same four-character Apple event code, then this method returns the class description for class C.
///
/// - Parameter appleEventCode: A four-character code used to identify a scriptable class in Apple events.
/// - Returns: The class description, or `nil` if no class matches.
- (nullable NSScriptClassDescription *)classDescriptionWithAppleEventCode:(FourCharCode)appleEventCode;

/// Returns the command description identified by a suite's four-character Apple event code of the class and the four-character Apple event code of the command.
///
/// - Parameters:
///   - appleEventClassCode: The four-character Apple event class code.
///   - appleEventIDCode: The four-character Apple event ID code.
/// - Returns: The command description, or `nil` if no command matches.
- (nullable NSScriptCommandDescription *)commandDescriptionWithAppleEventClass:(FourCharCode)appleEventClassCode andAppleEventCode:(FourCharCode)appleEventIDCode;

/// Returns an `NSData` object that contains data in `'aete'` resource format describing the scriptability information currently known to the application.
///
/// This method is typically invoked to implement the `get aete` Apple event for an application that provides scriptability information in the script suite format. The `languageName` argument is the name of a language for which a localized resource directory (such as `English.lproj`) exists. This language indication specifies the set of `.scriptTerminology` files to be used to generate the data. `NSScriptSuiteRegistry` does not create an `'aete'` resource unless this method is called.
///
/// - Parameter languageName: The name of a language for which localized script terminology files exist.
/// - Returns: Data in `'aete'` resource format, or `nil` if the data cannot be generated.
- (nullable NSData *)aeteResource:(NSString *)languageName;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
