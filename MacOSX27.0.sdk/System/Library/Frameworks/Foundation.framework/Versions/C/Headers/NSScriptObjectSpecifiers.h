/*
	NSScriptObjectSpecifiers.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSAppleEventDescriptor, NSNumber, NSScriptClassDescription, NSScriptWhoseTest, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Error codes for specific problems evaluating specifiers.
NS_ENUM(NSInteger) {
    /// No error encountered.
    NSNoSpecifierError = 0,
    /// Someone called evaluate with `nil`.
    NSNoTopLevelContainersSpecifierError,
    /// An error occurred evaluating the container specifier.
    NSContainerSpecifierError,
    /// Receivers do not understand the key.
    NSUnknownKeySpecifierError,
    /// Index out of bounds.
    NSInvalidIndexSpecifierError,
    /// Other internal error.
    NSInternalSpecifierError,
    /// An attempt was made to perform an unsupported operation on some key.
    NSOperationNotSupportedForKeySpecifierError
};


/// Constants that represent positions for inserting objects relative to a specified object.
typedef NS_ENUM(NSUInteger, NSInsertionPosition) {
    /// After the specified object.
    NSPositionAfter,
    /// Before the specified object.
    NSPositionBefore,
    /// At the beginning of the container.
    NSPositionBeginning,
    /// At the end of the container.
    NSPositionEnd,
    /// Replacing the specified object.
    NSPositionReplace
};

/// Constants that represent a relative position.
typedef NS_ENUM(NSUInteger, NSRelativePosition) {
    /// After the base object.
    NSRelativeAfter = 0,
    /// Before the base object.
    NSRelativeBefore
};

/// Constants that identify how to select subelements within a range.
typedef NS_ENUM(NSUInteger, NSWhoseSubelementIdentifier) {
    /// Select the subelement at a specific index.
    NSIndexSubelement = 0,
    /// Select every subelement.
    NSEverySubelement = 1,
    /// Select the middle subelement.
    NSMiddleSubelement = 2,
    /// Select a random subelement.
    NSRandomSubelement = 3,
    /// No subelement, only valid for the end subelement.
    NSNoSubelement = 4
};

/// An abstract class used to represent natural language expressions.
///
/// `NSScriptObjectSpecifier` is the abstract superclass for classes that instantiate objects called "object specifiers." An object specifier represents an AppleScript reference form, which is a natural-language expression such as `words 10 through 20` or `front document` or `words whose color is red`.
///
/// The scripting system maps these words or phrases to attributes and relationships of scriptable objects. A reference form rarely occurs in isolation; usually a script statement consists of a series of reference forms preceded by a command and typically connected to each other by `of`, such as:
///
/// ```objc
/// get words whose color is blue of paragraph 10 of front document
/// ```
///
///
/// The expression `words whose color is blue of paragraph 10 of front document` specifies a location in the application's AppleScript object model—the objects the application makes available to scripters. The classes of objects in the object model often closely match the classes of actual objects in the application, but they are not required to. An object specifier locates objects in the running application that correspond to the specified object model objects.
///
/// Your application typically creates object specifiers when it implements the `objectSpecifier` method for its scriptable classes. That method is defined by the NSScriptObjectSpecifiers protocol.
///
/// It is unlikely that you would ever need to create your own subclass of `NSScriptObjectSpecifier`; the set of valid AppleScript reference forms is determined by Apple Computer and object specifier classes are already implemented for this set. If for some reason you do need to create a subclass, you must override the primitive method ``indicesOfObjectsByEvaluating(withContainer:count:)`` to return indices to the elements within the container whose values are matched with the child specifier's key. In addition, you probably need to declare any special instance variables and implement an initializer that invokes super's designated initializer, ``init(containerClassDescription:containerSpecifier:key:)``, and initializes these variables.
///
/// For a comprehensive treatment of object specifiers, including sample code, see [Object Specifiers](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_object_specifiers/SAppsObjectSpecifiers.html#//apple_ref/doc/uid/TP40002164-CH3) in [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164).
@interface NSScriptObjectSpecifier : NSObject <NSCoding> {
    @private
    NSScriptObjectSpecifier *_container;
    NSScriptObjectSpecifier *_child;
    NSString *_key;
    NSScriptClassDescription *_containerClassDescription;
    BOOL _containerIsObjectBeingTested;
    BOOL _containerIsRangeContainerObject;
    char _padding[2];
    NSAppleEventDescriptor *_descriptor;
    NSInteger _error;
}

/// Given a `typeObjectSpecifier` Apple event descriptor, creates and returns an object specifier.
///
/// Returns `nil` on failure. If this is invoked and fails during the execution of a script command, information about the error that caused the failure is recorded in `[NSScriptCommand currentCommand]`.
+ (nullable NSScriptObjectSpecifier *)objectSpecifierWithDescriptor:(NSAppleEventDescriptor *)descriptor API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);

/// Initializes a specifier with a container specifier and key.
- (instancetype)initWithContainerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property;

/// The designated initializer.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

/// The child specifier of this specifier.
@property (nullable, assign) NSScriptObjectSpecifier *childSpecifier;

/// The container specifier of this specifier.
@property (nullable, retain) NSScriptObjectSpecifier *containerSpecifier;

/// A Boolean value that indicates whether the container is the object currently being tested by an `NSWhoseSpecifier`.
@property BOOL containerIsObjectBeingTested;
/// A Boolean value that indicates whether the container is the container for the current range specifier being evaluated.
@property BOOL containerIsRangeContainerObject;

/// The name of the key in the container object to be accessed by this specifier.
@property (copy) NSString *key;

/// The class description for the container.
@property (nullable, retain) NSScriptClassDescription *containerClassDescription;
/// The class description for the keyed objects.
@property (nullable, readonly, retain) NSScriptClassDescription *keyClassDescription;

/// Returns the indices of the specified objects in the container.
- (nullable NSInteger *)indicesOfObjectsByEvaluatingWithContainer:(id)container count:(NSInteger *)count NS_RETURNS_INNER_POINTER;
/// Returns the specified objects from the given containers.
- (nullable id)objectsByEvaluatingWithContainers:(id)containers;
/// The actual objects represented by this specifier.
@property (nullable, readonly, retain) id objectsByEvaluatingSpecifier;

/// The error number from the most recent evaluation.
@property NSInteger evaluationErrorNumber;
/// The specifier in which an evaluation error occurred.
@property (nullable, readonly, retain) NSScriptObjectSpecifier *evaluationErrorSpecifier;

/// An Apple event descriptor that represents this specifier.
@property (nullable, readonly, copy) NSAppleEventDescriptor *descriptor API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);

@end


@interface NSObject (NSScriptObjectSpecifiers)

@property (nullable, readonly, retain) NSScriptObjectSpecifier *objectSpecifier;
    // Overridden by objects that can provide a fully specified object specifier to themselves within an app.

- (nullable NSArray<NSNumber *> *)indicesOfObjectsByEvaluatingObjectSpecifier:(NSScriptObjectSpecifier *)specifier;
    // Containers that want to evaluate some specifiers on their own should implement this method.  The result array should be full of NSNumber objects which identify the indices of the matching objects.  If this method returns nil, the object specifier will go on to do its own evaluation.  If this method returns an array, the object specifier will use the NSNumbers in it as the indices.  So, if you evaluate the specifier and there are no objects which match, you should return an empty array, not nil.  If you find only one object you should still return its index in an array.  Returning an array with a single index where the index is -1 is interpretted to mean all the objects.

@end


/// A specifier representing an object in a collection (or container) with an index number.
///
/// The script terms `first` and `front` specify the object with index `0`, while `last` specifies the object with index of `count-1`. A negative index indicates a location by counting backward from the last object in the collection.
///
/// You don't normally subclass `NSIndexSpecifier`.
@interface NSIndexSpecifier : NSScriptObjectSpecifier {
    @private
    NSInteger _index;
}

/// Initializes a specifier with a container description, container specifier, key, and index.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property index:(NSInteger)index NS_DESIGNATED_INITIALIZER;

/// The index position of the object to be retrieved.
@property NSInteger index;

@end


/// A specifier that returns the middle object.

/// A specifier indicating the middle object in a collection or, if not a one-to-many relationship, the sole object.
///
/// You don't typically subclass `NSMiddleSpecifier`.
///
/// ## See Also
///
/// - [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164)
@interface NSMiddleSpecifier : NSScriptObjectSpecifier {}

@end


/// A specifier for an object in a collection (or container) by name.
///
/// As an example, the following script specifies both an application and a window by name. In this script, the named window's implicitly specified container is the Finder application's list of open windows.
///
/// ```objc
/// tell application "Finder" -- specifies an application  by name
/// close window "Reports" -- specifies a window by name
/// end tell
/// ```
///
///
/// This specifier works only for objects that have a name property. You don't normally subclass `NSNameSpecifier`.
///
/// The evaluation of an instance of `NSNameSpecifier` follows these steps until the specified object is found:
///
/// 1. If the container implements a method whose selector matches the relevant `valueIn<Key>WithName:` pattern established by scripting key-value coding, the method is invoked. This method can potentially be very fast, and it may be relatively easy to implement.
/// 2. As is the case when evaluating any script object specifier, the container of the specified object is given a chance to evaluate the object specifier. If the container class implements the `indicesOfObjectsByEvaluatingObjectSpecifier` method, the method is invoked. This method can potentially be very fast, but it is relatively difficult to implement.
/// 3. An instance of  `NSWhoseSpecifier` that specifies the first object whose relevant `'pnam'` attribute matches the name is synthesized and evaluated. The instance of `NSWhoseSpecifier` must search through all of the keyed elements in the container, looking for a match. The search is potentially very slow.
@interface NSNameSpecifier : NSScriptObjectSpecifier {
    @private
    NSString *_name;
}

- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;
/// Initializes a name specifier with a container description, container specifier, key, and name.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property name:(NSString *)name NS_DESIGNATED_INITIALIZER;
/// The name of the object to be retrieved.
@property (copy) NSString *name;

@end


/// A specifier for an insertion point in a container relative to another object in the container.
///
/// Instances of `NSPositionalSpecifier` specify an insertion point in a container relative to another object in the container, for example, `before first word` or `after paragraph 4`. The container is specified by an instance of `NSScriptObjectSpecifier`. `NSPositionalSpecifier` objects commonly encapsulate object specifiers used as arguments to the `make` (`create`) and `move` commands and indicate where the created or moved object is to be inserted relative to the object represented by an object specifier.
///
/// Invoking an accessor method to obtain information about an instance of `NSPositionalSpecifier`  causes the object to be evaluated if it hasn't been already.
///
/// You don't normally subclass `NSPositionalSpecifier`.
@interface NSPositionalSpecifier : NSObject {
    @private
    NSScriptObjectSpecifier *_specifier;
    NSInsertionPosition _unadjustedPosition;
    NSScriptClassDescription *_insertionClassDescription;
    id _moreVars;
    void *_reserved0;
}

/// Initializes a positional specifier with an insertion position and an object specifier.
- (instancetype)initWithPosition:(NSInsertionPosition)position objectSpecifier:(NSScriptObjectSpecifier *)specifier NS_DESIGNATED_INITIALIZER;

/// The insertion position.
@property (readonly) NSInsertionPosition position API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// The object specifier that identifies the reference object.
@property (readonly, retain) NSScriptObjectSpecifier *objectSpecifier API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sets the class description for the object or objects to be inserted.
- (void)setInsertionClassDescription:(NSScriptClassDescription *)classDescription;

/// Evaluates this positional specifier.
- (void)evaluate;

/// The container into which insertion should be done, if evaluation has been successful.
@property (nullable, readonly, retain) id insertionContainer;

/// The key for the to-many relationship for which insertion should be done, if evaluation has been successful.
@property (nullable, readonly, copy) NSString *insertionKey;

/// The index at which insertion should be done, if evaluation has been successful.
@property (readonly) NSInteger insertionIndex;

/// A Boolean value that indicates whether the object to be inserted should replace the keyed, indexed object.
@property (readonly) BOOL insertionReplaces;

@end


/// A specifier for a simple attribute value, a one-to-one relationship, or all elements of a to-many relationship.
///
/// You don't typically subclass ``NSPropertySpecifier``.
///
/// ## See Also
///
/// - [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164)
@interface NSPropertySpecifier : NSScriptObjectSpecifier {}

@end


/// A specifier for an arbitrary object in a collection or, if not a one-to-many relationship, the sole object.
///
/// ## See Also
///
/// - [Cocoa Scripting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ScriptableCocoaApplications/SApps_intro/SAppsIntro.html#//apple_ref/doc/uid/TP40002164)
@interface NSRandomSpecifier : NSScriptObjectSpecifier {}

@end


/// A specifier for a range of objects in a container.
///
/// An `NSRangeSpecifier` object specifies a range (that is, an uninterrupted series) of objects in a container through two delimiting objects. The range is represented by two object specifiers, a start specifier and an end specifier, which can be of any specifier type (such as ``NSIndexSpecifier`` or ``NSWhoseSpecifier`` object). These specifiers are evaluated in the context of the same container object as the range specifier itself.
///
/// You don't normally subclass `NSRangeSpecifier`.
@interface NSRangeSpecifier : NSScriptObjectSpecifier {
    @private
    NSScriptObjectSpecifier *_startSpec;
    NSScriptObjectSpecifier *_endSpec;
}
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;
/// Initializes a range specifier with start and end specifiers.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property startSpecifier:(nullable NSScriptObjectSpecifier *)startSpec endSpecifier:(nullable NSScriptObjectSpecifier *)endSpec NS_DESIGNATED_INITIALIZER;

/// The specifier for the beginning of the range.
@property (nullable, retain) NSScriptObjectSpecifier *startSpecifier;

/// The specifier for the end of the range.
@property (nullable, retain) NSScriptObjectSpecifier *endSpecifier;

@end


/// A specifier that indicates an object in a collection by its position relative to another object.
///
/// You don't normally subclass `NSRelativeSpecifier`.
@interface NSRelativeSpecifier : NSScriptObjectSpecifier {
    @private
    NSRelativePosition _relativePosition;
    NSScriptObjectSpecifier *_baseSpecifier;
}
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;
/// Initializes a relative specifier with a position and base specifier.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property relativePosition:(NSRelativePosition)relPos baseSpecifier:(nullable NSScriptObjectSpecifier *)baseSpecifier NS_DESIGNATED_INITIALIZER;

/// The relative position (before or after) of the object to be located.
@property NSRelativePosition relativePosition;

/// The specifier for the base object relative to which the target is located.
@property (nullable, retain) NSScriptObjectSpecifier *baseSpecifier;

@end


/// A specifier for an object in a collection (or container) by unique ID.
///
/// This specifier works only for objects that have an ID property. The unique ID object passed to an instance of  `NSUniqueIDSpecifier` must be either an `NSNumber` object or an `NSString` object. The exact type should match the scripting dictionary declaration of the ID attribute for the relevant scripting class.
///
/// You can expect that the ID property will be _read only_ for any object that supports it. Therefore a scripter can obtain the unique ID for an object and refer to the object by the ID, but cannot set the unique ID.
///
/// You don't normally subclass `NSUniqueIDSpecifier`.
///
/// The evaluation of `NSUniqueIDSpecifier` objects follows these steps until the specified object is found:
///
/// 1. If the container implements a method whose selector matches the relevant `valueIn<Key>WithUniqueID:` pattern established by scripting key-value coding, the method is invoked. This method can potentially be very fast, and it may be relatively easy to implement.
/// 2. As is the case when evaluating any script object specifier, the container of the specified object is given a chance to evaluate the object specifier. If the container class implements the <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/indicesofobjects(byevaluatingobjectspecifier:)> method, the method is invoked. This method can potentially be very fast, but it is relatively difficult to implement.
/// 3. An ``NSWhoseSpecifier`` object that specifies the first object whose relevant `'ID  '` attribute matches the ID is synthesized and evaluated. The `NSWhoseSpecifier` object must search through all of the keyed elements in the container, looking for a match. The search is potentially very slow.
@interface NSUniqueIDSpecifier : NSScriptObjectSpecifier {
    @private
    id _uniqueID;
}
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;
/// Initializes a unique ID specifier with the specified unique ID.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property uniqueID:(id)uniqueID NS_DESIGNATED_INITIALIZER;

/// The unique ID of the object to be located.
@property (copy) id uniqueID;

@end


/// A specifier that indicates every object in a collection matching a condition.
///
/// `NSWhoseSpecifier` specifies every object in a collection (or every element in a container) that matches the condition defined by a single Boolean expression or multiple Boolean expressions connected by logical operators. `NSWhoseSpecifier` is unique among object specifiers in that its top-level container is typically not the application object but an evaluated object specifier involved in the tested-for condition. An `NSWhoseSpecifier` object encapsulates a "test" object for defining this condition. A test object is instantiated from a subclass of the abstract ``NSScriptWhoseTest`` class, whose one declared method is ``NSScriptWhoseTest/isTrue()``. See "Boolean Expressions and Logical Operations" in ``NSScriptObjectSpecifier`` and the descriptions in NSComparisonMethods and NSScriptingComparisonMethods for more information.
///
/// The set of elements specified by an `NSWhoseSpecifier` object can be a subset of those that pass the `NSWhoseSpecifier` object's test. This subset is specified by the various sub-element properties of the `NSWhoseSpecifier` object . Consider as an example the specifier `paragraphs where color of third word is blue`. This would be represented by an `NSWhoseSpecifier` object  that uses a test specifier and another object specifier to identify a subset of the objects with the specified property. That is, the specifier's property is `paragraphs`; the test specifier is an index specifier with property `words` and `index 3`; and the qualifier is a key value qualifier for key `color` and value `[NSColor blueColor]`. The test object specifier (`word at index 3`) is evaluated for each object (paragraph) using that object as the container; the resulting objects (if any) are tested with the qualifier (`color blue`).
///
/// `NSWhoseSpecifier` is part of Cocoa's built-in script handling. You don't normally subclass it.
@interface NSWhoseSpecifier : NSScriptObjectSpecifier {
    @private
    NSScriptWhoseTest *_test;
    NSWhoseSubelementIdentifier _startSubelementIdentifier;
    NSInteger _startSubelementIndex;
    NSWhoseSubelementIdentifier _endSubelementIdentifier;
    NSInteger _endSubelementIndex;
}
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;
/// Initializes a whose specifier with a test.
- (instancetype)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(nullable NSScriptObjectSpecifier *)container key:(NSString *)property test:(NSScriptWhoseTest *)test NS_DESIGNATED_INITIALIZER;

/// The test used to qualify the objects.
@property (retain) NSScriptWhoseTest *test;
/// The identifier for the start subelement.
@property NSWhoseSubelementIdentifier startSubelementIdentifier;

/// The index of the start subelement. Only used if `startSubelementIdentifier` is `NSIndexSubelement`.
@property NSInteger startSubelementIndex;

/// The identifier for the end subelement.
@property NSWhoseSubelementIdentifier endSubelementIdentifier;

/// The index of the end subelement. Only used if `endSubelementIdentifier` is `NSIndexSubelement`.
@property NSInteger endSubelementIndex;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

