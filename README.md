## Multi-platform (Arduino-free) library version of [Philip Heron's *ax25beacon*](https://github.com/fsphil/ax25beacon) project

This simple library generates the [AFSK](https://en.wikipedia.org/wiki/Frequency-shift_keying#Audio_FSK) [baseband](https://en.wikipedia.org/wiki/Baseband)
audio tones for an [AX.25](https://en.wikipedia.org/wiki/AX.25) packet for use on the [APRS](https://en.wikipedia.org/wiki/Automatic_Packet_Reporting_System) (Automatic Packet Reporting System) network.
It encodes position, altitude and an optional comment field.

Essentially, this is what a [TNC](https://en.wikipedia.org/wiki/Terminal_node_controller) (Terminal Network Controller) is doing in hardware.

### Build the library
- All non-Windows platforms (for Raspberry Pi Pico, see down below for a special build configuration)

```
cmake -S . -B build
cmake --build build
```

- Windows (MinGW)

```
cmake -G "MinGW Makefiles" -S . -B build
cmake --build build
```
### Run the example program (on targets w/ OS only)
```
cd build
./ax25beaconExample
```
Creates a `aprs.wav` file containing the AFSK audio tone encoding of an APRS test message.
Decoding the original message can be done using the [direwolf](https://github.com/wb2osz/direwolf) program:

```
cat aprs.wav | direwolf -r 48000 -
```
### Test Status

Platform | Arch | OS | Test Status
-------------- | ------------ | ------------- | ---------------
PC | x86_64 | Ubuntu LINUX | :heavy_check_mark: Lib compiles & example runs
PC | x86_64 | Windows 10 (MinGW) | :heavy_check_mark: Lib compiles & example runs
Raspberry Pi 3B+, 4B | ARMv7l/ARMv8 | Raspberry Pi OS 32-bit | :heavy_check_mark: Lib compiles & example runs
Raspberry Pi Pico | ARMv6 | none | :heavy_check_mark: Lib compiles

### Special build configuration for Raspberry Pi Pico

Since this is a cross-platform build for an ARM target, you can't directly use the shipped `CMakeLists.txt` file, as it would perform a host build. Instead, you'll have to integrate the build of `ax25-aprs-lib` into the cmake configuration of your own Pico application in a manner like this:

```
cmake_minimum_required(VERSION 3.15)

# Copy this file from $PICO_SDK_PATH/pico-sdk/external
include(pico_sdk_import.cmake)

project(__YOUR_PROJECT_NAME_HERE__ VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Setup of eleccoder's 'ax25-aprs-lib'

include(FetchContent)
FetchContent_Declare(ax25_aprs_lib
    GIT_REPOSITORY    "https://github.com/eleccoder/ax25-aprs-lib.git" 
    GIT_SHALLOW       ON
)

FetchContent_MakeAvailable(ax25_aprs_lib)

# Setup of the application

set(EXE_NAME __YOUR_EXECUTABLE_NAME_HERE__)

add_executable(${EXE_NAME}
    src/file.c
)

target_include_directories(${EXE_NAME} PRIVATE
    include
)

# Set the console interface
pico_enable_stdio_usb(aprs_pico 1)    # USB
# pico_enable_stdio_uart(aprs_pico 1) # UART

# create map/bin/hex file etc.
pico_add_extra_outputs(${EXE_NAME})

target_link_libraries(${EXE_NAME}
    pico_stdlib
    ax25_aprs_lib::ax25beacon
)
```
### Acknowledgements

- I've taken something from [perplexinglysimple's pre-work](https://github.com/perplexinglysimple/ax25beacon)
- I'm using [brglng's libwav](https://github.com/brglng/libwav) for the example program
