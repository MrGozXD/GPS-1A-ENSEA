#include "stm32f4xx.h"
#include "driverLCD.h"


const short int retourne[16]={0x0,0x8,0x4,0xC,0x2,0xA,0x6,0xE,0x1,0x9,0x5,0xD,0x3,0xB,0x7,0xF};
const short int bar[6]={0x00,0x10,0x18,0x1C,0x1E,0x1F};
volatile char data[6]={0x33,0x32,0x28,0x0F,0x14,0x01};


void init_lcd(void) {
	int *pt_RCC_APB2ENR;
	pt_RCC_APB2ENR = (int*) 0x40021018;
	*pt_RCC_APB2ENR  |=(1<<4);
	//RCC->APB2ENR |=(1<<4); //initialisation de l'horloge
	//GPIOC->CRL=(GPIOC->CRL & 0xFFFF0000)|(0x3333); //GPIOC->CRL= 0x44443333;
	//GPIOC->CRH=(GPIOC->CRH & 0xFFF000FF)|(0x33300); //GPIOC->CRH= 0x44433344;
	GPIOC->MODER=0x03F000FF;
}
void LCDInit(void)
{ int j=0;
	int data[6]={0x33,0x32,0x28,0x0F,0x14,0x01};

	for (j=0;j<6;j++) {
		sendCMD8b(data[j]);
	}
}


void write4bData(int data) {
	data=data & 0x0000000F;												// On garde les 4 LSB
	GPIOC->ODR=(GPIOC->ODR & 0xFFFFFFF0)|(data);
}

void setEN(void) {
	GPIOC->ODR |=(1<<10);
}
void clearEN(void) {
	GPIOC->ODR &=~(1<<10);
}
void setRS(void) {
	GPIOC->ODR |=(1<<12);
}
void clearRS(void) {
	GPIOC->ODR &=~(1<<12);
}
void setRW(void) {
	GPIOC->ODR |=(1<<11);
}
void clearRW(void) {
	GPIOC->ODR &=~(1<<11);
}


void sendCMD8b(int cmd) {
	clearRS();
	clearRW();
	int LSBcmd = cmd;
	int MSBcmd = cmd>>4;	//write4bData n'envoie que les 4 LSB donc il faut right shift les 4 MSB pour les envoyer
	
	//Ecriture des MSB de cmd par Write4bData
	write4bData(MSBcmd);
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (10);
	
	//Ecriture des LSB de cmd par Write4bData
	write4bData(LSBcmd); 
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (8000);
}

void lcdSendChar (unsigned char c) {
	setRS();
	clearRW();
	unsigned char LSBc = c;
	unsigned char MSBc = c>>4;	//write4bData n'envoie que les 4 LSB donc il faut right shift les 4 MSB pour les envoyer
	
	//Ecriture des MSB de cmd par Write4bData
	write4bData(MSBc);
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (10);
	
	//Ecriture des LSB de cmd par Write4bData
	write4bData(LSBc); 
	waitN (10);
	setEN();
	waitN (200);
	clearEN();
	waitN (10);
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
			lcdFixePosition(0x40);// On revient à la ligne
		}
		 lcdSendChar (str[i]);
		 i=i+1;
	}
}

/*
void initBarreCGRAM (void) {
	int i,j;
	sendCMD8b(0x40); //Ecriture dans la GC RAM
	for (i=0;i<=5;i++) {
		for (j=0;j<8;j++) {
			lcdSendChar(bar[i]); //Ecriture du caractère
		}
	}
	lcdFixePosition(0); //Retour au mode normal
}
*/
/*
void bargraph(int val) {
	int i,q,r;
	q=val/5;
	r=val%5;
	//Calcul du nombre de charactère à afficher
	for (i=1;i<=q;i++) {
		lcdSendChar (0x05);
		if (i==16) {
			lcdFixePosition(0x40);// On revient à la ligne
		}
	}
	lcdSendChar (r);
}
*/
