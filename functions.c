#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"mp3_header.h"


void usage_menu()
{
    printf(CYAN"--------------------------------------------------------\n"RESET);
    printf("Error: ./a.out :Invalid arguments❌\n");
    printf("USAGE:\n");
    printf("To view please pass like : ./a.out -v mp3filename\n");
    printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
    printf("To get help pass like : ./a.out --help\n");
    printf(CYAN"---------------------------------------------------------\n"RESET);
}

void help()
{
    printf(CYAN"---------------HELP MENU---------------\n"RESET);
    printf("1.-v -> to view mp3 file contents\n");
    printf("2.-e -> to edit mp3 file contents\n");
    printf("\t2.1 -t -> to edit song title🎵\n");
    printf("\t2.2 -a -> to edit artist name🎤\n");
    printf("\t2.3 -A -> to edit album name💿\n");
    printf("\t2.1 -y -> to edit year📅\n");
    printf("\t2.1 -m -> to eit content📝\n");
    printf("\t2.1 -c -> to edit comment💬\n");
    printf(CYAN"---------------------------------------\n"RESET);
}
const char* tagname(char tag[])
{
    if(strcmp(tag,"TIT2")==0)
        return "Title🎵";
    if(strcmp(tag,"TPE1")==0)
        return "Artist🎤";
    if(strcmp(tag,"TALB")==0)
        return "Album💿";
    if(strcmp(tag,"TYER")==0)
        return "Year📅";
    if(strcmp(tag,"TCON")==0)
        return "Music🎶";
    if(strcmp(tag,"COMM")==0)
        return "Comments💬";
}
void convert_BE_TO_LE(int*size)
{
    char * ptr = (char*)size;
    //swapping bytes
    char temp;
    temp = ptr[0];
    ptr[0] = ptr[3];
    ptr[3] = temp;
    temp = ptr[1];
    ptr[1] = ptr[2];
    ptr[2] = temp;
}
void display_edit(char str[],char new[])
{
    printf(CYAN"-------------=====SELECTED EDIT DETAILS=====---------\n\n"RESET);
    printf("-------------------CHANGE THE %s--------------\n",str);
    printf("\n");
    printf(RED"\t\t%-10s    :   %-20s\n"RESET,str,new);  
    printf("\n");
    printf(CYAN"============%s CHANGED SUCCESSFULLY=================\n"RESET,str);
}

int isnumeric(char str[])
{
    int i=0,count=0;
    while(str[i] !='\0')
    {
        if(isdigit(str[i]) != 0)
        {
            count++; 
        }
        i++;
    }
    return count;
}