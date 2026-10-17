# ESPHome External Components
This repository contains my custom [ESPHome](https://esphome.io) electra ac remote [external component](https://esphome.io/components/external_components.html).

A custom [ESPHome](https://esphome.io) external component for controlling Electra air conditioners via an infrared (IR) transmitter and receiver.

## Requirements
* Generic ESP32 or ESP8266 microcontroller
* IR transmitter wired to the ESP
* IR receiver wired to the ESP (optional, for state tracking)

## Installation & Usage
You can add this component directly to your configuration using ESPHome's [ESPHome external components feature](https://esphome.io/components/external_components.html).


### 1. Import the Component
Add the following to your ESPHome configuration file to pull the component from this repository:
```yaml
external_components:
  - source:
      type: git
      url: https://github.com/WazWazMan/EsphomeElectraRemote
    components: [ climate_ir_electra ]
```

### 2. Configure the Hardware & Climate Platform
Define your IR transmitter, receiver, and the climate entity. Make sure to adjust the pin values to match your specific board wiring:
```yaml
climate:
  - platform: climate_ir_electra
    name: "AC"
    receiver_id: rec_1

remote_transmitter:
  pin: GPIO21 # Change this to the actual pin your IR LED is connected to
  carrier_duty_percent: 50%

remote_receiver:
  id: rec_1
  pin:
    number: GPIO4
    inverted: true
    mode:
      input: true
      pullup: true
  dump: all
  receive_symbols: 256
```

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! 

Feel free to check the [issues page](https://github.com/WazWazMan/EsphomeElectraRemote/issues). If you want to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.