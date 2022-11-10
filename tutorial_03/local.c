#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* bad(int n) 
{
        int res[n];

        for(int i = 0; i < n; i++) {
                res[i] = i;
        }

}

int* better(int n)
{
        int* res = malloc(n*sizeof(int));

        for(int i = 0; i < n; i++) {
                res[i] = i;
        }

        return res;
}

#define SEGFAULT_LOCAL 0
#define SEGFAULT_VLA 1

int main(int argc, char** argv)
{
        if(argc != 2) {
                printf("Use the Makefile or figure it out :p\n");
                return 0;
        }

        int* arr;
        int n;

        switch(atoi(argv[1])) {
                case 0:
                        n   = 10;
                        arr = bad(n);
                        break;
                case 1: 
                        n = INT_MAX;
                        arr = bad(n);
                        break;
                default:
                        n   = 10;
                        arr = better(n);
        }


        printf("Printing numbers from 0 to %d...\n", n);

        for(int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");

        return 0;
}
