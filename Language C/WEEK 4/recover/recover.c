#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 1. Validate command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // 2. Open the input memory card file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // 3. Set up the 512-byte raw data buffer
    uint8_t buffer[512];

    // 4. Initialize persistent tracking variables (OUTSIDE the loop)
    int image_count = 0;
    FILE *img = NULL;
    char filename[8];

    // 5. Read the memory card block by block
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if this block marks the beginning of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a previous JPEG is currently open, close it first
            if (img != NULL)
            {
                fclose(img);
            }

            // Generate a fresh filename formatted to 3 digits (e.g., "000.jpg")
            sprintf(filename, "%03i.jpg", image_count);

            // Open the new image file for writing data
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(card);
                printf("Could not create output file %s.\n", filename);
                return 1;
            }

            // Increment our image counter for the next JPEG found
            image_count++;
        }

        // If a JPEG file is actively open, write the current 512-byte block to it
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // 6. Clean up remaining open files after reaching the end of the card
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);

    return 0;
}
