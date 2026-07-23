//
//  VZEFISignatureList.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZEFISignature;

/**
 A class that represents a Unified Extensible Firmware Interface (UEFI) signature list.

 This class represents a UEFI signature list that can contain X.509 certificates or SHA-256 hashes.

 UEFI firmware stores the contents of signature lists in the Key Exchange Key (KEK) signature database,
 allowed signature database (db), and the forbidden signature database (dbx).

 ## Topics

 ## See Also

  - ``VZEFISignatureDatabaseConfiguration``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0)) NS_SWIFT_SENDABLE
@interface VZEFISignatureList : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Creates a signature list from a file.

 - Parameters:
    - url: The URL to a file containing signature data.
    - error: If not `nil`, assigned with the error if the initialization fails.

    The file can contain a DER-encoded X.509 certificate, UEFI signature lists in binary format, or a
    cryptographic hash (SHA-256).

    The format of the input data is automatically detected and parsed. If the file contains
    UEFI signature lists, it extracts all signatures from the lists. If the file contains a certificate,
    it creates a signature list with a single certificate entry. If the file contains a hash,
    it creates a signature list with a single SHA-256 hash entry.
 */
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url error:(NSError * _Nullable *)error NS_DESIGNATED_INITIALIZER;

/**
 Creates a signature list from the provided signatures.

 - Parameter: signatures An array of EFI signatures. This array can contain a mix of X.509 certificates and cryptographic hashes (SHA-256).
 - Returns: A new signature list object containing the specified signatures.
 */
- (instancetype)initWithSignatures:(NSArray<VZEFISignature *> *)signatures NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/**
 An array of EFI signatures this signature list contains.
 */
@property (readonly, copy) NSArray<VZEFISignature *> *signatures NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
