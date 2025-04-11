#ifndef UTILS_H_
#define UTILS_H_

#define return_defer(x) \
    do {                \
        result = (x);   \
        goto defer;     \
    } while (0)

#endif UTILS_H_