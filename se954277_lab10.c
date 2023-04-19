#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Sean Heisey
// COP 3502
// 4/19/2023
// Lab 10

// trie structure
struct Trie{
    int flag; 
    struct Trie *next[26];
};
// predefined functions
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *makeTrie(char data);
// main function
int main(void)
{
    // initialize trie
    struct Trie *trie = malloc(sizeof(struct Trie));
    trie->flag = 0;
    for(int i=0; i<26; i++)
        trie->next[i] = NULL;
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for(int i=0; i<5; i++){
        // insert trie
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if(trie!=NULL)
       printf("There is an error in this program\n");
    return 0;
}
// inserts to trie
void insert(struct Trie **ppTrie, char *word){
    // traverse 
    struct Trie *temp = *ppTrie;
    for(int i=0; word[i]!='\0'; i++){
        int idx = word[i] - 'a';
        if(temp->next[idx]==NULL)
            // create node
            temp->next[idx] = makeTrie(word[i]);
        temp = temp->next[idx];
    }
    temp->flag = 1;
}
// calculates occucences of each word
int numberOfOccurances(struct Trie *pTrie, char *word){
    // traverse
    for(int i=0; i<word[i]!='\0'; i++){
        int idx = word[i] - 'a';
        if(pTrie->next[idx]==NULL)
            return 0;
        pTrie = pTrie->next[idx];
    }
    // count words
    int count = 0;
    if(pTrie==NULL)
        return 0;
    if(pTrie->flag)
        count++;
    return count;
}
// initializes trie node 
struct Trie *makeTrie(char data){
    // using calloc
    struct Trie *node = calloc(1, sizeof(struct Trie));
    for(int i=0; i<26; i++)
        node->next[i] = NULL;
    node->flag = 0;
    node->flag = data;
    return node;
}
// free trie recursivly 
struct Trie *deallocateTrie(struct Trie *pTrie){
    if(pTrie==NULL)
        return NULL;
    for(int i=0; i<26; i++){
        if(pTrie->next[i]!=NULL)
            deallocateTrie(pTrie->next[i]);
    }
    // free trie node
    free(pTrie);
    return NULL;
}