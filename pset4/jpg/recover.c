/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>

#define IMAGE "card.raw"
#define BLOCK_SIZE 512

bool is_jpg(unsigned char *block)
{
    return (block[0] == 0xFF) && 
        (block[1] == 0xD8) && 
        (block[2] == 0xFF) && 
        (block[3] == 0xE0 || block[3] == 0xE1);
}

int main(int argc, char* argv[])
{
    // open disk image
    FILE *image = fopen(IMAGE, "r");
    if (image == NULL)
    {
        printf("fopen failed - %s\n", argv[1]);
        exit(1);
    }

    // a buffer to save one block at a time
    unsigned char block_buff[BLOCK_SIZE];

    // skip beginning white space
    while (fread(block_buff, BLOCK_SIZE, 1, image) == 1)
    {
        if (is_jpg(block_buff)) 
            break;
    }

    // keep track of how many pictures we find
    int counter = 0;
    char pic_name[10];

    // let the i:th picture have the name i.jpg
    sprintf(pic_name, "%03d.jpg", counter);

    FILE *pic = fopen(pic_name, "w");
    if (pic == NULL)
    {
        printf("fopen failed - %s\n", pic_name);
        exit(1);
    }

    // write the first found block to file
    if (fwrite(block_buff, BLOCK_SIZE, 1, pic) != 1)
    {
        printf("fwrite failed\n");
        exit(1);
    }

    while (fread(block_buff, BLOCK_SIZE, 1, image) == 1)
    {
        // a new jpg is found
        if (is_jpg(block_buff))
        {
            fclose(pic);
            counter++;

            sprintf(pic_name, "%03d.jpg", counter);
            pic = fopen(pic_name, "w");
        }

        fwrite(block_buff, BLOCK_SIZE, 1, pic);
    }

    // close picture
    fclose(pic);

    // close disk image
    fclose(image);
}
