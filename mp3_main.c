/*
Name: Manasa S
Date: 28/10/2025
Description: MP3 TAG READER AND EDITOR FOR ID3v2
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mp3_header.h"

int main(int argc,char *argv[])
{
    MP3 tag_reader;
    if(argc==1) //checking if only one argument is present 
    {
        usage_menu();
        return 0;
    }
    if(strcmp(argv[1],"--help")==0)
    {
        help();
        return 0;
    }

    if(strcmp(argv[1],"-v")== 0)
    {
        if(argc > 3)
        {
            printf("Error: Extra CLA passed\n");
            return 0;
        }
        else if(argc < 3)
        {
            printf("Error : No CLA passed\n");
            return 0;
        }
        if(strcmp(argv[2],".")==0)
        {
            printf("Only extension found\n");
            return 0;
        }
        char *ret = strstr(argv[2],".mp3");
        if(ret == NULL)
        {
            printf("No extension found\n");
            return 0;
        }
        else
        {
            if(strcmp(ret,".mp3")!=0)
            {
                printf("Its not a mp3 file.\n");
                return 0;
            }
        }
    }
    else if(strcmp(argv[1],"-e")== 0)
    {
        if(argc > 5)
        {
            printf("Error: Extra CLA passed\n");
            return 0;
        }
        else if(argc < 5)
        {
            printf("Error : No CLA passed\n");
            return 0;
        }
        if(strcmp(argv[4],".")==0)
        {
            printf("Only extension found\n");
            return 0;
        }
        char *ret = strstr(argv[4],".mp3");
        if(ret == NULL)
        {
            printf("No extension found\n");
            return 0;
        }
        else
        {
            if(strcmp(ret,".mp3")!=0)
            {
                printf("Its not a mp3 file.\n");
                return 0;
            }
        }
    }
    else
    {
        usage_menu();
        return 0;
    }
    
    if(strcmp(argv[1],"-v") == 0)
    {
        view_mp3(&tag_reader,argv[2]); //to view file
    }
    else if(strcmp(argv[1],"-e") == 0)
    {
        edit_mp3(argv[2],argv[3],argv[4]); //to edit file
    }
}