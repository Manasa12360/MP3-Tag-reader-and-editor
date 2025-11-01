
#define HEADER_H
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

typedef struct 
{
    char id3[4];
    char tag[5];
    int size;
}MP3;
void usage_menu(void);
void view_mp3(MP3 *tag_reader,char file_name[]);
const char* tagname(char tag[]);
void convert_BE_TO_LE(int *size);
void edit_mp3(char str[],char new[],char file_name[]);
void display_edit(char str[],char new[]);
void help(void);
int isnumeric(char str[]);
