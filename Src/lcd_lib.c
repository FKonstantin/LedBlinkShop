/* Возможна некорректная работа дисплея при использование форматирования текста по правому краю*/
// библиотека для работы с ЖКИ 1602 и 2004
// ЖКИ в 4-х битном режиме и работает через I2C
// поддержка русских букв в кодировке cp1251
// если указывать символ с кодом от 1 до 6 то выводятся спец символы
// код 1-стрелка вверх
// код 2-стрелка вниз
// код 3-стрелка влево
// код 4-стрелка вправо
// код 5-плюс/минус
// код 6-знак градуса
// код указывается через слешь (например lcd_put_char(10,1, '\4'); или lcd_put_string(1,1,"menu\6");)
// фактически работа с китайским 2-х строчным ЖКИ через переходник I2C

#include "lcd_lib.h"
#include <string.h>
#include "stm32f1xx_hal.h"

#define ARRAY_SIZE(arr)  (sizeof arr / sizeof(uchar))

unsigned char Acol = 0; //создаем переменную для хранения позиции курсора колонка 
unsigned char Arow = 0; //создаем переменную для хранения позиции курсора строка
uint8_t column = 0; /////
unsigned char ADDR_LCD; // переменная для хранения адреса ЖКИ (объявить extern в модуле где используется функции ЖКИ)
unsigned char DISPLAY_CONTROL = 0x08; //создаем переменную для запоминания состояния ЖКИ и курсора (объявить extern в модуле где используется функции ЖКИ)
unsigned char port_C = 0; //создаем переменную эквивалент регистра порта (объявить extern в модуле где используется функции ЖКИ)

user_simb table_convert[53];// __eeprom
Rus_Lat table_rus_lat[19];//__eeprom
uchar buff[80];
uchar buff_map[80];
uchar map[8];
static char str[33];
uint8_t buf[1]={0}; 
int lenColumn = 0; /////
extern I2C_HandleTypeDef hi2c1; 


__STATIC_INLINE void delay_us(__IO uint32_t micros);
                   
                      

