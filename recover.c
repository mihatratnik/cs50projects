// recover JPEG files

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // ensure a proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image_filename\n");
        return 1;
    }

    // open image file for reading
    FILE* infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 2;
    }

    // pointer to output file
    FILE* outfile;

    // jpeg blocks counter
    int jpeg_block_size = 512;
    fseek(infile, 0, SEEK_END);

    // go back to the beginning of the file
    fseek(infile, 0, SEEK_SET);

    // allocate memory for jpeg blocks
    unsigned char* buffer = malloc(jpeg_block_size * sizeof(char));

    //declare filename and counter
    char* filename = malloc(8 * sizeof(char));
    int filename_count = 0;

    // check 512 byte blocks until there are some
    while (fread(buffer, 1, jpeg_block_size, infile) == 512)
    {

        // check if the header contains jpeg header bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // close file if one is open
            if (filename_count > 0)
            {
                fclose(outfile);
            }

            // declare a new filename
            sprintf(filename, "%03i.jpg", filename_count);

            // open a new file with declared filename
            outfile = fopen(filename, "wb");
            if (outfile == NULL)
            {
                fprintf(stderr, "Could not open file %s.\n", filename);
                return 3;
            }

            // write this block to the new file
            fwrite(buffer, 1, jpeg_block_size, outfile);

            filename_count += 1;
        }

        else
        {
            if (filename_count > 0)
            {

                // write next no-header block to the file
                fwrite(buffer, 1, jpeg_block_size, outfile);
            }
        }
    }

    free(buffer);
    free(filename);

    fclose(infile);
}