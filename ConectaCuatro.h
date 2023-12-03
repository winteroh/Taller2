#include <iostream>
#pragma once
#define tamaño 8
#include <stdio.h>
#include <stdlib.h>
//usamos define para definir algo en este caso que el tamaño sera 8
//tambien usare define para definir los simbolos de player y cpu
#define cpu 'X'
#define player 'O'

using namespace std;

class ConectaCuatro 
{
	//funciones porfavor funcionen D:	
    public:
		ConectaCuatro();
        void RellenarForma(char tablero[tamaño][tamaño]);
        int Posibilidades(char tablero[tamaño][tamaño]);
        int VictoriaCPU(char tablero[tamaño][tamaño]);
        int VictoriaPlayer(char tablero[tamaño][tamaño]);
        void HacerTirada(char tablero[tamaño][tamaño], int columna, char movimiento);
        double VerificarVictoria(char tablero[tamaño][tamaño]);
};

ConectaCuatro :: ConectaCuatro()
{

}
void ConectaCuatro :: RellenarForma(char tablero[tamaño][tamaño])
{
    //Hacer forma del tablero
   int i; int j;

	printf("  ");for(i=0;i<tamaño;i++) printf("%d   ",i+1);printf("\n");
	printf("  ");for(i=0;i<tamaño;i++) printf("v   ");printf("\n");

	for(i=0;i<tamaño;i++)
    {
		printf(" ");for(j=0;j<tamaño;j++) printf("--- ");printf("\n");
		printf("|");for(j=0;j<tamaño;j++) printf(" %c |",tablero[i][j]);printf("\n");
	}

	printf(" ");for(i=0;i<tamaño;i++) printf("--- ");printf("\n");
}

int ConectaCuatro :: Posibilidades(char tablero[tamaño][tamaño])
{
    int j;
	int cont = 0;

	for(j=0;j<tamaño;j++){
		if(tablero[0][j] == ' '){
			cont += 1;
		}
	}

	return cont;
}
int ConectaCuatro :: VictoriaCPU(char tablero[tamaño][tamaño])
{
    int i; int j;
	// Chequeo horizontal
	for(i=0;i<tamaño;i++){
		for(j=0;j<(tamaño-3);j++){
			if(tablero[i][j] == cpu){
				if(tablero[i][j+1] == cpu){
					if(tablero[i][j+2] == cpu){
						if(tablero[i][j+3] == cpu){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo vertical
	for(j=0;j<tamaño;j++){
		for(i=0;i<(tamaño-3);i++){
			if(tablero[i][j] == cpu){
				if(tablero[i+1][j] == cpu){
					if(tablero[i+2][j] == cpu){
						if(tablero[i+3][j] == cpu){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal principal
	for(i=0;i<(tamaño-3);i++){
		for(j=0;j<(tamaño-3);j++){
			if(tablero[i][j] == cpu){
				if(tablero[i+1][j+1] == cpu){
					if(tablero[i+2][j+2] == cpu){
						if(tablero[i+3][j+3] == cpu){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal contraria
	for(i=0;i<5;i++){
		for(j=tamaño-1;j>2;j--){
			if(tablero[i][j] == cpu){
				if(tablero[i+1][j-1] == cpu){
					if(tablero[i+2][j-2] == cpu){
						if(tablero[i+3][j-3] == cpu){
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

int ConectaCuatro :: VictoriaPlayer(char tablero[tamaño][tamaño])
{
    int i; int j;
	// Chequeo horizontal
	for(i=0;i<tamaño;i++){
		for(j=0;j<(tamaño-3);j++){
			if(tablero[i][j] == player){
				if(tablero[i][j+1] == player){
					if(tablero[i][j+2] == player){
						if(tablero[i][j+3] == player){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo vertical
	for(j=0;j<tamaño;j++){
		for(i=0;i<(tamaño-3);i++){
			if(tablero[i][j] == player){
				if(tablero[i+1][j] == player){
					if(tablero[i+2][j] == player){
						if(tablero[i+3][j] == player){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal principal
	for(i=0;i<(tamaño-3);i++){
		for(j=0;j<(tamaño-3);j++){
			if(tablero[i][j] == player){
				if(tablero[i+1][j+1] == player){
					if(tablero[i+2][j+2] == player){
						if(tablero[i+3][j+3] == player){
							return 1;
						}
					}
				}
			}
		}
	}
	// Chequeo diagonal contraria
	for(i=0;i<5;i++){
		for(j=tamaño-1;j>2;j--){
			if(tablero[i][j] == player){
				if(tablero[i+1][j-1] == player){
					if(tablero[i+2][j-2] == player){
						if(tablero[i+3][j-3] == player){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}


void ConectaCuatro :: HacerTirada(char tablero[tamaño][tamaño], int columna, char movimiento)
{
    int i;
	for(i=0;i<tamaño;i++)
    {
        //verificar si esta vacia
		if(tablero[tamaño-1-i][columna]==' ')
        {
			tablero[tamaño-1-i][columna] = movimiento;
			break;
		}
	}
}

double ConectaCuatro :: VerificarVictoria(char tablero[tamaño][tamaño])
{
    if (VictoriaCPU(tablero)) 
    {
        return 100;
    }
	if (VictoriaPlayer(tablero)) 
    {
        return -100;
    }
	else 
    {
        return 0;
    }
        
}