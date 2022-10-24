/* *************************************************************************************************
**  File Name    : ADCAN.c
**  Description  : ADC conversion (microcontroller PIC18F2685) and CAN communication (MCP2561) with 
               multiple analog sensors (refer to Sensorics design) 
** ************************************************************************************************/

#include "ADCAN.h"
#include "ADCAN_vars.c"
#include "ADCAN_funs.c"

void main()
{
   //configuracio inicial programa
   Initial_Config(); //configuracio inicial del micro
   delay_ms(5);

   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL);

   setup_timer_2(T2_DIV_BY_4,250,5); //overflow cada 1.0 ms

   delay_ms(3);

   enable_interrupts(int_canrx0);  

   while (true)
   {
      output_high(LED1); //led comprovacio comunicacio del micro

      if (RXB0CON.RXFUL == 1)
      {
         RXB0CON.RXFUL = 0;      // si no es gestionen els missatges
         //CANFLAG0=1;           // si es gestionen els missatges
      }
      if (RXB1CON.RXFUL == 1)
      {
         RXB1CON.RXFUL = 0;      // si no es gestionen els missatges
         //CANFLAG1=1;           // si es gestionen els missatges
      }

      // CAN SINCRONISM
      if (CAN_flag == 1)         //quan CAN_flag s'hagi activat ...
      {
         CAN_flag = 0;           //reinicia variable
         contCAN++;              //comptador de CAN_flag per enviar alive

         if ( not_first_message == 1 )
         {  
            // SEND ALIVE
            if (contCAN >= 4)   //quan CAN_flag s'hagi activat 4 vegades ...
            {
               send_alive(0xB0); //enviar senyal per indicar que el node no esta penjat
            }  

            send_data (0x85,8,APPS2,APPS1,SteeringSensor,BrakeSensor); //envia dades sensors corresponents per CAN
            send_data (0x86,4,SUSPFL,SUSPFR,0,0); //envia dades sensors corresponents per CAN

         } // END if (not_first_message == 1)         

      not_first_message = 1;      //variable per no enviar les dades quan el primer CAN_flag

      } // END CAN_flag


      if ( read_ADC_flag>0 ) //cada 1ms
      {    

         enable_interrupts(INT_TIMER2); //reinicia timer2
         read_ADC_flag = 0;

         //es llegeixen les dades de cada sensor cada 1 ms, cada 8 dades es sumen en la variable sensor_sum (s'esta fent una funcio)
         
         // APP1
         set_adc_channel(0);
         delay_us(20);
         //SUMA = read_adc();
         //APPS1_sum += SUMA;
         APPS1 = read_adc();

         // APP2
         set_adc_channel(1);
         delay_us(20);
         //SUMA = read_adc();
         //APPS2_sum += SUMA;
         APPS2 = read_adc();

         // Brake           
         set_adc_channel(2);
         delay_us(20);
         //SUMA = read_adc();
         //BrakeS_sum += SUMA;
         BrakeSensor = read_adc();

         // Steering
         set_adc_channel(3);
         delay_us(20);
         //SUMA = read_adc();        
         //Steering_sum += SUMA;
         SteeringSensor = read_adc();

         // Spring FR
         set_adc_channel(10);
         delay_us(20);
         //SUMA = read_adc();
         //SpringFR_sum += SUMA;
         SUSPFL = read_adc();

         // Spring FL 
         set_adc_channel(8);
         delay_us(20);
         //SUMA = read_adc();
         //SpringFL_sum += SUMA;
         SUSPFR = read_adc();

         output_high(LED2); //led comprovacio conversió ADC 


/*         if ( mean_filter_flag < 8 )
         {
            enable_interrupts(INT_TIMER2);
         }
         else //cada 8 ms
         {
            enable_interrupts(INT_TIMER2);
            mean_filter_flag = 0;

            //filtre per cada senyal (s'esta fent una funcio)   
            APPS1_sum = APPS1_sum >> 3;           
            APPS1 = ((APPS1_sum<<8)&0xFF00)+((APPS1_sum>>8)&0x00FF);            

            APPS2_sum = APPS2_sum >> 3;            
            APPS2 = ((APPS2_sum<<8)&0xFF00)+((APPS2_sum>>8)&0x00FF);               

            BrakeS_sum = BrakeS_sum >> 3;
            BrakeSensor = ((BrakeS_sum<<8)&0xFF00)+((BrakeS_sum>>8)&0x00FF);            

            Steering_sum = Steering_sum >> 3;           
            SteeringSensor = ((Steering_sum<<8)&0xFF00)+((Steering_sum>>8)&0x00FF);  

            SpringFR_sum = SpringFR_sum >> 3;
            SUSPFR = ((SpringFR_sum<<8)&0xFF00)+((SpringFR_sum>>8)&0x00FF);            

            SpringFL_sum = SpringFL_sum >> 3;
            SUSPFL = ((SpringFL_sum<<8)&0xFF00)+((SpringFL_sum>>8)&0x00FF);

            //reinicialitzacio variables sensor_sum (s'esta fent una funcio)
            APPS1_sum = 0;
            APPS2_sum = 0;
            BrakeS_sum = 0;
            Steering_sum = 0;
            SpringFR_sum = 0;
            SpringFL_sum = 0;

         } */
      } // END if (read_adc_flag >0)
   } // END while(1)
} // END Main