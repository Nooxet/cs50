/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resize - resizes a BMP file with a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: %s <n> <infile> <outfile>\n", argv[0]);
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);

    if (!(n >= 1 && n <= 100))
    {
        printf("n must be in range [1, 100]\n");
        return 1;
    }

    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, nbf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    nbf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, nbi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // update header
    nbi = bi;
    nbi.biWidth = n * bi.biWidth;
    nbi.biHeight = n * bi.biHeight;

    // determine padding for scanlines
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    nbi.biSizeImage = (nbi.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(nbi.biHeight);
    nbf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nbi.biSizeImage;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // allocate a buffer for the rows
    int rowsize = nbi.biWidth * sizeof(RGBTRIPLE) + new_padding;
    BYTE *buff = calloc(rowsize, 1);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // to know where in the buffer to store next value
        int buff_idx = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < n; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                buff[buff_idx++] = triple.rgbtBlue;
                buff[buff_idx++] = triple.rgbtGreen;
                buff[buff_idx++] = triple.rgbtRed;
            }
        }

        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        // buff already has zeros at the end, from calloc
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }

        // repeat vertically n-1 times
        // since one row has already been written
        for (int k = 0; k < n - 1; k++)
        {
            fwrite(buff, rowsize, 1, outptr);
        }
    }

    // free buffer
    free(buff);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
