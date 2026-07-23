/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
 *
 * This document is the property of Apple Inc.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Apple Inc.
 */

#pragma once

#include <IOKit/IOService.h>
#include <AppleFirmwareKit/AFKTightbeamTransportInterface.h>

typedef  struct tb_endpoint_s * tb_endpoint_t;
class AFKEndpointInterface;
class IOCommandGate;
class IOWorkLoop;

class AFKTightbeamEndpoint : public IOService,
                             public AFKTightbeamTransportInterface
{
    using super = IOService;

    OSDeclareDefaultStructors(AFKTightbeamEndpoint)

protected:
    /**
     * AFKTightbeamTransportInterface overrides
     */
    /** AFKTightbeamTransportInterface::setCommandHandler() */
    virtual void setCommandHandler (CommandHandlerBlock handler) override;
    /** AFKTightbeamTransportInterface::setReportHandler() */
    virtual void setReportHandler (ReportHandlerBlock handler) override;
    /** AFKTightbeamTransportInterface::activate() */
    virtual void activate () override;
    /** AFKTightbeamTransportInterface::sendReport() */
    virtual IOReturn sendReport (uint8_t * report, size_t reportLength) override;
    /** AFKTightbeamTransportInterface::sendCommand() */
    virtual void sendCommand (uint8_t * command, size_t commandLength, CommandResponseHandlerBlock handler) override;
    /** AFKTightbeamTransportInterface::sendResponse() */
    virtual IOReturn sendResponse (void * commandContext, IOReturn result, uint8_t * response, size_t responseLength) override;

public:

    bool start(IOService *provider) APPLE_KEXT_OVERRIDE;

    void stop(IOService *provider) APPLE_KEXT_OVERRIDE;

    bool willTerminate( IOService * provider, IOOptionBits options) APPLE_KEXT_OVERRIDE;

    void free() APPLE_KEXT_OVERRIDE;
    
    virtual tb_endpoint_t getTightbeamEndpoint();
    
private:
    /** Internal implementation of activation. Open the endpoint interface and register message handler blocks.. */
    void activateImpl();

    struct command_context {
        IOReturn result;
        uint8_t * respBuffer;
        size_t respBufferLength;
    };

    CommandHandlerBlock _cmdHandler;
    ReportHandlerBlock _reportHandler;

    OSPtr<IOCommandGate> _gate;
    OSPtr<IOWorkLoop> _workloop;
    OSPtr<AFKEndpointInterface> _interface;
    tb_endpoint_t _epi;
};
