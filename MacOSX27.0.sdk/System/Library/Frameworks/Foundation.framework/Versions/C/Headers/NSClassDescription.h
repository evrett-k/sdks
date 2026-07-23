/*	NSClassDescription.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSException.h>
#import <Foundation/NSNotification.h>

@class NSString, NSArray<ObjectType>, NSDictionary;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An abstract class that provides the interface for querying the relationships and properties of a class.
@interface NSClassDescription : NSObject

/// Registers an ``NSClassDescription`` object for a given class in the ``NSClassDescription`` cache.
+ (void)registerClassDescription:(NSClassDescription *)description forClass:(Class)aClass;

/// Removes all ``NSClassDescription`` objects from the cache.
+ (void)invalidateClassDescriptionCache;

/// Returns the class description for a given class.
+ (nullable NSClassDescription *)classDescriptionForClass:(Class)aClass;

/// An array of ``NSString`` objects representing the receiver's attribute keys.
@property (readonly, copy) NSArray<NSString *> *attributeKeys;

/// An array of ``NSString`` objects representing the keys for the receiver's to-one relationships.
@property (readonly, copy) NSArray<NSString *> *toOneRelationshipKeys;

/// An array of ``NSString`` objects representing the keys for the receiver's to-many relationships.
@property (readonly, copy) NSArray<NSString *> *toManyRelationshipKeys;

/// Returns the name of the inverse relationship from a relationship specified by a given key.
- (nullable NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

@interface NSObject (NSClassDescriptionPrimitives)

@property (readonly, copy) NSClassDescription *classDescription;
@property (readonly, copy) NSArray<NSString *> *attributeKeys;
@property (readonly, copy) NSArray<NSString *> *toOneRelationshipKeys;
@property (readonly, copy) NSArray<NSString *> *toManyRelationshipKeys;
- (nullable NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

/// Posted when an ``NSClassDescription`` is needed for a class but one has not yet been registered.
FOUNDATION_EXPORT NSNotificationName const NSClassDescriptionNeededForClassNotification;

NS_HEADER_AUDIT_END(nullability, sendability)
