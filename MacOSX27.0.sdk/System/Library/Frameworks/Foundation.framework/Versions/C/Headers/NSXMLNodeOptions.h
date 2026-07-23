/*	NSXMLNodeOptions.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>

/*!
    @enum Init, input, and output options
    @constant NSXMLNodeIsCDATA This text node is CDATA
    @constant NSXMLNodeExpandEmptyElement This element should be expanded when empty, ie &lt;a>&lt;/a>. This is the default.
    @constant NSXMLNodeCompactEmptyElement This element should contract when empty, ie &lt;a/>
    @constant NSXMLNodeUseSingleQuotes Use single quotes on this attribute or namespace
    @constant NSXMLNodeUseDoubleQuotes Use double quotes on this attribute or namespace. This is the default.
    @constant NSXMLNodeNeverEscapeContents When generating a string representation of an XML document, don't escape the reserved characters '<' and '&' in Text nodes

    @constant NSXMLNodeOptionsNone Use the default options
    @constant NSXMLNodePreserveAll Turn all preservation options on
    @constant NSXMLNodePreserveNamespaceOrder Preserve the order of namespaces
    @constant NSXMLNodePreserveAttributeOrder Preserve the order of attributes
    @constant NSXMLNodePreserveEntities Entities should not be resolved on output
    @constant NSXMLNodePreservePrefixes Prefixes should not be chosen based on closest URI definition
    @constant NSXMLNodePreserveCDATA CDATA should be preserved
    @constant NSXMLNodePreserveEmptyElements Remember whether an empty element was in expanded or contracted form
    @constant NSXMLNodePreserveQuotes Remember whether an attribute used single or double quotes
    @constant NSXMLNodePreserveWhitespace Preserve non-content whitespace
    @constant NSXMLNodePromoteSignificantWhitespace When significant whitespace is encountered in the document, create Text nodes representing it rather than removing it. Has no effect if NSXMLNodePreserveWhitespace is also specified
    @constant NSXMLNodePreserveDTD Preserve the DTD until it is modified
    
    @constant NSXMLDocumentTidyHTML Try to change HTML into valid XHTML
    @constant NSXMLDocumentTidyXML Try to change malformed XML into valid XML
    
    @constant NSXMLDocumentValidate Valid this document against its DTD
 
    @constant NSXMLNodeLoadExternalEntitiesAlways Load all external entities instead of just non-network ones
    @constant NSXMLNodeLoadExternalEntitiesSameOriginOnly Load non-network external entities and external entities from urls with the same domain, host, and port as the document
    @constant NSXMLNodeLoadExternalEntitiesNever Load no external entities, even those that don't require network access

    @constant NSXMLNodePrettyPrint Output this node with extra space for readability
    @constant NSXMLDocumentIncludeContentTypeDeclaration Include a content type declaration for HTML or XHTML
*/

