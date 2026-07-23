#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/transform_correction.h>)
//
//  transform_correction.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef transform_correction_h
#define transform_correction_h

#import <ARKit/object.h>

/**
 A correction type to apply for transforms returned from ARKit APIs.
 */
API_AVAILABLE(visionos(26.0), macos(26.0), macCatalyst(26.0))
OS_ENUM(ar_transform_correction,
        intptr_t,
        /// Transforms are unaltered and represent actual locations.
        ar_transform_correction_none = 0,
        /// Transforms are corrected to render over physical objects in passthrough displays.
        ar_transform_correction_rendered)
AR_REFINED_FOR_SWIFT;

#endif // transform_correction_h
#else
#import <ARKitCore/transform_correction.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/transform_correction.h>)