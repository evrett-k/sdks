/*	NSURLHandle.h
	Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/
 
#import <Foundation/NSObject.h>

/* NSURLHandle has been deprecated; please use NSURLConnection instead. */

@class NSURLHandle, NSMutableArray, NSMutableData, NSData, NSURL;

	// HTTP Specific Property Keys
/// The HTTP status code for the response.
FOUNDATION_EXPORT NSString * const NSHTTPPropertyStatusCodeKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// The HTTP status reason phrase for the response.
FOUNDATION_EXPORT NSString * const NSHTTPPropertyStatusReasonKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// The HTTP version of the server's response.
FOUNDATION_EXPORT NSString * const NSHTTPPropertyServerHTTPVersionKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// The headers from an HTTP redirection response.
FOUNDATION_EXPORT NSString * const NSHTTPPropertyRedirectionHeadersKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// The body data from an HTTP error response page.
FOUNDATION_EXPORT NSString * const NSHTTPPropertyErrorPageDataKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// An `NSDictionary` containing proxy information to use in place of proxy identified in SystemConfiguration.framework.
///
/// To avoid any proxy use, pass an empty dictionary.
FOUNDATION_EXPORT NSString * const NSHTTPPropertyHTTPProxy API_DEPRECATED("", macos(10.2, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

// FTP Specific Property Keys
	// All keys are optional.  The default configuration allows an
	// anonymous, passive-mode, one-off transfer of the specified URL.
/// The FTP user login name. Default is `"anonymous"`.
FOUNDATION_EXPORT NSString * const NSFTPPropertyUserLoginKey API_DEPRECATED("", macos(10.2, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// The FTP user password. Default is `"NSURLHandle@apple.com"`.
FOUNDATION_EXPORT NSString * const NSFTPPropertyUserPasswordKey API_DEPRECATED("", macos(10.2, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// An `NSNumber` boolean indicating whether to use active transfer mode. Default is `NO` (passive mode).
FOUNDATION_EXPORT NSString * const NSFTPPropertyActiveTransferModeKey API_DEPRECATED("", macos(10.2, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// An `NSNumber` indicating the file offset for FTP transfers. Default is `0`.
FOUNDATION_EXPORT NSString * const NSFTPPropertyFileOffsetKey API_DEPRECATED("", macos(10.2, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// An `NSDictionary` containing proxy information to use in place of proxy identified in SystemConfiguration.framework.
///
/// To avoid any proxy use, pass an empty dictionary.
FOUNDATION_EXPORT NSString * const NSFTPPropertyFTPProxy API_DEPRECATED("", macos(10.3, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);



/// Constants returned by ``NSURLHandle/status`` that indicate the status of an URL handle.
typedef NS_ENUM(NSUInteger, NSURLHandleStatus) {
    /// The resource data has not been loaded.
    NSURLHandleNotLoaded = 0,
    /// The resource data was successfully loaded.
    NSURLHandleLoadSucceeded,
    /// The resource data is in the process of loading.
    NSURLHandleLoadInProgress,
    /// The resource data failed to load.
    NSURLHandleLoadFailed
};

/// The interface implemented by URL handle clients.
///
/// ``NSURLHandleClient`` is deprecated in macOS 10.4 and later. Applications that are intended for deployment in macOS 10.3 or later should use ``NSURLConnection`` or ``NSURLDownload`` instead; see <doc:url-loading-system>.
API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos)
@protocol NSURLHandleClient
/// Sent when new resource data becomes available.
- (void)URLHandle:(NSURLHandle *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// Sent when a resource begins loading.
- (void)URLHandleResourceDidBeginLoading:(NSURLHandle *)sender API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// Sent when a resource finishes loading.
- (void)URLHandleResourceDidFinishLoading:(NSURLHandle *)sender API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// Sent when a resource loading is canceled.
- (void)URLHandleResourceDidCancelLoading:(NSURLHandle *)sender API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// Sent when a resource fails to load.
- (void)URLHandle:(NSURLHandle *)sender resourceDidFailLoadingWithReason:(NSString *)reason API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);
@end

/// An object that accesses and manages resource data indicated by a URL.
///
/// > Important:
/// > ``NSURLHandle`` is deprecated in macOS 10.4 and later. Use ``URLSession`` instead.
///
/// A single ``NSURLHandle`` can service multiple equivalent ``NSURL`` objects, but only if these URLs map to the same resource.
///
/// Cocoa provides private concrete subclasses to handle HTTP and file URL schemes. If you want to implement support for additional URL schemes, you would do so by creating a subclass of `NSURLHandle`. You can use `NSURL` and `NSURLHandle` to download from FTP sites without subclassing.
///
/// @DeprecationSummary {
///     Use ``URLSession`` instead.
/// }
@interface NSURLHandle:NSObject
{
    NSMutableArray *_clients;
    id _data;
    NSURLHandleStatus _status;
    NSInteger _reserved;
}

/// Registers a subclass of `NSURLHandle` as an available subclass for handling URLs.
///
/// - Parameters:
///   - anURLHandleSubclass: The new subclass to register as an available subclass.
+ (void)registerURLHandleClass:(Class)anURLHandleSubclass API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the class of the URL handle that will be used for a specified URL.
///
/// - Parameters:
///   - anURL: The URL in question.
/// - Returns: The class of the URL handle that will be used for `anURL`.
///
/// Subclasses of `NSURLHandle` must be registered via `+registerURLHandleClass:`. The subclass is determined by asking the list of registered subclasses if it `+canInitWithURL:`; the first class to respond `YES` is selected.
+ (Class)URLHandleClassForURL:(NSURL *)anURL API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the status of the receiver.
///
/// - Returns: The status of the receiver, as an `NSURLHandleStatus` value.
- (NSURLHandleStatus)status API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns a string describing the reason a load failed.
///
/// - Returns: A string describing the reason a load failed. If the load has not failed, returns `nil`.
- (NSString *)failureReason API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Adds a client of the URL handle.
///
/// - Parameters:
///   - client: An object conforming to the `NSURLHandleClient` protocol.
- (void)addClient:(id <NSURLHandleClient>)client API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Removes `client` as an `NSURLHandleClient` of the receiver.
///
/// - Parameters:
///   - client: An object conforming to the `NSURLHandleClient` protocol.
- (void)removeClient:(id <NSURLHandleClient>)client API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Loads the receiver's data in the background.
///
/// Each subclass determines its own loading policy. Clients should not assume that multiple background loads can proceed simultaneously.
- (void)loadInBackground API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Called to cancel a load currently in progress.
///
/// This method is provided mainly for subclasses that wish to take some action before a background load is canceled. This method should invoke `super`'s implementation before returning.
- (void)cancelLoadInBackground API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the resource data managed by the receiver, loading it if necessary.
///
/// - Returns: The resource data managed by the receiver.
///
/// Blocks until all data is available.
- (NSData *)resourceData API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Immediately returns the currently available resource data managed by the URL handle.
///
/// - Returns: The currently available resource data managed by the URL handle. Returns `nil` if a previous attempt to load the data failed.
- (NSData *)availableResourceData API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the expected length of the resource data if it is provided by the server.
///
/// - Returns: The expected size of the resource data, in bytes. A negative value if the length is unknown.
///
/// This information can be queried before all the data has arrived.
- (long long) expectedResourceDataSize API_DEPRECATED("", macos(10.3, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Flushes any cached data for the URL served by this URL handle.
- (void)flushCachedData API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Called when a background load fails. Sends the failure message to clients.
///
/// - Parameters:
///   - reason: The status message indicating why the background load failed.
///
/// This method is provided mainly for subclasses that wish to take some action before passing along the failure notification to the URL client. This method should invoke `super`'s implementation before returning.
- (void)backgroundLoadDidFailWithReason:(NSString *)reason API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Appends new data to the receiver's resource data.
///
/// - Parameters:
///   - newBytes: The newly loaded bytes.
///   - yorn: `YES` if `newBytes` contains the last piece of data for the URL, `NO` otherwise.
///
/// You should call this method when loading the resource data in the background.
- (void)didLoadBytes:(NSData *)newBytes loadComplete:(BOOL)yorn API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns whether a URL handle can be initialized with a given URL.
///
/// - Parameters:
///   - anURL: The URL in question.
/// - Returns: `YES` if a URL handle can be initialized with `anURL`, `NO` otherwise.
///
/// Subclasses of `NSURLHandle` must override this method to identify which URLs they can service.
+ (BOOL)canInitWithURL:(NSURL *)anURL API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the URL handle from the cache that has serviced the specified URL or another identical URL.
///
/// - Parameters:
///   - anURL: The URL whose cached URL handle is desired.
/// - Returns: The URL handle from the cache that has serviced `anURL` or another identical URL. Returns `nil` if there is no such handle.
///
/// Subclasses of `NSURLHandle` must override this method.
+ (NSURLHandle *)cachedHandleForURL:(NSURL *)anURL API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Initializes a newly created URL handle with the specified URL.
///
/// - Parameters:
///   - anURL: The URL for the new handle.
///   - willCache: `YES` if the URL handle should cache its data and respond to requests from equivalent URLs for the cached data, `NO` otherwise.
///
/// Subclasses of `NSURLHandle` must override this method.
- initWithURL:(NSURL *)anURL cached:(BOOL)willCache API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the property for the specified key.
///
/// - Parameters:
///   - propertyKey: The key of the desired property.
/// - Returns: The value associated with `propertyKey`. Returns `nil` if there is no such key.
///
/// Subclasses of `NSURLHandle` must override this method.
- (id)propertyForKey:(NSString *)propertyKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the property for the specified key only if the value is already available; that is, the client doesn't need to do any work.
///
/// - Parameters:
///   - propertyKey: The key of the desired property.
/// - Returns: The value associated with `propertyKey`. Returns `nil` if there is no such key or if the client would have to do work to fetch the property.
- (id)propertyForKeyIfAvailable:(NSString *)propertyKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sets the property of the receiver's resource for a specified key to the specified value.
///
/// - Parameters:
///   - propertyValue: The new value for the property.
///   - propertyKey: The key of the desired property.
/// - Returns: `YES` if the modification was successful, `NO` otherwise.
///
/// Must be overridden by subclasses.
- (BOOL)writeProperty:(id)propertyValue forKey:(NSString *)propertyKey API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Attempts to write a specified set of data to the location specified by the receiver's URL.
///
/// - Parameters:
///   - data: The data to write.
/// - Returns: `YES` if successful, `NO` otherwise.
///
/// Must be overridden by subclasses.
- (BOOL)writeData:(NSData *)data API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Loads the receiver's data synchronously.
///
/// - Returns: The loaded data.
///
/// Called by `-resourceData`. Subclasses of `NSURLHandle` must override this method.
- (NSData *)loadInForeground API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Called when a background load begins.
///
/// This method is provided mainly for subclasses that wish to take advantage of the superclass failure-reporting mechanism.
- (void)beginLoadInBackground API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Halts any background loading.
///
/// This method is called by `-cancelLoadInBackground`.
- (void)endLoadInBackground API_DEPRECATED("", macos(10.0, 10.4)) API_UNAVAILABLE(ios, watchos, tvos);

@end

