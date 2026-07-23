/*
 * Copyright (c) 2013-2026 Apple Inc. All rights reserved.
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

#pragma once

#include <mach/kern_return.h>
#include <stddef.h>
#include <stdint.h>

__BEGIN_DECLS

/* New CoreAnalytics ECC logging mechanism. */

/**
 * ECC error handling flags/commands.
 *
 * This enum combines two concepts:
 * - Error type (what happened).
 * - Action modifiers (what to do about it).
 *
 * Bit 0 (error type) is mutually exclusive: it defines what type of error
 * occurred and these values cannot be combined.
 */
__options_decl(ecc_flags_t, uint32_t, {
	/* This is an uncorrectable error. */
	ECC_IS_UNCORRECTABLE            = (0ULL << 0),

	/* This error has been corrected. */
	ECC_IS_CORRECTABLE              = (1ULL << 0),

	/* Mask to extract the error type from combined flags. */
	ECC_TYPE_MASK                   = (1ULL << 0),

	/* The database is corrupted, tell daemon to drop it. */
	ECC_DB_CORRUPTED                = (1ULL << 1),

	/* The error was injected for testing purposes. */
	ECC_IS_TEST_ERROR               = (1ULL << 2),

	/* Do not trigger a CA report, just record the error to the DB. */
	ECC_DB_ONLY                     = (1ULL << 3),

	/* Remove this address from the DB. */
	ECC_REMOVE_ADDR                 = (1ULL << 4),

	/*
	 * ECC_NONE represents no flags set. Since bit 0 is clear, this has
	 * the same bit pattern as ECC_IS_UNCORRECTABLE, but should not be used
	 * to report actual errors.
	 */
	ECC_NONE                        = 0,
});

/**
 * ECC versions.
 */
__options_decl(ecc_version_t, uint32_t, {
	ECC_V1,

	// Metadata
	ECC_NUM_VERSIONS
});

/**
 * ECC event descriptor.
 *
 * @note If a new ECC version has been added (e.g. future hardware must
 * log new or different data) new fields should be appended to this struct to
 * represent the new data.  No fields should be deleted from this struct unless
 * the field corresponds only to hardware that has been deprecated.
 */
typedef struct {
	/* Version of this struct. */
	ecc_version_t version;

	/* Flags describing the reported error. */
	ecc_flags_t flags;

	/* Physical address of failure */
	uint64_t physaddr;

	/* Number of CEs reported at physaddr */
	uint32_t ce_count;

	/* Vendor ID */
	uint32_t vendor;

	/* Reserved for future extension to report row, column, bank, etc. */
	uint32_t reserved[4];
} ecc_event_t;

_Static_assert(sizeof(ecc_event_t) == 10 * sizeof(uint32_t),
    "ecc_event_t size must be updated in memory_error_notification.defs");


/* Flags to describe MCC memory errors */
__options_decl(mcc_flags_t, uint32_t, {
	MCC_NONE                        = 0x00000000,
	MCC_IS_SINGLE_BIT               = 0x00000001,
	MCC_IS_MULTI_BIT                = 0x00000002,
});

/**
 * MCC ECC versions.
 */
typedef enum {
	MCC_ECC_V1,

	// Metadata
	MCC_ECC_NUM_VERSIONS
} mcc_ecc_version_t;

/**
 * MCC ECC event descriptor.
 *
 * @note If a new MCC ECC version has been added, because i.e. future hardware must log new or different data,
 * new fields should be appended to this struct to represent the new data.  No fields should be
 * deleted from this struct unless the field corresponds only to hardware that has been deprecated.
 */
typedef struct {
	/* Version of this struct. */
	mcc_ecc_version_t version;
	/* Flags used to describe the error. */
	mcc_flags_t flags;
	/* Interrupt status at the time of the MCC error. */
	uint32_t status;
	/* AMCC on which the error occurred. */
	uint32_t amcc;
	/* Plane of the AMCC on which the error occurred. */
	uint32_t plane;
	/* MemCache error Bank of first one bit error. */
	uint32_t bank;
	/* MemCache error Way of first one bit error. */
	uint32_t way;
	/* MemCache error Index of first one bit error. */
	uint32_t index;
	/* Indicates whether the error is in upper half cache line or lower half cache line. */
	uint32_t bit_off_cl;
	/* MemCache one bit error bit offset of first one bit error with in half cache line. */
	uint32_t bit_off_within_hcl;
} mcc_ecc_event_t;
_Static_assert(sizeof(mcc_ecc_event_t) == 10 * sizeof(uint32_t), "mcc_ecc_event_t size must be updated in memory_error_notification.defs");

/**
 * Log an MCC error.
 *
 * @param event Event to be logged
 * @returns KERN_SUCCESS on success, KERN_FAILURE otherwise
 */
kern_return_t
mcc_log_memory_error(mcc_ecc_event_t event);

/**
 * Old ECC logging mechanism.
 */

#define ECC_EVENT_INFO_DATA_ENTRIES     8
struct ecc_event {
	uint8_t         id;     // ID of memory (e.g. L2C), platform-specific
	uint8_t         count;  // Of uint64_t's used, starting at index 0
	uint64_t        data[ECC_EVENT_INFO_DATA_ENTRIES] __attribute__((aligned(8))); // Event-specific data
};



__END_DECLS
