// библиотека для работы с ЖКИ 1602А
// зависит от библиотеки twi_lib.h
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

//unsigned char ADDR_LCD; // переменная для хранения адреса ЖКИ (объявить extern в модуле где используется функции ЖКИ)

#define lcd_putchar(x) lcd_putchar_buff(x, 1) 

#define I2C_SendPocketLCD(x) I2C_send_byte_LCD (ADDR_LCD, x) //макрос отправки пакетов LCD

#define LCD_RS_SET  I2C_SendPocketLCD (port_C |=0x01)   // установка лог. "1" на линии RS 
#define LCD_RS_CLR  I2C_SendPocketLCD (port_C &=~0x01)  // установка лог. "0" на линии RS 
#define LCD_RW_SET  I2C_SendPocketLCD (port_C |=0x02)   // установка лог. "1"(запись) R/W
#define LCD_RW_CLR  I2C_SendPocketLCD (port_C &=~0x02)  // установка лог. "0"(Чтение) R/W 
#define LCD_E_SET   I2C_SendPocketLCD (port_C |=0x04)  // установка лог. "1" на линии E 
#define LCD_E_CLR   I2C_SendPocketLCD (port_C &=~0x04) // установка лог. "0" на линии E  
#define LCD_BT_SET  I2C_SendPocketLCD (port_C|=0x08)   // установка лог. "1" на линии подсветки 
#define LCD_BT_CLR  I2C_SendPocketLCD (port_C&=~0x08)  // установка лог. "0" на линии подсветки 


#define LCD_COMMAND  0 // макрос, указывающий функции, что передаются команды 
#define LCD_DATA     1 // макрос, указывающий функции, что передаются данные

#define ADDR_DEV_LCD    0x27 // Адрес зависит от конкретного дисплея

#define RIGHT 1
#define LEFT 2
#define CENTER 3

// функция включения или отключения курсора LCD
#define LCD_CURSOR_ON  lcd_putbyte(DISPLAY_CONTROL|=0x02, LCD_COMMAND);
#define LCD_CURSOR_OFF lcd_putbyte(DISPLAY_CONTROL&=0xFD, LCD_COMMAND);

// функция включения или отключения LCD
#define LCD_ON  {lcd_putbyte(DISPLAY_CONTROL|=0x04, LCD_COMMAND);LCD_BT_SET;}
#define LCD_OFF {lcd_putbyte(DISPLAY_CONTROL&=0xFB, LCD_COMMAND);LCD_BT_CLR;}

// функция включения или отключения мигания курсора
#define LCD_CURSOR_BLINK_ON  lcd_putbyte(DISPLAY_CONTROL|=0x01, LCD_COMMAND);
#define LCD_CURSOR_BLINK_OFF lcd_putbyte(DISPLAY_CONTROL&=0xFE, LCD_COMMAND);

// макрос адреса + бит записи
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
// функция передачи тетрады в жки 
void lcd_putnibble(char tetrada);

// функция передачи байта в жки.
//char c - сам байт
//char rs - переменная, указывающая что передается:
//     rs = 0 - команда (устанавливается линия RS)
//     rs = 1 - данные (сбрасывается линия RS) */
void lcd_putbyte(char byte, char rs);

// функция передачи байта данных в жки.
// в текущую позицию курсора
void lcd_putchar_buff(char byte, uchar putbuff); 

// функция инициализации работы жки в 4-битном режиме, без курсора 
void lcd_init(unsigned char ADDR);

// функция очистки дисплея и возврата курсора в начальную позицию
void lcdClear(void);

// функция перемещения курсора в заданную позицию
// col - номер знакоместа по горизонтальной оси (от 0 до 15)
// row - номер строки (0 или 1) */
void lcdGoToXY(char row, char col);

//функция посылки команды ЖКИ
void lcd_command_set(unsigned char COMM);

// функция очистки позиции курсора
void lcdClrChar(char row, char col);

// функция перемешения курсора в начало
void lcd_cursor_home(void);

// функция проверяет корректность колонки и строки
// если что-то выходит за пределы то возвращаем 1 иначе 0
int lcdChkRowCol(char row, char col);

// функция выводит строку с заданной позиции
// если строка не влезает на ЖКИ то она обрезается
void lcdSendString(char row, char col, char stroka[]);

// функция заполняет таблицу соответствия русских символов глифам (образам)
void set_table_convert(void);

//Функция загрузки графического символа в память LCD
void lcd_set_user_gliff(unsigned char Simb, unsigned char NumSimb);

//инициализируем N-ный элемент в массиве table_convert
void init_table_convert(uchar N, uchar CP1251, uchar G1, uchar G2, uchar G3, uchar G4, uchar G5, uchar G6, uchar G7, uchar G8);

// функция конвертации символов из CP1251 в коды знокогенератора ЖКИ и загрузка при необходимости глифов
unsigned char convert_to_rus(unsigned char simb);

// функция заполнения программного буфера ЖКИ
void set_buff(unsigned char simb);

// функция ищит свободное место в карте глифов
char searh_free_space_glif(uchar simb, uchar Nsimb);

// функция выводит символ с заданной позиции 
void lcd_put_char(char row, char col, char simb);

// функция выводит строку в заданную физическую строку дисплея
// прижатую влево, вправо или по центру в зависимости от pos = RIGTH, LEFT, CENTER
// (строка должна заканчиваться 0-м)
// если строка не влезает на строку на ЖКИ то она обрезается
void lcd_put_string_LRC(const int pos,const int row, const char stroka[]);
//==============================================================================

int I2C_send_byte_LCD(char ADDR, char DATA);
//==============================================================================


void lcdSendNumInt(char row, char col, int num);
void lcdSendNumFloat(char row, char col, float num);
void lcdSendBlinkString(char row, char col, char string[]);
void lcdClrChars(char row, char col, int len);
void lcdBlinkEmpty(char row, char col, char string[]);





