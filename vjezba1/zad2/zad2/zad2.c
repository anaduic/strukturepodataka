#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[20];
    char surname[20];
    int day, month, year;
    struct Person* next;
} Person;

// Prototypes
Person* create_person();
Person* add_to_start(Person* head);
Person* add_to_end(Person* head);
Person* remove_person(Person* head, char* surname);
int print_list(Person* head);
int find_person(Person* head, char* surname);

int main() {
    Person* head = NULL;
    int choice = 0;
    char search_surname[20];
    int status = 0;

    do {
        printf("\n----------------------------------\n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Dodaj osobu na kraj\n");
        printf("3. Obrisi osobu iz liste\n");
        printf("4. Pretrazi po prezimenu\n");
        printf("5. Ispisi sve osobe\n");
        printf("6. Izlaz iz programa\n");
        printf("----------------------------------\n");
        printf("Odabir: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            head = add_to_start(head);
            break;
        case 2:
            head = add_to_end(head);
            break;
        case 3:
            printf("Unesite prezime osobe za brisanje: ");
            scanf("%19s", search_surname);
            head = remove_person(head, search_surname);
            break;
        case 4:
            printf("Unesite prezime osobe za pretragu: ");
            scanf("%19s", search_surname);
            if (find_person(head, search_surname) != 0)
                printf("Osoba s prezimenom '%s' nije pronadena!\n", search_surname);
            break;
        case 5:
            status = print_list(head);
            if (status != 0)
                printf("Lista je prazna!\n");
            break;
        case 6:
            printf("Zatvaranje programa...\n");
            break;
        default:
            printf("Pogresan unos, pokusajte ponovno!\n");
        }
    } while (choice != 6);

    // Oslobodi memoriju
    Person* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

// Funkcija za unos nove osobe
Person* create_person() {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (!new_person) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    printf("Unesite ime: ");
    scanf("%19s", new_person->name);
    printf("Unesite prezime: ");
    scanf("%19s", new_person->surname);
    printf("Unesite datum rodenja (dd mm yyyy): ");
    scanf("%d %d %d", &new_person->day, &new_person->month, &new_person->year);

    new_person->next = NULL;
    return new_person;
}

// Dodavanje osobe na pocetak liste
Person* add_to_start(Person* head) {
    Person* new_person = create_person();
    if (!new_person) return head;

    new_person->next = head;
    return new_person;
}

// Dodavanje osobe na kraj liste
Person* add_to_end(Person* head) {
    Person* new_person = create_person();
    if (!new_person) return head;

    if (head == NULL)
        return new_person;

    Person* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_person;
    return head;
}

// Ispis cijele liste
int print_list(Person* head) {
    if (head == NULL)
        return 1;

    printf("\n%-15s %-15s %-20s\n", "IME", "PREZIME", "DATUM RODENJA");
    printf("------------------------------------------------------------\n");

    Person* temp = head;
    while (temp != NULL) {
        printf("%-15s %-15s %02d.%02d.%04d\n",
            temp->name, temp->surname, temp->day, temp->month, temp->year);
        temp = temp->next;
    }

    return 0;
}

// Brisanje osobe iz liste po prezimenu
Person* remove_person(Person* head, char* surname) {
    Person* temp = head;
    Person* previous = NULL;

    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadena u listi.\n", surname);
        return head;
    }

    if (previous == NULL)
        head = temp->next;
    else
        previous->next = temp->next;

    printf("Osoba '%s %s' uspjesno obrisana iz liste.\n", temp->name, temp->surname);
    free(temp);
    return head;
}

// Pretraga osobe po prezimenu
int find_person(Person* head, char* surname) {
    if (head == NULL)
        return 1;

    for (Person* temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->surname, surname) == 0) {
            printf("Pronadena osoba: %s %s, roden/a %02d.%02d.%04d\n",
                temp->name, temp->surname, temp->day, temp->month, temp->year);
            return 0;
        }
    }
    return 1;
}