#ifndef HEADER_H
#define HEADER_H

#define RESET   "\033[0m"
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

void view_tag(char *filename);
void edit_tag(char *filename, char option, char *value);
void print_help(void);

int find_tag_size(unsigned char s[4]);

#endif
