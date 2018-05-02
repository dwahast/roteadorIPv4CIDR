#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "roteador.h"
/*
PARALELO
*/
typedef struct node{
	uint32_t pacote;
	struct node *prox;
}Node;

typedef struct in{
	uint32_t *pacs;
	uint32_t numPacs;
}In;

//variaveis globais
Node *HeadQueue;
entrada *filters,*routes;
uint32_t *result;
int count = 0;
int countOut = -1;
int max,numFiltros,numRotas,numPacotes;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

//funções fila
void insertQueue(void *pac);
void removeQueue();

uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes, 
	int num_pacotes, entrada * filtros, int num_filtros, int num_enlaces){
	if(pacotes){if(filtros){if(num_filtros){if(num_enlaces){}}}}
	
	result = calloc(num_pacotes, sizeof(uint32_t));
	HeadQueue = calloc(1,sizeof(Node));
	HeadQueue->prox = NULL;
   	max = num_pacotes;
   	numFiltros = num_filtros;
   	numRotas = num_rotas;
   	numPacotes = num_pacotes;
   	filters = filtros;
   	routes = rotas;
	In inInsert;	
	inInsert.pacs = pacotes;
	inInsert.numPacs = num_pacotes;
	pthread_t threadIn, threadOut1, threadOut2, threadOut3, threadOut4;
	
	pthread_create(&threadIn, NULL, (void *) insertQueue, (void *) &inInsert);
	pthread_create(&threadOut1, NULL, (void *)removeQueue, NULL);
	pthread_create(&threadOut2, NULL, (void *)removeQueue, NULL);
	pthread_create(&threadOut3, NULL, (void *)removeQueue, NULL);
	pthread_create(&threadOut4, NULL, (void *)removeQueue, NULL);
	

	pthread_join(threadIn, NULL);
    pthread_join(threadOut1, NULL); 
    pthread_join(threadOut2, NULL); 
    pthread_join(threadOut3, NULL);
    pthread_join(threadOut4, NULL);  
	
	count = 0;
	countOut = -1;
	free(HeadQueue);
	return  result;
} 	

void insertQueue(void *pac){

	Node *aux,*new;	
	In *paco;
	paco = (In *)pac;	
	//while	
	if(countOut == -1){				
	    HeadQueue = HeadQueue->prox;	  		   
	    countOut += 1;
	}
	while(count < numPacotes){			
		aux = HeadQueue;
		new = malloc(sizeof(Node));
		new->pacote = paco->pacs[count];		
		new->prox = NULL;				
		if(aux == NULL){//Se Vazia Insere no inicio
			//add				
			HeadQueue = new;
			count += 1;			
		}else{	
			for(;aux->prox != NULL;aux = aux->prox);//percorre até o ultimo Nodo
			//add					
			aux->prox = new;
			count += 1;			
		}			
	}		
}	

void removeQueue(){	
	uint32_t enlacePriority = 0;
	uint32_t currMasc = 0;
	while((countOut < max) && (countOut <= (int)count)){
		if(countOut == -1){			     
		    HeadQueue = HeadQueue->prox;	  		   
		    countOut += 1;
		}		
		if(!(countOut >= (int)count)){
			//função aqui
			for(int k = 0; k < numFiltros; k++){
				if(filters[k].endereco>>(32-filters[k].mascara) == HeadQueue->pacote>>(32-filters[k].mascara)){
					pthread_mutex_lock(&m1);	
					result[(uint32_t)filters[k].enlace] += 1;
					pthread_mutex_unlock(&m1);				
				}
			}
			for(int i = 0; i < numRotas;i++){
				if(routes[i].endereco>>(32-routes[i].mascara) == HeadQueue->pacote>>(32-routes[i].mascara)){
					if((uint32_t)(routes[i].mascara)>currMasc){
						currMasc = (uint32_t)routes[i].mascara;
						enlacePriority = i;
					}										
				}								
			}			
			if(currMasc!=0){	
				pthread_mutex_lock(&m2);					
				result[(int)(routes[enlacePriority].enlace)] += 1;	
				pthread_mutex_unlock(&m2);	
			}	

			countOut += 1;							
			HeadQueue = HeadQueue->prox;
			enlacePriority = 0;
		    currMasc=0;
		}
	}		
}