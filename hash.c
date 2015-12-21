/*
 * File:   Hash.c.c
 * Author: Alex
 *
 * Created on April 18, 2015, 12:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

#define table_size 10000

/*
struct stats {
    int key_count;
    int bucket_count;
    int used_bucket_count;
    int empty_bucket_count;
    int collision_count;
    int longest_chain_length;
    int average_chain_length;
};
typedef struct stats *statsP;
struct node{

    struct node *right;
    char *word;
};
typedef struct node *NodeP;
struct Hash {
    statsP stats;
    NodeP *table;

};


NodeP newNode(char *);
int calculateIndex(char *);
void printHashIndex(NodeP);
void printNode(NodeP);
void lookupHashRecur(NodeP , char *);
NodeP removeHashRecur(NodeP ,char * );
int countChainLength(NodeP );
void freeHashIndex(NodeP);
*/

HashP newHash(){
    int i;
    HashP my_hash = (HashP) malloc(sizeof(struct Hash));
    if(my_hash == NULL){
        fprintf(stderr, "Hash allocation failed!\n");
        return;
    }

    my_hash->stats = (statsP) malloc(sizeof(struct stats));
    my_hash->stats->average_chain_length = 0;
    my_hash->stats->bucket_count = table_size;
    my_hash->stats->collision_count = 0;
    my_hash->stats->empty_bucket_count = table_size;
    my_hash->stats->key_count = 0;
    my_hash->stats->longest_chain_length = 0;
    my_hash->stats->used_bucket_count = 0;
    my_hash->table = malloc(sizeof(NodeP)*table_size);

    for(i = 0; i<table_size;i++){
        my_hash->table[i] = NULL;
    }
    return my_hash;
}

int lookupHash(HashP my_hash, char *phrase){

    if(my_hash == NULL){
        fprintf(stderr, "No hash exists!\n");
        return -1;
    }
    int index = calculateIndex(phrase);
   // index = index % my_hash->stats->bucket_count;
    if(my_hash->table[index] == NULL){
      //  fprintf(stderr, "Phrase not found!\n");
        return -1;
    }
    return lookupHashRecur(my_hash->table[index], phrase);

}

void insertHash(HashP my_hash, char *phrase){

    if(my_hash == NULL){
        fprintf(stderr, "No hash exists!\n");
        return;
    }
    NodeP node_to_insert = newNode(phrase);
    int index = calculateIndex(phrase);
   // index = index % my_hash->stats->bucket_count;
    if(my_hash->table[index] == NULL){
        my_hash->table[index] = node_to_insert;
        my_hash->stats->empty_bucket_count -= 1;
        my_hash->stats->key_count++;
        my_hash->stats->used_bucket_count += 1;

        return;
    }
    node_to_insert->right = my_hash->table[index];
    my_hash->table[index] = node_to_insert;
    my_hash->stats->collision_count += 1;
    my_hash->stats->key_count += 1;

   return;
}


void removeHash(HashP my_hash, char *phrase){
    if(my_hash == NULL){
        fprintf(stderr, "No hash exists!\n");
        return;
    }
    int index = calculateIndex(phrase);
   // index = index % my_hash->stats->bucket_count;
    if(my_hash->table[index] == NULL){
     //   fprintf(stderr, "Contact not found!\n");
        return;
    }
    my_hash->table[index] = removeHashRecur(my_hash->table[index], phrase);
}

void displayHash(HashP my_hash){
    if(my_hash == NULL){
        fprintf(stderr, "No hash exists!\n");
        return;
    }
    int i;
    for(i=0;i<my_hash->stats->bucket_count;i++){
        printHashIndex(my_hash->table[i]);
    }
    return;
}

