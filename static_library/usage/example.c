#include "mymath.h"
#include <stdio.h>


int main(int argc, char** argv) {
    printf("%s: %d + %d = %d\n", argv[0], 3, 4, plus(3,4));
    printf("%s: %d - %d = %d\n", argv[0], 3, 4, minus(3,4));
    return 0;
}