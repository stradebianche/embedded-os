#!/bin/bash
echo 'Launching image.elf on qemu-system-aarch64 (Press Ctr+a, x to terminate):'
qemu-system-aarch64 -M virt -cpu cortex-a53 -nographic -kernel image.elf
echo 'Exit'
