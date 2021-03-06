/*
 * Private threading definitions for libppd.
 *
 * Copyright 2009-2017 by Apple Inc.
 *
 * Licensed under Apache License v2.0.  See the file "LICENSE" for more information.
 */

#ifndef _CUPS_THREAD_PRIVATE_H_
#  define _CUPS_THREAD_PRIVATE_H_

/*
 * Include necessary headers...
 */

#  include "config.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


#  ifdef HAVE_PTHREAD_H			/* POSIX threading */
#    include <pthread.h>
typedef pthread_mutex_t _cups_mutex_t;
typedef pthread_key_t	_cups_threadkey_t;
#    define _CUPS_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER
#    define _CUPS_THREADKEY_INITIALIZER 0
#    define _cupsThreadGetData(k) pthread_getspecific(k)
#    define _cupsThreadSetData(k,p) pthread_setspecific(k,p)

#  elif defined(_WIN32)			/* Windows threading */
#    include <winsock2.h>
#    include <windows.h>
typedef struct _cups_mutex_s
{
  int			m_init;		/* Flag for on-demand initialization */
  CRITICAL_SECTION	m_criticalSection;
					/* Win32 Critical Section */
} _cups_mutex_t;
typedef DWORD	_cups_threadkey_t;
#    define _CUPS_MUTEX_INITIALIZER { 0, 0 }
#    define _CUPS_THREADKEY_INITIALIZER 0
#    define _cupsThreadGetData(k) TlsGetValue(k)
#    define _cupsThreadSetData(k,p) TlsSetValue(k,p)

#  else					/* No threading */
typedef char	_cups_mutex_t;
typedef void	*_cups_threadkey_t;
#    define _CUPS_MUTEX_INITIALIZER 0
#    define _CUPS_THREADKEY_INITIALIZER (void *)0
#    define _cupsThreadGetData(k) k
#    define _cupsThreadSetData(k,p) k=p
#  endif /* HAVE_PTHREAD_H */


/*
 * Functions...
 */

extern void	_cupsMutexInit(_cups_mutex_t *mutex) _CUPS_PRIVATE;
extern void	_cupsMutexLock(_cups_mutex_t *mutex) _CUPS_PRIVATE;
extern void	_cupsMutexUnlock(_cups_mutex_t *mutex) _CUPS_PRIVATE;

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_THREAD_PRIVATE_H_ */
