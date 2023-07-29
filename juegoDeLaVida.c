#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define filas 50
#define columnas 175

int tablero[filas][columnas];
int tableroTemporal[filas][columnas];
int nuevaMatriz[filas][columnas];
int caracterVacio=' ';
int caracterCelula='#';
int caracterCursor='x';
int caracterEscapeCiclo ='e';
int caracterA ='a';
int caracterD ='d';
int caracterS ='s';
int caracterW ='w';
int caracterX ='x';
int opcion=' ';
/*
#ifdef _WIN32
    #include <windows.h>
#endif
*/
void inicializarMatriz(int matriz[filas][columnas])
{

	for(int f=0;f<filas;f++)
	{
		for(int c=0;c<columnas;c++)
		{
			matriz[f][c]=caracterVacio;
		}
	}
}
void limpiar_pantalla()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void imprimirMatriz(int matriz[filas][columnas])
{
  
	for(int f=0;f<filas;f++) // fila
	{
		if(f==0)
		{
			for(int c=0;c<columnas;c++) // columna
			{
				printf("-");
			}
			printf("--");
			printf("\n");
		}
		printf("|");
		for(int c=0;c<columnas;c++) // columna
		{
			printf("%c",matriz[f][c]);
		}
		printf("|");	
		printf("\n");
		if(f==filas-1)
		{
			for(int c=0;c<columnas;c++) // columna
			{
				printf("-");
			}
			printf("--");
			
			printf("\n");
		}
	}
}

void cursor(int matriz[filas][columnas],int posF,int posC)
{
	matriz[posF][posC]= printf("%c",caracterCursor);
}

char detectarVecinos(int posF,int posC,int matriz[filas][columnas])
{
	int numeroVecinos = 0;
    // x-- //
	// -o- // VERIFICADO
	// --- //
	// printf("actual -> %d\n",matriz[posF][posC]);
	if(posF-1>=0 && posC-1>=0)
	{
		if(matriz[posF-1][posC-1]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF-1][posC-1]);
	}
	// -x- //
	// -o- // VERIFICADO
	// --- //
	if(posF-1>=0)
	{
		if(matriz[posF-1][posC]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF-1][posC]);
	}
	// --x //
	// -o- // VERIFICADO
	// --- //
	if(posF-1>=0 && posC+1<columnas)
	{
		if(matriz[posF-1][posC+1]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF-1][posC+1]);
	}
	// --- //
	// xo- // VERIFICADO
	// --- //
	if(posC-1>=0)
	{
		if(matriz[posF][posC-1]==caracterCelula)
		{
			numeroVecinos+=1;
		}		
		//printf("%c",matriz[posF][posC-1]);
	}
	// --- //
	// -ox // VERIFICADO
	// --- //
	if(posC+1<columnas)
	{
		if(matriz[posF][posC+1]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF][posC+1]);
	}
	// --- //
	// -o- // VERIFICADO
	// --x //
	if(posF+1 && posC+1<columnas)
	{
		if(matriz[posF+1][posC+1]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF+1][posC+1]);
	}
	// --- //
	// -o- // VERIFICADO
	// -x- //
	if(posF+1<filas)
	{
		if(matriz[posF+1][posC]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF+1][posC]);
	}
	// --- //
	// -o- // VERIFICADO
	// x-- //
	if(posF+1<filas && posC-1>=0)
	{
		if(matriz[posF+1][posC-1]==caracterCelula)
		{
			numeroVecinos+=1;
		}
		//printf("%c",matriz[posF+1][posC-1]);
	}
    //printf("%d", numeroVecinos);
    // celula viva
    // matriz[posF][posC]==caracterCelula

    if (matriz[posF][posC]==caracterCelula)
    {
        //printf("celula viva");
        
        if (numeroVecinos == 2 || numeroVecinos == 3)
        {
            //printf("SOBREVIVE\n");
            return caracterCelula;
        }
        else if(numeroVecinos > 3 || numeroVecinos<=1)
        {
            //printf("MUERE\n");
            return caracterVacio;
        }
    }
    else// celula muerta
    {
        if(numeroVecinos==3)
        {
            //printf("NACE\n");
            return caracterCelula;
        }
        else
        {
            
            //printf("SE QUEDA MUERTA\n");
            return caracterVacio;
        }
    }

  
}

