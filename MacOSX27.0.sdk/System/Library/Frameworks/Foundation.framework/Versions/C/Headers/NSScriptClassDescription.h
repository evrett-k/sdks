/*
	NSScriptClassDescription.h
	Copyright (c) 1997-2019, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSClassDescription.h>

@class NSScriptCommandDescription;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A scriptable class that a macOS app supports.
///
/// A scriptable application provides scriptability information that describes the commands and objects scripters can use in scripts that target the application. That includes information about the classes those scriptable objects are created from.
///
/// An application's scriptability information is collected automatically by an instance of ``NSScriptSuiteRegistry``. The registry object creates an `NSScriptClassDescription` for each class it finds and caches these objects in memory. Cocoa scripting uses registry information in handling scripting requests that target the application.
///
/// A class description instance stores the name, attributes, relationships, and supported commands for a class. For example, a scriptable `document` class for a drawing application might support attributes such as `file` and `file type`, relationships such as collections of `circles`, `rectangles`, and `lines`, and commands such as `align` and `rotate`.
///
/// As with many of the classes in Cocoa's built-in scripting support, your application may never need to directly work with instances of `NSScriptClassDescription`. However, one case where you might need access to a class description is if you override `objectSpecifier` in a scriptable class. For information on how to do this, see [Object Specifiers](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_object_specifiers/SAppsObjectSpecifiers.html#//apple_ref/doc/uid/TP40002164-CH3) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
///
/// Another case where your application may need access to class description information is if you override `indicesOfObjectsByEvaluatingWithContainer:count:` in a specifier class.
///
/// Although you can subclass `NSScriptClassDescription`, it is unlikely that you would need to do so, or even to create instances of it.
@interface NSScriptClassDescription : NSClassDescription {
    @private
    NSString *_suiteName;
    NSString *_objcClassName;
    FourCharCode _appleEventCode;
    NSObject *_superclassNameOrDescription;
    NSArray *_attributeDescriptions;
    NSArray *_toOneRelationshipDescriptions;
    NSArray *_toManyRelationshipDescriptions;
    NSDictionary *_commandMethodSelectorsByName;
    id _moreVars;
}

/// Returns the class description for the specified class or, if it is not scriptable, for the first superclass that is.
///
/// - Parameter aClass: The class whose description is needed.
/// - Returns: The class description for the class specified by `aClass` or, if that class isn't scriptable, the class description for the first superclass that is. Returns `nil` if it doesn't find a scriptable class.
+ (nullable NSScriptClassDescription *)classDescriptionForClass:(Class)aClass;

/// Initializes and returns a newly allocated instance of `NSScriptClassDescription`.
///
/// This method registers `self` with the application's global instance of ``NSScriptSuiteRegistry``.
///
/// - Parameters:
///   - suiteName: The name of the suite (in the application's scriptability information) that the class belongs to. For example, `"AppName Suite"`.
///   - className: The name of the class that this instance describes.
///   - classDeclaration: A class declaration dictionary of the sort that is valid in script suite property list files. This dictionary provides information about the class such as its attributes and relationships.
/// - Returns: The initialized instance. Returns `nil` if the event code value for the class description itself is missing or is not an `NSString`. Also returns `nil` if the superclass name or any of the subdictionaries of descriptions are not of the right type.
- (nullable instancetype)initWithSuiteName:(NSString *)suiteName className:(NSString *)className dictionary:(nullable NSDictionary *)classDeclaration NS_DESIGNATED_INITIALIZER;

/// The name of the receiver's suite.
///
/// Within an application's scriptability information, named suites contain related sets of information.
@property (nullable, readonly, copy) NSString *suiteName;

/// The name of the class the receiver describes, as provided at initialization time.
///
/// This may be either the human-readable name for the class -- that is, the name that is used in a script -- or the name of the Objective-C class that is instantiated to implement the class. To reliably obtain the implementation name, use ``NSScriptClassDescription/implementationClassName``.
@property (nullable, readonly, copy) NSString *className;

/// The name of the Objective-C class instantiated to implement the scripting class.
///
/// The name returned by the ``NSScriptClassDescription/className`` property for an instance of `NSScriptClassDescription` resulting from an sdef class declaration is the human-readable name for the class. To obtain the name of the Objective-C class instantiated to implement the class, use this property.
@property (nullable, readonly, copy) NSString *implementationClassName;

/// The class description instance for the superclass of the receiver's class.
///
/// The instance of `NSScriptClassDescription` that describes the superclass can be in the same suite as the receiver or in a different suite. Returns `nil` if the class has no superclass.
@property (nullable, readonly, retain) NSScriptClassDescription *superclassDescription;

/// The Apple event code associated with the receiver's class.
///
/// This is the primary four-character code used to identify the described class in Apple events.
@property (readonly) FourCharCode appleEventCode;

/// Returns a Boolean value indicating whether a primary or secondary Apple event code in the receiver matches the passed code.
///
/// - Parameter appleEventCode: An Apple event code to compare against the receiver's primary or secondary codes.
/// - Returns: `true` if the receiver's primary four-character Apple event code or any of its secondary codes (its synonyms) matches `appleEventCode`; otherwise, `false`.
- (BOOL)matchesAppleEventCode:(FourCharCode)appleEventCode;

/// Returns a Boolean value indicating whether the receiver or any superclass supports the specified command.
///
/// - Parameter commandDescription: A description for a script command, such as `duplicate`, `make`, or `move`. Encapsulates the scriptability information for that command, such as its Objective-C selector, its argument names and types, and its return type (if any).
/// - Returns: `true` if the receiver or the instance of `NSScriptClassDescription` of any superclass of the receiver's class lists the command described by `commandDescription` among its supported commands; otherwise, `false`.
- (BOOL)supportsCommand:(NSScriptCommandDescription *)commandDescription;

/// Returns the selector associated with the receiver for the specified command description.
///
/// If the described class or one of its superclasses is explicitly declared to support the described command and the declaration includes a method name, returns the selector for the class' handler method for the command.
///
/// - Parameter commandDescription: A description for a script command, such as `duplicate`, `make`, or `move`. Encapsulates the scriptability information for that command, such as its Objective-C selector, its argument names and types, and its return type (if any).
/// - Returns: The selector from the receiver for the command specified by `commandDescription`. Searches in the receiver first, then in any superclass. Returns `NULL` if no matching selector is found.
- (nullable SEL)selectorForCommand:(NSScriptCommandDescription *)commandDescription;

/// Returns the name of the declared type of the attribute or relationship identified by the passed key.
///
/// - Parameter key: The identifying key for an attribute, one-to-one relationship, or one-to-many relationship of the receiver.
/// - Returns: The name of the declared type of the attribute or relationship identified by `key`; for example, `"NSString"`. Searches in the receiver first, then in any superclass. Returns `nil` if no match is found.
- (nullable NSString *)typeForKey:(NSString *)key;

/// Returns the class description instance for the class type of the specified attribute or relationship.
///
/// - Parameter key: The identifying key for an attribute or relationship of the receiver.
/// - Returns: The instance of `NSScriptClassDescription` for the type of the attribute or relationship specified by `key`. Returns `nil` if no scriptable property corresponds to `key`.
- (nullable NSScriptClassDescription *)classDescriptionForKey:(NSString *)key;

/// Returns the Apple event code for the specified attribute or relationship in the receiver.
///
/// - Parameter key: The identifying key for an attribute or relationship of the receiver.
/// - Returns: The four-character Apple event code associated with the attribute or relationship identified by `key` in the receiver or, if none exists, in the class description for the receiver's superclass. Returns `0` if no such attribute or relationship is found.
- (FourCharCode)appleEventCodeForKey:(NSString *)key;

/// Given an Apple event code that identifies a property or element class, returns the key for the corresponding attribute, one-to-one relationship, or one-to-many relationship.
///
/// - Parameter appleEventCode: An Apple event code that identifies a property or element class.
/// - Returns: The key that corresponds to the property or element class identified by `appleEventCode` in the receiver or, if none exists, in a class description in the receiver's superclasses. Returns `nil` if it cannot find any such attribute or relationship.
- (nullable NSString *)keyWithAppleEventCode:(FourCharCode)appleEventCode;

/// The value of the `DefaultSubcontainerAttribute` entry of the class declaration dictionary provided when the receiver was instantiated.
///
/// Returns `nil` if there was no such entry.
@property (nullable, readonly, copy) NSString *defaultSubcontainerAttributeKey;

/// Returns a Boolean value indicating whether an insertion location must be specified when creating a new object in the specified to-many relationship of the receiver.
///
/// A script command object that creates a new object in a to-many relationship needs to know whether an explicitly specified insertion location is required. It can get this information from an instance of `NSScriptClassDescription`. For example, `NSMakeCommand` uses this method to determine whether or not a specific `make` AppleScript command must have an `at` parameter.
///
/// - Parameter toManyRelationshipKey: The key for the to-many relationship that may require an insertion location.
/// - Returns: `true` if an insertion location must be specified; otherwise, `false`.
- (BOOL)isLocationRequiredToCreateForKey:(NSString *)toManyRelationshipKey;

/// Returns a Boolean value indicating whether the described class has a property identified by the specified key.
///
/// - Parameter key: The identifying key for a property of the receiver.
/// - Returns: `true` if the described class has a property identified by the specified key; otherwise, `false`.
- (BOOL)hasPropertyForKey:(NSString *)key API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Returns a Boolean value indicating whether the described class has an ordered to-many relationship identified by the specified key.
///
/// - Parameter key: The identifying key for a property of the receiver.
/// - Returns: `true` if the described class has an ordered to-many relationship identified by the specified key; otherwise, `false`.
- (BOOL)hasOrderedToManyRelationshipForKey:(NSString *)key API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Returns a Boolean value indicating whether the described class has a readable property identified by the specified key.
///
/// To determine if a property is read-only, invoke ``NSScriptClassDescription/hasWritableProperty(forKey:)``.
///
/// - Parameter key: The identifying key for a property of the receiver.
/// - Returns: `true` if the described class has a readable property identified by the specified key; otherwise, `false`.
- (BOOL)hasReadablePropertyForKey:(NSString *)key API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Returns a Boolean value indicating whether the described class has a writable property identified by the specified key.
///
/// - Parameter key: The identifying key for a property of the receiver.
/// - Returns: `true` if the described class has a writable property identified by the specified key; otherwise, `false`.
- (BOOL)hasWritablePropertyForKey:(NSString *)key API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);

@end

@interface NSScriptClassDescription(NSDeprecated)

/// Returns a Boolean value indicating whether a specified property in the receiver is read-only.
///
/// @DeprecationSummary {
///     Use ``NSScriptClassDescription/hasWritableProperty(forKey:)`` instead.
/// }
///
/// This method could return `false` either because `key` is unrecognized or because writing to the property is not supported. Use ``NSScriptClassDescription/hasWritableProperty(forKey:)`` instead.
///
/// - Parameter key: The identifying key for a property of the receiver.
/// - Returns: `true` if the property specified by `key` exists in the receiver or in the `NSScriptClassDescription` for any superclass, and is read only; otherwise, `false`.
- (BOOL)isReadOnlyKey:(NSString *)key API_DEPRECATED_WITH_REPLACEMENT("-hasWritablePropertyForKey:", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

@end

@interface NSObject(NSScriptClassDescription)

/* Return the four character code identifying the receiver's class in Apple events.
*/
@property (readonly) FourCharCode classCode;

/* Return the Objective-C name of the receiver's class.
*/
@property (readonly, copy) NSString *className;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
