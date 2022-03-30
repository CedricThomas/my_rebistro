
int my_getnbr(char *str) {
    long result = 0;
    long sign = 1;

    while (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -sign;
        str++;
    }
    for (int i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
        result *= 10;
        result += str[i] - '0';
    }
    return (int)(sign * result);
}