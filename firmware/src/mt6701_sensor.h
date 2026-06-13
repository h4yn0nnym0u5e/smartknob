#pragma once

#include <SimpleFOC.h>
#include "driver/spi_master.h"

struct MT6701Error {
    bool error;
    uint8_t received_crc;
    uint8_t calculated_crc;
};

class MT6701Sensor : public Sensor {
    public:
        MT6701Sensor();

        // initialize the sensor hardware
        void init();

        // Get current shaft angle from the sensor hardware, and 
        // return it as a float in radians, in the range 0 to 2PI.
        //  - This method is pure virtual and must be implemented in subclasses.
        //    Calling this method directly does not update the base-class internal fields.
        //    Use update() when calling from outside code.
        float getSensorAngle();
        bool isPushed(void) 
        { 
            return 0 != push_status  // pushed
                && 0 == field_status // and valid!
                && 0 == loss_status;
        }
        uint8_t rawStatus(void)
        {
            return (loss_status << 3) | (push_status<<2) | field_status;
        }

        MT6701Error getAndClearError();
    private:

        spi_device_handle_t spi_device_;
        spi_transaction_t spi_transaction_ = {};

        float x_;
        float y_;
        uint32_t last_update_;

        // datasheet rev 1.9 section 7.8.2
        uint8_t field_status;   // 0: OK; 1: too strong; 2: too weak 
        uint8_t push_status;    // 1: pushed
        uint8_t loss_status;    // 1: loss of track

        MT6701Error error_ = {};
};
