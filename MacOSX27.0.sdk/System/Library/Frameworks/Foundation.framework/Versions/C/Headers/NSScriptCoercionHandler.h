/*	NSScriptCoercionHandler.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A mechanism for converting one kind of scripting data to another.
///
/// A shared instance of this class coerces (converts) object values to objects of another class using information supplied by classes that register with it. Coercions frequently are required during key-value coding.
@interface NSScriptCoercionHandler : NSObject {
    @private
    id _coercers;
}

/// Returns the shared coercion handler.
+ (NSScriptCoercionHandler *)sharedCoercionHandler;

/// Attempts to coerce the given value to the given class.
- (nullable id)coerceValue:(id)value toClass:(Class)toClass;

/// Registers a coercer to convert values from one class to another.
///
/// The selector should take two arguments: the first is the value to be converted, and the second is the class to convert it to. The coercer should typically be a class object and the selector a factory method.
- (void)registerCoercer:(id)coercer selector:(SEL)selector toConvertFromClass:(Class)fromClass toClass:(Class)toClass;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
