#include <stdio.h>

#include <contiki.h>
#include <contiki-net.h>

#include <sys/clock.h>

#include "dev/leds.h"

#include "letmecreate/click/motion.h"
#include "letmecreate/core/common.h"

#include "letmecreate/core/debug.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include <p32xxxx.h>

#include "fsm.h"

void init_buttons(){
    //inicialización botón izquierda
    ANSELEbits.ANSE7=0;
    TRISEbits.TRISE7=1;
    LATEbits.LATE7=0;

    //inicialización botón derecha
    ANSELBbits.ANSB0=0;
    TRISBbits.TRISB0=1;
    LATBbits.LATB0=0; 

    leds_off(LED1);
    leds_off(LED2);
}


void switch_on(fsm_t* fsm){
    printf("LED ENCENDIDO \n");
    leds_on(LED1);
}

void switch_off(fsm_t* fsm){
    printf("LED APAGADO \n");
    leds_off(LED1);
}

int read_button_1(fsm_t* fsm){
    printf("boton1 \n");
    if(PORTEbits.RE7 == 0){ //boton izquierda
        printf("boton1 pulsado \n");
        return 1;
    }
    return 0;
}

int read_button_2(fsm_t* fsm){
    printf("boton2 \n");
    if(PORTBbits.RB0 == 0){ //boton derecha
        printf("boton2 pulsado \n");
        return 1;
    }
    return 0;
}





PROCESS(main_process, "Main process");
AUTOSTART_PROCESSES(&main_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
    PROCESS_BEGIN();
    INIT_NETWORK_DEBUG();
    {

        enum fsm_state { ON, OFF };

        static fsm_trans_t boton_led[] = {
            {ON,     read_button_1,     OFF,    switch_off},
            {OFF,    read_button_2,     ON,     switch_on},
            {-1, NULL, -1, NULL},
        };
        static struct etimer et;
        static fsm_t* fsm;

        printf("=====Start=====\n");
        leds_on(LED2);
        init_buttons();
        fsm = fsm_new(boton_led);
        switch_off(fsm);

        printf("********FSM CREADA********");
        leds_off(LED2);
        while(1)
        {
            etimer_set(&et, CLOCK_SECOND);

            fsm_fire(fsm);

            PROCESS_WAIT_EVENT();
        }
    }

    PROCESS_END();
}

/*---------------------------------------------------------------------------*/



