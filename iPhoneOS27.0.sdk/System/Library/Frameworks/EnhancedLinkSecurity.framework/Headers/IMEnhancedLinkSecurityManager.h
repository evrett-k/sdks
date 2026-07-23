/*!
 @header     IMEnhancedLinkSecurityManager
 @copyright  Copyright (c) 2026 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         IMEnhancedLinkSecurityManager
 @abstract      Store and check links to be handled with enhanced security
 */
API_AVAILABLE(ios(27.0), macCatalyst(27.0), visionos(27.0), macos(27.0), watchos(27.0), tvos(27.0))
NS_SWIFT_NAME(EnhancedLinkSecurityManager)
@interface IMEnhancedLinkSecurityManager: NSObject


/*!
 @property   sharedManager
 @abstract   Shared instance of IMEnhancedLinkSecurityManager
*/
@property (class, nonatomic, strong, readonly) IMEnhancedLinkSecurityManager *sharedManager;


/*!
 @property   hasURLsRequiringEnhancedSecurity
 @abstract   Whether there are any URLs that currently require enhanced security
*/
@property (nonatomic, assign, readonly) BOOL hasURLsRequiringEnhancedSecurity;

- (instancetype)init NS_UNAVAILABLE;

/*!
@method     requestEnhancedSecurityForURL:
@abstract   Marks a given URL as requiring enhanced security
@param      url  The URL to handle with enhanced security
*/
- (void)requestEnhancedSecurityForURL:(NSURL *)url;

/*!
@method     requestEnhancedSecurityForURLs:
@abstract   Marks the given URLs as requiring enhanced security
@param      urls  A list of URLs to handle with enhanced security
*/
- (void)requestEnhancedSecurityForURLs:(NSArray<NSURL *> *)urls;

/*!
@method     shouldUseEnhancedSecurityForURL:
@abstract   Synchronously check if a given URL should use enhanced security
@param      url  A URL to check if should be handled with enhanced security
@return     Whether the URL should be handled with enhanced security
*/
- (BOOL)shouldUseEnhancedSecurityForURL:(NSURL *)url;

/*!
@method     shouldUseEnhancedSecurityForURL:
@abstract   Asynchronously check if a given URL should use enhanced security
@param      url  The URL to check if should be handled with enhanced security
@param      completion  A completion handler with an argument indicating if the URL should be handled with enhanced security
*/
- (void)shouldUseEnhancedSecurityForURL:(NSURL *)url completion:(void (^)(BOOL))completion;

@end

NS_ASSUME_NONNULL_END
