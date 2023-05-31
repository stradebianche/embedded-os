# v8bsp
Boot code for ARMv8. Just to learn more about ARMv8 architecture.

## Status
  You can build image.elf file and load it into ZCU102 (or another ZynqUS+).
  Qemu not updated.

## How to build
  $ git clone https://github.com/stradebianche/v8bsp.git  
  $ cd v8bsp  
  $ source settings.sh  
  $ make  
  $ ./qemu/run.sh  

 ## TODO
  - Add arch timer, add systick interrupt
