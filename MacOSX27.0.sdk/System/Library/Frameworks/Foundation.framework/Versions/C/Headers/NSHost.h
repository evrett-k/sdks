/*	NSHost.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray<ObjectType>, NSMutableArray;

/**
 * DEPRECATION NOTICE
 *
 * If you’re using `NSHost` to resolve DNS names so that you can connect to a
 * service, switch to a connect-by-name API, for example, `nw_connection`.
 *
 * If you have other DNS resolution needs, switch to <dns_sd.h>.
 */

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A representation of an individual host on the network.
///
/// The ``NSHost`` class provides methods to access the network name and address information for a host. Instances of the ``NSHost`` class represent individual _hosts_ on a network. Use ``NSHost`` objects to get the current host's names and addresses and to look up other hosts by name or by address.
///
/// To create an ``NSHost`` object, use the ``current()``, ``init(address:)``, or ``init(name:)`` class methods (don't use `alloc` and `init`). These methods use available network administration services to discover all names and addresses for the host requested. They don't attempt to contact the host itself, however. This approach avoids untimely delays due to a host being unavailable, but it may result in incomplete information about the host.
///
/// An ``NSHost`` object contains all of the network addresses and names discovered for a given host by the network administration services. Each ``NSHost`` object may contain several addresses and have more than one name. If an ``NSHost`` object has more than one name, the additional names are variations on the same name, typically the basic host name plus the fully qualified domain name. For example, with a host name `"sales"` in the domain `"anycorp.com"`, an ``NSHost`` object can hold both the names `"sales"` and `"sales.anycorp.com"`.
///
/// ``NSHost`` methods are thread-safe.
///
/// @DeprecationSummary {
///     Use Network framework instead; see the deprecation notice in `<Foundation/NSHost.h>`.
/// }
API_DEPRECATED("Use Network framework instead, see deprecation notice in <Foundation/NSHost.h>", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NSHost : NSObject {
@private
    NSArray 	*names;
    NSArray 	*addresses;
    id		reserved;
}

/// Returns an ``NSHost`` object representing the host the process is running on.
///
/// This method executes synchronously. The execution time of this method can be highly variable, depending on the local network configuration, and may block for several seconds if the network is unreachable. To avoid blocking execution on the main thread, you should call this method in an ``Operation`` or _Grand Central Dispatch_ block that executes asynchronously in the background.
///
/// - Returns: `NSHost` object for the process's host.
+ (instancetype)currentHost;

/// Returns a host with a specific name.
///
/// - Parameters:
///   - name: Name of the host to look up. Can be either a simple hostname, such as `"sales"`, or a fully qualified domain name, such as `"sales.anycorp.com"`.
/// - Returns: The host named `name`.
+ (instancetype)hostWithName:(nullable NSString *)name;

/// Returns the `NSHost` with the Internet address `address`.
///
/// - Parameters:
///   - address: Network address to look up. For example, `"127.0.0.1"` or `"fe80::1"`.
/// - Returns: The host for `address`.
+ (instancetype)hostWithAddress:(NSString *)address;

/// Indicates whether the receiver represents the same host as another `NSHost` object.
///
/// - Parameters:
///   - aHost: Host to compare the receiver to.
/// - Returns: `YES` when the receiver and `aHost` share at least one network address; `NO` otherwise.
- (BOOL)isEqualToHost:(NSHost *)aHost;

/// One of the hostnames associated with the receiver.
///
/// Can be either a simple hostname, such as `"sales"`, or a fully qualified domain name, such as `"sales.anycorp.com"`.
@property (nullable, readonly, copy) NSString *name;

/// All of the hostnames associated with the receiver.
@property (readonly, copy) NSArray<NSString *> *names;

/// One of the addresses associated with the receiver, such as `"192.42.172.1"` or `"fe80::1"`.
@property (nullable, readonly, copy) NSString *address;

/// All of the addresses associated with the receiver, including IPv6 and IPv4 addresses.
@property (readonly, copy) NSArray<NSString *> *addresses;

/// The localized name for the host.
///
/// This is the name displayed in the Finder sidebar and the Sharing preference panel.
///
/// This property only returns a value when sent to the ``currentHost`` instance; all other instances currently return `nil`.
///
/// This property is key-value observable.
@property (nullable, readonly, copy) NSString *localizedName API_AVAILABLE(macos(10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sets whether the host cache is enabled.
+ (void)setHostCacheEnabled:(BOOL)flag API_DEPRECATED("Caching no longer supported", macos(10.0,10.7)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns whether the host cache is enabled.
+ (BOOL)isHostCacheEnabled API_DEPRECATED("Caching no longer supported", macos(10.0,10.7)) API_UNAVAILABLE(ios, watchos, tvos);

/// Clears the host cache.
+ (void)flushHostCache API_DEPRECATED("Caching no longer supported", macos(10.0,10.7)) API_UNAVAILABLE(ios, watchos, tvos);
@end

NS_HEADER_AUDIT_END(nullability, sendability)
