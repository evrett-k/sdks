/*	NSXMLDocument.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSXMLNode.h>

@class NSData, NSXMLDTD, NSXMLDocument, NSDictionary<KeyType, ObjectType>, NSArray<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// Input options
//  NSXMLNodeOptionsNone
//  NSXMLNodePreserveAll
//  NSXMLNodePreserveNamespaceOrder
//  NSXMLNodePreserveAttributeOrder
//  NSXMLNodePreserveEntities
//  NSXMLNodePreservePrefixes
//  NSXMLNodePreserveCDATA
//  NSXMLNodePreserveEmptyElements
//  NSXMLNodePreserveQuotes
//  NSXMLNodePreserveWhitespace
//  NSXMLNodeLoadExternalEntities
//  NSXMLNodeLoadExternalEntitiesSameOriginOnly
	
//  NSXMLDocumentTidyHTML
//  NSXMLDocumentTidyXML

//  NSXMLDocumentValidate

// Output options
//  NSXMLNodePrettyPrint
//  NSXMLDocumentIncludeContentTypeDeclaration

/// Type used to define the kind of document content.
///
/// For possible values, see <doc:xmldocument/document_content_types>.
typedef NS_ENUM(NSUInteger, NSXMLDocumentContentKind) {
	/// The default type of document content type, which is XML.
	NSXMLDocumentXMLKind = 0,
	/// The document output is XHTML. This is set automatically if the @c NSXMLDocumentTidyHTML option is set and NSXML detects HTML.
	NSXMLDocumentXHTMLKind,
	/// Outputs empty tags in HTML without a close tag, such as @c \<br\> .
	NSXMLDocumentHTMLKind,
	/// Outputs the string value of the document by extracting the string values from all text nodes.
	NSXMLDocumentTextKind
};

/// An XML document as internalized into a logical tree structure.
///
/// An ``XMLDocument`` object can have multiple child nodes but only one element, the root element. Any other node must be a ``XMLNode`` object representing a comment or a processing instruction. If you attempt to add any other kind of child node to an ``XMLDocument`` object, such as an attribute, namespace, another document object, or an element other than the root, ``XMLDocument`` raises an exception. If you add a valid child node and that object already has a parent, ``XMLDocument`` raises an exception. An ``XMLDocument`` object may also have document-global attributes, such as XML version, character encoding, referenced DTD, and MIME type.
///
/// The initializers of the ``XMLDocument`` class read an external source of XML, whether it be a local file or remote website, parse it, and process it into the tree representation. You can also construct an ``XMLDocument`` programmatically. There are accessor methods for getting and setting document attributes, methods for transforming documents using XSLT, a method for dynamically validating a document, and methods for printing out the content of an ``XMLDocument`` as XML, XHTML, HTML, or plain text.
///
/// The ``XMLDocument`` class is thread-safe as long as any given instance is used only in one thread.
///
/// ### Subclassing Notes
///
/// #### Methods to Override
///
/// To subclass `NSXMLDocument` you need to override the primary initializer, ``init(data:options:)``, and the methods listed below. In most cases, you need only invoke the superclass implementation, adding any subclass-specific code before or after the invocation, as necessary.
///
/// - ``rootElement()``
/// - ``setChildren(_:)``
/// - ``removeChild(at:)``
/// - ``insertChild(_:at:)``
/// - ``characterEncoding``
/// - ``characterEncoding``
/// - ``documentContentKind``
/// - ``documentContentKind``
/// - ``dtd``
/// - ``mimeType``
/// - ``isStandalone``
/// - ``version``
/// - ``version``
///
/// By default `NSXMLDocument` implements the `NSObject` <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)> method to perform a deep comparison: two `NSXMLDocument` objects are not considered equal unless they have the same name, same child nodes, same attributes, and so on. The comparison does not consider the parent node (and hence the node's location). If you want a different standard of comparison, override `isEqual:`.
///
/// #### Special Considerations
///
/// Because of the architecture and data model of NSXML, when it parses and processes a source of XML it cannot know about your subclass unless you override the class method ``replacementClass(for:)`` to return your custom class in place of an `NSXML` class. If your custom class has no direct `NSXML` counterpart—for example, it is a subclass of `NSXMLNode` that represents CDATA sections—then you can walk the tree after it has been created and insert the new node where appropriate.
@interface NSXMLDocument : NSXMLNode {
@protected
	NSString *_encoding;
	NSString *_version;
	NSXMLDTD *_docType;
	NSArray *_children;
	BOOL _childrenHaveMutated;
	BOOL _standalone;
	int8_t padding[2];
	NSXMLElement *_rootElement;
	NSString *_URI;
	id	 _extraIvars;
	NSUInteger _fidelityMask;
	NSXMLDocumentContentKind _contentKind;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Initializes and returns an @c NSXMLDocument object created from a string containing XML markup text.
///
/// The encoding of the document is set to UTF-8.
/// @param string A string object containing XML markup text.
/// @param mask A bit mask for input options. You can specify multiple options by bit-OR'ing them.
/// @param error An error object that, on return, identifies any parsing errors and warnings or connection problems.
- (nullable instancetype)initWithXMLString:(NSString *)string options:(NSXMLNodeOptions)mask error:(NSError **)error;

/// Initializes and returns an @c NSXMLDocument object created from the XML or HTML contents of a URL-referenced source.
/// @param url An @c NSURL object specifying a URL source.
/// @param mask A bit mask for input options. You can specify multiple options by bit-OR'ing them.
/// @param error An error object that, on return, identifies any parsing errors and warnings or connection problems.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url options:(NSXMLNodeOptions)mask error:(NSError **)error;

/// Initializes and returns an @c NSXMLDocument object created from data.
///
/// This method is the designated initializer for the @c NSXMLDocument class. If you specify @c NSXMLDocumentTidyXML as one of the options, @c NSXMLDocument performs several clean-up operations on the document XML (such as removing leading tabs). It does respect the @c xml:space="preserve" attribute when it attempts to tidy the XML.
/// @param data A data object with XML content.
/// @param mask A bit mask for input options. You can specify multiple options by bit-OR'ing them.
/// @param error An error object that, on return, identifies any parsing errors and warnings or connection problems.
- (nullable instancetype)initWithData:(NSData *)data options:(NSXMLNodeOptions)mask error:(NSError **)error NS_DESIGNATED_INITIALIZER; //primitive

/// Returns an @c NSXMLDocument object initialized with a single child, the root element.
/// @param element An @c NSXMLElement object representing an XML element.
- (instancetype)initWithRootElement:(nullable NSXMLElement *)element NS_DESIGNATED_INITIALIZER;

#if 0
#pragma mark --- Properties ---
#endif

/// Overridden by subclasses to substitute a custom class for an NSXML class that the parser uses to create node instances.
///
/// This method is invoked before a document is parsed. The substituted class must be a subclass of @c NSXMLNode, @c NSXMLDocument, @c NSXMLElement, @c NSXMLDTD, or @c NSXMLDTDNode.
/// @param cls A @c Class object identifying an NSXML class that is to be replaced by your custom class.
/// @return The substituted class.
+ (Class)replacementClassForClass:(Class)cls;

/// The character encoding of the receiver.
///
/// The encoding must match the name of an IANA character set. Typically the encoding is specified in the XML declaration of a document that is processed, but it can be set at any time. If the specified encoding does not match the actual encoding, parsing of the document might fail.
@property (nullable, copy) NSString *characterEncoding; //primitive

/// The version of the receiver's XML.
///
/// Currently, the version should be either "1.0" or "1.1".
@property (nullable, copy) NSString *version; //primitive

/// A Boolean value that specifies whether the receiver represents a standalone XML document.
///
/// A standalone document does not have an external DTD associated with it. If this option is set the standalone declaration will appear on output.
@property (getter=isStandalone) BOOL standalone; //primitive

/// The kind of output content for the receiver.
///
/// Most of the differences among document-content kind have to do with the handling of content-less tags such as @c \<br\> .
@property NSXMLDocumentContentKind documentContentKind; //primitive

/// The MIME type for the receiver (for example, "text/xml").
@property (nullable, copy) NSString *MIMEType; //primitive

/// The internal DTD associated with the receiver.
///
/// Returns an @c NSXMLDTD object representing the internal DTD associated with the receiver or @c nil if no DTD has been associated. This DTD will be output with the document.
@property (nullable, copy) NSXMLDTD *DTD; //primitive

/// Sets the root element of the receiver.
///
/// As a side effect, this method removes all other children, including @c NSXMLNode objects representing comments and processing-instructions.
/// @param root An @c NSXMLElement object that is to be the root element.
- (void)setRootElement:(NSXMLElement *)root;

/// Returns the root element of the receiver.
- (nullable NSXMLElement *)rootElement; //primitive

#if 0
#pragma mark --- Children ---
#endif

/// Inserts a node object at a specified position in the receiver's array of children.
/// @param child The @c NSXMLNode object to be inserted. The added node must represent a comment, processing instruction, or the root element.
/// @param index An integer specifying the index of the children array to insert @c child. The indexes of children after the new child are incremented. If @c index is out of bounds, an exception is raised.
- (void)insertChild:(NSXMLNode *)child atIndex:(NSUInteger)index; //primitive

/// Inserts an array of children at a specified position in the receiver's array of children.
/// @param children An array of @c NSXMLNode objects representing comments, processing instructions, or the root element.
/// @param index An integer identifying the location in the receiver's children array for insertion. If @c index is out of bounds, an exception is raised.
- (void)insertChildren:(NSArray<NSXMLNode *> *)children atIndex:(NSUInteger)index;

/// Removes the child node of the receiver located at a specified position in its array of children.
///
/// Subsequent children have their indexes decreased by one. The removed @c NSXMLNode object is autoreleased.
/// @param index An integer identifying the position of a child in the receiver's array. If @c index is out of bounds, an exception is raised.
- (void)removeChildAtIndex:(NSUInteger)index; //primitive

/// Sets the child nodes of the receiver.
///
/// Each of these objects must represent comments, processing instructions, or the root element; otherwise, an exception is raised. Pass in @c nil to remove all children.
/// @param children An array of @c NSXMLNode objects.
- (void)setChildren:(nullable NSArray<NSXMLNode *> *)children; //primitive

/// Adds a child node after the last of the receiver's existing children.
/// @param child The @c NSXMLNode object to be added.
- (void)addChild:(NSXMLNode *)child;

/// Replaces the child node of the receiver located at a specified position with another node.
///
/// The removed @c NSXMLNode object is autoreleased.
/// @param index An integer identifying a position in the receiver's array of children. If @c index is out of bounds, an exception is raised.
/// @param node An @c NSXMLNode object to replace the one at @c index; it must represent a comment, a processing instruction, or the root element.
- (void)replaceChildAtIndex:(NSUInteger)index withNode:(NSXMLNode *)node;

#if 0
#pragma mark --- Output ---
#endif

/// The XML string representation of the receiver—that is, the entire document—encapsulated in a data object.
///
/// This property invokes @c XMLDataWithOptions: with an option of @c NSXMLNodeOptionsNone. The encoding used is based on the value returned from @c characterEncoding or UTF-8 if no valid encoding is returned.
@property (readonly, copy) NSData *XMLData;

/// Returns the XML string representation of the receiver—that is, the entire document—encapsulated in a data object.
///
/// The encoding used is based on the value returned from @c characterEncoding.
/// @param options One or more options (bit-OR'd if multiple) to affect the output of the document.
- (NSData *)XMLDataWithOptions:(NSXMLNodeOptions)options;

#if 0
#pragma mark --- XSLT ---
#endif

/// Applies the XSLT pattern rules and templates (specified as a data object) to the receiver and returns a document object containing transformed XML or HTML markup.
///
/// Depending on intended output, the method returns an @c NSXMLDocument object or an @c NSData object containing transformed XML or HTML markup.
/// @param xslt A data object containing the XSLT pattern rules and templates.
/// @param arguments A dictionary containing @c NSString key-value pairs that are passed as runtime parameters to the XSLT processor. Pass in @c nil if you have no parameters to pass.
/// @param error If an error occurs, indirectly returns an @c NSError object encapsulating error or warning messages generated by XSLT processing.
- (nullable id)objectByApplyingXSLT:(NSData *)xslt arguments:(nullable NSDictionary<NSString *, NSString *> *)arguments error:(NSError **)error;

/// Applies the XSLT pattern rules and templates (specified as a string) to the receiver and returns a document object containing transformed XML or HTML markup.
///
/// Depending on intended output, the method returns an @c NSXMLDocument object or an @c NSData object containing transformed XML or HTML markup.
/// @param xslt A string object containing the XSLT pattern rules and templates.
/// @param arguments A dictionary containing @c NSString key-value pairs that are passed as runtime parameters to the XSLT processor. Pass in @c nil if you have no parameters to pass.
/// @param error If an error occurs, indirectly returns an @c NSError object encapsulating error or warning messages generated by XSLT processing.
- (nullable id)objectByApplyingXSLTString:(NSString *)xslt arguments:(nullable NSDictionary<NSString *, NSString *> *)arguments error:(NSError **)error;

/// Applies the XSLT pattern rules and templates located at a specified URL to the receiver and returns a document object containing transformed XML markup.
///
/// Depending on intended output, the method returns an @c NSXMLDocument object or an @c NSData object containing transformed XML or HTML markup.
/// @param xsltURL An @c NSURL object specifying a valid URL.
/// @param argument A dictionary containing @c NSString key-value pairs that are passed as runtime parameters to the XSLT processor. Pass in @c nil if you have no parameters to pass.
/// @param error If an error occurs, indirectly returns an @c NSError object encapsulating error or warning messages generated by XSLT processing or from an attempt to connect to a website identified by the URL.
- (nullable id)objectByApplyingXSLTAtURL:(NSURL *)xsltURL arguments:(nullable NSDictionary<NSString *, NSString *> *)argument error:(NSError **)error;

#if 0
#pragma mark --- Validation ---
#endif

/// Validates the document against the governing schema and returns whether the document conforms to the schema.
///
/// If the schema is defined with a DTD, this method uses the @c NSXMLDTD object set for the receiver for validation. If the schema is based on XML Schema, the method uses the URL specified as the value of the @c xsi:schemaLocation attribute of the root element. You can validate an XML document when it is first processed by specifying the @c NSXMLDocumentValidate option in the initializer methods.
/// @param error If validation fails, on return contains an @c NSError object describing the reason or reasons for failure.
- (BOOL)validateAndReturnError:(NSError **)error;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
