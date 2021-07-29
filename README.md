## This is a multi-platform (Arduino-free) library version of [Philip Heron's *ax25beacon*](https://github.com/fsphil/ax25beacon) project

This simple library generates the [AFSK](https://en.wikipedia.org/wiki/Frequency-shift_keying#Audio_FSK) [baseband](https://en.wikipedia.org/wiki/Baseband)
audio tones for an [AX.25](https://en.wikipedia.org/wiki/AX.25) packet for use on the [APRS](https://en.wikipedia.org/wiki/Automatic_Packet_Reporting_System) (Automatic Packet Reporting System) network.
It encodes position, altitude and an optional comment field.

Essentially, this is what a [TNC](https://en.wikipedia.org/wiki/Terminal_node_controller) (Terminal Network Controller) is doing in hardware.

### Build the library
- All non-Windows platforms

```
cmake -S . -B build
```

- Windows (MinGW)

```
cmake -G "MinGW Makefiles" -S . -B build
```

### Build the example program (LINUX or Windows only)
```
cmake --build build -t example
```

### Run the example program
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
Linux | x86_64 | Ubuntu | :heavy_check_mark: Lib compiles & example runs
Raspberry Pi Pico | ARMv6 | none | :heavy_check_mark: Lib compiles (build env. to be provided)
Raspberry Pi 3B+, 4B | ARMv7l/ARMv8 | Raspberry Pi OS 32-bit | :heavy_check_mark: Lib compiles & example runs
Windows / MinGW | x86_64 | Windows 10 | :heavy_check_mark: Lib compiles & example runs (w/ warnings)

### TODO (Aug 2021)

- [x] Complete testing on Raspberry Pi Pico
- [x] Provide the build environment for Raspberry Pi Pico

### Acknowledgements
- I've taken something from [perplexinglysimple's pre-work](https://github.com/perplexinglysimple/ax25beacon)
- I'm using [brglng's libwav](https://github.com/brglng/libwav) for the example program
