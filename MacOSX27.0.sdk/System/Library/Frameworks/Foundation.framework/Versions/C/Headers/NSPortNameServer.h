/*	NSPortNameServer.h
	Copyright (c) 1993-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSPort;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object-oriented interface to the port registration service used by the distributed objects system.
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
@interface NSPortNameServer : NSObject

/// Returns the default system port name server.
+ (NSPortNameServer *)systemDefaultPortNameServer;

/// Looks up and returns the port registered under the specified name on the local host.
- (nullable NSPort *)portForName:(NSString *)name;

/// Looks up and returns the port registered under the specified name on a given host.
- (nullable NSPort *)portForName:(NSString *)name host:(nullable NSString *)host;

/// Registers a given port as a network service with the specified name.
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

/// Unregisters the port for a given name.
- (BOOL)removePortForName:(NSString *)name;

@end

#if TARGET_OS_OSX || TARGET_OS_IPHONE

/// A port name server that takes and returns instances of ``NSMachPort``.
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// A port name server that takes and returns Mach port objects.
///
/// Port removal functionality is not supported in ``NSMachBootstrapServer``; if you want to cancel a service, you have to destroy the port (invalidate the ``NSMachPort`` given to ``registerPort:name:``).
@interface NSMachBootstrapServer : NSPortNameServer

/// Returns the shared instance of the Mach bootstrap server.
+ (id)sharedInstance;

/// Looks up and returns the port registered under the specified name.
- (nullable NSPort *)portForName:(NSString *)name;

/// Looks up and returns the port registered under the specified name on a given host.
///
/// The bootstrap server is a local-only server; the host parameter must be an empty string or `nil`.
- (nullable NSPort *)portForName:(NSString *)name host:(nullable NSString *)host;

/// Registers a given port as a network service with the specified name.
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

/// Returns the port for the specified service name, requesting the launch of the corresponding service if it is not already running.
- (nullable NSPort *)servicePortWithName:(NSString *)name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

#endif

/// A port name server that takes and returns instances of ``NSMessagePort``.
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// A server takes and returns message ports.
///
/// This port name server takes and returns instances of ``MessagePort``. Port removal functionality is not supported in ``NSMessagePortNameServer``; if you want to cancel a service, you have to destroy the port (invalidate the ``MessagePort`` object given to ``NSPortNameServer/registerPort:name:``).
@interface NSMessagePortNameServer : NSPortNameServer

/// Returns the shared instance of the message port name server.
+ (id)sharedInstance;

/// Looks up and returns the port registered under the specified name.
- (nullable NSPort *)portForName:(NSString *)name;

/// Looks up and returns the port registered under the specified name on a given host.
///
/// This name server is a local-only server; the host parameter must be an empty string or `nil`.
- (nullable NSPort *)portForName:(NSString *)name host:(nullable NSString *)host;

// removePortForName: functionality is not supported in
// this name server; if you want to cancel a service,
// you have to destroy the port (invalidate the
// NSMessagePort given to registerPort:name:).

@end

#if TARGET_OS_OSX

/// @DeprecationSummary {
/// Use ``NSXPCConnection`` instead.
/// }
///
/// A port name server that takes and returns socket ports.
///
/// Port removal functionality is supported by the ``removePortForName:`` method and should be used to remove invalid socket ports.
///
/// Unlike the other port name servers, ``NSSocketPortNameServer`` can operate over a network. By registering your socket ports, you make them available to other computers on the local network without hard-coding the TCP port numbers. Clients just need to know the name of the port.
///
/// ``NSPortNameServer`` is implemented using ``NetService`` and registers ports in the local network domain. The registered name of a port must be unique within the local domain, not just the local host. The name server only supports TCP/IP (either IPv4 or IPv6) sockets.
///
/// > Note:
/// > Prior to OS X 10.2, ``NSSocketPortNameServer`` was inoperable.
API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
@interface NSSocketPortNameServer : NSPortNameServer

/// Returns the shared instance of the socket port name server.
+ (id)sharedInstance;

/// Looks up and returns the port registered under the specified name.
- (nullable NSPort *)portForName:(NSString *)name;

/// Looks up and returns the port registered under the specified name on a given host.
- (nullable NSPort *)portForName:(NSString *)name host:(nullable NSString *)host;

/// Registers a given port as a network service with the specified name.
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

/// Unregisters the port for a given name.
- (BOOL)removePortForName:(NSString *)name;

/// Looks up and returns the port registered under the specified name on a given host, using the specified port number for the name server.
- (nullable NSPort *)portForName:(NSString *)name host:(nullable NSString *)host nameServerPortNumber:(uint16_t)portNumber;

/// Registers a given port as a network service with the specified name and name server port number.
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name nameServerPortNumber:(uint16_t)portNumber;

/// The default port number for the name server.
@property uint16_t defaultNameServerPortNumber;

@end

#endif

NS_HEADER_AUDIT_END(nullability, sendability)
