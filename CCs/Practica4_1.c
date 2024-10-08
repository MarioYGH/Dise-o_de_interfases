// Diseñe un programa en lenguaje C que implemente un voltmetro para registrar niveles de voltaje entre 0 y 5 volts. Utilice el convertidor A/D para adquirir el nivel de voltaje
// y transformarlo en una palabra binaria. El valor del voltaje se debe visualizar en un display LCD.

#include <18F4550.h>
#device ADC=10 // Configura la resolución del ADC a 10 bits // Tiene que ir después del pic pq sino marca error
#fuses NOWDT, HS, NOPROTECT, NOLVP
#use delay(clock=4000000)  
#include <lcd.c> 

void main() {
    float voltage; 
    int16 adc_value; 

    lcd_init();

    // Configuración del ADC
    setup_adc(ADC_CLOCK_INTERNAL); // Ciclo de reloj interno para el ADC
    setup_adc_ports(AN0); // Establecer el canal AN0 como entrada analógica
    set_adc_channel(0); // Seleccionar el canal 0 para la conversión

    while (TRUE) {
     
        adc_value = read_adc();
        delay_ms(100); 
        voltage = ((float)adc_value / 1023.0) * 5.0; // La fórmula es: voltage = (adc_value / 1023.0) * 5.0
        lcd_gotoxy(1, 1); 
        printf(lcd_putc, "Voltaje: %1.2f V", voltage); 
        delay_ms(500); 
    }
}
