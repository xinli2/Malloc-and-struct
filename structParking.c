#include "proj04.h"
#include <stdio.h>

int value;

int fillOneFoo(Foo* p)
{
    int ret;
    ret = scanf("%d%d%d%c%c", &p->arr[0], &p->arr[1], &p->arr[2], &p->c1, &p->c2);
    return ret;
}

void printInts(int *p, int count)
{
    for (int i = 0; i < count; ++i) {
        printf("0x%08x", *(unsigned int*)(p+i));
        if (i == count - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}

void printOneBar(Bar* p)
{
//Bar:  x: 0x00000001=1  y: 0x00000002=2  z: 0x00000003=3  c1: 0x78  c2: 0x79
    printf("Bar:  x: 0x%08x=%d  y: 0x%08x=%d  z: 0x%08x=%d  c1: 0x%02x  c2: 0x%02x\n",
           p->x, p->x, p->y, p->y, p->z, p->z, p->c1, p->c2);
}

void printOneBaz(Baz* p)
{
//Baz:  x: 0x00000001=1  c1: 0x02  y: 0x00000003=3  c2: 0x78  z: 0x0000000a=10
    printf("Baz:  x: 0x%08x=%d  c1: 0x%02x  y: 0x%08x=%d  c2: 0x%02x  z: 0x%08x=%d\n",
           p->x, p->x, p->c1, p->y, p->y, p->c2, p->z, p->z);
}

int main(void)
{
    struct Foo array[4];
    int i;
    int j;
    int n;
    unsigned char *p;
    int ret;
    scanf("%d", &n);
    for (i = 0; i < 4; i++) {
        p = (unsigned char*)(&array[i]);
        for (j = 0; j < (int)sizeof(Foo); j++) {
            *(p+j) = n;
        }
    }
    for (i = 0; i < 4; i++) {
        ret = fillOneFoo(&array[i]);
        if (ret != 5) {
            fprintf(stderr, "ERROR: fillOneFoo(): Could not read the required input; rc=0\n");
            return 1;
        }
    }

    // Printing Sizes
    printf("sizeof(Foo)=%ld\n", sizeof(Foo));
    printf("sizeof(Bar)=%ld\n", sizeof(Bar));
    printf("sizeof(Baz)=%ld\n", sizeof(Baz));

    printf("\n");

    // Printing Raw Data
    printInts((int*)array, (int)(sizeof(array) / sizeof(int)));

    printf("\n");

    // Printing Bar,Baz
    p = (unsigned char*)array;
    for(i = 0; i < 2; i++) {
        printOneBar((Bar*)(p+sizeof(Bar)*i));
    }
    printf("\n");

    for(i = 0; i < 2; i++) {
        printOneBaz((Baz*)(p+sizeof(Baz)*i));
    }
//    printf("\n");

    return 0;
}
