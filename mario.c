#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get a positive number between 1 and 23
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 0 || height > 23);

    for (int rows = 0; rows < height; rows++)
    {
        // left side of the pyramide
        for (int left_space = 0; left_space < height - 1 - rows; left_space++)
        {
            printf(" ");
        }
        for (int left_hash = 0; left_hash < rows + 1; left_hash++)
        {
            printf("#");
        }

        // space between the left and the right side

        printf("  ");

        // right side of the pyramide
        for (int right_hash = 0; right_hash < rows + 1; right_hash++)
        {
            printf("#");
        }

        // break a line and go to the top for loop
        printf("\n");
    }

}