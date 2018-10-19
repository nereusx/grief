#include <edidentifier.h>
__CIDENT_RCSID(gr_diff_hash_c,"$Id: diff_hash.c,v 1.9 2014/10/22 02:32:57 ayoung Exp $")

/* -*- mode: c; indent-width: 4; -*- */
/* $Id: diff_hash.c,v 1.9 2014/10/22 02:32:57 ayoung Exp $
 * Buffer differ
 *
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

#include <editor.h>

#include "diff.h"

#if defined(LOCAL_MAIN) && (0)
#define DD(x)           printf x
#else
#define DD(x)
#endif

static uint32_t         trim_leading(const unsigned char *text, uint32_t length);
static int              trim_trailing(const unsigned char *text, uint32_t length);


/*
 *  character translation tables:
 *      cup2low:        if folding upper to lower case.
 *      clow2low:       if not folding case.
 */
static unsigned char
clow2low[256] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
    0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41,
    0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c,
    0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62,
    0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d,
    0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83,
    0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e,
    0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
    0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
    0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba,
    0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0,
    0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb,
    0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6,
    0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1,
    0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc,
    0xfd, 0xfe, 0xff
    };


static unsigned char
cup2low[256] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
    0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x60, 0x61,
    0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,
    0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x60, 0x61, 0x62,
    0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d,
    0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83,
    0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e,
    0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
    0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
    0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba,
    0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0,
    0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb,
    0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6,
    0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1,
    0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc,
    0xfd, 0xfe, 0xff
    };


uint32_t
diff_hash(const void *data, uint32_t length, uint32_t flags)
{
    register const unsigned char *buf = data;
    uint32_t sum = 1;                           // seed

    // prelim checks
    if (NULL == buf || 0 == length)
        return sum;                             // blank line

    // suppress lfcr and trailing
    if ((flags & DIFF_SUPPRESS_LFCR) && buf[length-1] == '\r') {
        --length;
    }

    // cook stream
    if (flags == 0) {
        while (length--) {                      // native
            sum = sum * 127 + *buf++;
        }

    } else if (flags & DIFF_IGNORE_WHITESPACE) {
        const unsigned char *trans = (flags & DIFF_IGNORE_CASE ? cup2low : clow2low);

        while (length--) {
            const unsigned char c = *buf++;     // character value

            switch (c) {
            case '\r':
            case '\t':
            case '\v':
            case '\f':
            case ' ':
                continue;
            default:
                sum = sum * 127 + trans[c];     // sum
                continue;
            }
        }

    } else {    // white-space specific processing
        // leading/trailing
        if (flags & DIFF_SUPPRESS_LEADING) {
            uint32_t trim = trim_leading(buf, length);
            length -= trim, buf += trim;
        }

        if (flags & DIFF_SUPPRESS_TRAILING) {
            length = trim_trailing (buf, length);
        }

        // finally the content
        if (flags & DIFF_COMPRESS_WHITESPACE) {
            const unsigned char *trans = (flags & DIFF_IGNORE_CASE ? cup2low : clow2low);
            int space = 0;

            while (length--) {
                const unsigned char c = *buf++; // character value

                switch (c) {
            /*- case '\r': -*/
                case '\t':
                case '\v':
                case '\f':
                case ' ':
                    ++space;                    // accumlate whitespace count
                    continue;

                default:
                    if (space) {
                        sum = sum * 127 + ' ';  // replace with single space
                        space = 0;
                    }
                    sum = sum * 127 + trans[c]; // sum
                    continue;
                }
            }

        } else {    /*include white-space*/
            if (flags & DIFF_IGNORE_CASE) {
                while (length--) {              // case insensitive
                    sum = sum * 127 + cup2low[ *buf++ ];
                }

            } else {
                while (length--) {              // native
                    sum = sum * 127 + *buf++;
                }
            }
        }
    }
    return sum;

    /*
     *  There is a remote possibility that we end up with a zero sum.
     *  Zero is used as an EOF marker, so return 1 instead.
    return (sum == 0 ? 1 : sum);
     */
}


/*  Function:       trim_leading
        Trim leading white-space from the given line buffer, returning
        the character count that can be removed.

    Parameters:
	text - text buffer.
	length - Length of the buffer, in characters.

    Returns:	
	Offset within buffer which removes leading whitespace.
 */
static uint32_t
trim_leading(const unsigned char *text, uint32_t length)
{
    uint32_t trim = 0;

    while (length) {
        switch (*text++) {
        case '\t':
        case '\v':
        case '\f':
        case ' ':
            break;
        default:
            return trim;
        }
        --length;
        ++trim;
    }
    return trim;
}


/*  Function:       trim_leading
        Trim trailing white-space from the given line buffer, returning
        the result length of the trimmed line.

    Parameters:
	text - text buffer.
	length - Length of the buffer, in characters.

    Returns:
	Resulting buffer length, with trailing whitespace removed.
 */
static int
trim_trailing(const unsigned char *text, uint32_t length)
{
    const unsigned char *buf = text + (length-1);      // end of the buffer

    while (length) {
        switch (*buf--) {
        case '\t':
        case '\v':
        case '\f':
        case ' ':
            break;
        default:
            return length;
        }
        --length;
    }
    return length;
}


#if defined(LOCAL_MAIN)
int
main(void)
{
    static const char line1[] = "     Hash  this  line   \r";
#define LENGTH1         (sizeof(line1)-1)

    /* each of the following should have a different result */
    printf("%08lx\n", diff_hash(line1, LENGTH1, 0));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_IGNORE_WHITESPACE));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_IGNORE_CASE));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_COMPRESS_WHITESPACE));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_SUPPRESS_LFCR));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_SUPPRESS_LEADING ));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_SUPPRESS_LEADING|DIFF_SUPPRESS_TRAILING|DIFF_SUPPRESS_LFCR));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_SUPPRESS_LEADING|DIFF_SUPPRESS_TRAILING|DIFF_SUPPRESS_LFCR|DIFF_COMPRESS_WHITESPACE));
    printf("%08lx\n", diff_hash(line1, LENGTH1, DIFF_SUPPRESS_TRAILING|DIFF_SUPPRESS_LFCR));

    /* general */
    printf("%08lx\n", diff_hash(NULL, LENGTH1, 0));
    printf("%08lx\n", diff_hash(line1, 0, 0));

    return 0;
}
#endif  /*LOCAL_MAIN*/

/*end*/