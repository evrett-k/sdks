/*	NSProtocolChecker.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSProxy.h>
#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that restricts the messages that can be sent to another object (referred to as the checker's delegate).
///
/// A ``NSProtocolChecker`` object can be particularly useful when an object with many methods, only a few of which ought to be remotely accessible, is made available using the distributed objects system.
///
/// A protocol checker acts as a kind of proxy; when it receives a message that is in its designated protocol, it forwards the message to its target and consequently appears to be the target object itself. However, when it receives a message not in its protocol, it raises an ``NSExceptionName/invalidArgumentException`` to indicate that the message isn't allowed, whether or not the target object implements the method.
///
/// Typically, an object that is to be distributed (yet must restrict messages) creates an ``NSProtocolChecker`` for itself and returns the checker rather than returning itself in response to any messages. The object might also register the checker as the root object of an NSConnection.
///
/// The object should be careful about vending references to `self`—the protocol checker will convert a return value of `self` to indicate the checker rather than the object for any messages forwarded by the checker, but direct references to the object (bypassing the checker) could be passed around by other objects.
@interface NSProtocolChecker : NSProxy

/// The protocol object the receiver uses to verify whether a given message should be forwarded to its target.
@property (readonly) Protocol *protocol;

/// The target of the receiver.
@property (nullable, readonly, retain) NSObject *target;

@end

@interface NSProtocolChecker (NSProtocolCheckerCreation)

/// Returns an `NSProtocolChecker` instance that will forward any messages in the given protocol to the given target.
+ (instancetype)protocolCheckerWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;

/// Initializes a newly allocated `NSProtocolChecker` instance that will forward any messages in `aProtocol` to `anObject`, the protocol checker's target.
///
/// The checker can be vended in lieu of `anObject` to restrict the messages that can be sent to `anObject`. If `anObject` is allowed to be freed or dereferenced by clients, the `free` method should be included in `aProtocol`.
///
/// - Parameters:
///   - anObject: The target object.
///   - aProtocol: The protocol to restrict messages to.
- (instancetype)initWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
