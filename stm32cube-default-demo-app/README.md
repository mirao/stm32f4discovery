### How to flash

* Connect your STM32F4 to your PC
* Run: `st-flash write bin/demo.hex 0x8000000` # https://github.com/stlink-org/stlink
* Reconnect your STM32F4 or press Reset button (B2)
* Demo will start (LEDs should start blinking)