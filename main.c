/*
 * File:   main.c
 * Author: Alex
 *
 * Created on September 7, 2015, 8:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"
#include <string.h>

/*
 *
 */
int main() {
    HashP my_hash = newHash();

    int phraseLength = 0;

    while(phraseLength > 10 || phraseLength < 2){
      fprintf(stderr, "What is the number of words to analyze(2-10)?");
      scanf("%i", &phraseLength);
    }

    char **fileNames = malloc(sizeof(char *)*30);
    int numberOfFiles = createFileArray(fileNames);
    char *matrix[numberOfFiles + 1][numberOfFiles + 1];
    int i,j;
    for(i = 0; i<=numberOfFiles; i++)
        for(j = 0; j<=numberOfFiles ; j++)
            matrix[i][j] = NULL;
    i = 1;
    while(i<=numberOfFiles){
        char *fName = malloc(sizeof(char)*5);
        snprintf(fName, 5, "f%d", i);
        matrix[0][i] = fName;
        matrix[i][0] = fName;
        i++;

    }





        int a, b;
        //inserting into matrix
        for(a =numberOfFiles; a> 0; a--){
            for(b=numberOfFiles; b>0; b--){
                if(a>=b) break;
                fileOneInsertHash(my_hash, fileNames, phraseLength, b);
                printf("\n");
                int matches = fileTwoCompare(my_hash, fileNames, phraseLength, a);
                char *str = malloc(sizeof(char)*10000);
                char str1[10000];
                sprintf(str1, "%d", matches);
                strcpy(str, str1);
                matrix[a][b] = str;
                freeHash(my_hash);
                my_hash = newHash();
            }
        }

    //printing the matrix
    char hyphen = '-';
    for(i = 0; i<=numberOfFiles; i++){
        for(j = 0; j<=numberOfFiles; j++){
            if(j == 0 && i != 0) printf("%s", matrix[i][j]);
            else if(i>=j) printf(" %2c ", hyphen);
            else
                    printf(" %2s ", matrix[i][j]);

        }
        printf("\n" );
    }
    return 0;
}