void displayStatisticsHash(HashP my_hash){
    if(my_hash == NULL){
        fprintf(stderr, "No hash exists!\n");
        return;
    }
    int longest_chain = 0;
    int i;
    for(i = 0; i<my_hash->stats->bucket_count; i++){
        longest_chain = countChainLength(my_hash->table[i]);
        if (longest_chain > my_hash->stats->longest_chain_length){
            my_hash->stats->longest_chain_length = longest_chain;
        }
    }
    my_hash->stats->average_chain_length = (my_hash->stats->key_count) / (my_hash->stats->used_bucket_count);
    fprintf(stderr, "Average Chain Length: %i\n", my_hash->stats->average_chain_length);
    fprintf(stderr, "Longest Chain Length: %i\n", my_hash->stats->longest_chain_length);

    fprintf(stderr, "Bucket Count: %i\n", my_hash->stats->bucket_count);
    fprintf(stderr, "Used Bucket Count: %i\n", my_hash->stats->used_bucket_count);
    fprintf(stderr, "Empty Bucket Count: %i\n", my_hash->stats->empty_bucket_count);

    fprintf(stderr, "Collision Count: %i\n", my_hash->stats->collision_count);
    fprintf(stderr, "Key Count: %i\n", my_hash->stats->key_count);


}

HashP freeHash(HashP my_hash){
    if(my_hash == NULL){
        fprintf(stderr, "No hash exists!\n");
        return NULL;
    }
    int i;
    for(i= 0; i < my_hash->stats->bucket_count; i++){
        freeHashIndex(my_hash->table[i]);
    }
    free(my_hash->table);
    free(my_hash->stats);
    return NULL;
}

NodeP newNode(char *phrase){
        char * buffer = malloc(sizeof(char)* 20000);
        strcpy(buffer, phrase);
    NodeP nodeToInsert = malloc(sizeof(struct node));
    if(newNode == NULL){
        fprintf(stderr, "Node Memory allocation failed!\n");
        return NULL;
        }
    nodeToInsert->word = buffer;

        nodeToInsert->right = NULL;
        return nodeToInsert;
}


int calculateIndex(char *phrase){
    int total = 1;
    int len = strlen(phrase);
    int i;
    for(i = 0; i < len; i++){
        total += phrase[i] * (i + 1);

    }
    if(total < 0)
        total *= -1;

    return total%table_size;
}

void printHashIndex(NodeP indexToPrint){
    if(indexToPrint == NULL) return;
    printNode(indexToPrint);
    if(indexToPrint->right != NULL)
        printHashIndex(indexToPrint->right);
    return;

}


void printNode(NodeP nodeToPrint){
    printf("%s\n", nodeToPrint->word);

    return;
}

int lookupHashRecur(NodeP nodeToFind, char *phrase){
    if(strcmp(phrase, nodeToFind->word) == 0){
        //printNode(nodeToFind);
        return 1;
    }
    if(nodeToFind->right != NULL){
        lookupHashRecur(nodeToFind->right, phrase);
    }
    if(nodeToFind->right == NULL){
      //  fprintf(stderr, "Not found!\n");
        return -1;
    }

    return -1;
}


NodeP removeHashRecur(NodeP nodeToFind,char *phrase){
    if(strcmp(phrase, nodeToFind->word) == 0){
        NodeP node_to_return = nodeToFind->right;
        free(nodeToFind);
        return node_to_return;
    }
    if(nodeToFind->right != NULL){
        nodeToFind->right = removeHashRecur(nodeToFind->right, phrase);
    }
    if(nodeToFind->right == NULL){
        fprintf(stderr, "Contact not found!\n");
        return;
    }
}

int countChainLength(NodeP chain){
    if(chain==NULL){
        return 0;
    }
    NodeP p = chain;
    int chainLength = 0;
    if(chain->right == NULL) return 1;
    while(p->right != NULL){
        chainLength++;
        p = p->right;
    }
    return chainLength + 1;
}

void freeHashIndex(NodeP index){
    if(index == NULL) return;
    if(index->right == NULL){
        free(index);
        return;
    }
    freeHashIndex(index->right);
    free(index);
    return;

}
