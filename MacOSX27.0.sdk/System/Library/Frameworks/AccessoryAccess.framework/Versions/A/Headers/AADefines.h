//
//  AADefines.h
//  AccessoryAccess
//
//  Copyright © 2023-2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define AA_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define AA_EXPORT extern __attribute__((visibility ("default")))
#endif

