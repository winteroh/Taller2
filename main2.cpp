#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
//Francisco Astudillo Intento numero 3 :D
const int filas = 6;
const int columnas = 7;
const int NumJugador = 2;
const int NumIA = 1;

using namespace std;

struct NodoTablero 
{
    int tablero[filas][columnas];
    int columna;
    int valor;
    vector<NodoTablero*> hijos;

    //Constructor
    NodoTablero(int col) : columna(col), valor(0) 
    {
        // No es necesario inicializar el tablero aquí
    }

    //Destructor
    ~NodoTablero() 
    {
        for (auto hijo : hijos) {
            delete hijo;
        }
    }
};

//Funciones wonitas por favor funcionen no me fallen esta vez q ya llevo como 3 intentos
int Minimax(NodoTablero* nodo, int jugador, int profundidad, int alfa, int beta);
int JugadaOptima(int tablero[filas][columnas], int jugador);
pair<int, int> VerificarLinea(int tablero[filas][columnas], int n, int jugador);
bool TerminoJuego(int tablero[filas][columnas], int jugador);
void PrintearTablero(int tablero[filas][columnas]);
bool Movimiento(int tablero[filas][columnas], int columna, int jugador);
int TurnoHumano(int tablero[filas][columnas]);
int TurnoIA(int tablero[filas][columnas], int dificultad);
void HacerHijos(NodoTablero* nodo, int jugador);
void GuardarPartida(int tablero[filas][columnas], int jugador, int dificultad);
bool CargarPartida(int tablero[filas][columnas], int& jugador, int& dificultad);
void PartidasGuardadas();

int Minimax(NodoTablero* nodo, int jugador, int profundidad, int alfa, int beta) {
    if (TerminoJuego(nodo->tablero, jugador) || profundidad == 0) {
        return JugadaOptima(nodo->tablero, jugador);
    }
    //Minimax con alfa, beta para ir viendo las rutas optimas
    HacerHijos(nodo, jugador);

    int max_puntuacion = INT_MIN;

    for (auto hijo : nodo->hijos) {
        int puntuacion = -Minimax(hijo, jugador * -1, profundidad - 1, -beta, -alfa);

        if (puntuacion > max_puntuacion) {
            max_puntuacion = puntuacion;
            nodo->columna = hijo->columna;
            nodo->valor = max_puntuacion;
        }

        if (max_puntuacion >= beta) {
            break;
        }

        if (max_puntuacion > alfa) {
            alfa = max_puntuacion;
        }
    }

    return max_puntuacion;
}

int JugadaOptima(int tablero[filas][columnas], int jugador) 
{
    auto n2 = VerificarLinea(tablero, 2, jugador).second;
    auto n3 = VerificarLinea(tablero, 3, jugador).second;
    auto n4 = VerificarLinea(tablero, 4, jugador).second;

    int valor_jugada = 4 * n2 + 9 * n3 + 1000 * n4;
    return valor_jugada;
}
pair<int, int> VerificarLinea(int tablero[filas][columnas], int n, int jugador) 
{
        //Ver si el movimiento de la linea se puede realizar
    int ganador = 0;
    int num_lineas = 0;
    int lineas_posibles = 8 - n;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Buscar línea horizontal
            if (j <= columnas - n) {
                bool linea_horizontal = true;
                for (int k = 0; k < n; ++k) {
                    if (tablero[i][j + k] != jugador) {
                        linea_horizontal = false;
                        break;
                    }
                }
                if (linea_horizontal && (j == 0 || tablero[i][j - 1] != jugador) &&
                    (j + n == columnas || tablero[i][j + n] != jugador)) {
                    ganador = jugador;
                    num_lineas++;
                }
            }

            // Buscar línea vertical
            if (i <= filas - n) {
                bool linea_vertical = true;
                for (int k = 0; k < n; ++k) {
                    if (tablero[i + k][j] != jugador) {
                        linea_vertical = false;
                        break;
                    }
                }
                if (linea_vertical && (i == 0 || tablero[i - 1][j] != jugador) &&
                    (i + n == filas || tablero[i + n][j] != jugador)) {
                    ganador = jugador;
                    num_lineas++;
                }
            }

            // Buscar líneas diagonales
            if (i <= filas - n && j <= columnas - n) {
                bool diagonal1 = true;
                bool diagonal2 = true;
                for (int k = 0; k < n; ++k) {
                    if (tablero[i + k][j + k] != jugador) {
                        diagonal1 = false;
                    }
                    if (tablero[i + k][j + n - k - 1] != jugador) {
                        diagonal2 = false;
                    }
                }
                if (diagonal1 && (i == 0 || j == 0 || tablero[i - 1][j - 1] != jugador) &&
                    (i + n == filas || j + n == columnas || tablero[i + n][j + n] != jugador)) {
                    ganador = jugador;
                    num_lineas++;
                }
                if (diagonal2 && (i == 0 || j == columnas - n || tablero[i - 1][j + n] != jugador) &&
                    (i + n == filas || j - 1 == 0 || tablero[i + n][j - 1] != jugador)) {
                    ganador = jugador;
                    num_lineas++;
                }
            }
        }
    }
    return make_pair(ganador, num_lineas);
}

