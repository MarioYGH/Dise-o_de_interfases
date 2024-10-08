// Asigne un numero decimal a cada LED, por ejemplo, LED D1 número 0, LED D2 número 1, etc. Haga lo mismo para cada micro switch de la matriz de 3x3. Ahora,
// diseñe un programa en lenguaje C que lea el micro switch que fue presionado y encienda el LED asociado. Noté que le faltará un LED (9 micro switch y 8 LEDs).
// Cuando el micro switch sobrante sea presionado, el programa diseñado debe iniciar la secuencia descrita en el paso 2. Para detener la secuencia, el usuario
// debe presionar nuevamente el switch sobrante. Cuando la secuencia este activa el programa no debe permitir que los otros botones funcionen.

#include <16F877A.h>
#fuses XT, NOWDT,NOPUT,NOLVP,NOPROTECT,BROWNOUT
#use delay(clock=20000000) 

#use fast_io(B) 
#use fast_io(D)

int q=2;

int delay(){
   for(int i=0; i<9; i++){
      delay_ms(10);
      if(!input(pin_b5)){return 1;}
   }
}

int secuencia(){
   for(int i=1; i<128; i = i*2){
      if(delay()) { return 1; }
      output_d(i);
   }
   for(int c=128; c>1/2; c=c/2){
      if(delay()) { return 1; }
      output_d(c);
   }
   
   return 1;
}


void main()
{
   set_tris_d(0x00); 
   set_tris_b(0x38);  
   PORT_B_PULLUPS(TRUE);    // Habilitar resistencias de pull-up en puerto B

   while(TRUE)
   {  
        
      output_b(6);
      output_d( !input(pin_b0)*!input(pin_b3) + !input(pin_b0)*!input(pin_b4)*2 + !input(pin_b0)*!input(pin_b5)*4 );
      delay_ms(q);
      
      output_b(5);
      output_d( !input(pin_b1)*!input(pin_b3)*8 + !input(pin_b1)*!input(pin_b4)*16 + !input(pin_b1)*!input(pin_b5)*32  );
      delay_ms(q);
      
      output_b(3);
      output_d( !input(pin_b2)*!input(pin_b3)*64 + !input(pin_b2)*!input(pin_b4)*128 );
      if(!input(pin_b5)) {
         secuencia();
      }
      delay_ms(q);
      
   }

}
