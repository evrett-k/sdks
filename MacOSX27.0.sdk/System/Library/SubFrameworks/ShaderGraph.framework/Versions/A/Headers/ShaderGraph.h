//
// Copyright © 2025 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

// MARK: - SGDataType
// These types correspond to the set of USD types taken from:
// https://graphics.pixar.com/usd/docs/api/_usd__page__datatypes.html
typedef NS_ENUM(NSUInteger, SGDataType) {
    SGDataTypeInvalid = 0, // Used to report the result of an invalid type conversion

    SGDataTypeBool = 1,
    SGDataTypeUchar = 2,
    SGDataTypeInt = 3,
    SGDataTypeUint = 6,
    SGDataTypeHalf = 7,
    SGDataTypeFloat = 9,
    SGDataTypeTimecode = 10,
    SGDataTypeString = 11, // TODO: These are either URLs or enum values, convert to dedicated types
    SGDataTypeToken = 12, // TODO: Remove this, these should be converted to dedicated semantic types, eg SGDataTypeSurfaceShader
    SGDataTypeAsset = 13,
    SGDataTypeMatrix2f = 14,
    SGDataTypeMatrix3f = 15,
    SGDataTypeMatrix4f = 17,
    SGDataTypeQuatf = 18,
    SGDataTypeQuath = 20,
    SGDataTypeFloat2 = 21,
    SGDataTypeHalf2 = 22,
    SGDataTypeInt2 = 24,
    SGDataTypeFloat3 = 25,
    SGDataTypeHalf3 = 26,
    SGDataTypeInt3 = 28,
    SGDataTypeFloat4 = 29,
    SGDataTypeHalf4 = 30,
    SGDataTypeInt4 = 31,

    // semantic types:
    SGDataTypePoint3f = 32,
    SGDataTypePoint3h = 33,
    SGDataTypeNormal3f = 35,
    SGDataTypeNormal3h = 36,
    SGDataTypeVector3f = 38,
    SGDataTypeVector3h = 39,
    SGDataTypeColor3f = 41,
    SGDataTypeColor3h = 42,
    SGDataTypeColor4f = 44,
    SGDataTypeColor4h = 45,
    SGDataTypeTexCoord2h = 47,
    SGDataTypeTexCoord2f = 49,
    SGDataTypeTexCoord3h = 50,
    SGDataTypeTexCoord3f = 52,

    // The following types are RE-specific
    SGDataTypeSurfaceShader = 53,
    SGDataTypeGeometryModifier = 54,

    SGDataTypeCGColor3 = 55,
    SGDataTypeCGColor4 = 56,

    // RE-specific
    SGDataTypePostLightingShader = 57,
};

typedef NS_ENUM(NSUInteger, SGLightingModel) {
    SGLightingModelNone = 0,
    SGLightingModelRealityKitPBR = 1,
    SGLightingModelRealityKitUnlit = 2,
    SGLightingModelRealityKitClearcoat = 3,

    SGLightingModelRealityKitPortal = 4,
#if SUPPORTS_CHARACTER_RENDERING
    SGLightingModelRealityKitHair = 5,
#endif
};

typedef NS_ENUM(NSUInteger, SGBlending) {
    SGBlendingOpaque = 0,
    SGBlendingTransparent = 1
};
