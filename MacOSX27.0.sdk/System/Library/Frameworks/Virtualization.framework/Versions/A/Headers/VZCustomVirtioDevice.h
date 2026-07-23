//
//  VZCustomVirtioDevice.h
//  Virtualization
//
//  Copyright © 2020-2026 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZGuestMemoryMapping;
@class VZNegotiatedVirtioFeatureSet;
@class VZVirtioDeviceSpecificConfiguration;
@class VZVirtioQueue;
@class VZVirtioSharedMemoryRegion;
@protocol VZCustomVirtioDeviceDelegate;

/**
 An interface that represents a custom Virtio device that you provide the implementation for.

 A Virtio device is a virtual emulated device the framework exposes to the guest OS following the Virtio standard. For more
  information about the Virtio standard, see the [Virtio specification](https://docs.oasis-open.org/virtio/virtio/v1.3/csd01/virtio-v1.3-csd01.html).

 A `VZCustomVirtioDevice` allows you to define, configure, and provide your own implementation for a device that uses the Virtio protocol.

 To define a `VZCustomVirtioDevice` create and configure a `VZCustomVirtioDeviceConfiguration` object.

 Once configured, the framework creates a `VZCustomVirtioDevice` object and returns it through the invocation of the delegate's ``Virtualization/VZCustomVirtioDeviceConfigurationDelegate/customVirtioConfiguration(_:didCreateDevice:)`` method. Implement a class that conforms to the ``VZCustomVirtioDeviceDelegate`` protocol to provide an implementation for the device.

 The Virtualization framework performs all operations on the ``VZCustomVirtioDevice`` and ``VZCustomVirtioDeviceDelegate`` through a serial queue that you can configure through the ``VZCustomVirtioDevice/deviceQueue`` property. If the queue isn't set, the framework performs all operations on the queue in the VM's ``VZVirtualMachine`` ``VZVirtualMachine/queue`` property by default.

 ## See Also

 - ``VZCustomVirtioDeviceConfiguration``
 - ``VZCustomVirtioDeviceConfigurationDelegate``
 - ``VZCustomVirtioDeviceDelegate``
 - ``VZVirtioQueue``
 - ``VZVirtioSharedMemoryRegion``

 */
VZ_EXPORT API_AVAILABLE(macos(27.0))
@interface VZCustomVirtioDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 The device's delegate.

 To be able to respond to events from a ``VZCustomVirtioDevice``, implement a class that conforms to the ``VZCustomVirtioDeviceDelegate`` protocol and assign it to this property. You can call the delegate as soon as ``Virtualization/VZCustomVirtioDeviceConfigurationDelegate/customVirtioConfiguration(_:didCreateDevice:)``
    returns, to avoid missing any calls, set this delegate when the framework calls ``Virtualization/VZCustomVirtioDeviceConfigurationDelegate/customVirtioConfiguration(_:didCreateDevice:)``.
 */
@property (nullable, weak) id <VZCustomVirtioDeviceDelegate> delegate;

/**
 The dispatch queue this device uses.

 The framework performs all operations on `VZCustomVirtioDevice` and ``VZCustomVirtioDeviceDelegate`` on this serial queue.
*/
@property (readonly) dispatch_queue_t deviceQueue;

/**
 The set of features that the driver and the device have successfully negotiated, or `nil` if no feature negotiation has taken place.

 The value is only valid after the framework calls ``VZCustomVirtioDeviceDelegate/customVirtioDeviceDidAcceptDriverOk:``. The framework calls this method when the guest driver sets `DRIVER_OK`.
 */
@property (readonly, nullable) VZNegotiatedVirtioFeatureSet *negotiatedFeatures;

/**
 An array of shared memory regions that this device exposes to the guest.

 ## See Also

  - ``VZVirtioSharedMemoryRegion``

 */
@property (readonly, copy) NSArray<VZVirtioSharedMemoryRegion *> *sharedMemoryRegions;

/**
 Returns guest memory mapping referred to by physicalAddress and length.

 - Parameters:
    - physicalAddress: The guest physical address of the memory.
    - length: Length of the memory.

 - Returns: A ``VZGuestMemoryMapping`` object that contains the guest memory in the host address space, or `nil` if `physicalAddress` and `length` do not reference a valid guest RAM region.
 */
- (nullable VZGuestMemoryMapping *)guestMemoryMappingAtPhysicalAddress:(uint64_t)physicalAddress length:(size_t)length;

/**
  Returns Virtio queue at the specified index that belongs to this device.

  The framework sets up the virtqueues (Virtio queues) when the guest driver sets `DRIVER_OK`; this call returns a valid result only after the framework calls ``VZCustomVirtioDeviceDelegate/customVirtioDeviceDidAcceptDriverOk:``.
 - Parameter index: The index of the ``VZVirtioQueue``.

 - Returns: The ``VZVirtioQueue`` object at the specified index, or `nil` if the index is invalid or the guest driver has disabled the queue.
 */
- (nullable VZVirtioQueue *)queueAtIndex:(uint16_t)index;

/**
 A request to reset the device.

 This method initiates a reset from the host by setting `DEVICE_NEEDS_RESET`, and the guest may or may not take action.
 The guest could also initiate a reset by itself. In both scenarios, the framework calls``VZCustomVirtioDeviceDelegate/customVirtioDeviceWillReset:`` when the device should reset.
 */
- (void)requestDeviceReset;

/**
 Updates the device's device-specific configuration.

 The size of the underlying data for the new configuration must be the same as the previous
    configuration. The framework raises an exception if this condition isn't met.

  - Parameters:
    - newConfiguration: The ``VZVirtioDeviceSpecificConfiguration`` object that contains the new configuration data.
    - completionHandler: A block the framework calls after the device's configuration updates successfully, or on error.
        The error parameter the framework passes to the block is `nil` if the configuration update was successful.
 */
- (void)updateDeviceSpecificConfiguration:(VZVirtioDeviceSpecificConfiguration *)newConfiguration completionHandler:(void (^)(NSError * _Nullable))completionHandler;

@end

NS_ASSUME_NONNULL_END
