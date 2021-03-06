

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
#include "altera_avalon_jtag_uart_regs.h"


main(){


	unsigned int bEntrar, bVoltar, bSubir, bDescer;
	int opcao =0;

	iniciaLCD();

	escreveLCD(0,0);
	char comando[] = "AT+CWMODE=1\r\n";

	//printf("%d",strlen(comando));
	mandeComando(strlen(comando), comando);

	char comando2[] = "AT+CWJAP=\"WLessLEDS\",\"HelloWorldMP31\"\r\n";
	mandeComando(strlen(comando2), comando2);



	/*
	 * CIPMUX
	 * CIPStart
	 */

	char comando3[] = "AT+CIPMUX=0\r\n";
	mandeComando(strlen(comando3), comando3);

	char comando4[] = "AT+CIPMODE=0\r\n";
	mandeComando(strlen(comando4), comando4);

	char comando5[] = "AT+CIPSTART=\"TCP\",\"192.168.1.102\",1883\r\n";
	mandeComando(strlen(comando5), comando5);

	conectaMQTT();

	//char comando5[] = "AT+CIPSEND=\r\n";
	//mandeComando(strlen(comando2), comando5);

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

void conectaMQTT(){
	char mensagemConexao[] = {0x10};
	char mensagemConexao2[] = {0xc2};
	char comando5[] = "AT+CIPSEND=1\r\n";
	mandeComando(strlen(comando5), comando5);
	mandeComando(strlen(mensagemConexao), mensagemConexao);

	char comando6[] = "AT+CIPSEND=1\r\n";
	mandeComando(strlen(comando6), comando6);
	mandeComando(strlen(mensagemConexao2), mensagemConexao2);

	char comando7[] = "AT+CIPCLOSE=0\r\n";
	mandeComando(strlen(comando7), comando7);

}

void enviaMensagem(){
	//AT+CIPCLOSE=0
}

void mandeComando(int tamanho, char* comando){


	alt_putstr(comando);

	char c ="";
	while(1){

		if((IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<7))){
			c = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );

				IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,c);

				if(c == 'K'){
					return;
				}


		}
	}


}




/*******************************************************************************/
void escreveTXUart(int tamanho, char* comando){

	unsigned long status = 0;
	    int i;

	    char data[200] ="";
	    char a = "";

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
				data[i] = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );

				printf(" %c  ",data[i]);

					if(data[i] == 'K'){
						for(int a =0;a<strlen(data);a++)
							printf(" %c  ",data[a]);
						return;
					}

				//printf("STATUS DEPOIS DA LEITURA - %x \n",IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE));
					i++;
				}


}




/*
 * SSID - WLessLEDS
 * Senha - HelloWorldMP31
 * Endere�o do Broker - rpibroker.local
 * ip: 192.168.1.102   -d (pub)
 */



void escreveLCDGenerico(char* palavra, int n){ // n � o tamanho da palavra


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
			//printf("\n\nif posi��o : %c", opcoes[posicao][i] );
			usleep(1000);
		}
		//printf("Acabou de escrever  if \n\n");
	}
	else{
		int i;

		for(i=0; i<strlen(entrar);i++){
			IOWR(LCD_16207_0_BASE, 2, entrar[posicao][i]);
			//printf("\n\nElse posi��o : %c", entrar[posicao][i] );
			usleep(1000);
		}

		//printf("Acabou de escrever else \n\n");
	}

}













