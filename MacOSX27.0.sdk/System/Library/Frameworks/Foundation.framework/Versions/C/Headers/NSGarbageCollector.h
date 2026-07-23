/*	NSGarbageCollector.h
	Copyright (c) 2006-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A convenient interface to the garbage collection system.
///
/// > Important: Garbage collection is deprecated in OS X 10.8. Use ARC instead.
API_DEPRECATED("Building Garbage Collected apps is no longer supported.", macos(10.5, 10.10)) API_UNAVAILABLE(ios, watchos, tvos)
NS_AUTOMATED_REFCOUNT_UNAVAILABLE
NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported")
@interface NSGarbageCollector : NSObject

/// Returns the default garbage collector.
+ (id)defaultCollector;

/// Returns a Boolean value that indicates whether a collection is currently in progress.
- (BOOL)isCollecting API_DEPRECATED("", macos(10.0, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/// Temporarily disables collections.
- (void)disable;

/// Enables collections after a prior disabling.
- (void)enable;

/// Returns a Boolean value that indicates whether garbage collection is currently enabled.
- (BOOL)isEnabled;

/// Tells the receiver to collect if memory consumption thresholds have been exceeded.
- (void)collectIfNeeded;

/// Tells the receiver to perform a full collection.
- (void)collectExhaustively;

/// Specifies that a given pointer will not be collected.
- (void)disableCollectorForPointer:(const void *)ptr;

/// Specifies that a given pointer may be collected.
- (void)enableCollectorForPointer:(const void *)ptr;

/// Returns a memory zone that is not scanned by the garbage collector.
- (NSZone *)zone;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
