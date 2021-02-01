// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <cs50.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10007;

// Hash table
node *table[N];

// Counter
int counter = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    int a = strlen(word);
    long long result = 0;
    long long base = 32;
    long long current = 1;

    for(int i = 0; i < a; i++){
        result = (result + (current * tolower(word[i])) % N);
        current = current * base % N;
    }
    return (int) result % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if(file == NULL){
        printf("Cannot open file\n");
        return false;
    }


    // Read Strings from file
    memset(table, 0, sizeof(table));
    while (true) {
        char word[512] = {0};
        int ret = fscanf(file, "%s", word);
        if (ret == EOF) break;

        // Hash word
        int index = hash(word);

        // Insert node into hash table
        if (table[index] == NULL)
        {
            table[index] = calloc(1, sizeof(node));
            if (!table[index])
            {
                fprintf(stderr, "Computer out of memory\n");
                return false;
            }
            strcpy(table[index]->word, word);
        }
        else
        {
            node *m = table[index];
            while(m->next != NULL) {
                m = m->next;
            }
            m->next = calloc(1, sizeof(node));
            if (!m->next)
            {
                fprintf(stderr, "Computer out of memory\n");
                return false;
            }
            strcpy(m->next->word, word);
        }

        counter++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int i = hash(word);
    node *cursor = table[i];
    while(cursor != NULL){
        if (strcasecmp(cursor->word, word) == 0){
            return true;
        }
        else{
            cursor = cursor->next;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    for(int i = 0; i < N; i++){
        cursor = table[i];
        while(cursor != NULL) {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
