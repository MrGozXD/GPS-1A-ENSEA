#include "stm32f4xx.h"
#include "driverLCD.h"


const short int bar[6]={0x00,0x10,0x18,0x1C,0x1E,0x1F};
volatile char data[6]={0x33,0x32,0x28,0x0F,0x14,0x01};


void init_lcd(void) {


	RCC->AHB1ENR  |=0x10; 
	GPIOE->MODER=(GPIOE->MODER & 0xFFFFC000)|(0x00001555);  //Paramétrage de nos entrées et sorties
	
}
void LCDInit(void)
{ int j=0;
	int data[6]={0x33,0x32,0x28,0x0D,0x1C,0x01};

	for (j=0;j<6;j++) {
		sendCMD8b(data[j]);
	}
	}


void write4bData(int data) {
	data=data & 0x0000000F;
	GPIOE->ODR=(GPIOE->ODR & 0xFFFFFFF0)|(data);
}

void setEN(void) {
	GPIOE->ODR |=(1<<4);
}
void clearEN(void) {
	GPIOE->ODR &=~(1<<4);
}

void setRW(void) {
	GPIOE->ODR |=(1<<5);
}
void clearRW(void) {
	GPIOE->ODR &=~(1<<5);
}

void setRS(void) {
	GPIOE->ODR |=(1<<6);
}
void clearRS(void) {
	GPIOE->ODR &=~(1<<6);
}


void sendCMD8b(int cmd) {
	int tmp;
	tmp=cmd&0xF0;
	tmp=tmp>>4;
	clearRS();
	clearRW();
	
	//Ecriture des MSB de cmd par Write4bData
	write4bData(tmp);
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (10);
	
	//Ecriture des LSB de cmd par Write4bData
	tmp=cmd;
	tmp=tmp&0xF;
	write4bData(tmp); // on masque le MSB et on retourne le reste
	
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (8000);
}

void lcdSendChar (unsigned char c) {
	int tmp;
	tmp=c&0xF0;
	tmp=tmp>>4;
	setRS();
	clearRW();
	
	//Ecriture des MSB de cmd par Write4bData
	write4bData(tmp);
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (10);
	
	//Ecriture des LSB de cmd par Write4bData
	tmp=c&0xF;
	write4bData(tmp); // on masque le MSB et on retourne le reste
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (20);
}

void lcdFixePosition(unsigned char position) {
	int cmd;
	
	// Choix de la position du curseur
	cmd=0x80|position;
	sendCMD8b(cmd);
}

void lcdSendStr (unsigned char *str) {
	int i=0;
	while(str[i]!='\0') {
		if (i==16) {
			lcdFixePosition(0x40);// On revient � la ligne
		}
		 lcdSendChar (str[i]);
		 i=i+1;
	}
}