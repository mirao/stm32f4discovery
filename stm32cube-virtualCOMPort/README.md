## Demo of transfer between MCU and PC connected over Micro USB connector (USB CDC, Virtual COM Port)
Inspired by https://www.youtube.com/watch?v=AYICE0gU-Sg

1. Connect your MCU to PC using Mini USB cable (needed for programming of MCU)
2. Connect your MCU to PC using Micro USB cable
3. OS should detect new devices, one for STLink and one for STM32 Virtual ComPort:
```
$ ls -ld /dev/ttyACM*
crw-rw-rw- 1 root plugdev 166, 0 Aug 31 13:57 /dev/ttyACM0
crw-rw-rw- 1 root dialout 166, 1 Aug 31 15:47 /dev/ttyACM1
```
> Tested on Ubuntu 19.04, other OS might have different devices
4. Compile and upload app to MCU: **Platform IO: Upload**
5. Open **Platform IO: Serial Monitor**, you should get this:
```
> Executing task: platformio device monitor <

--- Miniterm on /dev/ttyACM1  9600,8,N,1 ---
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
```
> If it fails, open the config file `platform.ini` and change or remove the option `monitor_port = /dev/ttyACM1`. PIO is able to detect and offer device interactively

6. In monitor window if you press any of the keys `g`, `o`, `r`, `b`, then the appropriate MCU's LED is turned on ("Green", "Orange", "Red", "Blue") and an info is logged to console
7. If you press/release push button on MCU, it's logged to console too
