/*	NSConnection.h
	Copyright (c) 1989-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSMutableData, NSDistantObject, NSException, NSData, NSString, NSNumber;
@class NSPort, NSRunLoop, NSPortNameServer, NSDictionary<KeyType, ObjectType>, NSArray<ObjectType>;
@class NSDistantObjectRequest;
@protocol NSConnectionDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// An object that manages the communication between objects in different threads or between a thread and a process running on a local or remote system.
///
/// Connection objects form the backbone of the distributed objects mechanism and normally operate in the background. You use the methods of ``NSConnection`` explicitly when vending an object to other applications, when accessing such a vended object through a proxy, and when altering default communication parameters. At other times, you simply interact with a vended object or its proxy.
///
/// A single connection object may be shared by multiple threads and used to access a vended object.
NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
@interface NSConnection : NSObject {
    @private
    id		receivePort;
    id		sendPort;
    id          delegate;
    int32_t	busy;
    int32_t	localProxyCount;
    int32_t	waitCount;
    id		delayedRL;
    id		statistics;
    unsigned char isDead;
    unsigned char isValid;
    unsigned char wantsInvalid;
    unsigned char authGen:1;
    unsigned char authCheck:1;
    unsigned char _reserved1:1;
    unsigned char _reserved2:1;
    unsigned char doRequest:1;
    unsigned char isQueueing:1;
    unsigned char isMulti:1;
    unsigned char invalidateRP:1;
    id          ___1;
    id          ___2;
    id          runLoops;
    id		requestModes;
    id          rootObject;
    void *	registerInfo;
    id		replMode;
    id          classInfoImported;
    id		releasedProxies;
    id		reserved;
}

/// A dictionary containing various statistics for the receiver.
///
/// An `NSDictionary` object containing various statistics for the receiver, such as the number of vended objects,
/// the number of requests and replies, and so on. The statistics dictionary should be used only for debugging purposes.
@property (readonly, copy) NSDictionary<NSString *, NSNumber *> *statistics;

/// Returns an array of all existing `NSConnection` objects.
+ (NSArray<NSConnection *> *)allConnections;

/// Returns the default `NSConnection` object for the current thread.
+ (NSConnection *)defaultConnection API_DEPRECATED("", macos(10.0, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns an `NSConnection` object for the specified registered name and host.
+ (nullable instancetype)connectionWithRegisteredName:(NSString *)name host:(nullable NSString *)hostName;

/// Returns an `NSConnection` object for the specified registered name, host, and name server.
+ (nullable instancetype)connectionWithRegisteredName:(NSString *)name host:(nullable NSString *)hostName usingNameServer:(NSPortNameServer *)server;

/// Returns a proxy for the root object of the `NSConnection` object registered under the specified name and host.
+ (nullable NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(nullable NSString *)hostName;

/// Returns a proxy for the root object of the `NSConnection` object registered under the specified name, host, and name server.
+ (nullable NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(nullable NSString *)hostName usingNameServer:(NSPortNameServer *)server;

/// Returns an `NSConnection` object that both listens for contact from external clients and has a designated root object.
+ (nullable instancetype)serviceConnectionWithName:(NSString *)name rootObject:(id)root usingNameServer:(NSPortNameServer *)server API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns an `NSConnection` object that both listens for contact from external clients and has a designated root object, using the default name server.
+ (nullable instancetype)serviceConnectionWithName:(NSString *)name rootObject:(id)root API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The timeout interval for outgoing requests.
@property NSTimeInterval requestTimeout;

/// The timeout interval for replies.
@property NSTimeInterval replyTimeout;

/// The object that the receiver makes available to other applications or threads.
@property (nullable, retain) id rootObject;

/// The receiver's delegate.
///
/// A connection's delegate can process incoming messages itself instead of letting the `NSConnection` object handle them.
/// The delegate can also authenticate messages and accept, deny, or modify new connections.
@property (nullable, assign) id<NSConnectionDelegate> delegate;

/// A Boolean value that indicates whether the receiver handles requests atomically.
@property BOOL independentConversationQueueing;

/// A Boolean value that indicates whether the receiver is known to be valid.
@property (readonly, getter=isValid) BOOL valid;

/// The proxy for the root object of the receiver's peer in another application or thread.
///
/// The proxy returned can change between invocations if the peer `NSConnection` object's root object is changed.
///
/// > Note: If the `NSConnection` object uses separate send and receive ports and has no peer, when you invoke
/// > `rootProxy` it will block for the duration of the reply timeout interval, waiting for a reply.
@property (readonly, retain) NSDistantObject *rootProxy;

/// Invalidates the receiver.
- (void)invalidate;

/// Adds `rmode` to the set of run-loop input modes that the receiver uses for connection requests.
///
/// The default input mode is `NSDefaultRunLoopMode`. See the `NSRunLoop` class specification for more information on input modes.
- (void)addRequestMode:(NSString *)rmode;

/// Removes `rmode` from the set of run-loop input modes the receiver uses for connection requests.
- (void)removeRequestMode:(NSString *)rmode;

/// The set of request modes the receiver's receive port is registered for with its `NSRunLoop` object.
@property (readonly, copy) NSArray<NSString *> *requestModes;

/// Registers the receiver with the default `NSPortNameServer` under the given name.
- (BOOL)registerName:(nullable NSString *) name;

/// Registers the receiver with the given name server under the given name.
- (BOOL)registerName:(nullable NSString *) name withNameServer:(NSPortNameServer *)server;

/// Returns an `NSConnection` object initialized with the specified send and receive ports.
+ (nullable instancetype)connectionWithReceivePort:(nullable NSPort *)receivePort sendPort:(nullable NSPort *)sendPort;

/// Returns an object representing an ongoing conversation triggered by a received message.
+ (nullable id)currentConversation;

/// Initializes and returns an `NSConnection` object initialized with the specified send and receive ports.
- (nullable instancetype)initWithReceivePort:(nullable NSPort *)receivePort sendPort:(nullable NSPort *)sendPort;

/// The port on which the receiver sends messages.
@property (readonly, retain) NSPort *sendPort;

/// The port on which the receiver receives messages.
@property (readonly, retain) NSPort *receivePort;

/// Configures the receiver to allow requests from multiple threads to the remote object, without requiring each thread to maintain its own connection.
- (void)enableMultipleThreads;

/// A Boolean value that indicates whether the receiver supports requests from multiple threads.
@property (readonly) BOOL multipleThreadsEnabled;

/// Adds the specified run loop to the list of run loops on which the receiver listens for incoming messages.
- (void)addRunLoop:(NSRunLoop *)runloop;

/// Removes the specified run loop from the list of run loops on which the receiver listens for incoming messages.
- (void)removeRunLoop:(NSRunLoop *)runloop;

/// Configures the receiver to use a new thread for its connection.
- (void)runInNewThread;

/// The proxies for all remote objects that have been received over the connection but have not yet been deallocated.
@property (readonly, copy) NSArray *remoteObjects;

/// All local objects that are being vended over the connection.
@property (readonly, copy) NSArray *localObjects;

/// Dispatches Distributed Objects component data received over the wire.
///
/// NSPort subclasses should use this method to ask a connection object to dispatch Distributed Objects component data.
/// This will decode the data, authenticate, and send the message.
- (void)dispatchWithComponents:(NSArray *)components API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

/// The run loop mode that `NSConnection` objects use for waiting for replies.
FOUNDATION_EXPORT NSString * const NSConnectionReplyMode NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));

/// Posted when an `NSConnection` object is deallocated or when it's notified that its port has been invalidated.
FOUNDATION_EXPORT NSString * const NSConnectionDidDieNotification NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));


API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// An interface for interacting with low-level, interprocess connections.
///
/// The ``NSConnectionDelegate`` protocol defines the optional methods implemented by delegates of ``NSConnection`` objects.
@protocol NSConnectionDelegate <NSObject>
@optional

/// Informs the delegate that a new connection object has been created.
///
/// Use the `NSConnectionDidInitializeNotification` notification instead of this delegate method if possible.
- (BOOL)makeNewConnection:(NSConnection *)conn sender:(NSConnection *)ancestor;

/// Asks the delegate whether it will allow a new connection to be created.
///
/// Use the `NSConnectionDidInitializeNotification` notification instead of this delegate method if possible.
- (BOOL)connection:(NSConnection *)ancestor shouldMakeNewConnection:(NSConnection *)conn;

/// Returns authentication data for the given components.
- (NSData *)authenticationDataForComponents:(NSArray *)components;

/// Returns a Boolean value that indicates whether given authentication data is valid for a given set of components.
///
/// Use this message for validation of incoming messages. An `NSConnection` object raises an
/// `NSFailedAuthenticationException` on receipt of a remote message the delegate doesn't authenticate.
- (BOOL)authenticateComponents:(NSArray *)components withData:(NSData *)signature;

/// Allows the delegate to create a new conversation object for the given connection.
- (id)createConversationForConnection:(NSConnection *)conn;

/// Allows the delegate to intercept distant object requests.
///
/// - Returns: `YES` if the request was handled by the delegate, `NO` if the request should proceed as if the delegate did not intercept it.
- (BOOL)connection:(NSConnection *)connection handleRequest:(NSDistantObjectRequest *)doreq;

@end

/// The name of an exception raised in case of authentication failure.
FOUNDATION_EXPORT NSString * const NSFailedAuthenticationException NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));

/// Posted when an `NSConnection` object is initialized.
FOUNDATION_EXPORT NSString * const NSConnectionDidInitializeNotification NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));

/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// An object used by the distributed objects system to help handle invocations between different processes.
///
/// Do not create ``NSDistantObjectRequest`` objects directly. Unless you are getting involved with the low-level details of distributed objects, there should never be a need to access an ``NSDistantObjectRequest``. To intercept and possibly process requests yourself, implement the ``NSConnection`` delegate method ``NSConnectionDelegate/connection:handleRequest:``.
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
@interface NSDistantObjectRequest : NSObject

/// The invocation object for the request.
@property (readonly, retain) NSInvocation *invocation;

/// The connection over which the request was received.
@property (readonly, retain) NSConnection *connection;

/// The token object representing the conversation in which the request was received.
@property (readonly, retain) id conversation;

/// Sends a reply back to the sender of the request, signaling an exception if one is provided.
- (void)replyWithException:(nullable NSException *)exception;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
