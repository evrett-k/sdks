/* iig(DriverKit-509.0.1) generated from AFKEndpointInterface.iig */

/* AFKEndpointInterface.iig:1-31 */
/*
 * Copyright (c) 2021-2025 Apple Inc.  All rights reserved.
 *
 * This document is the property of Apple Inc.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Apple Inc.
 */

#if !__IIG
#if KERNEL
#include <AppleFirmwareKit/AFKEndpointInterface.h>
#endif
#endif

#ifndef _AFKDriverKit_AFKEndpointInterface_h
#define _AFKDriverKit_AFKEndpointInterface_h
#include <AFKDriverKit/AFKDriverKitCommon.h>
#if __has_include(<AppleFirmwareKit/AFKEPSendOpts.h>)
#include <AppleFirmwareKit/AFKEPSendOpts.h>
#elif __has_include(<AFKDriverKit/AFKEPSendOpts.h>)
#include <AFKDriverKit/AFKEPSendOpts.h>
#endif
#include <DriverKit/IOService.h>  /* .iig include */

typedef void (^CloseHandler)(void);

class AFKUserDataPipe;

/* source class AFKEndpointInterface AFKEndpointInterface.iig:32-145 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*! @class       AFKEndpointInterface
 *  @brief       Interface for interacting with an AFKEndpoint.
 *  @classdesign Match this class as a client and open it to begin communication with AFKEndpoints.
 *  DK driver require "com.apple.developer.driverkit.transport.afk" entitlement to interact with object
 *
 */
class KERNEL AFKEndpointInterface : public IOService
{
    using super = IOService;

public:
    // Overridden functions, see IOService documentation for usage
    virtual bool init() override;
    virtual void free() override;

    /*!
     * @function open
     * @abstract Open the interface, call before using the interface.
     * @param    forClient The IOService based client of the interface.
     * @param    commandHandler The callback.
     * @param    reportHandler The callback.
     * @param    options Options to specify the request. Currently the only
     *           supported option is kOpenOptions_Multi_Client, to indicate
     *           if exclusive access is requested.
     * @result   bool indicating if the open was successful.
     */
    virtual bool open(IOService * forClient,
                      CommandBlock commandHandler,
                      ReportBlock reportHandler,
                      uint32_t options) LOCALONLY;

    /*!
     * @function close
     * @abstract Close the interface.
     *           This will need to be called, and the provided handler block
     *           will need to be invoked before it is safe to release the interface.
     * @param    forClient The IOService based client of the interface.
     * @param    handler The interface has asynchronous tasks that need
     *           to be completed after close. This handler will be invoked
     *           when those tasks are complete and it is safe to release
     *           the interface. The handler will always be invoked.
     * @param    options Options to specify the request. Currently there
     *           are no supported options.
     * @result   bool indicating if the close was successful.
     */
    virtual bool close(IOService * forClient,
                       CloseHandler handler,
                       uint32_t options) LOCALONLY;

    /*! @function enqueueReport
     *  @abstract Send a report via the endpoint interface.
     *            This method will send a report packet over the endpoint interface.
     *            A report is a message that does not require an acknowledgement.
     *            The packet will either be sent immediately (blocking), or it will
     *            be enqueued and sent asynchronously depending on the endpoint
     *            implementation.
     *  @param    packetType The type of packet, implementation specific.
     *            Values less than kIOPPacketTypePrivate are reserved for internal
     *            AFK use. See AFKPacket.h.
     *  @param    reportBuffer The report to send. Can be specified as an
     *            IOBufferMemoryDescriptor or a raw buffer and size.
     *  @param    options See AFKEPReportOptions for available options.
     *  @result   kIOReturnSuccess if the enqueue was successful,
     *            an error code otherwise.
     */
    virtual IOReturn enqueueReport(uint8_t packetType,
                                   PayloadBuffer reportBuffer,
                                   AFKEPReportOptions options = AFKEPReportOptions::defReportOpt()) LOCALONLY;

