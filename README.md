## This is a generic (Arduino-free) library version of [Philip Heron's *ax25beacon*](https://github.com/fsphil/ax25beacon) project

This simple library generates the [AFSK](https://en.wikipedia.org/wiki/Frequency-shift_keying#Audio_FSK) (Automatic Packet Reporting System) [baseband](https://en.wikipedia.org/wiki/Baseband)
audio tones for an [AX.25](https://en.wikipedia.org/wiki/AX.25) packet for use on the [APRS](https://en.wikipedia.org/wiki/Automatic_Packet_Reporting_System) network.
It encodes position, altitude and an optional comment field.

### Build
```
mkdir build
cd build
cmake ..
make
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

Platform | Arch | Test Status
------------ | ------------ | -------------
Ubuntu Linux | x86_64 | Compiles & Runs
Raspberry Pi Pico | ARMv6 | Lib Compiles (build environment to be provided)
Raspberry Pi 3B+ & 4B | ARMv7l / ARMv8 | TBD

### TODO (Aug 2021)

- [x] Complete testing on Raspberry Pi Pico
- [x] Provide the build environment for Raspberry Pi Pico
- [x] Testing on Raspberry Pi 3B+ and 4B

### Acknowledgements
I've also taken some of [perplexinglysimple's pre-work](https://github.com/perplexinglysimple/ax25beacon).