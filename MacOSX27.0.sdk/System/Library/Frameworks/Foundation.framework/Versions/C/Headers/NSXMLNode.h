/*	NSXMLNode.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSXMLNodeOptions.h>

@class NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSError, NSString, NSURL;
@class NSXMLElement, NSXMLDocument;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// `NSXMLNode` declares the following constants of type NSXMLNodeKind for specifying a node's kind in the initializer methods ``XMLNode/init(kind:)`` and ``XMLNode/init(kind:options:)``:
typedef NS_ENUM(NSUInteger, NSXMLNodeKind) {
	/// Indicates a node object created without a valid kind being specified (as returned by the @c kind property).
	NSXMLInvalidKind = 0,
	/// Specifies a document node.
	NSXMLDocumentKind,
	/// Specifies an element node.
	NSXMLElementKind,
	/// Specifies an attribute node.
	NSXMLAttributeKind,
	/// Specifies a namespace node.
	NSXMLNamespaceKind,
	/// Specifies a processing-instruction node.
	NSXMLProcessingInstructionKind,
	/// Specifies a comment node.
	NSXMLCommentKind,
	/// Specifies a text node.
	NSXMLTextKind,
	/// Specifies a document-type declaration (DTD) node.
	NSXMLDTDKind NS_SWIFT_NAME(DTDKind),
	/// Specifies an entity-declaration node.
	NSXMLEntityDeclarationKind,
	/// Specifies an attribute-list declaration node.
	NSXMLAttributeDeclarationKind,
	/// Specifies an element declaration node.
	NSXMLElementDeclarationKind,
	/// Specifies a notation declaration node.
	NSXMLNotationDeclarationKind
};

// initWithKind options
//  NSXMLNodeOptionsNone
//  NSXMLNodePreserveAll
//  NSXMLNodePreserveNamespaceOrder
//  NSXMLNodePreserveAttributeOrder
//  NSXMLNodePreserveEntities
//  NSXMLNodePreservePrefixes
//  NSXMLNodeIsCDATA
//  NSXMLNodeExpandEmptyElement
//  NSXMLNodeCompactEmptyElement
//  NSXMLNodeUseSingleQuotes
//  NSXMLNodeUseDoubleQuotes

// Output options
//  NSXMLNodePrettyPrint

/*!
    @class NSXMLNode
    @abstract The basic unit of an XML document.
*/

