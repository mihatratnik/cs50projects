#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // condition to run
    if (argc == 2)
    {
        // print input hash
        const char *user_input = argv[1];

        // create an array of alhpabet letters
        const char alphabet[53] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

        // create salt
        char salt[3];
        salt[0] = user_input[0];
        salt[1] = user_input[1];
        salt[2] = '\0';

        // decifre input hash
        char password[6];

        for (int i = 0; i < strlen(alphabet); i++) //for 5 letter passwords
        {
            if (i > 0)
            {
                password[5] = '\0';
                password[4] = alphabet[i];
            }

            for (int j = 0; j < strlen(alphabet); j++) //for 4 letter passwords
            {
                if (i == 0)
                {
                    password[4] = '\0';
                }

                password[3] = alphabet[j];

                for (int k = 0; k < strlen(alphabet); k++) // for 3 letter password
                {
                    if (j == 0)
                    {
                        password[3] = '\0';
                    }

                    password[2] = alphabet[k];

                    for (int l = 0; l < strlen(alphabet); l++) // for 2 letter password
                    {
                        if (k == 0)
                        {
                            password[2] = '\0';
                        }

                        password[1] = alphabet[l];

                        for (int m = 0; m < strlen(alphabet); m++) // for 1 letter password
                        {
                            if (l == 0)
                            {
                                password[1] = '\0';
                            }

                            password[0] = alphabet[m];

                            if (strcmp(crypt(password, salt), argv[1]) == 0)
                            {
                                printf("%s\n", password);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    // no or too many arguments
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}