//==============================================================================
//инициализируем N-ный элемент в массиве table_convert
void init_table_convert(uchar N, uchar CP1251, uchar G1, uchar G2, uchar G3, uchar G4, uchar G5, uchar G6, uchar G7, uchar G8)
{
  table_convert[N].SimbCP1251=CP1251;
  table_convert[N].gliff[0]=G1; table_convert[N].gliff[1]=G2;
  table_convert[N].gliff[2]=G3; table_convert[N].gliff[3]=G4;
  table_convert[N].gliff[4]=G5; table_convert[N].gliff[5]=G6;
  table_convert[N].gliff[6]=G7; table_convert[N].gliff[7]=G8;
}
//==============================================================================
// функция заполняет таблицу соответствия русских символов глифам (образам)
// а так же соответствие начертанию русских символов английским
void set_table_convert()
{
  
  init_table_convert(0, 193, 0x1F, 0x11, 0x10, 0x1E, 0x11, 0x11, 0x1E, 0x00); // Б
  init_table_convert(1, 222, 0x12, 0x15, 0x15, 0x1D, 0x15, 0x15, 0x12, 0x00); // Ю
  init_table_convert(2, 247, 0x00, 0x00, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x00); // ч
  init_table_convert(3, 196, 0x0F, 0x05, 0x05, 0x05, 0x09, 0x11, 0x1F, 0x11); // Д
  init_table_convert(4, 195, 0x1F, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00); // Г
  init_table_convert(5, 223, 0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11, 0x00); // Я
  init_table_convert(6, 248, 0x00, 0x00, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x00); // ш
  init_table_convert(7, 214, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x01); // Ц
  init_table_convert(8, 168, 0x0A, 0x00, 0x1E, 0x10, 0x1C, 0x10, 0x1E, 0x00); // Ё
  init_table_convert(9, 225, 0x03, 0x0C, 0x10, 0x1E, 0x11, 0x11, 0x0E, 0x00); // б
  init_table_convert(10, 250, 0x00, 0x00, 0x18, 0x08, 0x0E, 0x09, 0x0E, 0x00); // ъ
  init_table_convert(11, 217, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x01); // Щ
  init_table_convert(12, 198, 0x15, 0x15, 0x15, 0x0E, 0x15, 0x15, 0x15, 0x00); // Ж
  init_table_convert(13, 226, 0x00, 0x00, 0x1C, 0x12, 0x1C, 0x12, 0x1C, 0x00); // в
  init_table_convert(14, 251, 0x00, 0x00, 0x11, 0x11, 0x1D, 0x13, 0x1D, 0x00); // ы
  init_table_convert(15, 228, 0x00, 0x00, 0x0F, 0x05, 0x09, 0x11, 0x1F, 0x11); // д
  init_table_convert(16, 199, 0x1E, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x1E, 0x00); // З
  init_table_convert(17, 227, 0x00, 0x00, 0x1F, 0x11, 0x10, 0x10, 0x10, 0x00); // г
  init_table_convert(18, 252, 0x00, 0x00, 0x10, 0x10, 0x1C, 0x12, 0x1C, 0x00); // ь
  init_table_convert(19, 244, 0x00, 0x04, 0x04, 0x0E, 0x15, 0x15, 0x0E, 0x04); // ф
  init_table_convert(20, 200, 0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x00); // И
  init_table_convert(21, 184, 0x0A, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00); // ё
  init_table_convert(22, 253, 0x00, 0x00, 0x0E, 0x11, 0x07, 0x11, 0x0E, 0x00); // э
  init_table_convert(23, 246, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x01); // ц
  init_table_convert(24, 201, 0x15, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x00); // Й
  init_table_convert(25, 230, 0x00, 0x00, 0x15, 0x15, 0x0E, 0x15, 0x15, 0x00); // ж
  init_table_convert(26, 254, 0x00, 0x00, 0x12, 0x15, 0x1D, 0x15, 0x12, 0x00); // ю
  init_table_convert(27, 249, 0x00, 0x00, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x01); // щ
  init_table_convert(28, 203, 0x0F, 0x05, 0x05, 0x05, 0x05, 0x15, 0x09, 0x00); // Л
  init_table_convert(29, 231, 0x00, 0x00, 0x1E, 0x01, 0x06, 0x01, 0x1E, 0x00); // з
  init_table_convert(30, 255, 0x00, 0x00, 0x0F, 0x11, 0x0F, 0x05, 0x09, 0x00); // я
  init_table_convert(31, 207, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00); // П
  init_table_convert(32, 232, 0x00, 0x00, 0x11, 0x13, 0x15, 0x19, 0x11, 0x00); // и
  init_table_convert(33, 211, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x08, 0x10, 0x00); // У
  init_table_convert(34, 233, 0x00, 0x0A, 0x04, 0x11, 0x13, 0x15, 0x19, 0x00); // й
  init_table_convert(35, 212, 0x04, 0x0E, 0x15, 0x15, 0x15, 0x0E, 0x04, 0x00); // Ф 
  init_table_convert(36, 234, 0x00, 0x00, 0x12, 0x14, 0x18, 0x14, 0x12, 0x00); // к
  init_table_convert(37, 215, 0x11, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00); // Ч
  init_table_convert(38, 235, 0x00, 0x00, 0x0F, 0x05, 0x05, 0x15, 0x09, 0x00); // л
  init_table_convert(39, 216, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x00); // Ш
  init_table_convert(40, 236, 0x00, 0x00, 0x11, 0x1B, 0x15, 0x11, 0x11, 0x00); // м
  init_table_convert(41, 218, 0x18, 0x08, 0x08, 0x0E, 0x09, 0x09, 0x0E, 0x00); // Ъ
  init_table_convert(42, 237, 0x00, 0x00, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00); // н
  init_table_convert(43, 219, 0x11, 0x11, 0x11, 0x19, 0x15, 0x15, 0x19, 0x00); // Ы
  init_table_convert(44, 239, 0x00, 0x00, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x00); // п
  init_table_convert(45, 221, 0x0E, 0x11, 0x01, 0x07, 0x01, 0x11, 0x0E, 0x00); // Э
  init_table_convert(46, 242, 0x00, 0x00, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x00); // т
  init_table_convert(47, 1, 0x00, 0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x00); // стрелка вверх
  init_table_convert(48, 2, 0x00, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04, 0x00); // стрелка вниз
  init_table_convert(49, 3, 0x00, 0x00, 0x04, 0x08, 0x1F, 0x08, 0x04, 0x00); // стрелка влево
  init_table_convert(50, 4, 0x00, 0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00); // стрелка вправо
  init_table_convert(51, 5, 0x00, 0x00, 0x04, 0x0E, 0x04, 0x00, 0x0E, 0x00); // плюс/минус
  init_table_convert(52, 6, 0x00, 0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00); // знак градуса
 
  table_rus_lat[0].SimbCP1251_RUS=192; table_rus_lat[0].SimbCP1251_LAT=65;  // A
  table_rus_lat[1].SimbCP1251_RUS=194; table_rus_lat[1].SimbCP1251_LAT=66;  // B
  table_rus_lat[2].SimbCP1251_RUS=197; table_rus_lat[2].SimbCP1251_LAT=69;  // E
  table_rus_lat[3].SimbCP1251_RUS=202; table_rus_lat[3].SimbCP1251_LAT=75;  // K
  table_rus_lat[4].SimbCP1251_RUS=204; table_rus_lat[4].SimbCP1251_LAT=77;  // M
  table_rus_lat[5].SimbCP1251_RUS=205; table_rus_lat[5].SimbCP1251_LAT=72;  // H
  table_rus_lat[6].SimbCP1251_RUS=206; table_rus_lat[6].SimbCP1251_LAT=79;  // O
  table_rus_lat[7].SimbCP1251_RUS=208; table_rus_lat[7].SimbCP1251_LAT=80;  // P
  table_rus_lat[8].SimbCP1251_RUS=209; table_rus_lat[8].SimbCP1251_LAT=67;  // C
  table_rus_lat[9].SimbCP1251_RUS=210; table_rus_lat[9].SimbCP1251_LAT=84;  // T
  table_rus_lat[10].SimbCP1251_RUS=213; table_rus_lat[10].SimbCP1251_LAT=88;  // X
  table_rus_lat[11].SimbCP1251_RUS=220; table_rus_lat[11].SimbCP1251_LAT=98;  // b
  table_rus_lat[12].SimbCP1251_RUS=224; table_rus_lat[12].SimbCP1251_LAT=97;  // a
  table_rus_lat[13].SimbCP1251_RUS=229; table_rus_lat[13].SimbCP1251_LAT=101; // e
  table_rus_lat[14].SimbCP1251_RUS=238; table_rus_lat[14].SimbCP1251_LAT=111; // o
  table_rus_lat[15].SimbCP1251_RUS=240; table_rus_lat[15].SimbCP1251_LAT=112; // p
  table_rus_lat[16].SimbCP1251_RUS=241; table_rus_lat[16].SimbCP1251_LAT=99;  // c
  table_rus_lat[17].SimbCP1251_RUS=243; table_rus_lat[17].SimbCP1251_LAT=121; // y
  table_rus_lat[18].SimbCP1251_RUS=245; table_rus_lat[18].SimbCP1251_LAT=120; // x
 
}
//==============================================================================
// функция передачи тетрады в жки (4-х бит в 4-х проводном режиме) 
void lcd_putnibble(char tetrada)
{
    tetrada<<=4;
    LCD_E_CLR;
    delay_us(2);
    port_C=port_C&0x0F;
    port_C=port_C|tetrada;
    I2C_SendPocketLCD (port_C);
    LCD_E_SET;
    delay_us(2);
    LCD_E_CLR;
    delay_us(100);
}
//==============================================================================
// функция передачи байта в жки.
//char c - сам байт
//char rs - переменная, указывающая что передается:
//     rs = 0 - команда (устанавливается линия RS)
//     rs = 1 - данные (сбрасывается линия RS) */
void lcd_putbyte(char byte, char rs)
{
    char high_byte=0;
    
    high_byte=byte>>4;
    if (rs==LCD_COMMAND) LCD_RS_CLR;
    else                 LCD_RS_SET;
    lcd_putnibble(high_byte);
    lcd_putnibble(byte);
}
//==============================================================================
// функция ищит свободное место в карте глифов
char searh_free_space_glif(uchar simb, uchar Nsimb)
{
  uchar i, err = 1;
  uchar retval;
  int free_pos = -1;
  
  for(i = 0; i < 8; i++)
  {
    if(simb==map[i]){retval=i; err=0; break;}
    if(map[i]==0) {free_pos=i; break; }
  }
  
  if((err==1)&&(free_pos>-1)) 
    { 
      lcd_set_user_gliff(Nsimb,free_pos); 
      retval=free_pos; 
      map[free_pos]=table_convert[Nsimb].SimbCP1251;
    }
  
  if((err==1)&&(free_pos==(-1))) retval='*';
  return retval;
}
//==============================================================================
// функция конвертации символов из CP1251 в коды знокогенератора ЖКИ и загрузка при необходимости глифов
unsigned char convert_to_rus(unsigned char simb)
{
  uchar i;
  uchar retval;
  
  retval = simb;
	
  for(i = 0; i < 53; i++)
  {
    if(simb == table_convert[i].SimbCP1251)
     {
		retval = searh_free_space_glif(simb,i); 
		break;
     }
    if(i<19)
    {
     if(simb == table_rus_lat[i].SimbCP1251_RUS) 
     {
       retval = table_rus_lat[i].SimbCP1251_LAT;
       break;
     }
    }
  }
  
  return retval;
}
//==============================================================================
// функция заполнения программного буфера ЖКИ
void set_buff(unsigned char simb)
{
	uchar i,j;
	uchar err;
	

	buff[(20*Arow)+Acol] = simb;
	buff_map[(20*Arow)+Acol] = simb;
	// проверяем карту глифов и удаляем неиспользуемые
	for(i = 0; i < 8; i++)
	{
		err = 0;
				
		for(j = 0; j < 80; j++)
		{ 
			if((map[i] == buff_map[j]) && (buff_map[j] != 0))
			{
				err = 1;
			} 
		}
		
		if(err == 0)
		{
			map[i] = 0;
		}
	}
	
	if((simb > 127) || ((simb > 0) && (simb < 7)))
	{
		buff[(20 * Arow)+Acol] = convert_to_rus(simb);
	}
}

