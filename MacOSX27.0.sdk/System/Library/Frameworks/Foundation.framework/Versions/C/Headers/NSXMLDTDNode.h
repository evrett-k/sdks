/*	NSXMLDTDNode.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSXMLNode.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The subkind of a DTD node kind.
///
/// Constants that specify the kind and subkind of DTD declaration represented by an `NSXMLDTDNode` object.
typedef NS_ENUM(NSUInteger, NSXMLDTDNodeKind) {
	/// Identifies a general entity declaration.
	NSXMLEntityGeneralKind = 1,
	/// Identifies a parsed entity declaration.
	NSXMLEntityParsedKind,
	/// Identifies an unparsed entity declaration.
	NSXMLEntityUnparsedKind,
	/// Identifies a parameter entity declaration.
	NSXMLEntityParameterKind,
	/// Identifies a predefined entity declaration.
	NSXMLEntityPredefined,

	/// Identifies an attribute-list declaration with a `CDATA` (character data) value type.
	NSXMLAttributeCDATAKind,
	/// Identifies an attribute-list declaration with an `ID` value type (per-document unique element name).
	NSXMLAttributeIDKind,
	/// Identifies an attribute-list declaration with an `IDREF` value type (refers to element `ID` type).
	NSXMLAttributeIDRefKind,
	/// Identifies an attribute-list declaration with an `IDREFS` value type (refers to multiple elements of `ID` type).
	NSXMLAttributeIDRefsKind,
	/// Identifies an attribute-list declaration with an `ENTITY` value type (refers to unparsed entity declared in document).
	NSXMLAttributeEntityKind,
	/// Identifies an attribute-list declaration with an `ENTITIES` value type (refers to multiple unparsed entities declared elsewhere in document).
	NSXMLAttributeEntitiesKind,
	/// Identifies an attribute-list declaration with a `NMTOKEN` value type (name token).
	NSXMLAttributeNMTokenKind,
	/// Identifies an attribute-list declaration with a `NMTOKENS` value type (multiple name tokens).
	NSXMLAttributeNMTokensKind,
	/// Identifies an attribute-list declaration with an enumeration value type (list of all possible values).
	NSXMLAttributeEnumerationKind,
	/// Identifies an attribute-list declaration with a `NOTATION` value type (name of declared notation).
	NSXMLAttributeNotationKind,

	/// Identifies an undefined element declaration.
	NSXMLElementDeclarationUndefinedKind,
	/// Identifies a declaration (`EMPTY`) of an empty element.
	NSXMLElementDeclarationEmptyKind,
	/// Identifies an `ANY` element declaration.
	NSXMLElementDeclarationAnyKind,
	/// Identifies a declaration of an element with mixed content (`(#PCDATA | child)`).
	NSXMLElementDeclarationMixedKind,
	/// Identifies a declaration of an element with child elements.
	NSXMLElementDeclarationElementKind
};

/// The nodes that are exclusive to a DTD.
///
/// Every DTD node has a name. Object value is defined as follows:
/// - **Entity declaration** - the string that that entity resolves to eg `<`
/// - **Attribute declaration** - the default value, if any
/// - **Element declaration** - the validation string
/// - **Notation declaration** - no objectValue
@interface NSXMLDTDNode : NSXMLNode {
@protected
	NSXMLDTDNodeKind _DTDKind;
	NSString *_name;
	NSString *_notationName;
	NSString *_publicID;
	NSString *_systemID;
}

/// Returns an element, attribute, entity, or notation DTD node based on the full XML string.
///
/// - Parameter string: The DTD declaration.
/// - Returns: An `NSXMLDTDNode` object initialized with the DTD declaration in `string`. Returns `nil` if initialization did not succeed, as might occur if the passed-in declaration is malformed.
///
/// The node kind (NSXMLNode) assigned to the returned object -- element, attribute, entity, or notation declaration -- is based on the full XML string that is parsed. To assign a subkind, set the ``dtdKind`` property.
///
/// You may also use the ``XMLNode/dtdNode(withXMLString:)`` or ``XMLNode/init(kind:)`` methods to create `NSXMLDTDNode` instances. However, you cannot use the latter method to create `NSXMLDTDNode` instances for attribute-list declarations.
- (nullable instancetype)initWithXMLString:(NSString *)string NS_DESIGNATED_INITIALIZER; //primitive

- (instancetype)initWithKind:(NSXMLNodeKind)kind options:(NSXMLNodeOptions)options NS_DESIGNATED_INITIALIZER; //primitive

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Returns the receiver's DTD kind.
///
/// The DTD kind is distinct from a `NSXMLDTDNode` object's node kind (returned by the `NSXMLNode` ``XMLNode/kind`` method).
@property NSXMLDTDNodeKind DTDKind; //primitive

/// True if the system id is set. Valid for entities and notations.
@property (readonly, getter=isExternal) BOOL external; //primitive

/// Returns the public identifier associated with the receiver.
///
/// The public ID is applicable to entities and notations. This identifier should be in the default catalog in `/etc/xml/catalog` or in a path specified by the environment variable `XML_CATALOG_FILES`. When the public id is set the system id must also be set.
@property (nullable, copy) NSString *publicID; //primitive

/// Returns the system identifier associated with the receiver.
///
/// This should be a URL that points to a valid DTD. Valid for entities and notations.
@property (nullable, copy) NSString *systemID; //primitive

/// Returns the name of the notation associated with the receiver.
///
/// Notations are applicable to unparsed external entities, processing instructions, and some attribute values.
@property (nullable, copy) NSString *notationName; //primitive

@end

NS_HEADER_AUDIT_END(nullability, sendability)
