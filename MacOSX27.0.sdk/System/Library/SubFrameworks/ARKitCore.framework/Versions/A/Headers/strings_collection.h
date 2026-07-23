//
//  strings_collection.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef strings_h
#define strings_h

#import <ARKitCore/object.h>

#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Strings Collection

/**
 A collection of strings.
 */
AR_OBJECT_DECL(ar_strings)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macos(26.0), macCatalyst(26.0));

API_UNAVAILABLE_BEGIN(macos);
API_UNAVAILABLE_BEGIN(macCatalyst);

/**
 Returns the number of strings in this collection.

 - Parameter strings: The strings collection.

 - Returns: Count of strings in the collection.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN size_t ar_strings_get_count(ar_strings_t strings) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating a collection of strings.

 - Parameter string: An UTF-8 encoded string representation.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (^ar_strings_enumerator_t)(const char *string) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of strings.

 - Parameters:
   - strings: Strings collection.
   - strings_enumerator: The enumerator handler.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_strings_enumerate_strings(ar_strings_t strings, ar_strings_enumerator_t strings_enumerator) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of strings.

 - Parameters:
   - context: The application-defined context.
   - string: An UTF-8 encoded string representation.

 - Returns: `true` to continue enumerating, or `false` to stop enumerating.
*/
API_AVAILABLE(visionos(26.0))
typedef bool (*ar_strings_enumerator_function_t)(void *_Nullable context, const char *string) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of strings using a function.

 - Parameters:
   - strings: Strings collection.
   - context: The application-defined context parameter to pass to the function.
   - strings_enumerator_function: The enumerator handler.
*/
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_strings_enumerate_strings_f(ar_strings_t strings,
                                              void *_Nullable context,
                                              ar_strings_enumerator_function_t strings_enumerator_function) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macCatalyst
API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // strings_h
