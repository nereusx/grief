#ifndef GR_RWLOCK_H_INCLUDED
#define GR_RWLOCK_H_INCLUDED
#include <edidentifier.h>
__CIDENT_RCSID(gr_libw32_sys_rwlock_h,"$Id: rwlock.h,v 1.5 2015/02/19 00:17:39 ayoung Exp $")
__CPRAGMA_ONCE

/* -*- mode: c; indent-width: 4; -*- */
/*
 * win32 <rwlock.h> implementation
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

#include <sys/cdefs.h>

typedef struct rwlock {
    unsigned int        opaque[16];
} rwlock_t;

#define RWLOCK_INITIALIZER      {0xffff}

__BEGIN_DECLS

void                    rwlock_init(struct rwlock *rw);
void                    rwlock_destroy(struct rwlock *rw);
void                    rwlock_rdlock(struct rwlock *rw);
void                    rwlock_wrlock(struct rwlock *rw);
void                    rwlock_rdunlock(struct rwlock *rw);
void                    rwlock_wrunlock(struct rwlock *rw);

__END_DECLS

#endif /*GR_RWLOCK_H_INCLUDED*/