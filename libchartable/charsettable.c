#include <edidentifier.h>
__CIDENT_RCSID(gr_charsettable_c,"$Id: charsettable.c,v 1.9 2015/02/19 00:17:04 ayoung Exp $")

/* -*- mode: c; indent-width: 4; -*- */
/* conversion tables.
 *
 *
 * Copyright (c) 2012 - 2015, Adam Young.
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

#include <edtypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "./charsetdesc.h"
#include "libchartable.h"


static __CINLINE const void *
charsetdesc(uint32_t ch)
{
    uint32_t first = 0,
        last = (sizeof(x_charsetdesc_lookup)/sizeof(x_charsetdesc_lookup[0])) - 1;
 
    while (first <= last) {
        const uint32_t middle = (first + last) / 2;
        const struct charsetdesc *desc = x_charsetdesc_lookup + middle;
        uint32_t base = desc->base;

        if (ch >= base) {
            if (ch <= (base + desc->count)) {
                return x_charsetdesc_characters[ desc->offset + (ch - base) ];
            }
            first = middle + 1;

        } else {
            last  = middle - 1;
        }
    }
    return NULL;
}


static __CINLINE const void *
utf8_decode(const void *src, int32_t *result)
{
    register const unsigned char *t_src = (const unsigned char *)src;
    unsigned char ch;
    int32_t ret = 0;
    int remain;

    ch = *t_src++;
    if (ch & 0x80) {

        if ((ch & 0xE0) == 0xC0) {              
            remain = 1;
            ret = ch & 0x1F;

        } else if ((ch & 0xF0) == 0xE0) {       
            remain = 2;
            ret = ch & 0x0F;

        } else if ((ch & 0xF8) == 0xF0) {       
            remain = 3;
            ret = ch & 0x07;

        } else if ((ch & 0xFC) == 0xF8) {       
            remain = 4;
            ret = ch & 0x03;

        } else if ((ch & 0xFE) == 0xFC) {       
            remain = 5;
            ret = ch & 0x01;

        } else {                                
            ret = -ch;
            goto done;
        }

        while (remain--) {
            ch = *t_src++;
            if (0x80 != (0xc0 & ch)) {          
                --t_src;
                ret = -ret;
                goto done;
            }
            ret <<= 6;
            ret |= (ch & 0x3f);
        }

    } else {
        ret = ch;
    }

done:;
    *result = ret;
    return (const void *)t_src;
}


const char *
charset_description(int32_t ch, char *buffer, int buflen)
{
    if (ch >= 0) {
        const unsigned char *desc = charsetdesc((uint32_t)ch);

        if (desc) {
            char *cursor = buffer,
                *end = cursor + (buflen - 1);
            unsigned char dc;

            while (0 != (dc = *desc) && (cursor < end)) {
                if (dc >= 0x60) {               /* word reference, UFT8 encoded character */

                    desc = utf8_decode(desc, &ch);

                    if ((ch -= 0x60) >= 0 &&
                            ch < (sizeof(x_charsetdesc_words)/sizeof(x_charsetdesc_words[0]))) {

                        const char *word = x_charsetdesc_words[ch];

                        while (0 != (dc = *word++) && (cursor < end)) {
                            *cursor++ = dc;
                        }

                        if (*desc && cursor < end) {
                            *cursor++ = ' ';    /* implied spacing */
                        }

                    } else {
                        assert(0);
                    }

                } else {
                    *cursor++ = dc;             /* character literal */
                    ++desc;
                }
            }

            *cursor = 0;
            return buffer;
        }
    }
    *buffer = 0;
    return NULL;
}


#if defined(LOCAL_MAIN)
//
//  test framework
//
#include <stdio.h>

void
main(void)
{
    char buffer[64];
    int32_t ch;

    for (ch = 0; ch < 0xe1000; ++ch) {
        const char *desc =
            charset_description(ch, buffer, sizeof(buffer));

        if (desc) {
            printf("%6d/0x%05x \"%s\"\n", ch, ch, buffer);
        }
    }
}
#endif  /*LOCAL_MAIN*/
/*end*/