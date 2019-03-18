#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Drzewo oparte jest na 26 literowym alfabecie (niestety nie obsluguje polskich znakow)
#define CHAR_SIZE 26
//Program przyjmuje 32 literowe slowo
#define WORD_SIZE 32

struct TrieTree {

    int isWordEnd;// 1 jezeli wezel jest lisciem
    struct TrieTree *children[CHAR_SIZE];
};

int calculateStringLength(char word[]);

struct TrieTree *createNewTrieNode()
{
    //Dynamiczne alokowanie pamieci dla nowego wezla
    struct TrieTree *newNode = (struct TrieTree *)malloc(sizeof(struct TrieTree));
    if(newNode){
        //Ustawianie wartosci isLeafe wezla na 0 oraz wypelnianie tablicy wartosciami NULL
        newNode->isWordEnd = 0;
        for (int i = 0; i < CHAR_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    //zwracanie wezla
    return  newNode;
}



int insertWord(struct TrieTree **root, char word[])
{

    //Oblicznie dlugosci wpisywanego slowa
    int counter = calculateStringLength(word);

    struct TrieTree *current = *root;

    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *)(word[j] - 'A');

        if(current->children[tableNumber] == NULL){
            current->children[tableNumber] = createNewTrieNode();
        };

        current = current->children[tableNumber];
    }

    current->isWordEnd = 1;
}


int searchWord(struct TrieTree **root, char word[]){

    if (*root == NULL){
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

    return current->isWordEnd;


}

int haveChildren(struct TrieTree *current){
    for (int i = 0; i < CHAR_SIZE; i++) {
        if(current->children[i])
        {
            return 1 ;//ma dziecko
        }
    }
    return 0;
}




int deleteWord(struct TrieTree **current, char word[], int j){

    if(*current == NULL)
    {
        return 0;
    }

    int i = j;

    int counter = calculateStringLength(word);

    int tableNumber = (int *)(word[i] - 'A');

    if(i<counter){
        if( *current != NULL && (*current)->children[tableNumber] != NULL && deleteWord((&((*current)->children[tableNumber])),word,i+1) && (*current)->isWordEnd == 0)
        {
            if(!haveChildren(*current))
            {
                free(*current);
                (*current) = NULL;
                return 1;
            }else{
                return 0;
            }
        }
    }

    if(i == counter  && (*current)->isWordEnd)
    {
        if(!haveChildren(*current))
        {
            free(*current);
            (*current) = NULL;
            return 1;
        }
        else {
            (*current)->isWordEnd = 0;
            return 0;
        }
    }

    return 0;

}


//Funkcja liczaca dlugosc wpisanego slowa
int calculateStringLength(char word[]){

    return (int *)strlen(word);
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

//Funkcja wypełnia tablice wartosciami NULL
void fillWordArrayWithNull(char word[])
{
    for (int i = 0; i < 32; ++i) {
        word[i] = NULL;
    }
}

int main() {

    struct TrieTree *root = createNewTrieNode();

    int choice;

    do{

        char word[WORD_SIZE];

        printf("\n1. Wstaw do drzewa \n2. Sprawdz czy istnieje \n3. Usun z Drzewa \n4. Wyjdz z programu \n\nTwoj wybor:");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Wpisz slowo ktore ma być wpisane do drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s",word);
                word[32] = toUpperCase(word);
                insertWord(&root, word);
                printf("\033[01;32mSlowo dodane pomyslnie!\033[0m");
                break;
            case 2:
                printf("Wpisz slowo ktore ma byc sprawdzone czy istnieje w drzewie: ");
                fillWordArrayWithNull(word);
                scanf("%s",word);
                word[32] = toUpperCase(word);
                (searchWord(&root, word)) ? printf("\033[01;32mSlowo jest obecne!\033[0m"):printf("\033[22;31mSlowa nie ma w slowniku!\033[0m");
                break;
            case 3:
                printf("Wpisz slowo ktore ma byc usuniete z drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s",word);
                word[32] = toUpperCase(word);
                deleteWord(&root,word,0) ? printf("\033[01;32mSlowo usunięte!\033[0m"):printf("\033[22;31mSlowo nie zostalo usuniete!\033[0m");;
                break;
            case 4: break;
            default:
                break;
        }
    }while(choice != 4);

    return 0;
}