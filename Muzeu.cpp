#include <iostream>

//structura informatiei utile dintr-un nod
struct Muzeu {
	char* nume;
	int nrExpozitii;
	float pretBilet;
};

//structura pt nodurile listei simple inlantuite
struct Nod {
	Muzeu info; //informatia utila dintr-un nod
	Nod* next; //pointer catre nodul urmator al listei
};


//functia de citire a unui Muzeu de la tastatura
Muzeu citireMuzeu() {
	Muzeu m; //am declarat un nou Muzeu (o instantiere a unui Muzeu)
	char buffer[20]; //vector alocat static de char in care citim numele
	printf("Nume: "); 
	scanf("%s", buffer);//se citeste de la tastatura in buffer, s este specificatorul de format pt sirul de caractere
	m.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1)); //se aloca memorie cu malloc (in loc de new)
	strcpy(m.nume, buffer); //se copiaza din buffer in numele din muzeu

	printf("Numar expozitii: ");
	scanf("%d", &m.nrExpozitii); //d este specificatorul de format pt int

	printf("Pretul biletului: ");
	scanf("%f", &m.pretBilet); //f este specificatorul de format pt float

	return m;
}

//functia de afisare a unui Muzeu
void afisareMuzeu(Muzeu m) {
	printf("Muzeul %s are %d expozitii iar pretului biletului este %.2f\n", m.nume, m.nrExpozitii, m.pretBilet); //%.2f ca sa arate doar 2 zecimale
}

//functia de copiere Muzeu
Muzeu copiereMuzeu(Muzeu m) {
	Muzeu copie;
	copie.nume = (char*)malloc(sizeof(char)*(strlen(m.nume) + 1)); //strlen .....+1 este doar la siruri!!!
	strcpy(copie.nume, m.nume);

	copie.nrExpozitii = m.nrExpozitii;

	copie.pretBilet = m.pretBilet;

	return copie;
}

//inserare inceput
Nod* inserareInceput(Nod* cap, Muzeu m) { //cap reprezinta lista si m reprezinta informatia utila pt nodul nou inserat in lista
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //alocam memorie pt un nod nou
	nou->info = copiereMuzeu(m); //copiem informatia utila in noul nod
	nou->next = cap; //noul nod va pointa catre vechiul cap
	return nou; //noul nod va fi returnat ca nou cap al listei
}

//inserare la final
Nod* inserareSfarsit(Nod* cap, Muzeu m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //alocam memorie pt un nod nou
	nou->info = copiereMuzeu(m); //copiem informatia utila in noul nod
	nou->next = NULL; //noul nod va pointa catre NULL, il marcam ca fiind ultimul din lista
	if(cap) { //daca exista cap (e acelasi lucru cu cap == true)
		Nod* p = cap; //se creaza un nou pointer catre capul listei pt a parcurge lista fara a o altera
		while (p->next) { //se cauta ultimul nod din lista, acesta are p->next = NULL
			p = p->next; //daca exista un nod urmator, p va pointa catre acest nod, daca nu exista va iesi, p ramanand ultimul nod
		}
		p->next = nou; //fostul ultim nod (cel pe care l-a gasit p) va pointa catre noul nod
	}
	else { //daca nu exista lista
		cap = nou; //noul nod este singurul nod si deci primul din lista 
	}
	return cap; //returnam capul listei
}

//inserare sortata
Nod* inserareSortata(Nod* cap, Muzeu m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = copiereMuzeu(m);
	if (cap) { //merge si fara acest if
		Nod* p = cap;
		while (p->next && p->next->info.nrExpozitii < m.nrExpozitii) { //daca nu avem p->next aici, il insereaza pe 4 dupa 5 de ex, in loc sa insereze inainte
			p = p->next;
		}
		if (p->next) { //merge si cu if(p) aici
			nou->next = p->next;
			p->next = nou;
		}
		else {
			cap = inserareSfarsit(cap, m);
		}
	}
	return cap;
}

//functie de afisare a listei
void afisareLista(Nod* cap) {
	Nod* p = cap; //se creaza un nou pointer catre capul listei pt a parcurge lista fara a o altera
	while (p) { //cat timp exista noduri in lista
		afisareMuzeu(p->info); //se afiseaza info utila din nod
		p = p->next; //se trece la urmatorul nod
	}
}

//functie de dezalocare memorie pentru lista
void stergereLista(Nod* cap) {
	while (cap) { //cat timp exista exista noduri in lista
		free(cap->info.nume); //se dezaloca pentru char* nume, din fiecare nod (doar pt nume, pt ca e alocat dinamic)
		Nod* temp = cap; //se salveaza adresa nodului curent
		cap = cap->next; //se trece la urmatorul nod
		free(temp); //se dezaloca memoria pentru nodul salvat
	}
}


void main() {

	Nod* listaSimpla = NULL; //am creat pointerul cap (listaSimpla este aici capul)
	listaSimpla = inserareInceput(listaSimpla, citireMuzeu()); //am inserat un Muzeu la inceput
	listaSimpla = inserareInceput(listaSimpla, citireMuzeu()); //am inserat un alt Muzeu la inceput
	listaSimpla = inserareSfarsit(listaSimpla, citireMuzeu()); //am inserat un Muzeu la sfarsit (listaSimpla pt ca functia inserareSfarsit returneaza cap)
	listaSimpla = inserareSortata(listaSimpla, citireMuzeu());
	listaSimpla = inserareSortata(listaSimpla, citireMuzeu());


	afisareLista(listaSimpla); //apelam functia de afisare lista

	stergereLista(listaSimpla);//apelam functia de dezalocare memorie
	listaSimpla = NULL;
}