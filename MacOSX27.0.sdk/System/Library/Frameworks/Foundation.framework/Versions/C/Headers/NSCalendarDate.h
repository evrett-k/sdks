/*	NSCalendarDate.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSDate.h>

@class NSString, NSArray, NSTimeZone;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#if 1 || NS_ENABLE_CALENDAR_DEPRECATIONS
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#else
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_AVAILABLE_MAC(A)
#endif
#endif

/// A specialized date object with embedded calendar information.
///
/// @DeprecationSummary {
/// Use ``NSDate`` and ``NSCalendar`` instead.
/// }
API_DEPRECATED("Use NSCalendar and NSDateComponents and NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0))
NS_SWIFT_UNAVAILABLE("Use NSCalendar and NSDateComponents and NSDateFormatter instead")
@interface NSCalendarDate : NSDate {
@private
    NSUInteger		refCount;
    NSTimeInterval 	_timeIntervalSinceReferenceDate;
    NSTimeZone		*_timeZone;
    NSString 		*_formatString;
    void		*_reserved;
}

/*    DEPRECATED DEPRECATED DEPRECATED
 *    These methods are deprecated.
 *    Use NSCalendar for calendrical calculations.
 *    Use NSDateFormatter for date<->string conversions.
 */
+ (id)calendarDate API_DEPRECATED("Use NSCalendar instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
+ (nullable id)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(nullable id)locale API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
+ (nullable id)dateWithString:(NSString *)description calendarFormat:(NSString *)format API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
+ (id)dateWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(nullable NSTimeZone *)aTimeZone API_DEPRECATED("Use NSCalendar and NSDateComponents instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSCalendarDate *)dateByAddingYears:(NSInteger)year months:(NSInteger)month days:(NSInteger)day hours:(NSInteger)hour minutes:(NSInteger)minute seconds:(NSInteger)second API_DEPRECATED("Use NSCalendar instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)dayOfCommonEra API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)dayOfMonth API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)dayOfWeek API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)dayOfYear API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)hourOfDay API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)minuteOfHour API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)monthOfYear API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)secondOfMinute API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSInteger)yearOfCommonEra API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar component:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSString *)calendarFormat API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(nullable id)locale API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSString *)descriptionWithCalendarFormat:(NSString *)format API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSString *)descriptionWithLocale:(nullable id)locale API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (NSTimeZone *)timeZone API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (nullable id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(nullable id)locale API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (nullable id)initWithString:(NSString *)description calendarFormat:(NSString *)format API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (nullable id)initWithString:(NSString *)description API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (id)initWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(nullable NSTimeZone *)aTimeZone API_DEPRECATED("Use NSCalendar and NSDateComponents instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (void)setCalendarFormat:(nullable NSString *)format API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (void)setTimeZone:(nullable NSTimeZone *)aTimeZone API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (void)years:(nullable NSInteger *)yp months:(nullable NSInteger *)mop days:(nullable NSInteger *)dp hours:(nullable NSInteger *)hp minutes:(nullable NSInteger *)mip seconds:(nullable NSInteger *)sp sinceDate:(NSCalendarDate *)date API_DEPRECATED_WITH_REPLACEMENT("-[NSCalendar components:fromDate:]", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
+ (instancetype)distantFuture API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
+ (instancetype)distantPast API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
@end

@interface NSDate (NSCalendarDateExtras)
/*    DEPRECATED DEPRECATED DEPRECATED
 *    These methods are deprecated.
 *    Use NSCalendar for calendrical calculations.
 *    Use NSDateFormatter for date<->string conversions.
 */
/// Creates and returns a date object set to the date and time specified by a given string.
///
/// This method supports only a limited set of colloquial phrases, primarily in English. It may give unexpected results, and its use is strongly discouraged. To create a date object from a string, you should use a date formatter object instead (see ``DateFormatter`` and [Data Formatting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DataFormatting/DataFormatting.html#//apple_ref/doc/uid/10000029i)).
///
/// The keys and values that represent the locale data from `locale` are used when parsing the string. In addition to the locale keys listed in the class description, these keys are used when parsing natural language strings:
///
/// - NSDateTimeOrdering
/// - NSEarlierTimeDesignations
/// - NSHourNameDesignations
/// - NSLaterTimeDesignations
/// - NSNextDayDesignations
/// - NSNextNextDayDesignations
/// - NSPriorDayDesignations
/// - NSThisDayDesignations
/// - NSYearMonthWeekDesignations
///
/// - Parameters:
///   - string: A string that contains a colloquial specification of a date, such as "last Tuesday at dinner," "3pm December 31, 2001," "12/31/01," or "31/12/01."
///   - locale: An `NSDictionary` object containing locale data. To use the user's preferences, you can use `[[NSUserDefaults standardUserDefaults] dictionaryRepresentation]`. If you pass `nil` or an instance of `NSLocale`, `NSDate` uses the system default locale---this is not the same as the current user's locale.
/// - Returns: A new `NSDate` object set to the date and time specified by `string` as interpreted according to `locale`.
+ (nullable id)dateWithNaturalLanguageString:(NSString *)string locale:(nullable id)locale API_DEPRECATED("Create an NSDateFormatter with `init` and set the dateFormat property instead.", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Creates and returns a date object set to the date and time specified by a given string.
///
/// This method supports only a limited set of colloquial phrases, primarily in English. It may give unexpected results, and its use is strongly discouraged. To create a date object from a string, you should use a date formatter object instead (see ``DateFormatter`` and [Data Formatting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DataFormatting/DataFormatting.html#//apple_ref/doc/uid/10000029i)).
///
/// In parsing the string, this method uses the date and time preferences stored in the user's defaults database. (See ``NSDate/date(withNaturalLanguageString:locale:)`` for a list of the specific items used.)
///
/// - Parameter string: A string that contains a colloquial specification of a date, such as "last Tuesday at dinner," "3pm December 31, 2001," "12/31/01," or "31/12/01."
/// - Returns: A new `NSDate` object set to the current date and time specified by `string`.
+ (nullable id)dateWithNaturalLanguageString:(NSString *)string API_DEPRECATED("Create an NSDateFormatter with `init` and set the dateFormat property instead.", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Creates and returns a date object with a date and time value specified by a given string in the international string representation format (`YYYY-MM-DD HH:MM:SS ±HHMM`).
///
/// To create a date object from a string, you should typically use a date formatter object instead (see ``DateFormatter`` and [Data Formatting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DataFormatting/DataFormatting.html#//apple_ref/doc/uid/10000029i)).
///
/// - Parameter aString: A string that specifies a date and time value in the international string representation format---`YYYY-MM-DD HH:MM:SS ±HHMM`, where `±HHMM` is a time zone offset in hours and minutes from UTC (for example, "`2001-03-24 10:45:32 +0600`"). You must specify all fields of the format string, including the time zone offset, which must have a plus or minus sign prefix.
/// - Returns: An `NSDate` object with a date and time value specified by `aString`.
+ (id)dateWithString:(NSString *)aString API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Converts the receiver to a calendar date with a given format string and time zone.
///
/// @DeprecationSummary {
///     Use `NSDate` methods to set the individual date values.
/// }
///
/// - Parameters:
///   - format: The format for the returned string. Pass `nil` to use the default format string, `"%Y-%m-%d %H:%M:%S %z"`.
///   - aTimeZone: The time zone for the new calendar date. Pass `nil` to use the default time zone.
/// - Returns: A new `NSCalendarDate` object bound to `format` and the time zone `aTimeZone`.
- (NSCalendarDate *)dateWithCalendarFormat:(nullable NSString *)format timeZone:(nullable NSTimeZone *)aTimeZone API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Returns a string representation of the date formatted as specified by given conversion specifiers.
- (nullable NSString *)descriptionWithCalendarFormat:(nullable NSString *)format timeZone:(nullable NSTimeZone *)aTimeZone locale:(nullable id)locale API_DEPRECATED("", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Returns a date object initialized with a date and time value specified by a given string in the international string representation format.
///
/// - Parameters:
///   - description: A string that specifies a date and time value in the international string representation format---`YYYY-MM-DD HH:MM:SS ±HHMM`,
///     where `±HHMM` is a time zone offset in hours and minutes from UTC (for example, "`2001-03-24 10:45:32 +0600`").
///     You must specify all fields of the format string, including the time zone offset, which must have a plus or minus sign prefix.
/// - Returns: An `NSDate` object initialized with a date and time value specified by `description`.
- (nullable id)initWithString:(NSString *)description API_DEPRECATED("Use NSDateFormatter instead", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
