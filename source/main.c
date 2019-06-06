#include "../headers/main.h"
/*!
 * \authors Paweł Mróz, Mikołaj Dyk, Dawid Daszkiewicz
 * \date 06.05.2019
 */


#define CHAR_SIZE 26
#define WORD_SIZE 32


int main() {

    startMenu();

    return 0;
}

struct TrieTree *createNewTrieNode() {

    struct TrieTree *newNode = (struct TrieTree *) malloc(sizeof(struct TrieTree));
    if (newNode) {
        newNode->isWordEnd = 0;
        for (int i = 0; i < CHAR_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

int insertWord(struct TrieTree **root, char word[]) {

    int counter = calculateStringLength(word);

    struct TrieTree *current = *root;
    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *) (word[j] - 'A');
        if (current->children[tableNumber] == NULL) {
            current->children[tableNumber] = createNewTrieNode();
        };
        current = current->children[tableNumber];
    }
    current->isWordEnd = 1;
}

int searchWord(struct TrieTree **root, char word[]) {

    if (*root == NULL) {
        return 0;
    }

    struct TrieTree *current = *root;

    int counter = calculateStringLength(word);

    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *) (word[j] - 'A');

        current = current->children[tableNumber];

        if (current == NULL) {
            return 0;
        }
    }

    return current->isWordEnd;


}

bool isFreeNode(struct TrieTree *root) {
    int i;
    for (i = 0; i < CHAR_SIZE; ++i) {
        if (root->children[i])
            return false;
    }
    return true;
}

bool isWordEndNode(struct TrieTree *root) {
    return root->isWordEnd == 1;
}

bool deleteHelper(struct TrieTree *root, char *key, int level, int len) {
    int ind;

    if (root != NULL) {
        if (level == len) {

            if (root->isWordEnd) {
                root->isWordEnd = 0;

                return isFreeNode(root);
            }
        } else {
            ind = key[level] - 'A';
            if (deleteHelper(root->children[ind], key, level + 1, len)) {
                free(root->children[ind]);
                root->children[ind] = NULL;

                if (!isWordEndNode(root) && isFreeNode(root)) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

void deleteWord(struct TrieTree *root, char key[]) {
    int len = (int *) strlen(key);
    if (len > 0) {

        if (deleteHelper(root, key, 0, len)) {
            root = NULL;
            free(root);
        }
    }
}

int calculateStringLength(char word[]) {

    return (int *) strlen(word);
}

void toUpperCase(char word[]) {
    int i;
    for (i = 0; i <= strlen(word); i++) {
        if (word[i] >= 97 && word[i] <= 122) {
            word[i] = word[i] - 32;
        }
    }
};

void fillWordArrayWithNull(char word[]) {
    for (int i = 0; i < 32; ++i) {
        word[i] = NULL;
    }
}

void printWord(char *str, int n) {
    puts("");
    for (int i = 0; i < n; i++) {
        printf("%c", str[i]);
    }
}

void printAllWords(struct TrieTree *root, char *word, int pos) {
    if (root == NULL) {
        return;
    }

    if (root->isWordEnd) {
        printWord(word, pos);
    }
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (root->children[i] != NULL) {
            word[pos] = i + 'A';
            printAllWords(root->children[i], word, pos + 1);
        }
    }
}

void checkRootPointer(struct TrieTree *root) {

    if (isFreeNode(root)) {
        printf("\033[22;31m\nDrzewo jest puste!\033[0m");
    }
}


int checkUserInput(char word[])
{
    int length = calculateStringLength(word);

    for(int i = 0; i < length; i++)
    {
        if(word[i] < 65 || word[i] > 91)
        {
            return true;
        }
    }

    return false;
}


void startMenu() {
    struct TrieTree *root = createNewTrieNode();
    int choice;

    do {

        char word[WORD_SIZE];
        printf("\n1. Wstaw do drzewa \n2. Sprawdz czy istnieje \n3. Usun z Drzewa \n4. Wyswietl zawartosc drzewa \n5. Wyjdz z programu \n\nTwoj wybor:");
        scanf("%d", &choice);
        system("clear");
        switch (choice) {
            case 1:
                printf("Wpisz slowo ktore ma być wpisane do drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s", word);
                toUpperCase(word);
                if(checkUserInput(word)==1){
                    printf("\033[22;31m\nSłowo zawiera niedozwolone znaki!\033[0m");
                } else {
                    insertWord(&root, word);
                    system("clear");
                    printf("\033[01;32mSlowo dodane pomyslnie!\033[0m");
                }

                break;
            case 2:
                printf("Wpisz slowo ktore ma byc sprawdzone czy istnieje w drzewie: ");
                fillWordArrayWithNull(word);
                scanf("%s", word);
                toUpperCase(word);
                if(checkUserInput(word)==1){
                    printf("\033[22;31m\nSłowo zawiera niedozwolone znaki!\033[0m");
                }else {
                    (searchWord(&root, word)) ? printf("\033[01;32mSlowo jest obecne!\033[0m") : printf(
                            "\033[22;31mSlowa nie ma w slowniku!\033[0m");
                }
                break;
            case 3:
                printf("Wpisz slowo ktore ma byc usuniete z drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s", word);
                toUpperCase(word);
                if(checkUserInput(word)==1){
                    printf("\033[22;31m\nSłowo zawiera niedozwolone znaki!\033[0m");
                } else {
                    deleteWord(root, word);
                    printf("\033[01;32mSlowo usuniete pomyslnie!\033[0m");
                }
                break;
            case 4:
                printf("\033[01;32mWszystkie slowa obecne w drzewie:\033[0m");
                printf("\033[01;32m\n/////////////////////////\033[0m");
                fillWordArrayWithNull(word);
                checkRootPointer(root);
                printAllWords(root, word, 0);
                printf("\033[01;32m\n/////////////////////////\033[0m");
                fillWordArrayWithNull(word);
                break;
            case 5:
                break;
            default:
                break;
        }
    } while (choice != 5);
}