void evaluarMatriz(int matriz[filas][columnas],int matrizTemporal[filas][columnas])
{
    int nuevaCelula = ' ';
    for (int f = 0; f < filas;f++)
    {
        for (int c = 0; c < columnas;c++)
        {
            nuevaCelula = detectarVecinos(f, c, matriz);
            matrizTemporal[f][c] = nuevaCelula;
        }
    }
    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            matriz[f][c] = matrizTemporal[f][c];
        }
    }
}

void moverseEnTablero(int opcion,int matriz[filas][columnas])
{
	int posF=0;
	int posC=0;
	int posF_A=0;
	int posC_A=0;
	int caracterAnterior=' ';
	while(opcion!=caracterEscapeCiclo)
	{
		fflush(stdin);

		//printf("EDITOR \n");	
		caracterAnterior = matriz[posF][posC];// guarda caracter posicion actual
		cursor(matriz,posF,posC);// sobrescribe el caracter de la posicion actual
		imprimirMatriz(matriz);
		printf("DIRECCION -> ");
		scanf("%c", &opcion);
		matriz[posF][posC] = caracterAnterior;
		posF_A=posF;
		posC_A=posC;
		if(opcion==caracterA)
		{
			if(posC-1>=0)
			{
				posC--;
			}
		}
		else if(opcion==caracterD)
		{
			if(posC+1<columnas)
			{
				posC++;
			}
		}
		else if(opcion==caracterS)
		{
			if(posF+1<filas)
			{
				posF++;
			}
		}
		else if(opcion==caracterW)
		{
			if(posF-1>=0)
			{
				posF--;
			}
		}
		else if(opcion==caracterX)
		{
			if(caracterAnterior == caracterCelula)
			{
				caracterAnterior = caracterVacio;
			}
			else
			{
				caracterAnterior = caracterCelula;
			}
			
		}
		matriz[posF_A][posC_A] = caracterAnterior;
	}
}


void leerArchivo(int matriz[filas][columnas],char nombre[30])
{
	//scanf("%s", cadena); /* Las cadenas NO llevan & */
 	FILE *archivo;	
 	char caracteres[columnas+5];
 	//char caracteresVacios[165];
 	archivo = fopen(nombre,"r");
 	
 	if (archivo == NULL)
    {
    	printf("ARCHIVO NO ENCONTRADO..\n");
        exit(1);
    }
 	else
    {
 	    for(int f=0;f<filas;f++)
		{
			fgets(caracteres,columnas,archivo);		
			for(int c=0;c<columnas;c++)
			{
				if(caracteres[c]=='x')
				{
					matriz[f][c]='#';
				}
				else
				{
					matriz[f][c]=' ';
				}
			
			}
		}	
    }
    
    fclose(archivo);	
}

void logo()
{
	printf(" -----EL-JUEGO-DE-LA------ \n");
	printf("| #   # ##### ####  ##### |\n");
	printf("| #   #   #   #   # #   # |\n");
	printf("| #   #   #   #   # ##### |\n");
	printf("|  # #    #   #   # #   # |\n");
	printf("|   #   ##### ####  #   # |\n");
	printf(" ------------------------- \n");
	//printf("|  %s CARGAR ARCHIVO %s   |");
}

void interfaz(int opcion,int selector)
{ 
	int s1,s2=selector; 
	if(opcion==0)
	{
		s1=selector;
		s2=' ';
	}
	else if(opcion==1)
	{		
		s1=' ';
		s2=selector;
	}
	
	printf("|        %c JUGAR %c        |\n",s1,s1);
	printf("|   %c CARGAR ARCHIVO %c    |\n",s2,s2);
	printf(" ------------------------- \n");
}

