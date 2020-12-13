# Baremetal RISC-V with GigaDevices GD32VF103 and Nuclei NMSIS

## Install tools

Set RISC-V GNU toolchain bin directory and Clone/build 

> export PATH=$PATH:/opt/riscv-gcc/bin

>git clone --recursive https://github.com/riscv/riscv-gnu-toolchain

>cd riscv-gnu-toolchain

>mkdir build

>cd build

>../configure --with-arch=rv32im --prefix=/opt/riscv-gcc/bin

>make

Install CMake

> sudo apt install cmake

Install Visual Code

> sudo apt install code

Download and install SEGGER *JLink Software and Documentation Pack*

https://www.segger.com/downloads/jlink/



## Project setup

Create the root directory and clone this example repo and the Nuclei NMSIS sdk repo side-by-side in the same directory.

> mkdir nmsis_blinky

> cd nmsis_blinky

> git clone https://github.com/cracked-machine/nmsis_blinky


> git clone https://github.com/Nuclei-Software/nuclei-sdk

