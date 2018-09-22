// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: f infile outfile\n");
        return 1;
    }

    // factor
    float f = atof(argv[1]);

    // ensure factor is correct
    if (f < 0.0 || f >= 100.0)
    {
        fprintf(stderr, "Usage: f must be between 0.0 and 100.0\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // define new BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER bf_new = bf;
    BITMAPINFOHEADER bi_new = bi;

    // determine new BITMAPFILEHEADER and BITMAPINFOHEADER values
    bi_new.biWidth *= f;
    bi_new.biHeight *= f;

    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_new.biSizeImage = (((sizeof(RGBTRIPLE) * bi_new.biWidth) + padding_new) * abs(bi_new.biHeight));
    bf_new.bfSize = bf_new.bfOffBits + bi_new.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    if (f >= 1)
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {

            // add outfile's scanlines
            for (float j = 0; j < f; j++)
            {

                // get to the beginning of the ith line
                fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ((bi.biWidth * sizeof(RGBTRIPLE) + padding) * i), SEEK_SET);

                // iterate over pixels in scanline
                for (int k = 0; k < bi.biWidth; k++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple from infile
                    for (int l = 0; l < f; l++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip over padding in the infile
                fseek(inptr, padding, SEEK_CUR);

                // add new padding to outfile
                for (int m = 0; m < padding_new; m++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    }

    else
    {
        // get scanline factor
        int f_lessone = 1 / f;

        // iterate over infile's scanlines by factor f_lessone
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i += f_lessone)
        {

            // get to the beginning of the ith line
            fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ((bi.biWidth * sizeof(RGBTRIPLE) + padding) * i), SEEK_SET);

            // iterate over pixels in scanline by factor f_lessone
            for (int j = 0; j < bi.biWidth; j += f_lessone)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple from infile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                // skip next f_lessone RGBTRIPLEs in infile
                fseek(inptr, sizeof(RGBTRIPLE) * (f_lessone - 1), SEEK_CUR);
            }

            // skip over padding in the infile
            fseek(inptr, padding, SEEK_CUR);

            // add new padding to outfile
            for (int m = 0; m < padding_new; m++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