//==============================================================================
// функция передачи символа (кода символа) в жки для отображения 
// в текущую позицию курсора
void lcd_putchar_buff(char byte, uchar putbuff)
{
	uchar i;
	int ratio = 0;	
	
		
	set_buff(byte); 
	Acol++;
	
	if(putbuff == 1)
	{		
		if(Arow == 0) 
		{			
			lcdGoToXY(Arow, column);	
			ratio = column;
			delay_us(500);			
		}
		else if(Arow == 1) 
		{			
			lcdGoToXY(Arow, column);	
			delay_us(500);
			ratio = 20 + column;
		}
		else if(Arow == 2) 
		{		
			lcdGoToXY(Arow, column);	
			delay_us(500);
			ratio = 40 + column;
		}
		else if(Arow == 3) 
		{			
			lcdGoToXY(Arow, column);	
			delay_us(500);
			ratio = 60 + column;
		}				
		
		for(i = 0; i < lenColumn; i++)  
		{ 																	
			lcd_putbyte(buff[i + ratio],LCD_DATA);												
		}
		
		memset(buff, 0, sizeof(buff));
	}
}
//==============================================================================
// функция инициализации работы жки в 4-битном режиме, без курсора 
void lcd_init(unsigned char ADDR)
{
    uchar i;  
  
    set_table_convert();
    
    for(i = 0; i < 20; i++)
	{
		buff[i] = 20; 
		buff_map[i] = 20; 
		str[i] = 20;
	}
    for(i = 0; i < 8; i++)
	{
		map[i] = 0;
	}
	
    DISPLAY_CONTROL = 0x08;
    ADDR_LCD = ADDR;
    HAL_Delay(150);
    port_C = 0;
    LCD_RS_CLR;
    delay_us(50);
    LCD_RW_CLR;
    delay_us(50);
    LCD_BT_SET;
    
    lcd_putnibble(0x30);
    lcd_putnibble(0x2);
    lcd_putnibble(0xC);
	
	lcd_putnibble(0x1);
    lcd_putnibble(0x80);
    lcd_putnibble(0xC0);	    
}
//==============================================================================
// функция очистки дисплея и возврата курсора в начальную позицию
void lcdClear()
{
    uchar i;
    lcd_putbyte(0x01, LCD_COMMAND);
    
	for(i = 0; i < 20; i++)
	{ 
		buff[i] = 20; 
		buff_map[i] = 20; 
		str[i] = 20;
	}
    for(i=0;i<8;i++)
	{
		map[i] = 0;
	}
	
    delay_us(1500);
}
//==============================================================================
// функция перемещения курсора в заданную позицию
// col - номер знакоместа по горизонтальной оси (от 0 до 15)
// row - номер строки (0 или 1) */
void lcdGoToXY(char row, char col)
{
	if(row == 0)
	{
		lcd_putbyte((col|0x80), LCD_COMMAND);
		HAL_Delay(1);
	}
	else if(row == 1)
	{
		lcd_putbyte(((0x40+col)|0x80), LCD_COMMAND);
		HAL_Delay(1);
	}
	else if(row == 2)
	{
		lcd_putbyte(((0x14+col)|0x80), LCD_COMMAND);
		HAL_Delay(1);
	}
	else if(row == 3)
	{
		lcd_putbyte(((0x54+col)|0x80), LCD_COMMAND);
		HAL_Delay(1);
	}	
	
	Acol = col;
    Arow = row;			
}
//==============================================================================
// функция очистки позиции курсора
void lcdClrChar(char row, char col)
{
	char tcol, trow;


	column = col;
	
	if(lcdChkRowCol(row, col)==0)
	{
		lenColumn = 1; /////
		tcol=Acol; trow=Arow;
		lcdGoToXY(row, col);
		lcd_putchar(' '); 
		lcdGoToXY(trow, tcol);
	}
	
	column = 0; /////
}
//==============================================================================
// функция перемешения курсора в начало
void lcd_cursor_home()
{
  lcd_putbyte(0x2, LCD_COMMAND);  
  delay_us(50);
  Acol=0; Arow=0;
}
//==============================================================================
// функция выводит строку с заданной позиции (строка должна заканчиваться 0-м)
// если строка не влезает на ЖКИ то она переходит на другую
void lcdSendString(char row, char col, char stroka[])
{
	uchar i = 0;
	char simb;		


	if(lcdChkRowCol(row, col) == 1)
	{
		col = 0; 
		row = 0;
	}

	lcdGoToXY(row, col);
	column = col;
	
	for(int i = 0; i < 20; i++)
	{
		if(stroka[i] == '\0')
		{
			lenColumn = i;
			break;
		}
		
		if(i == 19)
		{
			lenColumn = 20;
			break;
		}
	}
	
	for(i = 0; stroka[i] != 0; i++) 
	{		
		simb = stroka[i];
		if(stroka[i + 1] == 0)
		{
			lcd_putchar_buff(simb, 1); 
			break; 
		}
		else
		{
			lcd_putchar_buff(simb, 0);
		}
	}

	column = 0;
	lenColumn = 0;
}
//==============================================================================
// функция проверяет корректность колонки и строки
// если что-то выходит за пределы то курсор устанавливается в начальную позицию
int lcdChkRowCol(char row, char col)
{
	char err = 0;
	int x,y;

	x = col; y = row;
	
	if((x > 19)||(x < 0))
	{
		err = 1;  
	}

	if((y > 3)||(y < 0))
	{
		err = 1;
	}	
	
	return err;
}
//==============================================================================
//Функция загрузки графического символа в память LCD
void lcd_set_user_gliff(unsigned char NSimb, unsigned char NumSimb)
{
  unsigned char addr_user_simb;
  
  if(NumSimb>7) NumSimb=7;
  addr_user_simb=(0x40 | (NumSimb<<3));
  for (unsigned char i=0; i<8; i++)
  {
   lcd_putbyte(addr_user_simb++, LCD_COMMAND);
   lcd_putbyte(table_convert[NSimb].gliff[i],LCD_DATA);
  }
  lcdGoToXY(Arow, Acol);
}
//==============================================================================
// функция выводит символ с заданной позиции 
void lcd_put_char(char row, char col, char simb)
{
  //char tcol, trow;

	column = col;
	
	if(lcdChkRowCol(row, col)==0)
	{
		lenColumn = 2; /////
		//tcol=Acol; trow=Arow;
		//set_buff(simb); 
		//lcd_putchar_buff(simb, 0);
		lcd_putchar_buff(simb, 1);
		//lcdGoToXY(row, col);
		//lcd_putchar(' '); 
		//lcdGoToXY(trow, tcol);
	}
	
	column = 0; 
	
	/*if(lcdChkRowCol(col, row)==1){col=0; row=0;}
  lcdGoToXY(col, row);
  lcd_putchar_buff(simb,1);*/
}
//==============================================================================
// функция выводит строку в заданную физическую строку дисплея
// прижатую влево, вправо или по центру в зависимости от pos = RIGTH, LEFT, CENTER
// (строка должна заканчиваться 0-м)
// если строка не влезает на строку на ЖКИ то она обрезается
void lcd_put_string_LRC(const int pos,const int row, const char stroka[])
{
  int len_str;
  int i, j, k;  
  char col;
    
  
  len_str=strlen(stroka);
    
  if(pos==CENTER)
   {
     i=8-(int)(len_str/2);
     if(i<0) 
     {
       col=0;
       i=(int)(len_str/2)-8;
       k=0;
       for(j=i; j<len_str; j++) { str[k]=stroka[j];  k++;  if(k==20) break; }
     }
     else
      {
        col=i;
        for(j=0; j<len_str; j++) str[j]=stroka[j];
        str[len_str]=0x0;
      }
     lcdSendString(col,row,str);
   }
  //-------------
  if(pos==LEFT)
   {
    col=0;
    if(len_str>19)len_str=19;
    for(j=0; j<len_str; j++) str[j]=stroka[j];
    str[len_str]=0x0;
    lcdSendString(col,row,str);
   }
  //-------------
  if(pos==RIGHT)
   {
     if((20-len_str)<0)
     {
      col=0; 
      for(j=0; j<20; j++) str[j]=stroka[(len_str-20)+j];
     }
     else
     {
      col=20-len_str;
      for(j=0; j<len_str; j++) str[j]=stroka[j];
     }
      
     lcdSendString(col,row,str);
   }  
}
//==============================================================================
int I2C_send_byte_LCD(char ADDR, char DATA)
{
    int err = 0;
 
 
    buf[0] = DATA;
    HAL_I2C_Master_Transmit(&hi2c1,(uint16_t) ADDR_DEV_LCD << 1, buf, 1 ,1000); //0x4E

 return err;
}