    /*! @function enqueueCommand
     *  @abstract Send a command via the endpoint interface.
     *            This method will send a command packet over the endpoint
     *            interface. A command is a message that requires an
     *            acknowledgement. The packet will either be sent immediately
     *            (blocking), or it will be enqueued and sent asynchronously
     *            depending on the endpoint implementation.
     *  @param    context Caller defined context, passed to the response
     *            handler when a response is received for this command.
     *  @param    packetType The type of packet, implementation specific.
     *            Values less than kIOPPacketTypePrivate are reserved for
     *            internal AFK use. See AFKPacket.h.
     *  @param    commandBuffer The command to send. Can be specified
     *            as an IOBufferMemoryDescriptor or a raw buffer and size.
     *  @param    responseHandler Response handler
     *  @param    options See AFKEPCommandResponseOptions for available options.
     */
    virtual void enqueueCommand(uint8_t packetType,
                                PayloadBuffer commandBuffer,
                                ResponseHandler responseHandler,
                                AFKEPCommandResponseOptions options =
                                    AFKEPCommandResponseOptions::defCommandResponseOpt()) LOCALONLY;

    /*! @function enqueueResponse
     *  @abstract Send a response via the endpoint interface.
     *            This method will send a response packet over the endpoint
     *            interface. A response is a message sent in response to a
     *            command received via the command handler. The packet
     *            will either be sent immediately (blocking), or it will be
     *            enqueued and sent asynchronously depending on the
     *            endpoint implementation.
     *  @param    id CommandID that was previously passed
     *            to the command handler.
     *  @param    result Result of the associated command.
     *  @param    responseBuffer The response to send. Can be specified as an
     *            IOBufferMemoryDescriptor or a raw buffer and size.
     *  @param    options See AFKEPCommandResponseOptions for available options.
     *  @return   kIOReturnSuccess if the enqueue was successful,
     *            an error code otherwise.
     */
    virtual IOReturn enqueueResponse(CommandID id,
                                     IOReturn result,
                                     PayloadBuffer responseBuffer,
                                     AFKEPCommandResponseOptions options =
                                     AFKEPCommandResponseOptions::defCommandResponseOpt()) LOCALONLY;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class AFKEndpointInterface AFKEndpointInterface.iig:32-145 */

#define AFKEndpointInterface_Close_ID            0x8b3103b608452ec4ULL
#define AFKEndpointInterface_Open_ID            0xabcd77e378998de1ULL

#define AFKEndpointInterface_Close_Args \
        IOService * forClient, \
        uint32_t options

#define AFKEndpointInterface_Open_Args \
        IOService * forClient, \
        AFKUserDataPipe ** pipe, \
        uint32_t options

#define AFKEndpointInterface_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(AFKEndpointInterface * self, const IORPC rpc);\
\
    kern_return_t\
    Close(\
        IOService * forClient,\
        uint32_t options,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    Open(\
        IOService * forClient,\
        AFKUserDataPipe ** pipe,\
        uint32_t options,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Close_Handler)(OSMetaClassBase * target, AFKEndpointInterface_Close_Args);\
    static kern_return_t\
    Close_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        Close_Handler func);\
\
    typedef kern_return_t (*Open_Handler)(OSMetaClassBase * target, AFKEndpointInterface_Open_Args);\
    static kern_return_t\
    Open_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        Open_Handler func);\
\


#define AFKEndpointInterface_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    Close_Impl(AFKEndpointInterface_Close_Args);\
\
    kern_return_t\
    Open_Impl(AFKEndpointInterface_Open_Args);\
\


#define AFKEndpointInterface_VirtualMethods \
\
public:\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    open(\
        IOService * forClient,\
        CommandBlock commandHandler,\
        ReportBlock reportHandler,\
        uint32_t options) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    close(\
        IOService * forClient,\
        CloseHandler handler,\
        uint32_t options) APPLE_KEXT_OVERRIDE;\
