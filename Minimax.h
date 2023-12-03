
#include <iostream>
#include "ConectaCuatro.h"
#include <stdio.h>

//Definir nodo para trabajar con arbol
typedef struct nodo
        {
	        struct nodo **hijos;
	        int *movimientos;
	        int n_hijos;
	        char tablero[tamaño][tamaño];
	        double valor;
	        int nivel;
        } Nodo;


class Minimax 
{

    public:
        void CopiarTablero(char tablero1[tamaño][tamaño],char tablero2[tamaño][tamaño]);
        Nodo CrearNodo(char tablero[tamaño][tamaño],int nivel,int dificultad );
        void CrearNivel(Nodo *Padre,char ficha ,int dificultad );
        void CrearDobleNivel(Nodo *raiz,int dificultad );
        void CrearArbol(Nodo *raiz,int profundidad ,int dificultad );
        void BorrarArbol(Nodo *raiz);
        void ImprimirArbol(Nodo *raiz);
        void ValorarHojas(Nodo *raiz);
        void MiniMax(Nodo *raiz);
        //Para que la IA pueda hacer tiradas
        int ElegirTirada(char partida[tamaño][tamaño],int dificultad);
};

void Minimax :: CopiarTablero(char tablero1[tamaño][tamaño],char tablero2[tamaño][tamaño])
{
    int i; int j;
	for(i=0;i<tamaño;i++){
		for(j=0;j<tamaño;j++){
			tablero2[i][j] = tablero1[i][j];
		}
	}
}

Nodo Minimax :: CrearNodo(char tablero[tamaño][tamaño],int nivel,int dificultad)
{
    ConectaCuatro wa();
    int i; int j=0;
	Nodo p;
	p.nivel = nivel;
	CopiarTablero(tablero,p.tablero);
    p.n_hijos = wa.Posibilidades(tablero);
	p.valor = 0;
	if (wa.VictoriaCPU(p.tablero) || wa.VictoriaPlayer(p.tablero) || p.nivel == 2*dificultad+2)
    {
        p.n_hijos = 0;
	}

	if (p.n_hijos != 0)
    {
        p.hijos = (Nodo **) malloc(p.n_hijos*sizeof(Nodo *));
        p.movimientos = (int *) malloc(p.n_hijos*sizeof(int));
        for(i=0;i<tamaño;i++){
            if(tablero[0][i] == ' '){
                p.movimientos[j] = i;
                j += 1;
            }
        }
	}
	else{
        p.hijos = NULL;
        p.movimientos = NULL;
	}


	return p;
}

void Minimax :: CrearNivel(Nodo *Padre,char ficha,int dificultad)
{
    int i;
	Nodo *Hijo;

	for(i=0;i<Padre->n_hijos;i++)
    {
		Hijo = (Nodo *) malloc(sizeof(Nodo));
		CopiarTablero(Padre->tablero,Hijo->tablero);
		HacerTirada(Hijo->tablero,Padre->movimientos[i],ficha);
		*Hijo = CrearNodo(Hijo->tablero,Padre->nivel+1,dificultad);
		Padre->hijos[i] = Hijo;
	}
}

void Minimax :: CrearDobleNivel(Nodo *raiz,int dificultad)
{
    int i;
	CrearNivel(raiz,player,dificultad);
	for(i=0;i<raiz->n_hijos;i++){
		CrearNivel(raiz->hijos[i],player,dificultad);
	}
}

void Minimax :: CrearArbol(Nodo *raiz,int profundidad ,int dificultad )
{
    CrearDobleNivel(raiz,dificultad);
	if(profundidad == 0)
    {
        return;
    } 
	else
    {
		int i; int j;
		for(i=0;i<raiz->n_hijos;i++){
			for(j=0;j<raiz->hijos[i]->n_hijos;j++){
				CrearArbol(raiz->hijos[i]->hijos[j],profundidad-1,dificultad);
			}
		}
	}
	return;
}

void Minimax :: BorrarArbol(Nodo *raiz)
{
    if(raiz->n_hijos == 0){
        free(raiz);
	}
	else{
        int i;
        for (i=0;i<raiz->n_hijos;i++){
            BorrarArbol(raiz->hijos[i]);
        }
        free(raiz->hijos);
        free(raiz->movimientos);
	}

	return;
}

void Minimax :: ImprimirArbol(Nodo *raiz)
{
    char * tab = "";
    if (raiz->nivel != 0){
        tab = (char *) malloc((2*raiz->nivel+1)*sizeof(char));
        int j; for (j=0;j<2*raiz->nivel;j++) tab[j] = ' ';
        tab[2*raiz->nivel] = '\0';
    }
    if (raiz->n_hijos == 0) printf("%sNodo (valor %lf)\n",tab,raiz->valor);
    else{
        int i;
        printf("%sNodo (valor %lf)\n",tab,raiz->valor);
        for (i=0;i<raiz->n_hijos;i++) ImprimirArbol(raiz->hijos[i]);
    }
    free(tab);
}

void Minimax :: ValorarHojas(Nodo *raiz)
{
    if (raiz->n_hijos == 0){
        raiz->valor = VerificarVictoria(raiz->tablero);
    }
    else{
        int i;
        for (i=0;i<raiz->n_hijos;i++){
            ValorarHojas(raiz->hijos[i]);
        }
    }
}

void Minimax :: MiniMax(Nodo *Raiz)
{
     int i;
	//Hacer minimax para buscar las rutas mas opticas 
	if (Raiz->n_hijos != 0){
        for (i=0;i<Raiz->n_hijos;i++){
            if (Raiz->hijos[i]->n_hijos != 0){
                MiniMax(Raiz->hijos[i]);
            }
        }

        if (Raiz->nivel % 2 == 0){ // MAX
            Raiz->valor = Raiz->hijos[0]->valor;
            for (i=1;i<Raiz->n_hijos;i++){
                if (Raiz->hijos[i]->valor > Raiz->valor){
                    Raiz->valor = Raiz->hijos[i]->valor;
                }
            }
        }

		if (Raiz->nivel % 2 == 1){ // Min
            Raiz->valor = Raiz->hijos[0]->valor;
            for (i=1;i<Raiz->n_hijos;i++){
                if (Raiz->hijos[i]->valor < Raiz->valor){
                    Raiz->valor = Raiz->hijos[i]->valor;
                }
            }
        }

		Raiz->valor /= 2;
	}
}

int Minimax :: ElegirTirada(char partida[tamaño][tamaño],int dificultad)
{
    Nodo Raiz = CrearNodo(partida,0,dificultad);
	int movimiento;
	CrearArbol(&Raiz,dificultad,dificultad);
	ValorarHojas(&Raiz);
	MiniMax(&Raiz);
	//ImprimirArbol(&Raiz);

	// Elegimos random entre todas las posibilidades que son igual de buenas
	int num_tiradas_buenas = 0;
	int tiradas_buenas[8];
	int i; int j=0;
	for (i=0;i<Raiz.n_hijos;i++){
		if (Raiz.hijos[i]->valor == 2.0*Raiz.valor){
			num_tiradas_buenas++;
			tiradas_buenas[j] = Raiz.movimientos[i];
			j++;
		}
	}
	int index = rand()%num_tiradas_buenas;
	movimiento = tiradas_buenas[index];
	BorrarArbol(&Raiz);

	return movimiento;
}