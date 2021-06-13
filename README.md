# v8bsp
Boot code for ARMv8. Just to learn more about ARMv8 architecture.

## How to build
<code>
  $ git clone https://github.com/stradebianche/v8bsp.git
  $ cd v8bsp
  $ source settings.sh
  $ make
  $ ./qemu/run.sh
 </code>

 ## TODO
  - Add translation table entry for Zynq US+ UART
  - Add drivers for Zynq US+ UART