#include <18f4620.h>
#use delay(clock=16M)
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use FAST_IO(A)
#use FAST_IO(B)
#use FAST_IO(C)
#use FAST_IO(D)


//Variables Globales
int8 contador1 = 0; //Conteo de puerto A 100 ms
int8 contador2 = 0; //Conteo de puerto B 500 ms
int8 contador3 = 0; //Conteo de puerto C 1000 ms
int8 contador4 = 0; //Conteo de puerto D 1500 ms

unsigned int8 anilloA = 1;
unsigned int8 anilloB = 1;
unsigned int8 anilloC = 1;
unsigned int8 anilloD = 1;

int1 banderaA = 0;
int1 banderaB = 0;
int1 banderaC = 0;
int1 banderaD = 0;

#int_timer0
void isr_TMR0(void){ //Rutina de interrupcion
   contador1++;
   contador2++;
   contador3++;
   contador4++;
   
   if(contador1 >= 6){
      contador1 = 0;
      banderaA = 1;
   }
   if(contador2 >= 32){
      contador2 = 0;
      banderaB = 1;
   }
   if(contador3 >= 61){
      contador3 = 0;
      banderaC = 1;
   }
   if(contador4 >= 91){
      contador4 = 0;
      banderaD = 1;
   }
   
   /*
   if (contadorUno == 10){ //Cuando pasa 10 veces 10 ms son 100 ms
      banderaContador = 1; //Se activa la bandera
      set_timer0(144); //Reinicia el tmr
   }else{
      set_timer0(144); //Reinicia el tmr
   }*/
   
}
   


void main (void){

   SETUP_OSCILLATOR(OSC_16MHZ);
   SETUP_ADC_PORTS(NO_ANALOGS);
   
   SET_TIMER0(0); //Valor de TMR
   
   //Habilita interrupciones
   ENABLE_INTERRUPTS(GLOBAL);
   ENABLE_INTERRUPTS(INT_TIMER0);
   
   //Configuracion TMR
   SETUP_TIMER_0(RTCC_INTERNAL | RTCC_DIV_256 |T0_8_BIT); //Predivisor
   
   SET_TRIS_A(0x00);
   SET_TRIS_B(0x00);
   SET_TRIS_C(0x00);
   SET_TRIS_D(0x00);
   
   while(true){
      /*output_a(0xFF);
      output_b(0xFF);
      output_c(0xFF);
      output_d(0xFF);
      */
      if(banderaA){
         banderaA = 0;
 
         anilloA <<= 1;
         if(anilloA == 0){
            anilloA = 1;
         }
      }
      
      if(banderaB){
         banderaB = 0;
         
         anilloB <<= 1;
         if(anilloB == 0){
            anilloB = 1;
         }
      }
      if(banderaC){
         banderaC = 0;
         
         anilloC <<= 1;
         if(anilloC == 0){
            anilloC = 1;
         }
      }
      if(banderaD){
         banderaD = 0;
         
         anilloD <<= 1;
         if(anilloD == 0){
            anilloD = 1;
         }
      }
      
      /*
      if(banderaContador){ //Si han pasado 100 ms
         puertoA <<= 1;
         contadorDos ++; 
         banderaContador = 0; //Limpia la bandera
         if(contadorDos == 5){ //Si han pasado 500 ms
            puertoB <<= 1;
            contadorTres ++;
            contadorCuatro ++;
            contadorDos = 0;
            if(contadorTres == 2){ //Si han pasado 1000 ms
            puertoC <<= 1;
            contadorTres = 0;
            }
            if(contadorCuatro == 3){ //Si han pasado 1500 ms
            puertoD <<= 1;
            contadorCuatro = 0;
            }
         }
      }
      */
      output_a(anilloA);
      output_b(anilloB);
      output_c(anilloC);
      output_d(anilloD);
      
   }
}


