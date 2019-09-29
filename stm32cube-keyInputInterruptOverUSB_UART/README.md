## Receive characters and print them to serial console over UART

### Deployment

- Connect your MCU to PC over Mini USB connector (internal ST-LINK module is used, needed for programming of MCU)
- Connect your "USB to TTL RS232 converter" ([PL2303](https://www.aliexpress.com/item/1981712661.html)) to PC, also over Mini USB connector
- Connect the converter to MCU. Use these three wires:
    1. TX cable (green) to pin PB11 (USART3_RX)
    2. RX cable (white) to pin PD8 (USART3_TX)
    3. GND cable (black) to GND pin
> If you've already uploaded the app, feel free to disconnect ST-LINK from PC and connect the converter's fourth red cable to 5V on MCU. App should be still working.    
- OS should detect new devices, one for STLink and one for serial port:
```
$ lsusb
Bus 001 Device 009: ID 067b:2303 Prolific Technology, Inc. PL2303 Serial Port
Bus 001 Device 008: ID 0483:374b STMicroelectronics ST-LINK/V2.1
```
> Tested on Ubuntu 19.04, other OS's might have different devices
- Compile and upload app to MCU: **Platform IO: Upload**
- Open **Platform IO: Serial Monitor**, you should get this:
```
> Executing task: platformio device monitor <

--- Miniterm on /dev/ttyUSB0  115200,8,N,1 ---
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
```
> If it fails, check the config file `platform.ini` and change or remove the option `monitor_port = /dev/ttyUSB0`. PIO is able to detect and offer the right device.

> If you get an error "Device or resource busy", uninstall ModemManager: `apt remove modemmanager`

### Usage
- When you press RESET button, an initial text is displayed
- Start typing characters and they will be displayed immediately
- "Enter" key is interpreted correctly
- Copy&paste of a short string is working
    - If you paste a long string some characters might be lost

