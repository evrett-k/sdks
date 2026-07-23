/*
	NSHFSFileTypes.h
	Copyright (c) 2000-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <CoreFoundation/CFBase.h>

@class NSString;

/// Returns a string encoding a file type code.
///
/// - Parameter hfsFileTypeCode: An HFS file type code.
/// - Returns: A string that encodes `hfsFileTypeCode`. The format of the string is a private implementation detail, but such strings are suitable for inclusion in arrays that also contain file name extension strings.
FOUNDATION_EXPORT NSString *NSFileTypeForHFSTypeCode(OSType hfsFileTypeCode);

/// Returns a file type code.
///
/// - Parameter fileTypeString: A string of the sort encoded by `NSFileTypeForHFSTypeCode()`.
/// - Returns: The HFS file type code corresponding to `fileTypeString`, or `0` if it cannot be found.
FOUNDATION_EXPORT OSType NSHFSTypeCodeFromFileType(NSString *fileTypeString);

/// Returns a string encoding a file type.
///
/// - Parameter fullFilePath: The full absolute path of a file.
/// - Returns: A string that encodes `fullFilePath`'s HFS file type, or `nil` if the operation was not successful.
FOUNDATION_EXPORT NSString *NSHFSTypeOfFile(NSString *fullFilePath);
