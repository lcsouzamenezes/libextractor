/*
     This file is part of libextractor.
     (C) 2002, 2003, 2004, 2006, 2009 Vidyut Samanta and Christian Grothoff

     libextractor is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 2, or (at your
     option) any later version.

     libextractor is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with libextractor; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.


     Some of this code is based on AVInfo 1.0 alpha 11
     (c) George Shuklin, gs]AT[shounen.ru, 2002-2004
     http://shounen.ru/soft/avinfo/

 */

#define DEBUG_EXTRACT_MP3 0

#include "platform.h"
#include "extractor.h"
#include "convert.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct
{
  char *title;
  char *artist;
  char *album;
  char *year;
  char *comment;
  const char *genre;
  unsigned int track_number;
} id3tag;

static const char *const genre_names[] = {
  gettext_noop ("Blues"),
  gettext_noop ("Classic Rock"),
  gettext_noop ("Country"),
  gettext_noop ("Dance"),
  gettext_noop ("Disco"),
  gettext_noop ("Funk"),
  gettext_noop ("Grunge"),
  gettext_noop ("Hip-Hop"),
  gettext_noop ("Jazz"),
  gettext_noop ("Metal"),
  gettext_noop ("New Age"),
  gettext_noop ("Oldies"),
  gettext_noop ("Other"),
  gettext_noop ("Pop"),
  gettext_noop ("R&B"),
  gettext_noop ("Rap"),
  gettext_noop ("Reggae"),
  gettext_noop ("Rock"),
  gettext_noop ("Techno"),
  gettext_noop ("Industrial"),
  gettext_noop ("Alternative"),
  gettext_noop ("Ska"),
  gettext_noop ("Death Metal"),
  gettext_noop ("Pranks"),
  gettext_noop ("Soundtrack"),
  gettext_noop ("Euro-Techno"),
  gettext_noop ("Ambient"),
  gettext_noop ("Trip-Hop"),
  gettext_noop ("Vocal"),
  gettext_noop ("Jazz+Funk"),
  gettext_noop ("Fusion"),
  gettext_noop ("Trance"),
  gettext_noop ("Classical"),
  gettext_noop ("Instrumental"),
  gettext_noop ("Acid"),
  gettext_noop ("House"),
  gettext_noop ("Game"),
  gettext_noop ("Sound Clip"),
  gettext_noop ("Gospel"),
  gettext_noop ("Noise"),
  gettext_noop ("Alt. Rock"),
  gettext_noop ("Bass"),
  gettext_noop ("Soul"),
  gettext_noop ("Punk"),
  gettext_noop ("Space"),
  gettext_noop ("Meditative"),
  gettext_noop ("Instrumental Pop"),
  gettext_noop ("Instrumental Rock"),
  gettext_noop ("Ethnic"),
  gettext_noop ("Gothic"),
  gettext_noop ("Darkwave"),
  gettext_noop ("Techno-Industrial"),
  gettext_noop ("Electronic"),
  gettext_noop ("Pop-Folk"),
  gettext_noop ("Eurodance"),
  gettext_noop ("Dream"),
  gettext_noop ("Southern Rock"),
  gettext_noop ("Comedy"),
  gettext_noop ("Cult"),
  gettext_noop ("Gangsta Rap"),
  gettext_noop ("Top 40"),
  gettext_noop ("Christian Rap"),
  gettext_noop ("Pop/Funk"),
  gettext_noop ("Jungle"),
  gettext_noop ("Native American"),
  gettext_noop ("Cabaret"),
  gettext_noop ("New Wave"),
  gettext_noop ("Psychedelic"),
  gettext_noop ("Rave"),
  gettext_noop ("Showtunes"),
  gettext_noop ("Trailer"),
  gettext_noop ("Lo-Fi"),
  gettext_noop ("Tribal"),
  gettext_noop ("Acid Punk"),
  gettext_noop ("Acid Jazz"),
  gettext_noop ("Polka"),
  gettext_noop ("Retro"),
  gettext_noop ("Musical"),
  gettext_noop ("Rock & Roll"),
  gettext_noop ("Hard Rock"),
  gettext_noop ("Folk"),
  gettext_noop ("Folk/Rock"),
  gettext_noop ("National Folk"),
  gettext_noop ("Swing"),
  gettext_noop ("Fast-Fusion"),
  gettext_noop ("Bebob"),
  gettext_noop ("Latin"),
  gettext_noop ("Revival"),
  gettext_noop ("Celtic"),
  gettext_noop ("Bluegrass"),
  gettext_noop ("Avantgarde"),
  gettext_noop ("Gothic Rock"),
  gettext_noop ("Progressive Rock"),
  gettext_noop ("Psychedelic Rock"),
  gettext_noop ("Symphonic Rock"),
  gettext_noop ("Slow Rock"),
  gettext_noop ("Big Band"),
  gettext_noop ("Chorus"),
  gettext_noop ("Easy Listening"),
  gettext_noop ("Acoustic"),
  gettext_noop ("Humour"),
  gettext_noop ("Speech"),
  gettext_noop ("Chanson"),
  gettext_noop ("Opera"),
  gettext_noop ("Chamber Music"),
  gettext_noop ("Sonata"),
  gettext_noop ("Symphony"),
  gettext_noop ("Booty Bass"),
  gettext_noop ("Primus"),
  gettext_noop ("Porn Groove"),
  gettext_noop ("Satire"),
  gettext_noop ("Slow Jam"),
  gettext_noop ("Club"),
  gettext_noop ("Tango"),
  gettext_noop ("Samba"),
  gettext_noop ("Folklore"),
  gettext_noop ("Ballad"),
  gettext_noop ("Power Ballad"),
  gettext_noop ("Rhythmic Soul"),
  gettext_noop ("Freestyle"),
  gettext_noop ("Duet"),
  gettext_noop ("Punk Rock"),
  gettext_noop ("Drum Solo"),
  gettext_noop ("A Cappella"),
  gettext_noop ("Euro-House"),
  gettext_noop ("Dance Hall"),
  gettext_noop ("Goa"),
  gettext_noop ("Drum & Bass"),
  gettext_noop ("Club-House"),
  gettext_noop ("Hardcore"),
  gettext_noop ("Terror"),
  gettext_noop ("Indie"),
  gettext_noop ("BritPop"),
  gettext_noop ("Negerpunk"),
  gettext_noop ("Polsk Punk"),
  gettext_noop ("Beat"),
  gettext_noop ("Christian Gangsta Rap"),
  gettext_noop ("Heavy Metal"),
  gettext_noop ("Black Metal"),
  gettext_noop ("Crossover"),
  gettext_noop ("Contemporary Christian"),
  gettext_noop ("Christian Rock"),
  gettext_noop ("Merengue"),
  gettext_noop ("Salsa"),
  gettext_noop ("Thrash Metal"),
  gettext_noop ("Anime"),
  gettext_noop ("JPop"),
  gettext_noop ("Synthpop"),
};

