// Header files
#include "msp430g2553.h"

// Constants
#define NOTE_VELOCITY   0x7F
#define NOTE_C          0x3C
#define NOTE_D          0x3E
#define NOTE_E          0x40
#define NOTE_F          0x41
#define NOTE_G          0x43
#define NOTE_A          0x45
#define NOTE_B          0x47

/*--------------------------------------------------
----------------------------------------------------

-----------------------MIDI-------------------------

----------------------------------------------------
----------------------------------------------------*/

// Send number of bytes (ArrayLength) in the array (TxArray) using the hardware UART 0
// Example usage:
//    UARTSendArray("Hello", 5);
//    int data[2]={1023, 235};
//    UARTSendArray(data, 4);
// Note: because the UART transmits bytes it is necessary to send two bytes for each integer hence the data
// length is twice the array length
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
   while(ArrayLength--) {           // Loop until StringLength == 0 and post decrement
      while(!(IFG2 & UCA0TXIFG));   // Wait for TX buffer to be ready for new data
      UCA0TXBUF = *TxArray;         // Write the character at the location specified py the pointer
      TxArray++;                    // Increment the TxString pointer to point to the next character
   }
}

// Setup the UART such that MIDI signals can be sent over the transmit line.
void setup_midi()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

   BCSCTL1 = CALBC1_1MHZ;     // Set DCO to 1MHz
   DCOCTL = CALDCO_1MHZ;      // Set DCO to 1MHz

   // Configure hardware UART
   P1SEL = BIT1 + BIT2 ;      // P1.1 = RXD, P1.2=TXD
   P1SEL2 = BIT1 + BIT2 ;     // P1.1 = RXD, P1.2=TXD
   UCA0CTL1 |= UCSSEL_2;      // Use SMCLK
   UCA0BR0 = 32;              // Set baud rate to 31250 with 1MHz clock (Data Sheet 15.3.13)
   UCA0BR1 = 0;               // Set baud rate to 31250 with 1MHz clock
   UCA0MCTL = UCBRS0;         // Modulation UCBRSx = 1
   UCA0CTL1 &= ~UCSWRST;      // Initialize USCI state machine
   IE2 |= UCA0RXIE;           // Enable USCI_A0 RX interrupt
}

void send_midi_signal(char command, char note_num, char note_vel)
{
   setup_midi();

   // Initialize inputs such that they can be passed onto the transmit line.
   unsigned char refval = command;
   unsigned char refval2 = note_num;
   unsigned char refval3 = note_vel;

   // Send the given values
   UARTSendArray(&refval, 1);
   UARTSendArray(&refval2, 1);
   UARTSendArray(&refval3, 1);

   // Wait a bit..
   int i = 100;
   for (;i>0;i--);
}

// UART receive interrupt
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
//data = UCA0RXBUF;
}

/*--------------------------------------------------
----------------------------------------------------

-----------------------ADC-------------------------

----------------------------------------------------
----------------------------------------------------*/

// ADC setup methods
// Note: these must be called before poll_ADC() in order to take
//    the measurement from the correct ADC.

void setup_ADC_one()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10IE + ADC10ON;
   ADC10CTL1 = INCH_3;        // input A3
   ADC10AE0 |= BIT3;          // P1.3 ADC option select
}

void setup_ADC_two()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10IE + ADC10ON;
   ADC10CTL1 = INCH_4;        // input A4
   ADC10AE0 |= BIT4;          // P1.4 ADC option select
}

void setup_ADC_three()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10IE + ADC10ON;
   ADC10CTL1 = INCH_5;        // input A5
   ADC10AE0 |= BIT5;          // P1.5 ADC option select
}

void setup_ADC_four()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10IE + ADC10ON;
   ADC10CTL1 = INCH_6;        // input A6
   ADC10AE0 |= BIT6;          // P1.6 ADC option select
}

void setup_ADC_five()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10ON;
   ADC10CTL1 = INCH_7;        // input A7
   ADC10AE0 |= BIT7;          // P1.7 ADC option select
}

void setup_ADC_six()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10ON;
   ADC10CTL1 = INCH_0;        // input A0
   ADC10AE0 |= BIT0;          // P1.0 ADC option select
}

void setup_ADC_seven()
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   BCSCTL1 = CALBC1_1MHZ;     // Set DCO, clock @1MHz
   DCOCTL = CALDCO_1MHZ;      // ADC
   ADC10CTL0 = ADC10SHT_0 + SREF_1 + REFON + REF2_5V + ADC10ON;
   ADC10CTL1 = INCH_1;        // input A1
   ADC10AE0 |= BIT1;          // P1.1 ADC option select
}

// Poll the ADC
// Note: make certain to setup the ADC that is to be polled before calling this method.
unsigned int poll_ADC()
{
   // Enable ADC interrupt
   ADC10CTL0 |= ADC10IE;

   // Start conversion and wait for the ADC to interrupt.
   ADC10CTL0 |= ENC + ADC10SC;      // Sampling and conversion start
   __bis_SR_register(CPUOFF + GIE); // LPM0, ADC10_ISR will force exit

   // Disable ADC interrupt
   ADC10CTL0 &= ~ADC10IE;

   // Return the measured ADC value
   return (unsigned int)ADC10MEM;
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
   __bic_SR_register_on_exit(CPUOFF);  // Clear CPUOFF bit from 0(SR)
}