//------------------------------------------------------------------------------
__STATIC_INLINE void delay_us(__IO uint32_t micros)
{
	micros *=(SystemCoreClock / 1000000) / 5;
	while (micros--);
}

//------------------------------------------------------------------------------
/**
  * @brief  Sends a integer number to the LCD in the specified position
  * @param  row - LCD line number. 
  *			@arg 0 - 1 line
  *			@arg 1 - 2 line
  *			@arg 2 - 3 line
  *			@arg 3 - 4 line
  * @param  col - LCD column number. 
  *			@arg 0 - 1 column
  *			...
  *			@arg 19 - 20 column
  * @param  num - integer number for display
  * @retval None
  */
void lcdSendNumInt(char row, char col, int num)
{	
	char string[4] = {0, 0, 0, 0};
	
	
	sprintf(string, "%d", num);
	lcdGoToXY(row, col);	
	lcdSendString(row, col, string);
}

//------------------------------------------------------------------------------
/**
  * @brief  Sends a float number to the LCD in the specified position
  * @param  row - LCD line number. 
  *			@arg 0 - 1 line
  *			@arg 1 - 2 line
  *			@arg 2 - 3 line
  *			@arg 3 - 4 line
  * @param  col - LCD column number. 
  *			@arg 0 - 1 column
  *			...
  *			@arg 19 - 20 column
  * @param  num - integer number for display
  * @retval None
  */
