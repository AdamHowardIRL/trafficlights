struct State {

  unsigned long Out;

  unsigned long Time; 

  unsigned long Next[4];};
typedef const struct State STyp;

#define goN   0

#define waitN 1

#define goE   2

#define waitE 3

STyp FSM[4]={

 {0x21,3000,{goN,waitN,goN,waitN}},

 {0x22, 500,{goE,goE,goE,goE}},

 {0x0C,3000,{goE,goE,waitE,waitE}},

 {0x14, 500,{goN,goN,goN,goN}}};

unsigned long S;  // index to the current state

unsigned long Input;
unsigned long oldInput;
int gotInput; 


typedef volatile struct {
 uint32_t DR;
 uint32_t RSR_ECR;
 uint8_t reserved1[0x10];
 const uint32_t FR;
 uint8_t reserved2[0x4];
 uint32_t LPR;
 uint32_t IBRD;
 uint32_t FBRD;
 uint32_t LCR_H;
 uint32_t CR;
 uint32_t IFLS;
 uint32_t IMSC;
 const uint32_t RIS;
 const uint32_t MIS;
 uint32_t ICR;
 uint32_t DMACR;
} pl011_T;
 
enum {
 RXFE = 0x10,
 TXFF = 0x20,
};
 
pl011_T * const UART0 = (pl011_T *)0x101f1000;
pl011_T * const UART1 = (pl011_T *)0x101f2000;
pl011_T * const UART2 = (pl011_T *)0x101f3000;
 
static inline char upperchar(char c) {
 if((c >= 'a') && (c <= 'z')) {
  return c - 'a' + 'A';
 } else {
  return c;
 }
}
 
static void uart_echo(pl011_T *uart) {
 if ((uart->FR & RXFE) == 0) {
  	Input = 0;
	gotInput = 1;
        if (uart->DR == 'E')
           Input |= 2;
        if (uart->DR == 'N')
           Input |= 1;
 }
}
 
void c_entry() {
 for(;;) {
	int out = FSM[S].Out;
	 usleep(1000);
	if(out&1){
	printf("Green on north");
	}
	if(out&2){
	printf("Yellow on north");
	}
	if(out&4){
	printf("Red on north");
	}
	if(out&8){
	printf("Green on west");
	}
	if(out&16){
	printf("Yellown on west");
	}
	if(out&32){
	printf("Red on west");
	}

  uart_echo(UART0);
  uart_echo(UART1);
  uart_echo(UART2);
 }
}

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
 
void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}