/*--------------------------------------------------
----------------------------------------------------

---------------------CONTROL------------------------

----------------------------------------------------
----------------------------------------------------*/

void main(void)
{
   // Variable setup
   volatile unsigned int retval = 0;
   //volatile unsigned int q = 0x3FF;
   volatile unsigned int photo_on_one = 0x199;
   volatile unsigned int photo_on_two = 0x12C;
   //volatile unsigned int photo_off_two = 0x2E9;
   //volatile unsigned int photo_off_three = 0x2E9;
   //volatile int ispressed = 0;
   //volatile unsigned int temp;
   //unsigned int last_volume = 0x3ff;
   volatile unsigned int mode = 0;
   volatile unsigned int trigger1 = 0, trigger2 = 0, trigger3 = 0, trigger4 = 0,
                         trigger5 = 0, trigger6 = 0, trigger7 = 0;

   // Turn the volume up
   send_midi_signal(0xB0, 0x07, NOTE_VELOCITY);

   // Wait a bit..
   int i = 1000;
   for(; i > 0; i--)

   // Main loop
   while(1)
   {
      // Check if either in chord mode or beat mode
      if ((P2IN & BIT0) == BIT0)
         mode = 1;   // beat mode
      else
         mode = 0;   // chord mode

      // Check ADC 1
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_one();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger1) {
            trigger1 = 1;
            // chord mode & beat mode: play note C on channel 1
            send_midi_signal(0x90, NOTE_C, NOTE_VELOCITY);
            _delay_cycles(98000);
            send_midi_signal(0x80, NOTE_C, NOTE_VELOCITY);
         }
      }
      else
         trigger1 = 0;

      // Check ADC 2
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_two();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger2) {
            trigger2 = 1;
            
            if (mode == 0) {  // chord mode: play note D on channel 1
               send_midi_signal(0x90, NOTE_D, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x80, NOTE_D, NOTE_VELOCITY);
            }
            else  {           // beat mode: play note C on channel 2
               send_midi_signal(0x91, NOTE_C, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x81, NOTE_C, NOTE_VELOCITY);
            }
         }
      }
      else
         trigger2 = 0;

      // Check ADC 3
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_three();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger3) {
            trigger3 = 1;
            
            if (mode == 0) {  // chord mode: play note E on channel 1
               send_midi_signal(0x90, NOTE_E, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x80, NOTE_E, NOTE_VELOCITY);
            }
            else  {           // beat mode: play note C on channel 3
               send_midi_signal(0x92, NOTE_C, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x82, NOTE_C, NOTE_VELOCITY);
            }
         }
      }
      else
         trigger3 = 0;

      // Check ADC 4
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_four();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger4) {
            trigger4 = 1;
            
            if (mode == 0) {  // chord mode: play note F on channel 1
               send_midi_signal(0x90, NOTE_F, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x80, NOTE_F, NOTE_VELOCITY);
            }
            else  {           // beat mode: play note C on channel 4
               send_midi_signal(0x93, NOTE_C, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x83, NOTE_C, NOTE_VELOCITY);
            }
         }
      }
      else
         trigger4 = 0;

      // Check ADC 5
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_five();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger5) {
            trigger5 = 1;
            
            if (mode == 0) {  // chord mode: play note G on channel 1
               send_midi_signal(0x90, NOTE_G, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x80, NOTE_G, NOTE_VELOCITY);
            }
            else  {           // beat mode: play note C on channel 5
               send_midi_signal(0x94, NOTE_C, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x84, NOTE_C, NOTE_VELOCITY);
            }
         }
      }
      else
         trigger5 = 0;

      // Check ADC 6
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_six();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger6) {
            trigger6 = 1;
            
            if (mode == 0) {  // chord mode: play note A on channel 1
               send_midi_signal(0x90, NOTE_A, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x80, NOTE_A, NOTE_VELOCITY);
            }
            else  {           // beat mode: play note C on channel 6
               send_midi_signal(0x95, NOTE_C, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x85, NOTE_C, NOTE_VELOCITY);
            }
         }
      }
      else
         trigger6 = 0;

      // Check ADC 7
      // If our ADC value is less than some determined number, then
      // execute the consequent code.
      setup_ADC_seven();
      retval = poll_ADC();
      if(retval > photo_on_one)
      {
         if (!trigger7) {
            trigger7 = 1;
            
            if (mode == 0) {  // chord mode: play note B on channel 1
               send_midi_signal(0x90, NOTE_B, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x80, NOTE_B, NOTE_VELOCITY);
            }
            else  {           // beat mode: play note C on channel 7
               send_midi_signal(0x96, NOTE_C, NOTE_VELOCITY);
               _delay_cycles(98000);
               send_midi_signal(0x86, NOTE_C, NOTE_VELOCITY);
            }
         }
      }
      else
         trigger7 = 0;
   } 
}
