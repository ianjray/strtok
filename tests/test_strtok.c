#include "strtok.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_stdlib(void)
{
    const char *input = ",,;,aaa;;bbb,";
    char *copy;
    struct str_tokeniser t;

    copy = strdup(input);
    assert(!strcmp(strtok(copy, ","), ";"));
    assert(!strcmp(strtok(NULL, ";,"), "aaa"));
    assert(!strcmp(strtok(NULL, ";,"), "bbb"));
    assert(NULL == strtok(NULL, ";,"));
    assert(NULL == strtok(NULL, ";,"));
    free(copy);

    str_tokeniser_init(&t, input);
    assert(slice_equal(str_tokeniser_next(&t, ","), slice_from_string(";")));
    assert(slice_equal(str_tokeniser_next(&t, ";,"), slice_from_string("aaa")));
    assert(slice_equal(str_tokeniser_next(&t, ";,"), slice_from_string("bbb")));
    assert(slice_equal(str_tokeniser_next(&t, ";,"), slice_make(NULL, 0)));
    assert(slice_equal(str_tokeniser_next(&t, ";,"), slice_make(NULL, 0)));
}

static void test_null(void)
{
    struct str_tokeniser t;

    /* Nothing to do. */
    str_tokeniser_init(NULL, NULL);

    /* No input. */
    str_tokeniser_init(&t, NULL);
    assert(NULL == t.cursor);
    assert(slice_equal(str_tokeniser_next(&t, NULL), slice_make(NULL, 0)));

    /* Empty input. */
    str_tokeniser_init(&t, "");
    assert(NULL != t.cursor);
    assert(slice_equal(str_tokeniser_next(&t, NULL), slice_make(NULL, 0)));

    /* No separators. */
    str_tokeniser_init(&t, "a:b:c");
    assert(slice_equal(str_tokeniser_next(&t, NULL), slice_from_string("a:b:c")));
}

static void test_interleaved(void)
{
    const char *input = "a:b,c:d";
    struct str_tokeniser t1;
    struct str_tokeniser t2;

    str_tokeniser_init(&t1, input);
    str_tokeniser_init(&t2, input);

    assert(slice_equal(str_tokeniser_next(&t1, ","), slice_from_string("a:b")));
    assert(slice_equal(str_tokeniser_next(&t2, ":"), slice_from_string("a")));

    assert(slice_equal(str_tokeniser_next(&t1, ","), slice_from_string("c:d")));
    assert(slice_equal(str_tokeniser_next(&t2, ":"), slice_from_string("b,c")));

    assert(slice_equal(str_tokeniser_next(&t1, ","), slice_make(NULL, 0)));
    assert(slice_equal(str_tokeniser_next(&t2, ":"), slice_from_string("d")));

    assert(slice_equal(str_tokeniser_next(&t2, ":"), slice_make(NULL, 0)));
}

int main(void)
{
    test_stdlib();
    test_null();
    test_interleaved();
}
