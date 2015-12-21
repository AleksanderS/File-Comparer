#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

void listFiles();
void fileOneInsertHash(HashP , char **, int, int);
int fileTwoCompare(HashP , char ** , int, int );

int createFileArray(char **);

void listFiles(){

    system("ls ./datafiles/ > inputfile.txt");
    return;
}

void fileOneInsertHash(HashP myHash, char ** fileList, int phraseLength, int numberOfFiles){
    char buffer[50000];
    char fileOneName[500];
    strcpy(fileOneName, "./datafiles/");
    strcat(fileOneName, fileList[numberOfFiles-1]);
    FILE* firstFile = fopen(fileOneName, "r");

    fread(buffer, 1, 50000, firstFile);

    //whole file is now stored in buffer string. must tokenize it and put in hash.
    int i;
    char *stringToHash = malloc(sizeof(char)*5000);
    char *token = malloc(sizeof(char)*5000);
    char * search = " ";
    token = strtok(buffer, search);

    strcpy(stringToHash, token);
    strcat(stringToHash, " ");


        for(i = 1; i<phraseLength;i++){
               token = strtok(NULL, search);
               strcat(stringToHash, token);
               strcat(stringToHash, " ");
        }
        insertHash(myHash, stringToHash);
        char *findFirstSpace = &stringToHash[0];
        while( *findFirstSpace != ' '){
            findFirstSpace++;
        }
        findFirstSpace++;
        strcpy(stringToHash, findFirstSpace);

        while(token != NULL){
            findFirstSpace = &stringToHash[0];
            token = strtok(NULL, search);
            if(token == NULL) break;
            strcat(stringToHash, token);
            strcat(stringToHash, " ");

            insertHash(myHash, stringToHash);

            while( *findFirstSpace != ' '){
                findFirstSpace++;
            }
        findFirstSpace++;
        strcpy(stringToHash, findFirstSpace);

        }
        free(token);
        free(stringToHash);

}

int fileTwoCompare(HashP my_hash, char ** fileList, int phraseLength, int numberOfFiles){
    char buffer[50000];
    char fileOneName[500];
    strcpy(fileOneName, "./datafiles/");
    strcat(fileOneName, fileList[numberOfFiles-1]);
    FILE* firstFile = fopen(fileOneName, "r");

    fread(buffer, 1, 50000, firstFile);

    //whole file is now stored in buffer string. must tokenize it and put in hash.
    int i;

    int matchCount = 0;
    char stringToHash[5000];
    char *token = malloc(sizeof(char)*5000);
    char * search = " ";
    token = strtok(buffer, search);

    strcpy(stringToHash, token);
    strcat(stringToHash, " ");


        for(i = 1; i<phraseLength;i++){
               token = strtok(NULL, search);
               strcat(stringToHash, token);
               strcat(stringToHash, " ");
        }


        if (lookupHash(my_hash, stringToHash) == 1){
            matchCount++;
        }

        char *findFirstSpace = &stringToHash[0];
        while( *findFirstSpace != ' '){
            findFirstSpace++;
        }
        findFirstSpace++;
        strcpy(stringToHash, findFirstSpace);

        while(token != NULL){
            findFirstSpace = &stringToHash[0];
            for(i = 1; i<=1; i++){
                token = strtok(NULL, search);
                if(token == NULL) break;
                strcat(stringToHash, token);
                strcat(stringToHash, " ");

                if (lookupHash(my_hash, stringToHash) == 1){
                     matchCount++;
                 }
            }
            if(token == NULL) break;

            while( *findFirstSpace != ' '){
            findFirstSpace++;
        }
        findFirstSpace++;
        strcpy(stringToHash, findFirstSpace);

        }
        free(token);
        return matchCount;
}






int createFileArray(char ** fileArray){
    int i;
    for (i = 0; i<30; i++){
        fileArray[i] = NULL;
    }
    listFiles();
    FILE* file = fopen("inputfile.txt", "r");
    i = 0;
    char currentFile[500];
    while(fscanf(file, "%s", currentFile) == 1 ){


        fileArray[i] = malloc(sizeof(char)*200);
        strcpy(fileArray[i], currentFile);

        i++;
    }
    fclose(file);

    return i;
}




