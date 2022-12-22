#include <ax25beacon.h>
#include <wav.h>

#include <stdio.h>


static void audio_callback(const void* user_data, const int16_t* sample_data, size_t num_samples, uint16_t samplerate_in_hz)
{
  printf("Number of samples  : %li\n", num_samples);
  printf("Sample rate (in Hz): %i\n", samplerate_in_hz);

  WavFile* file = wav_open("aprs.wav", WAV_OPEN_WRITE);

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
                        "SRC", "DST",      // Call signs
                        "PATH1", "PATH2",
                        10.0, 20.0, 100.0, // Lat, lon, alt (in m)
                        "CALL-SRC is testing ...",
                        '/', 'O');

  printf((err == 0) ? "Successful\n" : "Error\n");

  return err;
}
