/* Copyright 2015 Philip Heron <phil@sanslogic.co.uk>                    */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <ax25.h>
#include <ax25beacon.h>

#include <stdio.h>

int ax25_beacon(void* userData, audio_callback_t callback, char* src_callsign, char* dst_callsign, char* path1,
                char* path2, double latitude, double longitude, double altitude, char* comment, char sym_table,
                char sym_code)
{
 	if (src_callsign == NULL) return -1;
	if (dst_callsign == NULL) return -1;
	if (path1 == NULL)        return -1;
	if (path2 == NULL)        return -1;
	if (callback == NULL)     return -1;

  ax25_t ax25;
  char slat[5], slng[5];
	
	ax25_init(&ax25, AX25_AFSK1200);
	
	/* Set the audio callback */
	ax25_set_audio_callback(&ax25, (void *)callback, (void *) userData);
	
	/* Warn if the sample rate doesn't divide cleanly into the bit rate */
  if (ax25.samplerate % ax25.bitrate != 0)
    printf("Warning: The sample rate %d does not divide evently into %d. The bit rate will be %.2f\n", ax25.samplerate,
           ax25.bitrate, (float)ax25.samplerate / (ax25.samplerate / ax25.bitrate));
	
	/* Convert the position to the format APRS requires */
	latitude  = ( 90.0 - latitude) * 380926;
	longitude = (180.0 + longitude) * 190463;
	altitude  = altitude * 3.2808399;

	ax25_base91enc(slat, 4, latitude);
	ax25_base91enc(slng, 4, longitude);
	
	/* Generate the audio tones and send to callback */
	return ax25_frame(
		&ax25,
		src_callsign, dst_callsign,
		path1, path2,
		"!%c%s%s%c   /A=%06.0f%s",
		sym_table, slat, slng, sym_code, altitude,
		(comment ? comment : "")
	);
}

