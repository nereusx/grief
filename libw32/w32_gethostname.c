#include <edidentifier.h>
__CIDENT_RCSID(gr_w32_gethostname_c,"$Id: w32_gethostname.c,v 1.7 2015/02/19 00:17:28 ayoung Exp $")

/* -*- mode: c; indent-width: 4; -*- */
/*
 * win32 gethostname
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
 *
 * Notice: Portions of this text are reprinted and reproduced in electronic form. from
 * IEEE Portable Operating System Interface (POSIX), for reference only. Copyright (C)
 * 2001-2003 by the Institute of. Electrical and Electronics Engineers, Inc and The Open
 * Group. Copyright remains with the authors and the original Standard can be obtained
 * online at http://www.opengroup.org/unix/online.html.
 * ==extra==
 */

#include "win32_internal.h"
#include <unistd.h>

/*
//  NAME
//      gethostname - get name of current host
//
//  SYNOPSIS
//      #include <unistd.h>
//
//      int gethostname(char *name, size_t namelen);
//
//  DESCRIPTION
//      The  gethostname() function shall return the standard host name for the
//      current machine. The namelen argument shall specify  the  size  of  the
//      array  pointed  to  by  the  name argument.  The returned name shall be
//      null-terminated, except that if namelen is an  insufficient  length  to
//      hold the host name, then the returned name shall be truncated and it is
//      unspecified whether the returned name is null-terminated.
//
//      Host names are limited to {HOST_NAME_MAX} bytes.
//
//  RETURN VALUE
//      Upon successful completion, 0 shall be returned; otherwise, -1 shall be
//      returned.
//
//  ERRORS
//      No errors are defined.
//
//      The following sections are informative.
*/
int
w32_gethostname(char *name, size_t namelen)
{
    const char *host;

#undef gethostname
    if (0 == gethostname(name, namelen)) {
        return 0;
    }

#if (TODO)
    char buffer[MAX_COMPUTERNAME_LENGTH+1] = {0};
    DWORD dwSize = sizeof(buffer);

    if (GetComputerNameEx((COMPUTER_NAME_FORMAT)cnf, buffer, &dwSize)) {
    }
#endif

    host = getenv("COMPUTERNAME");
    if (NULL == host) host = "pccomputer";
    strncpy(name, (const char *)host, namelen);
    return 0;
}