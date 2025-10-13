#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BROJ_BODOVA 75

// Definicija strukture koja opisuje jednog studenta
typedef struct {
	char ime[50];
	char prezime[50];
	int aps_br_bodova;
	float rel_br_bodova;
}_Student;

// Deklaracija funkcije koja broji koliko redaka ima u datoteci
int koliko_redaka(FILE*);

// Deklaracija funkcije koja uèitava podatke o studentima iz datoteke
_Student* upis_studenata(_Student*, FILE*, int);

int main() {
	int broj_redaka;
	
	// Otvaranje datoteke "studenti.txt" za èitanje
	FILE* fp = fopen("studenti.txt", "r");
	_Student* s;

	broj_redaka = koliko_redaka(fp);
	rewind(fp);

	// Dinamièka alokacija memorije za niz struktura _Student
	s = malloc(broj_redaka * sizeof(_Student));

	// Uèitavanje podataka o studentima iz datoteke
	s = upis_studenata(s, fp, broj_redaka);

	printf("%d", broj_redaka);
}

// Funkcija koja broji koliko redaka ima u datoteci 
int koliko_redaka(FILE* fp) {
	int brojac = 0;
	char string[100];

	// Èitanje svake linije dok ne doðe do kraja datoteke
	while (fgets(string, 100, fp)) {
		brojac++;
	}
	return brojac;
	// Vraæa broj redova
}

// Funkcija koja uèitava podatke o studentima iz datoteke u niz struktura
_Student* upis_studenata(_Student* s, FILE* fp, int broj_redaka) {
	for (int i = 0; i < broj_redaka; i++) {
		fscanf(fp, "%s %s\t\t%d\n", s[i].ime, s[i].prezime, &s[i].aps_br_bodova);
		s[i].rel_br_bodova = ((float)s[i].aps_br_bodova / 75) * 100;
	}

	// Ispis podataka o svakom studentu
	for (int i = 0; i < broj_redaka; i++) {
		printf("%s %s\t\t%d\t%.2f\n", s[i].ime, s[i].prezime, s[i].aps_br_bodova, s[i].rel_br_bodova);
	}
}