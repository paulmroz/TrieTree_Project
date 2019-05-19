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


//Funkcja pokazująca menu
void startMenu();

//Funkcja ktora tworzy nowy Node
struct TrieTree *createNewTrieNode();

//Funkcja dodajaca slowo
int insertWord(struct TrieTree **root, char word[]);

//Funkcja sprwadzajaca czy dane slowo istnieje
int searchWord(struct TrieTree **root, char word[]);

//Funkcja sprawdzająca czy dany węzeł posiada dzieci
bool isFreeNode(struct TrieTree* p);

//Funkcja sprawdzająca czy dane węzeł jest liściem
bool isLeafNode(struct TrieTree* p);

//Funkcja pomocniczna do usuwania słowa
bool deleteHelper(struct TrieTree* root, char* key, int level, int len);

//Funkcja usuwająca słowo z drzewa
void deleteWord(struct TrieTree* root, char key[]);

//Funkcja liczaca dlugosc wpisanego slowa
int calculateStringLength(char word[]);

//Funkcja ktora zmienia litery na duze
void toUpperCase(char word[]);

//Funkcja wypełnia tablice wartosciami NULL
void fillWordArrayWithNull(char word[]);

//Funkcja wypisująca słowo
void printWord(char* str, int n);

//Funkcja wypisujaca wszystkie slowa z drzewa
void printAllWords(struct TrieTree *root, char* word, int pos);

//Funkcja sprawdza czy czy wskaźnik root jest pusty (nie ma żadnych słów do wyświetlenia)
void checkRootPointer(struct TrieTree *root);

#endif //TRIETREE_PROJECT_MAIN_H