/// These constants are input and output options for all `NSXMLNode` objects (unless otherwise indicated), including ``XMLDocument`` objects.
///
/// You can specify these options in the `NSXMLNode` methods ``XMLNode/init(kind:options:)`` and ``XMLNode/xmlString(options:)``.
///
/// The options with "Preserve" in their names are applicable only when external sources of XML are parsed; they have no effect on node objects that are programmatically created. Other options are used in initialization and output methods of `NSXMLDocument`; see the ``XMLDocument`` reference documentation for details.
typedef NS_OPTIONS(NSUInteger, NSXMLNodeOptions) {
    /// No options are requested for this input or output action.
    NSXMLNodeOptionsNone = 0,

    // Init
    /// Specifies that a text node contains and is written out as a CDATA section.
    NSXMLNodeIsCDATA = 1UL << 0,
    /// This element should be expanded when empty, ie @c \<a\>\</a\> . This is the default.
    NSXMLNodeExpandEmptyElement = 1UL << 1, // <a></a>
    /// This element should contract when empty, ie @c \<a/\> .
    NSXMLNodeCompactEmptyElement =  1UL << 2, // <a/>
    /// Use single quotes on this attribute or namespace.
    NSXMLNodeUseSingleQuotes = 1UL << 3,
    /// Use double quotes on this attribute or namespace. This is the default.
    NSXMLNodeUseDoubleQuotes = 1UL << 4,
    /// When generating a string representation of an XML document, don't escape the reserved characters '<' and '&' in Text nodes.
    NSXMLNodeNeverEscapeContents = 1UL << 5,

    // Tidy
    /// Try to change HTML into valid XHTML.
    NSXMLDocumentTidyHTML = 1UL << 9,
    /// Try to change malformed XML into valid XML.
    NSXMLDocumentTidyXML = 1UL << 10,

    // Validate
    /// Validate this document against its DTD.
    NSXMLDocumentValidate = 1UL << 13,

    // External Entity Loading
    // Choose only zero or one option. Choosing none results in system-default behavior.
    /// Load all external entities instead of just non-network ones.
    NSXMLNodeLoadExternalEntitiesAlways = 1UL << 14,
    /// Load non-network external entities and external entities from URLs with the same domain, host, and port as the document.
    NSXMLNodeLoadExternalEntitiesSameOriginOnly = 1UL << 15,
    /// Load no external entities, even those that don't require network access.
    NSXMLNodeLoadExternalEntitiesNever = 1UL << 19,

    // Parse
    NSXMLDocumentXInclude = 1UL << 16,

    // Output
    /// Output this node with extra space for readability.
    NSXMLNodePrettyPrint = 1UL << 17,
    /// Include a content type declaration for HTML or XHTML.
    NSXMLDocumentIncludeContentTypeDeclaration = 1UL << 18,

    // Fidelity
    /// Preserve the order of namespaces.
    NSXMLNodePreserveNamespaceOrder = 1UL << 20,
    /// Preserve the order of attributes.
    NSXMLNodePreserveAttributeOrder = 1UL << 21,
    /// Entities should not be resolved on output.
    NSXMLNodePreserveEntities = 1UL << 22,
    /// Prefixes should not be chosen based on closest URI definition.
    NSXMLNodePreservePrefixes = 1UL << 23,
    /// CDATA should be preserved.
    NSXMLNodePreserveCDATA = 1UL << 24,
    /// Preserve non-content whitespace.
    NSXMLNodePreserveWhitespace = 1UL << 25,
    /// Preserve the DTD until it is modified.
    NSXMLNodePreserveDTD = 1UL << 26,
    /// Preserve character references.
    NSXMLNodePreserveCharacterReferences = 1UL << 27,
    /// When significant whitespace is encountered in the document, create Text nodes representing it rather than removing it. Has no effect if @c NSXMLNodePreserveWhitespace is also specified.
    NSXMLNodePromoteSignificantWhitespace = 1UL << 28,
    /// Remember whether an empty element was in expanded or contracted form.
    NSXMLNodePreserveEmptyElements =
            (NSXMLNodeExpandEmptyElement | NSXMLNodeCompactEmptyElement),
    /// Remember whether an attribute used single or double quotes.
    NSXMLNodePreserveQuotes =
            (NSXMLNodeUseSingleQuotes | NSXMLNodeUseDoubleQuotes),
    /// Turn all preservation options on.
    NSXMLNodePreserveAll = (
            NSXMLNodePreserveNamespaceOrder |
            NSXMLNodePreserveAttributeOrder |
            NSXMLNodePreserveEntities |
            NSXMLNodePreservePrefixes |
            NSXMLNodePreserveCDATA |
            NSXMLNodePreserveEmptyElements |
            NSXMLNodePreserveQuotes |
            NSXMLNodePreserveWhitespace |
            NSXMLNodePreserveDTD |
            NSXMLNodePreserveCharacterReferences |
            0xFFF00000) // high 12 bits
};
