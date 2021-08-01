//Alice Bernardi Gottardello
//2019003913
//Liquidificador


#include "pic18f4520.h"
#include "lcd.h"
#include "config.h"
#include "bits.h"
#include "delay.h"
#include "keypad.h"
#include "teclado.h"
#include "io.h"
#include "ssd.h"
#include "pwm.h"



//TECLADO
#define LIN0 PIN_D0
#define LIN1 PIN_D1
#define LIN2 PIN_D2
#define LIN3 PIN_D3
#define COL0 PIN_B0 
#define COL1 PIN_B1
#define COL2 PIN_B2
//#define col0 PORTDbits.RD0 bitTst(PORTD,3)

int varreduraTeclado() {
    int val = -1;
    unsigned char column;

    do {
        PORTD = 0X0F; // Make Row pins high 
        column = PORTD; // Read column pin status: Read the port
        column &= 0xF0; // Read column pin status: Extract column pin status from PortD
    } while (column == 0x00); // Repeat this procedure till a keypress event got detected


    PORTD = 0x01;
    if ((COL0 == 0) && (LIN0 == 0)) {
        val = 1;
        while (COL0 == 0); //tecla ainda pressionada
    }


    PORTD = 0x02;
    if ((COL1 == 0) && (LIN0 == 0)) {
        val = 2;
        while (COL1 == 0); //tecla ainda pressionada
    }

    PORTD = 0x04;
    if ((COL2 == 0) && (LIN0 == 0)) {
        val = 3;
        while (COL2 == 0); //tecla ainda pressionada
    } else {
        val = 5;
        while (COL2 == 0);

    }


    PORTD = 0x08;
    if ((COL0 == 0)&&(LIN1 == 0)) {
        val = 4;
        while (COL0 == 0); //tecla ainda pressionada
    }

    return val;
}

void relogioSeteSeg() {
    //float time;
    unsigned long int cont;
    ssdInit();
    for (;;) {
        cont++;
        ssdDigit(((cont / 300) % 10), 3);
        ssdDigit(((cont / 3000) % 6), 2);
        ssdDigit(((cont / 18000) % 10), 1);
        ssdDigit(((cont / 180000) % 6), 0);
        ssdUpdate();
        //for (tempo = 0; tempo < 10; tempo++); // +- 10ms
    }
}

void pulsar() {
    PORTD = 0x00; //acende todos os leds
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Pulsar..."); //isso foi de 0 a 100 mt rapido :v
    relogioSeteSeg();
    pwmSet1(96);
    atraso_s(2);
    pwmSet1(0);
    atraso_s(1);
    pwmSet1(96);
    atraso_s(2);
    pwmSet1(0);
    atraso_s(1);
    pwmSet1(96);
    atraso_s(2);
    pwmSet1(0);
    lcd_cmd(L_CLR);
    /*ssdDigit(0,3);
    ssdDigit(0,2);
    ssdDigit(0,1);
    ssdDigit(0,0);*/
    ssdUpdate();
}

void vitamina() {
    PORTD = 0xFE; //acende alguns leds
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Vitamina..."); //constancia
    relogioSeteSeg();
    pwmSet1(32);
    atraso_s(5);
    pwmSet1(0);
    lcd_cmd(L_CLR);
    /*ssdDigit(0,3);
    ssdDigit(0,2);
    ssdDigit(0,1);
    ssdDigit(0,0);*/
    ssdUpdate();
}

void sopa() {
    PORTD = 0xFD; //acende alguns leds
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Sopinha..."); //varia potencia
    relogioSeteSeg();
    pwmSet1(64);
    atraso_s(3);
    pwmSet1(32);
    atraso_s(2);
    pwmSet1(64);
    atraso_s(2);
    pwmSet1(0);
    lcd_cmd(L_CLR);
    /*ssdDigit(0,3);
    ssdDigit(0,2);
    ssdDigit(0,1);
    ssdDigit(0,0);*/
    ssdUpdate();
}

