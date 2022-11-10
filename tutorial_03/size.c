#include <stdio.h>

struct v1 {
        char a;
        short h;
        struct v1 *o;
};

struct v2 {
        struct v2 *o;
        short h;
        char a;
};


// force struct to be packed, removing alignment padding
struct __attribute__((__packed__)) v3 {
        struct v2 *o;
        short h;
        char a;
};

typedef struct v4 {
        struct v2 *o;
        short h;
        char a;
} V4;

int main(void)
{
        // PADDING
        printf("sizeof(char): %ld, sizeof(short): %ld, sizeof(void*): %ld\n",
                        sizeof(char), sizeof(short), sizeof(void*));

        printf("sizeof(v1): %ld, sizeof(v2): %ld, sizeof(v3): %ld\n",
                        sizeof(struct v1), sizeof (struct v2), sizeof(struct v3));


        // TYPE (UN)SAFETY

        struct v2 data = {NULL, 1, 2};

        struct v2* p2 = &data;

        struct v1 data_cast = *(struct v1*) p2;

        printf("data_cast.o: %p\n", data_cast.o);


        // TYPEDEF!
        V4 nicer = {NULL, 1, 2};
        // so -Wall doesnt yell unused :)
        (void)nicer;
}
