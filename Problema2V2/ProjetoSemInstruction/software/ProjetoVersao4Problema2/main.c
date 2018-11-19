

#include <stdio.h>
#include "io.h"
#include "system.h"
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_lcd_16207_regs.h"
#include "altera_avalon_lcd_16207.h"
#include "altera_avalon_uart_regs.h"


main(){


	unsigned int bEntrar, bVoltar, bSubir, bDescer;
	int opcao =0;

	iniciaLCD();

	escreveLCD(0,0);
	char comando[] = "AT+CWMODE_CUR=1";

	//printf("%d",strlen(comando));
	escreveTXUart(strlen(comando), comando);

	char comando2[] = "AT+CWJAP_CUR=\"WLessLEDS\",\"HelloWorldMP31\"";
	escreveTXUart(strlen(comando2), comando2);
	//comando = "AT+CWMODE_CUR=1";
	//lerRXUart();

	//testeESP01();
	//escreveLCDGenerico("testeLCD", 8);


	while(1){
		bSubir = IORD(BOTAOSUBIR_BASE,0);
		bDescer = IORD(BOTAODESCER_BASE,0);
		bEntrar = IORD(BOTAOENTRAR_BASE,0);
		bVoltar = IORD(BOTAOVOLTAR_BASE,0);

		if(bSubir){

			if(opcao == 4){
				opcao = 0;
			}
			else{
				opcao++;
			}
			escreveLCD(opcao,0);
			esperar();
		}
		else if(bDescer){
			if(opcao == 0){
				opcao = 4;
			}
			else{
				opcao--;
			}
			escreveLCD(opcao,0);
			esperar();
		}
		else if(bEntrar){
			escreveLCD(opcao,1);
			acendeLed(opcao);
			printf("entrar\n");
			esperar();

		}
		else if(bVoltar){
			escreveLCD(opcao,0);
			IOWR(LEDVERMELHO_BASE, 0, 0);//apaga o led
			IOWR(LEDVERDE_BASE, 0, 0);
			IOWR(LEDAZUL_BASE, 0, 0);
			usleep(900);
			printf("voltar\n");
		}
	}


	return 0;
}




/*******************************************************************************/
void escreveTXUart(int tamanho, char* comando){

	unsigned long status = 0;
	    int i;

	    char data ="";
	    char a = "";
while(1){
	  	printf("STATUS INICIO %x \n",IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE));

	    for (i = 0; i < tamanho; i++) {
	    	//printf("COMANDO :%c -- \n", comando[i]);
	    	while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<6)));
	    	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, comando[i]);

	    }
	    while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<6)));
	    IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, '\r');


	    //printf("%x \n",IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE));
	    while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<6)));
	    IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, '\n');


	    printf("STATUS ANTES DA LEITURA - %x \n",IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE));
i=0;

				while((IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<7))){
				data = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );
				printf(" %c  ",data);

					if(data == 'K'){
						return;
					}

				//printf("STATUS DEPOIS DA LEITURA - %x \n",IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE));

				}
}

}

void lerRXUart(){
	char data;
	char palavra[5];
	int i=0;
	unsigned long status = 0;
	    while(1){

	    	//escreveLCDGenerico("c",1);

	    	//printf("\nEntrou no ler UART");
	    	//IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, 0x80);


//
//
//	    	if(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) & 0x16c){
//


        	data = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );
	    		if(data == 'K') {
	    			printf("Status rx: %x", IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE));
	    			printf("\n caracter  - %c ",data);
	    			status =IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
	    			    	printf(" Status rx dentro do loop - %x",status);
	    		}


/*
	        if( (status & 0x1e8 ) != 0x1e8){
	    		status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
	    		printf(" Status rx dentro do loop - %x",status);


	        }
	        else{

	        }
//	    		usleep(1000);
//	    	}

*/
	    	//printf("Depois do if");

		    //palavra[i]=data;




	    	 i++;
		}





}


void testeESP01(){
	//escreveLCDGenerico("testeLCD", 8);
	// alt_putstr("AT\r\n"); //Envia comando teste em serial

	/*IOWR(LCD_16207_0_BASE, 0, 0x02);//limpa display
	usleep(2000);
	IOWR(LCD_16207_0_BASE, 0, 0x01); // coloca cursor no inicio
	usleep(2000);*/

	/************************** Envia AT ************************/

	char at[2] = "AT";

	usleep(1000);

	for(int i=0;  ;i++){
		 IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, at[i]);
		 usleep(1000);

	}


	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, '\r');
	usleep(1000);
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, '\n');
	usleep(1000);


	/******************** Recebe resposta*************************/
	 char response = 'T';

	 while(response != 'K'){ //O ESP deve responder com um OK
		 response= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 usleep(1000);
		 //IOWR(LCD_16207_0_BASE, 2, response);
		 //usleep(1000);
		 printf("\n\n caracter  : %c", response );

	 }


/*
	 if(response == 'K'){

		IOWR(LEDVERMELHO_BASE, 0, 0);
		IOWR(LEDVERDE_BASE, 0, 0);
		IOWR(LEDAZUL_BASE, 0, 1);
		esperar();
		esperar();
	 }


*/


}

/*
 * SSID - WLessLEDS
 * Senha - HelloWorldMP31
 * Endereço do Broker - rpibroker.local
 * ip: 192.168.1.100   -d (pub)
 */

