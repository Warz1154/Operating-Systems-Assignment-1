#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000
#define MAX_LINES 100

//1 - cat file reads and prints the content of the file
//2 - cat > file writes in the file and overwrite
//3 - cat > file file > file1 append two contents of the files and writes it in file1
//4 - cat file1 > file2 write content of file1 in file2 (overwrites)
//5 - cat < file1 > file2 write content of file 1 into file2 (overwrites)
//6 - cat >> file writes the file

//4 5 are the same,


//1 - cat file reads and prints the content of the file
void read(char arr[])
{
    char ch;
    FILE* fptr;
    fptr = fopen(arr, "r");

    if(fptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }

    while(1)
    {
        ch = fgetc(fptr);
        if(ch == EOF) break;

        printf("%c", ch);
    }
    fclose(fptr);

}

//2 - cat > file writes in the file and doesnt overwrite
void write(char arr[])
{
    FILE* fptr;
    fptr = fopen(arr, "w");

    if(fptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }

    char inp[200];
    
    scanf(" %[^\n]", inp);
    
    fprintf(fptr, "%s", inp);
    fclose(fptr);
}

//3 - cat > file file > file1 append two contents of the files and writes it in file1
void conc_nfile(char loc[], char loc1[], char loc2[])
{   
    FILE *fptr, *fptr1, *nfptr;
    

    fptr = fopen(loc, "r");
    fptr1 = fopen(loc1, "r");
    nfptr = fopen(loc2, "w");

    if(fptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }
    else if (fptr1 == NULL)
    {
       
        perror("mycat: No such file or directory");
        return;
    }
    else if(nfptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }

    char data[MAX_LINES][MAX_LEN];

    int line = 0;

    if(fptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }
    else if (fptr1 == NULL)
    {
       
        perror("mycat: No such file or directory");
        return;
    }
    else if (nfptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }
    
    
    

    while(!feof(fptr))
    {
        if(fgets(data[line], MAX_LEN, fptr) != NULL) line++;
    }
    
    
    while(!feof(fptr1))
    {
        if(fgets(data[line], MAX_LEN, fptr1) != NULL) line ++;
    }

    for(int i = 0; i < line; i++)
    {
        fprintf(nfptr, "%s", data[i]);
    }
    
    fclose(nfptr);
    fclose(fptr);
    fclose(fptr1);
}

//4 - cat file1 > file2 write content of file1 in file2
//5 - cat < file1 > file2 write content of file 1 into file2

void read_write(char loc[],char loc1[])
{
    FILE *fptr, *fptr1;
    char data[MAX_LINES][MAX_LEN];
    int line = 0;

    fptr = fopen(loc, "r");
    fptr1 = fopen(loc1, "w");

    if(fptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }
    else if (fptr1 == NULL)
    {
       
        perror("mycat: No such file or directory");
        return;
    }

    while(!feof(fptr))
    {
        if(fgets(data[line], MAX_LEN, fptr) != NULL) line++;
    }

    for(int i = 0; i < line; i++)
    {
        fprintf(fptr1, "%s", data[i]);
    }

    fclose(fptr);
    fclose(fptr1);
}
//6 - cat >> file
void append(char loc[])
{
    FILE *fptr;
    char inpt[100];

    fptr = fopen(loc, "a");

    if(fptr == NULL)
    {
        perror("mycat: No such file or directory");
        return;
    }
    
    scanf(" %[^\n]", inpt);

    fprintf(fptr, "%s", inpt);

    fclose(fptr);
}

int main()
{
    char ch;
    char inpt[100];
    char inpt1[100];
    char dest[100];
    char loc[100] = "/home/abdelrahman/nu_courses/Assignment1/";
    char loc1[100] = "/home/abdelrahman/nu_courses/Assignment1/";
    char loc2[100] = "/home/abdelrahman/nu_courses/Assignment1/";
    

    scanf(" %[^\n]", inpt);
    
    char * pc;

    pc = strtok(inpt, " ");
    int counter = 0;
    int word_size = 0;

    char *words[20];
    while(pc != NULL)
    {
        
        words[counter++] = pc;
        word_size ++;
        
        pc = strtok(NULL, " ");
    }

    //check if the array doesn't contain any "<" ">"
    int flag = 1;

    for(int i = 0; i < word_size; i++)
    {
        char *word = words[i];
        for(int j = 0; word[j] != '\0'; j++)
        {
            if(word[j] == '>' || word[j] == '<')
            {
                flag = 0;
                break;
            }
        }
    }
    
    //specify which command

    //cat filename
    if(word_size == 1)
    {
        read(strcat(loc, words[0]));
    }
    //cat > filename
    else if (word_size == 2 && (strcmp(words[0], ">") == 0))
    {
        write(strcat(loc, words[1]));
    }
    //cat > filename filename > filename
    else if(word_size == 5 && (strcmp(words[0], ">") == 0) && strcmp(words[3], ">") == 0)
    {
        conc_nfile(strcat(loc, words[1]), strcat(loc1, words[2]), strcat(loc2, words[4]));
    }
    //cat file1 > file2 && cat < file1 > fil2 
    else if((word_size == 3 && strcmp(words[1], ">") == 0) || (word_size == 4 && strcmp(words[0], "<") == 0 && strcmp(words[2], ">") == 0))
    {
        if(word_size == 3)
        {
            read_write(strcat(loc, words[0]), strcat(loc1, words[2]));
        }
        else
        {
            read_write(strcat(loc, words[1]), strcat(loc1, words[3]));
        }

    }
    //cat >> file
    else if(word_size == 2 && strcmp(words[0], ">>") == 0)
    {
        append(strcat(loc, words[1]));
    }
    
    // cat filename filename filename
    else if(flag)
    {
        for(int i = 0; i < word_size; i++)
        {
            read(strcat(loc, words[i]));
            strcpy(loc, "/home/abdelrahman/nu_courses/Assignment1/");
        }
    }
    
    else
    {
        printf("Wrong command!\n");
    }
    
    
    
    

    // for(int i =0; i < 5; i++)
    // {
    //     if(i == 0 && words[i] != NULL && !strcmp(words[i], "<") && strcmp(words[i], ">")){
    //         strcat(loc, words[i]);
    //     }
    //     else if(i == 1 && words[i] != NULL && !strcmp(words[i], "<") && strcmp(words[i], ">"))
    //     {
    //         strcat(loc1, words[i]);
    //     }
    //     else if(i == 2 && words[i] != NULL && !strcmp(words[i], "<") && strcmp(words[i], ">"))
    //     {
    //         strcat(loc2, words[i]);
    //     }

        
    // }
    
    // int word_size = sizeof(words)/sizeof(char);

    // printf("size = %d\n", word_size);
    
    //concatentation
    // int loc_size = (sizeof(loc)/sizeof(loc[0]));
    // int arr_size = (sizeof(arr)/sizeof(arr[0]));

    // char* file1 = malloc(300* sizeof(char));
    // memcpy(file1, loc, loc_size * sizeof(char));
    // memcpy(file1 + loc_size, arr,  arr_size* sizeof(char));


    // strcat(loc, inpt);
    // strcat(loc1, inpt1);
    // strcat(loc2, dest);

    // fptr = fopen(loc, "r");

    // if(fptr == NULL)
    // {
    //     printf("Wrong file name!");
    // }
    // else
    // {
        // printf("%s %s %s \n", loc, loc1,loc2);
        // conc_nfile(loc, loc1, loc2);
        // write(loc);
    // }

    
}

