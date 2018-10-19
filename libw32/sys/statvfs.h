#ifndef GR_STATVFS_H_INCLUDED
#define GR_STATVFS_H_INCLUDED
#include <edidentifier.h>
__CIDENT_RCSID(gr_libw32_sys_statvfs_h,"$Id: statvfs.h,v 1.5 2015/02/19 00:17:39 ayoung Exp $")
__CPRAGMA_ONCE

/* -*- mode: c; indent-width: 4; -*- */
/*
 * win32 [f]statvfs implementation
 *
 * Copyright (c) 1998 - 2015, Adam Young.
 * All rights reserved.
 *
 * This file is part of the GRIEF Editor.
 *
 * The GRIEF Editor is free software: you can redistribute it
 * and/or modify it under the terms of the GRIEF Editor License.
 *
 * The GRIEF Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License for more details.
 * ==end==
 */

/*
//  NAME
//      fstatvfs, statvfs - get file system information
//
//  SYNOPSIS
//
//      #include <sys/statvfs.h>
//
//      int fstatvfs(int fildes, struct statvfs *buf);
//      int statvfs(const char *restrict path, struct statvfs *restrict buf); [Option End]
//
//  DESCRIPTION
//
//      The fstatvfs() function shall obtain information about the file system containing
//      the file referenced by fildes.
//
//      The statvfs() function shall obtain information about the file system containing
//      the file named by path.
//
//      For both functions, the buf argument is a pointer to a statvfs structure that shall
//      be filled. Read, write, or execute permission of the named file is not required.
//
//      The following flags can be returned in the f_flag member:
//
//      ST_RDONLY
//          Read-only file system.
//      ST_NOSUID
//          Setuid/setgid bits ignored by exec.
//
//      It is unspecified whether all members of the statvfs structure have meaningful
//      values on all file systems.
//
//  RETURN VALUE
//
//      Upon successful completion, statvfs() shall return 0. Otherwise, it shall return -1
//      and set errno to indicate the error.
//
//  ERRORS
//
//      The fstatvfs() and statvfs() functions shall fail if:
//
//      [EIO]
//          An I/O error occurred while reading the file system.
//
//      [EINTR]
//          A signal was caught during execution of the function.
//
//      [EOVERFLOW]
//          One of the values to be returned cannot be represented correctly in the
//          structure pointed to by buf.
//
//      The fstatvfs() function shall fail if:
//
//      [EBADF]
//          The fildes argument is not an open file descriptor.
//
//      The statvfs() function shall fail if:
//
//      [EACCES]
//          Search permission is denied on a component of the path prefix.
//
//      [ELOOP]
//          A loop exists in symbolic links encountered during resolution of the path argument.
//
//      [ENAMETOOLONG]
//          The length of a pathname exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}.
//
//      [ENOENT]
//          A component of path does not name an existing file or path is an empty string.
//
//      [ENOTDIR]
//          A component of the path prefix of path is not a directory.
//
//      The statvfs() function may fail if:
//
//      [ELOOP]
//          More than {SYMLOOP_MAX} symbolic links were encountered during resolution of the path argument.
//
//      [ENAMETOOLONG]
//          Pathname resolution of a symbolic link produced an intermediate result whose length exceeds {PATH_MAX}.
//
*/

#include <sys/cdefs.h>

struct statvfs {
    unsigned long   f_bsize;                    /* File system block size. */
    unsigned long   f_frsize;                   /* Fundamental file system block size. */
    unsigned long   f_blocks;                   /* Total number of blocks on file system in units of f_frsize. */
    unsigned long   f_bfree;                    /* Total number of free blocks. */
    unsigned long   f_bavail;                   /* Number of free blocks available to */
                                                /* non-privileged process. */
    unsigned long   f_files;                    /* Total number of file serial numbers. */
    unsigned long   f_ffree;                    /* Total number of free file serial numbers. */
    unsigned long   f_favail;                   /* Number of file serial numbers available to */
                                                /* non-privileged process. */
    unsigned long   f_fsid;                     /* File system ID. */
    unsigned long   f_flag;                     /* Bit mask of f_flag values. */
#define ST_RDONLY   0x01                        /* read-only file system. */
#define ST_NOSUID   0x02                        /* Does not support ST_ISUID and ST_ISGID file mode bits. */

    unsigned long   f_namemax;                  /* Maximum filename length. */
};

__BEGIN_DECLS

int                 statvfs (const char *path, struct statvfs *fs);
int                 fstatvfs (int, struct statvfs *);

__END_DECLS

#endif /*GR_STATVFS_H_INCLUDED*/