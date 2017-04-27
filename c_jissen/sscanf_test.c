#include <stdio.h>

// #define DEBUG

#define HOGE (3)

char    line[100];
int     value;

int main (void)
{
        printf("Enter a value. : ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &value);
        printf("value:%d\n", value);
        printf("hoge :%d\n", HOGE + HOGE);  // `cc -E sscanf_test.c` мя
#ifdef DEBUG
        printf("debug mode\n");
#else
        printf("not debug mode\n");
#endif // DEBUG
        return 0;
}

