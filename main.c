#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Drzewo oparte jest na 26 literowym alfabecie
#define CHAR_SIZE 26
#define WORD_SIZE 32

struct TrieTree {

    int isLeaf;// 1 jezeli wezel jest lisciem
    struct TrieTree *children[CHAR_SIZE];
};

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



void insertWord(struct TrieTree **root, char word[])
{
    if (root == NULL){
        return 0;
    }

    int counter = calculateStringLength(word);

    struct TrieTree* curr = *root;

    for (int i = 0; i < 32; i++) {

        if(word[i] != NULL)
        {
            counter++;
        }
    }

    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *)(word[j] - 'A');

        if(curr->children[tableNumber] == NULL){
            curr->children[tableNumber] = getNewTrieNode();
        };

        curr = curr->children[tableNumber];
    }

    curr->isLeaf = 1;
}


//int searchWord(struct TrieTree *root, char word[])


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


int main() {

    struct TrieTree *root = getNewTrieNode();

    int choice;
    do{
        char word[WORD_SIZE];
        for (int i = 0; i < 32; ++i) {
            word[i] = NULL;
        }
        int result;
        printf("\n\n1. Wstaw do drzewa \n2. Sprawdz czy istnieje \n3. Usun z Drzewa \n4. Wyjdz z programu \n\nTwoj wybor:");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Wpisz slowo ktore ma być wpisane do drzewa: ");
                scanf("%s",word);
                word[32] = toUpperCase(word);
                insertWord(&root, word);
                puts("Slowo dodane pomyslnie");
                break;
            case 2:
                printf("Wpisz slowo ktore ma byc sprwadzone czy istnieje w drzewie: ");
                scanf("%s",word);
                toUpperCase(word);
                break;
            case 3:
                printf("Wpisz slowo ktore ma byc usuniete z drzewa: ");
                scanf("%s",word);
                toUpperCase(word);
                break;
            case 4: break;
            default:
                break;
        }
    }while(choice != 4);

    return 0;
}