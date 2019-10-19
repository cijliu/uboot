/*
 * Copyright (c) 2019 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __HI_AUDIO_AO_H__
#define __HI_AUDIO_AO_H__

typedef enum hiAUDIO_SAMPLE_RATE_E
{
	AUDIO_SAMPLE_RATE_8000   = 8000,    /* 8K samplerate*/
	AUDIO_SAMPLE_RATE_12000  = 12000,   /* 12K samplerate*/
	AUDIO_SAMPLE_RATE_11025  = 11025,   /* 11.025K samplerate*/
	AUDIO_SAMPLE_RATE_16000  = 16000,   /* 16K samplerate*/
	AUDIO_SAMPLE_RATE_22050  = 22050,   /* 22.050K samplerate*/
	AUDIO_SAMPLE_RATE_24000  = 24000,   /* 24K samplerate*/
	AUDIO_SAMPLE_RATE_32000  = 32000,   /* 32K samplerate*/
	AUDIO_SAMPLE_RATE_44100  = 44100,   /* 44.1K samplerate*/
	AUDIO_SAMPLE_RATE_48000  = 48000,   /* 48K samplerate*/
	AUDIO_SAMPLE_RATE_BUTT,
} AUDIO_SAMPLE_RATE_E;

#endif

