#include <ax25beacon.h>
#include <wav.h>

#include <stdio.h>


static void audio_callback(const void* user_data, const int16_t* sample_data, size_t num_samples, uint16_t samplerate_in_hz)
{
  const char* FILE_NAME = "aprs.wav";

  printf("File '%s' has been generated.\n\n", FILE_NAME);

  printf("Number of samples       : %li\n", num_samples);
  printf("Sample rate (in Hz)     : %i\n", samplerate_in_hz);
  printf("MD5 sum has to be       : 26714d9fb09de2cab2dd220d8be61f6c - verify by 'md5sum %s'\n", FILE_NAME);
  printf("Run check by 'Dire Wolf': 'cat %s | direwolf -r %i -D 1 -'\n", FILE_NAME, samplerate_in_hz);

  WavFile* file = wav_open(FILE_NAME, WAV_OPEN_WRITE);

  wav_set_format(file, WAV_FORMAT_PCM);
  wav_set_num_channels(file, 1);
  wav_set_sample_size(file, sizeof(sample_data[0]));
  wav_set_sample_rate(file, samplerate_in_hz);
  wav_write(file, sample_data, num_samples);

  wav_close(file);
}


int main()
{
  int err = ax25_beacon(NULL,              // User data
                        audio_callback,
                        "SRC", "DST", // Call signs
                        "PATH1", "PATH2",
                        10.0, 20.0, 100.0,  // Lat, lon, alt (in m)
                        "CALLSIGN-SRC is testing ...",
                        '/', 'O');
  return err;
}
