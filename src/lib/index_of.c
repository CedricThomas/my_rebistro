
int index_of(char needle, const char *haystack) {
    for (int i = 0; haystack[i]; i++) {
        if (needle == haystack[i])
            return i;
    }
    return -1;
}