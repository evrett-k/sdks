//
//  VZEFISignatureDatabaseConfiguration.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZEFISignatureList;

/**
A container for Unified Extensible Firmware Interface (UEFI) Secure Boot signature lists.

This class represents the signature lists used in UEFI Secure Boot configuration. It contains three
separate arrays, one for each UEFI signature database, which are:

 - term Key Exchange Key (KEK): This list contains keys authorized to update the db and dbx databases. The array
    acts as a bridge between the platform owner (who controls the Platform Key) and operating system vendors.
 - term Allowed Signature Database (db): An "allow list" of trusted UEFI applications, bootloaders, and
    drivers. The EFI boot loader allows code signed by these signatures to execute during boot.
 - term Forbidden Signature Database (dbx): A "deny list" of revoked or malicious signatures. The EFI boot loader
    blocks code matching these signatures from running, even if it matches a signature in the db database.

 ## Topics

 ## See Also

  - ``VZEFISignatureList``
  - ``VZEFIVariableStore``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0)) NS_SWIFT_SENDABLE
@interface VZEFISignatureDatabaseConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Creates a signature lists container from signature list objects.

 - Parameters:
    - keyExchangeKeys: An array of ``VZEFISignatureList`` objects for the Key Exchange Key (KEK) database.
      Must contain only X.509 certificates. If any signature list contains SHA-256 hashes, the framework raises an exception.
      This parameter can be empty if you don't need to add KEK signatures.

    - dbSignatures: An array of ``VZEFISignatureList`` objects for the allowed signature database (db).
        This parameter can be empty if you don't need to add allowed signatures.

    - dbxSignatures: An array of ``VZEFISignatureList`` objects for the forbidden signature database (dbx).
      This parameter can be empty if you don't need to add forbidden signatures.

 > Warning: Make sure that the signature data is in the correct format. Applying a malformed configuration may
    corrupt the variable store and render the guest unbootable.

 This initializer creates a container holding signature lists for all three UEFI Secure Boot databases.

 The following example demonstrates the creation of a `VZEFISignatureDatabaseConfiguration` with a fully custom configuration.
 @TabNavigator(){
   @Tab("Swift"){
    ```swift
     do {
         // Load platform key certificate.
         let platformKeyData = try Data(contentsOf: URL(fileURLWithPath: "/path/to/PK.der"))
         guard let platformKey = SecCertificateCreateWithData(nil, platformKeyData as CFData) else {
             // Handle error.
         }

         // Create signature lists from files.
         let kekList = try VZEFISignatureList(contentsOf: URL(fileURLWithPath: "/path/to/KEK.bin"))
         let dbList = try VZEFISignatureList(contentsOf: URL(fileURLWithPath: "/path/to/db.bin"))
         let dbxList = try VZEFISignatureList(contentsOf: URL(fileURLWithPath: "/path/to/dbx.sha256"))
         let signatures = VZEFISignatureDatabaseConfiguration(
             keyExchangeKeys: [kekList],
             dbSignatures: [dbList],
             dbxSignatures: [dbxList]
         )

         // Enable Secure Boot with custom Platform Key.
         try variableStore.enableSecureBoot(platformKey: platformKey)

         // Enroll custom signatures.
         try variableStore.enrollSecureBootSignatures(signatures)
     } catch {
         // Handle error.
     }
    ```
   }

   @Tab("Objective-C"){
    ```objc
     // Load Platform Key certificate.
     NSData *platformKeyData = [NSData dataWithContentsOfURL:[NSURL fileURLWithPath:@"/path/to/PK.der"]];
     SecCertificateRef platformKey = SecCertificateCreateWithData(NULL, (__bridge CFDataRef)platformKeyData);
     if (!platformKey) {
         // Handle error.
     }

     // Create signature lists from files.
     NSError *error;
     VZEFISignatureList *kekList = [[VZEFISignatureList alloc] initWithContentsOfURL:[NSURL fileURLWithPath:@"/path/to/KEK.bin"] error:&error];
     VZEFISignatureList *dbList = [[VZEFISignatureList alloc] initWithContentsOfURL:[NSURL fileURLWithPath:@"/path/to/db.bin"] error:&error];
     VZEFISignatureList *dbxList = [[VZEFISignatureList alloc] initWithContentsOfURL:[NSURL fileURLWithPath:@"/path/to/dbx.sha256"] error:&error];
     if (!kekList || !dbList || !dbxList) {
         // Handle error.
     }
     VZEFISignatureDatabaseConfiguration *signatures = [[VZEFISignatureDatabaseConfiguration alloc] initWithKeyExchangeKeys:@[ kekList ]
                                            dbSignatures:@[ dbList ]
                                            dbxSignatures:@[ dbxList ]];

     // Enable secure boot with custom Platform Key.
     if (![variableStore enableSecureBootWithPlatformKey:platformKey error:&error]) {
         // Handle error.
     }

     // Enroll custom signatures.
     if (![variableStore enrollSecureBootSignatures:signatures error:&error]) {
         // Handle error.
     }

     CFRelease(platformKey);
    ```
   }
 }

 */
- (instancetype)initWithKeyExchangeKeys:(NSArray<VZEFISignatureList *> *)keyExchangeKeys dbSignatures:(NSArray<VZEFISignatureList *> *)dbSignatures dbxSignatures:(NSArray<VZEFISignatureList *> *)dbxSignatures NS_DESIGNATED_INITIALIZER;

/**
 Key Exchange Key (KEK) database entries.
 */
@property (readonly, copy) NSArray<VZEFISignatureList *> *keyExchangeKeys;

/**
 Allowed signature database (db) entries.
 */
@property (readonly, copy) NSArray<VZEFISignatureList *> *dbSignatures;

/**
 Forbidden signature database (dbx) entries.
 */
@property (readonly, copy) NSArray<VZEFISignatureList *> *dbxSignatures;

@end

NS_ASSUME_NONNULL_END
