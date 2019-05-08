#ifndef TRIETREE_PROJECT_MAIN_H
#define TRIETREE_PROJECT_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//struktura drzewa trie
struct TrieTree {

    int isWordEnd;// 1 jezeli wezel jest koncem slowa
    struct TrieTree *children[26];
};


int calculateStringLength(char word[]);

void startMenu();

//Funkcja ktora tworzy nowy Node
struct TrieTree *createNewTrieNode();

//Funkcja dodajaca slowo
int insertWord(struct TrieTree **root, char word[]);

//Funkcja sprwadzajaca czy dane slowo istnieje
int searchWord(struct TrieTree **root, char word[]);

//Funkcja sprwadza czy dany node ma szukane slowo
int haveChildren(struct TrieTree *current);

//Funkcja usuwajaca slowo
int deleteWord(struct TrieTree **current, char word[], int j);

//Funkcja liczaca dlugosc wpisanego slowa
int calculateStringLength(char word[]);

//Funkcja ktora zmienia litery na duze
char toUpperCase(char word[]);

//Funkcja wypełnia tablice wartosciami NULL
void fillWordArrayWithNull(char word[]);


#endif //TRIETREE_PROJECT_MAIN_H