void lcdSendNumFloat(char row, char col, float num)
{	
	char string[5] = {0, 0, 0, 0};
	
	
	sprintf(string, "%.1f", num);
	lcdGoToXY(row, col);	
	lcdSendString(row, col, string);
}

//------------------------------------------------------------------------------
/**
  * @brief  Blinks 2 times with the specified text
  * @param  row - LCD line number. 
  *			@arg 0 - 1 line
  *			@arg 1 - 2 line
  *			@arg 2 - 3 line
  *			@arg 3 - 4 line
  * @param  col - LCD column number. 
  *			@arg 0 - 1 column
  *			...
  *			@arg 19 - 20 column
  * @param  string[] - The text which want to blink
  * @retval None
  */
void lcdSendBlinkString(char row, char col, char string[])
{
	uint16_t lenStr = 0;
	uint16_t tmpCol;
	
	
	lenStr = strlen(string);
	tmpCol = col;	
	
	for(int i = 0; i < lenStr; i++)
	{		
		lcdSendString(row, tmpCol, " ");	
		tmpCol++;		
	}
	
	HAL_Delay(70);
	lcdSendString(row, col, string);
	HAL_Delay(70);	
	tmpCol = col;	
	
	for(int i = 0; i < lenStr; i++)
	{		
		lcdSendString(row, tmpCol, " ");	
		tmpCol++;		
	}
	
	HAL_Delay(70);
	lcdSendString(row, col, string);
}

