/*
	NSScriptExecutionContext.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSConnection;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The context in which the current script command is executed.
///
/// An `NSScriptExecutionContext` object is a shared instance (there is only one instance of the class) that represents the context in which the current script command is executed. `NSScriptExecutionContext` tracks global state relating to the command being executed, especially the top-level container object (that is, the container implied by a specifier object that specifies no container) used in an evaluation of an ``NSScriptObjectSpecifier`` object.
///
/// In most cases, the top-level container for a complete series of nested object specifiers is automatically set to the application object (`NSApp`), and you can get this object with the ``topLevelObject`` method. But you can also set this top-level container to something else (using ``topLevelObject``) if the situation warrants it.
///
/// It is unlikely that you will need to subclass `NSScriptExecutionContext`.
@interface NSScriptExecutionContext : NSObject {
    @private
    id _topLevelObject;
    id _objectBeingTested;
    id _rangeContainerObject;
    id _moreVars;
}

/// Returns the shared script execution context.
+ (NSScriptExecutionContext *)sharedScriptExecutionContext;

/// The top-level object in the current scripting context.
@property (nullable, retain) id topLevelObject;
/// The object currently being tested by an `NSWhoseSpecifier`.
@property (nullable, retain) id objectBeingTested;
/// The container object for the current range specifier being evaluated.
@property (nullable, retain) id rangeContainerObject;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
