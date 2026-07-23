/*
 * Copyright (C) 2026 Apple Inc. All rights reserved.
 *
 * This document is the property of Apple Inc.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Apple Inc.
*/


#ifndef _AFKHIDTBDEVICE_H
#define _AFKHIDTBDEVICE_H


#include <IOKit/hid/IOHIDDevice.h>
#include <IOKit/IOService.h>
#include "AFKHIDTBDevice_c.h"
#include <sys/queue.h>

class AFKTightbeamEndpoint;

/*!
 * @class AFKHIDTBDevice
 * @brief IOKit kernel extension implementing HID device interface for firmware-based HID devices
 */
class AFKHIDTBDevice : public IOHIDDevice
{
    OSDeclareDefaultStructors (AFKHIDTBDevice);

private:

    /**
     * @function serializeDebugState
     * @brief Serialize debug statistics for IORegistry
     * @param ref Unused reference parameter
     * @param serializer OSSerializer to serialize debug state into
     * @return true on successful serialization, false otherwise
     * @discussion Serializes failure counters (_setReportFailCount, _getReportFailCount)
     * for debugging purposes. Registered as DebugState property in IORegistry.
     */
    bool serializeDebugState(void *ref, OSSerialize *serializer);

    /**
     * @function handleMatchingNotification
     * @brief Service matching notification handler for companion Tightbeam endpoint
     * @param refCon Reference context (unused)
     * @param service Matched IOService
     * @param notifier IONotifier that triggered this callback
     * @return true to continue notifications, false to stop
     * @discussion Called when the companion endpoint (specified by KEXTTBEPCompanion property)
     * is published. Completes Tightbeam setup by initializing server endpoint and server callback,
     * then calls registerService(). Removes notification after success.
     */
    bool handleMatchingNotification(void *refCon, IOService *service, IONotifier *notifier);

    bool setupDeviceProperties();

    /**
     * @function handleSendReport
     * @brief Tightbeam server callback for receiving input reports from firmware
     * @param timestamp Timestamp when report was generated
     * @param report Tightbeam report structure containing report data
     * @discussion Called by firmware via Tightbeam RPC to send input reports to the kernel.
     * Creates IOBufferMemoryDescriptor and forwards to handleReportWithTime().
     * This is the primary data path for input events from firmware to IOHIDFamily.
     */
    void handleSendReport(uint64_t timestamp, const afkhidtbdevice_report_s * report);

    /**
     * @function serviceMatchingThreadCallHandler
     * @brief thread call handler for service matching notification
     * @param target The AFKHIDTBDevice instance (this)
     * @discussion Called from thread_call context. Dispatches work to workloop via gated method.
     */
    void serviceMatchingThreadCallHandler(thread_call_param_t param);

    /**
     * @function completeServiceMatchingGated
     * @brief Gated method that completes Tightbeam server initialization
     * @discussion Called on workloop via runActionBlock from thread call handler.
     * Performs all heavy allocations, server initialization, and registerService().
     * @return kIOReturnSuccess on success, error code otherwise
     */
    IOReturn completeServiceMatchingGated();


protected:
    bool                              _serverStarted;
    
    /*!
     @function handleStart
     @abstract Prepare the hardware and driver to support I/O operations.
     @discussion IOHIDDevice will call this method from start() before
     any I/O operations are issued to the concrete subclass. Methods
     such as newReportDescriptor() are only called after handleStart()
     has returned true. A subclass that overrides this method should
     begin its implementation by calling the version in super, and
     then check the return value.
     @param provider The provider argument passed to start().
     @result True on success, or false otherwise. Returning false will
     cause start() to fail and return false.
     */
    virtual bool handleStart(IOService * provider) APPLE_KEXT_OVERRIDE;
       
    /*! @function getReportGated
     @abstract Get a report from the HID device. Called in gate context by implementation of getReport
     @param report A memory descriptor that describes the memory to store
     the report read from the HID device.
     @param reportType The report type.
     @param options The lower 8 bits will represent the Report ID.  The
     other 24 bits are options to specify the request.
     @result kIOReturnSuccess on success, or an error return otherwise. */
    IOReturn getReportGated(IOMemoryDescriptor   * report,
                            IOHIDReportType      reportType,
                            IOOptionBits         options);
    
    /*! @function setReportGated
     @abstract Send a report to the HID device. Called in gate context by implementation of setReport
     @param report A memory descriptor that describes the report to send
     to the HID device.
     @param reportType The report type.
     @param options The lower 8 bits will represent the Report ID.  The
     other 24 bits are options to specify the request.
     @result kIOReturnSuccess on success, or an error return otherwise. */
    IOReturn setReportGated(IOMemoryDescriptor   * report,
                            IOHIDReportType      reportType,
                            IOOptionBits         options);
    
public:

