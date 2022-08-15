void SystemInit(){};
	//***************     System Clock Enable      ************************* //
#define SYSCTL_RCGCGPIO_R 	(*((volatile unsigned long*) 0x400FE608)) 

  //********* PORT A Initializations. Base Address is 0x40025000 **********//
#define GPIO_PORTA_DATA_R		(*((volatile unsigned long*) 0x400043FC))
#define GPIO_PORTA_DIR_R		(*((volatile unsigned long*) 0x40004400))
#define GPIO_PORTA_DEN_R		(*((volatile unsigned long*) 0x4000451C))
#define GPIO_PORTA_PDR_R		(*((volatile unsigned long*) 0x40004514))
#define GPIO_PORTA_PUR_R		(*((volatile unsigned long*) 0x40004510))
	
	//********* PORT B Initializations. Base Address is 0x40005000 **********//
#define GPIO_PORTB_DATA_R		(*((volatile unsigned long*) 0x400053FC))
#define GPIO_PORTB_DIR_R		(*((volatile unsigned long*) 0x40005400))
#define GPIO_PORTB_DEN_R		(*((volatile unsigned long*) 0x4000551C))
#define GPIO_PORTB_PDR_R		(*((volatile unsigned long*) 0x40005514))
#define GPIO_PORTB_PUR_R		(*((volatile unsigned long*) 0x40005510))
	
//********* Defining all Macros ***********//
#define CLK_PORTA 	  0x01          // clock enable for port A
#define CLK_PORTB	  0x02          // clock enable for port B

#define PA2           0x04
#define PA3           0x08
#define PA4           0x10
#define PA5           0x20
#define PA6           0x40
#define PA7           0x80

#define PB0			  0x01          //IN1
#define PB1	          0x02          //IN2
#define PB2			  0x04          //IN3
#define PB3			  0x08          //IN4
#define PB4           0x10
#define PB5           0x20
#define PB6           0x40

void Delay_ms(int time_ms);
//Timers Configurations start here

// Timer 1 base address
# define TM_BASE 0x40031000
// Peripheral clock enabling for timer and GPIO
# define RCGC_TIMER_R *( volatile unsigned long *)0x400FE604
# define RCGC2_GPIO_R *( volatile unsigned long *)0x400FE108
# define CLOCK_GPIOF 0x00000020 // Port F clock control
# define SYS_CLOCK_FREQUENCY 16000000
// General purpose timer register definitions
# define GPTM_CONFIG_R *( volatile long *)( TM_BASE + 0x000 )
# define GPTM_TA_MODE_R *( volatile long *)( TM_BASE + 0x004 )
# define GPTM_CONTROL_R *( volatile long *)( TM_BASE + 0x00C )
# define GPTM_INT_MASK_R *( volatile long *)( TM_BASE + 0x018 )
# define GPTM_INT_CLEAR_R *( volatile long *)( TM_BASE + 0x024 )
# define GPTM_TA_IL_R *( volatile long *)( TM_BASE + 0x028 )
# define GPTM_TA_MATCH_R *( volatile long *)( TM_BASE + 0x030 )
// GPIO PF2 alternate function configuration
# define GPIO_PORTF_AFSEL_R *(( volatile unsigned long *)0x40025420 )
# define GPIO_PORTF_PCTL_R *(( volatile unsigned long *)0x4002552C )
# define GPIO_PORTF_DEN_R *(( volatile unsigned long *)0x4002551C )
// Timer config and mode bit field definitions
# define TIM_16_BIT_CONFIG 0x00000004 // 16- bit timer
# define TIM_PERIODIC_MODE 0x00000002 // Periodic timer mode
# define TIM_A_ENABLE 0x00000001 // Timer A enable control
# define TIM_PWM_MODE 0x0000000A // Timer in PWM mode
# define TIM_CAPTURE_MODE 0x00000004 // Timer capture mode
// Timer1 A reload value for 1 kHz PWM frequency
# define TIM_A_INTERVAL 16000 // Timer reload value for
// 1 kHz PWM frequency at
// clock frequency of 16 MHz
// 16 ,000 ,000/16000
// = 1 kHz
#define TIM_A_MATCH 							 16000 // Timer match value for 75%     //PF2, right motor, 6400 = 60%, 9600 = 40%, 10400 = 35%