int menu()
{
	int opcionSeleccionada=0;
	int direccion=0;
	int maxOpcion=1;
	do
	{
		limpiar_pantalla(); 
		
		logo();
		interfaz(opcionSeleccionada,caracterCelula);	
		
		scanf("%d",&direccion);
		if(direccion==2)
		{
			if(opcionSeleccionada-- <= 0)
			{
				opcionSeleccionada=maxOpcion;
			}
		}
		else if(direccion==8)
		{
			if(opcionSeleccionada++ >= maxOpcion)
			{
				opcionSeleccionada=0;
			}
		}
		fflush(stdin);
		
	}while(direccion!=5);
	
	if(opcionSeleccionada==0)
		return 0;
	else
		return 1;
}

int main()
{
	int opcionMenu=0;
	do
	{
		
		// Entramos al menu
		opcionMenu = menu();
		// Salimos del menu
		if(opcionMenu==0)
		{
			FILE *guardado;
			if(fopen("guardado.txt","r")!=NULL)
			{
				limpiar_pantalla(); 
				char nombreArchivo[20];
				char nombreFormateado[30];
				int opcionVerArchivo=0;
				// abro el archivo que contiene el nombre del ultimo archivo ejecutado
				guardado = fopen("guardado.txt","r");
				printf("ARCHIVO ACTUAL -> ");
				fgets(nombreArchivo,20,guardado);
				printf("%s\n",nombreArchivo);
				// copio el nombre y le concateno ".txt"
				strcpy(nombreFormateado,nombreArchivo);
				strcat(nombreFormateado,".txt");		
				// ingreso la informacion del archivo al tablero y lo imprimo	
				leerArchivo(tablero,nombreFormateado);
				imprimirMatriz(tablero);
				// pregunto si es el archivo que desea
				printf(" CONFIRMAR -> 0		REGRESAR -> 1\n");
				scanf("%d",&opcionVerArchivo);
				fflush(stdin);
				// si, entonces preparo los tableros he inicio la ejecucion
				if(opcionVerArchivo==0)
				{
					limpiar_pantalla();
					inicializarMatriz(tablero);
					inicializarMatriz(tableroTemporal);
					leerArchivo(tablero,nombreFormateado);
					for(int i = 0; i <10000;i++)
					{
						limpiar_pantalla();
						printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					    printf("|GENERACION #%d                                                                           |\n",i);
				    	//printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						imprimirMatriz(tablero);
						evaluarMatriz(tablero, tableroTemporal);
						Sleep(1000);
					}
				}
			}
			else
				printf("ARCHIVO NO ENCONTRADO\n");
		}
		else
		{
			char archivoAbrir[30];
			char nombreFormateado[30];
			FILE *guardadoEscribir;
			do
			{	
				limpiar_pantalla(); 
				printf("INGRESE EL NOMBRE DEL ARCHIVO -> ");
				scanf("%s",&archivoAbrir);
				fflush(stdin);
				strcpy(nombreFormateado,archivoAbrir);
				strcat(nombreFormateado,".txt");
				if(fopen(nombreFormateado,"r")==NULL)
				{
					printf("ARCHIVO [%s] NO ENCONTRADO \n",nombreFormateado);
					system("PAUSE");
				}
			}while(fopen(nombreFormateado,"r")==NULL);
			limpiar_pantalla(); 
			guardadoEscribir = fopen("guardado.txt","w+");
			
			fprintf(guardadoEscribir,"%s",archivoAbrir);
			fclose(guardadoEscribir);
			printf("ARCHIVO CARGADO EXITOSAMENTE\n");
			system("PAUSE");
			
		}
	}while(opcionMenu!=4);

	fflush(stdin);
	printf("PRESIONA CUALQUIER TECLA PARA TERMINAR...");
	scanf("%c", &opcion);
	return 0;
}
