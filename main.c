#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Drzewo oparte jest na 26 literowym alfabecie (niestety nie obsluguje polskich znakow)
#define CHAR_SIZE 26
//
#define WORD_SIZE 32

struct TrieTree {

    int isLeaf;// 1 jezeli wezel jest lisciem
    struct TrieTree *children[CHAR_SIZE];
};

int calculateStringLength(char word[]);

struct TrieTree *getNewTrieNode()
{
    //Dynamiczne alokowanie pamieci dla nowego wezla
    struct TrieTree *newNode = (struct TrieTree *)malloc(sizeof(struct TrieTree));
    if(newNode){
        //Ustawianie wartosci isLeafe wezla na 0 oraz wypelnianie tablicy wartosciami NULL
        newNode->isLeaf = 0;
        for (int i = 0; i < CHAR_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    //zwracanie wezla
    return  newNode;
}


int insertWord(struct TrieTree **root, char word[])
{
    if (root == NULL){
        return 0;
    }
    //Oblicznie dlugosci wpisywanego slowa
    int counter = calculateStringLength(word);

    struct TrieTree *current = *root;

    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *)(word[j] - 'A');

        if(current->children[tableNumber] == NULL){
            current->children[tableNumber] = getNewTrieNode();
        };

        current = current->children[tableNumber];
    }

    current->isLeaf = 1;
}


int searchWord(struct TrieTree **root, char word[]){

    if (root == NULL){
        return 0;
    }

    struct TrieTree *current = *root;

    int counter = calculateStringLength(word);

    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *)(word[j] - 'A');

        current = current->children[tableNumber];

        if(current == NULL)
        {
            return 0;
        }
    }

    return current->isLeaf;


}


//Funkcja liczaca dlugosc wpisanego slowa
int calculateStringLength(char word[]){

    int counter = 0;
    for (int i = 0; i < 32; i++) {

        if(word[i] != NULL)
        {
            counter++;
        }
    }

    return counter;
}
//Funkcja ktora zmienia litery na duze
char toUpperCase(char word[]) {
    int i;
    for(i=0;i<=strlen(word);i++){
        if(word[i]>=97 && word[i]<=122)
        {
            word[i]=word[i]-32;
        }
    }
    return word;
};

void fillWordArrayWithNull(char word[])
{
    for (int i = 0; i < 32; ++i) {
        word[i] = NULL;
    }
}

int main() {

    struct TrieTree *root = getNewTrieNode();

    int choice;
    do{
        char word[WORD_SIZE];

        printf("\n\n1. Wstaw do drzewa \n2. Sprawdz czy istnieje \n3. Usun z Drzewa \n4. Wyjdz z programu \n\nTwoj wybor:");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Wpisz slowo ktore ma być wpisane do drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s",word);
                word[32] = toUpperCase(word);
                insertWord(&root, word);
                puts("\nSlowo dodane pomyslnie");
                break;
            case 2:
                printf("Wpisz slowo ktore ma byc sprwadzone czy istnieje w drzewie: ");
                fillWordArrayWithNull(word);
                scanf("%s",word);
                word[32] = toUpperCase(word);
                printf(searchWord(&root, word) ? "OBECNE" : "NIEOBECNE");
                break;
            case 3:
                printf("Wpisz slowo ktore ma byc usuniete z drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s",word);
                word[32] = toUpperCase(word);
                break;
            case 4: break;
            default:
                break;
        }
    }while(choice != 4);

    return 0;
}