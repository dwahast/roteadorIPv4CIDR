#include <stdio.h>
#include <stdlib.h>
#include "roteador.h"

uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes, 
	int num_pacotes, entrada * filtros, int num_filtros, int num_enlaces){

	uint32_t currMasc = 0;
	uint32_t enlacePriority;
	uint32_t *result;
	int j=0,k=0,i=0;
	
	result = malloc(num_enlaces * sizeof(int));
	//certifica que não tem lixo no vetor.
		for(int l = 0; l < num_enlaces; l ++){
			result[l] = 0;
		}
	
		for(j = 0; j < num_pacotes; j++){
			for(k = 0; k < num_filtros; k++){
				if(filtros[k].endereco>>(32-filtros[k].mascara) == pacotes[j]>>(32-filtros[k].mascara)){
					result[(uint32_t)filtros[k].enlace] += 1;
					j++;
				}
			}
			for(i = 0; i < num_rotas;i++){
				if(rotas[i].endereco>>(32-rotas[i].mascara) == pacotes[j]>>(32-rotas[i].mascara)){
					if((uint32_t)(rotas[i].mascara)>currMasc){
						currMasc = (uint32_t)rotas[i].mascara;
						enlacePriority = i;
					}										
				}							
			}

			if(currMasc!=0){	
				result[(int)(rotas[enlacePriority].enlace)] += 1;	
			}
			enlacePriority = 0;
		    currMasc=0;
		    i = 0;
		    k = 0;
		}
		

	return result;
} 	

