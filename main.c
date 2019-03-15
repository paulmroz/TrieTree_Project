#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Drzewo oparte jest na 26 literowym alfabecie
#define CHAR_SIZE 26

struct Node {

    int isLeaf;
    struct Node *character[CHAR_SIZE];
};






char toUppperCase(char word[]) {
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

    int choice;
    do{
        char word[32];
        int result;
        printf("\n\n1. Wstaw do drzewa \n2. Sprawdz czy istnieje \n3. Usun z Drzewa \n4. Wyjdz z programu \n\nTwoj wybor:");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Wpisz slowo ktore ma być wpisane do drzewa: ");
                scanf("%s",word);
                toUppperCase(word);

                break;
            case 2:
                printf("Wpisz slowo ktore ma byc sprwadzone czy istnieje w drzewie: ");
                scanf("%s",word);
                toUppperCase(word);
                break;
            case 3:
                printf("Wpisz slowo ktore ma byc usuniete z drzewa: ");
                scanf("%s",word);
                toUppperCase(word);
                break;
            case 4: break;
            default:
                break;
        }
    }while(choice != 4);

    return 0;
}