#include <stdio.h>
#include <string.h>
#include "header.h"

/* Display ID3 tag values */
void view_tag(char *file)
{
    FILE *fp = fopen(file, "rb");          // Open MP3 file
    if (!fp)
    {
        printf(RED"File open error\n"RESET);
        return;
    }

    unsigned char header[10];
    fread(header, 1, 10, fp);              // Read ID3 header

    if (memcmp(header, "ID3", 3) != 0)     // Verify ID3 tag
    {
        printf("No ID3 tag found\n");
        fclose(fp);
        return;
    }

    int tag_size = find_tag_size(&header[6]); // Get tag size
    long tag_end = tag_size + 10;

    printf(YELLOW"------------------------------------\n");
    printf("      Detial of the mp3 song\n");
    printf("------------------------------------\n"RESET);
    while (ftell(fp) < tag_end)            // Traverse frames
    {
        char id[5] = {0};
        unsigned char size_bytes[4];

        if (fread(id, 1, 4, fp) != 4)      // Read frame ID
            break;

        fread(size_bytes, 1, 4, fp);       // Read frame size

        int size =
            (size_bytes[0] << 24) |
            (size_bytes[1] << 16) |
            (size_bytes[2] << 8)  |
            size_bytes[3];

        fseek(fp, 2, SEEK_CUR);            // Skip flags

        if (!strncmp(id, "TIT2", 4) || !strncmp(id, "TPE1", 4) ||
            !strncmp(id, "TALB", 4) || !strncmp(id, "TYER", 4) ||
            !strncmp(id, "TCON", 4))
        {
            fseek(fp, 1, SEEK_CUR);        // Skip encoding byte
            char data[256] = {0};
            fread(data, 1, size - 1, fp);  // Read text data

            
            if (!strncmp(id, "TIT2", 4)) printf("Title   : %s\n", data);
            if (!strncmp(id, "TPE1", 4)) printf("Artist  : %s\n", data);
            if (!strncmp(id, "TALB", 4)) printf("Album   : %s\n", data);
            if (!strncmp(id, "TYER", 4)) printf("Year    : %s\n", data);
            if (!strncmp(id, "TCON", 4)) printf("Genre   : %s\n", data);
        }
        else if (!strncmp(id, "COMM", 4))
        {
            char ch;
            fseek(fp, 4, SEEK_CUR);        // Skip COMM header
            while ((ch = fgetc(fp)) != '\0');
            char comment[256] = {0};
            fread(comment, 1, size, fp);   // Read comment
            printf("Comment : %s\n", comment);
        }
        else
        {
            fseek(fp, size, SEEK_CUR);     // Skip unknown frame
        }
    }

    fclose(fp);                            // Close file
}
