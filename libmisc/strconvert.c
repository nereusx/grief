#include <edidentifier.h>
__CIDENT_RCSID(gr_strconvert_c,"$Id: strconvert.c,v 1.6 2015/02/19 00:17:14 ayoung Exp $")

/* -*- mode: c; indent-width: 4; -*- */
/* $Id: strconvert.c,v 1.6 2015/02/19 00:17:14 ayoung Exp $
 * libstr - String convert utility functions.
 *
 *
 * Copyright (c) 1998 - 2015, Adam Young.
 * All rights reserved.
 *
 * This file is part of the GRIEF Editor.
 *
 * The GRIEF Editor is free software: you can redistribute it
 * and/or modify it under the terms of the GRIEF Editor License.
 *
 * Redistributions of source code must retain the above copyright
 * notice, and must be distributed with the license document above.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, and must include the license document above in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * The GRIEF Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License for more details.
 * ==end==
 */

#include <config.h>
#include <editor.h>
#include <edtypes.h>
#include <assert.h>

#if defined(HAVE_STRVERSCMP)
#define  _GNU_SOURCE
#include <string.h>                             /* strverscmp() */
#endif
#include <stdarg.h>

#include <libstr.h>
#include <unistd.h>


/*  Function:           str_rev
 *      Reverse the order of the characters in the string, pointed to by 's'.
 *
 *  Parameters:
 *      p - Address of the source string.
 *
 *  Returns:
 *      The str_rev routine returns the original string 'p'.
 */
char *
str_rev(char *p)
{
    register char *l = p, *r = p;
    char ch;

    r += (strlen(p) - 1);
    while (r > l) {
        ch = *r;
        *r = *l;
        *l = ch;
        --r; ++l;
    }
    return p;
}


/*  Function:           str_upper
 *      Converts characters contained within the string to uppercase.
 *
 *  Parameters:
 *      p - Address of the source string.
 *
 *   Returns:
 *      The str_rev routine returns the original string 'p'.
 */
char *
str_upper(char *p)
{
    register char *s = p;

    while (*s) {
        *s = toupper(*s);
        ++s;
    }
    return p;
}


/*  Function:           str_lower
 *      Converts to characters contained within the string to lowercase.
 *
 *  Parameters:
 *      p - Address of the source string.
 *
 *   Returns:
 *      The str_rev routine returns the original string 'p'.
 */
char *
str_lower(char *p)
{
    register char *s = p;

    while (*s) {
        *s = tolower(*s);
        ++s;
    }
    return p;
}

/*end*/