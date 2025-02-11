/*
     This file is part of libextractor.
     Copyright (C) 2004 Vidyut Samanta and Christian Grothoff

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

#ifndef CONVERT_H
#define CONVERT_H

#include "platform.h"
#include "extractor.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Convert the 'len' characters long character sequence given in
 * 'input' that is in the given 'charset' to UTF-8.
 *
 * @param input string to convert
 * @param len number of bytes in input
 * @param charset input character set
 * @return the converted string (0-terminated), NULL on error
 */
char * 
EXTRACTOR_common_convert_to_utf8 (const char * input,
				  size_t len,
				  const char *charset);

#ifdef __cplusplus
}
#endif

#endif
