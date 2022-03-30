#include "bistro.h"

void putnbr(int nbr) {
    long copy = nbr;
    if (copy < 0) {
        my_putchar('-');
        copy = -copy;
    }
    if (copy / 10 != 0) {
        putnbr((int)(copy / 10));
    }
    my_putchar((copy % 10) + '0');
}

void putnbrd(int fd, int nbr) {
    long copy = nbr;
    if (copy < 0) {
        my_putchard(fd, '-');
        copy = -copy;
    }
    if (copy / 10 != 0) {
        putnbrd(fd, (int)(copy / 10));
    }
    my_putchard(fd, (copy % 10) + '0');
}