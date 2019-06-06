#ifndef TRIETREE_PROJECT_MAIN_H
#define TRIETREE_PROJECT_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

/*! typ bazowy elementu drzewa trie */
struct TrieTree {
    /** Flaga określająca węzeł jest ostatnim elementem słowa */
    int isWordEnd;
    /** Tablica wskaźników na kolejne węzły drzewa*/
    struct TrieTree *children[26];
};


/**
 * funkcja inicjująca menu
 */
void startMenu();

/**
 * funkcja tworząca drzewo trie
 * @return struktura stworzona przez funkcje
 */

struct TrieTree *createNewTrieNode();

/**
 * funkcja dodająca słowo do drzewa
 * @param wskaźnik root
 * @param word
 */

int insertWord(struct TrieTree **root, char word[]);


/**
 * funkcja sprawdzająca czy dane słowo jest obecne w drzewie
 * @return wartość pola isWordEnd szukanego słowa
 */
int searchWord(struct TrieTree **root, char word[]);


/**
 * funkcja sprawdzająca czy dany węzeł posiada inne węzły
 * @param root
 * @return wartość typu bool
 */
bool isFreeNode(struct TrieTree *root);


/**
 * funkcja sprawdzająca czy dany węzeł jest końcem słowa
 * @param wskaźnik root
 * @return wartość typu bool
 */
bool isWordEndNode(struct TrieTree *root);

/**
 * Funkcja pomocnicza służąca do usuwania słowa
 * @param wskaźnik root
 * @param słowo do usunięcia key
 * @param level
 * @param dlugość słowa len
 */
bool deleteHelper(struct TrieTree *root, char *key, int level, int len);

/**
 * Funkcja usuwająca słowo z drzewa
 * @param wskaźnik root
 * @param słowo do usunięcia key
 */
void deleteWord(struct TrieTree *root, char key[]);

/**
 * Funkcja obliczająca długość podanego slowa
 * @param word
 * @return długość słowa
 */
int calculateStringLength(char word[]);


/**
 * Funkcja która zmienia litery w słowie na duże
 * @param tablica ze słowem
 */
void toUpperCase(char word[]);

/**
 * Funkcja wypełnia tablice wartosciami NULL
 * @param tablica ze słowem
 */
void fillWordArrayWithNull(char word[]);

/**
 * Funkcja wypisująca słowo
 * @param słowo
 * @param n
 */
void printWord(char *str, int n);

/**
 * Funkcja wypisujaca wszystkie slowa z drzewa
 * @param wskaźnik root
 * @param word
 * @param pos
 */
void printAllWords(struct TrieTree *root, char *word, int pos);


/**
 * Funkcja sprawdza czy czy wskaźnik root jest pusty (nie ma żadnych słów do wyświetlenia)
 * @param wskaźnik root
 */
void checkRootPointer(struct TrieTree *root);

/**
 * Funkcja sprawdza czy slowo zawiera tylko dozwolone znaki
 * @param word
 * @return bool
 */
int checkUserInput(char word[]);

#endif //TRIETREE_PROJECT_MAIN_H
