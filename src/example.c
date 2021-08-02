#include <ax25beacon.h>
#include <wav.h>

#include <stdio.h>


static void audio_callback(const void* data, const int16_t* wav, size_t wav_len)
{
  printf("wav_len: %li\n", wav_len);

  const unsigned int sample_rate_in_hz = 48000u;

  WavFile* fp = wav_open("aprs.wav", WAV_OPEN_WRITE);

  wav_set_format(fp, WAV_FORMAT_IEEE_FLOAT);
  wav_set_sample_size(fp, sizeof(int16_t));
  wav_set_num_channels(fp, 1);
  wav_set_sample_rate(fp, sample_rate_in_hz);
  wav_write(fp, wav, wav_len);

  wav_close(fp);
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

  return 0;
}