bool TerminoJuego(int tablero[filas][columnas], int jugador) {
    auto ganador_info = VerificarLinea(tablero, 4, jugador);

    int ganador = ganador_info.first;

    if (ganador != 0) 
    {
        return true;
    }

    // Verificar si el tablero está lleno
    for (int i = 0; i < filas; ++i) 
    {
        for (int j = 0; j < columnas; ++j) {
            if (tablero[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

void mostrarTablero(int tablero[filas][columnas])
{
    //Printea el tablero solito
    for(int i = 0; i < filas; i++){
        cout << "|";
        for(int j = 0; j < columnas; j++){
            cout<<tablero[i][j];
            cout << "|";
        }
        cout<<endl;
    }
    cout<<endl;
}

void PrintearTablero(int tablero[filas][columnas])
{
    for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++)
            {
                if(tablero[i][j] = 0)
                {
                        cout<<"[ ] ";
                }
                else if(tablero[i][j] = 1)
                {
                        cout<<"X ";
                }
                else if(tablero[i][j] = 2)
                {
                       cout<<"O ";
                }
                else
                {
                    
                }
            }
            cout<<endl;
        }
        cout<<endl;
}

bool Movimiento(int tablero[filas][columnas],  int columna, int jugador)
{
        for(int fila = filas - 1; fila >= 0; fila--)
        {
            if (tablero[fila][columna] == 0) 
            {
                tablero[fila][columna] = jugador;
                return true;
            }
        }
        return false;
}

int TurnoHumano(int tablero[filas][columnas]) 
{
    int col;
    bool movimiento_valido = false;

    while (!movimiento_valido) 
    {
        cout << "Columna (0 para salir, -1 para guardar): ";
        cin >> col;

        if (col == -1) {
            GuardarPartida(tablero, NumJugador, 0);
            cout << "Partida guardada exitosamente. Volviendo al menú principal." << endl;
            return col;
        } else if (col == 0 || col < 1 || col > columnas || !Movimiento(tablero, col - 1, NumJugador)) {
            cout << "Movimiento ilegal. Intente de nuevo." << endl;
        } else {
            movimiento_valido = true;
        }
    }
    return col - 1;
}

int TurnoIA(int tablero[filas][columnas], int dificultad) {
    srand(time(nullptr));

    int col;
    //modo facil
    if(dificultad == 1)
    {
        col = rand() % columnas;
        while (tablero[0][col] != 0);

            Movimiento(tablero, col, NumIA);
            return col;
    }
    if(dificultad == 2)
    {
        col = rand() % columnas;
            if (tablero[0][col] == 0) 
            {
                Movimiento(tablero, col, NumIA);
                return col;
            }
    }
    if(dificultad == 3)
    {
        NodoTablero* nodo = new NodoTablero(0);
            nodo->valor = INT_MIN;

            for (int i = 0; i < columnas; ++i) 
            {
                if (tablero[0][i] == 0) 
                {
                    NodoTablero* hijo = new NodoTablero(i);
                    hijo->valor = JugadaOptima(tablero, NumIA);
                    Movimiento(hijo->tablero, i, NumIA);
                    nodo->hijos.push_back(hijo);
                }
            }

            for (auto hijo : nodo->hijos) 
            {
                int puntuacion = -Minimax(hijo, NumIA, 3, INT_MIN, INT_MAX);
                if (puntuacion > nodo->valor) 
                {
                    nodo->valor = puntuacion;
                    col = hijo->columna;
                }
            }

            Movimiento(tablero, col, NumIA);
            delete nodo;

            return col;
    }

    return -1; // Error
}

void HacerHijos(NodoTablero* nodo, int jugador) 
{
    for (int col = 0; col < columnas; ++col) 
    {
        if (nodo->tablero[0][col] == 0) {
            NodoTablero* hijo = new NodoTablero(col);
            Movimiento(hijo->tablero, col, jugador);
            hijo->valor = JugadaOptima(hijo->tablero, jugador);
            nodo->hijos.push_back(hijo);
        }
    }
}

void GuardarPartida(int tablero[filas][columnas], int jugador, int dificultad) {
    ofstream archivo("partida_guardada.txt");

    if (archivo.is_open()) {
        archivo << jugador << " " << dificultad << endl;

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                archivo << tablero[i][j] << " ";
            }
            archivo << endl;
        }

        archivo.close();
        cout << "Partida guardada exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo para guardar la partida." << endl;
    }
}
bool CargarPartida(int tablero[filas][columnas], int& jugador, int& dificultad) {
        ifstream archivo("partida_guardada.txt");

    if (archivo.is_open()) {
        archivo >> jugador >> dificultad;

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                archivo >> tablero[i][j];
            }
        }

        archivo.close();
        return true;
    } else {
        cout << "No se pudo abrir el archivo para cargar la partida." << endl;
        return false;
    }
}
void PartidasGuardadas() {
    ifstream archivo("partida_guardada.txt");

    if (archivo.is_open()) {
        string linea;

        while (getline(archivo, linea)) {
            cout << linea << endl;
        }

        archivo.close();
    } else {
        cout << "No hay partidas guardadas." << endl;
    }
}
int main()
{
    int tablero[filas][columnas] = {{0}};

    int jugador = NumJugador;
    int IA = NumIA;
    int dificultad;
    string ganador = "flop";

    while(true)
    {
        cout << "Bienvenido al Menu del ConectaCuatro mas fome :D " << endl;
		cout << "1) Jugar vs IA" << endl;
		cout << "2) Ver Puntos." << endl;
        cout << "3) Partidas guardadas" << endl;
		cout << "4) Salir" << endl;

		int opcion; 
        cin >> opcion;

        auto ganador_info = VerificarLinea(tablero, 4, jugador);
        int g = ganador_info.first;

        
		if(opcion == 1)
        {
                cout << "Seleccione la dificultad:" << endl;
                cout << "1. Facil" << endl;
                cout << "2. Medio" << endl;
                cout << "3. Dificil" << endl;
                cout << "Ingrese su opcion: ";
                cin >> dificultad;

                if (dificultad < 1 || dificultad > 3) 
                {
                    cout << "Opcion no valida. Seleccionando dificultad facil por defecto." << endl;
                    dificultad = 1;
                }

                // Reiniciar variables relacionadas con la partida
                jugador = NumJugador;
                ganador = "Tablas";
                // Reiniciar el tablero
                for (int i = 0; i < filas; i++) 
                {
                    for (int j = 0; j < columnas; j++) 
                    {
                        tablero[i][j] = 0;
                    }
                }

                    // Pelea IA VS Humano
                while (true) 
                {
                    mostrarTablero(tablero);
               
                    // Turno del jugador humano
                    int col = TurnoHumano(tablero);
               
                    if (col == -1) 
                    {
                        GuardarPartida(tablero, jugador, dificultad);
                        //salir = true;
                        break;
                    }

                    // Verificar si el jugador humano ha ganado después de su movimiento
                    ganador_info = VerificarLinea(tablero, 4, NumJugador);
                    g = ganador_info.first;
                    if (g != 0) 
                    {
                        ganador = "Jugador";
                        break;
                    }

                     // Turno de la IA
                    int movIA = TurnoIA(tablero, dificultad);
                    Movimiento(tablero, movIA, NumIA);
               
                    // Verificar si la IA ha ganado después de su movimiento
                    ganador_info = VerificarLinea(tablero, 4, NumIA);
                    g = ganador_info.first;
                    if (g != 0) 
                    {
                        ganador = "Ordenador";
                        break;
                    }
               
                    if (TerminoJuego(tablero, NumJugador)) 
                    {
                        break;
                    }
                }
                    //PROBLEMA ANTES DE AKI
                    PrintearTablero(tablero);


                  ganador_info = VerificarLinea(tablero, 4, jugador);
                 g = ganador_info.first;

                   if (g == jugador) 
                   {
                    ganador = "Jugador";
                    } 
                    else if (g == NumJugador) 
                    {
                    ganador = "Ordenador";
                    } 
                    else 
                    {
                    ganador = "Tablas";
                    }

                 cout << "Ganador: " << ganador << endl;
                 break;
		} 
		else if(opcion == 2)
        {
            // Cargar partida
                if (CargarPartida(tablero, jugador, dificultad)) 
                {
                    cout << "Partida cargada exitosamente." << endl;
                } else {
                    cout << "No hay partidas guardadas o no se pudo cargar la partida." << endl;
                }
                break;
		} 
        else if(opcion == 3)
        {
           // Ver partidas guardadas
                PartidasGuardadas();
                break;
        }
		else if(opcion == 4){
			cout << "chao chao" << endl;
			break;
		} else 
        {
			cout << "Opcion invalida" << endl;
		}
    }
    return 0;
}