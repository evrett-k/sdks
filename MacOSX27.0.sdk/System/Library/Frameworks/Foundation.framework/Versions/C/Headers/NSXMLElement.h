/*	NSXMLElement.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSXMLNode.h>

@class NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSMutableArray, NSEnumerator, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The element nodes in an XML tree structure.
///
/// An ``XMLElement`` object may have child nodes, specifically comment nodes, processing-instruction nodes, text nodes, and other ``XMLElement`` nodes. It may also have attribute nodes and namespace nodes associated with it (however, namespace and attribute nodes are not considered children). Any attempt to add a ``XMLDocument`` node, ``XMLDTD`` node, namespace node, or attribute node as a child raises an exception. If you add a child node to an ``XMLElement`` object and that child already has a parent, ``XMLElement`` raises an exception; the child must be detached or copied first.
///
/// ### Subclassing Notes
///
/// You can subclass `NSXMLElement` if you want element nodes with more specialized attributes or behavior, for example, paragraph and font attributes that specify how the string value of the element should appear.
///
/// #### Methods to Override
///
/// To subclass `NSXMLElement` you need to override the primary initializer, ``init(name:uri:)``, and the methods listed below. In most cases, you need only invoke the superclass implementation, adding any subclass-specific code before or after the invocation, as necessary.
///
///
/// | ``addAttribute(_:)`` | ``removeNamespace(forPrefix:)`` |
/// |---|---|
/// | ``removeAttribute(forName:)`` | ``namespaces`` |
/// | ``attributes`` | ``namespaces`` |
/// | ``attribute(forLocalName:uri:)`` | ``insertChild(_:at:)`` |
/// | ``attributes`` | ``removeChild(at:)`` |
/// | ``addNamespace(_:)`` | ``setChildren(_:)`` |
///
///
/// `NSXMLElement` implements  <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)> to perform a deep comparison: two ``XMLDocument`` objects are not considered equal unless they have the same name, same child nodes, same attributes, and so on. If you want a different standard of comparison, override `isEqual:`.
///
/// #### Special Considerations
///
/// Because of the architecture and data model of NSXML, when it parses and processes a source of XML it cannot know about your subclass unless you override the class method ``XMLDocument/replacementClass(for:)`` to return your custom class in place of an NSXML class. If your custom class has no direct NSXML counterpart—for example, it is a subclass of `NSXMLNode` that represents CDATA sections—then you can walk the tree after it has been created and insert the new node where appropriate.
///
/// Note that you can safely set the root element of the XML document (using the `NSXMLDocument` ``XMLDocument/setRootElement(_:)``method) to be an instance of your subclass because this method only checks to see if the added node is of an element kind (`NSXMLElementKind`). These precautions do not apply, of course, if you are creating an XML tree programmatically.
@interface NSXMLElement : NSXMLNode {
@protected
	NSString *_name;
	id _attributes;
	id _namespaces;
	NSArray *_children;
	BOOL _childrenHaveMutated;
	BOOL _zeroOrOneAttributes;
	BOOL _zeroOrOneNamespaces;
	uint8_t _padding;
	NSString *_URI;	
	NSInteger _prefixIndex;
}

/// Returns an @c NSXMLElement object initialized with the specified name.
///
/// The XML string representation of this object is @c \<name\>\</name\> . This method invokes @c initWithName:URI: with the URI parameter set to @c nil.
/// @param name A string specifying the name of the element.
- (instancetype)initWithName:(NSString *)name;

/// Returns an @c NSXMLElement object initialized with the specified name and URI.
///
/// You can look up the namespace prefix for this element node based on its URI using @c resolvePrefixForNamespaceURI: . This method is the primary initializer for the @c NSXMLElement class.
/// @param name A string that specifies the qualified name of the element.
/// @param URI A string that specifies the namespace URI associated with the element.
- (instancetype)initWithName:(NSString *)name URI:(nullable NSString *)URI NS_DESIGNATED_INITIALIZER; //primitive

/// Returns an @c NSXMLElement object initialized with a specified name and a single text-node child containing a specified value.
///
/// The string representation of this object is @c \<name\>string\</name\> .
/// @param name A string specifying the name of the element.
/// @param string The string value of the receiver's text node.
- (instancetype)initWithName:(NSString *)name stringValue:(nullable NSString *)string;

/// Returns an @c NSXMLElement object created from a specified string containing XML markup.
/// @param string A string containing XML markup for an element.
/// @param error On return, an @c NSError object that describes any errors or warnings resulting from the parsing of the markup.
- (nullable instancetype)initWithXMLString:(NSString *)string error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithKind:(NSXMLNodeKind)kind options:(NSXMLNodeOptions)options;

#if 0
#pragma mark --- Elements by name ---
#endif

/// Returns the child element nodes (as @c NSXMLElement objects) of the receiver that have a specified name.
///
/// If @c name is a qualified name, then this method invokes @c elementsForLocalName:URI: with the URI parameter set to the URI associated with the prefix. Otherwise comparison is based on string equality of the qualified or non-qualified name.
/// @param name A string specifying the name of the child element nodes to find and return.
/// @return An array of @c NSXMLElement objects or an empty array if no matching children can be found.
- (NSArray<NSXMLElement *> *)elementsForName:(NSString *)name;

/// Returns the child element nodes (as @c NSXMLElement objects) of the receiver that are matched with the specified local name and URI.
/// @param localName A string specifying a local name of an element.
/// @param URI A string specifying a URI associated with an element.
/// @return An array of @c NSXMLElement objects or an empty array if no matching children could be found.
- (NSArray<NSXMLElement *> *)elementsForLocalName:(NSString *)localName URI:(nullable NSString *)URI;

#if 0
#pragma mark --- Attributes ---
#endif

/// Adds an attribute node to the receiver.
///
/// If the receiver already has an attribute with the same name, @c attribute replaces the old attribute. The order of multiple attributes is preserved if the @c NSXMLPreserveAttributeOrder option is specified when the element is created.
/// @param attribute An XML node object representing an attribute.
- (void)addAttribute:(NSXMLNode *)attribute; //primitive

/// Removes an attribute node identified by name.
/// @param name A string specifying the name of an attribute.
- (void)removeAttributeForName:(NSString *)name; //primitive

/// The attributes of the receiver.
///
/// In the case of duplicate names, the first attribute with the name is used. To set attributes using an @c NSDictionary object as the input parameter, see @c setAttributesWithDictionary: .
@property (nullable, copy) NSArray<NSXMLNode *> *attributes;

/// Sets the attributes of the receiver based on a name-value dictionary.
///
/// The method uses these names and object values to create @c NSXMLNode objects of kind @c NSXMLAttributeKind. Existing attributes are removed.
/// @param attributes A dictionary of key-value pairs where the attribute name is the key and the object value of the attribute is the dictionary value.
- (void)setAttributesWithDictionary:(NSDictionary<NSString *, NSString *> *)attributes;

/// Returns the attribute node of the receiver with the specified name.
///
/// If @c name is a qualified name, then this method invokes @c attributeForLocalName:URI: with the URI parameter set to the URI associated with the prefix. Otherwise comparison is based on string equality of the qualified or non-qualified name.
/// @param name A string specifying the name of an attribute.
/// @return An XML node object representing a matching attribute or @c nil if no such node was found.
- (nullable NSXMLNode *)attributeForName:(NSString *)name;

/// Returns the attribute node of the receiver that is identified by a local name and URI.
/// @param localName A string specifying the local name of an attribute.
/// @param URI A string identifying the URI associated with an attribute.
/// @return An XML node object representing a matching attribute or @c nil if no such node was found.
- (nullable NSXMLNode *)attributeForLocalName:(NSString *)localName URI:(nullable NSString *)URI; //primitive

#if 0
#pragma mark --- Namespaces ---
#endif

/// Adds a namespace node to the receiver.
///
/// If the receiver already has a namespace with the same name, @c aNamespace is not added.
/// @param aNamespace An XML node object of kind @c NSXMLNamespaceKind.
- (void)addNamespace:(NSXMLNode *)aNamespace; //primitive

/// Removes a namespace node that is identified by a given prefix.
/// @param name A string that is the prefix for a namespace.
- (void)removeNamespaceForPrefix:(NSString *)name; //primitive

/// The namespace nodes of the receiver.
///
/// In the case of duplicate names, the first namespace with the name is used. Set to @c nil to remove all namespace nodes.
@property (nullable, copy) NSArray<NSXMLNode *> *namespaces; //primitive

/// Returns the namespace node with a specified prefix.
/// @param name A string specifying a namespace prefix.
/// @return An @c NSXMLNode object of kind @c NSXMLNamespaceKind or @c nil if there is no namespace node with that prefix.
- (nullable NSXMLNode *)namespaceForPrefix:(NSString *)name;

/// Returns the namespace node with the prefix matching the given qualified name.
///
/// The method looks in the entire namespace chain for the prefix.
/// @param name A string that is the qualified name for a namespace (a qualified name is prefix plus local name).
/// @return An @c NSXMLNode object of kind @c NSXMLNamespaceKind or @c nil if there is no matching namespace node.
- (nullable NSXMLNode *)resolveNamespaceForName:(NSString *)name;

/// Returns the prefix associated with the specified URI.
///
/// The method looks in the entire namespace chain for the URI.
/// @param namespaceURI A string identifying the URI associated with the namespace.
/// @return A string that is the matching prefix or @c nil if it finds no matching prefix.
- (nullable NSString *)resolvePrefixForNamespaceURI:(NSString *)namespaceURI;

#if 0
#pragma mark --- Children ---
#endif

/// Inserts a new child node at a specified location in the receiver's list of child nodes.
///
/// Insertion of the node increments the indexes of sibling nodes after it.
/// @param child An XML node object to be inserted as a child of the receiver.
/// @param index An integer identifying a position in the receiver's list of children. An exception is raised if @c index is out of bounds.
- (void)insertChild:(NSXMLNode *)child atIndex:(NSUInteger)index; //primitive

/// Inserts an array of child nodes at a specified location in the receiver's list of children.
///
/// Insertion of the nodes increases the indexes of sibling nodes after them by the count of @c children.
/// @param children An array of XML node objects to add as children of the receiver.
/// @param index An integer identifying a position in the receiver's list of children. An exception is raised if @c index is out of bounds.
- (void)insertChildren:(NSArray<NSXMLNode *> *)children atIndex:(NSUInteger)index;

/// Removes the child node of the receiver identified by a given index.
///
/// The XML node object is released upon removal. The indices of subsequent children are decremented by one.
/// @param index An integer identifying the node in the receiver's list of children to remove. An exception is raised if @c index is out of bounds.
- (void)removeChildAtIndex:(NSUInteger)index; //primitive

/// Removes all existing children and replaces them with the new children.
///
/// Set @c children to @c nil to simply remove all children.
/// @param children An array of @c NSXMLElement objects or @c NSXMLNode objects.
- (void)setChildren:(nullable NSArray<NSXMLNode *> *)children; //primitive

/// Adds a child node at the end of the receiver's current list of children.
///
/// The new node has an index value that is one greater than the last of the current children.
/// @param child An XML node object to add to the receiver's children.
- (void)addChild:(NSXMLNode *)child;

/// Replaces a child node at a specified location with another child node.
///
/// The replaced XML node object is released upon removal.
/// @param index An integer identifying a position in the receiver's list of children. An exception is raised if @c index is out of bounds.
/// @param node An XML node object that will replace the current child.
- (void)replaceChildAtIndex:(NSUInteger)index withNode:(NSXMLNode *)node;

/// Coalesces adjacent text nodes of the receiver that you have explicitly added, optionally including CDATA sections.
///
/// A text node with a value of an empty string is removed. When you process an input source of XML, adjacent text nodes are automatically normalized. You should invoke this method (with @c preserve as @c NO) before using the @c NSXMLNode methods @c objectsForXQuery:constants:error: or @c nodesForXPath:error: .
/// @param preserve @c YES if CDATA sections are left alone as text nodes, @c NO otherwise.
- (void)normalizeAdjacentTextNodesPreservingCDATA:(BOOL)preserve;

@end

@interface NSXMLElement (NSDeprecated)
/// Sets the attributes based on a name-value dictionary.
///
/// @deprecated This method is deprecated because it does not function properly. Use @c setAttributesWithDictionary: instead.
/// @param attributes A dictionary of key-value pairs where the attribute name is the key and the object value of the attribute is the dictionary value.
- (void)setAttributesAsDictionary:(NSDictionary *)attributes API_DEPRECATED_WITH_REPLACEMENT("setAttributesWithDictionary:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
