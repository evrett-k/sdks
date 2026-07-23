#if (defined(USE_APPKIT_PUBLIC_HEADERS) && USE_APPKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextAlternatives.h>)
#import <TargetConditionals.h>

#if !TARGET_OS_IPHONE
//
//  NSTextAlternatives.h
//  Text Kit
//
//  Copyright (c) 2011-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSNotification.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSString;

APPKIT_EXTERN API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface NSTextAlternatives : NSObject <NSSecureCoding>

- (instancetype)initWithPrimaryString:(NSString *)primaryString alternativeStrings:(NSArray<NSString *> *)alternativeStrings;

@property (readonly, copy) NSString *primaryString;
@property (readonly, copy) NSArray<NSString *> *alternativeStrings;

- (void)noteSelectedAlternativeString:(NSString *)alternativeString;

@end

APPKIT_EXTERN NSNotificationName NSTextAlternativesSelectedAlternativeStringNotification API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // @"NSAlternativeString"
NS_HEADER_AUDIT_END(nullability, sendability)
#endif // !TARGET_OS_IPHONE
#else
#import <UIFoundation/NSTextAlternatives.h>
#endif
