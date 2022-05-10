
#include "driverLCD.h"

int main(void)
	 {
		 unsigned char str[]="Hello from ENSEA !";
		 init_lcd();
		 LCDInit();
		 lcdSendChar(0x42);
		 //Ecriture de Hello from ENSEA sur les deux lignes
		 lcdSendStr (str);
		 while(1);
		 return 0;
		 }
	 
