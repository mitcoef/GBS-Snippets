#include <stdio.h>
#include <string.h>

// super random hex value, very safe boss!
#define ADMIN_ACESS 0x2B

const char *secret_pwd = "admin123";

int main(void) 
{
        // HUGE buffer (who has a 255 character password??)
        char password[255] = {0};

        char status = 0x00;

        // read password from user
        printf("\n\nEnter password:\n");
        gets(password);

        // compare both strings, if they are equal, set ADMIN_ACCESS
        if(!strcmp(password, secret_pwd)){
                status = ADMIN_ACESS;
        }

        // if admin access is granted, print the keycode
        if(status == ADMIN_ACESS) {
                printf("They keycode for the server-room is 420\n");
        }
        else {
                printf("Denied!\n");
        }
}
