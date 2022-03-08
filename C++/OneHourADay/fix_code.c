#include <stdio.h>
#include <stdlib.h>

int get_lines(FILE *fptr);
void clean_string(char* arr, char target, char numposttarget);
int cleanup_and_write(FILE *srcptr, FILE *targetptr, int total_lines);
int copy_and_write(FILE *srcptr, FILE *targetptr, int total_lines);

int main(int argc, char* argv[])
{
    FILE *fptr1 = NULL;
    FILE *fptr2 = NULL;
    const char temp_file[] = "temp_cleanup";
    // Argument Hendling
    if(argc==2){
        printf("Cleaning File: %s\n", argv[1]);
        fptr1 = fopen(argv[1],"r+");
        fptr2 = fopen(temp_file,"w+");
    }
    else{
        printf("\nIncorrect number of arguments.");
        printf("\nUsage ./clean_file <source_filename>");
        printf("\nProgram will now exit.");
        return -1;
    }

    // Main loop
    int total_lines = get_lines(fptr1);
    printf("File %s has %d lines.",argv[1],total_lines);
    if (cleanup_and_write(fptr1,fptr2,total_lines)==total_lines){
        // when correct temp file is generated, close current source file and reopen in write mode.
        total_lines = get_lines(fptr2);
        fclose(fptr1);
        // using w+ to truncate original file to zero length
        fptr1 = fopen(argv[1],"w+");
        
        if(copy_and_write(fptr2,fptr1,total_lines)==total_lines){
            printf("\nOperation Complete. Deleting temporary file.");
            remove(temp_file);
        }
        else{
            printf("\nFailed to complete the final operation. Check temporary file: [temp_cleanup]");
        }
    }
    else{
        printf("Failed in cleaning the file. Program terminating.");
        return -1;
    }

    fclose(fptr1);
    fclose(fptr2);

    return(0);
}

int get_lines(FILE *fptr){
    int count = 0;  
    char c;
    if (fptr == NULL)
    {
        printf("Could not open file.");
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
  
    rewind(fptr);
    return count+1;
}

void clean_string(char* arr, char target, char numposttarget){
    int i = 0 ;
    int found = -1;

    while(arr[i]!='\0'){
        if(target == arr[i]){
            found = i;
            break;
        }
        i++;
    }
    if(found!=-1){
        i=0;
        // Clean the string i.e. remove numbers and colon example: remove [14:], [100:]
        while(arr[found+i+1]!='\0'){
            // TODO replace “ character with "
            // if(arr[found+i+1]=='“'){
            //     arr[found+i+1]='"';
            // }
            arr[i] = arr[found+i+1];
            i++;
        }
        arr[i] = '\0';
        //If first character is still ' ' then left shift the array
        i=0;
        if(arr[0]==' '){
            while(arr[i+1]!='\0'){
                arr[i] = arr[i+1];
                i++;
            }
            arr[i] = '\0';
        }
    }
}

int cleanup_and_write(FILE *srcptr, FILE *targetptr, int total_lines){
    char *buffer;
    size_t bufsize = 100;
    size_t characters;
    int curr_line = 0;

    // Memory handling for program
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("\nUnable to allocate buffer");
        exit(1);
    }

    // Write in target file
    while( (characters = getline(&buffer,&bufsize,srcptr)) != -1 ){
        //printf("%s",buffer);
        printf("\nDone: %.2f",(float)100*curr_line/total_lines);
        clean_string(buffer,':',1);
        fprintf(targetptr,"%s",buffer);
        curr_line ++ ;
    }
    printf("\nDone: %.2f",(float)100*curr_line/total_lines);
    rewind(srcptr);
    rewind(targetptr);
    return curr_line;
}

int copy_and_write(FILE *srcptr, FILE *targetptr, int total_lines){
    char *buffer;
    size_t bufsize = 100;
    size_t characters;
    int curr_line = 0;

    // Memory handling for program
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("\nUnable to allocate buffer");
        exit(1);
    }

    // Write in target file
    while( (characters = getline(&buffer,&bufsize,srcptr)) != -1 ){
        //printf("%s",buffer);
        printf("\nDone: %.2f",(float)100*curr_line/total_lines);
        fprintf(targetptr,"%s",buffer);
        curr_line ++ ;
    }
    printf("\nDone: %.2f",(float)100*curr_line/total_lines);
    rewind(srcptr);
    rewind(targetptr);
    return curr_line;
}