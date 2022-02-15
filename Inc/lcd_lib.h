// ���������� ��� ������ � ��� 1602�
// ������� �� ���������� twi_lib.h
// ��� � 4-� ������ ������ � �������� ����� I2C
// ��������� ������� ���� � ��������� cp1251
// ���� ��������� ������ � ����� �� 1 �� 6 �� ��������� ���� �������
// ��� 1-������� �����
// ��� 2-������� ����
// ��� 3-������� �����
// ��� 4-������� ������
// ��� 5-����/�����
// ��� 6-���� �������
// ��� ����������� ����� ����� (�������� lcd_put_char(10,1, '\4'); ��� lcd_put_string(1,1,"menu\6");)
// ���������� ������ � ��������� 2-� �������� ��� ����� ���������� I2C

//unsigned char ADDR_LCD; // ���������� ��� �������� ������ ��� (�������� extern � ������ ��� ������������ ������� ���)

#define lcd_putchar(x) lcd_putchar_buff(x, 1) 

#define I2C_SendPocketLCD(x) I2C_send_byte_LCD (ADDR_LCD, x) //������ �������� ������� LCD

#define LCD_RS_SET  I2C_SendPocketLCD (port_C |=0x01)   // ��������� ���. "1" �� ����� RS 
#define LCD_RS_CLR  I2C_SendPocketLCD (port_C &=~0x01)  // ��������� ���. "0" �� ����� RS 
#define LCD_RW_SET  I2C_SendPocketLCD (port_C |=0x02)   // ��������� ���. "1"(������) R/W
#define LCD_RW_CLR  I2C_SendPocketLCD (port_C &=~0x02)  // ��������� ���. "0"(������) R/W 
#define LCD_E_SET   I2C_SendPocketLCD (port_C |=0x04)  // ��������� ���. "1" �� ����� E 
#define LCD_E_CLR   I2C_SendPocketLCD (port_C &=~0x04) // ��������� ���. "0" �� ����� E  
#define LCD_BT_SET  I2C_SendPocketLCD (port_C|=0x08)   // ��������� ���. "1" �� ����� ��������� 
#define LCD_BT_CLR  I2C_SendPocketLCD (port_C&=~0x08)  // ��������� ���. "0" �� ����� ��������� 


#define LCD_COMMAND  0 // ������, ����������� �������, ��� ���������� ������� 
#define LCD_DATA     1 // ������, ����������� �������, ��� ���������� ������

#define ADDR_DEV_LCD    0x27 // ����� ������� �� ����������� �������

#define RIGHT 1
#define LEFT 2
#define CENTER 3

// ������� ��������� ��� ���������� ������� LCD
#define LCD_CURSOR_ON  lcd_putbyte(DISPLAY_CONTROL|=0x02, LCD_COMMAND);
#define LCD_CURSOR_OFF lcd_putbyte(DISPLAY_CONTROL&=0xFD, LCD_COMMAND);

// ������� ��������� ��� ���������� LCD
#define LCD_ON  {lcd_putbyte(DISPLAY_CONTROL|=0x04, LCD_COMMAND);LCD_BT_SET;}
#define LCD_OFF {lcd_putbyte(DISPLAY_CONTROL&=0xFB, LCD_COMMAND);LCD_BT_CLR;}

// ������� ��������� ��� ���������� ������� �������
#define LCD_CURSOR_BLINK_ON  lcd_putbyte(DISPLAY_CONTROL|=0x01, LCD_COMMAND);
#define LCD_CURSOR_BLINK_OFF lcd_putbyte(DISPLAY_CONTROL&=0xFE, LCD_COMMAND);

// ������ ������ + ��� ������
#define ADDR_DEV_WRITE(x)  (x << 1)&0xFE

typedef struct 
{
  unsigned char SimbCP1251;
  unsigned char gliff[8];
} user_simb;

typedef struct 
{
  unsigned char SimbCP1251_RUS;
  unsigned char SimbCP1251_LAT;
} Rus_Lat;

typedef unsigned char uchar;

//==============================================================================
// ������� �������� ������� � ��� 
void lcd_putnibble(char tetrada);

// ������� �������� ����� � ���.
//char c - ��� ����
//char rs - ����������, ����������� ��� ����������:
//     rs = 0 - ������� (��������������� ����� RS)
//     rs = 1 - ������ (������������ ����� RS) */
void lcd_putbyte(char byte, char rs);

// ������� �������� ����� ������ � ���.
// � ������� ������� �������
void lcd_putchar_buff(char byte, uchar putbuff); 

// ������� ������������� ������ ��� � 4-������ ������, ��� ������� 
void lcd_init(unsigned char ADDR);

// ������� ������� ������� � �������� ������� � ��������� �������
void lcdClear(void);

// ������� ����������� ������� � �������� �������
// col - ����� ���������� �� �������������� ��� (�� 0 �� 15)
// row - ����� ������ (0 ��� 1) */
void lcdGoToXY(char row, char col);

//������� ������� ������� ���
void lcd_command_set(unsigned char COMM);

// ������� ������� ������� �������
void lcdClrChar(char row, char col);

// ������� ����������� ������� � ������
void lcd_cursor_home(void);

// ������� ��������� ������������ ������� � ������
// ���� ���-�� ������� �� ������� �� ���������� 1 ����� 0
int lcdChkRowCol(char row, char col);

// ������� ������� ������ � �������� �������
// ���� ������ �� ������� �� ��� �� ��� ����������
void lcdSendString(char row, char col, char stroka[]);

// ������� ��������� ������� ������������ ������� �������� ������ (�������)
void set_table_convert(void);

//������� �������� ������������ ������� � ������ LCD
void lcd_set_user_gliff(unsigned char Simb, unsigned char NumSimb);

//�������������� N-��� ������� � ������� table_convert
void init_table_convert(uchar N, uchar CP1251, uchar G1, uchar G2, uchar G3, uchar G4, uchar G5, uchar G6, uchar G7, uchar G8);

// ������� ����������� �������� �� CP1251 � ���� ��������������� ��� � �������� ��� ������������� ������
unsigned char convert_to_rus(unsigned char simb);

// ������� ���������� ������������ ������ ���
void set_buff(unsigned char simb);

// ������� ���� ��������� ����� � ����� ������
char searh_free_space_glif(uchar simb, uchar Nsimb);

// ������� ������� ������ � �������� ������� 
void lcd_put_char(char row, char col, char simb);

// ������� ������� ������ � �������� ���������� ������ �������
// �������� �����, ������ ��� �� ������ � ����������� �� pos = RIGTH, LEFT, CENTER
// (������ ������ ������������� 0-�)
// ���� ������ �� ������� �� ������ �� ��� �� ��� ����������
void lcd_put_string_LRC(const int pos,const int row, const char stroka[]);
//==============================================================================

int I2C_send_byte_LCD(char ADDR, char DATA);
//==============================================================================


void lcdSendNumInt(char row, char col, int num);
void lcdSendNumFloat(char row, char col, float num);
void lcdSendBlinkString(char row, char col, char string[]);
void lcdClrChars(char row, char col, int len);
void lcdBlinkEmpty(char row, char col, char string[]);





