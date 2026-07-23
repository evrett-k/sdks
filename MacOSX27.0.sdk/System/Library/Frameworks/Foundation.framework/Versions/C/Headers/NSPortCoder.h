/*	NSPortCoder.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>

@class NSConnection, NSPort, NSArray;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead")
@interface NSPortCoder : NSCoder

/// Returns a Boolean value that indicates whether the receiver has been told to encode objects by copying them.
- (BOOL)isBycopy;

/// Returns a Boolean value that indicates whether the receiver has been told to encode objects by reference.
- (BOOL)isByref;

/// Encodes a given port so that a copy or proxy of it can be decoded in another process.
- (void)encodePortObject:(NSPort *)aport;

/// Decodes and returns a port that was previously encoded with `-encodePortObject:`.
- (nullable NSPort *)decodePortObject;

// The following methods are deprecated. Instead of using these methods, NSPort subclasses should look up an NSConnection object using +connectionWithReceivePort:sendPort: and then ask that object to dispatch recieved component data using -dispatchWithComponents:. The NSConnection object will take care of creating the right kind of NSPortCoder object and giving it the data to decode and dispatch.

/// Returns the connection used by the receiver.
- (nullable NSConnection *)connection API_DEPRECATED("", macos(10.0, 10.7), ios(2.0, 2.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

/// Returns an `NSPortCoder` instance initialized with the given ports and components.
+ (id) portCoderWithReceivePort:(nullable NSPort *)rcvPort sendPort:(nullable NSPort *)sndPort components:(nullable NSArray *)comps API_DEPRECATED("", macos(10.0, 10.7), ios(2.0, 2.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

/// Initializes and returns an `NSPortCoder` instance with the given ports and components.
- (id)initWithReceivePort:(nullable NSPort *)rcvPort sendPort:(nullable NSPort *)sndPort components:(nullable NSArray *)comps API_DEPRECATED("", macos(10.0, 10.7), ios(2.0, 2.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

/// Processes the encoded message and delivers it to the intended receiver.
- (void)dispatch API_DEPRECATED("", macos(10.0, 10.7), ios(2.0, 2.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

@end

@interface NSObject (NSDistributedObjects)

@property (readonly) Class classForPortCoder NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));

- (nullable id)replacementObjectForPortCoder:(NSPortCoder *)coder NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
