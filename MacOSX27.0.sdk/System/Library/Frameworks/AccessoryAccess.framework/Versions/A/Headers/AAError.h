//
//  AAError.h
//  AccessoryAccess
//
//  Copyright © 2023-2026 Apple Inc. All rights reserved.
//

#import <AccessoryAccess/AADefines.h>

AA_EXPORT NSErrorDomain const AAErrorDomain API_AVAILABLE(macos(27.0));

/*!
 @enum AAErrorCode
 @abstract
    Error type returned by the AccessoryAccess framework.
    The `NSError` domain is `AAErrorDomain`, the code is one of the `AAErrorCode` constants.

    The AccessoryAccess framework can also report errors from other domains when the error originates from a lower level component.

 @constant AAErrorCodeInternal
    An internal error.
 @constant AAErrorCodeAccessoryListenerAlreadyRegistered
    The accessory listener is already registered, and therefore cannot be re-registered.
 @constant AAErrorCodeAccessoryNotAccessible
    The accessory is not accessible since it may already be in use.
 @constant AAErrorCodeInvalidAccessoryState
    API used when the accessory is not in the correct state.
 */
typedef NS_ERROR_ENUM(AAErrorDomain, AAErrorCode) {
    AAErrorCodeInternal NS_SWIFT_NAME(internalError) = 1,
    AAErrorCodeAccessoryListenerAlreadyRegistered = 2,
    AAErrorCodeAccessoryNotAccessible = 3,
    AAErrorCodeInvalidAccessoryState = 4,
} API_AVAILABLE(macos(27.0));
