/*
 * Private image library definitions for CUPS.
 *
 * Copyright © 2007-2019 by Apple Inc.
 * Copyright © 1993-2006 by Easy Software Products.
 *
 * Licensed under Apache License v2.0.  See the file "LICENSE" for more
 * information.
 */

#ifndef _CUPS_RASTER_PRIVATE_H_
#  define _CUPS_RASTER_PRIVATE_H_

/*
 * Include necessary headers...
 */

#  include <cups/raster.h>
#  include "debug-private.h"
#  include "string-private.h"
#  ifdef _WIN32
#    include <io.h>
#    include <winsock2.h>		/* for htonl() definition */
#  else
#    include <unistd.h>
#    include <fcntl.h>
#  endif /* _WIN32 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Structure...
 */

struct _cups_raster_s			/**** Raster stream data ****/
{
  unsigned		sync;		/* Sync word from start of stream */
  void			*ctx;		/* File descriptor */
  cups_raster_iocb_t	iocb;		/* IO callback */
  cups_mode_t		mode;		/* Read/write mode */
  cups_page_header2_t	header;		/* Raster header for current page */
  unsigned		rowheight,	/* Row height in lines */
			count,		/* Current row run-length count */
			remaining,	/* Remaining rows in page image */
			bpp;		/* Bytes per pixel/color */
  unsigned char		*pixels,	/* Pixels for current row */
			*pend,		/* End of pixel buffer */
			*pcurrent;	/* Current byte in pixel buffer */
  int			compressed,	/* Non-zero if data is compressed */
			swapped;	/* Non-zero if data is byte-swapped */
  unsigned char		*buffer,	/* Read/write buffer */
			*bufptr,	/* Current (read) position in buffer */
			*bufend;	/* End of current (read) buffer */
  size_t		bufsize;	/* Buffer size */
#  ifdef DEBUG
  size_t		iostart,	/* Start of read/write buffer */
			iocount;	/* Number of bytes read/written */
#  endif /* DEBUG */
  unsigned		apple_page_count;/* Apple raster page count */
};


#if 0
/*
 * min/max macros...
 */

#  ifndef max
#    define 	max(a,b)	((a) > (b) ? (a) : (b))
#  endif /* !max */
#  ifndef min
#    define 	min(a,b)	((a) < (b) ? (a) : (b))
#  endif /* !min */
#endif // 0


/*
 * Prototypes...
 */

extern void		_cupsRasterAddError(const char *f, ...) _CUPS_FORMAT(1,2) _CUPS_PRIVATE;
extern void		_cupsRasterClearError(void) _CUPS_PRIVATE;
extern const char	*_cupsRasterErrorString(void) _CUPS_PRIVATE;

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_RASTER_PRIVATE_H_ */
