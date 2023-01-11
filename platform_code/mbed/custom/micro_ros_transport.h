#if !defined(CommunicationInterface_h)
#define CommunicationInterface_h

#include <mbed.h>
#include <rmw_microros/custom_transport.h>
#include <uxr/client/transport.h>
#include "UARTSerial.h"

extern "C" {

static bool platformio_transport_open(struct uxrCustomTransport *transport) {
    mbed::UARTSerial *serial = (mbed::UARTSerial *)transport->args;
    serial->set_flow_control(mbed::SerialBase::Disabled);
    serial->set_blocking(false);
    return true;
}

static bool platformio_transport_close(struct uxrCustomTransport *transport) {
    return true;
}

static size_t platformio_transport_write(struct uxrCustomTransport *transport,
                                     const uint8_t *buf, size_t len,
                                     uint8_t *err) {
    mbed::UARTSerial *serial = (mbed::UARTSerial *)transport->args;
    return serial->write(buf, len);
}

static size_t platformio_transport_read(struct uxrCustomTransport *transport,
                                    uint8_t *buf, size_t len, int timeout,
                                    uint8_t *err) {
    mbed::UARTSerial *serial = (mbed::UARTSerial *)transport->args;
    return serial->read(buf, len);
}
}

void set_microros_serial_transports(mbed::UARTSerial *serial) {
    rmw_uros_set_custom_transport(MICROROS_TRANSPORTS_FRAMING_MODE, 
    				serial, 
    				platformio_transport_open,
                               	platformio_transport_close, 
                               	platformio_transport_write,
                                platformio_transport_read);
}

#endif // CommunicationInterface_h
