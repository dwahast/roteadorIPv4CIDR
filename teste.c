#include "roteador.h"
#include "simplegrade.h"
#include <math.h>


uint32_t iptoint(int a, int b, int c, int d){
	return ((a<<24)+(b<<16)+(c<<8)+d);
}

void testeFiltro(){

	entrada rotas[2] = {
							{iptoint(23,4,0,2), 8, 1},
							{iptoint(255,255,0,0), 16, 2}
					   };

	entrada filtros[2] = {
							{iptoint(5,4,0,0), 24, 0},
							{iptoint(1,1,1,0), 16, 0}
						 };

	uint32_t pacotes[4] = {  
							iptoint(5,4,0,1),
							iptoint(1,1,1,1),
							iptoint(23,0,12,0),
							iptoint(255,255,1,1)
					      };	

	uint32_t *result;

	WHEN("Tenho duas rotas");
	IF("Envio dois pacotes que serão filtrados");

	result = roteamento(rotas,2,pacotes,4,filtros,2,4);	

	THEN("Devo ter descartado dois pacotes");
	isEqual(result[0], 2, 1);
	
	free(result);
}

void teste_1(){

	entrada filtros[1] = {
    						{iptoint(9,9,9,0), 24, 0}
    					};
	
	entrada rotas[2] = {
							{iptoint(5,127,127,127), 8, 1},
							{iptoint(1,255,255,255), 8, 2}
					   };

     
	uint32_t pacotes[2] = {  
							iptoint(5,4,0,1),
							iptoint(1,1,1,1),
						  };	

	uint32_t *result;

	WHEN("Tenho duas rotas");
	IF("Envio dois pacotes");

	result = roteamento(rotas,2,pacotes,2,filtros,1,3);	

	THEN("Devo ter um pacote em cada rota");
	isEqual(result[0],0,1);
	for(int i = 1; i < 2; i++){
		isEqual(result[i], 1, 1);
	}
	free(result);
}

void teste_2(){

	entrada filtros[1] = {
    						{iptoint(9,9,9,0), 8, 0}
    					};

	entrada rotas[2] = {
							{iptoint(10,0,1,0), 24, 1},							
							{iptoint(10,0,0,0), 16, 2}
					   };
    
	uint32_t pacotes[1] = { 
							iptoint(10,0,1,5)
						  };	

	uint32_t *result;

	WHEN("Tenho 2 rotas e 1 filtro");
	IF("Envio 1 pacote");

	result = roteamento(rotas,2,pacotes,1,filtros,1,3);	

	THEN("Devo ter 1 pacote em 1 enlace");
	
	isEqual(result[0],0,1);
	isEqual(result[1],1,1);
	
	free(result);
}

void teste_3(){

	entrada filtros[1] = {
    						{iptoint(9,9,9,0), 8, 0}
    					};

	entrada rotas[2] = {
							{iptoint(10,0,1,0), 24, 1},							
							{iptoint(10,0,0,0), 16, 2}
					   };
    
	uint32_t pacotes[3] = { 
							iptoint(10,0,1,5),
							iptoint(10,0,4,2),
							iptoint(10,0,2,3)
						  };	

	uint32_t *result;

	WHEN("Tenho 2 rotas e um filtro");
	IF("Envio 3 pacotes");

	result = roteamento(rotas,2,pacotes,3,filtros,1,3);	

	THEN("Devo ter 1 pacote no enlace 1, 2 pacotes no enlace 2 e nenhum filtrado");
	
	isEqual(result[0],0,1);
	isEqual(result[1],1,1);
	isEqual(result[2],2,1);

	free(result);
}

void teste_4(){

	entrada filtros[1] = {
    						{iptoint(9,9,9,0), 8, 0}
    					};

	entrada rotas[4] = {
							{iptoint(5,4,0,0), 8, 1},
							{iptoint(1,0,0,0), 8, 2},
							{iptoint(10,0,1,0), 24, 3},
							{iptoint(10,0,0,0), 16, 4}
					   };
    
	uint32_t pacotes[5] = { 
							iptoint(9,0,1,5), 
							iptoint(10,0,0,22), 
							iptoint(10,0,1,5), 
							iptoint(5,4,0,1),
							iptoint(1,1,1,1) 
						  };	

	uint32_t *result;

	WHEN("Tenho 4 rotas e um filtro");
	IF("Envio 5 pacotes");

	result = roteamento(rotas,4,pacotes,5,filtros,1,5);	

	THEN("Devo ter 1 pacote em cada rota e 1 filtrado");
	

	for(int i = 0; i < 5; i++){
		isEqual(result[i],1,1);
	}
	free(result);
}

void teste_5(){

	entrada filtros[1] = {
    						{iptoint(9,9,9,0), 8, 0}
    					};

	entrada rotas[4] = {
							{iptoint(5,4,0,0), 8, 1},
							{iptoint(1,0,0,0), 8, 2},
							{iptoint(10,0,1,0), 24, 3},
							{iptoint(10,0,0,0), 16, 4}
					   };
    
	uint32_t pacotes[5] = { 
							iptoint(5,0,1,5), 
							iptoint(10,0,0,22), 
							iptoint(10,0,1,5), 
							iptoint(5,4,0,1),
							iptoint(1,1,1,1) 
						  };	

	uint32_t *result;

	WHEN("Tenho 4 rotas e 1 filtro");
	IF("Envio 5 pacotes");

	result = roteamento(rotas,4,pacotes,5,filtros,1,5);	

	THEN("Devo ter 2 pacotes no enlace 1 e nas outras rotas 1 pacote, nenhum pacote é filtrado");
	
	isEqual(result[0],0,1);
	isEqual(result[1],2,1);
	isEqual(result[2],1,1);
	isEqual(result[3],1,1);
	isEqual(result[4],1,1);

	free(result);
}

void teste_6(){

	entrada filtros[1] = {
    						{iptoint(9,9,9,0), 8, 0}
    					};

	entrada rotas[5] = {
							{iptoint(5,4,0,0), 8, 1},
							{iptoint(1,0,0,0), 8, 2},
							{iptoint(10,0,1,0), 24, 3},
							{iptoint(10,0,0,0), 16, 4}
					   };
    
	uint32_t pacotes[14] = { 
							iptoint(9,0,1,5), 
							iptoint(10,0,0,22), 
							iptoint(10,0,1,5), 
							iptoint(1,1,1,1), 
							iptoint(9,17,98,5), 
							iptoint(10,0,17,99), 
							iptoint(10,0,1,5), 
							iptoint(5,0,0,0),
							iptoint(1,2,3,4), 
							iptoint(9,9,9,9), 
							iptoint(5,0,99,99), 
							iptoint(9,9,9,7),							
						  };	

	uint32_t *result;

	WHEN("Tenho 4 rotas e um filtro");
	IF("Envio 14 pacotes");

	result = roteamento(rotas,5,pacotes,14,filtros,1,5);	

	THEN("Devo ter 2 pacotes em cada rota e 4 filtrados");
	
	isEqual(result[0],4,1);
	for(int i = 1; i < 5; i++){
		isEqual(result[i],2,1);
	}
	free(result);
}

int main()
{	
	testeFiltro();
	teste_1();
	teste_2();
	teste_3();
	teste_4();
	teste_5();
	teste_6();
	//testes
	GRADEME();
	return 0;
}