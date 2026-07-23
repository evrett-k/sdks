/*
	File:  AVInterfaceControllable.h
	
	Framework:  AVKit
	
	Copyright © 2025 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */

#import <CoreGraphics/CoreGraphics.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <Foundation/Foundation.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

#if TARGET_OS_MACCATALYST
#import <AVKitCore/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_MACCATALYST


// MARK: - Typedefs

/*!
 Describes possible playback states of the interface source.
 */
typedef NS_ENUM(NSInteger, AVInterfacePlaybackState) {
	/// Indicates the source is in a normal state.
	AVInterfacePlaybackStateNormal = 0,
	/// Indicates the source is scanning forward or backward at an accelerated rate.
	AVInterfacePlaybackStateScanning,
	/// Indicates the source is being scrubbed by user interaction with the timeline.
	AVInterfacePlaybackStateScrubbing,
} API_DEPRECATED("Use AVPlaybackUserInterfacePlaybackState instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);

/*!
 Describes navigation capabilities of the media source.
 
 This option set defines timeline navigation operations. Different content types and sources may have varying
 levels of navigation support based on technical limitations, licensing restrictions, or content type.
 */
typedef NS_OPTIONS(NSUInteger, AVInterfaceSeekCapabilities) {
	/// The source does not support any scanning or seeking operations.
	AVInterfaceSeekCapabilitiesNone			= 0,
	/// The source supports forward scanning at accelerated rates for fast-forward operations. Enables rapid progression through content at speeds greater than normal playback.
	AVInterfaceSeekCapabilitiesScanForward	= 1 << 0,
	/// The source supports backward scanning at accelerated rates for rewind operations. Enables rapid reverse progression through content at speeds greater than normal playback.
	AVInterfaceSeekCapabilitiesScanBackward	= 1 << 1,
	/// The source supports seeking to specific time positions for precise navigation. Enables jumping directly to any arbitrary point within the seekable time ranges.
	AVInterfaceSeekCapabilitiesSeek			= 1 << 2,
} API_DEPRECATED("Use AVPlaybackUserInterfaceSeekCapabilities instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos);


// MARK: -

NS_ASSUME_NONNULL_BEGIN

/*!
 Represents a contiguous segment of timeline content with specific playback characteristics.
 
 Timeline segments divide media content into distinct regions, each with its own classification
 and behavior rules. Segments are typically used to distinguish between primary content and
 auxiliary content such as advertisements or bonus material, and to control whether users can
 seek or skip through specific portions of the timeline.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceTimelineSegment instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVInterfaceTimelineSegment : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// The time range defining the segment's position and duration within the overall timeline.
@property (nonatomic, readonly) CMTimeRange timeRange;

/// Indicates whether this segment consists of auxiliary or main content. Returns YES for auxiliary content, such as advertisements, interludes, or bonus material, and NO for main content, such as the main program material.
@property (nonatomic, readonly, getter = isAuxiliaryContent) BOOL auxiliaryContent;

/// Indicates whether this segment should be visually highlighted or marked in the timeline UI.
@property (nonatomic, readonly, getter = isMarked) BOOL marked;

/// Indicates whether this segment must be played sequentially without seeking or skipping. Typically used for advertisements or important announcements.
@property (nonatomic, readonly) BOOL requiresLinearPlayback;

/// Optional external identifier for tracking or analytics purposes. May correspond to advertisement IDs, chapter markers, or other external systems.
@property (nonatomic, readonly, copy, nullable) NSString *identifier;

/*!
 Initializes a new timeline segment with the specified characteristics.
 
 @param timeRange The time range defining the segment's position and duration within the timeline.
 @param auxiliaryContent Whether the segment contains main or auxiliary content.
 @param marked Whether the segment should be visually highlighted in the timeline UI.
 @param requiresLinearPlayback Whether the segment must be played sequentially without seeking or skipping.
 @param identifier External identifier for tracking or analytics purposes.
 */
- (instancetype)initWithTimeRange:(CMTimeRange)timeRange
				 auxiliaryContent:(BOOL)auxiliaryContent
						   marked:(BOOL)marked
		   requiresLinearPlayback:(BOOL)requiresLinearPlayback
					   identifier:(nullable NSString *)identifier NS_DESIGNATED_INITIALIZER;

@end

/*!
 Represents a media selection option for audio tracks or subtitle tracks.
 
 This class represents individual media options (such as audio tracks or subtitle tracks)
 that can be selected by the user in media playback interfaces. Each option provides
 display information and metadata for user selection.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceMediaSelectionOption instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVInterfaceMediaSelectionOptionSource : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// Human-readable name for this media option displayed in user interfaces (e.g., "English", "Spanish (Latin America)", "Director's Commentary").
@property (nonatomic, readonly, copy) NSString *displayName;

/// Unique system identifier for this media option, used for programmatic selection and persistence across sessions.
@property (nonatomic, readonly, copy) NSString *identifier;

/// IETF BCP 47 language identifier (e.g., "en-US", "es-419", "zh-Hans-CN") indicating the primary language and locale of this option.
/// This standardized tag provides detailed language information including region, script, and variants. May be empty for language-neutral content such as music-only audio tracks, sound effects, or visual-only subtitles without spoken content.
@property (nonatomic, readonly, copy, nullable) NSString *extendedLanguageTag NS_REFINED_FOR_SWIFT;

/*!
 Initializes a new media selection option with the specified attributes.
 
 @param displayName Human-readable name displayed in user interfaces.
 @param identifier Unique system identifier for programmatic selection.
 @param extendedLanguageTag IETF BCP 47 language identifier, or nil for language-neutral content.
 */
- (instancetype)initWithDisplayName:(NSString *)displayName
						 identifier:(NSString *)identifier
				extendedLanguageTag:(nullable NSString *)extendedLanguageTag NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@end

@class AVInterfaceURLAlbumArtwork;

/*!
 Base class representing album artwork or cover art for media content.

 Use a concrete subclass such as @c AVInterfaceURLAlbumArtwork to create artwork instances.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceContentArtwork instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVInterfaceAlbumArtwork : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// URL pointing to the album artwork image resource.
@property (nonatomic, readonly, copy, nullable) NSURL *url API_DEPRECATED("url is deprecated", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos);

/// The uniform type identifier for the artwork image data.
@property (nonatomic, readonly, copy, nullable) UTType *contentType API_DEPRECATED("contentType is deprecated", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos);

/// The pixel dimensions of the artwork image.
@property (nonatomic, readonly) CGSize size;

/*!
 Initializes a new album artwork object with the specified image resource information.
 
 @param url URL pointing to the album artwork image resource.
 @param contentType The uniform type identifier for the artwork image data.
 @param size The pixel dimensions of the artwork image.
 */
- (instancetype)initWithURL:(NSURL *)url
				contentType:(UTType *)contentType
					   size:(CGSize)size API_DEPRECATED("Use artworkWithURL:contentType:size: instead", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos);

/*!
 Creates an artwork instance that references an image at the given URL.
 
 @param url URL pointing to the artwork image resource.
 @param type The uniform type identifier for the image data.
 @param size The pixel dimensions of the artwork image.
 */
+(AVInterfaceURLAlbumArtwork *)artworkWithURL:(NSURL *)url
								  contentType:(UTType *)type
										 size:(CGSize)size NS_SWIFT_NAME(artwork(url:contentType:size:));

@end

/*!
 An album artwork subclass that references artwork via a URL and content type.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceContentURLArtwork instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
@interface AVInterfaceURLAlbumArtwork : AVInterfaceAlbumArtwork

/// URL pointing to the album artwork image resource.
@property (nonatomic, readonly, copy) NSURL *url;

/// The uniform type identifier for the artwork image data.
@property (nonatomic, readonly, copy) UTType *contentType;

AVKIT_INIT_UNAVAILABLE

@end

/*!
 A mutable template for configuring media metadata before creating immutable metadata objects.
 
 Use this class to build and configure metadata for media content with full control over all properties.
 Once configured, create an immutable `AVInterfaceMetadata` object using `initWithTemplate:` to provide
 stable metadata for playback interfaces.
 
 This template provides a convenient way to incrementally build metadata information, allowing you to
 set properties individually before finalizing the metadata. All properties are mutable (readwrite),
 making it ideal for scenarios where metadata is constructed from multiple sources or updated over time.
 
 Example usage:
 
 AVInterfaceMetadataTemplate *template = [[AVInterfaceMetadataTemplate alloc] init];
 template.audioOnly = NO;
 template.title = @"Episode 5: The Journey Continues";
 template.subtitle = @"Season 2";
 template.albumArtworkRepresentations = @[artwork1, artwork2];
 
 AVInterfaceMetadata *metadata = [[AVInterfaceMetadata alloc] initWithTemplate:template];
 
 @see AVInterfaceMetadata
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceContentMetadataTemplate instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_REFINED_FOR_SWIFT
@interface AVInterfaceMetadataTemplate : NSObject <NSCopying, NSSecureCoding>

/// Indicates whether the content is audio-only (no video component). Used to optimize UI layout and player controls for audio-focused presentations.
/// When YES, video-related controls and layouts should be hidden or adapted for audio-only playback experiences.
@property (nonatomic, readwrite, getter = isAudioOnly) BOOL audioOnly;

/// The natural pixel dimensions of the video content for display purposes.
/// This represents the encoded size of the video stream and can be used to determine aspect ratio and optimal presentation layout. For audio-only content, this value is CGSizeZero.
@property (nonatomic, readwrite) CGSize presentationSize;

/// Primary title or name of the media content for display in player UI and system interfaces.
/// This should be the main identifying text for the content, such as a song title, episode name, or movie title.
@property (nonatomic, readwrite, copy, nullable) NSString *title;

/// Secondary descriptive text such as artist name, episode description, or additional context for the content.
/// This provides supplementary information to help users identify and understand the content being played.
@property (nonatomic, readwrite, copy, nullable) NSString *subtitle;

/// Array of available album artwork representations in various formats and sizes for this media content.
/// Multiple representations allow the system to choose the most appropriate artwork for different display contexts (thumbnails, full-screen, high-DPI displays).
/// Each representation specifies its dimensions, format, and URL for optimal loading and display performance.
@property (nonatomic, readwrite, copy) NSArray<AVInterfaceAlbumArtwork *> *albumArtworkRepresentations;

@end

/*!
 Provides metadata information about media content including title, artwork, and content type.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceContentMetadata instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_SENDABLE
NS_REFINED_FOR_SWIFT
@interface AVInterfaceMetadata : NSObject <NSCopying, NSSecureCoding>

AVKIT_INIT_UNAVAILABLE

/// Indicates whether the content is audio-only (no video component). Used to optimize UI layout and player controls for audio-focused presentations.
/// When YES, video-related controls and layouts should be hidden or adapted for audio-only playback experiences.
@property (nonatomic, readonly, getter = isAudioOnly) BOOL audioOnly;

/// The natural pixel dimensions of the video content for display purposes.
/// This represents the encoded size of the video stream and can be used to determine aspect ratio and optimal presentation layout. For audio-only content, this value is CGSizeZero.
@property (nonatomic, readonly) CGSize presentationSize;

/// Primary title or name of the media content for display in player UI and system interfaces.
/// This should be the main identifying text for the content, such as a song title, episode name, or movie title.
@property (nonatomic, readonly, copy, nullable) NSString *title;

/// Secondary descriptive text such as artist name, episode description, or additional context for the content.
/// This provides supplementary information to help users identify and understand the content being played.
@property (nonatomic, readonly, copy, nullable) NSString *subtitle;

/// Array of available album artwork representations in various formats and sizes for this media content.
/// Multiple representations allow the system to choose the most appropriate artwork for different display contexts (thumbnails, full-screen, high-DPI displays).
/// Each representation specifies its dimensions, format, and URL for optimal loading and display performance.
@property (nonatomic, readonly, copy) NSArray<AVInterfaceAlbumArtwork *> *albumArtworkRepresentations;

/*!
 Initializes a new metadata object with the specified properties.
 
 @param audioOnly Whether the content is audio-only (no video component).
 @param presentationSize The pixel dimensions for video presentation.
 @param title Primary title or name of the media content.
 @param subtitle Secondary descriptive text such as artist name or episode description.
 @param albumArtworkRepresentations Array of available album artwork representations in various formats and sizes.
 */
- (instancetype)initWithAudioOnly:(BOOL)audioOnly
				 presentationSize:(CGSize)presentationSize
							title:(nullable NSString *)title
						 subtitle:(nullable NSString *)subtitle
	  albumArtworkRepresentations:(NSArray<AVInterfaceAlbumArtwork *> *)albumArtworkRepresentations NS_DESIGNATED_INITIALIZER;

/*!
 Initializes a new metadata object by copying values from a metadata template.
 
 This initializer creates an immutable `AVInterfaceMetadata` instance from a mutable
 `AVInterfaceMetadataTemplate`, providing a convenient way to convert configured template
 data into stable metadata for playback interfaces.
 
 All properties from the template are copied into the new metadata object, creating an
 independent immutable snapshot of the template's current state. Subsequent changes to
 the template will not affect the created metadata object.
 
 @param metadataTemplate The metadata template to copy values from. If nil, returns a metadata object with default values.
 
 @see AVInterfaceMetadataTemplate
 */
- (instancetype)initWithTemplate:(nullable AVInterfaceMetadataTemplate *)metadataTemplate;

@end


// MARK: - Protocols

/*!
 Provides playback control and state management for media content.
 */
API_DEPRECATED("Use AVPlaybackUserInterfacePlaybackControllable instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVInterfacePlaybackControllable <NSObject>

/// Indicates whether the media source is ready for playback operations. Returns YES when the source has sufficient data and is prepared to begin playback.
/// Use this property to determine when playback controls should be enabled and when the media can respond to play requests. Must be key-value observable.
@property (nonatomic, readonly, getter = isReady) BOOL ready;

/// Indicates whether the media is currently playing. Setting this property starts or pauses playback. Must be key-value observable.
@property (nonatomic, readwrite, getter = isPlaying) BOOL playing;

/// Indicates whether the media source is currently buffering content. Returns YES when the source is loading data and cannot immediately continue playback. Must be key-value observable.
@property (nonatomic, readonly, getter = isBuffering) BOOL buffering;

/// The current playback speed multiplier. A value of 1.0 represents normal speed, values greater than 1.0 represent faster playback, and values between 0.0 and 1.0 represent slower playback. Must be key-value observable.
@property (nonatomic, readwrite) float playbackSpeed;

/// The scanning speed multiplier used during fast-forward or rewind operations. A positive value indicates forward scanning, negative indicates backward scanning. Must be key-value observable.
@property (nonatomic, readwrite) float scanSpeed;

/// The current operational state of the interface source. Must be key-value observable.
@property (nonatomic, readwrite) AVInterfacePlaybackState state;

/// An option set indicating which timeline navigation operations are supported by this media source.
/// This property defines the available navigation capabilities, including precise seeking to specific time positions and accelerated scanning for fast-forward/rewind operations.
/// The supported modes may vary based on content type, licensing restrictions, or technical limitations of the underlying media format. Must be key-value observable.
@property (nonatomic, readonly) AVInterfaceSeekCapabilities supportedSeekCapabilities;

/// Indicates whether the content contains live streaming content. Returns YES for live streams and NO for on-demand content. Must be key-value observable.
@property (nonatomic, readonly) BOOL containsLiveStreamingContent;

/// Error information when the source encounters a playback failure. Nil when playback is functioning normally. Must be key-value observable.
@property (nonatomic, readonly, nullable) NSError *playbackError;


#if TARGET_OS_TV
/// The default playback speed to use when playback begins.
/// This value is used to set the initial playback rate when starting playback.
/// A value of 1.0 represents normal speed. Must be key-value observable.
@property (nonatomic, readwrite) float defaultPlaybackSpeed API_UNAVAILABLE(tvos) API_UNAVAILABLE(ios, macCatalyst, macos, visionos, watchos);
#endif // TARGET_OS_TV

@end

/*!
 Provides time control and navigation capabilities for media content.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceTimeControllable instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVInterfaceTimeControllable <NSObject>

/// The time range representing the total duration and bounds of the media content.
/// This defines the overall playable timeline, with all segments and seekable ranges falling within this range. Must be key-value observable.
@property (nonatomic, readonly) CMTimeRange timeRange;

/// The current playback position within the media time, expressed in seconds from the start of the content.
/// This value should be within the bounds defined by the start and duration properties and represents the exact temporal position of playback. Must be key-value observable.
@property (nonatomic, readwrite) CMTime currentPlaybackPosition;

/// Segments representing different content types within the timeline. All segments should be contiguous and collectively cover the entire timeline duration without gaps or overlaps.
/// Each segment defines a specific portion of content (such as main program, advertisements, or bonus material) with its own playback characteristics. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVInterfaceTimelineSegment *> *segments;

/// The segment containing the current playback position. This property automatically updates as playback progresses through different timeline segments.
/// Use this to determine the current content type (primary vs. secondary) and any special playback characteristics that apply to the current position. Must be key-value observable.
@property (nonatomic, readonly, strong) AVInterfaceTimelineSegment *currentSegment;

/// An array of time ranges within the timeline where seeking operations are permitted.
/// Each range is represented as an NSValue wrapping a CMTimeRange structure, defining portions of the timeline where users can jump to specific time positions during playback.
/// If nil, the entire content defined by timeRange is considered seekable. When provided, each range must be a subset of the overall timeRange and should not overlap with other seekable ranges.
/// An empty array means the entire content defined by timeRange is not seekable.
/// Seekable ranges typically exclude segments where requiresLinearPlayback is YES, such as advertisements, mandatory content, or licensing-restricted portions.
/// The array should contain ranges in chronological order for optimal performance. Must be key-value observable.
@property (nonatomic, readonly, copy, nullable) NSArray<NSValue *> *seekableTimeRanges;

@end

/*!
 Provides audio and subtitle selection capabilities for media content.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceMediaSelectionControllable instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVInterfaceMediaSelectionControllable <NSObject>

/// Currently selected audio track for playback. Setting this property changes the active audio stream.
/// This includes language variants, audio descriptions, director's commentary, and other audio content. Must be key-value observable.
@property (nonatomic, readwrite, strong, nullable) AVInterfaceMediaSelectionOptionSource *currentAudioOption;

/// Currently selected subtitle or caption track. Setting this property controls text overlay presentation.
/// This includes subtitles in different languages, closed captions, and forced narrative text. Set to nil to disable text display. Must be key-value observable.
@property (nonatomic, readwrite, strong, nullable) AVInterfaceMediaSelectionOptionSource *currentLegibleOption;

/// Array of available audio track options for selection. This includes all audio streams provided by the media source such as different languages, audio descriptions, director's commentary, and alternative audio mixes.
/// Options are ordered by preference with the primary language or default audio track typically appearing first. May be empty for content without selectable audio options. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVInterfaceMediaSelectionOptionSource *> *audioOptions;

/// Array of available subtitle and caption track options for selection. This includes text overlays in different languages, closed captions for accessibility, forced narrative subtitles, and sign language interpretation tracks.
/// May be empty for content without text tracks. Must be key-value observable.
@property (nonatomic, readonly, copy) NSArray<AVInterfaceMediaSelectionOptionSource *> *legibleOptions;

@end

/*!
 Provides volume and audio muting control for media content.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceVolumeControllable instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVInterfaceVolumeControllable <NSObject>

/// Indicates whether the media contains audio tracks and can produce sound output. Returns NO for video-only content, silent content, or when audio tracks are unavailable. Must be key-value observable.
@property (nonatomic, readonly) BOOL hasAudio;

/// Controls whether audio output is temporarily silenced. When YES, audio is muted regardless of the volume level setting. Must be key-value observable.
@property (nonatomic, readwrite, getter = isMuted) BOOL muted;

/// The audio output level as a normalized value between 0.0 (completely silent) and 1.0 (maximum system volume).
/// This value is independent of the muted state and represents the user's volume preference. Must be key-value observable.
@property (nonatomic, readwrite) float volume;

@end

/*!
 Provides metadata information about media content including title, artwork, and content type.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceMetadataProviding instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVInterfaceMetadataProviding <NSObject>

/// The metadata object containing information about the media content. Must be key-value observable.
@property (nonatomic, readonly, strong) AVInterfaceMetadata *metadata;

@end

/*!
 A comprehensive protocol that provides complete media control and information for playback, timeline navigation, audio/subtitle selection, volume control, and metadata access.
 
 This protocol consolidates all media source capabilities into a single interface, enabling rich media experiences with full control over playback state, timeline interactions, and content metadata. Implementations should provide key-value observable properties where specified to ensure proper integration with media player controls and UI frameworks.
 */
API_DEPRECATED("Use AVPlaybackUserInterfaceControllable instead.", ios(27.0, 27.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_MAIN_ACTOR
NS_REFINED_FOR_SWIFT
@protocol AVInterfaceControllable <	AVInterfaceTimeControllable,
									AVInterfacePlaybackControllable,
									AVInterfaceMediaSelectionControllable,
									AVInterfaceVolumeControllable,
									AVInterfaceMetadataProviding	>

@end

NS_ASSUME_NONNULL_END
