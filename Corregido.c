#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define INFO(I) ((I)->info)
#define SIG(I) ((I)->sig)
#define ANT(I) ((I)->ant)

typedef struct Nodo * NODO;

struct Nodo {
	char info;
	struct Nodo *sig, *ant;

};

NODO Instanciar(char info);
NODO New_nodo(NODO datos, char info);
void Insertar(NODO datos, int posicion, char info);
NODO Posicion(NODO datos, int posicion);
void Eliminar(NODO datos, int posicion);
void Imprimir_lista(NODO datos);
void Imprimir_lista_reversa(NODO datos);
void Busqueda(NODO datos, int posicion);
void Modificar(NODO datos,int posicion, char info);
void Salvar_cambios(NODO datos);
void Mostrar_bitacora(void);
void Ayuda(void);
void Guardar_bitacora(int Error);


int num_datos=0;
char cad_aux[10];
char dato;
int i;
int main(int argc, char *argv[])
{	
	//system("clear");
	int posicion;
	/*for (i = 0; i < argc; ++i)
	{
	printf("Total: %d Entrada: %d %s\n",argc,i,argv[i]);
	}*/
	sprintf(cad_aux,"%s",argv[1]);
	if ((!strcmp(cad_aux,"h")) || (!strcmp(cad_aux,"-h")) || (!strcmp(cad_aux,"--help"))){
		Ayuda();
		exit(0);}
	if ((!strcmp(cad_aux,"bitacora")) || (!strcmp(cad_aux,"-b")) || (!strcmp(cad_aux,"--log"))){
		Mostrar_bitacora();
		exit(0);}

	if(argc <= 1){
		printf("--> Error: no ingreso ningun parametro ó faltan parametros, \n(--help o h para mayor informacion) \n");
		printf("Debe contener:\n");
		printf("\"Archivo_Lista\" \"Parametro\" \"Posicion\" \"Dato\"\n");
		//Guardar_bitacora(1,*argv[1]);
		Guardar_bitacora(1);
		exit(0);}
	


	FILE *archivo_lista;
	archivo_lista=fopen(argv[1],"r");
	NODO datos=NULL;
	//printf("\n\t");
    //printf("%c ",dato);
	if(archivo_lista!=NULL){
	//printf("****************Datos Lista****************\n\t"); //Por que si no no tiene caso la funcion mostrar
	dato = fgetc(archivo_lista);
	//printf("%c ",dato );
	datos=New_nodo(datos,dato);
		while(!feof(archivo_lista)){
			dato = fgetc(archivo_lista);
	        if(dato !=' '&& dato != (feof(archivo_lista))){
	            datos=New_nodo(datos,dato);
	          //  printf("%c ",dato );
	            num_datos++;
	        	}
			//fscanf(archivo_lista,"%s", buffer);
			//fgetc(archivo_lista);
			}
	printf("\n");
	fclose(archivo_lista);
	}else{
		printf("No se encontro el archivo\n");
		Guardar_bitacora(2);
		//Guardar_bitacora(2,*argv[1]);
		exit(0);
	}
	

	switch (*argv[2]){
		case 'i':
			printf("****************Insertar****************\n\t");
			Imprimir_lista(datos);
			posicion=atoi(argv[3]);
			if(argc>5){
			Guardar_bitacora(6);
			printf("--> Error: Se excedio el numero de parametros \n(--help o h para mayor informacion) \n");
			exit(0);}
			Insertar(datos,posicion,*argv[4]);

			break;

		case 'e':
			printf("****************Eliminar****************\n\t");
			Imprimir_lista(datos);
			posicion=atoi(argv[3]);
			if(argc>4){
			Guardar_bitacora(6);
			printf("--> Error: Se excedio el numero de parametros \n(--help o h para mayor informacion) \n");
			exit(0);}
			if(posicion>num_datos){
			printf("--> Error: La Posicion %d no es valida ó no se encuentra \n", posicion);
			Guardar_bitacora(4);
			exit(0);
			}
			Eliminar(datos, posicion);

			break;

		case 'm':
			printf("****************Mostrar****************\n\t");
			if(argc>4){
			Guardar_bitacora(6);
			printf("--> Error: Se excedio el numero de parametros \n");
				printf("--help o h para mayor informacion \n");
			exit(0);}
			
			Imprimir_lista(datos);

			break;

			case 'r':
			printf("****************Mostrar al revez****************\n\t");
			if(argc>5){
			Guardar_bitacora(6);
			printf("--> Error: Se excedio el numero de parametros \n(--help o h para mayor informacion) \n");
			exit(0);}
			Imprimir_lista_reversa(datos);

			break;

		case 'c':
			printf("****************Modificar****************\n\t");
			posicion=atoi(argv[3]);
			Imprimir_lista(datos);
			if(argc>5){
			Guardar_bitacora(6);
			printf("--> Error: Se excedio el numero de parametros \n(--help o h para mayor informacion) \n");
			exit(0);}
			if(posicion>num_datos){
			printf("--> Error: La Posicion %d no es valida ó no se encuentra \n", posicion);
			Guardar_bitacora(4);
			exit(0);
			}
			Modificar(datos, posicion, *argv[4]);

			break;

		case 's':
			printf("****************Busqueda****************\n\t");
			posicion=atoi(argv[3]);
			if(argc>4){
			Guardar_bitacora(6);
			printf("--> Error: Se excedio el numero de parametros \n(--help o h para mayor informacion) \n");
			exit(0);}
			if(posicion>num_datos){
			printf("--> Error: La Posicion %d no es valida ó no se encuentra \n", posicion);
			Guardar_bitacora(4);
			exit(0);
			}
			Busqueda(datos, posicion);

			break;
		case 'h':
			Ayuda();
			break;
		default:
			printf("--> Error: Se ingreso un parametro incorrecto: %s\n", argv[2]);
			printf("\t--help o h para mayor informacion\n" );
			Guardar_bitacora(3);
			break;				

	
	}
	Salvar_cambios(datos);
	return 0;
}

