/*
 * We must cope with three different scenarios:
 * 1. We're using the platform's getopt(), and we should just import the
 *    appropriate declarations.
 * 2. The platform lacks getopt(), and we must declare everything.
 * 3. The platform has getopt(), but we're not using it because we don't
 *    like its behavior.  The declarations we make here must be compatible
 *    with both the platform's getopt().
 *
 * Portions Copyright (c) 1987, 1993, 1994
 * The Regents of the University of California.  All rights reserved.
 *
 * Portions Copyright (c) 2003-2024, PostgreSQL Global Development Group
 */
#ifndef APACHE_GETOPT_H
#define APACHE_GETOPT_H

/* POSIX says getopt() is provided by unistd.h */
#include <unistd.h>

/* rely on the system's getopt.h if present */
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

/*
 * If we have <getopt.h>, assume it declares these variables, else do that
 * ourselves.  (We used to just declare them unconditionally, but Cygwin
 * doesn't like that.)
 */
#ifndef HAVE_GETOPT_H

extern  char *optarg;
extern  int optind;
extern  int opterr;
extern  int optopt;

#endif							/* HAVE_GETOPT_H */


/* Provide getopt() declaration if the platform doesn't have it */
#ifndef HAVE_GETOPT
extern int	getopt(int nargc, char *const *nargv, const char *ostr);
#endif

#endif							/* APACHE_GETOPT_H */
