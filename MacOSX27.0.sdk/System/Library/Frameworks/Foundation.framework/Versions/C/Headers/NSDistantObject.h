/*	NSDistantObject.h
	Copyright (c) 1989-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSProxy.h>

@class Protocol, NSConnection, NSCoder;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// A proxy for objects in other applications or threads.
///
/// When a distant object receives a message, in most cases it forwards the message through its ``NSConnection`` object to the real object in another application, supplying the return value to the sender of the message if one is received, and propagating any exception back to the invoker of the method that raised it.
///
/// ``NSDistantObject`` is a concrete subclass of ``NSProxy``, adding two useful instance methods of its own: ``NSDistantObject/connectionForProxy`` returns the ``NSConnection`` object that handles the receiver; ``setProtocolForProxy:`` establishes the set of methods the real object is known to respond to, saving the network traffic required to determine the argument and return types the first time a particular selector is forwarded to the remote proxy.
///
/// There are two kinds of distant object: local proxies and remote proxies. A local proxy is created by an ``NSConnection`` object the first time an object is sent to another application. It is used by the connection for bookkeeping purposes and should be considered private. The local proxy is transmitted over the network using the ``NSCoding`` protocol to create the remote proxy, which is the object that the other application uses. ``NSDistantObject`` defines methods for an ``NSConnection`` object to create instances, but they're intended only for subclasses to override—you should never invoke them directly. Use the ``NSConnection/rootProxyForConnectionWithRegisteredName:host:`` method of ``NSConnection``, which sets up all the required state for an object-proxy pair.
///
/// > Important:
/// > ``NSDistantObject`` conforms to the ``NSCoding`` protocol, but only supports coding by an ``NSPortCoder``. ``NSDistantObject`` and its subclasses do not support archiving.
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
@interface NSDistantObject : NSProxy <NSCoding> {
    @private
    id         _knownSelectors;
    NSUInteger _wireCount;
    NSUInteger _refCount;
    id         _proto;
    uint16_t   ___2;
    uint8_t    ___1;
    uint8_t    _wireType;
    id         _remoteClass;
}

// Do not attempt to subclass NSDistantObject -- it is futile
// Do not use these next two methods

/// Returns a proxy for the specified target object accessible through the given connection.
+ (nullable id)proxyWithTarget:(id)target connection:(NSConnection *)connection;

/// Initializes the receiver as a proxy for the specified target object accessible through the given connection.
- (nullable instancetype)initWithTarget:(id)target connection:(NSConnection *)connection;

/// Returns a local proxy for the specified target object accessible through the given connection.
+ (id)proxyWithLocal:(id)target connection:(NSConnection *)connection;

/// Initializes the receiver as a local proxy for the specified target object accessible through the given connection.
- (instancetype)initWithLocal:(id)target connection:(NSConnection *)connection;

- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

/// Sets the protocol the receiver uses to determine which messages it can handle.
- (void)setProtocolForProxy:(nullable Protocol *)proto;

/// The connection object used by the receiver.
@property (readonly, retain) NSConnection *connectionForProxy;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
