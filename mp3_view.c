#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mp3_header.h"

void view_mp3(MP3 *tag_reader, char file_name[])
{
    FILE*fptr = fopen(file_name,"r");
    if(fptr == NULL)
    {
        printf("File doesn't exists!\n");
        return;
    }

    
        
    fread(tag_reader->id3,(sizeof(tag_reader->id3)-1),1,fptr);
    tag_reader->id3[(sizeof(tag_reader->id3)-1)]='\0';
    if(strcmp(tag_reader->id3,"ID3")!=0)
    {
        printf("It is not a mp3 file.\n");
        return;
    }
    fseek(fptr,7,SEEK_CUR);//skipping 7 bytes of header
    printf(CYAN"---------------SELECTED VIEW DETAILS---------------\n\n"RESET);
    printf(RED"---------------------------------------------------\n"RESET);
    printf(CYAN"\tMP3 TAG READER AND EDITOR FOR ID3v2🎶\t\n"RESET);
    printf(RED"---------------------------------------------------\n"RESET);
    for(int i = 0;i < 6;i++)
    {    
        fread(tag_reader->tag,(sizeof(tag_reader->tag)-1),1,fptr);
        tag_reader->tag[(sizeof(tag_reader->tag)-1)] = '\0';
        fread(&(tag_reader->size),sizeof(tag_reader->size),1,fptr);
        convert_BE_TO_LE(&(tag_reader->size)); // Convert from big-endian to little-endian
        fseek(fptr,3,SEEK_CUR);//skipping flag->2bytes,encoding byte->1byte
        char str[tag_reader->size];
        fread(str,(tag_reader->size)-1,1,fptr);
        str[(tag_reader->size)-1] = '\0';
        printf("%-14s   :%-20s\n",tagname(tag_reader->tag),str);
    }
    printf(RED"---------------------------------------------------\n"RESET);
    printf(CYAN"\tDETAILS DISPLAYED SUCCESSFULLY\t\n"RESET);
    fclose(fptr);
}