void conectaESP01(){


	 alt_putstr("AT+CWMODE_CUR=1"); //Seta como uma station para se conectar a uma rede
	 //Parece que o comando de conexão só funciona se ele estiver neste modo


	 char response[200]; //Responde com a instrução AT enviada
	 int i =0;
	 while(!strcmp(response, 'AT+CWMODE_CUR=1')){ //O ESP deve responder com um OK
		 response[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }

	 char response2[2]; //Responde também com um OK
	 i =0;
	 while(!strcmp(response2, 'OK')){ //O ESP deve responder com um OK
		 response2[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }


	 alt_putstr("AT+CWJAP_CUR=WLessLEDS,HelloWorldMP31");

	 char response3[200]; //Responde com a instrução AT enviada
	 i =0;
	 while(!strcmp(response3, 'AT+CWJAP_CUR=WLessLEDS,HelloWorldMP31')){ //O ESP deve responder com um OK
		 response3[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }

	 char response4[2]; //Responde também com um OK
	 i =0;
	 while(!strcmp(response4, 'OK')){ //O ESP deve responder com um OK
		 response4[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }


}

void escreveLCDGenerico(char* palavra, int n){ // n é o tamanho da palavra


	IOWR(LCD_16207_0_BASE, 0, 0x02);//limpa display
	usleep(2000);
	IOWR(LCD_16207_0_BASE, 0, 0x01); // coloca cursor no inicio
	usleep(2000);

	int i;
	for(i=0; i<n ;i++){
		IOWR(LCD_16207_0_BASE, 2, palavra[i]);
		//printf("\n\nif palavra  : %c", palavra[i] );
		usleep(1000);
	}
}
/******************************************************************************/

void acendeLed(int opcao){
	switch(opcao){
		case 0:
			//verde
			IOWR(LEDVERMELHO_BASE, 0, 1);
			IOWR(LEDVERDE_BASE, 0, 0);
			IOWR(LEDAZUL_BASE, 0, 0);
			esperar();
			break;
		case 1:
			//vermelho
			IOWR(LEDVERMELHO_BASE, 0, 0);
			IOWR(LEDVERDE_BASE, 0, 1);
			IOWR(LEDAZUL_BASE, 0, 0);
			esperar();
			break;
		case 2:
			// azul
			IOWR(LEDVERMELHO_BASE, 0, 0);
			IOWR(LEDVERDE_BASE, 0, 0);
			IOWR(LEDAZUL_BASE, 0, 1);
			esperar();
			break;
		case 3:
			//branco
			IOWR(LEDVERMELHO_BASE, 0, 1);
			IOWR(LEDVERDE_BASE, 0, 1);
			IOWR(LEDAZUL_BASE, 0, 1);
			esperar();
			break;
		case 4:
			//magenta
			IOWR(LEDVERMELHO_BASE, 0, 0);
			IOWR(LEDVERDE_BASE, 0, 1);
			IOWR(LEDAZUL_BASE, 0, 1);
			esperar();
			break;
		default:
			break;
		}
}

void esperar(){
	usleep(100000);
}

void iniciaLCD(){
	usleep(15000);
	IOWR(LCD_16207_0_BASE, 0, 0x30);
	usleep(4100);
	IOWR(LCD_16207_0_BASE, 0, 0x30);
	usleep(100);
	IOWR(LCD_16207_0_BASE, 0, 0x30);
	usleep(5000);
	IOWR(LCD_16207_0_BASE, 0, 0x39);
	usleep(100);
	IOWR(LCD_16207_0_BASE, 0, 0x14);
	usleep(100);
	IOWR(LCD_16207_0_BASE, 0, 0x56);
	usleep(100);
	IOWR(LCD_16207_0_BASE, 0, 0x6D);
	usleep(100);
	IOWR(LCD_16207_0_BASE, 0, 0x70);
	usleep(2000);
	IOWR(LCD_16207_0_BASE, 0, 0x0C);
	usleep(2000);
	IOWR(LCD_16207_0_BASE, 0, 0x06);
	usleep(2000);
	IOWR(LCD_16207_0_BASE, 0, 0x01);
	usleep(2000);

	//printf("Acabou");
}

void escreveLCD(int posicao, int selecao){ //selecao=0 - ta no menu, selecao=1 entrou em uma opcao
	//printf("Escreve no LCD \n\n");

	char opcoes[5][15] = {"OPCAO 1", "OPCAO 2", "OPCAO 3","OPCAO 4", "OPCAO 5"} ;
	char entrar[5][15] = {"SELECIONOU 1", "SELECIONOU 2", "SELECIONOU 3", "SELECIONOU 4", "SELECIONOU 5"};
	usleep(100);

	IOWR(LCD_16207_0_BASE, 0, 0x02);//limpa display
	usleep(2000);
	IOWR(LCD_16207_0_BASE, 0, 0x01); // coloca cursor no inicio
	usleep(2000);

	if(selecao == 0){
		int i;

		for(i=0; i<strlen(opcoes);i++){
			IOWR(LCD_16207_0_BASE, 2, opcoes[posicao][i]);
			//printf("\n\nif posição : %c", opcoes[posicao][i] );
			usleep(1000);
		}
		//printf("Acabou de escrever  if \n\n");
	}
	else{
		int i;

		for(i=0; i<strlen(entrar);i++){
			IOWR(LCD_16207_0_BASE, 2, entrar[posicao][i]);
			//printf("\n\nElse posição : %c", entrar[posicao][i] );
			usleep(1000);
		}

		//printf("Acabou de escrever else \n\n");
	}

}













