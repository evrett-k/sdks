/*	NSArchiver.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>
#import <Foundation/NSException.h>

@class NSString, NSData, NSMutableData, NSMutableDictionary, NSMutableArray;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* ***********		Archiving: Writing	****************/

/// A coder that stores an object's data to an archive.
///
/// ``NSArchiver``, a concrete subclass of ``NSCoder``, provides a way to encode objects into an architecture-independent format that can be stored in a file. When you archive a graph of objects, the class information and instance variables for each object are written to the archive. The companion class ``NSUnarchiver`` decodes the data in an archive and creates a graph of objects equivalent to the original set.
///
/// ``NSArchiver`` stores the archive data in a mutable data object (``NSMutableData``). After encoding the objects, you can have the ``NSArchiver`` object write this mutable data object immediately to a file, or you can retrieve the mutable data object for some other use.
///
/// In macOS 10.2 and later, ``NSArchiver`` and ``NSUnarchiver`` have been replaced by ``NSKeyedArchiver`` and ``NSKeyedUnarchiver`` respectively—see [Archives and Serializations Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Archiving.html#//apple_ref/doc/uid/10000047i).
///
/// @DeprecationSummary {
///     Use ``NSKeyedArchiver`` instead.
/// }
API_DEPRECATED("Use NSKeyedArchiver instead", macos(10.0,10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
@interface NSArchiver : NSCoder {
@private
    void		*mdata;
    void		*pointerTable;
    void		*stringTable;
    void		*ids;
    void		*map;
    void		*replacementTable;
    void		*reserved;
}

/// Returns an archiver, initialized to encode stream and version information into a given mutable data object.
///
/// - Parameters:
///   - mdata: The mutable data object into which to write the archive. This value must not be `nil`.
/// - Returns: An archiver object, initialized to encode stream and version information into `mdata`.
///
/// Raises an `NSInvalidArgumentException` if `mdata` is `nil`.
- (instancetype)initForWritingWithMutableData:(NSMutableData *)mdata NS_DESIGNATED_INITIALIZER;

/// The receiver's archive data.
///
/// The returned data object is the same one specified as the argument to ``NSArchiver/init(forWritingWith:)``. It contains whatever data has been encoded thus far by invocations of the various encoding methods. It is safest not to invoke this method until after ``NSArchiver/encodeRootObject(_:)`` has returned. In other words, although it is possible for a class to invoke this method from within its ``NSCoding/encode(with:)`` method, that method must not alter the data.
@property (readonly, retain) NSMutableData *archiverData;

/// Encodes a given root object, along with all of the objects it's connected to.
///
/// If any object is encountered more than once while traversing the graph, it is encoded only once, but the multiple references to it are stored.
///
/// This message must not be sent more than once to a given `NSArchiver` object; an `NSInvalidArgumentException` is raised if a root object has already been encoded. If you need to encode multiple object graphs, don't attempt to reuse an `NSArchiver` instance; instead, create a new one for each graph.
///
/// - Parameter rootObject: The root object of the object graph to archive.
- (void)encodeRootObject:(id)rootObject;

/// Encodes an object only if it is referenced by another object in the archive.
///
/// This method overrides the superclass implementation to allow `object` to be encoded only if it is also encoded unconditionally by another object in the object graph. Conditional encoding lets you encode one part of a graph detached from the rest.
///
/// This method should be invoked only from within an ``NSCoding/encode(with:)`` method. If `object` is `nil`, the `NSArchiver` object encodes it unconditionally as `nil`. This method raises an `NSInvalidArgumentException` if no root object has been encoded.
///
/// - Parameter object: The object to archive.
- (void)encodeConditionalObject:(nullable id)object;

/// Returns a data object that contains the encoded form of the object graph formed by the given root object.
///
/// This method invokes ``NSArchiver/initForWritingWithMutableData:`` and ``NSArchiver/encodeRootObject:`` to create a temporary archiver that encodes the object graph.
///
/// - Parameter rootObject: The root object of the object graph to archive.
/// - Returns: A data object containing the encoded form of the object graph whose root object is `rootObject`.
+ (NSData *)archivedDataWithRootObject:(id)rootObject;

/// Archives an object graph rooted at a given object by encoding it into a data object then atomically writing the resulting data object to a file at a given path.
///
/// This convenience method invokes ``NSArchiver/archivedDataWithRootObject:`` to get the encoded data, and then sends that data object the message ``NSData/writeToFile:atomically:``, using `path` for the first argument and `YES` for the second.
///
/// The archived data should be retrieved from the archive by an ``NSUnarchiver`` object.
///
/// - Parameters:
///   - rootObject: The root object of the object graph to archive.
///   - path: The location of the file into which to write the archive.
/// - Returns: `YES` if the archive was written successfully, otherwise `NO`.
+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path;

/// Encodes a given class under a given name.
///
/// Any subsequently encountered objects of class `trueName` are archived as instances of class `inArchiveName`. It is safest not to invoke this method during the archiving process (that is, within an ``NSCoding/encode(with:)`` method). Instead, invoke it before ``encodeRootObject:``.
///
/// - Parameters:
///   - trueName: The real name of a class in the object graph being archived.
///   - inArchiveName: The name of the class to use in the archive in place of `trueName`.
- (void)encodeClassName:(NSString *)trueName intoClassName:(NSString *)inArchiveName;
/// Returns the name under which a given class was encoded.
///
/// - Parameter trueName: The real name of an encoded class.
/// - Returns: The name of the class used to archive instances of the class `trueName`.
- (nullable NSString *)classNameEncodedForTrueClassName:(NSString *)trueName;

/// Replaces one object with another during encoding.
///
/// Causes the receiver to treat subsequent requests to encode `object` as though they were requests to encode `newObject` instead. Both `object` and `newObject` must be valid objects.
///
/// - Parameters:
///   - object: An object in the object graph being archived.
///   - newObject: The object with which to replace `object` in the archive.
- (void)replaceObject:(id)object withObject:(id)newObject;

@end

/* ***********		Archiving: Reading		****************/

/// A decoder that restores data from an archive.
///
/// ``NSUnarchiver``, a concrete subclass of ``NSCoder``, defines methods for decoding a set of Objective-C objects from an archive. Such archives are produced by objects of the ``NSArchiver`` class.
///
/// In macOS 10.2 and later, ``NSArchiver`` and ``NSUnarchiver`` have been replaced by ``NSKeyedArchiver`` and ``NSKeyedUnarchiver`` respectively—see [Archives and Serializations Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Archiving.html#//apple_ref/doc/uid/10000047i).
///
/// @DeprecationSummary {
///     Use ``NSKeyedUnarchiver`` instead.
/// }
API_DEPRECATED("Use NSKeyedUnarchiver instead", macos(10.0,10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0))
@interface NSUnarchiver : NSCoder {
@private
    void *		datax;
    NSUInteger		cursor;
    NSZone              *objectZone;
    NSUInteger		systemVersion;
    signed char		streamerVersion;
    char		swap;
    char		unused1;
    char		unused2;
    void		*pointerTable;
    void		*stringTable;
    id			classVersions;
    NSInteger			lastLabel;
     void		*map;
    void		*allUnarchivedObjects;
    id			reserved;
}

/// Returns an `NSUnarchiver` object initialized to read an archive from a given data object.
///
/// The method decodes the system version number that was archived in `data` and prepares the `NSUnarchiver` object for a subsequent invocation of ``NSCoder/decodeObject()``.
///
/// Raises an `NSInvalidArgumentException` if `data` is `nil`.
///
/// - Parameter data: The archive data.
/// - Returns: An `NSUnarchiver` object initialized to read an archive from `data`. Returns `nil` if `data` is not a valid archive.
- (nullable instancetype)initForReadingWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

/// Sets the zone in which decoded objects are allocated.
- (void)setObjectZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
/// Returns the zone in which decoded objects are allocated.
- (nullable NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// A Boolean value that indicates whether the receiver has reached the end of the encoded data while decoding.
///
/// You can invoke this after invoking `decodeObject` to discover whether the archive contains extra data following the encoded object graph. If it does, you can either ignore this anomaly or consider it an error.
@property (getter=isAtEnd, readonly) BOOL atEnd;

/// The system version number in effect when the archive was created.
///
/// This information is available as soon as the receiver has been initialized.
@property (readonly) unsigned int systemVersion;

/// Decodes and returns the previously-archived object graph in the given data.
///
/// This method invokes ``NSUnarchiver/initForReadingWithData:`` and ``NSCoder/decodeObject`` to create a temporary `NSUnarchiver` object that decodes the object. If the archived object is the root of a graph of objects, the entire graph is unarchived.
///
/// - Parameter data: An `NSData` object that contains an archive created using `NSArchiver`.
/// - Returns: The object, or object graph, that was archived in `data`. Returns `nil` if `data` cannot be unarchived.
+ (nullable id)unarchiveObjectWithData:(NSData *)data;
/// Decodes and returns the previously-archived object graph from the file at the given path.
///
/// This convenience method reads the file by invoking the `NSData` method ``NSData/dataWithContentsOfFile:`` and then invokes ``NSUnarchiver/unarchiveObjectWithData:``.
///
/// - Parameter path: The path to a file that contains an archive created using ``NSArchiver``.
/// - Returns: The object, or object graph, that was archived in the file at `path`. Returns `nil` if the file at `path` cannot be unarchived.
+ (nullable id)unarchiveObjectWithFile:(NSString *)path;

/// Sets a class-wide substitution mapping, translating a given class name from the archive to a given replacement class name during decoding.
///
/// This method enables easy conversion of unarchived data when the name of a class has changed since the archive was created.
///
/// Note that there is also an instance method of the same name. An instance of `NSUnarchiver` can maintain its own mapping of class names. However, if both the class method and the instance method have been invoked using an identical value for `inArchiveName`, the class method takes precedence.
///
/// - Parameters:
///   - inArchiveName: The ostensible name of a class in an archive.
///   - trueName: The name of the class to use when instantiating objects whose ostensible class, according to the archived data, is `inArchiveName`.
+ (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;

/// Sets a per-instance substitution mapping, translating a given class name from the archive to a given replacement class name during decoding.
///
/// This method enables easy conversion of unarchived data when the name of a class has changed since the archive was created.
///
/// Note that there's also a class method of the same name. The class method has precedence in case of conflicts.
///
/// - Parameters:
///   - inArchiveName: The ostensible name of a class in an archive.
///   - trueName: The name of the class to use when instantiating objects whose ostensible class, according to the archived data, is `inArchiveName`.
- (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;

/// Returns the class name that the unarchiver class substitutes for a given archived class name.
///
/// Returns `inArchiveName` if no substitute name has been specified using the class method ``NSUnarchiver/decodeClassName:asClassName:``.
///
/// Note that each individual instance of `NSUnarchiver` can be given its own class name mappings by invoking the instance method ``NSUnarchiver/decodeClassName:asClassName:``. The `NSUnarchiver` class has no information about these instance-specific mappings, however, so they don't affect the return value of this method.
///
/// - Parameter inArchiveName: The name of a class.
/// - Returns: The name of the class used when instantiating objects whose ostensible class, according to the archived data, is `inArchiveName`.
+ (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;
/// Returns the class name that this unarchiver substitutes for a given archived class name.
///
/// Returns `inArchiveName` unless a substitute name has been specified using the instance method ``decodeClassName:asClassName:``.
///
/// - Parameter inArchiveName: The name of a class.
/// - Returns: The name of the class used when instantiating objects whose ostensible class, according to the archived data, is `inArchiveName`.
- (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;

/// Replaces one object with another during decoding.
///
/// Causes the receiver to substitute `newObject` for `object` whenever `object` is extracted from the archive. `newObject` can be of a different class from `object`, and the class mappings set by ``decodeClassName:asClassName:`` are ignored.
///
/// - Parameters:
///   - object: The archived object to replace.
///   - newObject: The object with which to replace `object`.
- (void)replaceObject:(id)object withObject:(id)newObject;

@end

/* ***********		Object call back		****************/

@interface NSObject (NSArchiverCallback)

@property (nullable, readonly) Class classForArchiver;

- (nullable id)replacementObjectForArchiver:(NSArchiver *)archiver API_DEPRECATED_WITH_REPLACEMENT("replacementObjectForCoder:", macos(10.0,10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
