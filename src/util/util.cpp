#include "util.h"


std::size_t pk::hash_str(const char* s) {
    std::size_t hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}


void pk::readstr(char* buffer, FILE* file) {
    int i = 0;
    char c = '0';
    while (c != '\0') {
        fread(&c, sizeof(char), 1, file);
        buffer[i++] = c;
    }
}