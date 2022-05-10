
void init_lcd(void);
void write4bData(int data);
void setEN(void);
void clearEN(void);
void setRS(void);
void clearRS(void);
void setRW(void);
void clearRW(void);
void waitN(int n);
void sendCMD8b(int cmd);
void LCDInit(void);

void lcdSendChar(unsigned char c);
void lcdSendStr( unsigned char *str);

void lcdFixePosition (unsigned char position);
void initBarreCGRAM(void);
void bargraph (int value);
void convert(int value);