void vegetais() {
    PORTD = 0x00; //acende leds
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Vegetais...");
    relogioSeteSeg();
    pwmSet1(96); //potencia, vegetais duros
    atraso_s(5);
    pwmSet1(0);
    lcd_cmd(L_CLR);
    /*ssdDigit(0,3);
    ssdDigit(0,2);
    ssdDigit(0,1);
    ssdDigit(0,0);*/
    ssdUpdate();
}

void massa() {
    PORTD = 0xFF; //acende alguns leds
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Massa/bolo...");
    relogioSeteSeg();
    pwmSet1(32);
    atraso_s(7); //constancia
    pwmSet1(0);
    lcd_cmd(L_CLR);
    /*ssdDigit(0,3);
    ssdDigit(0,2);
    ssdDigit(0,1);
    ssdDigit(0,0);*/
    ssdUpdate();
}

void main(void) {
    unsigned char op = 0;
    int tecla = 0;
    unsigned char tempo = 0;
    //unsigned char column;
    ADCON1 = 0x06;
    TRISB = 0x01;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    TRISB = 0xF8;
    lcd_init();
    //ssdInit();
    kpInit();
    pwmInit();

    lcd_cmd(L_CLR); //limpa
    lcd_cmd(L_L1); //seta linha 1
    lcd_str("Liquidificador");
    atraso_s(3);

    for (;;) {
        ssdUpdate();
        kpDebounce();

        lcd_cmd(L_CLR); //limpa
        lcd_cmd(L_L1); //seta linha 1
        lcd_str("Escolha uma das");
        lcd_cmd(L_L2);
        lcd_str("     opcoes: ");
        atraso_s(4);
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str("1 - Pulsar");
        lcd_cmd(L_L2);
        lcd_str("2 - Vitamina");
        atraso_s(3);
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str("3 - Sopa");
        lcd_cmd(L_L2);
        lcd_str("4 - Vegetais");
        atraso_s(3);
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str("5 - Massas/bolos");
        atraso_s(3);

        //op = kpRead();

        //if (kpRead() != op) {
        //  op = kpRead(); //le a tecla pressionada pelo usuario
        //op = tc_tecla(0);

        //enquanto o usuario n escolher
        //mostra as opcoes
        tecla = varreduraTeclado();
        /*if (tecla == -1) {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str("1 - Pulsar");
            lcd_cmd(L_L2);
            lcd_str("2 - Vitamina");
            atraso_s(3);
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str("3 - Sopa");
            lcd_cmd(L_L2);
            lcd_str("4 - Vegetais");
            atraso_s(3);
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str("5 - Massas/bolos");
            atraso_s(3);
        }//end bitsts0*/

        //pulsar
        if (tecla == 1) {
            lcd_cmd(L_CLR);
            pulsar();
        }//end bits1

        //vitamina
        if (tecla == 2) {
            lcd_cmd(L_CLR);
            vitamina();
        }//end bits2

        //sopa
        if (tecla == 3) {
            lcd_cmd(L_CLR);
            sopa();
        }//end bits3

        //vegetais
        if (tecla == 4) {
            lcd_cmd(L_CLR);
            vegetais();
        }//end bits4

        //massa/bolo
        if (tecla == 5) {
            lcd_cmd(L_CLR);
            massa();
        }//end bits1

        //kpDebounce();

        //op = tc_tecla();

        /*switch (op) {
                //Pulsar
            case 1:
                lcd_cmd(L_CLR);
                lcd_str("funf1");
                break;

                //vitamina
            case 2:
                lcd_cmd(L_CLR);
                lcd_str("funf2");
                break;

                //sopa
            case 3:
                lcd_cmd(L_CLR);
                lcd_str("funf3");
                break;

                //vegetais
            case 4:
                lcd_cmd(L_CLR);
                lcd_str("funf4");
                break;

                //massa/bolos
            case 5:
                lcd_cmd(L_CLR);
                lcd_str("funf5");
                break;

        }*///end switch
        //op = kpRead(); //le a tecla pressionada pelo usuario

        //}
        //for (tempo = 0; tempo < 250; tempo++);

    }//end loop

}//end main
