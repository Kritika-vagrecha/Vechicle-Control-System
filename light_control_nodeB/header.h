//--------- Delay functions declarations ---------
extern void delay_sec(const unsigned int);
extern void delay_ms(const unsigned int);
extern void delay_us(const unsigned int);
//--------- LCD functions declarations ---------
extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_atoi(int);
extern void lcd_atof(float);
extern void lcd_cgram(void);
extern void lcd_cgram_dash(unsigned int *,unsigned int);
extern void lcd_time(unsigned char,unsigned char,unsigned char);
extern void lcd_date(unsigned char,unsigned char,unsigned char);
extern void lcd_day(unsigned char);
//--------- UART0 functions declarations ---------
extern void uart0_init(unsigned int);
extern void uart0_tx(unsigned char);
extern void uart0_tx_string(char *);
extern unsigned char uart0_rx(void);
extern void uart0_hex(unsigned char);
extern void uart0_ascii(unsigned char); 
extern void uart0_rx_string(char *,int);
extern void uart0_float(float);
extern void uart0_integer(int); 
extern void uart0_int_hex(unsigned int);
//--------- ADC functions declarations ---------
extern unsigned short int adc_read(unsigned char);
extern void adc_init(void);
//--------- Interrupt functions declarations ---------
//--- Uart0 Interrupt funtions ---
extern void uart0_handler(void) __irq;
extern void config_vic_for_uart0(void);
extern void en_uart0_interrupt(void);
extern void ds_uart0_interrupt(void);
//--- Timer1 Interrupt funtions ---
extern void timer1_handler(void) __irq;
extern void config_vic_for_timer1(void);
extern void en_timer1_interrupt(void);
extern void ds_timer1_interrupt(void);
//--- Ext0 Interrupt funtions ---
extern void ext0_handler(void) __irq;
extern void config_vic_for_ext0(void);
extern void en_ext0_interrupt(void);
//--- Ext1 Interrupt funtions ---
extern void ext1_handler(void) __irq;
extern void config_vic_for_ext1(void);
extern void en_ext1_interrupt(void);
extern void ds_ext1_interrupt(void);
//--------- SPI functions declarations ---------
extern void spi0_init(void);
extern unsigned char spi0(unsigned char);
//--------- MCP3204 functions declarations ---------
extern unsigned short int read_mcp3204(unsigned char);
#define CS0 (1<<7)
//--------- MCP3208 functions declarations ---------
extern unsigned short int read_mcp3208(unsigned char);
//--------- I2C functions declarations ---------
extern void i2c_init(void);
extern void i2c_byte_write_frame(unsigned char,unsigned char,unsigned char);
extern unsigned char i2c_byte_read_frame(unsigned char,unsigned char);
//--------- CAN1 functions declarations ---------
//---- CAN1 structure declaration ----
typedef struct CAN1_MSG{
	unsigned int id,byteA,byteB;
	unsigned char dlc,rtr;
}CAN1;
//---- CAN2 structure declaration ----
typedef struct CAN2_MSG{
	unsigned int id,byteA,byteB;
	unsigned char dlc,rtr;
}CAN2;
//---- CAN1 function declaration ----
extern void can1_init(void);
extern void can1_tx(CAN1);
extern void can1_rx(CAN1 *);
//---- CAN2 function declaration ----
extern void can2_init(void);
extern void can2_tx(CAN2);
extern void can2_rx(CAN2 *);
//--- CAN1 Interrupt funtions ---
extern void en_can1_interrupt(void);
extern void config_vic_for_can1(void);
//--- CAN2 Interrupt funtions ---
extern void en_can2_interrupt(void);
extern void config_vic_for_can2(void);
//--- CAN2 Interrupt funtions ---
extern float read_distance(void);
