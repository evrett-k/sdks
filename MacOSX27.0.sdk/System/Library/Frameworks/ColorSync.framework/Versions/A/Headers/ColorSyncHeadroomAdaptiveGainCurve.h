/*
 * ColorSync - ColorSyncHeadroomAdaptiveGainCurve.h
 * Copyright (c)  2026 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCHEADROOMADAPTIVEGAINCURVE__
#define __COLORSYNCHEADROOMADAPTIVEGAINCURVE__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncBase.h>
#include <ColorSync/ColorSyncProfile.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

API_AVAILABLE_BEGIN(macos(27.0), ios(27.0), tvos(27.0), watchos(27.0), visionos(27.0))

/* Returns a new profile that is a copy of 'profile' with the supplied Headroom Adaptive Gain Curve
 * data embedded as an HAGC tag.
 * 'profile' must be a profile with a CICP tag indicating PQ, HLG, or Linear transfer
 * function (the latter is for extended-range data); passing an SDR profile returns NULL.
 * 'data' must be non-NULL.
 * 'options' is reserved for future use; pass NULL.
 * Caller must CFRelease the result. */
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateCopyWithHeadroomAdaptiveGainCurveMetadata(ColorSyncProfileRef, CFDataRef, __nullable CFDictionaryRef) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/* Returns a copy of the raw Headroom Adaptive Gain Curve data embedded in
 * the profile, or NULL if none is present.  Caller must CFRelease the result. */
CSEXTERN CFDataRef __nullable ColorSyncProfileCopyHeadroomAdaptiveGainCurveMetadata(ColorSyncProfileRef) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/* Returns a new profile that is a copy of 'profile' with an HAGC tag synthesised
 * from the supplied info dictionary (see Keys section below).
 * 'profile' must be a profile with a CICP tag indicating PQ, HLG, or Linear transfer
 * function (the latter is for extended-range data); passing an SDR profile returns NULL.
 * Caller must CFRelease the result. */
CSEXTERN ColorSyncProfileRef __nullable ColorSyncProfileCreateCopyWithHeadroomAdaptiveGainCurveInfoDictionary(ColorSyncProfileRef, CFDictionaryRef) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/* Returns a dictionary representing the HAGC info decoded from 'profile', or NULL
 * if the profile carries no HAGC tag.  See Keys section below for dictionary contents.
 * Caller must CFRelease the result. */
CSEXTERN CFDictionaryRef __nullable ColorSyncProfileCopyHeadroomAdaptiveGainCurveInfoDictionary(ColorSyncProfileRef profile) CF_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;

/* Returns true if the profile contains a Headroom Adaptive Gain Curve tag. */
CSEXTERN bool ColorSyncProfileContainsHeadroomAdaptiveGainCurve(ColorSyncProfileRef) ;

