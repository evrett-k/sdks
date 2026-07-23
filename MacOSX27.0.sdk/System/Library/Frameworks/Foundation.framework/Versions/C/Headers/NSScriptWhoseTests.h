/*
	NSScriptWhoseTests.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;
@class NSScriptObjectSpecifier;
@class NSSpecifierTest;
@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that specify comparison operations for use in script whose tests.
typedef NS_ENUM(NSUInteger, NSTestComparisonOperation) {
    /// Tests for equality.
    NSEqualToComparison = 0,
    /// Tests for less-than-or-equal-to.
    NSLessThanOrEqualToComparison,
    /// Tests for less-than.
    NSLessThanComparison,
    /// Tests for greater-than-or-equal-to.
    NSGreaterThanOrEqualToComparison,
    /// Tests for greater-than.
    NSGreaterThanComparison,
    /// Tests whether a string begins with another string.
    NSBeginsWithComparison,
    /// Tests whether a string ends with another string.
    NSEndsWithComparison,
    /// Tests whether a string contains another string.
    NSContainsComparison
};

/// An abstract class that provides the basis for testing specifiers one at a time or in groups.
///
/// `NSScriptWhoseTest` is an abstract class whose sole method is ``isTrue()``. Two concrete subclasses of `NSScriptWhoseTest` generate objects representing Boolean expressions comparing one object with another and objects representing multiple Boolean expressions connected by logical operators (`OR`, `AND`, `NOT`). These classes are, respectively, ``NSSpecifierTest`` and ``NSLogicalTest``. In evaluating itself, an ``NSWhoseSpecifier`` invokes the ``isTrue()`` method of its "test" object.
///
/// You shouldn't need to subclass `NSScriptWhoseTest`, and you should rarely need to subclass one of its subclasses.
@interface NSScriptWhoseTest : NSObject <NSCoding> {}

/// Returns a Boolean value that indicates whether this test evaluates to true.
- (BOOL)isTrue;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

@end


/// A script whose test that combines other tests using logical AND, OR, or NOT operations.
@interface NSLogicalTest : NSScriptWhoseTest {
    @private
    int _operator;
    id _subTests;
}

/// Initializes a logical AND test with the given subtests.
- (instancetype)initAndTestWithTests:(NSArray<NSSpecifierTest *> *)subTests NS_DESIGNATED_INITIALIZER;
/// Initializes a logical OR test with the given subtests.
- (instancetype)initOrTestWithTests:(NSArray<NSSpecifierTest *> *)subTests NS_DESIGNATED_INITIALIZER;
/// Initializes a logical NOT test with the given subtest.
- (instancetype)initNotTestWithTest:(NSScriptWhoseTest *)subTest NS_DESIGNATED_INITIALIZER;

@end


/// A script whose test that compares an object specifier against a value using a comparison operator.
///
/// The specifiers are evaluated normally before the comparison operator is evaluated.
@interface NSSpecifierTest : NSScriptWhoseTest {
    @private
    NSTestComparisonOperation _comparisonOperator;
    NSScriptObjectSpecifier *_object1;
    id _object2;
}
- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;
/// Initializes a specifier test with an object specifier, comparison operator, and test object.
- (instancetype)initWithObjectSpecifier:(nullable NSScriptObjectSpecifier *)obj1 comparisonOperator:(NSTestComparisonOperation)compOp testObject:(nullable id)obj2 NS_DESIGNATED_INITIALIZER;

@end


@interface NSObject (NSComparisonMethods)
- (BOOL)isEqualTo:(nullable id)object;
    // Implemented using isEqual:. Returns NO if receiver is nil.
- (BOOL)isLessThanOrEqualTo:(nullable id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isLessThan:(nullable id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isGreaterThanOrEqualTo:(nullable id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isGreaterThan:(nullable id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isNotEqualTo:(nullable id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)doesContain:(id)object;
    // Returns nil if receiver is not an NSArray or if array doesn't contain object.
    // This operator is not working against the database.
- (BOOL)isLike:(NSString *)object;
    // argument should be a string using simple shell wildcards (* and ?).
    // (e.g. "Stev*" or "N?XT").
    // Returns NO if receiver is not an NSString.
- (BOOL)isCaseInsensitiveLike:(NSString *)object;
@end


@interface NSObject (NSScriptingComparisonMethods)

//  Often the correct way to compare two objects for scripting is different from the correct way to compare objects programmatically.  This category defines a set of methods that can be implemented to perform the comparison appropriate for scripting that is independant of other existing methods for doing comparisons, like those defined in EOQualifier.h

// If the object1 implements the appropriate one of these methods for the comparison operation, these methods will be used.  If object1 does not implement the appropriate one of these, and object2 the inverted version, and the comparison operator is one of the first five, then the comparison operator is inverted (ie scriptingIsGreaterThan: -> scriptingIsLessThanOrEqualTo:).
// If neither object1 or object2 implement the appropriate one of these selectors, we will fall back on trying to use standard EOQualifier-type methods like isEqualto:, isGreaterThan:, etc... for the first five.

- (BOOL)scriptingIsEqualTo:(id)object;
- (BOOL)scriptingIsLessThanOrEqualTo:(id)object;
- (BOOL)scriptingIsLessThan:(id)object;
- (BOOL)scriptingIsGreaterThanOrEqualTo:(id)object;
- (BOOL)scriptingIsGreaterThan:(id)object;

- (BOOL)scriptingBeginsWith:(id)object;
- (BOOL)scriptingEndsWith:(id)object;
- (BOOL)scriptingContains:(id)object;

@end

NS_HEADER_AUDIT_END(nullability, sendability)


