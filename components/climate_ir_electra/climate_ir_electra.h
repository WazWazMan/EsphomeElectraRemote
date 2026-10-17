#pragma once

#include "esphome/components/climate_ir/climate_ir.h"
#include "electra_remote_protocol.h"
#include <set>

namespace esphome::climate_ir_electra
{

    // Temperature
    const uint8_t TEMP_MIN = 16; // Celsius
    const uint8_t TEMP_MAX = 32; // Celsius

    class ElectraIrClimate final : public esphome::climate_ir::ClimateIR
    {
    public:
        ElectraIrClimate() : climate_ir::ClimateIR(TEMP_MIN, TEMP_MAX, 1.0f, true, true, {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
                                                   {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_BOTH, climate::CLIMATE_SWING_VERTICAL, climate::CLIMATE_SWING_HORIZONTAL})
        {
            this->set_supports_heat_cool(false);
        }

        void set_header_high(uint32_t header_high) { this->header_high_ = header_high; }
        void set_header_low(uint32_t header_low) { this->header_low_ = header_low; }
        void set_bit_high(uint32_t bit_high) { this->bit_high_ = bit_high; }
        void set_bit_one_low(uint32_t bit_one_low) { this->bit_one_low_ = bit_one_low; }
        void set_bit_zero_low(uint32_t bit_zero_low) { this->bit_zero_low_ = bit_zero_low; }

    protected:
        /// Transmit via IR the state of this climate controller.
        void transmit_state() override;
        /// Handle received IR Buffer
        bool on_receive(remote_base::RemoteReceiveData data) override;
        ElectraRemoteProtocol::ElectraRemoteProtocol electraRemoteProtocol;
        uint32_t header_high_;
        uint32_t header_low_;
        uint32_t bit_high_;
        uint32_t bit_one_low_;
        uint32_t bit_zero_low_;
    };
}