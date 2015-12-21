/*
 * Hash.h
 * Cop 3530 Spring 15
 * jlewis
 */

#ifndef _hash_h
#define _hash_h
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
int lookupHashRecur(NodeP , char *);
NodeP removeHashRecur(NodeP ,char * );
int countChainLength(NodeP );
void freeHashIndex(NodeP);


/*
 * Definition for a pointer to a Hash struct.
 */
typedef struct Hash *HashP;

/*
 * Hash Interface
 */

/*
 * Returns a pointer to a new empty Hash
 * Parameters: integer indicating desired size of table
 * If memory cannot be allocated, returns a NULL pointer
 */
HashP newHash();

/*
 * Locates and displays the desired contact from the hash table
 * If entry is not found, display an appropriate message
 * Parameters: hash, first name, last name
 */
int lookupHash(HashP, char *);

/*
 * Creates a new entry for the hash table using provided data
 * Parameters: hash, first name, last name, address, phone, email
 */
void insertHash(HashP, char *);

/*
 * Removes the entry containing the matching names
 * Parameters: hash, first name, last name
 */
void removeHash(HashP, char *);

/*
 * Displays all the entries in the hash table
 * Note: they need not be in any order
 */
void displayHash(HashP);

/*
 * Displays statistics for hash table
 *      Key count
 *      Bucket count (table size)
 *      Used bucket count
 *      Empty bucket count
 *      Collision count
 *      Longest chain length
 *      Average chain length of "used" buckets
 * Parameters: hash
 */
void displayStatisticsHash(HashP);

/*
 * Frees the memory used by this hash
 * Frees all the nodes
 * Parameters: hash
 * Returns NULL
 */
HashP freeHash(HashP);

#endif