void Guardar_bitacora(int Error){
	FILE *bitacora;
	bitacora = fopen("bitacora.log","a+");
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char fecha[128];
    strftime(fecha,128,"%d/%m/%y %H:%M:%S",tlocal);
    fprintf(bitacora,"\n******************************%s******************************\n",fecha);
    fprintf(bitacora,"\t\tUsuario que lo ejecuto: %s\n",getenv("USER") );
    fprintf(bitacora, "El tipo de error fue:\n" );
    switch(Error){
    	case 1:
			fprintf(bitacora,"--> Error: no ingreso ningun parametro ó faltan parametros \n");
			break;
		case 2: 
			fprintf(bitacora,"--> Error: No se encuentra el \"Archivo_Lista\": \n");
			break;
		case 3:
			fprintf(bitacora,"--> Error: No se reconoce como parametro valido: ");
			//fprintf(bitacora,"%s \n",dato); 
			break;
		case 4: 
			fprintf(bitacora,"--> Error: La Posicion no es valida ó no se encuentra: ");
			//fprintf(bitacora,"%s \n",dato); 
			break;
		case 5: 
			fprintf(bitacora,"--> Error: No se ingreso ningun dato en la lista \n");
			break;
		case 6: 
		fprintf(bitacora,"--> Error: Se excedio el numero de parametros, \n");
			break;
    }

	fclose(bitacora);
    return;
}

void Mostrar_bitacora(void){
	FILE *archivo;
	archivo=fopen("bitacora.log","r");
	if(archivo!=NULL){
		printf("\t****************Bitacora****************\n");
		while(!feof(archivo)){
			printf("%c",fgetc(archivo));
			}
		fclose(archivo);
		exit(0);
	}else{
		printf("No se encuentra la bitacora!!\n");
		exit(0);
	}
	fclose(archivo);
}