#define GENRE_NAME_COUNT \
    ((unsigned int)(sizeof genre_names / sizeof (const char *const)))


#define MAX_MP3_SCAN_DEEP 16768
const int max_frames_scan = 1024;
enum
{ MPEG_ERR = 0, MPEG_V1 = 1, MPEG_V2 = 2, MPEG_V25 = 3 };

enum
{ LAYER_ERR = 0, LAYER_1 = 1, LAYER_2 = 2, LAYER_3 = 3 };

#define MPA_SYNC_MASK          ((unsigned int) 0xFFE00000)
#define MPA_LAST_SYNC_BIT_MASK ((unsigned int) 0x00100000)
#define MPA_VERSION_MASK       ((unsigned int) 0x00080000)
#define MPA_LAYER_MASK         ((unsigned int) 0x3)
#define MPA_LAYER_SHIFT        17
#define MPA_BITRATE_MASK       ((unsigned int) 0xF)
#define MPA_BITRATE_SHIFT      12
#define MPA_FREQ_MASK          ((unsigned int) 0x3)
#define MPA_FREQ_SHIFT         10
#define MPA_CHMODE_MASK        ((unsigned int) 0x3)
#define MPA_CHMODE_SHIFT       6
#define MPA_PADDING_SHIFT      9
#define MPA_COPYRIGHT_SHIFT    3
#define MPA_ORIGINAL_SHIFT     2

static const unsigned int bitrate_table[16][6] = {
  {0,   0,   0,   0,   0,   0},
  {32,  32,  32,  32,  8,   8},
  {64,  48,  40,  48,  16,  16},
  {96,  56,  48,  56,  24,  24},
  {128, 64,  56,  64,  32,  32},
  {160, 80,  64,  80,  40,  40},
  {192, 96,  80,  96,  48,  48},
  {224, 112, 96,  112, 56,  56},
  {256, 128, 112, 128, 64,  64},
  {288, 160, 128, 144, 80,  80},
  {320, 192, 160, 160, 96,  96},
  {352, 224, 192, 176, 112, 112},
  {384, 256, 224, 192, 128, 128},
  {416, 320, 256, 224, 144, 144},
  {448, 384, 320, 256, 160, 160},
  {-1, -1, -1, -1, -1, -1}
};
static const int freq_table[4][3] = {
  {44100, 22050, 11025},
  {48000, 24000, 12000},
  {32000, 16000, 8000}
};
static const char * const channel_modes[4] = {
  gettext_noop("stereo"),
  gettext_noop("joint stereo"),
  gettext_noop("dual channel"),
  gettext_noop("mono")
};
static const char * const mpeg_versions[3] = {
  gettext_noop("MPEG-1"),
  gettext_noop("MPEG-2"),
  gettext_noop("MPEG-2.5")
};
static const char * const layer_names[3] = {
  gettext_noop("Layer I"),
  gettext_noop("Layer II"),
  gettext_noop("Layer III")
};


