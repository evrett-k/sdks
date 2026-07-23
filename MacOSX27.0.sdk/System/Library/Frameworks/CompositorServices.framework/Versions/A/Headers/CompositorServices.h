//
//  CompositorServices.h
//  CompositorServices
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <CoreFoundation/CoreFoundation.h>
#import <simd/simd.h>

#undef CP_ARKIT_AVAILABLE
#define CP_ARKIT_AVAILABLE (TARGET_OS_VISION || TARGET_OS_OSX)

#import <CompositorServices/cp_conditionals.h>

#ifdef __OBJC__
#if (TARGET_OS_IOS || TARGET_OS_VISION) && !TARGET_OS_MACCATALYST
#import <UIKit/UIKit.h>
#endif
#import <Metal/Metal.h>
#import <ARKit/ARKit.h>
#endif

/*!
 * @header
 *
 * CompositorServices is an API that allows your application to render directly into the compositor server.
 * It provides a set of APIs to pace the rendering of your application in a way that
 * is optimal for the system power constraints and input latency.
 */

#import <CompositorServices/cp_base.h>

#import <CompositorServices/cp_error.h>
#import <CompositorServices/cp_types.h>
#import <CompositorServices/tracking_area.h>
#import <CompositorServices/frame_timing.h>
#import <CompositorServices/layer_renderer_layout.h>
#import <CompositorServices/layer_renderer_capabilities.h>
#import <CompositorServices/layer_renderer_configuration.h>
#import <CompositorServices/layer_renderer_properties.h>
#import <CompositorServices/view.h>
#import <CompositorServices/drawable_render_context.h>
#import <CompositorServices/drawable.h>
#import <CompositorServices/frame.h>
#import <CompositorServices/layer_renderer.h>
