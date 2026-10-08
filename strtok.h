#ifndef LIBXSTRTOK_API_H_
#define LIBXSTRTOK_API_H_

#include <libslice/slice.h>

struct str_tokeniser {
    const char *cursor;
};

/// Initialise the cursor.
/// The input string @c input must remain valid for the duration of tokenisation.
void str_tokeniser_init(struct str_tokeniser *t, const char *input);

/// Variant of strtok(3) which does not modify the input string.
/// The separator string, @c separators, must be supplied each time, and may change between calls.
/// The returned tokens are always nonempty strings.
/// @return Slice (where @c buf is NULL when all tokens have been consumed).
struct slice str_tokeniser_next(struct str_tokeniser *t, const char *separators);

#endif
