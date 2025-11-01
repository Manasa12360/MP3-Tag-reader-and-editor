#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"mp3_header.h"

void edit_mp3(char str[],char new[],char file_name[])
{
    FILE*fptr = fopen(file_name,"rb");
    if(fptr == NULL)
    {
        printf("File doesn't exists!\n");
        return;
    }
    char header[10];
    fread(header,10,1,fptr); // Copy the ID3 header (10 bytes)
    FILE *fp = fopen("temp.mp3","wb");
    if (fp == NULL)
    {
        printf("Unable to create temp file!\n");
        return;
    }
    fwrite(header,10,1,fp);
    char tag_name[5];
    // Identify which tag needs to be edited
    if(strcmp(str,"-t")== 0 )
        strcpy(tag_name,"TIT2");
    else if(strcmp(str,"-a")==0)
    {
        strcpy(tag_name,"TPE1");
    }
    else if(strcmp(str,"-A")==0)
    {
        strcpy(tag_name,"TALB");
    }
    else if(strcmp(str,"-y")==0)
    {
        if((strlen(new) != 4) || (isnumeric(new) !=4))
        {
            printf("Invalid Year\n");
            return ;
        }
        strcpy(tag_name,"TYER");
    }
    else if(strcmp(str,"-m")==0)
    {
        strcpy(tag_name,"TCON");
    }
    else if(strcmp(str,"-c")==0)
    {
        strcpy(tag_name,"COMM");
    }
    else
    {
        printf(RED"Unknown tag option: %s\n"RESET, str);
        help();
        fclose(fptr);
        fclose(fp);
        return;
    }
    tag_name[4] = '\0';
    char tag[5];
    int size = strlen(new);
    int new_size,temp_size;
    char flag[2];
    while (fread(tag, 4, 1, fptr) == 1) // Loop through all frames
    {
     
     
        if(tag[0]==0)
        {
            break;
        }
     
     tag[4] = '\0';
     fwrite(tag,4,1,fp);
     fread(&temp_size,4,1,fptr);
     fread(flag,2,1,fptr);
     convert_BE_TO_LE(&temp_size); // Convert from big-endian to little-endian
     
     char *frame_content;
     if(strcmp(tag,tag_name)==0)
     {
        
        new_size = size+1;
        convert_BE_TO_LE(&new_size);
        fwrite(&new_size,4,1,fp);
        fwrite(flag,2,1,fp);
        fputc('\0',fp);
        fwrite(new,size,1,fp);
        fseek(fptr,temp_size,SEEK_CUR);
          
     }
     else
     {
        int size2=temp_size;
        convert_BE_TO_LE(&size2);
        fwrite(&size2,4,1,fp);
        fwrite(flag,2,1,fp);
        frame_content = malloc(temp_size);
        fread(frame_content,temp_size,1,fptr);
        fwrite(frame_content,temp_size,1,fp);
        free(frame_content);
     }
     
     
    }
    // Copy the remaining (audio) part of the file
    char ch;
    while((ch=fgetc(fptr)) != EOF)
    {
        fputc(ch,fp);
    }
    fclose(fptr);
    fclose(fp);

    remove(file_name);
    rename("temp.mp3",file_name);
    char opt[10];
    strcpy(opt,tagname(tag_name));
    display_edit(opt,new);
    
}