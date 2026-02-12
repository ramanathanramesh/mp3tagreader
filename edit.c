#include <stdio.h>
#include <string.h>
#include "header.h"

/* Convert sync-safe size to integer */
int find_tag_size(unsigned char s[4])
{
    return (s[0] << 21) | (s[1] << 14) | (s[2] << 7) | s[3];
}

/* Edit selected ID3 tag */
void edit_tag(char *filename, char option, char *value)
{
    FILE *fp = fopen(filename, "rb+");        // Open MP3 file
    if (!fp)
    {
        printf(RED"File open error\n"RESET);
        return;
    }

    unsigned char header[10];
    fread(header, 1, 10, fp);                 // Read ID3 header

    if (memcmp(header, "ID3", 3) != 0)        // Check ID3 tag
    {
        printf(RED"No ID3 tag found\n"RESET);
        fclose(fp);
        return;
    }

    int tag_size = find_tag_size(&header[6]); // find the overall tag sie
    long tag_end = tag_size + 10;            // find the tag size using overall tag size + 10 header

    const char *tag_name = NULL;

    switch (option)                           // Select frame ID
    {
        case 't': tag_name = "TIT2"; break;
        case 'a': tag_name = "TPE1"; break;
        case 'A': tag_name = "TALB"; break;
        case 'y': tag_name = "TYER"; break;
        case 'g': tag_name = "TCON"; break;
        case 'c': tag_name = "COMM"; break;
    }

    while (ftell(fp) < tag_end)              // loop run up to tag_end
    {
        char id[5] = {0};
        unsigned char find_size[4];

        fread(id, 1, 4, fp);                  // Read frame ID
        fread(find_size, 1, 4, fp);          // Read frame size

        int size =
            (find_size[0] << 24) |
            (find_size[1] << 16) |
            (find_size[2] << 8)  |
             find_size[3];

        fseek(fp, 2, SEEK_CUR);               // Skip flags

        if (strcmp(id, tag_name) == 0)             // check the tag is match or not
        {
            long start = ftell(fp);

            if (option == 'c')                // Skip COMM header
            {
                fseek(fp, 4, SEEK_CUR);
                while (fgetc(fp) != '\0');
            }
            else
            {
                fseek(fp, 1, SEEK_CUR);       // Skip encoding byte
            }

            int max_len = size - (ftell(fp) - start);

            if (strlen(value) <= max_len)
            {
                fwrite(value, 1, strlen(value), fp);  // Write new data to the filee
                for (int i = strlen(value); i < max_len; i++)
                    fputc('\0', fp);           // put remaining unsed fill with NULL

                printf("%s updated successfully\n", tag_name);
            }
            else
                printf(RED"Value too long\n"RESET);

            break;
        }
        else
            fseek(fp, size, SEEK_CUR);         // Skip frame other frames 
    }

    fclose(fp);                                // Close file
}
