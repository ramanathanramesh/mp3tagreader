#include <stdio.h>
#include "header.h"

void print_help(void)
{
    printf(BLUE"\n========== MP3 TAG READER / EDITOR ==========\n\n"RESET);

    printf(GREEN"USAGE:\n"RESET);
    printf("  ./mp3tag -v <mp3file>\n");
    printf("  ./mp3tag -e <mp3file> -t|-a|-A|-y|-g|-c \"new_value\"\n");
    printf("  ./mp3tag -h\n\n");

    printf(BLUE"OPTIONS:\n"RESET);
    printf("  -v   View MP3 tags\n");
    printf("  -e   Edit MP3 tag\n");
    printf("  -h   Show help menu\n\n");

    printf(GREEN"TAG OPTIONS:\n"RESET);
    printf("  -t   Title   (TIT2)\n");
    printf("  -a   Artist  (TPE1)\n");
    printf("  -A   Album   (TALB)\n");
    printf("  -y   Year    (TYER)\n");
    printf("  -g   Genre   (TCON)\n");
    printf("  -c   Comment (COMM)\n\n");

    printf(BLUE"EXAMPLES:\n"RESET);
    printf("  View tags:\n");
    printf("     ./a.out -v song.mp3\n\n");

    printf("  Edit title:\n");
    printf("     ./a.out -e song.mp3 -t \"New Title\"\n\n");

    printf("  Edit comment:\n");
    printf("     ./a.out -e song.mp3 -c \"Nice song\"\n\n");

    printf("============================================\n");
}