/*
Dictionary structure returned by `ColorSyncProfileCopyHeadroomAdaptiveGainCurveInfoDictionary`.
Indentation reflects nesting; entries marked (1) or (2) share the value from array index 0
when the indicated flag is true.


| Key                                                       | Type               | Condition |
| --------------------------------------------------------- | ------------------ | --------- |
| `kColorSyncHeadroomAdaptiveGainCurveApplicationVersion`   | `CFNumberRef (u8)` | always    |
| `kColorSyncHeadroomAdaptiveGainCurveColorVolumeTransform` | `CFDictionaryRef`  | if Custom Reference White or Headroom-Adaptive tone map |
| `├─ kColorSyncCustomHDRReferenceWhite`                    | `CFNumberRef (f)`  | if Custom Reference White |
| `└─ kColorSyncHeadroomAdaptiveToneMappingInfo`            | `CFDictionaryRef`  | if Headroom-Adaptive tone map (`kCFBooleanFalse` otherwise) |
| `  ├─ kColorSyncBaselineHeadroomStops`                    | `CFNumberRef (f)`  | always    |
| `  └─ kColorSyncHeadroomAdaptiveGainCurveInfo`            | `CFDictionaryRef`  | if `RWTMO == false` (`kCFBooleanFalse` otherwise) |
| `    ├─ kColorSyncAlternateCurveCount`                    | `CFNumberRef (u8)` | always    |
| `    ├─ kColorSyncCommonComponentMixing`                  | `CFBooleanRef`     | always    |
| `    ├─ kColorSyncCommonCurveParameters`                  | `CFBooleanRef`     | always    |
| `    ├─ kColorSyncGainCurveChromaticities`                | `CFNumberRef (u8)`<br> or `CFArrayRef (f)` | always; CFNumberRef for standard primaries enum,<br>or CFArray of 8 floats for custom primaries |
| `    └─ kColorSyncAlternateGainCurveInfo`                 | `CFArrayRef`       | if `alternate curve count > 0` |
| `      └─ [each of alternate_curve_count elements]`       | `CFDictionaryRef`  |           |
| `        ├─ kColorSyncAlternateCurveHeadroomStops`        | `CFNumberRef (f)`  | always    |
| `        ├─ kColorSyncComponentMix`                       | `CFNumberRef (u8)` | always (1)|
| `        ├─ kColorSyncComponentCoefficients`              | `CFDictionaryRef`  | if `component_mix == 3` (1) |
| `        │ ├─ kColorSyncCoefficientRed`                   | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientGreen`                 | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientBlue`                  | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientMaxRGB`                | `CFNumberRef (f)`  | if present in bitstream |
| `        │ ├─ kColorSyncCoefficientMinRGB`                | `CFNumberRef (f)`  | if present in bitstream |
| `        │ └─ kColorSyncCoefficientComponent`             | `CFNumberRef (f)`  | if present in bitstream |
| `        ├─ kColorSyncMaxControlPointIndex`               | `CFNumberRef (u8)` | always (2) |
| `        ├─ kColorSyncInterpolateSlopes`                  | `CFBooleanRef`     | always (2) |
| `        ├─ kColorSyncControlPointsX`                     | `CFArrayRef (f)`   | always (2) × number of points |
| `        ├─ kColorSyncControlPointsY`                     | `CFArrayRef (f)`   | always (2) × number of points |
| `        └─ kColorSyncControlPointSlopes`                 | `CFArrayRef (f)`   | if `kColorSyncInterpolateSlopes == false` (2) × number of points |```

    (1) Shared across all array entries from index 0 when kColorSyncCommonComponentMixing is true.
    (2) Shared across all array entries from index 0 when kColorSyncCommonCurveParameters is true.
*/

/* ---------------------------------------------------------
    Keys for Headroom Adaptive Gain Curve Info Dictionary
   --------------------------------------------------------  */

/*  ................................. */
/*  ........ Baseline Curve ......... */
/*  ................................. */

/* Application version (uint8_t, 0–7). 3-bit field from ST 2094-50 Table C.1.
 * Currently always 0. */
CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveGainCurveApplicationVersion;

/* Top-level container (CFDictionaryRef) for the color volume transform.
 * It may contain parameters for Headroom-Adaptive tone mapping or indicate
 * usage of the Reference-White Tone Mapping Method. It allows for specifying
 * a custom HDR Reference White luminance.
 */
CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveGainCurveColorVolumeTransform;

/* Custom reference white luminance in nits (float), overriding the standard
 * 203-nit reference white. */
CSEXTERN CFStringRef kColorSyncCustomHDRReferenceWhite;

/* Container (CFDictionaryRef) for Headroom-Adaptive tone mapping parameters.
 * Present when Headroom-Adaptive tone mapping is encoded. Contains kColorSyncBaselineHeadroomStops
 * and either kColorSyncHeadroomAdaptiveGainCurveInfo or, when set to kCFBooleanFalse,
 * indicates the Reference-White Tone Mapping Operator (RWTMO) method. */
CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveToneMappingInfo;
    /* Headroom of the source (baseline) curve in stops above reference white (float).
     */
    CSEXTERN CFStringRef kColorSyncBaselineHeadroomStops;

    /* Container (CFDictionaryRef) for the adaptive gain curve data.
     * Contains the alternate curve count, sharing flags, chromaticities, and
     * the per-alternate curve info array.
     * When set to kCFBooleanFalse instead of CFDictionary, the RWTMO is active. */
    CSEXTERN CFStringRef kColorSyncHeadroomAdaptiveGainCurveInfo;

    /* Number of alternate (tone-mapped) curves encoded in the metadata
     * (uint8_t). Each alternate targets a different display headroom. */
    CSEXTERN CFStringRef kColorSyncAlternateCurveCount;

    /* CFArrayRef of per-alternate dictionaries (see Alternate curve keys below).
     * Count equals kColorSyncAlternateCurveCount. Only present when
     * alternate curve count > 0. */
    CSEXTERN CFStringRef kColorSyncAlternateGainCurveInfo;

    /* Chromaticity primaries used to compute the driving signal for the gain curve.
     * Standard values (CFNumberRef uint8_t): 0 = BT.709, 1 = Display P3,
     * 2 = BT.2020, 3 = Custom.  For custom (3), value is a CFArrayRef of 8 floats
     * encoding four xy chromaticity pairs: R, G, B, white point. */
    CSEXTERN CFStringRef kColorSyncGainCurveChromaticities;

    /* CFBooleanRef. When true, all alternate curves share the component mixing
     * configuration from array index 0, reducing bitstream size. */
    CSEXTERN CFStringRef kColorSyncCommonComponentMixing;

    /* CFBooleanRef. When true, all alternate curves share the gain curve control
     * points, slopes, and slope interpolate flag from array index 0,
     * reducing bitstream size. */
    CSEXTERN CFStringRef kColorSyncCommonCurveParameters;