#define OK         0
#define SYSERR     1
#define INVALID_ID3 2

static void
trim (char *k)
{
  while ((strlen (k) > 0) && (isspace (k[strlen (k) - 1])))
    k[strlen (k) - 1] = '\0';
}

static int
get_id3 (const char *data, size_t size, id3tag * id3)
{
  const char *pos;

  if (size < 128)
    return INVALID_ID3;

  pos = &data[size - 128];
  if (0 != strncmp ("TAG", pos, 3))
    return INVALID_ID3;
  pos += 3;

  id3->title = EXTRACTOR_common_convert_to_utf8 (pos, 30, "ISO-8859-1");
  trim (id3->title);
  pos += 30;
  id3->artist = EXTRACTOR_common_convert_to_utf8 (pos, 30, "ISO-8859-1");
  trim (id3->artist);
  pos += 30;
  id3->album = EXTRACTOR_common_convert_to_utf8 (pos, 30, "ISO-8859-1");
  trim (id3->album);
  pos += 30;
  id3->year = EXTRACTOR_common_convert_to_utf8 (pos, 4, "ISO-8859-1");
  trim (id3->year);
  pos += 4;
  id3->comment = EXTRACTOR_common_convert_to_utf8 (pos, 30, "ISO-8859-1");
  trim (id3->comment);
  if ( (pos[28] == '\0') &&
       (pos[29] != '\0') )
    {
      /* ID3v1.1 */
      id3->track_number = pos[29];
    }
  else
    {
      id3->track_number = 0;
    }
  pos += 30;
  id3->genre = "";
  if (pos[0] < GENRE_NAME_COUNT)
    id3->genre = dgettext (PACKAGE, genre_names[(unsigned) pos[0]]);
  return OK;
}


#define ADDR(s,t) do { if (0 != proc (proc_cls, "mp3", t, EXTRACTOR_METAFORMAT_UTF8, "text/plain", s, strlen(s)+1)) return 1; } while (0)

