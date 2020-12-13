# Baremetal RISC-V with GigaDevices GD32VF103 and Nuclei NMSIS

This is an blinky example for using the [Nuclei NMSIS framework](https://doc.nucleisys.com/nuclei_sdk/index.html) with [GigaDevices GD32VF103 RISC-V MCU](https://www.gigadevice.com/products/microcontrollers/gd32/risc-v/). 

RTOS support is also provided by the NMSIS framework. This repo should be used as a basic template.

It uses the CMake build tool with Visual Studio Code and the SEGGER JLink debug interface.

The RISC-V ported toolchain is built from source and it is assumed that it will be installed to **/opt/riscv-gcc/bin**

## 1. Install tools ##

#### Set RISC-V GNU toolchain bin directory and Clone/build ####

`export PATH=$PATH:/opt/riscv-gcc/bin`

`git clone --recursive https://github.com/riscv/riscv-gnu-toolchain`

`cd riscv-gnu-toolchain`

`mkdir build`

`cd build`

`../configure --with-arch=rv32im --prefix=/opt/riscv-gcc/bin`

`make`

#### Install CMake ####

`sudo apt install cmake`

#### Install Visual Code ####

`sudo apt install code`

#### Download and install SEGGER JLink Software and Documentation Pack ####

`https://www.segger.com/downloads/jlink/`


## 2. Project setup ##

Create the root directory and clone this example repo and the Nuclei NMSIS sdk repo side-by-side in the same directory.

`mkdir nmsis_blinky`

`cd nmsis_blinky`

`git clone https://github.com/cracked-machine/nmsis_blinky`


`git clone https://github.com/Nuclei-Software/nuclei-sdk`

## 3. Run the example ##

Open the workspace in visual code

Install the **C/C++**, **Cmake** and **CMake Tools** extensions.

Run **CMake: Delete Cache and Reconfigure** from command palette.

Run **CMake: Clean ReBuild** from command palette. Executable will be flashed to GD32VF103 during post-build. Manual flash script can be found in root directory.

## 4. Debug project ##

Run the SEGGER JLink GDBServer (select USB, JTAG, 4000KHz, GD32VF103CBT6)

`JLinkGDBServerExe &`

Connect to the target using RISC-V toolchain GDB

`/opt/riscv-gcc/bin/riscv32-unknown-elf-gdb`

`file ./build/build.elf`

`target remote localhost:2331`

`monitor reset`

`load`

`break main`

`continue`


