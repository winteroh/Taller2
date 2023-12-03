#include <stdio.h>

class Records
{
	private:
    public:
    void GuardarNombre(char *, char *);
    void PrintearRecords(char [30][10],int [30]);
    void NuevoRecord(int ,int );
};

void Records :: GuardarNombre(char *dest, char *source)
{
    int i=0;
	while (source[i]!='\0'){
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}

void Records :: PrintearRecords(char persona[30][10], int puntuacion[30])
{
	int i;
	FILE *RECORDS = fopen("Records.txt","r+");
	for (i=0;i<30;i++) fscanf(RECORDS,"%s %d",persona[i],puntuacion+i);
    {
	fclose(RECORDS);
    }
}

void Records :: NuevoRecord(int puntuacionjugador, int dificultad)
{
    printf("\n\n********************* NUEVO RECORD!!! *********************\n");

	/* Leer los records actuales */
	char persona[30][10]; int puntuacion[30];
	PrintearRecords(persona,puntuacion);

	/* Ubicar que posicion ha alcanzado */
	int pos=(3-dificultad)*10-1;
	while(puntuacionjugador<puntuacion[pos]){
		pos--;
	}
	printf("\nEnhorabuena! Estas en el puesto %d de este nivel\n",pos%10+2);

	/* Registro del record */
	char nombre_jugador[10];
	printf("Introduce tu nombre (maximo 10 caracteres): "); scanf("%s",&nombre_jugador);
	int i;
	for (i=(3-dificultad)*10-1;i>(3-dificultad-1)*10;i--){
		if (puntuacionjugador < puntuacion[i-1]){
			GuardarNombre(persona[i],persona[i-1]);
			puntuacion[i] = puntuacion[i-1];
			GuardarNombre(persona[i-1],nombre_jugador);
			puntuacion[i-1] = puntuacionjugador;
		}
		else break;
	}

	/* Reescribir el archivo de records */
	FILE *NRECORDS = fopen("records.txt","w+");
	for (i=0;i<30;i++){
		fprintf(NRECORDS,"%s %d\n",persona[i],puntuacion[i]);
	}
	fclose(NRECORDS);
}