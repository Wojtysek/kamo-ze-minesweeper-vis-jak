#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int hra[10][10];
int hra_checked[10][10];
int data[10][10];

int x = 0;
int y = 0;

int radek = 0;
int sloupec = 0;

int var1;
int var2;

int count = 0;

void vypis_dat() {
	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf(" %d ", i);
	}
	printf("\n\r");
	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf("---");
	}
	printf("\n\r");

	for (int i = 1; i <= 10; i++) {
		printf("%2d ", i);
		printf("|");
		for (int j = 0; j <= 9; j++) {

			if (data[i-1][j] == -1) {
				printf(" M ");
			}
			else {
				printf(" %d ", data[i-1][j]);
			}
		}
		printf("|\n\r");
	}
	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf("---");
	}
	printf("\n\r");
}

void vypis_hry() {

	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf(" %d ", i);
	}
	printf("\n\r");
	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf("---");
	}
	printf("\n\r");

	for (int i = 1; i <= 10; i++) {
		printf("%2d ", i);
		printf("|");
		for (int j = 0; j < 10; j++) {

			if (hra[i-1][j] >= 0) {

				printf(" %d ", (hra[i-1][j]));
			}
			else if(hra[i-1][j] == -2){
				printf(" * ");
			}
			else {
				continue;
			}
		}
		printf("|\n\r");
	}
	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf("---");
	}
	printf("\n\r");
}

int main() {

	srand(time(NULL));
	//zapis pole dat + generovani 20 min
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			data[i][j] = 0;
		}
	}
	for (int i = 0; i < 10; i++) {   //zapis do pole zkontrolovanych hodnot
		for (int j = 0; j < 10; j++) {
			hra_checked[i][j] = 0;
		}
	}
	int miny = 0;
	int max_miny = 20;
	while (miny < max_miny) {
		int y = rand() % 10;
		int x = rand() % 10;
		if (data[y][x] == 0) {
			data[y][x] = -1;
			miny++;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (data[i][j] == -1) continue;   //hledame miny

			int pocet = 0;
			for (int plus_i = -1; plus_i <= 1; plus_i++) {   //pocitame 
				for (int plus_j = -1; plus_j <= 1; plus_j++) {
					int ii = i + plus_i, jj = j + plus_j;
					if (ii >= 0 && ii < 10 && jj >= 0 && jj < 10) {
						if (data[ii][jj] == -1) {  //pokud mina tak pricteme k poctu jedna
							pocet++;
						}
					}
				}
			}
			data[i][j] = pocet; //zapiseme do pole dat
		}
	} 
	//------------------------------------
	//generovani prvniho prazdneho pole

	printf("--------------- M I N E S W E E P E R --------------\n\r");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			hra[i][j] = -2;
		}
	}

	printf("    ");
	for (int i = 1; i <= 10; i++) {
		printf(" %d ", i);
	}
	printf("\n\r");
	printf("    ");
	for (int i = 0; i <= 9; i++) {
		printf("---");
	}
	printf("\n\r");

	for (int i = 1; i <= 10; i++) {
		printf("%2d ", i);
		printf("|");
		for (int j = 0; j <= 9; j++) {

			if (hra[i-1][j] == -2) {
				printf(" * ");
			}
		}
		printf("|\n\r");
	}
	printf("    ");
	for (int i = 0; i <= 9; i++) {
		printf("---");
	}
	printf("\n\r");

	//zacatek hry
	
	while (1) {
		printf("zadej cislo sloupce: ");
		scanf_s("%d", &var1);
		printf("zadej cislo radku: ");
		scanf_s("%d", &var2);

		radek = var1 - 1;
		sloupec = var2 - 1;


		if ((radek == -1) || (sloupec == -1)) {  //zobrazeni všech min
			vypis_dat();
			break;
		}
		else if(data[sloupec][radek] == -1){  //trefa miny
			vypis_dat();
			printf("\n\r");
			printf("BOOM! trefil si minu\n\r");
			break;
		}
		else if (hra_checked[sloupec][radek] >= 10) {
			printf("\n\r");
			printf("tato souradnice je jiz odkryta!\n\r");
			vypis_hry;
			continue;
		}
		else {
			hra[sloupec][radek] = data[sloupec][radek];
			hra_checked[sloupec][radek] = data[sloupec][radek] + 10;  //kontrola pouzitych souradnic

			printf("pocet min v okoli: %d\n\r", hra[sloupec][radek]);
			vypis_hry();
			count++;
		}
	}
	printf("---------------- !!! K O N E C   H R Y !!! -----------------\n\r");
	printf("\n\r");
	printf("vase skore: %d/80\n\r", count);
}