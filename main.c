#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include "TM1638picB.h"
#include "TM1638picB.c"
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    EPWM1_Initialize();
    EPWM2_Initialize();
    
    ImpostaDisplay(ON, 5);
    Resetta();
    
    PSTR1CON = 0x08;
    PSTR2CON = 0x01;
    
    int t, q;
    int delay = 100;
    
    while (1)
    {
        if(LeggiPulsanti()!=0){
            t=LeggiPulsanti();
           
        }
        switch(t){
            case 1: 
                MostraStringa("LENTO");
                for(q=22;q<=70;q=q+30){
                EPWM1_LoadDutyValue(q);
                EPWM2_LoadDutyValue(q);
                __delay_ms(4000);}
                break;
            case 2: 
                MostraStringa("MEDIO");
                for(q=22;q<=70;q=q+30){
                EPWM1_LoadDutyValue(q);
                EPWM2_LoadDutyValue(q);
                __delay_ms(2000);}
                break;
            case 4: 
                MostraStringa("VELOCE");
                for(q=22;q<=70;q=q+30){
                EPWM1_LoadDutyValue(q);
                EPWM2_LoadDutyValue(q);
                __delay_ms(500);}
                break;
            case 8:
                MostraStringa("OFF");
                EPWM1_LoadDutyValue(22);
                EPWM2_LoadDutyValue(22);
                }    
    }
}
