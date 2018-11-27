

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

	char comandoCWMode[] = "AT+CWMODE=1";
	mandeComando(strlen(comandoCWMode), comandoCWMode);


	char comandoCWJAP[] = "AT+CWJAP=\"WLessLEDS\",\"HelloWorldMP31\"";
	mandeComando(strlen(comandoCWJAP), comandoCWJAP);

	char conectaTCP[] = "AT+CIPSTART=\"TCP\",\"192.168.1.103\",1883";
	mandeComando(strlen(conectaTCP), conectaTCP);


	char pacoteConexao[] = {
						  0x10, 0x12, 0x00, 0x04, 0x4D, 0x51, 0x54, 0x54,
						  0x04, 0x02, 0x00, 0x14, 0x00, 0x05, 0x4E, 0x69,  //o 3 de traz pra frente era 0x06 e agora é 0x05
						  0x6F, 0x73, 0x20, 0x32

		};


	char comandoSendConexao[] = "AT+CIPSEND=20\r\n";
		mandeComandoSend(sizeof(comandoSendConexao), comandoSendConexao,sizeof(pacoteConexao), pacoteConexao);





		usleep(1000000);


	/*char comandoSendConexao[] = "AT+CIPSEND=20";
	mandeComando(strlen(comandoSendConexao), comandoSendConexao);*/

	/*char conectaTCP[] = "AT+CIPSTART=\"TCP\",\"192.168.1.103\",1883";
	mandeComando(strlen(conectaTCP), conectaTCP);*/


	//usleep(1000);

	/*************************************************************/
	//conectaMQTT(); // o conecta Mqtt deve estar no botão de seleção
	/**************************************************************/

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
			conectaMQTT(opcao); // passar opcao como parametro
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

void conectaMQTT(int posicao){


//MQTT versão 4
/*
	char pacoteConexao[] = {
					  0x10, 0x12, 0x00, 0x04, 0x4D, 0x51, 0x54, 0x54,
					  0x04, 0x02, 0x00, 0x14, 0x00, 0x05, 0x4E, 0x69,  //o 3 de traz pra frente era 0x06 e agora é 0x05
					  0x6F, 0x73, 0x20, 0x32

	};
*/
/*
	char pacotePublish[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
						0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
							0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x31};

*/

	char pacotePublish[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
							0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
							0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x31};



		//IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,posicao);


		switch(posicao){
			case 0:
				;
			break;
			case 1:
				pacotePublish[26] = 0x32;
			break;
			case 2:
				pacotePublish[26] = 0x33;
			break;
			case 3:
				pacotePublish[26] = 0x34;
			break;
			case 4:
				pacotePublish[26] = 0x35;
			break;
			default:
				break;
			}







	// 12345 em hexa = 0x31 0x32 0x33 0x34 0x35

	//desconecta MQTT
	char pacoteDisconnect[] = {
			0xe0, 0x00
	};
	//usleep(1000);






	//usleep(1000);


	//usleep(1000);

/*
	char comandoSendConexao[] = "AT+CIPSEND=20\r\n";
	mandeComandoSend(sizeof(comandoSendConexao), comandoSendConexao,sizeof(pacoteConexao), pacoteConexao);





	usleep(1000000);*/
	char comandoSendPublish[] = "AT+CIPSEND=27\r\n";
	usleep(1000000);
	mandeComandoSend(sizeof(comandoSendPublish), comandoSendPublish,sizeof(pacotePublish), pacotePublish);



	usleep(1000000);

	//char comandoSendDisconnectMQTT[] = "AT+CIPSEND=2\r\n";
	//mandeComandoSend(sizeof(comandoSendDisconnectMQTT), comandoSendDisconnectMQTT,sizeof(pacoteDisconnect), pacoteDisconnect);



	//usleep(1000000);

	//char comandoDesconectaTCP[] = "AT+CIPCLOSE=0";
	//mandeComando(strlen(comandoDesconectaTCP), comandoDesconectaTCP);




}

void publish(int posicao){
	//pacotes de publish para cada mensagem
	char mensagem0[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
			0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
			0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x31};
	char mensagem1[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
			0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
			0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x32};
	char mensagem2[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
			0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
			0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x33};
	char mensagem3[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
			0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
			0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x34};
	char mensagem4[] = {0x30, 0x19, 0x00, 0x0B, 0x74, 0x65, 0x73, 0x74, 0x65,
			0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x53, 0x45, 0x4c,
			0x45, 0x43, 0x49, 0x4f, 0x4e, 0x4f, 0x55, 0x20, 0x35};



	switch(posicao){
	case 0:
		//conectaMQTT();
	break;
	case 1:
		//conectaMQTT();
	break;
	case 2:
		//conectaMQTT();
	break;
	case 3:
		//conectaMQTT();
	break;
	case 4:
		//conectaMQTT();
	break;
	default:
		break;
	}


}


void mandeComandoSend(int tamanhoComando, char* comando, int tamanhoPacote, char* pacote){


	alt_putstr(comando);






        	char c ="";
        	while(1){
                		//IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,'t');
                		if((IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<7))){
                			c = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );

                			IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,c);

                			if(c == '>'){
                				for(int i=0; i<tamanhoPacote; i++){
                					while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<6)));
                			    	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, pacote[i]);
                				}
                				while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<6)));
                				IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, '\r');

                				while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<6)));
                			     IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, '\n');

                			     leituraUart();
                			     //IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,'t');
                			     return;
                			}
                		}
                	}


}


void leituraUart(){
	char c= "";
	while(1){
        		//IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,'t');
        		if((IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<7))){
        			c = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );

        			IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,c);

        			if(c == 'K'){
        				return;
        			}
        		}
        	}

}


void mandeComando(int tamanho, char* comando){


	alt_putstr(comando);
	alt_putstr("\r\n");
	//usleep(1000);
	//IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,'T');

	char c ="";
	while(1){
		//IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,'t');
		if((IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) &(1<<7))){
			//IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,'a');
			c = IORD_ALTERA_AVALON_UART_RXDATA( UART_0_BASE );
			IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_0_BASE,c);

			if(c == 'K'){
				return;
			}
		}
	}


}


/*******************************************************************************/
/*void escreveTXUart(int tamanho, char* comando){

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


}*/




/*
 * SSID - WLessLEDS
 * Senha - HelloWorldMP31
 * Endereço do Broker - rpibroker.local
 * ip: 192.168.1.103   -d (pub)
 */



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