void Ayuda(void){
	printf("****************Ayuda****************\n");
	printf("Debe contener:\n");
	printf("[Lista] [Parametro] [Posicion] [Dato]");
	printf("Ejemplo:\n");
	printf("Nombre_programa Lista.txt c 5 dato\n");
	printf("\t[Lista]\t\tIndica el archivo que contiene la lista\n");
	printf("\t[Parametro]\tIndica la funcion a realizar\n");
	printf("\t\tLos parametros validos son:\n");
	printf("\t i\tInsert\tAlgrega un elemento\n");
	printf("\t e\tDelete\tElimina un elemento\n");
	printf("\t m\tShow\tMuestra los elementos de la lista\n");
	printf("\t r\tReverse\tMuesta los elementos de la lista en orden inverso\n");
	printf("\t c\tChange\tModifica un elemento de la lista\n");
	printf("\t s\tSearch\tBusca un elemento de la lista por su posicion\n");
	printf("\t h\tHelp\tMuestra el menu de ayuda\n");
	printf("\t[Posicion]\tLugar del elemento a crear o modificar, es del tipo int\n");
	printf("\t[Dato]\t\tInformacio del elemento a crear o modificar, es del tipo char\n");
}

NODO Instanciar(char info){
	NODO nuevo;
	nuevo = (NODO) malloc(sizeof(struct Nodo));
	INFO(nuevo)= info;
	SIG(nuevo) = NULL;
	ANT(nuevo) = NULL;
	return nuevo;
}

NODO New_nodo(NODO datos, char info){
    NODO aux;
    aux = (NODO) malloc(sizeof(struct Nodo));/*Crea nuevo elemento*/
    if(datos == NULL){
        aux = Instanciar(info);
        return aux;
    }else if(SIG(datos)==NULL){
        SIG(aux) = datos;
        SIG(datos) = aux;
        ANT(aux) = datos;
        ANT(datos) = aux;   
    }else{
        datos->sig->ant = aux;
        SIG(aux) = SIG(datos);/*aterriza a null el último elemento*/
        SIG(datos) = aux;
        ANT(aux) = datos;
    }
    INFO(aux) = info;/*guarda el dato en el elemento*/
    return aux;
}

void Insertar(NODO datos, int posicion, char info){
	NODO aux,nuevo;
    nuevo = Instanciar(info);
    aux = Posicion(datos,posicion);
    aux->ant->sig = nuevo;
    SIG(nuevo) = aux;
    ANT(nuevo) = ANT(aux);
    ANT(aux) = nuevo;
}

NODO Posicion(NODO datos, int posicion){
	int i=0;
	NODO aux;
	aux=datos;
	for (i = 0; i < posicion; i++){
		aux=SIG(aux);
	}
	return aux;
}

void Eliminar(NODO datos, int posicion){
	NODO aux = Posicion(datos,posicion);
    aux->ant->sig =aux->sig;
    aux->sig->ant = aux->ant;
    free(aux);
}

void Imprimir_lista(NODO datos){
	NODO apr;
	apr = Posicion(datos,1);
	datos=apr;
	do{
        printf("%c ", datos->info);
        datos = SIG(datos);
    }while(datos != apr);
    printf("\n");
}
void Imprimir_lista_reversa(NODO datos){
	NODO apr=Posicion(datos,1);
	datos=apr;
	do
    {
        printf("%c ", datos->info);
        datos = ANT(datos);
    }while(datos != apr);
    printf("\n");
}

void Busqueda(NODO datos, int posicion){
	NODO aux;
	aux = Posicion(datos,posicion);
	printf("Dato: %c\n", aux->info);
    printf("Siguiente: %s\n", aux->sig);
    printf("Anterior: %s\n", aux->ant);
}

void Modificar(NODO datos,int posicion, char info){
	NODO aux=Posicion(datos, posicion);
	INFO(aux)=info;
}

void Salvar_cambios(NODO datos){
	NODO apr=Posicion(datos,1);
	datos=apr;
	FILE *prueba;
	prueba=fopen("texto2.txt","w+");
	printf("****************La nueva lista queda****************\n");
	do{
       	printf("%c ", datos->info);
        fprintf(prueba,"%c ", datos->info);
        datos = SIG(datos);
    }while(datos != apr);
    fclose(prueba);
    return;
}