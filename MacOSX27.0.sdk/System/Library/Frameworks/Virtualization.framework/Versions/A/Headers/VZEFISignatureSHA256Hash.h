//
//  VZEFISignatureSHA256Hash.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZEFISignature.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A class that represents a Unified Extensible Firmware Interface (UEFI) signature based on a SHA-256 cryptographic hash.

 This class represents a signature entry containing a SHA-256 hash value. The forbidden signature database (dbx) uses
 hash-based signatures to block specific UEFI binaries that OS vendors have revoked or found to be vulnerable.

 ## Topics

 ## See Also

  - ``VZEFISignature``
  - ``VZEFISignatureList``

*/
VZ_EXPORT API_AVAILABLE(macos(27.0)) NS_REFINED_FOR_SWIFT
@interface VZEFISignatureSHA256Hash : VZEFISignature

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Creates a signature from SHA-256 hash data.
 - Parameter data: Data containing the SHA-256 hash.

 The hash data must be exactly 32 bytes in length. If data isn't exactly 32 bytes, the framework raises an exception.
*/
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

/**
 The SHA-256 hash data this signature contains.
*/
@property (readonly, copy) NSData *data;

@end

NS_ASSUME_NONNULL_END