    /**
     * @function start
     * @brief Initialize the device and set up Tightbeam communication
     * @param provider Provider IOService (expected to be AFKTightbeamEndpoint)
     * @return true if initialization successful, false otherwise
     * @discussion This method:
     * 1. Allocates Tightbeam client and server structures
     * 2. Validates provider is AFKTightbeamEndpoint and retains it as _epIN
     * 3. Sets up device properties via setupDeviceProperties()
     * 4. Calls super::start() to initialize the IOHIDDevice
     * 5. Sets up service matching notification for companion endpoint (specified by KEXTTBEPCompanion property)
     * @note Device registration is deferred until handleMatchingNotification() finds companion endpoint and calls registerService()
     * @note Calls super::stop() on failure to clean up partial initialization
     */
    virtual bool start(IOService * provider) APPLE_KEXT_OVERRIDE;

    /**
     * @function stop
     * @brief Stop the device and remove matching notification
     * @param provider Provider IOService
     * @discussion Removes the companion endpoint matching notification and calls super::stop().
     * Actual cleanup of Tightbeam resources happens in free().
     * @note This may be called during initialization failure or normal termination
     */
    virtual void stop(IOService * provider) APPLE_KEXT_OVERRIDE;

    /**
     * @function free
     * @brief Free allocated resources
     * @discussion Releases provider, notification, client, server, and device description.
     * Called during object destruction.
     */
    virtual void free() APPLE_KEXT_OVERRIDE;

    /*!
     @function newReportDescriptor
     @abstract Create and return a new memory descriptor that describes the
     report descriptor for the HID device.
     @result kIOReturnSuccess on success, or an error return otherwise.
     */
    
    virtual IOReturn newReportDescriptor(IOMemoryDescriptor ** descriptor ) const APPLE_KEXT_OVERRIDE;
    
    /*!
     @function newTransportString
     @abstract Returns a string object that describes the transport
     layer used by the HID device.
     @result A string object. The caller must decrement the retain count
     on the object returned.
     */
    virtual OSString * newTransportString() const APPLE_KEXT_OVERRIDE;
    
    /*! @function newProductIDNumber
     @abstract Returns a number object that describes the product ID
     of the HID device.
     @result A number object. The caller must decrement the retain count
     on the object returned. */
    virtual OSNumber * newProductIDNumber() const APPLE_KEXT_OVERRIDE;

    /*! @function newSerialNumberString
     @abstract Returns a string object that describes the serial number
     of the HID device.
     @result A number object. The caller must decrement the retain count
     on the object returned. */
    virtual OSString * newSerialNumberString(void) const APPLE_KEXT_OVERRIDE;
   
    /*! @function newReportIntervalNumber
     @abstract Returns a number object that describes the report interval
     of the HID device.
     @result A number object. The caller must decrement the retain count
     on the object returned. */
    virtual OSNumber * newReportIntervalNumber(void) const APPLE_KEXT_OVERRIDE;
    
    /*! @function newLocationIDNumber
     @abstract Returns a number object that describes the location
     of the HID device.
     @result A number object. The caller must decrement the retain count
     on the object returned. */
    virtual OSNumber *newLocationIDNumber(void) const APPLE_KEXT_OVERRIDE;
    
    
    /*! @function getReport
     @abstract Get a report from the HID device.
     @param report A memory descriptor that describes the memory to store
     the report read from the HID device.
     @param reportType The report type.
     @param options The lower 8 bits will represent the Report ID.  The
     other 24 bits are options to specify the request.
     @result kIOReturnSuccess on success, or an error return otherwise. */

    virtual IOReturn getReport(IOMemoryDescriptor   * report,
                               IOHIDReportType      reportType,
                               IOOptionBits         options) APPLE_KEXT_OVERRIDE;
    
    /*! @function setReport
     @abstract Send a report to the HID device.
     @param report A memory descriptor that describes the report to send
     to the HID device.
     @param reportType The report type.
     @param options The lower 8 bits will represent the Report ID.  The
     other 24 bits are options to specify the request.
     @result kIOReturnSuccess on success, or an error return otherwise. */

    virtual IOReturn setReport(IOMemoryDescriptor   * report,
                               IOHIDReportType      reportType,
                               IOOptionBits         options = 0) APPLE_KEXT_OVERRIDE;
    
private:
    OSPtr<IOCommandGate> _commandGate;          ///< Command gate for serializing device operations on workloop
    OSPtr<IOWorkLoop> _workLoop;                ///< Workloop for asynchronous operations
    uint32_t _setReportFailCount;          ///< Debug counter for failed setReport operations
    uint32_t _getReportFailCount;          ///< Debug counter for failed getReport operations

    // Tightbeam infrastructure
    OSPtr<AFKTightbeamEndpoint> _epIN;          ///< Provider endpoint for receiving DeviceClient server callbacks (sendReport)
    OSPtr<AFKTightbeamEndpoint> _epOUT;         ///< Companion endpoint for sending Device client RPCs (getReport/setReport/etc)

    afkhidtbdevice_device_s * _client;                      ///< Tightbeam client for calling Device RPCs
    afkhidtbdevice_deviceclient__server_s * _server;        ///< Tightbeam server for receiving sendReport callbacks
    afkhidtbdevice_deviceclient__service_s * _service;      ///< Tightbeam service connection handle for DeviceClient

    IONotifier * _notif;   ///< Matching notification for finding companion endpoint
    thread_call_t _matchingThread;   ///< Thread call for deferred service matching completion
};


#endif /* !_AFKHIDTBDEVICE_H */


