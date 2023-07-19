#include <iostream>
#include "string.h"


static size_t hashCode(char c){return (size_t) c;}
static size_t hashCode(int k){return (size_t) k;}
static size_t hashCode(long long i){return (size_t) ((i >> 32) + (int) i);}
static size_t hashCode(char s[]){
    int h = 0;
    for (size_t n = strlen(s), i = 0; i < n; i ++){
        h = (h << 5) | (h >> 27);
        h += (int) s[i];
        return (size_t) h;
    }
}