/// The nodes in the abstract, logical tree structure that represents an XML document.
///
/// Node objects can be of different kinds, corresponding to the following markup constructs in an XML document: element, attribute, text, processing instruction, namespace, and comment. In addition, a document-node object (specifically, an instance of ``XMLDocument``) represents an XML document in its entirety. ``XMLNode`` objects can also represent document type declarations as well as declarations in Document Type Definitions (DTDs). Class factory methods of ``XMLNode`` enable you to create nodes of each kind. Only document, element, and DTD nodes may have child nodes.
///
/// Among the XML family of classes (excluding ``XMLParser``) the ``XMLNode`` class is the base class. Inheriting from it are the classes ``XMLElement``, ``XMLDocument``, ``XMLDTD``, and ``XMLDTDNode``. ``XMLNode`` specifies the interface common to all XML node objects and defines common node behavior and attributes, for example hierarchy level, node name and value, tree traversal, and the ability to emit representative XML markup text.
///
/// ### Subclassing Notes
///
/// You can subclass ``XMLNode`` if you want nodes of kinds different from the supported ones, You can also create a subclass with more specialized attributes or behavior than ``XMLNode``.
///
/// #### Methods to Override
///
/// To subclass ``XMLNode`` you need to override the primary initializer, ``init(kind:options:)``, and the methods listed below. In most cases, you need only invoke the superclass implementation, adding any subclass-specific code before or after the invocation, as necessary.
///
///
/// | ``kind`` | ``parent`` |
/// |---|---|
/// | ``name`` | ``child(at:)`` |
/// | ``name`` | ``childCount`` |
/// | ``objectValue`` | ``children`` |
/// | ``objectValue`` | ``detach()`` |
/// | ``stringValue`` | ``localName`` |
/// | ``setStringValue(_:resolvingEntities:)`` | ``prefix`` |
/// | ``index`` | ``uri`` |
///
///
/// By default ``XMLNode`` implements the `NSObject` <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)> method to perform a deep comparison: two ``XMLNode`` objects are not considered equal unless they have the same name, same child nodes, same attributes, and so on. The comparison looks at the node and its children, but does not include the node's parent. If you want a different standard of comparison, override `isEqual:`.
///
/// #### Special Considerations
///
/// Because of the architecture and data model of NSXML, when it parses and processes a source of XML it cannot know about your subclass unless you override the ``XMLDocument`` class method ``XMLDocument/replacementClass(for:)`` to return your custom class in place of an NSXML class. If your custom class has no direct NSXML counterpart—for example, it is a subclass of ``XMLNode`` that represents CDATA sections—then you can walk the tree after it has been created and insert the new node where appropriate.
@interface NSXMLNode : NSObject <NSCopying> {
@protected
#if __LP64__
    NSXMLNode *_parent;
    id _objectValue;
    NSXMLNodeKind _kind:4;
    uint32_t     _index:28;
@private
    int32_t _private;
#else
    NSXMLNodeKind _kind;
    NSXMLNode *_parent;
    uint32_t _index;
    id _objectValue;
#endif
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Returns an @c NSXMLNode instance initialized with the constant indicating node kind.
///
/// Invokes @c initWithKind:options: with options set to @c NSXMLNodeOptionsNone.
///
/// Do not use this initializer for creating instances of @c NSXMLDTDNode for attribute-list declarations. Instead, use the @c DTDNodeWithXMLString: class method of this class or the @c initWithXMLString: method of the @c NSXMLDTDNode class.
/// @param kind An @c enum constant of type @c NSXMLNodeKind that indicates the type of node.
- (instancetype)initWithKind:(NSXMLNodeKind)kind;

/// Returns an @c NSXMLNode instance initialized with the constant indicating node kind and one or more initialization options.
///
/// Do not use this initializer for creating instances of @c NSXMLDTDNode for attribute-list declarations. Instead, use the @c DTDNodeWithXMLString: class method of this class or the @c initWithXMLString: method of the @c NSXMLDTDNode class.
/// @param kind An @c enum constant of type @c NSXMLNodeKind that indicates the type of node.
/// @param options One or more constants that specify initialization options; if there are multiple constants, bit-OR them together.
- (instancetype)initWithKind:(NSXMLNodeKind)kind options:(NSXMLNodeOptions)options NS_DESIGNATED_INITIALIZER; //primitive

/// Returns an empty document node.
///
/// Returns an @c NSXMLDocument instance without a root element or XML-declaration information (version, encoding, standalone flag). Returns @c nil if the object couldn't be created.
+ (id)document;

/// Returns an @c NSXMLDocument object initialized with a given root element.
/// @param element An @c NSXMLElement object representing an element.
+ (id)documentWithRootElement:(NSXMLElement *)element;

/// Returns an @c NSXMLElement object with a given tag identifier, or name.
///
/// The equivalent XML markup is @c \<name\>\</name\> .
/// @param name A string that is the name (or tag identifier) of an element.
+ (id)elementWithName:(NSString *)name;

/// Returns an element whose fully qualified name is specified.
/// @param name A string that is the name (or tag identifier) of an element.
/// @param URI A URI (Universal Resource Identifier) that qualifies @c name.
+ (id)elementWithName:(NSString *)name URI:(NSString *)URI;

/// Returns an @c NSXMLElement object with a single text-node child containing the specified text.
///
/// The equivalent XML markup is @c \<name\>string\</name\> .
/// @param name A string that is the name (tag identifier) of the element.
/// @param string A string that is the content of the receiver's text node.
+ (id)elementWithName:(NSString *)name stringValue:(NSString *)string;

/// Returns an @c NSXMLElement object with the given tag (name), attributes, and children.
/// @param name A string that is the name (tag identifier) of the element.
/// @param children An array of @c NSXMLElement objects or @c NSXMLNode objects. Specify @c nil if there are no children to add to this node object.
/// @param attributes An array of @c NSXMLNode objects of kind @c NSXMLAttributeKind. Specify @c nil if there are no attributes to add to this node object.
+ (id)elementWithName:(NSString *)name children:(nullable NSArray<NSXMLNode *> *)children attributes:(nullable NSArray<NSXMLNode *> *)attributes;

/// Returns an @c NSXMLNode object representing an attribute node with a given name and string.
///
/// For example, in the attribute "id='12345'", "id" is the attribute name and "12345" is the attribute value.
/// @param name A string that is the name of an attribute.
/// @param stringValue A string that is the value of an attribute.
+ (id)attributeWithName:(NSString *)name stringValue:(NSString *)stringValue;

/// Returns an @c NSXMLNode object representing an attribute node with a given qualified name and string.
///
/// For example, in the attribute "bst:id='12345'", "bst" is the name qualifier (derived from the URI), "id" is the attribute name, and "12345" is the attribute value.
/// @param name A string that is the name of an attribute.
/// @param URI A URI (Universal Resource Identifier) that qualifies @c name.
/// @param stringValue A string that is the value of the attribute.
+ (id)attributeWithName:(NSString *)name URI:(NSString *)URI stringValue:(NSString *)stringValue;

/// Returns an @c NSXMLNode object representing a namespace with a specified name and URI.
///
/// The equivalent namespace declaration in XML markup is @c xmlns:name="value" .
/// @param name A string that is the name of the namespace. Specify an empty string for @c name to get the default namespace.
/// @param stringValue A string that identifies the URI associated with the namespace.
+ (id)namespaceWithName:(NSString *)name stringValue:(NSString *)stringValue;

/// Returns an @c NSXMLNode object representing a processing instruction with a specified name and value.
///
/// The equivalent XML markup is @c \<?name\ value?\> .
/// @param name A string that is the name of the processing instruction.
/// @param stringValue A string that is the value of the processing instruction.
+ (id)processingInstructionWithName:(NSString *)name stringValue:(NSString *)stringValue;

/// Returns an @c NSXMLNode object representing a comment node containing given text.
/// @param stringValue A string specifying the text of the comment. You may specify @c nil or an empty string.
+ (id)commentWithStringValue:(NSString *)stringValue;

/// Returns an @c NSXMLNode object representing a text node with specified content.
/// @param stringValue A string that is the textual content of the node.
+ (id)textWithStringValue:(NSString *)stringValue;

/// Returns an @c NSXMLDTDNode object representing the DTD declaration for an element, attribute, entity, or notation based on a given string.
///
/// @c NSXMLNode is able to assign the created node object a kind by parsing the string. Note that if an attribute-list declaration (@c \<!ATTLIST...\>) has multiple attributes, @c NSXMLNode only creates an @c NSXMLDTDNode object for the last attribute in the declaration.
/// @param string A string that is a DTD declaration. The receiver parses this string to determine the kind of DTD node to create.
+ (nullable id)DTDNodeWithXMLString:(NSString *)string;

#if 0
#pragma mark --- Properties ---
#endif

/// Returns the kind of node the receiver is as a constant of type @c NSXMLNodeKind.
///
/// @c NSXMLNode objects can represent documents, elements, attributes, namespaces, text, processing instructions, comments, document type declarations, and specific declarations within DTDs.
@property (readonly) NSXMLNodeKind kind; //primitive

/// The name of the receiver.
///
/// This property is applicable only to @c NSXMLNode objects representing elements, attributes, namespaces, processing instructions, and DTD-declaration nodes. If the receiver is not an object of one of these kinds, this property returns @c nil. If the name is associated with a namespace, the qualified name is returned.
@property (nullable, copy) NSString *name; //primitive

/// The object value of the receiver.
///
/// The object value may be the same as the value returned by @c stringValue. For nodes without content (for example, document nodes), this property returns the string value, or an empty string if there is no string value.
@property (nullable, retain) id objectValue; //primitive

/// The content of the receiver as a string value.
///
/// If the receiver is a node object of element kind, the content is that of any text-node children. This method recursively visits element nodes and concatenates their text nodes in document order with no intervening spaces.
@property (nullable, copy) NSString *stringValue; //primitive

/// Sets the content as with @c setStringValue:, but when @c resolve is @c YES, character references, predefined entities and user entities available in the document's DTD are resolved. Entities not available in the DTD remain in their entity form.
///
/// User-defined entities not declared in the DTD remain in their unresolved form. This method can only be invoked on @c NSXMLNode objects that may have content. Setting the string value of a node object removes all existing children, including processing instructions and comments. Setting the string value of an element node object creates a text node as the sole child.
/// @param string A string to assign as the value of the receiver.
/// @param resolve @c YES to resolve character references, predefined entities, and user-defined entities as declared in the associated DTD; @c NO otherwise.
- (void)setStringValue:(NSString *)string resolvingEntities:(BOOL)resolve; //primitive

#if 0
#pragma mark --- Tree Navigation ---
#endif

/// The index of the receiver identifying its position relative to its sibling nodes.
///
/// The first child node of a parent has an index of zero.
@property (readonly) NSUInteger index; //primitive

/// The nesting level of the receiver within the tree hierarchy.
///
/// The root element of a document has a nesting level of one.
@property (readonly) NSUInteger level;

/// The @c NSXMLDocument object containing the root element and representing the XML document as a whole.
///
/// If the receiver is a standalone node (that is, a node at the head of a detached branch of the tree), this property returns @c nil.
@property (nullable, readonly, retain) NSXMLDocument *rootDocument;

/// The parent node of the receiver.
///
/// Document nodes and standalone nodes (that is, the root of a detached branch of a tree) have no parent, and sending this message to them returns @c nil. A one-to-one relationship does not always exist between a parent and its children; although a namespace or attribute node cannot be a child, it still has a parent element.
@property (nullable, readonly, copy) NSXMLNode *parent; //primitive

/// The number of child nodes the receiver has.
///
/// The receiver should be an @c NSXMLNode object representing a document, element, or document type declaration. For performance reasons, use this property instead of getting the count from the array returned by @c children.
@property (readonly) NSUInteger childCount; //primitive

/// An immutable array containing the child nodes of the receiver (as @c NSXMLNode objects).
@property (nullable, readonly, copy) NSArray<NSXMLNode *> *children; //primitive

/// Returns the child node of the receiver at the specified location.
///
/// The receiver should be an @c NSXMLNode object representing a document, element, or document type declaration. The returned node object can represent an element, comment, text, or processing instruction.
/// @param index An integer specifying a node position in the receiver's array of children. If @c index is out of bounds, an exception is raised.
- (nullable NSXMLNode *)childAtIndex:(NSUInteger)index; //primitive

/// The previous @c NSXMLNode object that is a sibling node to the receiver.
///
/// This object will have an index value that is one less than the receiver's. If there are no more previous siblings (that is, other child nodes of the receiver's parent) the property returns @c nil.
@property (nullable, readonly, copy) NSXMLNode *previousSibling;

/// The next @c NSXMLNode object that is a sibling node to the receiver.
///
/// This object will have an index value that is one more than the receiver's. If there are no more subsequent siblings (that is, other child nodes of the receiver's parent) the property returns @c nil.
@property (nullable, readonly, copy) NSXMLNode *nextSibling;

/// The previous @c NSXMLNode object in document order.
///
/// You use this property to "walk" backward through the tree structure representing an XML document or document section. Document order is the natural order that XML constructs appear in markup text. If you send this message to the first node in the tree (that is, the root element), @c nil is returned. @c NSXMLNode bypasses namespace and attribute nodes when it traverses a tree in document order.
@property (nullable, readonly, copy) NSXMLNode *previousNode;

/// The next @c NSXMLNode object in document order.
///
/// You use this property to "walk" forward through the tree structure representing an XML document or document section. Document order is the natural order that XML constructs appear in markup text. If you send this message to the last node in the tree, @c nil is returned. @c NSXMLNode bypasses namespace and attribute nodes when it traverses a tree in document order.
@property (nullable, readonly, copy) NSXMLNode *nextNode;

/// Detaches the receiver from its parent node.
///
/// This method is applicable to @c NSXMLNode objects representing elements, text, comments, processing instructions, attributes, and namespaces. Once the node object is detached, you can add it as a child node of another parent.
- (void)detach; //primitive

/// The XPath expression identifying the receiver's location in the document tree.
///
/// For example, this property might return a string such as "foo/bar[2]/baz". The result of this property can be used directly in the @c nodesForXPath:error: and @c objectsForXQuery:constants:error: methods.
@property (nullable, readonly, copy) NSString *XPath;

#if 0
#pragma mark --- QNames ---
#endif

/// The local name of the receiver.
///
/// The local name is the part of a node name that follows a namespace-qualifying colon or the full name if there is no colon. For example, "chapter" is the local name in the qualified name "acme:chapter".
@property (nullable, readonly, copy) NSString *localName; //primitive

/// The prefix of the receiver's name.
///
/// The prefix is the part of a namespace-qualified name that precedes the colon. For example, "acme" is the prefix in the qualified name "acme:chapter". Returns an empty string if the receiver's name is not qualified by a namespace.
@property (nullable, readonly, copy) NSString *prefix; //primitive

/// The URI associated with the receiver.
///
/// A node's URI is derived from its namespace or a document's URI; for documents, the URI comes either from the parsed XML or is explicitly set. You cannot change the URI for a particular node other than for a namespace or document node.
@property (nullable, copy) NSString *URI; //primitive

/// Returns the local name from the specified qualified name.
///
/// For example, if the qualified name is "bst:title", this method returns "title".
/// @param name A string that is a qualified name.
+ (NSString *)localNameForName:(NSString *)name;

/// Returns the prefix from the specified qualified name.
///
/// For example, if the qualified name is "bst:title", this method returns "bst".
/// @param name A string that is a qualified name.
+ (nullable NSString *)prefixForName:(NSString *)name;


/// Returns an @c NSXMLNode object representing one of the predefined namespaces with the specified prefix.
/// @param name A string specifying a prefix for a predefined namespace, for example "xml", "xs", or "xsi". If something other than a predefined-namespace prefix is specified, the method returns @c nil.
+ (nullable NSXMLNode *)predefinedNamespaceForPrefix:(NSString *)name;

#if 0
#pragma mark --- Output ---
#endif

/*!
    @abstract Used for debugging. May give more information than XMLString.
*/
@property (readonly, copy) NSString *description;

/// The string representation of the receiver as it would appear in an XML document.
///
/// The returned string includes the string representations of all children. This property invokes @c XMLStringWithOptions: with an @c options argument of @c NSXMLNodeOptionsNone.
@property (readonly, copy) NSString *XMLString;

/// Returns the string representation of the receiver as it would appear in an XML document, with one or more output options specified.
///
/// The returned string includes the string representations of all children.
/// @param options One or more @c enum constants identifying an output option; bit-OR multiple constants together.
- (NSString *)XMLStringWithOptions:(NSXMLNodeOptions)options;

/// Returns a string object encapsulating the receiver's XML in canonical form.
///
/// Be sure to set the input option @c NSXMLNodePreserveWhitespace for true canonical form. The canonical form of an XML document is defined by the World Wide Web Consortium at http://www.w3.org/TR/xml-c14n.
/// @param comments @c YES to preserve comments, @c NO otherwise.
- (NSString *)canonicalXMLStringPreservingComments:(BOOL)comments;

#if 0
#pragma mark --- XPath/XQuery ---
#endif

/// Returns the nodes resulting from executing an XPath query upon the receiver.
///
/// The receiver acts as the context item for the query ("."). If you have explicitly added adjacent text nodes as children of an element, you should invoke the @c NSXMLElement method @c normalizeAdjacentTextNodesPreservingCDATA: (with an argument of @c NO) on the element before applying any XPath queries to it; this method coalesces these text nodes.
/// @param xpath A string that expresses an XPath query.
/// @param error If query errors occur, indirectly returns an @c NSError object describing the errors.
/// @return An array of @c NSXMLNode objects that match the query, or an empty array if there are no matches.
- (nullable NSArray<__kindof NSXMLNode *> *)nodesForXPath:(NSString *)xpath error:(NSError **)error;

/// Returns the objects resulting from executing an XQuery query upon the receiver.
///
/// The receiver acts as the context item for the query ("."). If the receiver has been changed after parsing to have multiple adjacent text nodes, you should invoke the @c NSXMLElement method @c normalizeAdjacentTextNodesPreservingCDATA: (with an argument of @c NO) to coalesce the text nodes before querying.
/// @param xquery A string that expresses an XQuery query.
/// @param constants A dictionary containing externally declared constants where the name of each constant variable is a key.
/// @param error If query errors occur, indirectly returns an @c NSError object describing the errors.
/// @return An array whose elements are kinds of @c NSArray, @c NSData, @c NSDate, @c NSNumber, @c NSString, @c NSURL, or @c NSXMLNode.
- (nullable NSArray *)objectsForXQuery:(NSString *)xquery constants:(nullable NSDictionary<NSString *, id> *)constants error:(NSError **)error;

/// Returns the objects resulting from executing an XQuery query upon the receiver.
///
/// This convenience method invokes @c objectsForXQuery:constants:error: with @c nil for the @c constants dictionary.
/// @param xquery A string that expresses an XQuery query.
/// @param error If query errors occur, indirectly returns an @c NSError object describing the errors.
- (nullable NSArray *)objectsForXQuery:(NSString *)xquery error:(NSError **)error;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
