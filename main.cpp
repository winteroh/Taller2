//Taller estructure 2 - main
//Intento de conecta 4 asi d xistis probanding
#include "ConectaCuatro.h"
#include "Minimax.h"
#include "Records.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void DesignarDificultad(int* dificultad)
{
    int opcion;
    cout << "Qué dificultad quieres" << endl;
    cout << "1 ) Facil" << endl;
    cout << "2 ) Normal" << endl;
    cout << "3 ) Dificil " << endl;

    cin >> opcion;
	*dificultad = opcion;
	//*dificultad = respuesta - '0'-1;
}
void CrearPartida(char partida[tamaño][tamaño]){
	int i; int j;
	for(i=0;i<tamaño;i++){
		for(j=0;j<tamaño;j++){
			partida[i][j] = ' ';
		}
	}
}

int JuegaJugador(char partida[tamaño][tamaño],int numero_jugador,char ficha){
	char respuesta;
	int columna;

	ImprimirTablero(partida);
	printf("(Presione ESC para volver al menu inicial)\n");
	if (numero_jugador == 0){
		printf("Turno jugador: ");
	}
	else{
		printf("Turno jugador %d: ",numero_jugador);
	}
	respuesta = getche();
	if(respuesta == 27) return 1; // Parametro de salida
	columna = respuesta-'0'-1;
	if(columna <0 || columna>7){
		ImprimirTablero(partida);
		printf("\a");
		printf("Que columna es esa? Selecciona otra. (Presione ENTER para continuar)\n");
		return JuegaJugador(partida,numero_jugador,ficha);
	}
	if(partida[0][columna] != ' '){
		system("cls");
		ImprimirTablero(partida);
		printf("\a");
		printf("La columna %d esta llena! Selecciona otra. (Presione ENTER para continuar)\n",columna+1);
		return JuegaJugador(partida,numero_jugador,ficha);
	}
	AplicarTirada(partida,columna,ficha);
	return 0;
}

int JuegaCPU(char partida[N][N], int dificultad,char ficha){
	ImprimirTablero(partida);
	//printf("Valor heuristico del tablero actual: %lf\n",Heuristica(partida));
	printf("El rival esta pensando...\n");

	int columna = ElegirTirada(partida,dificultad);
	AplicarTirada(partida,columna,ficha);
	//system("PAUSE");
	return 0;
}
void Partida()
{
    char partida[tamaño][tamaño]; 
    int dificultad;
    CrearPartida(partida);
    DesignarDificultad(&dificultad);

    char persona[30][10]; int puntuacion[30];
	PrintearRecords(persona,puntuacion);
	int MIN_RECORD = puntuacion[(3-dificultad)*10-1];

	int contador_jugadas = 1;
	while(1){
		// Turno Jugador
		int EXIT = JuegaJugador(partida,0,'O');
		if(EXIT == 1){
			Menu();
			break;
		}
		if(VictoriaJugador(partida)){
			ImprimirTablero(partida);
			printf("\a");
			printf("Gana el jugador en %d jugadas! ",contador_jugadas);
			if (contador_jugadas< MIN_RECORD){
				NuevoRecord(contador_jugadas,dificultad);
				PantallaRecords();
			}
			else{
				printf("(Presione ENTER para continuar)");
				PantallaPrincipal();
			}
			break;
		}
		// Turno CPU
		JuegaCPU(partida,dificultad,'X');
		if(VictoriaCPU(partida)){
			ImprimirTablero(partida);
			printf("\a");
			printf("Gana el CPU! (Presione ENTER para continuar)");
			Menu();
			break;
		}

		// Si se llena el tablero
		if(Posibilidades(partida)==0){
			ImprimirTablero(partida);
			printf("\a");
			printf("Se acabo el juego. Empate. (Presione ENTER para continuar)");
			Menu();
			break;
		}

		contador_jugadas++;
	}
}
void MostrarPuntuaciones(){
	int i;
	char persona[30][10]; int puntuacion[30];
	PrintearRecords(persona,puntuacion);
	printf("################### HIGHSCORES ###################\n");
	printf("\n     DIFICIL    |     NORMAL     |      FACIL     \n");
	printf("--------------------------------------------------\n");
	for (i=0;i<10;i++){
		printf(" %-10s %3d | %-10s %3d | %-10s %3d\n",persona[i],puntuacion[i],persona[10+i],puntuacion[10+i],persona[20+i],puntuacion[20+i]);
	}
	Menu();
}

void Menu()
{
    int respuesta;
    cout << "Bienvenido al ConectaCuatro que quizas ni funcione :c" << endl;
    cout << "1) Jugar contra la IA" << endl;
    cout << "2) Ver puntuaciones" << endl;
    cout << "3) Continuar partida" << endl;
    cout << "4) Salir " << endl;

    cin >> respuesta;

    if(respuesta == 1)
    {
        Partida();
    }
    else if(respuesta == 2)
    {
        MostrarPuntuaciones();
    }
}
int main() 
{
    Menu();
}