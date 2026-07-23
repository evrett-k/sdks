//
//  VZEFISignature.h
//  Virtualization
//
//  Copyright © 2025-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A base class that represents a Unified Extensible Firmware Interface (UEFI) signature.

 Don't instantiate `VZEFISignature` objects directly; instead, create an instance of one of its subclasses, such as
 ``VZEFISignatureX509Certificate`` or ``VZEFISignatureSHA256Hash``.

## Topics

## See Also

  - ``VZEFISignatureX509Certificate``
  - ``VZEFISignatureSHA256Hash``
  - ``VZEFISignatureList``

*/
VZ_EXPORT API_AVAILABLE(macos(27.0)) NS_REFINED_FOR_SWIFT
@interface VZEFISignature : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
