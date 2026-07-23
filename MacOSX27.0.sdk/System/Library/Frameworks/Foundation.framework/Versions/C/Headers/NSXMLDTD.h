/*	NSXMLDTD.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSXMLNode.h>

@class NSArray<ObjectType>, NSData, NSMutableDictionary;
@class NSXMLDTDNode;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A representation of a Document Type Definition.
///
/// An instance of the ``XMLDTD`` class is held as a property of an ``XMLDocument`` instance, accessed through the ``XMLDocument`` property ``XMLDocument/dtd``.
///
/// In the data model, an ``XMLDTD`` object is conceptually similar to namespace and attribute nodes: it is not considered to be a child of the ``XMLDocument`` object although it is closely associated with it. It is at the "root" of a shallow tree consisting primarily of nodes representing DTD declarations. Acceptable child nodes are instances of the ``XMLDTDNode`` class as well as ``XMLNode`` objects representing comment nodes and processing-instruction nodes.
///
/// You create an `NSXMLDTD` object in one of three ways:
///
/// - By processing an XML document with its own internal (in-line) DTD
/// - By process a standalone (external) DTD
/// - Programmatically
///
/// Once an ``XMLDTD`` instance is in place, you can add, remove, and change the ``XMLDTDNode`` objects representing various DTD declarations. When you write the document out as XML, the new or modified internal DTD is included (assuming you set the DTD in the ``XMLDocument`` instance). You may also programmatically create an external DTD and write that out to its own file.
@interface NSXMLDTD : NSXMLNode

#if 0
#pragma mark --- Properties ---
#endif

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithKind:(NSXMLNodeKind)kind options:(NSXMLNodeOptions)options API_UNAVAILABLE(macos, ios, watchos, tvos);
/// Initializes and returns an `NSXMLDTD` object created from the DTD declarations in a URL-referenced source.
///
/// - Parameters:
///   - url: An `NSURL` object identifying a URL source.
///   - mask: A bit mask specifying input options; bit-OR multiple options. The current valid options are `NSXMLNodePreserveWhitespace` and `NSXMLNodePreserveEntities`; these constants are described in the "Constants" section of the ``XMLNode`` reference.
///   - error: On return, this parameter holds an `NSError` object describing any errors and warnings related to parsing and remote connection.
/// - Returns: An initialized `NSXMLDTD` object or `nil` if initialization fails because of parsing errors or other reasons.
///
/// You use this method to create a stand-alone DTD which you can thereafter query and use for validation. You can associate the DTD created through this message with a document by setting the ``XMLDocument/dtd`` property on an ``XMLDocument`` object.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url options:(NSXMLNodeOptions)mask error:(NSError **)error;
/// Initializes and returns an `NSXMLDTD` object created from the DTD declarations encapsulated in an `NSData` object.
///
/// - Parameters:
///   - data: A data object containing DTD declarations.
///   - mask: A bit mask specifying input options; bit-OR multiple options. The current valid options are `NSXMLNodePreserveWhitespace` and `NSXMLNodePreserveEntities`; these constants are described in the "Constants" section of the ``XMLNode`` reference.
///   - error: On return, this parameter holds an `NSError` object describing any errors and warnings related to parsing and remote connection.
/// - Returns: An initialized `NSXMLDTD` object or `nil` if initialization fails because of parsing errors or other reasons.
///
/// This method is the designated initializer for the `NSXMLDTD` class. You use this method to create a stand-alone DTD which you can thereafter query and use for validation. You can associate the DTD created through this message with a document by setting the ``XMLDocument/dtd`` property on an ``XMLDocument`` object.
- (nullable instancetype)initWithData:(NSData *)data options:(NSXMLNodeOptions)mask error:(NSError **)error NS_DESIGNATED_INITIALIZER; //primitive

/// Returns the receiver's public identifier.
///
/// This identifier should be in the default catalog in `/etc/xml/catalog` or in a path specified by the environment variable `XML_CATALOG_FILES`. When the public id is set the system id must also be set.
@property (nullable, copy) NSString *publicID; //primitive

/// Returns the receiver's system identifier.
///
/// This should be a URL that points to a valid DTD.
@property (nullable, copy) NSString *systemID; //primitive

#if 0
#pragma mark --- Children ---
#endif

/// Inserts a child node in the receiver's list of children at a specific location in the list.
///
/// - Parameters:
///   - child: An XML-node object that represents the child to insert.
///   - index: An integer identifying the location in the receiver's list of children to insert `child`. The indices of subsequent children in the list are incremented by one.
- (void)insertChild:(NSXMLNode *)child atIndex:(NSUInteger)index; //primitive

/// Inserts an array of child nodes at a specified location in the receiver's list of children.
///
/// - Parameters:
///   - children: An array of ``XMLNode`` objects to insert as children of the receiver.
///   - index: An integer identifying the location in the list of current children to make the insertion. The indices of subsequent children in the list are incremented by the number of inserted children.
- (void)insertChildren:(NSArray<NSXMLNode *> *)children atIndex:(NSUInteger)index;

/// Removes the child node at a particular location in the receiver's list of children.
///
/// - Parameter index: An integer identifying the child node to remove. The indices of subsequent children in the list are decremented by one.
///
/// The removed child node is released.
- (void)removeChildAtIndex:(NSUInteger)index; //primitive

/// Removes all existing children of the receiver and replaces them with an array of new child nodes.
///
/// - Parameter children: An array of ``XMLNode`` objects. To remove all existing children, pass in `nil`.
///
/// Replaced or removed child nodes are released.
- (void)setChildren:(nullable NSArray<NSXMLNode *> *)children; //primitive

/// Adds a child node to the end of the list of existing children.
///
/// - Parameter child: The node object to add to the existing children.
- (void)addChild:(NSXMLNode *)child;

/// Replaces a child at a particular index with another child.
///
/// - Parameters:
///   - index: An integer identifying the position of a node in the receiver's list of child nodes.
///   - node: An ``XMLNode`` object to replace the object at `index`.
///
/// The replaced child node is released.
- (void)replaceChildAtIndex:(NSUInteger)index withNode:(NSXMLNode *)node;

#if 0
#pragma mark --- Accessors ---
#endif

/// Returns the DTD node representing the entity declaration matching this name.
///
/// - Parameter name: A string that is the name of an entity.
/// - Returns: An autoreleased ``XMLDTDNode`` object, or `nil` if there is no match.
- (nullable NSXMLDTDNode *)entityDeclarationForName:(NSString *)name; //primitive

/// Returns the DTD node representing the notation declaration identified by the specified notation name.
///
/// - Parameter name: A string that is the name of a notation.
/// - Returns: An autoreleased ``XMLDTDNode`` object, or `nil` if there is no match.
- (nullable NSXMLDTDNode *)notationDeclarationForName:(NSString *)name; //primitive

/// Returns the DTD node representing an element declaration for a specified element.
///
/// - Parameter name: A string that is the name of an element.
/// - Returns: An autoreleased ``XMLDTDNode`` object, or `nil` if there is no match.
- (nullable NSXMLDTDNode *)elementDeclarationForName:(NSString *)name; //primitive

/// Returns the DTD node representing an attribute-list declaration for a given attribute and its element.
///
/// - Parameters:
///   - name: A string object identifying the name of an attribute.
///   - elementName: A string object identifying the name of an element.
/// - Returns: An autoreleased ``XMLDTDNode`` object, or `nil` if there is no matching attribute-list declaration.
///
/// For example, in the attribute-list declaration `<!ATTLIST person idnum CDATA "0000">`, "idnum" would correspond to `attrName` and "person" would correspond to `elementName`.
- (nullable NSXMLDTDNode *)attributeDeclarationForName:(NSString *)name elementName:(NSString *)elementName; //primitive

/// Returns a DTD node representing the predefined entity declaration with the specified name.
///
/// - Parameter name: A string identifying a predefined entity declaration.
/// - Returns: An autoreleased ``XMLDTDNode`` object, or `nil` if there is no match for `name`.
///
/// The five predefined entity references (or character references) are `&lt;` (less-than sign), `&gt;` (greater-than sign), `&amp;` (ampersand), `&quot;` (quotation mark), and `&apos;` (apostrophe).
+ (nullable NSXMLDTDNode *)predefinedEntityDeclarationForName:(NSString *)name;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
