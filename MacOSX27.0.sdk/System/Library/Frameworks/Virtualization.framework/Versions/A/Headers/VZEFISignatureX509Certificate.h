//
//  VZEFISignatureX509Certificate.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Security/Security.h>
#import <Virtualization/VZEFISignature.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A class that represents a Unified Extensible Firmware Interface (UEFI) signature based on an X.509 certificate.

 This class represents a signature entry containing a DER-encoded X.509 certificate. The Platform Key (PK), the Key Exchange Key (KEK)
 database, and the allowed signature database (db) commonly use X.509 certificates.

 ## Topics

 ## See Also

  - ``VZEFISignature``
  - ``VZEFISignatureList``

*/
VZ_EXPORT API_AVAILABLE(macos(27.0)) NS_REFINED_FOR_SWIFT
@interface VZEFISignatureX509Certificate : VZEFISignature

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Creates a signature from an X.509 certificate.

 - Parameter certificate: An X.509 certificate object.
*/
- (instancetype)initWithCertificate:(SecCertificateRef)certificate NS_DESIGNATED_INITIALIZER;

/**
 The X.509 certificate contained in this signature.
*/
@property (readonly) SecCertificateRef certificate;

@end

NS_ASSUME_NONNULL_END
