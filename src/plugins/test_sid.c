/*
     This file is part of libextractor.
     Copyright (C) 2012 Vidyut Samanta and Christian Grothoff

     libextractor is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 3, or (at your
     option) any later version.

     libextractor is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with libextractor; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
     Boston, MA 02110-1301, USA.
*/
/**
 * @file plugins/test_sid.c
 * @brief testcase for sid plugin
 * @author Christian Grothoff
 */
#include "platform.h"
#include "test_lib.h"


/**
 * Main function for the SID testcase.
 *
 * @param argc number of arguments (ignored)
 * @param argv arguments (ignored)
 * @return 0 on success
 */
int
main (int argc, char *argv[])
{
  struct SolutionData sid_wizball_sol[] =
    {
      { 
	EXTRACTOR_METATYPE_MIMETYPE,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"audio/prs.sid",
	strlen ("audio/prs.sid") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_FORMAT_VERSION,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"2",
	strlen ("2") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_SONG_COUNT,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"9",
	strlen ("9") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_STARTING_SONG,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"4",
	strlen ("4") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_ALBUM,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"Wizball",
	strlen ("Wizball") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_ARTIST,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"Martin Galway",
	strlen ("Martin Galway") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_COPYRIGHT,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"1987 Ocean",
	strlen ("1987 Ocean") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_BROADCAST_TELEVISION_SYSTEM,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"PAL",
	strlen ("PAL") + 1,
	0 
      },
      { 
	EXTRACTOR_METATYPE_TARGET_ARCHITECTURE,
	EXTRACTOR_METAFORMAT_UTF8,
	"text/plain",
	"MOS6581",
	strlen ("MOS6581") + 1,
	0 
      },
      { 0, 0, NULL, NULL, 0, -1 }
    };
  struct ProblemSet ps[] =
    {
      { "testdata/sid_wizball.sid",
	sid_wizball_sol },
      { NULL, NULL }
    };
  return ET_main ("sid", ps);
}

/* end of test_sid.c */