\
    virtual IOReturn\
    enqueueReport(\
        uint8_t packetType,\
        PayloadBuffer reportBuffer,\
        AFKEPReportOptions options = AFKEPReportOptions::defReportOpt()) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    enqueueCommand(\
        uint8_t packetType,\
        PayloadBuffer commandBuffer,\
        ResponseHandler responseHandler,\
        AFKEPCommandResponseOptions options = AFKEPCommandResponseOptions::defCommandResponseOpt()) APPLE_KEXT_OVERRIDE;\
\
    virtual IOReturn\
    enqueueResponse(\
        CommandID id,\
        IOReturn result,\
        PayloadBuffer responseBuffer,\
        AFKEPCommandResponseOptions options = AFKEPCommandResponseOptions::defCommandResponseOpt()) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gAFKEndpointInterfaceMetaClass;
extern const OSClassLoadInformation AFKEndpointInterface_Class;

class AFKEndpointInterfaceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  AFKEndpointInterfaceInterface : public OSInterface
{
public:
    virtual bool
    open(IOService * forClient,
        CommandBlock commandHandler,
        ReportBlock reportHandler,
        uint32_t options) = 0;

    virtual bool
    close(IOService * forClient,
        CloseHandler handler,
        uint32_t options) = 0;

    virtual IOReturn
    enqueueReport(uint8_t packetType,
        PayloadBuffer reportBuffer,
        AFKEPReportOptions options) = 0;

    virtual void
    enqueueCommand(uint8_t packetType,
        PayloadBuffer commandBuffer,
        ResponseHandler responseHandler,
        AFKEPCommandResponseOptions options) = 0;

    virtual IOReturn
    enqueueResponse(CommandID id,
        IOReturn result,
        PayloadBuffer responseBuffer,
        AFKEPCommandResponseOptions options) = 0;

    bool
    open_Call(IOService * forClient,
        CommandBlock commandHandler,
        ReportBlock reportHandler,
        uint32_t options)  { return open(forClient, commandHandler, reportHandler, options); };\

    bool
    close_Call(IOService * forClient,
        CloseHandler handler,
        uint32_t options)  { return close(forClient, handler, options); };\

    IOReturn
    enqueueReport_Call(uint8_t packetType,
        PayloadBuffer reportBuffer,
        AFKEPReportOptions options)  { return enqueueReport(packetType, reportBuffer, options); };\

    void
    enqueueCommand_Call(uint8_t packetType,
        PayloadBuffer commandBuffer,
        ResponseHandler responseHandler,
        AFKEPCommandResponseOptions options)  { return enqueueCommand(packetType, commandBuffer, responseHandler, options); };\

    IOReturn
    enqueueResponse_Call(CommandID id,
        IOReturn result,
        PayloadBuffer responseBuffer,
        AFKEPCommandResponseOptions options)  { return enqueueResponse(id, result, responseBuffer, options); };\

};

struct AFKEndpointInterface_IVars;
struct AFKEndpointInterface_LocalIVars;

class AFKEndpointInterface : public IOService, public AFKEndpointInterfaceInterface
{
#if !KERNEL
    friend class AFKEndpointInterfaceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef AFKEndpointInterface_DECLARE_IVARS
AFKEndpointInterface_DECLARE_IVARS
#else /* AFKEndpointInterface_DECLARE_IVARS */
    union
    {
        AFKEndpointInterface_IVars * ivars;
        AFKEndpointInterface_LocalIVars * lvars;
    };
#endif /* AFKEndpointInterface_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gAFKEndpointInterfaceMetaClass; };
#endif /* KERNEL */

    using super = IOService;

#if !KERNEL
    AFKEndpointInterface_Methods
    AFKEndpointInterface_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* AFKEndpointInterface.iig:147-148 */

// Internally used private functions
/* AFKEndpointInterface.iig:158- */

#endif /* _AFKDriverKit_AFKEndpointInterface_h */
