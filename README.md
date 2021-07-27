## This is a generic (Arduino-free) library version of [Philip Heron's *ax25beacon*](https://github.com/fsphil/ax25beacon) project

This simple library generates the [AFSK](https://en.wikipedia.org/wiki/Frequency-shift_keying#Audio_FSK) [baseband](https://en.wikipedia.org/wiki/Baseband)
audio tones for an [AX.25](https://en.wikipedia.org/wiki/AX.25) packet for use on the [APRS](https://en.wikipedia.org/wiki/Automatic_Packet_Reporting_System) (Automatic Packet Reporting System) network.
It encodes position, altitude and an optional comment field.

Essentially, this is what a [TNC](https://en.wikipedia.org/wiki/Terminal_node_controller) (Terminal Network Controller) is doing in hardware.

### Configure the build
```
mkdir build
cd build
cmake ..
```

### Build the library
```
make
```

### Build the example program (LINUX only)
```
make example
```

### Run the example program
```
./ax25beaconExample
```
Creates a `aprs.wav` file containing the AFSK audio tone encoding of an APRS test message.
Decoding the original message can be done using the [direwolf](https://github.com/wb2osz/direwolf) program:

```
./ax25beaconExample && cat aprs.wav | direwolf -r 48000 -
```

### Test Status

Platform | Arch | OS | Test Status
------------ | ------------ | ------------- | -------------
Linux | x86_64 | Ubuntu | Lib compiles & example runs :heavy_check_mark:
Raspberry Pi Pico | ARMv6 | none | Lib compiles (build environment to be provided) :heavy_check_mark:
Raspberry Pi 3B+ | ARMv7l / ARMv8 | Raspberry Pi OS 32-bit | Lib compiles & example runs :heavy_check_mark:
Raspberry Pi 4B | ARMv7l / ARMv8 | Raspberry Pi OS | TBD
Windows / MinGW | x86_64 | Windows 10 | Lib compiles & example runs (w/ warnings) (:heavy_check_mark:)

### TODO (Aug 2021)

- [x] Complete testing on Raspberry Pi Pico
- [x] Provide the build environment for Raspberry Pi Pico
- [x] Testing on Raspberry Pi 4B

### Acknowledgements
- I've taken something from [perplexinglysimple's pre-work](https://github.com/perplexinglysimple/ax25beacon)
- I'm using [brglng's libwav](https://github.com/brglng/libwav) for the example program