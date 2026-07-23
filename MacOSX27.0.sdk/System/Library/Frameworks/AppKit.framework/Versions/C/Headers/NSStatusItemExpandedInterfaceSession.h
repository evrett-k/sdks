/*
        NSStatusItemExpandedInterfaceSession.h
        Application Kit
        Copyright (c) 2026, Apple Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

API_AVAILABLE(macos(27.0))
@interface NSStatusItemExpandedInterfaceSession : NSObject

/*  Cancels tracking of the expanded interface state in the menu bar system. NSStatusItemExpandedInterfaceDelegate will receive -statusItemDidEndExpandedInterfaceSession:animated: after cancellation.
 */
- (void)cancel;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
