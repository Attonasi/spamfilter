#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"


int get_files(const char* directory, char** files){

    Dirent_t* direntPtr;
    DIR* inputFilePtr = opendir(directory);

    if(inputFilePtr != NULL){
        int numberOfFiles = 0;

        while((direntPtr = readdir(inputFilePtr)) != NULL){

            if( !strcmp(direntPtr->d_name, ".") || !strcmp(direntPtr->d_name, "..")){
                // It would seem easy to not need this to get rid of .. and . It isn't.
                // This is the place to add ignore files in the if statement above
            } else {
                files[numberOfFiles] = (char*) calloc(1, sizeof(directory)+sizeof(direntPtr->d_name));
                sprintf(files[numberOfFiles++], "%s/%s", directory, direntPtr->d_name);
            }
        }
        files[numberOfFiles] = NULL;
        closedir(inputFilePtr);
        return numberOfFiles;

    }else{
        printf("\nDirectory Not Found\n");
        return 0;
    }
}

