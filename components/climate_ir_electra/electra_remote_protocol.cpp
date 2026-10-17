#include "electra_remote_protocol.h"

ElectraRemoteProtocol::ElectraRemoteProtocol::ElectraRemoteProtocol()
    : temp(TEMPERATURE::TEMP_24), fan_speed(FAN_SPEED::FAN_AUTO), power(POWER::POWER_OFF), swing1(SWING1::SWING_OFF), swing2(SWING2::SWING_OFF), button(BUTTON::BUTTON_POWER), mode(MODE::MODE_COOL), sleep(SLEEP::SLEEP_OFF) {}

ElectraRemoteProtocol::ElectraRemoteProtocol::~ElectraRemoteProtocol() = default;

void ElectraRemoteProtocol::ElectraRemoteProtocol::set_temperature(TEMPERATURE temp)
{
    if (temp > this->temp)
    {
        this->button = BUTTON::BUTTON_TEMP_UP;
    }
    else
    {
        this->button = BUTTON::BUTTON_TEMP_DOWN;
    }

    this->temp = temp;
}

ElectraRemoteProtocol::TEMPERATURE ElectraRemoteProtocol::ElectraRemoteProtocol::get_temperature()
{
    return this->temp;
}

void ElectraRemoteProtocol::ElectraRemoteProtocol::set_fan_speed(FAN_SPEED speed)
{
    this->fan_speed = speed;
    this->button = BUTTON::BUTTON_SPEED;
}

ElectraRemoteProtocol::FAN_SPEED ElectraRemoteProtocol::ElectraRemoteProtocol::get_fan_speed()
{
    return this->fan_speed;
}

void ElectraRemoteProtocol::ElectraRemoteProtocol::set_power(POWER power)
{
    this->power = power;
    this->button = BUTTON::BUTTON_POWER;
}

ElectraRemoteProtocol::POWER ElectraRemoteProtocol::ElectraRemoteProtocol::get_power()
{
    return this->power;
}

void ElectraRemoteProtocol::ElectraRemoteProtocol::set_swing1(SWING1 swing1)
{
    this->swing1 = swing1;
    this->button = BUTTON::BUTTON_SWING1;
}

ElectraRemoteProtocol::SWING1 ElectraRemoteProtocol::ElectraRemoteProtocol::get_swing1()
{
    return this->swing1;
}
void ElectraRemoteProtocol::ElectraRemoteProtocol::set_swing2(SWING2 swing2)
{
    this->swing2 = swing2;
    this->button = BUTTON::BUTTON_SWING2;
}

ElectraRemoteProtocol::SWING2 ElectraRemoteProtocol::ElectraRemoteProtocol::get_swing2()
{
    return this->swing2;
}
void ElectraRemoteProtocol::ElectraRemoteProtocol::set_mode(MODE mode)
{
    this->mode = mode;
    this->button = BUTTON::BUTTON_MODE;
}

ElectraRemoteProtocol::MODE ElectraRemoteProtocol::ElectraRemoteProtocol::get_mode()
{
    return this->mode;
}

void ElectraRemoteProtocol::ElectraRemoteProtocol::set_sleep(SLEEP sleep)
{
    this->sleep = sleep;
    this->button = BUTTON::BUTTON_SLEEP;
}

ElectraRemoteProtocol::SLEEP ElectraRemoteProtocol::ElectraRemoteProtocol::get_sleep()
{
    return this->sleep;
}

uint8_t ElectraRemoteProtocol::ElectraRemoteProtocol::reverse_Uint8_t(uint8_t byte)
{
    uint8_t reversed = 0;
    for (int i = 0; i < 8; ++i)
    {
        reversed <<= 1;
        reversed |= (byte & 1);
        byte >>= 1;
    }
    return reversed;
}

std::vector<uint8_t> ElectraRemoteProtocol::ElectraRemoteProtocol::encode()
{
    std::vector<uint8_t> signal_bytes(13);

    // byte 0 address
    signal_bytes[0] = address;

    // byte 1 swing 1 and temp
    // swing1, tmp
    // xxx     yyyyy
    signal_bytes[1] = (static_cast<uint8_t>(swing1) << 5) | (static_cast<uint8_t>(temp));

    // byte 2 hours(which we ignore and set to 00000) and swing 2
    // const swing2
    // 00000 xxx
    // incase we need hours we need to change this

    signal_bytes[2] = (0b00000 << 3) | (static_cast<uint8_t>(swing2));

    // byte 3 minutes(which we ignore and set to 00000)
    // minutes
    // 00000000
    // incase we need minutes we need to change this

    signal_bytes[3] = 0b00000000;

    // byte 4 fullhours of time(which we ignore and set to 00000) and fan speed
    // const fan speed
    // 00000 xxx
    signal_bytes[4] = (0b00000 << 3) | (static_cast<uint8_t>(fan_speed));

    // byte 5 last time i checked it have the stong off/on and is timer on
    // we set it all to 0 for now
    signal_bytes[5] = 0b00000000;

    // byte 6 sleep and mode
    // sleep, mode
    // xxxxx  yyy
    signal_bytes[6] = (static_cast<uint8_t>(sleep) << 3) | (static_cast<uint8_t>(mode));

    // byte 7 last i chagned it changed feel/health mode but we ignore it and set to 00000000
    signal_bytes[7] = 0b00000000;

    // byte 8 const 0b0000000
    signal_bytes[8] = 0b00000000;

    // byte 9 on off in this case, but i saw some other remores that control here is heating and is timer and is health
    // we ignore it and use it as on/off switch
    signal_bytes[9] = static_cast<uint8_t>(power);

    // byte 10 const 0b00000000
    signal_bytes[10] = 0b00000000;

    // byte 11 button
    signal_bytes[11] = static_cast<uint8_t>(button);

    // calculate checksum
    uint8_t checksum = 0;
    for (size_t i = 0; i < 12; ++i)
    {
        checksum += reverse_Uint8_t(signal_bytes[i]);
    }

    signal_bytes[12] = reverse_Uint8_t(checksum);

    return signal_bytes;
}