//------------------------------------------------------------------------------
/**
  * @brief  Clears the row from the specified column position
  * @param  row - LCD line number. 
  *			@arg 0 - 1 line
  *			@arg 1 - 2 line
  *			@arg 2 - 3 line
  *			@arg 3 - 4 line
  * @param  col - LCD column number. 
  *			@arg 0 - 1 column
  *			...
  *			@arg 19 - 20 column
  * @param  len - The number of columns to be cleared. Since @param  col
  * @retval None
  */
void lcdClrChars(char row, char col, int len)
{
	if((len < 0) && (len > 19))
	{
		return;
	}
	
	for(int i = 0; i < len; i++)
	{		
		lcdSendString(row, col, " ");	
		col++;		
	}
}

//------------------------------------------------------------------------------
/**
  * @brief  Blinks 2 times with the specified text. Write "Empty." Then displays 
			the specified text again
  * @param  row - LCD line number. 
  *			@arg 0 - 1 line
  *			@arg 1 - 2 line
  *			@arg 2 - 3 line
  *			@arg 3 - 4 line
  * @param  col - LCD column number. 
  *			@arg 0 - 1 column
  *			...
  *			@arg 19 - 20 column
  * @param   string[] - The text which want to blink
  * @retval None
  */
void lcdBlinkEmpty(char row, char col, char string[])
{
	uint16_t lenStr = 0;
	
	
	lenStr = strlen(string);
	lcdSendBlinkString(row, col, string);
	lcdClrChars(row, col, lenStr);
	lcdSendString(row, col, "Empty");
	HAL_Delay(500);
	lcdClrChars(row, col, lenStr);
	lcdSendString(row, col, string);
}















