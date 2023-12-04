# Taller2
Hola Profesor D: Espero teniendo un buen dia
Mis decision de diseño fueron bastante simples, ya que me enfoque mas en el analisis de minimax, ya que era una nueva logica que estabamos trabajando donde el tablero se muestra de esta forma (Donde 2 vendria a ser el jugador, mientras que el 1 la IA)
|0|0|0|0|0|0|0|                         
|0|0|0|0|0|0|0|
|0|0|0|0|0|0|0|
|0|0|0|0|0|0|0|
|0|0|0|0|0|0|0|
|0|2|0|0|0|1|0|
El menu se muestra asi:
Bienvenido al Menu del ConectaCuatro mas fome :D 
1) Jugar vs IA
2) Cargar partida
3) Partidas guardadas
4) Salir
1
Seleccione la dificultad:
1. Facil
2. Medio
3. Dificil
Donde se pueden utilizar todas las funciones aplicadas ahi, pero quizas el cargar partida presente algun error minimo.

Implementacion: 
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
Estas fueron algunas funciones que me salvaron, ya que podia ir realizando acciones ahi mismo con el tablero para que fuera mucho mas dinamico, Minimax fue una de las mas importante para poder crear el arbol, pero tambien importo esta
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
Donde obviamente la estructura Nodo es la primordial para que todo funcione.

Comparacion de Minimax sin poda y con poda

Minimax sin poda = El algoritmo va explorando todas las hojas una por una, el cual obviamente se va demorando mucho mas. Entonces no es efectivo realizar esto ya que no tendriamos una optimizacion optima. 
Minimax con poda = Poda alfa-beta sin duda es una mejora a este sistema. Reduce el numero de nodos evaluados, eliminando algunas ramas de los arboles que no sirvan entonces no termina afectando en nada. Entonces reduce en consideracion el tiempo efectuado, otorgando mucha calidad.
