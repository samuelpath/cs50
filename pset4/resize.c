/*
  TODO: now handle resize factors inferior to 1
*/

// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // retrieve f (resize factor)
    // TODO, use sscanf? https://reference.cs50.net/stdio/sscanf
    // use get_float? (maybe for corner cases)
    float f = atof(argv[1]);

    if (f == 0 || f > 100)
    {
        fprintf(stderr, "f must be a floating-point value in (0.0, 100.0]\n");
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
    BITMAPFILEHEADER bfIn;
    fread(&bfIn, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER biIn;
    fread(&biIn, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bfIn.bfType != 0x4d42 || bfIn.bfOffBits != 54 || biIn.biSize != 40 ||
        biIn.biBitCount != 24 || biIn.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create copies of bi and bf for outfile
    BITMAPFILEHEADER bfOut;
    BITMAPINFOHEADER biOut;
    memcpy(&bfOut, &bfIn, sizeof(BITMAPFILEHEADER));
    memcpy(&biOut, &biIn, sizeof(BITMAPINFOHEADER));

    biOut.biWidth = biIn.biWidth * f;
    biOut.biHeight = biIn.biHeight * f;

    int paddingIn = (4 - (biIn.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOut = (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    biOut.biSizeImage = ((sizeof(RGBTRIPLE) * biOut.biWidth) + paddingOut) * abs(biOut.biHeight);
    bfOut.bfSize = biOut.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biIn.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE usefulLine[biOut.biWidth];

        // iterate over pixels in original scanline to generate usefulLine
        for (int j = 0; j < biIn.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // copy each pixel as many times as f
            for (int l = 0; l < f; l++)
            {
                int idx = j*f + l;
                usefulLine[idx] = triple;
            }
        }

        // copy each line from original as many times as f
        for (int m = 0; m < f; m++)
        {
            fwrite(&usefulLine, biOut.biWidth * sizeof(RGBTRIPLE), 1, outptr);
            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
