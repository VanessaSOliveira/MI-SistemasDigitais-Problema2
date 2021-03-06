
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

void iniciaESP01(){

	 alt_putstr("AT"); //Envia comando teste em serial

	 char response[2] = {'0','0'};
	 int i =0;
	 while(!strcmp(response, 'OK')){ //O ESP deve responder com um OK
		 response[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }


}

void conectaESP01(){


	 alt_putstr("AT+CWMODE_CUR=Station mode"); //Seta como uma station para se conectar a uma rede
	 //Parece que o comando de conex�o s� funciona se ele estiver neste modo


	 char response[200]; //Responde com a instru��o AT enviada
	 int i =0;
	 while(!strcmp(response, 'AT+CWMODE_CUR=SoftwareAP mode')){ //O ESP deve responder com um OK
		 response[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }

	 char response2[2]; //Responde tamb�m com um OK
	 i =0;
	 while(!strcmp(response2, 'OK')){ //O ESP deve responder com um OK
		 response2[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }


	 alt_putstr("AT+CWJAP_CUR=HomeNetwork,12345678");

	 char response3[200]; //Responde com a instru��o AT enviada
	 i =0;
	 while(!strcmp(response3, 'AT+CWJAP_CUR=HomeNetwork,12345678')){ //O ESP deve responder com um OK
		 response3[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }

	 char response4[2]; //Responde tamb�m com um OK
	 i =0;
	 while(!strcmp(response4, 'OK')){ //O ESP deve responder com um OK
		 response4[i]= IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		 i++;
	 }


}


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

	printf("Acabou");
}

void escreveLCD(int posicao, int selecao){ //selecao=0 - ta no menu, selecao=1 entrou em uma opcao
	printf("Escreve no LCD \n\n");

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
			printf("\n\nif posi��o : %c", opcoes[posicao][i] );
			usleep(1000);
		}
		printf("Acabou de escrever  if \n\n");
	}
	else{
		int i;

		for(i=0; i<strlen(entrar);i++){
			IOWR(LCD_16207_0_BASE, 2, entrar[posicao][i]);
			printf("\n\nElse posi��o : %c", entrar[posicao][i] );
			usleep(1000);
		}

		printf("Acabou de escrever else \n\n");
	}

}






