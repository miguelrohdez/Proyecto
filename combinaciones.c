#include <stdio.h>
#include <string.h>
#include <time.h>
#define LONG  64//64 //

time_t start, end;
long int total_clock,total_sec;
clock_t inicio, fin;

//char A[LONG]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','*','o','p','q','r','s','t','u','v','w','x','y','z'};
//char A[LONG]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','*','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','+','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char A[LONG]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','*','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','+','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
int i,j,k,l,m;
char pass[3]="Xls";
char nada[4];
int main(int argc, char const *argv[])
{
inicio = clock();
start = time( NULL );

	//for(m=0; m<LONG;m++){
		//for(l=0; l<LONG;l++){
			for (k = 0; k < LONG; k++){
				for (j = 0; j < LONG; j++){
					for (i = 0; i < LONG; i++){

					//printf("%c \n",A[i]); //A[l],
					//printf("%c%c \n",A[j],A[i]); //A[l],
					//printf("%c%c%c \n",A[k],A[j],A[i]); //A[l],
					//printf("%c%c%c \n",A[k],A[j],A[i+1]); //A[l],
					//printf("%c%c%c%c \n",A[l],A[k],A[j],A[i]); //A[l],
					//printf("%c%c%c%c \n",A[l],A[k],A[j],A[i+1]); //A[l],
					//printf("%c%c%c%c \n",A[l],A[k],A[j],A[i+2]); //A[l],
					//printf("%c%c%c%c \n",A[l],A[k],A[j],A[i+3]); //A[l],
					//printf("%c%c%c%c%c \n",A[m],A[l+1],A[k+1],A[j+1],A[i+1]); //A[l],
					sprintf(nada,"%c%c%c",A[k],A[j],A[i]); //A[l],
					printf("%c%c%c = %s \n",A[k],A[j],A[i],pass); //A[l],
						if (!strcmp(nada,pass)){
							printf("a huevoooo\n");
							printf("%c%c%c = %s \n",A[k],A[j],A[i],nada); //A[l],
							end = time( NULL );
							fin = clock();
							total_clock=((double)(fin-inicio));
							total_sec=((long int)(end-start));
							printf("Ciclos totales: %d\n",total_clock );
							printf("Tiempo total en sec: %ld\n",total_sec );
							return 0;
						}
					}
				}
			}
		//}
	//}
	
//end = time( NULL );
//fin = clock();
//total_clock=((double)(fin-inicio));
//total_sec=((long int)(end-start));

//printf("Ciclos totales: %d\n",total_clock );
//printf("Tiempo total en sec: %ld\n",total_sec );
	return 0;
}