void ElectraRemoteProtocol::ElectraRemoteProtocol::decode(const std::vector<uint8_t> &signal)
{
    if (signal.size() != 13)
    {
        return;
    }

    const auto temp_value = signal[1] & 0b00011111;
    switch (temp_value)
    {
    case static_cast<uint8_t>(TEMPERATURE::TEMP_16):
        this->temp = TEMPERATURE::TEMP_16;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_17):
        this->temp = TEMPERATURE::TEMP_17;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_18):
        this->temp = TEMPERATURE::TEMP_18;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_19):
        this->temp = TEMPERATURE::TEMP_19;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_20):
        this->temp = TEMPERATURE::TEMP_20;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_21):
        this->temp = TEMPERATURE::TEMP_21;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_22):
        this->temp = TEMPERATURE::TEMP_22;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_23):
        this->temp = TEMPERATURE::TEMP_23;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_24):
        this->temp = TEMPERATURE::TEMP_24;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_25):
        this->temp = TEMPERATURE::TEMP_25;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_26):
        this->temp = TEMPERATURE::TEMP_26;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_27):
        this->temp = TEMPERATURE::TEMP_27;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_28):
        this->temp = TEMPERATURE::TEMP_28;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_29):
        this->temp = TEMPERATURE::TEMP_29;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_30):
        this->temp = TEMPERATURE::TEMP_30;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_31):
        this->temp = TEMPERATURE::TEMP_31;
        break;
    case static_cast<uint8_t>(TEMPERATURE::TEMP_32):
        this->temp = TEMPERATURE::TEMP_32;
        break;
    default:
        this->temp = TEMPERATURE::TEMP_24;
        break;
    }

    const uint8_t swing1_bits = (signal[1] >> 5) & 0b00000111;
    this->swing1 = (swing1_bits == 0b000) ? SWING1::SWING_ON : SWING1::SWING_OFF;

    const uint8_t swing2_bits = signal[2] & 0b00000111;
    this->swing2 = (swing2_bits == 0b000) ? SWING2::SWING_ON : SWING2::SWING_OFF;

    const uint8_t fan_bits = signal[4] & 0b00000111;
    switch (fan_bits)
    {
    case static_cast<uint8_t>(FAN_SPEED::FAN_AUTO):
        this->fan_speed = FAN_SPEED::FAN_AUTO;
        break;
    case static_cast<uint8_t>(FAN_SPEED::FAN_LOW):
        this->fan_speed = FAN_SPEED::FAN_LOW;
        break;
    case static_cast<uint8_t>(FAN_SPEED::FAN_MEDIUM):
        this->fan_speed = FAN_SPEED::FAN_MEDIUM;
        break;
    case static_cast<uint8_t>(FAN_SPEED::FAN_HIGH):
        this->fan_speed = FAN_SPEED::FAN_HIGH;
        break;
    default:
        this->fan_speed = FAN_SPEED::FAN_AUTO;
        break;
    }

    const uint8_t mode_bits = signal[6] & 0b00000111;
    switch (mode_bits)
    {
    case static_cast<uint8_t>(MODE::MODE_AUTO):
        this->mode = MODE::MODE_AUTO;
        break;
    case static_cast<uint8_t>(MODE::MODE_COOL):
        this->mode = MODE::MODE_COOL;
        break;
    case static_cast<uint8_t>(MODE::MODE_HEAT):
        this->mode = MODE::MODE_HEAT;
        break;
    case static_cast<uint8_t>(MODE::MODE_FAN):
        this->mode = MODE::MODE_FAN;
        break;
    case static_cast<uint8_t>(MODE::MODE_DRY):
        this->mode = MODE::MODE_DRY;
        break;
    default:
        this->mode = MODE::MODE_COOL;
        break;
    }

    const uint8_t sleep_bits = (signal[6] >> 3) & 0b00011111;
    this->sleep = (sleep_bits == static_cast<uint8_t>(SLEEP::SLEEP_ON)) ? SLEEP::SLEEP_ON : SLEEP::SLEEP_OFF;

    const uint8_t power_bits = signal[9] & 0b00000111;
    this->power = (power_bits == static_cast<uint8_t>(POWER::POWER_ON)) ? POWER::POWER_ON : POWER::POWER_OFF;

    this->button = static_cast<BUTTON>(signal[11]);

    this->bytes = signal;
}