# LED blinking in GNU Assembly using gcc + st-flash

Ubuntu tools installation:

```bash
$ sudo apt install gcc-arm-none-eabi
$ sudo apt install stlink-tools
```

Run the commands:
```bash
$ arm-none-eabi-gcc -Wall -Wextra -o main.elf -nostdlib -mcpu=cortex-m4 -Tbasic.ld main.S
$ arm-none-eabi-objcopy -O binary main.elf main.bin
$ st-flash write main.bin 0x8000000
```