// duty cycle
// Timer and GPIO intialization and configuration
void Timer1A_Init ( void )
{
// Enable the clock for port F and Timer1
RCGC2_GPIO_R |= CLOCK_GPIOF ;
RCGC_TIMER_R |= 0x02 ;
// Configure PortF pin 2 as Timer1 A output
GPIO_PORTF_AFSEL_R |= 0x00000004 ;
GPIO_PORTF_PCTL_R |= 0x00000700 ; // Configure as timer CCP pin
GPIO_PORTF_DEN_R |= 0x00000004 ;
// Enable the clock for Timer 1
GPTM_CONTROL_R &= ~( TIM_A_ENABLE ); // disable timer 1 A
// Timer1 A configured as 16- bit timer
GPTM_CONFIG_R |= TIM_16_BIT_CONFIG ;
// Timer1 A in periodic timer , edge count and PWM mode
GPTM_TA_MODE_R |= TIM_PWM_MODE ;
GPTM_TA_MODE_R &= ~( TIM_CAPTURE_MODE );
// Make PWM frequency 1 kHz using reload value of 1600010.11. SUMMARY OF KEY CONCEPTS 345
GPTM_TA_IL_R = TIM_A_INTERVAL ;
// Configure PWM duty cycle value ( should be less than 16000)
//GPTM_TA_MATCH_R = 11200 ;
// Enable timer1 A
GPTM_CONTROL_R |= TIM_A_ENABLE ;
}

//Timer A ends here
//Timer B starts here

//PWM on PF3

// Timer 1 base address
#define TM_BASE 0x40031000
// Peripheral clock enabling for timer and GPIO
#define RCGC_TIMER_R                *( volatile unsigned long *)0x400FE604
#define RCGC2_GPIO_R                *( volatile unsigned long *)0x400FE108
#define CLOCK_GPIOF                 0x00000020 // Port F #define SYS_CLOCK_FREQUENCY         16000000
// General purpose timer register definitions
#define GPTM_CONFIG_R                *( volatile long *)( TM_BASE + 0x000 )
#define GPTM_TB_MODE_R               *( volatile long *)( TM_BASE + 0x008 )
#define GPTM_CONTROL_R               *( volatile long *)( TM_BASE + 0x00C )
#define GPTM_INT_MASK_R              *( volatile long *)( TM_BASE + 0x018 )
#define GPTM_INT_CLEAR_R             *( volatile long *)( TM_BASE + 0x024 )
#define GPTM_TB_IL_R                 *( volatile long *)( TM_BASE + 0x02C )
#define GPTM_TB_MATCH_R              *( volatile long *)( TM_BASE + 0x034 )


// GPIO PF2 alternate function configuration
#define GPIO_PORTF_AFSEL_R *(( volatile unsigned long *)0x40025420 )
#define GPIO_PORTF_PCTL_R  *(( volatile unsigned long *)0x4002552C )
#define GPIO_PORTF_DEN_R   *(( volatile unsigned long *)0x4002551C )

// Timer config and mode bit field definitions
#define TIM_16_BIT_CONFIG          0x00000004   
#define TIM_PERIODIC_MODE          0x00000002   
#define TIM_B_ENABLE               0x00000100
#define TIM_PWM_MODE               0x0000000A  
#define TIM_CAPTURE_MODE           0x00000004  

// Timer1 A reload value for 1 kHz PWM frequency
#define TIM_B_INTERVAL             16000         
#define TIM_B_MATCH                16000   //PF3, left motor                                  8000 = 50%, 11200 = 30%                        

// Timer and GPIO intialization and configuration
void Timer1B_Init ( void )
{
    // Enable the clock for port F and Timer1
    RCGC2_GPIO_R |= CLOCK_GPIOF ;
    RCGC_TIMER_R |= 0x02 ;
    // Configure PortF pin 2 as Timer1 A output
    GPIO_PORTF_AFSEL_R |= 0x00000008 ;
    GPIO_PORTF_PCTL_R |= 0x00007000 ;                
	  GPIO_PORTF_DEN_R |= 0x00000008 ;
	    // Enable the clock for Timer 1
    GPTM_CONTROL_R &= ~( TIM_B_ENABLE );         // disable timer 1 A
    // Timer1 A configured as 16- bit timer
    GPTM_CONFIG_R |= TIM_16_BIT_CONFIG ;
    // Timer1 A in periodic timer , edge count and PWM mode
    GPTM_TB_MODE_R |= TIM_PWM_MODE ;
    GPTM_TB_MODE_R &= ~( TIM_CAPTURE_MODE );
    // Make PWM frequency 1 kHz using reload value of 16000
    GPTM_TB_IL_R = TIM_B_INTERVAL ;
    // Configure PWM duty cycle value ( should be less than 
    //GPTM_TB_MATCH_R = TIM_B_MATCH ;
     // Enable timer1 A
     GPTM_CONTROL_R |= TIM_B_ENABLE ;
}




//************   Delay Function ************//
void Delay(long value)
{
	int l;
	for(l = 0; l<value; l++);
}

//************ Variables to store the output of sensors ************//


//************ main function **************//

int dutyCycle(double duty);

int motorLeftDuty, motorRightDuty;


