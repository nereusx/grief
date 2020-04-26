#include <edidentifier.h>
__CIDENT_RCSID(cr_splookup_c,"$Id: splookup.c,v 1.14 2020/04/11 20:01:27 cvsuser Exp $")

/* -*- mode: c; indent-width: 4; -*- */
/* $Id: splookup.c,v 1.14 2020/04/11 20:01:27 cvsuser Exp $
 * libsplay version 2.0 - SPLAY tree implementation.
 *
 *
 * Copyright (c) 1998 - 2020, Adam Young.
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

#include "spheaders.h"


/*  Function:           splookup
 *      Given key, find a node in a tree. Splays the found node to the root.
 *
 *  Parameters:
 *      key - search key.
 *      tree - splay tree reference.
 *
 *  Returns:
 *      Address of element.
 */
SPBLK *
splookup(void const * key, SPTREE * tree)
{
    _sproot *root = &tree->sp_root;
    SPBLK elm;

    SP_INCR(splookup);
    SPI_INCR(tree->lookups);

    elm.key = (void *)key;
    return SPLAY_FIND(libsplay, root, &elm);
}
