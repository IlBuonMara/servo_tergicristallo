//Questo programma utilizza i pulsanti e i display della tm1638 per comandare
//attraverso i due moduli eccp del pic due motori servo che funzionano come tergicristalli

//nelle proprietà del progetto, nella sezione program options dedicata al pickit3 è necessario impostare "apply vpp before vdd (reccomended)" 
//nelle impostazioni del code confiurator nella sezione system module è necessario mettere la spunta su low voltge programming enable

//  Consegna:
//  Creare il nuovo progetto in modo che due servomotori partano dalla posizione 0° e venga visualizzata la scritta "OFF" sui display della scheda tm1638
//
//- se si preme il pulsante s1 della scheda tm1638 i due servomotori ruotano di 180° e ritornano a 0°, ripetendo continuamente il ciclo dopo lo stesso tempo di 4 secondi, e sui display della scheda tm1638 viene scritto "LENTO"
//
//- se si preme il pulsante s2, il ritardo nella rotazione si abbassa a 2 secondi e sui display della scheda tm1638 viene scritto "MEDIO"
//
//- se si preme il pulsante s3, il ritardo nella rotazione si abbassa a 0,5 secondi e sui display della scheda tm1638 viene scritto "VELOCE"
//
//- se si preme il pulsante s4 della scheda tm1638 due servomotori si posizionano a 0° (posizione di riposo) e non ruotano fino alla premuta di uno degli altri tasti e sui display della scheda tm1638 viene scritto "OFF"
//
//  Utilizzare i moduli ECCP1 ed ECCP2 per il pilotaggio dei due servo con tecnica PWM



#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include "TM1638picB.h" //includere le librerie della tm1638
#include "TM1638picB.c" //includere le librerie della tm1638
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    EPWM1_Initialize(); //inizializzo i due moduli epwm
    EPWM2_Initialize();
    
    ImpostaDisplay(ON, 5); //il display è impostato on con luminosità 5
    Resetta(); //il display viene pulito
    
    PSTR1CON = 0x08; //nel modulo eccp1 si utilizza l'output pxd, quindi rb7
    PSTR2CON = 0x01; //nel modulo eccp2 si utilizza l'output pxa, quindi rb6
    
    int t, q;
    
    while (1)
    {
        if(LeggiPulsanti()!=0){ //se un pulsante è premuto
            t=LeggiPulsanti(); //scrive in t il valore della lettura dei pulsanti
        }
        switch(t){
            case 1: 
                MostraStringa("LENTO"); //Scrive sul display della tm "LENTO"
                for(q=18;q<=70;q=q+58){ // il valore che comanda l'angolo dei motori passa da 18 a 76
                EPWM1_LoadDutyValue(q); //scrive nei motori il valore appena settato
                EPWM2_LoadDutyValue(q);
                __delay_ms(4000);}
                break;
            case 2: 
                MostraStringa("MEDIO"); //Scrive sul display della tm "MEDIO"
                for(q=18;q<=70;q=q+58){ // il valore che comanda l'angolo dei motori passa da 18 a 76
                EPWM1_LoadDutyValue(q); //scrive nei motori il valore appena settato
                EPWM2_LoadDutyValue(q);
                __delay_ms(2000);}
                break;
            case 4: 
                MostraStringa("VELOCE"); //Scrive sul display della tm "VELOCE"
                for(q=18;q<=70;q=q+58){ // il valore che comanda l'angolo dei motori passa da 18 a 76
                EPWM1_LoadDutyValue(q); //scrive nei motori il valore appena settato
                EPWM2_LoadDutyValue(q);
                __delay_ms(500);}
                break;
            case 8:
                MostraStringa("OFF"); //Scrive sul display della tm "OFF"
                EPWM1_LoadDutyValue(18); //imposta i motori in posizione di riposo/partenza
                EPWM2_LoadDutyValue(18);
                }    
    }
}
