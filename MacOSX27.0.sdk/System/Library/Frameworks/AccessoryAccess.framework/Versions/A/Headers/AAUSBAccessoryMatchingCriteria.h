//
//  AAUSBAccessoryMatchingCriteria.h
//  AccessoryAccess
//
//  Copyright © 2023-2026 Apple Inc. All rights reserved.
//

#import <AccessoryAccess/AADefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Options for performing interface matching using interface matching criteria/dictionaries.
*/
typedef NS_ENUM(NSInteger, AAUSBAccessoryMatchingCriteriaInterfaceMatchingOption) {
    /*! Matching is successful for USB accessories where every criterion/dictionary matches at least one USB interface. */
    AAUSBAccessoryMatchingCriteriaInterfaceMatchingOptionMatchAll,

    /*! Matching is successful for USB accessories where any of the criteria/dictionaries match at least one USB interface. */
    AAUSBAccessoryMatchingCriteriaInterfaceMatchingOptionMatchAny,
} NS_SWIFT_NAME(AAUSBAccessoryMatchingCriteria.InterfaceMatchingOption) API_AVAILABLE(macos(27.0));

/*!
 @abstract Class representing the accessory matching criteria for a USB accessory.
 @discussion
    A class conforming to the `AAUSBAccessoryListener` protocol can use `AAUSBAccessoryMatchingCriteria` objects
    to register itself with `AAUSBAccessoryManager`.
 @see AAUSBAccessoryListener
 @see AAUSBAccessoryManager
 */
AA_EXPORT API_AVAILABLE(macos(27.0)) NS_SWIFT_SENDABLE
@interface AAUSBAccessoryMatchingCriteria : NSObject<NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize a criteria object using a USB device matching dictionary.
 @discussion
    Use `-[IOUSBHostDevice createMatchingDictionaryWithVendorID:productID:bcdDevice:deviceClass:deviceSubclass:
    deviceProtocol:speed:productIDArray:]` to create such a matching dictionary.

    See USBSpec.h User-Space (https://developer.apple.com/documentation/iokit/usbspec_h_user-space?language=objc)
    in IOKit for more details about dictionary keys for the USB device properties.
 @param dictionary The matching dictionary containing USB device properties.
 @see IOUSBHostDevice
 */
- (nullable instancetype)initWithDeviceMatchingDictionary:(NSDictionary<NSString *, id NS_SWIFT_SENDABLE> *)dictionary NS_SWIFT_NAME(init(deviceMatchingDictionary:)) NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Initialize a criteria object using USB interface matching dictionaries, for the given USB device matching dictionary.
 @discussion
    Use `-[IOUSBHostDevice createMatchingDictionaryWithVendorID:productID:bcdDevice:deviceClass:deviceSubclass:
    deviceProtocol:speed:productIDArray:]` to create a USB device matching dictionary.

    Use `-[IOUSBHostInterface createMatchingDictionaryWithVendorID:productID:bcdDevice:interfaceNumber:
    configurationValue:interfaceClass:interfaceSubclass:interfaceProtocol:speed:productIDArray:]` to create
    a USB interface matching dictionary.

    See USBSpec.h User-Space (https://developer.apple.com/documentation/iokit/usbspec_h_user-space?language=objc)
    in IOKit for more details about dictionary keys for the USB device/interface matching dictionaries.
 @param deviceMatchingDictionary USB device matching dictionary.
 @param interfaceMatchingDictionaries USB interface matching dictionaries.
 @param interfaceMatchingOption Option specifying how interface matching is performed for a USB accessory.
    If the criteria is initialized with `AAUSBAccessoryMatchingCriteriaInterfaceMatchingOptionMatchAll`, then it
    evaluates to true for a USB accessory when
    - It matches the given non-`nil` `deviceMatchingDictionary`, and
    - For the currently set configuration, all the `interfaceMatchingDictionaries` match at least one of its USB interfaces.

    If the criteria is initialized with `AAUSBAccessoryMatchingCriteriaInterfaceMatchingOptionMatchAny`, then it
    evaluates to true for a USB accessory when
    - It matches the given non-`nil` `deviceMatchingDictionary`, and
    - For the currently set configuration, any of the `interfaceMatchingDictionaries` match at least one of its USB interfaces.
 @see IOUSBHostDevice
 @see IOUSBHostInterface
 */
- (nullable instancetype)initWithDeviceMatchingDictionary:(NSDictionary<NSString *, id NS_SWIFT_SENDABLE> * _Nullable)deviceMatchingDictionary interfaceMatchingDictionaries:(NSArray<NSDictionary<NSString *, id NS_SWIFT_SENDABLE> *> *)interfaceMatchingDictionaries interfaceMatchingOption:(AAUSBAccessoryMatchingCriteriaInterfaceMatchingOption)interfaceMatchingOption NS_SWIFT_NAME(init(deviceMatchingDictionary:interfaceMatchingDictionaries:interfaceMatchingOption:)) NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
