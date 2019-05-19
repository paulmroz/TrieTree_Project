#include "../headers/main.h"

#define CHAR_SIZE 26
#define WORD_SIZE 32


int main() {

    startMenu();

    return 0;
}


//Funkcja ktora tworzy nowy Node
struct TrieTree *createNewTrieNode() {
    //Dynamiczne alokowanie pamieci dla nowego wezla
    struct TrieTree *newNode = (struct TrieTree *) malloc(sizeof(struct TrieTree));
    if (newNode) {
        //Ustawianie wartosci isLeafe wezla na 0 oraz wypelnianie tablicy wartosciami NULL
        newNode->isWordEnd = 0;
        for (int i = 0; i < CHAR_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    //zwracanie wezla
    return newNode;
}


//Funkcja dodajaca slowo
int insertWord(struct TrieTree **root, char word[]) {

    //Oblicznie dlugosci wpisywanego slowa
    int counter = calculateStringLength(word);

    struct TrieTree *current = *root;
    //Petla wykona sie tyle razy ile jest slow w dodawanym slowie
    for (int j = 0; j < counter; j++) {

        //Obliczanie indeksu w tablocy do sprawdzenia
        int tableNumber = (int *) (word[j] - 'A');
        //Jezeli w tabeli children danego Node nie ma litery z wpisywanego slowa to jest tworzone
        if (current->children[tableNumber] == NULL) {
            current->children[tableNumber] = createNewTrieNode();
        };
        //Przejcie do kolejnego Node
        current = current->children[tableNumber];
    }
    //Po dodaniu wszystich liter ostatni Node oznaczany jest jako koniec slowa;
    current->isWordEnd = 1;
}


//Funkcja sprwadzajaca czy dane slowo istnieje
int searchWord(struct TrieTree **root, char word[]) {

    if (*root == NULL) {
        return 0;
    }

    struct TrieTree *current = *root;

    int counter = calculateStringLength(word);

    //Sprawdzanie czy w danym Node jest litera szukanego slowa jezeli
    // nie ma funkcja zwroci 0 jezeli jest sprwadza czy jest to koniec slowa i zwroci fale isWordEnd;
    for (int j = 0; j < counter; j++) {

        int tableNumber = (int *) (word[j] - 'A');

        current = current->children[tableNumber];

        if (current == NULL) {
            return 0;
        }
    }

    return current->isWordEnd;


}

//Funkcja sprawdzająca czy dany węzeł posiada dzieci
bool isFreeNode(struct TrieTree *p) {
    int i;
    for (i = 0; i < CHAR_SIZE; ++i) {
        if (p->children[i])
            return false;
    }
    return true;
}


//Funkcja sprawdzająca czy dane węzeł jest liściem
bool isLeafNode(struct TrieTree *p) {
    return p->isWordEnd == 1;
}


//Funkcja pomocniczna do usuwania słowa
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

                if (!isLeafNode(root) && isFreeNode(root)) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

//Funkcja usuwająca słowo z drzewa
void deleteWord(struct TrieTree *root, char key[]) {
    int len = (int *) strlen(key);
    if (len > 0) {

        if (deleteHelper(root, key, 0, len)) {
            root = NULL;
            free(root);
        }
    }
}


//Funkcja liczaca dlugosc wpisanego slowa
int calculateStringLength(char word[]) {

    return (int *) strlen(word);
}

//Funkcja ktora zmienia litery na duze
void toUpperCase(char word[]) {
    int i;
    for (i = 0; i <= strlen(word); i++) {
        if (word[i] >= 97 && word[i] <= 122) {
            word[i] = word[i] - 32;
        }
    }
};

//Funkcja wypełnia tablice wartosciami NULL
void fillWordArrayWithNull(char word[]) {
    for (int i = 0; i < 32; ++i) {
        word[i] = NULL;
    }
}

//Funkcja wypisująca słowo
void printWord(char *str, int n) {
    puts("");
    for (int i = 0; i < n; i++) {
        printf("%c", str[i]);
    }
}

//Funkcja wypisujaca wszystkie slowa z drzewa
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

//Funkcja sprawdza czy czy wskaźnik root jest pusty (nie ma żadnych słów do wyświetlenia)
void checkRootPointer(struct TrieTree *root) {
    int counter = 0;
    for (int j = 0; j < CHAR_SIZE; j++) {
        if (root->children[j] == NULL /*|| root->children[j] == 0*/) {
            counter++;
        }
    }

    if (counter == 26) {
        printf("\033[22;31m\nDrzewo jest puste!\033[0m");
    }
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
                insertWord(&root, word);
                system("clear");
                printf("\033[01;32mSlowo dodane pomyslnie!\033[0m");
                break;
            case 2:
                printf("Wpisz slowo ktore ma byc sprawdzone czy istnieje w drzewie: ");
                fillWordArrayWithNull(word);
                scanf("%s", word);
                toUpperCase(word);
                (searchWord(&root, word)) ? printf("\033[01;32mSlowo jest obecne!\033[0m") : printf(
                        "\033[22;31mSlowa nie ma w slowniku!\033[0m");
                break;
            case 3:
                printf("Wpisz slowo ktore ma byc usuniete z drzewa: ");
                fillWordArrayWithNull(word);
                scanf("%s", word);
                toUpperCase(word);
                deleteWord(root, word);
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