#ifndef GR_WIN32_MISC_H_INCLUDED
#define GR_WIN32_MISC_H_INCLUDED
#include <edidentifier.h>
__CIDENT_RCSID(gr_libw32_win32_misc_h,"$Id: win32_misc.h,v 1.7 2015/02/19 00:17:34 ayoung Exp $")
__CPRAGMA_ONCE

/* -*- mode: c; indent-width: 4; -*- */
/*
 * win32 public interface.
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

#include <sys/cdefs.h>

__BEGIN_DECLS

enum w32ostype {            /* generalised machine types, ignoring server */
    OSTYPE_WIN_8,
    OSTYPE_WIN_7,
    OSTYPE_WIN_VISTA,
    OSTYPE_WIN_NT,
    OSTYPE_WIN_CE,
    OSTYPE_WIN_95
};

#define SYSDIR_TEMP         0x000001

#define WIN32_PATH_MAX      1024                /* 255, unless UNC names are used */
#define WIN32_LINK_DEPTH    8

enum w32ostype              w32_ostype(void);
int                         w32_getexedir(char *buf, int maxlen);
int                         w32_getsysdir(int id, char *buf, int maxlen);

int                         w32_regstrget(const char *subkey, const char *valuename, char *buf, int len);
int                         w32_regstrgetx(HKEY hkey, const char *subkey, const char *valuename, char *buf, int len);
const char *                w32_getlanguage(char *buffer, int len);

const char *                w32_selectfolder(const char *strMessage, char *szBuffer);

int                         w32_IsElevated(void);
int                         w32_IsAdministrator(void);

__END_DECLS

#endif /*GR_WIN32_MISC_H_INCLUDED*/