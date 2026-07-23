//
//  cp_conditionals.h
//  WakeBoard
//
//  Created by Jacob Wilson on 3/14/25.
//  Copyright © 2025 Apple. All rights reserved.
//

#ifndef cp_conditionals_h
#define cp_conditionals_h

// TODO: Remove the the workaround for TARGET_OS_MACCATALYST
// rdar://165627547 (remove ar_device_anchor_t workaround for TARGET_OS_MACCATALYST) after
// rdar://163150992 (CompositorServices drawable.h references ar_device_anchor_t but does not import a header where that is defined)
#define CP_ARKITCORE_AVAILABLE ((TARGET_OS_VISION && !TARGET_OS_SIMULATOR) || TARGET_OS_OSX) && !TARGET_OS_MACCATALYST
#define CP_MTL4_AVAILABLE      !TARGET_OS_SIMULATOR

#endif
