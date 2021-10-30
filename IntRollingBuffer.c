#include <stdio.h>
#include <stdlib.h>

void dumpInts(int *array, int count, int hex);

void dumpInts(int *array, int count, int hex)
{
    int i;
    for (i = 0; i < count; i++) {
        // 0xdeadbeef  0x00000001  0x00000003  0x00000003  0x00000004  0xc0d4f00d
        if (i > 0)
            printf(" ");
        if (hex == 0) {
            printf("%11d", array[i]);
        } else {
            printf(" 0x%08x", array[i]);
        }
    }
    printf("\n");
}

void insertInt(int *array, int count, int n)
{
    int i;
    if (count < 2) return;
    array[1] = n;
    for (i = 1; i < count-2; i++) {
        if (n > array[i + 1]) {
            array[i] = array[i+1];
            array[i+1] = n;
        } else {
            break;
        }
    }
    printf("\n");
    dumpInts(array, count, 0);
    dumpInts(array, count, 1);
}

int main() {
    int *array = NULL;
    int n = 0;
    int ret;
    int i;
    int c;
    int last = 0;
    int v;
    ret = scanf("%d", &n);
    if (ret == 0) {
        fprintf(stderr, "ERROR: Cannot read the buffer length.\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "ERROR: len is less than 1.\n");
        return 1;
    }
    array = (int *)malloc(sizeof(int) * (n + 2));
    if (array == NULL) {
        fprintf(stderr, "ERROR: malloc error.\n");
        return 1;
    }
    array[0] = 0xdeadbeef;
    array[n+1] = 0xc0d4f00d;
    for (i = 1; i <= n; i++) {
        array[i] = i;
    }
    dumpInts(array, n + 2, 0);
    dumpInts(array, n + 2, 1);
    while (1) {
        c = getchar();
        if (c == EOF) break;
        // get input integer
        if (c >= '0' && c <= '9') {
            if (last) {
                if (v < 0) {
                    v = v * 10 - (c - '0');
                } else {
                    v = v * 10 + c - '0';
                }
            } else {
                v = c - '0';
                last = 1;
            }
        } else if (c == '+') {
            // processing +
            if (last) {
                insertInt(array, n + 2, v);
                last = 0;
            }
            c = getchar();
            if (c >= '0' && c <= '9') {
                v = c - '0';
                last = 1;
            } else {
                fprintf(stderr, "\nOOPS: Non-integer input!  0x%x='%c'\n", '+', '+');
            }
        } else if (c == '-') {
            // processing -
            if (last) {
                insertInt(array, n + 2, v);
                last = 0;
            }
            c = getchar();
            if (c >= '0' && c <= '9') {
                v = c - '0';
                v *= -1;
                last = 1;
            } else {
                fprintf(stderr, "\nOOPS: Non-integer input!  0x%x='%c'\n", '+', '+');
            }
        } else if (c == '\n' || c == ' ') {
            // end processing one integer
            if (last) {
                insertInt(array, n + 2, v);
                last = 0;
            }
        }
        else {
            if (last) {
                insertInt(array, n + 2, v);
                last = 0;
            }
            fprintf(stderr, "\nOOPS: Non-integer input!  0x%x='%c'\n", c, c);
        }
    }
    return 0;
}