static int
mp3parse (const unsigned char *data, size_t size,
	  EXTRACTOR_MetaDataProcessor proc,
	  void *proc_cls)
{
  unsigned int header;
  int counter = 0;
  char mpeg_ver = 0;
  char layer = 0;
  int idx_num = 0;
  int bitrate = 0;              /*used for each frame */
  int avg_bps = 0;              /*average bitrate */
  int vbr_flag = 0;
  int copyright_flag = 0;
  int original_flag = 0;
  int length = 0;
  int sample_rate = 0;
  int ch = 0;
  int frame_size;
  int frames = 0;
  size_t pos = 0;
  char format[512];

  do
    {
      /* seek for frame start */
      if (pos + sizeof (header) > size)
        {
          return 0;
        }                       /*unable to find header */
      header = (data[pos] << 24) | (data[pos+1] << 16) |
               (data[pos+2] << 8) | data[pos+3];
      if ((header & MPA_SYNC_MASK) == MPA_SYNC_MASK)
        break;                  /*found header sync */
      pos++;
      counter++;                /*next try */
    }
  while (counter < MAX_MP3_SCAN_DEEP);
  if (counter >= MAX_MP3_SCAN_DEEP)
    return 0;
  ADDR ("audio/mpeg", EXTRACTOR_METATYPE_MIMETYPE);

  do
    {                           /*ok, now we found a mp3 frame header */
      frames++;
      switch (header & (MPA_LAST_SYNC_BIT_MASK | MPA_VERSION_MASK))
        {
        case (MPA_LAST_SYNC_BIT_MASK | MPA_VERSION_MASK):
          mpeg_ver = MPEG_V1;
          break;
        case (MPA_LAST_SYNC_BIT_MASK):
          mpeg_ver = MPEG_V2;
          break;
        case 0:
          mpeg_ver = MPEG_V25;
          break;
        case (MPA_VERSION_MASK):
        default:
          mpeg_ver = MPEG_ERR;  /*error */
          break;
        }
      switch (header & (MPA_LAYER_MASK << MPA_LAYER_SHIFT))
        {
        case (0x1 << MPA_LAYER_SHIFT):
          layer = LAYER_3;
          break;
        case (0x2 << MPA_LAYER_SHIFT):
          layer = LAYER_2;
          break;
        case (0x3 << MPA_LAYER_SHIFT):
          layer = LAYER_1;
          break;
        case 0x0:
        default:
          layer = LAYER_ERR;        /*error */
        }
      if (!layer || !mpeg_ver)
        return 0;            /*unknown mpeg type */
      if (mpeg_ver < MPEG_V25)
        idx_num = (mpeg_ver - 1) * 3 + layer - 1;
      else
        idx_num = 2 + layer;
      bitrate = 1000 * bitrate_table[(header >> MPA_BITRATE_SHIFT) &
                                     MPA_BITRATE_MASK][idx_num];
      if (bitrate < 0)
        {
          frames--;
          break;
        }                       /*error in header */
      sample_rate = freq_table[(header >> MPA_FREQ_SHIFT) &
                               MPA_FREQ_MASK][mpeg_ver - 1];
      if (sample_rate < 0)
        {
          frames--;
          break;
        }                       /*error in header */
      ch = ((header >> MPA_CHMODE_SHIFT) & MPA_CHMODE_MASK);
      copyright_flag = (header >> MPA_COPYRIGHT_SHIFT) & 0x1;
      original_flag = (header >> MPA_ORIGINAL_SHIFT) & 0x1;
      frame_size =
        144 * bitrate / (sample_rate ? sample_rate : 1) +
        ((header >> MPA_PADDING_SHIFT) & 0x1);
      avg_bps += bitrate / 1000;

      pos += frame_size - 4;
      if (frames > max_frames_scan)
        break;                  /*optimization */
      if (avg_bps / frames != bitrate / 1000)
        vbr_flag = 1;
      if (pos + sizeof (header) > size)
        break;                  /* EOF */
      header = (data[pos] << 24) | (data[pos+1] << 16) |
               (data[pos+2] << 8) | data[pos+3];
    }
  while ((header & MPA_SYNC_MASK) == MPA_SYNC_MASK);

  if (!frames)
    return 0;                /*no valid frames */
  avg_bps = avg_bps / frames;
  if (max_frames_scan)
    {                           /*if not all frames scaned */
      length =
        size / (avg_bps ? avg_bps : bitrate ? bitrate : 0xFFFFFFFF) / 125;
    }
  else
    {
      length = 1152 * frames / (sample_rate ? sample_rate : 0xFFFFFFFF);
    }

  ADDR (mpeg_versions[mpeg_ver-1], EXTRACTOR_METATYPE_FORMAT_VERSION);
  snprintf (format,
	    sizeof(format),
	    "%s %s audio, %d kbps (%s), %d Hz, %s, %s, %s",
            mpeg_versions[mpeg_ver-1],
            layer_names[layer-1],
            avg_bps,
            vbr_flag ? _("VBR") : _("CBR"),
            sample_rate,
            channel_modes[ch],
            copyright_flag ? _("copyright") : _("no copyright"),
            original_flag ? _("original") : _("copy") );

  ADDR (format, EXTRACTOR_METATYPE_RESOURCE_TYPE);
  snprintf (format,
	    sizeof (format), "%dm%02d",
            length / 60, length % 60);
  ADDR (format, EXTRACTOR_METATYPE_DURATION);
  return 0;
}


#define ADD(s,t) do { if (0 != (ret = proc (proc_cls, "mp3", t, EXTRACTOR_METAFORMAT_UTF8, "text/plain", s, strlen(s)+1))) goto FINISH; } while (0)


/* mimetype = audio/mpeg */
int 
EXTRACTOR_mp3_extract (const char *data,
		       size_t size,
		       EXTRACTOR_MetaDataProcessor proc,
		       void *proc_cls,
		       const char *options)
{
  id3tag info;
  char track[16];
  int ret;

  if (0 != get_id3 (data, size, &info))
    return 0;
  if (strlen (info.title) > 0)
    ADD (info.title, EXTRACTOR_METATYPE_TITLE);
  if (strlen (info.artist) > 0)
    ADD (info.artist, EXTRACTOR_METATYPE_ARTIST);
  if (strlen (info.album) > 0)
    ADD (info.album, EXTRACTOR_METATYPE_ALBUM);
  if (strlen (info.year) > 0)
    ADD (info.year, EXTRACTOR_METATYPE_PUBLICATION_YEAR);
  if (strlen (info.genre) > 0)
    ADD (info.genre, EXTRACTOR_METATYPE_GENRE);
  if (strlen (info.comment) > 0)
    ADD (info.comment, EXTRACTOR_METATYPE_COMMENT);
  if (info.track_number != 0)
    {
      snprintf(track, 
	       sizeof(track), "%u", info.track_number);
      ADD (track, EXTRACTOR_METATYPE_TRACK_NUMBER);
    }
  ret = mp3parse ((const unsigned char *) data, size, proc, proc_cls);
FINISH:
  free (info.title);
  free (info.year);
  free (info.album);
  free (info.artist);
  free (info.comment);
  return ret; 
}

/* end of mp3_extractor.c */
