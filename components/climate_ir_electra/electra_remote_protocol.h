#pragma once

#include <stdint.h>
#include <vector>

namespace ElectraRemoteProtocol
{
    static uint8_t address = 0b11000011;
    enum class TEMPERATURE
    {
        TEMP_16 = 0b00010,
        TEMP_17 = 0b10010,
        TEMP_18 = 0b01010,
        TEMP_19 = 0b11010,
        TEMP_20 = 0b00110,
        TEMP_21 = 0b10110,
        TEMP_22 = 0b01110,
        TEMP_23 = 0b11110,
        TEMP_24 = 0b00001,
        TEMP_25 = 0b10001,
        TEMP_26 = 0b01001,
        TEMP_27 = 0b11001,
        TEMP_28 = 0b00101,
        TEMP_29 = 0b10101,
        TEMP_30 = 0b01101,
        TEMP_31 = 0b11101,
        TEMP_32 = 0b00011,
    };

    enum class FAN_SPEED
    {
        FAN_AUTO = 0b101,
        FAN_LOW = 0b110,
        FAN_MEDIUM = 0b010,
        FAN_HIGH = 0b100,
    };

    enum class POWER
    {
        POWER_OFF = 0b00000000,
        POWER_ON = 0b00000100,
    };

    enum class SWING1
    {
        SWING_OFF = 0b111,
        SWING_ON = 0b000,
    };

    enum class SWING2
    {
        SWING_OFF = 0b111,
        SWING_ON = 0b000,
    };

    enum class BUTTON
    {
        BUTTON_POWER = 0b10100000,
        BUTTON_MODE = 0b01100000,
        BUTTON_TEMP_UP = 0b00000000,
        BUTTON_TEMP_DOWN = 0b10011100,
        BUTTON_SPEED = 0b00100000,
        BUTTON_SWING1 = 0b01000000,
        BUTTON_SWING2 = 0b11000000,
        BUTTON_SCREEN = 0b10101000,
        BUTTON_SLEEP = 0b11010000,
    };

    enum class MODE
    {
        MODE_AUTO = 0b000,
        MODE_COOL = 0b100,
        MODE_HEAT = 0b001,
        MODE_FAN = 0b011,
        MODE_DRY = 0b010,
    };

    enum class SLEEP
    {
        SLEEP_ON = 0b00100,
        SLEEP_OFF = 0b00000,
    };

    class ElectraRemoteProtocol
    {
    private:
        TEMPERATURE temp;
        FAN_SPEED fan_speed;
        POWER power;
        SWING1 swing1;
        SWING2 swing2;
        BUTTON button;
        MODE mode;
        SLEEP sleep;
        std::vector<uint8_t> bytes;

        uint8_t reverse_Uint8_t(uint8_t byte);

    public:
        ElectraRemoteProtocol();
        ~ElectraRemoteProtocol();

        void set_temperature(TEMPERATURE temp);
        TEMPERATURE get_temperature();
        void set_fan_speed(FAN_SPEED speed);
        FAN_SPEED get_fan_speed();
        void set_power(POWER power);
        POWER get_power();
        void set_swing1(SWING1 swing1);
        SWING1 get_swing1();
        void set_swing2(SWING2 swing2);
        SWING2 get_swing2();
        void set_mode(MODE mode);
        MODE get_mode();
        void set_sleep(SLEEP sleep);
        SLEEP get_sleep();
        std::vector<uint8_t> encode();
        void decode(const std::vector<uint8_t> &signal);
    };

}