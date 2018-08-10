#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    // check arguments
    if (argc == 2 && argv > 0)
    {
        int key = atoi(argv[1]);

        // ask user for plaintext input
        string user_input = get_string("plaintext: ");

        //get individual chars for user input
        char ciphertext[100];
        char alpha_user_chars;
        for (int user_chars = 0; user_chars < strlen(user_input); user_chars++)
        {
            // check if alphabet character
            if (isalpha(user_input[user_chars]))
            {

                //check if upper and apply cipher
                if (isupper(user_input[user_chars]))
                {
                    alpha_user_chars = (((user_input[user_chars] - 65) + key) % 26) + 65;

                }

                //check if lower and apply cipher
                else if (islower(user_input[user_chars]))
                {
                    alpha_user_chars = (((user_input[user_chars] - 97) + key) % 26) + 97;
                }
            }
            //check if non-alpha and copy to alpha_user_chars
            else
            {
                alpha_user_chars = user_input[user_chars];
            }
            ciphertext[user_chars] = alpha_user_chars;
        }
        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        // return error if user does not add argument in the command line
        eprintf("Usage: ./ceasar {key}\n");
        return 1;
    }
}