cmake_minimum_required(VERSION 3.0.0)

SET(CMAKE_C_STANDARD 11)

# prevents adding the -dynamic flag that Linux builds use by default
set(CMAKE_SYSTEM_NAME		Generic)

set(CMAKE_SYSTEM_VERSION	1)
set(CMAKE_SYSTEM_PROCESSOR	riscv)

SET(CMAKE_CROSSCOMPILING 1)

# Nuclei NMSIS-SDK paths. See README.md
set(NUCLEI_SDK_ROOT "../nuclei-sdk")
set(NUCLEI_SDK_NMSIS "${NUCLEI_SDK_ROOT}/NMSIS")
set(NUCLEI_SDK_COMMON "${NUCLEI_SDK_ROOT}/SoC/gd32vf103/Common")
set(NUCLEI_SDK_LONGAN_BSP "${NUCLEI_SDK_ROOT}/SoC/gd32vf103/Board/gd32vf103c_longan_nano")
set(NUCLEI_SDK_DEMO_APP "${NUCLEI_SDK_ROOT}/application/baremetal/helloworld")

# required by function 'SystemBannerPrint' in nuclei-sdk/SoC/gd32vf103/Common/Source/system_gd32vf103.c
add_definitions(-DDOWNLOAD_MODE)

set(LINKER_FILE "-T../${NUCLEI_SDK_LONGAN_BSP}/Source/GCC/gcc_gd32vf103xb_flashxip.ld")

set(RISCV_STARTUP   "${NUCLEI_SDK_COMMON}/Source/GCC/startup_gd32vf103.S")
set(RISCV_INTEXC    "${NUCLEI_SDK_COMMON}/Source/GCC/intexc_gd32vf103.S")

enable_language(C)
enable_language(ASM)

set(CMAKE_C_FLAGS           "-O1 -g -fmessage-length=0 --specs=nosys.specs -march=rv32imac -mabi=ilp32 -mcmodel=medlow" CACHE INTERNAL "c compiler flags")

# "-x assembler-with-cpp prevents Error: unknown CSR `CSR_MSTATUS'"
set(CMAKE_ASM_FLAGS	        "-x assembler-with-cpp -c -O0 -Wall -fmessage-length=0 -march=rv32imac -mabi=ilp32 -mcmodel=medlow" CACHE INTERNAL "asm compiler flags")

set(CMAKE_EXE_LINKER_FLAGS  "-Wall -Wl,--no-relax -Wl,--gc-sections -nostartfiles -lc -lgcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow " CACHE INTERNAL "exe link flags")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}${LINKER_FILE}" CACHE INTERNAL "exe link flags")

include_directories(SYSTEM
    # MNSIS System Configuration Files
    "${NUCLEI_SDK_COMMON}/Include"
    # NMSIS Core
    "${NUCLEI_SDK_NMSIS}/Core/Include"
    # Longan Nano devkit BSP
    "${NUCLEI_SDK_LONGAN_BSP}/Include"
    # local app files
    "inc"
)

file(GLOB
    MAIN_SOURCE
    ${RISCV_STARTUP}
    ${RISCV_INTEXC}
    # NMSIS driver implementations
    "${NUCLEI_SDK_COMMON}/Source/Drivers/*.c"
    # MNSIS System Configuration Files
    "${NUCLEI_SDK_COMMON}/Source/*.c"
    # NMSIS libc stubs
    "${NUCLEI_SDK_COMMON}/Source/Stubs/*.c"
    # Longan Nano devkit BSP
    "${NUCLEI_SDK_LONGAN_BSP}/Source/*.c"

    ### Application Code ###

    # local app files
    "src/main.c"
    # NMSIS demo app files
    #"${NUCLEI_SDK_DEMO_APP}/main.c"
)

project(NMSIS_BLINKY VERSION 0.1.0)

# compile and link
add_executable(build.elf ${MAIN_SOURCE} )

# display size data for build
add_custom_target(size ALL riscv32-unknown-elf-size build.elf DEPENDS build.elf)

# objcopy from .bin to .hex
add_custom_target(build.bin ALL DEPENDS build.elf COMMAND riscv32-unknown-elf-objcopy -O ihex build.elf build.hex)

# flash the target
add_custom_command(TARGET build.bin POST_BUILD COMMAND /bin/sh ../cmake_scripts/flash.sh )

add_custom_command(TARGET build.elf
    PRE_BUILD
    COMMAND /bin/sh "../cmake_scripts/cleanhex.sh"
    )
