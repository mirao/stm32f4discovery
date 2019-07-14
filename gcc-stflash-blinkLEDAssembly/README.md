# LED blinking in GNU Assembly using gcc + st-flash

Ubuntu tools installation:

```bash
$ sudo apt install gcc-arm-none-eabi
$ sudo apt install stlink-tools
$ sudo apt install gdb-multiarch # For debugging only
```

Run the commands:
```bash
$ arm-none-eabi-gcc -Wall -Wextra -o main.elf -nostdlib -mcpu=cortex-m4 -Tbasic.ld main.S
$ arm-none-eabi-objcopy -O binary main.elf main.bin
$ st-flash write main.bin 0x8000000
```

### Debugging:

Server
```bash
$ st-util # Run gdb server 
```
Client
```bash
$ arm-none-eabi-gcc -g -Wall -Wextra -o main.elf -nostdlib -mcpu=cortex-m4 -Tbasic.ld main.S # -g produces debugging info
$ gdb-multiarch main.elf 
```

```
(gdb) tar ext :4242
(gdb) load
(gdb) ...
(gdb) continue
```
