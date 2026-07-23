//
//  VZEFIVariableStore.h
//  Virtualization
//
//  Copyright © 2019-2026 Apple Inc. All rights reserved.
//

#import <Security/Security.h>
#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZEFISignatureDatabaseConfiguration;

/**
 Options for creating a new Extensible Firmware Interface (EFI) variable store.
*/
typedef NS_OPTIONS(NSUInteger, VZEFIVariableStoreInitializationOptions) {
    VZEFIVariableStoreInitializationOptionAllowOverwrite = 1ULL << 0,
} NS_SWIFT_NAME(VZEFIVariableStore.InitializationOptions) API_AVAILABLE(macos(13.0));

/**
 The Extensible Firmware Interface (EFI) variable store.

 The EFI variable store contains NVRAM variables exposed by the EFI ROM.

 ## Topics

 ## See Also

  - ``VZEFIBootLoader``

 */

VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZEFIVariableStore : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 Initializes the variable store from the URL of an existing file.

 - Parameter URL: The URL of the variable store on the local file system.

 To create a new variable store, use ``VZEFIVariableStore/initCreatingVariableStoreAtURL:options:error:``.
 */
- (instancetype)initWithURL:(NSURL *)URL;

/**
 Writes an initialized Extensible Firmware Interface (EFI) variable to a URL on a file system.

 - Parameters:
   - URL: The ``URL`` to write the variable store to on the local file system.
   - options: The initialization options.
   - error: If not `nil`, the framework assigns the error value if the creation fails.

 - Returns: A newly initialized ``VZEFIVariableStore`` on success. If the framework encounters an error, this method returns `nil`, and `error` contains the error.
 */
- (nullable instancetype)initCreatingVariableStoreAtURL:(NSURL *)URL options:(VZEFIVariableStoreInitializationOptions)options error:(NSError **)error;

/**
 The URL of the variable store on the local file system.
 */
@property (readonly, copy) NSURL *URL;

/**
 Enables Secure Boot with an Apple-managed Platform Key.

 - Parameter error: If not nil, assigned with the error if the operation fails.
 - Returns: `YES` if the framework enables Secure Boot successfully, `NO` otherwise.

 This operation overwrites the Platform Key (PK) global variable with an Apple-managed Platform Key,
 sets the "SetupMode" global variable to `0`, and enables Secure Boot.
 */
- (BOOL)enableSecureBootUsingDefaultPlatformKeyWithError:(NSError * _Nullable *)error API_AVAILABLE(macos(27.0));

/**
 Enables Secure Boot with a custom Platform Key.

 - Parameters:
    - platformKey: A custom Platform Key as an X.509 certificate.
    - error: If not `nil`, assigned with the error if the operation fails.

 - Returns: `YES` if the framework enabled Secure Boot successfully, `NO` otherwise.

    This operation overwrites the Platform Key (PK) global variable with the given Platform Key, sets the
    "SetupMode" global variable to `0`, and enables Secure Boot.
 */
- (BOOL)enableSecureBootWithPlatformKey:(SecCertificateRef)platformKey error:(NSError * _Nullable *)error NS_SWIFT_NAME(enableSecureBoot(platformKey:)) API_AVAILABLE(macos(27.0));

/**
 Disables Secure Boot while preserving the existing configuration.

 - Parameter error: If not nil, assigned with the error if the operation fails.
 - Returns:`YES` if the framework disabled Secure Boot successfully, `NO` otherwise.

    This operation disables Secure Boot in the variable store without modifying the applied configuration, as shown in the following example.

 @TabNavigator(){
   @Tab("Swift"){
    ```swift
     do {
         try variableStore.disableSecureBoot()
     } catch {
         // Handle error.
     }
    ```
   }

   @Tab("Objective-C"){
    ```objc
     NSError *error;
     if (![variableStore disableSecureBootWithError:&error]) {
         // Handle error.
     }
    ```
   }
 }

 */
- (BOOL)disableSecureBootWithError:(NSError * _Nullable *)error API_AVAILABLE(macos(27.0));

/**
 Clears any previously applied Secure Boot configuration and disables Secure Boot.

 - Parameter error: If not `nil`, assigned with the error if the operation fails.
 - Returns: `YES`  if the existing configuration was cleared successfully, NO otherwise.

 This operation clears any previously applied Secure Boot configuration, sets the "SetupMode"
  global variable to `1`, and disables Secure Boot in the variable store.

 */
- (BOOL)resetSecureBootWithError:(NSError * _Nullable *)error API_AVAILABLE(macos(27.0));

/**
 Returns a Boolean value that indicates whether Secure Boot is in an enabled state in the variable store.

 - Parameters:
    - enabled: On success, set to YES if Secure Boot is enabled, NO otherwise.
    - error: Assigned with the error if the operation fails, or `nil` upon success.
 - Returns: `YES` if the operation succeeded, `NO` if an error occurred.
 */
- (BOOL)getSecureBootEnabled:(BOOL *)enabled error:(NSError * _Nullable *)error API_AVAILABLE(macos(27.0)) NS_REFINED_FOR_SWIFT;

/**
 Enrolls the default signatures to Secure Boot databases.

  - Parameter error: If not `nil`, assigned with the error if the operation fails.
  - Returns: `YES` if the framework completed the operation successfully, `NO` otherwise.

 This operation adds Microsoft Key Exchange Keys, UEFI CA signatures, and the latest UEFI revocation list
 to the Key Exchange Key (KEK) database, allowed signature database (db), and forbidden signature database
 (dbx) respectively. You can add these signatures before or after enrolling a Platform Key. The framework preserves
 the Platform Key, if present.

 This allows Microsoft-signed Linux distributions to boot with Secure Boot enabled.

 For more information about these signature files, see the [Microsoft Secure Boot Objects repository](https://github.com/microsoft/secureboot_objects).
 */
- (BOOL)enrollDefaultSecureBootSignaturesWithError:(NSError * _Nullable *)error API_AVAILABLE(macos(27.0));

/**
 Enrolls the given signatures to Secure Boot databases.

 - Parameters:
    - signatures: Signatures to enroll in the KEK, db, and dbx signature databases.
    - error: If not `nil`, assigned with the error if the operation fails.
 - Returns: `YES` if the operation completed successfully, `NO` otherwise.

 > Warning: Make sure that the given Secure Boot signatures are valid before enabling Secure Boot, otherwise it may
    render the guest unbootable.

 This operation appends the given signatures to the Key Exchange Key (KEK) database, allowed signature
 database (db), and forbidden signature database (dbx). The method ignores a signature that already exists in the database.
 You can add these signatures before or after enrolling a Platform Key. The framework preserves the Platform Key, if present.

 Call this method multiple times to incrementally add signatures without replacing existing ones.
 */
- (BOOL)enrollSecureBootSignatures:(VZEFISignatureDatabaseConfiguration *)signatures error:(NSError * _Nullable *)error NS_SWIFT_NAME(enrollSecureBootSignatures(_:)) API_AVAILABLE(macos(27.0));

/**
 Returns the currently enrolled Secure Boot signatures in the Key Exchange Key (KEK), allowed signature (db), and forbidden signature (dbx) databases.

 - Parameter error: If not `nil`, assigned with the error if the operation fails.
 - Returns: A `VZEFISignatureDatabaseConfiguration` object containing the enrolled signatures, or `nil` if an error occurred.
 */
- (nullable VZEFISignatureDatabaseConfiguration *)getEnrolledSecureBootSignaturesWithError:(NSError * _Nullable *)error API_AVAILABLE(macos(27.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
