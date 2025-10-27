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


Person* create_person();
Person* add_to_start(Person* head);
Person* add_to_end(Person* head);
Person* remove_person(Person* head, char* surname);
int print_list(Person* head);
int find_person(Person* head, char* surname);


Person* addAfter(Person* head);
Person* addBefore(Person* head);
Person* sort(Person* head);
int write(Person* head);
Person* readFromFile();

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
        printf("7. Dodaj osobu iza odredene osobe\n");
        printf("8. Dodaj osobu ispred odredene osobe\n");
        printf("9. Sortiraj listu po prezimenima\n");
        printf("10. Spremi listu u datoteku\n");
        printf("11. Ucitaj listu iz datoteke\n");
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
            printf("Zatvaranje programa\n");
            break;
        case 7:
            head = addAfter(head);
            break;
        case 8:
            head = addBefore(head);
            break;
        case 9:
            head = sort(head);
            break;
        case 10:
            write(head);
            break;
        case 11:
            head = readFromFile();
            break;
        default:
            printf("Pogresan unos, pokusajte ponovno\n");
        }
    } while (choice != 6);

    // Oslobodanje memorije
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

// Dodavanje osobe iza odredene osobe
Person* addAfter(Person* head)
{
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Neuspjesna alokacija memorije!\n");
        return head;
    }

    printf("Unesi ime osobe: ");
    scanf("%19s", newPerson->name);
    printf("Unesi prezime osobe: ");
    scanf("%19s", newPerson->surname);
    printf("Unesi datum rodenja (dd mm yyyy): ");
    scanf("%d %d %d", &newPerson->day, &newPerson->month, &newPerson->year);

    char afterSurname[20];
    printf("Unesi prezime osobe iza koje zelite dodati novu osobu: ");
    scanf("%19s", afterSurname);

    Person* temp = head;
    while (temp != NULL && strcmp(afterSurname, temp->surname) != 0)
        temp = temp->next;

    if (temp != NULL) {
        newPerson->next = temp->next;
        temp->next = newPerson;
        printf("Osoba unesena.\n");
    }
    else {
        printf("Greska, nema osobe s tim prezimenom!\n");
        free(newPerson);
    }

    return head;
}

// Dodavanje osobe ispred odredene osobe
Person* addBefore(Person* head)
{
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Neuspjesna alokacija memorije!\n");
        return head;
    }

    printf("Unesi ime osobe: ");
    scanf("%19s", newPerson->name);
    printf("Unesi prezime osobe: ");
    scanf("%19s", newPerson->surname);
    printf("Unesi datum rodenja (dd mm yyyy): ");
    scanf("%d %d %d", &newPerson->day, &newPerson->month, &newPerson->year);

    char beforeSurname[20];
    printf("Unesi prezime osobe ispred koje zelite dodati novu osobu: ");
    scanf("%19s", beforeSurname);

    Person* temp = head;

    if (head != NULL && strcmp(head->surname, beforeSurname) == 0) {
        newPerson->next = head;
        head = newPerson;
        printf("Osoba unesena.\n");
        return head;
    }

    while (temp->next != NULL && strcmp(temp->next->surname, beforeSurname) != 0)
        temp = temp->next;

    if (temp->next != NULL) {
        newPerson->next = temp->next;
        temp->next = newPerson;
        printf("Osoba unesena.\n");
    }
    else {
        printf("Greska, nema osobe s tim prezimenom!\n");
        free(newPerson);
    }

    return head;
}

// Sortiranje liste po prezimenima
Person* sort(Person* head)
{
    Person* current = NULL;
    Person* previous = NULL;
    Person* temp = NULL;
    Person* last = NULL;

    while (head != NULL && head->next != last)
    {
        previous = head;
        current = head->next;

        while (current->next != last)
        {
            if (strcmp(current->surname, current->next->surname) > 0)
            {
                temp = current->next;
                previous->next = temp;
                current->next = temp->next;
                temp->next = current;

                current = temp;
            }
            previous = current;
            current = current->next;
        }
        last = current;
    }

    printf("Lista je sortirana.\n");
    return head;
}

// Upis liste u datoteku
int write(Person* head)
{
    char filename[50];
    printf("Unesite ime datoteke u koje zelite upisati listu: ");
    scanf("%49s", filename);

    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    while (head != NULL) {
        fprintf(fp, "%s %s %d %d %d\n", head->name, head->surname, head->day, head->month, head->year);
        head = head->next;
    }

    fclose(fp);
    printf("Lista uspjesno spremljena u '%s'.\n", filename);
    return 0;
}

// Ucitavanje liste iz datoteke
Person* readFromFile()
{
    char filename[50];
    int counter = 0;
    Person* head = NULL;
    Person* P = NULL;
    Person* q = NULL;

    printf("Unesite ime datoteke iz koje zelite ucitat listu: ");
    scanf("%49s", filename);

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        return NULL;
    }

    // Brojanje linija u datoteci
    while (!feof(fp)) {
        if (fgetc(fp) == '\n')
            counter++;
    }
    rewind(fp);

    if (counter != 0) {
        for (int i = 0; i < counter; i++) {
            q = (Person*)malloc(sizeof(Person));
            if (!q) {
                printf("Greska u alokaciji memorije!\n");
                fclose(fp);
                // oslobodivanje vec alociranih elemenata
                while (head != NULL) {
                    Person* temp = head;
                    head = head->next;
                    free(temp);
                }
                return NULL;
            }

            if (fscanf(fp, "%19s %19s %d %d %d", q->name, q->surname, &q->day, &q->month, &q->year) != 5) {
                free(q);
                break;
            }

            q->next = NULL;

            if (head == NULL) {
                head = q;
                P = head;
            }
            else {
                P->next = q;
                P = P->next;
            }
        }
    }

    fclose(fp);
    printf("Lista ucitana iz '%s'.\n", filename);
    return head;
}