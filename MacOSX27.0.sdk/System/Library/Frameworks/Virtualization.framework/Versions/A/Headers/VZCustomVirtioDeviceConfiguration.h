//
//  VZCustomVirtioDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZCustomVirtioDevice;
@class VZCustomVirtioDeviceProvider;
@class VZVirtioDeviceSpecificConfiguration;
@class VZVirtioFeatureSet;
@class VZVirtioSharedMemoryRegionConfiguration;
@protocol VZCustomVirtioDeviceConfigurationDelegate;

/**
 An object that defines a custom Virtio Device configuration.

 `VZCustomVirtioDeviceConfiguration` defines the configuration of a ``VZCustomVirtioDevice``.

    In order for a guest to be able to discover a Virtio device, you need to configure the following properties in the custom device configuration:

    - ``deviceID``
    - ``PCIClassID``
    - ``PCISubclassID``
    - ``virtioQueueCount``

    The remaining custom device configuration properties define additional features and configurations that are specific to the kind of Virtio device you're defining.

 If the `VZCustomVirtioDeviceConfiguration` you configure is valid, the Virtualization framework creates a ``VZCustomVirtioDevice`` upon the
 creation of the ``VZVirtualMachine``. The framework notifies you upon creating the device by calling
 ``Virtualization/VZCustomVirtioDeviceConfigurationDelegate/customVirtioConfiguration(_:didCreateDevice:)`` on the delegate method you provide.

 ## See Also

 - ``VZCustomVirtioDevice``
 - ``VZCustomVirtioDeviceConfigurationDelegate``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZCustomVirtioDeviceConfiguration : NSObject <NSCopying>

/**
 The Virtio device ID of the device.
 */
@property (readwrite) uint16_t deviceID;

/**
 The PCI class ID of the device.
 */
@property (readwrite) uint8_t PCIClassID;

/**
 The PCI subclass ID of the device.
 */
@property (readwrite) uint8_t PCISubclassID;

/**
 The number of virtqueues (Virtio queues) on this device.
 */
@property (readwrite) uint16_t virtioQueueCount;

/**
 The set of mandatory features that the device offers and the guest must accept.

 The mandatory features are the set of features that the device offers and the guest must accept.
 The framework won't successfully initialize the device if the guest driver fails to accept this set of features.
 The feature bit `VIRTIO_F_VERSION_1` is always set to `1` internally by default.
 */
@property (readonly, strong) VZVirtioFeatureSet *mandatoryFeatures;

/**
 The set of optional features that the device offers.

 The optional features are the set of features that the guest driver may or may not accept, see
  ``VZCustomVirtioDevice/negotiatedFeatures`` for the set of features that the guest accepts. A few feature bits are always set
    internally by default for optimal performance.
 */
@property (readonly, strong) VZVirtioFeatureSet *optionalFeatures;

/**
 The device-specific configuration for the device.
 */
@property (nullable, strong) VZVirtioDeviceSpecificConfiguration *deviceSpecificConfiguration;

/**
 The custom Virtio device provider.

 This data defines how the virtual device is implemented.

 ## See Also

  - ``VZCustomVirtioDeviceDelegateProvider``

 */
@property (readwrite, nullable, strong) VZCustomVirtioDeviceProvider *provider;

/**
 The maximum number of Virtio shared memory regions the framework allows.

 ## See Also

 - ``VZCustomVirtioDeviceConfiguration/sharedMemoryRegions``

 */
@property (class, readonly) NSUInteger maximumAllowedSharedMemoryRegionCount;

/**
 The list of shared memory regions.

 The list is empty by default.
 */
@property (readwrite, copy) NSArray<VZVirtioSharedMemoryRegionConfiguration *> *sharedMemoryRegions;

/*!
 @abstract Whether the device supports save/restore.
 @discussion
    This property defaults to `NO`. Set to `YES` if the device supports save/restore.
    If `supportsSaveRestore` is `YES` but the delegate set on `VZCustomVirtioDevice` does not actually
    implement the save/restore methods, an exception will be raised.
 */
@property (readwrite) BOOL supportsSaveRestore;

@end

NS_ASSUME_NONNULL_END
