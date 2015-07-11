
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT "dict.txt"

int crack(char *);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <passwd file>\n", argv[0]);
        exit(1);
    }

    FILE *passwd = fopen(argv[1], "r");
    if (passwd == NULL) {
        printf("Failed to open %s\n", argv[1]);
        exit(1);
    }
    
    char cred[64];  // store credentials, username:password
    char *pass;     // pointer to the password part in cred
    
    while (fgets(cred, 64, passwd) != NULL) {
        /* remove trailing newline char '\n' */
        cred[strlen(cred) - 1] = '\0';
        
        pass = cred;
        while (*pass++ != ':');

        printf("cracking %s...\n", cred);
        crack(pass);
    }
    
    fclose(passwd);
}

int crack(char *pass)
{
    FILE *dict = fopen(DICT, "r");
    if (dict == NULL) {
        printf("Failed to open %s\n", DICT);
        exit(1);
    }
    
    char plain[64];
    char *cpass;
    char salt[3];
    
    while (fgets(plain, 64, dict) != NULL) {
        /* remove trailing newline char '\n' */
        plain[strlen(plain) - 1] = '\0';
        

        /* extract the salt from the encrypted password */
        strncpy(salt, pass, 2);
        salt[2] = '\0';
        
        cpass = crypt(plain, salt);
        if (strcmp(cpass, pass) == 0) {
            printf("password found - %s\n", plain);
            fclose(dict);
            return 0;
        }
    }

    fclose(dict);
    return -1;
}
