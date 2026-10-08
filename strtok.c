#include "strtok.h"

#include <errno.h>
#include <string.h>

void str_tokeniser_init(struct str_tokeniser *t, const char *input)
{
    if (!t) {
        return;
    }

    t->cursor = input;
}

struct slice str_tokeniser_next(struct str_tokeniser *t, const char *separators)
{
    struct slice slice = { NULL, 0 };

    if (!t || !t->cursor) {
        return slice;
    }

    if (!separators) {
        /* Default. */
        separators = "";
    }

    /* Find start of token. */
    while (*t->cursor && strchr(separators, *t->cursor)) {
        t->cursor++;
    }

    if (*t->cursor) {
        const char *end = t->cursor;

        /* Find end of token. */
        while (*end && !strchr(separators, *end)) {
            end++;
        }

        slice = slice_from_range(t->cursor, end);

        if (*end) {
            /* Skip delimiter.
             * Must be done here, since delimiter string could change on next call. */
            end++;
        }

        t->cursor = end;
    }

    return slice;
}
