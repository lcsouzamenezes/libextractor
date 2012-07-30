/*
     This file is part of libextractor.
     (C) 2012 Vidyut Samanta and Christian Grothoff

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
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
 */
/**
 * @file main/extractor_logging.h
 * @brief logging API for GNU libextractor
 * @author Christian Grothoff
 */
#ifndef EXTRACTOR_LOGGING_H
#define EXTRACTOR_LOGGING_H

#define DEBUG 1

#if DEBUG

/**
 * Log function.
 *
 * @param file name of file with the error
 * @param line line number with the error
 * @param ... log message and arguments
 */
void
EXTRACTOR_log_ (const char *file, int line, const char *format, ...);

/**
 * Log a message.
 *
 * @param fmt format string
 * @param ... arguments for fmt (printf-style)
 */
#define LOG(fmt, ...) EXTRACTOR_log_ (__FILE__, __LINE__, fmt, __VA_ARGS__)
#else
#define LOG(...)
#endif


/**
 * Abort the program reporting an assertion failure
 *
 * @param file filename with the failure
 * @param line line number with the failure
 */
void
EXTRACTOR_abort_ (const char *file,
		  int line);

/**
 * Abort program if assertion fails.
 *
 * @param cond assertion that must hold.
 */
#define ASSERT(cond) do { if (! (cond)) EXTRACTOR_abort_ (__FILE__, __LINE__); } while (0)


#endif
