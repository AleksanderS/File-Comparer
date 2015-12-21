#include <stdio.h>
#include <stdlib.h>

void insertFileNamesMatrix(char ***matrix, int numberOfFiles, char ** fileNames){
    int i = 1;
    while(i<=numberOfFiles){
        matrix[0][i] = fileNames[i-1];
        matrix[i][0] = fileNames[i-1];
    }

}

