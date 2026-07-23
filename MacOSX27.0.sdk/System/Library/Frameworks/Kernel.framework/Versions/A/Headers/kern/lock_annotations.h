/*
 * Copyright (c) 2026 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _KERN_LOCK_ANNOTATIONS_H_
#define _KERN_LOCK_ANNOTATIONS_H_

/*
 * Compile-time lock analysis via clang's thread safety annotations
 * (-Wthread-safety, https://clang.llvm.org/docs/ThreadSafetyAnalysis.html)
 * Example use:
 *   struct foo {
 *       lock_t my_lock XNU_LOCKCHECK_LOCK_CAPABILITY("mutex");
 *       int protected_data;
 *   };
 *   void lock_foo(struct foo *f) XNU_LOCKCHECK_ACQUIRES_LOCK_EX(f->my_lock);
 *   void unlock_foo(struct foo *f) XNU_LOCKCHECK_RELEASES_LOCK_EX(f->my_lock);
 *   void process_foo(struct foo *f) XNU_LOCKCHECK_REQUIRES_LOCK_EX(f->my_lock) {
 *       f->protected_data++;
 *   }
 */

#if __has_attribute(capability)

/*
 * Denotes the field as representing a lock capability.
 * The name should describe the lock type.
 */
#define XNU_LOCKCHECK_LOCK_CAPABILITY(name) \
	__attribute__((capability(name)))

/*
 * Mark that the function must be called while holding the specified lock(s).
 */
#define XNU_LOCKCHECK_REQUIRES_LOCK_EX(...) \
	__attribute__((requires_capability(__VA_ARGS__)))

/*
 * Mark that the function acquires the specified lock(s).
 */
#define XNU_LOCKCHECK_ACQUIRES_LOCK_EX(...) \
	__attribute__((acquire_capability(__VA_ARGS__)))

/*
 * Mark that the function releases the specified lock(s).
 */
#define XNU_LOCKCHECK_RELEASES_LOCK_EX(...) \
	__attribute__((release_capability(__VA_ARGS__)))

/*
 * Mark that the function must be called while not holding the specified lock(s).
 *
 * This is useful if the function internally acquires the lock, for example.
 */
#define XNU_LOCKCHECK_REQUIRES_UNLOCKED(...) \
	__attribute__((locks_excluded(__VA_ARGS__)))

/*
 * Disable thread safety analysis for the function.
 *
 * Useful when it's onerous to describe the lock lifecycle to the analyzer.
 */
#define XNU_LOCKCHECK_IGNORE \
	__attribute__((no_thread_safety_analysis))

/*
 * Disable lock checking for the scope wrapped by this macro pair.
 * Useful when an entire file or chunk of functionality cannot be lock-checked.
 */
#define XNU_LOCKCHECK_PUSH_IGNORE \
	_Pragma("clang attribute push(__attribute__((no_thread_safety_analysis)), apply_to=function)")
#define XNU_LOCKCHECK_POP_IGNORE \
	_Pragma("clang attribute pop")

#else /* !__has_attribute(capability) */
#define XNU_LOCKCHECK_LOCK_CAPABILITY(name)
#define XNU_LOCKCHECK_REQUIRES_LOCK_EX(...)
#define XNU_LOCKCHECK_ACQUIRES_LOCK_EX(...)
#define XNU_LOCKCHECK_RELEASES_LOCK_EX(...)
#define XNU_LOCKCHECK_REQUIRES_UNLOCKED(...)
#define XNU_LOCKCHECK_IGNORE
#endif /* __has_attribute(capability) */
#endif /* _KERN_LOCK_ANNOTATIONS_H_ */
