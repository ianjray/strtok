# strtok
String tokeniser

A variant of [strtok(3)](https://man7.org/linux/man-pages/man3/strtok.3.html) which addresses weaknesses in the standard library function:

* Does not modify the first argument.
* Can be used on constant strings.

## Example

```c
#include <libtok/strtok.h>
#include <stdio.h>

int main(void)
{
    struct str_tokeniser t;
    struct slice r;

    str_tokeniser_init(&t, ":a:bc::def:");

    while ((r = str_tokeniser_next(&t, ":")).buf) {
        printf("%*.*s\n", (int)r.len, (int)r.len, r.buf);
    }

    return 0;
}
``` 