/*  ................................. */
/* ....... Alternate Curves ....... */
/*  ................................. */

/* Target headroom of this alternate curve in stops above reference white (float).
 * The renderer selects the closest alternate to the actual display headroom. */
CSEXTERN CFStringRef kColorSyncAlternateCurveHeadroomStops;

/* Component mixing type (uint8_t) matching component_mixing_value in ST 2094-50.
 * Determines how the scalar driving signal is derived from the RGB pixel:
 *   0 = MAX(R, G, B)
 *   1 = single component (Headroom Adaptive Gain Curve is applied to individual components)
 *   2 = luma_A (weighted luminance using the gain curve chromaticities)
 *   3 = free-style (custom linear combination via kColorSyncComponentCoefficients)
 * Shared across all alternates from index 0 when kColorSyncCommonComponentMixing is true. */
CSEXTERN CFStringRef kColorSyncComponentMix;

/* Sub-dictionary of custom linear-combination coefficients for free-style component
 * mixing (component mixing type == 3). Each present key contributes its value as a weight
 * in: signal = R*red + G*green + B*blue + MAX*maxRGB + MIN*minRGB + C*component.
 * Only present when kColorSyncAlternateCurveComponentMix == 3. */
CSEXTERN CFStringRef kColorSyncComponentCoefficients;
    /* Weight for the red channel in the free-style component mixing sum. */
    CSEXTERN CFStringRef kColorSyncCoefficientRed;
    /* Weight for the green channel in the free-style component mixing sum. */
    CSEXTERN CFStringRef kColorSyncCoefficientGreen;
    /* Weight for the blue channel in the free-style component mixing sum. */
    CSEXTERN CFStringRef kColorSyncCoefficientBlue;
    /* Weight for the MAX(R,G,B) term in the free-style component mixing sum. */
    CSEXTERN CFStringRef kColorSyncCoefficientMaxRGB;
    /* Weight for the MIN(R,G,B) term in the free-style component mixing sum. */
    CSEXTERN CFStringRef kColorSyncCoefficientMinRGB;
    /* Weight for the 'component' term in the free-style component mixing sum. */
    CSEXTERN CFStringRef kColorSyncCoefficientComponent;

/* Index of the last control point (uint8_t, 0–31), i.e. number of control points
 * minus 1. Shared across all alternates from index 0 when kColorSyncCommonCurveParameters
 * is true. */
CSEXTERN CFStringRef kColorSyncMaxControlPointIndex;

/* CFBooleanRef. When true, slopes at control points are computed by
 * Piecewise Cubic Hermite Interpolating Polynomial from the X,Y control point
 * coordinates and kColorSyncControlPointSlopes must be absent. When false, explicit slopes need
 * to be supplied in kColorSyncControlPointSlopes (see below).
 * Shared across all alternates from index 0 when kColorSyncCommonCurveParameters is true. */
CSEXTERN CFStringRef kColorSyncInterpolateSlopes;

/* CFArrayRef of floats — X-axis coordinates of the gain curve control points,
 * normalised to [0, 1] where 0 is at reference white and 1 is at peak signal.
 * Shared across all alternates from index 0 when kColorSyncCommonCurveParameters is true. */
CSEXTERN CFStringRef kColorSyncControlPointsX;

/* CFArrayRef of floats — Y-axis coordinates of the gain curve control points.
 * Positive values expand dynamic range; negative values compress it.
 * Shared across all alternates from index 0 when kColorSyncCommonCurveParameters is true. */
CSEXTERN CFStringRef kColorSyncControlPointsY;

/* CFArrayRef of floats — explicit tangent slopes at each control point, expressed
 * as tan(slope_angle). Only present when kColorSyncInterpolateSlopes is false.
 * Shared across all alternates from index 0 when kColorSyncCommonCurveParameters is true. */
CSEXTERN CFStringRef kColorSyncControlPointSlopes;

API_AVAILABLE_END

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCHEADROOMADAPTIVEGAINCURVE__ */
