/* Libreria per il TM1638, utilizzabile con la demoboard LED&KEY e QYF-TM1638.
 * 
 * Per utilizzare questa libreria sono necessarie alcune configurazioni:
 * - Dichiarare _XTAL_FREQ ... nel main prima di includere questa libreria, 
 *   perchè necessita delle funzioni di ritardo del compilatore 
 *   (si può usare sia il quarzo interno che quello esterno).
 * - Bisogna includere sia il file TM1638pic.h che il file TM1638pic.c nel main
 * - I pin utilizzati (DIO, CLK, STB) POSSONO ESSERE CAMBIATI a proprio
 *   piacimento, la cosa necessaria è CONFIGURARLI COME OUTPUT E COME DIGITALI 
 * - Per far funzionare il display occorre settarlo attraverso la funzione
 *   ImpostaDisplay(...); e resettarlo con Resetta();
 * 
 *  N.B. utilizzando il pickit3 è necessario scollegarlo dopo la programmazione
 * avvenuta esclusivamente con scheda TM1638 completamente disconnessa, per poi
 * ricollegarlo.
 */

#define DO  LATBbits.LATB4
#define DI  PORTBbits.RB4

#define CLK LATBbits.LATB1 
#define STB LATBbits.LATB2

#define ON 1
#define OFF 0

const char FontCarattere[] = {
    0b00000000, // (32)  <space>
    0b10000110, // (33)	!
    0b00100010, // (34)	"
    0b01111110, // (35)	#
    0b01101101, // (36)	$
    0b00000000, // (37)	%
    0b00000000, // (38)	&
    0b00000010, // (39)	'
    0b00110000, // (40)	(
    0b00000110, // (41)	)
    0b01100011, // (42)	*
    0b00000000, // (43)	+
    0b00000100, // (44)	,
    0b01000000, // (45)	-
    0b10000000, // (46)	.
    0b01010010, // (47)	/
    0b00111111, // (48)	0
    0b00000110, // (49)	1
    0b01011011, // (50)	2
    0b01001111, // (51)	3
    0b01100110, // (52)	4
    0b01101101, // (53)	5
    0b01111101, // (54)	6
    0b00000111, // (55)	7
    0b01111111, // (56)	8
    0b01101111, // (57)	9
    0b00000000, // (58)	:
    0b00000000, // (59)	;
    0b00000000, // (60)	<
    0b01001000, // (61)	=
    0b00000000, // (62)	>
    0b01010011, // (63)	?
    0b01011111, // (64)	@
    0b01110111, // (65)	A
    0b01111111, // (66)	B
    0b00111001, // (67)	C
    0b00111111, // (68)	D
    0b01111001, // (69)	E
    0b01110001, // (70)	F
    0b00111101, // (71)	G
    0b01110110, // (72)	H
    0b00000110, // (73)	I
    0b00011111, // (74)	J
    0b01101001, // (75)	K
    0b00111000, // (76)	L
    0b00010101, // (77)	M
    0b00110111, // (78)	N
    0b00111111, // (79)	O
    0b01110011, // (80)	P
    0b01100111, // (81)	Q
    0b00110001, // (82)	R
    0b01101101, // (83)	S
    0b01111000, // (84)	T
    0b00111110, // (85)	U
    0b00101010, // (86)	V
    0b00011101, // (87)	W
    0b01110110, // (88)	X
    0b01101110, // (89)	Y
    0b01011011, // (90)	Z
    0b00111001, // (91)	[
    0b01100100, // (92)	\ (this can't be the last char on a line, even in comment or it'll concat)
    0b00001111, // (93)	]
    0b00000000, // (94)	^
    0b00001000, // (95)	_
    0b00100000, // (96)	`
    0b01011111, // (97)	a
    0b01111100, // (98)	b
    0b01011000, // (99)	c
    0b01011110, // (100)	d
    0b01111011, // (101)	e
    0b00110001, // (102)	f
    0b01101111, // (103)	g
    0b01110100, // (104)	h
    0b00000100, // (105)	i
    0b00001110, // (106)	j
    0b01110101, // (107)	k
    0b00110000, // (108)	l
    0b01010101, // (109)	m
    0b01010100, // (110)	n
    0b01011100, // (111)	o
    0b01110011, // (112)	p
    0b01100111, // (113)	q
    0b01010000, // (114)	r
    0b01101101, // (115)	s
    0b01111000, // (116)	t
    0b00011100, // (117)	u
    0b00101010, // (118)	v
    0b00011101, // (119)	w
    0b01110110, // (120)	x
    0b01101110, // (121)	y
    0b01000111, // (122)	z
    0b01000110, // (123)	{
    0b00000110, // (124)	|
    0b01110000, // (125)	}
    0b00000001, // (126)	~
};

#if (LEDKEY_TEST == 1)
const char IndirizzoLed[] = {
    0b00000001, //LED1
    0b00000011, //LED2
    0b00000101, //LED3
    0b00000111, //LED4
    0b00001001, //LED5
    0b00001011, //LED6
    0b00001101, //LED7
    0b00001111, //LED8
};

const char IndirizzoDisplay[] = {
    0b00000000, //DISPLAY1
    0b00000010, //DISPLAY2
    0b00000100, //DISPLAY3
    0b00000110, //DISPLAY4
    0b00001000, //DISPLAY5
    0b00001010, //DISPLAY6
    0b00001100, //DISPLAY7
    0b00001110, //DISPLAY8
};
#endif

#if (QYF_TEST == 1)
const char IndirizzoDisplay[] = {
    0b00000001, //DISPLAY8
    0b00000010, //DISPLAY7
    0b00000100, //DISPLAY6
    0b00001000, //DISPLAY5
    0b00010000, //DISPLAY4
    0b00100000, //DISPLAY3
    0b01000000, //DISPLAY2
    0b10000000, //DISPLAY1
};

const char Segmenti[] = {
    0b11000000, //a
    0b11000010, //b
    0b11000100, //c
    0b11000110, //d
    0b11001000, //e
    0b11001010, //f
    0b11001100, //g
    0b11001110, //DP
};
#endif

#if (LEDKEY_TEST == 1)
/* Questa funzione scrive un byte in un determinato indirizzo
 * 
 * @param: unsigned char Adress --> l'indirizzo nel quale scrivere il byte
 *         unsigned char Dato --> byte da scrivere
 * @return: nessuno
 */
 
 /* Questa funzione crea ritardi di  microsecondi
 * 
 * @param: nessuno
 * @return: nessuno
 */
void RitardoUS(int Conta) {
    while (Conta > 0) {
        __delay_us(1);
        Conta--;
    }
}


//MODIFICA APPORTATA NELLA LIBRERIA  
//NON SONO PIU' PRESENTI DELLE FUNZIONI COMUNI 

/* Questa funzione scrive un byte sul pun DIO
 *
 * @param: unsigned char data --> byte da scrivere
 * @return: nessuno
 */
void Scrivi1638(unsigned char Dato) {
    for (char i = 0; i < 8; i++) {
        DO = (Dato & 0X01);
        CLK = 0;
        Dato = Dato >> 1;
        RitardoUS(2);
        CLK = 1;
    }
    RitardoUS(20);
}

/* Questa funzione legge un byte dal pin DIO
 *  
 * @param: nessuno
 * @return: unsigned char ... --> byte letto
 */
unsigned char Leggi1638(void) {
    unsigned char i;
    unsigned char Temporaneo = 0;
    DO = 1;
    for (i = 0; i < 8; i++) {
        Temporaneo >>= 1;
        CLK = 0;
        if (DI == 1)
            Temporaneo |= 0x80;
        CLK = 1;
    }
    return Temporaneo;
}

/* Questa funzione manda un comando al TM1638
 *
 * @param: unsigned char Comando --> comando da inviare
 * @return: nessuno
 */
void ScriviComando(unsigned char Comando) {
    STB = 0;
    Scrivi1638(Comando);
    STB = 1;
}


void ScriviDato(unsigned char Indirizzo, unsigned char Dato) {
    //Funzione necessaria per inviare un dato (da datasheet)
    ScriviComando(0x44);
    STB = 0;
    Scrivi1638(0xC0 | Indirizzo);
    Scrivi1638(Dato);
    STB = 1;
}

/* Questa funzione resetta i TM1638
 * 
 * @param: nessuno
 * @return: nessuno
 */
void Resetta(void) {
    //Imposta il TM1638 per funzionare in modalità auto-incremento
    ScriviComando(0x40);
    //Metto il pin STROBE a livello basso per inviare un dato
    STB = 0;
    //Seleziono il registro 0
    Scrivi1638(0xC0);
    //Scrivo 0 nel registro 16 volte
    for (char i = 0; i < 16; i++) {
        Scrivi1638(0x00);
    }
    //Metto il pin STROBE a livello alto per indicare che la trasmissione del dato è finita
    STB = 1;
}

/* Questa funzione setta i parametri inziali del TM1638 
 *
 * @param: char state --> display abilitato(1, ON) display disabilitato (0, OFF)
 *         char brightness --> luminosità (0...7)
 * @return: nessuno
 */
void ImpostaDisplay(unsigned char Stato, unsigned char Luminosita) {
    unsigned char Comando = 0x80;
    if (Stato == 1)
        Comando = Comando | 0x08;
    if (Luminosita < 7)
        Comando = Comando | Luminosita;
    ScriviComando(Comando);
}

/* Questa funzione controlla un led collegato al TM1638
 *
 * @param: char led --> il numero del led da controllare (0...7)
 *         char state --> led acceso(1 o ON) led spento(0 o OFF)
 * @return: nessuno
 */
void LedSettaggioSingolo(char Led, char Stato) {
    char s;
    if (Stato == 1)
        s = 0x01;
    else
        s = 0x00;
    ScriviDato(IndirizzoLed[Led], s);
}
/* Questa funzione accende e spegne i led
 *
 * @param: char Led --> i led da accendere (1) da spegnere (0)
 *                      Esempio: LedSettaggio(0b00001001);
 *                               // accendo i led 1,4 gli altri li spengo
 * @return: nessuno
 */
void LedSettaggio(char Led) {
    for (char i = 0; i < 8; i++) {
        char controllo = (Led >> i) & 0x01;
        if (controllo == 0x01)
            LedSettaggioSingolo(i, ON);
        else
            LedSettaggioSingolo(i, OFF);
    }
}

/* Questa funzione spegne tutti i led
 * 
 * @param: nessuno
 * @return: nessuno
 */
void LedPulisci(void) {
    for (char i = 0; i < 8; i++) {
        //Scrivo nel led[i] niente, quindi spengo il led
        ScriviDato(IndirizzoLed[i], 0x00);
    }
}

/* Questa funzione scrive una cifra o un carattere ad una determinata posizione
 *
 * @param: unsigned char c --> cifra o numero da scrivere
 *         unsigned char pos --> numero del display in cui scrivere
 * @return: none
 */
void MostraCarattere(unsigned char c, unsigned char pos) {
    ScriviComando(0x44);
    STB = 0;
    Scrivi1638(0xc0 | IndirizzoDisplay[pos]);
    Scrivi1638(FontCarattere[c - 32]);
    STB = 1;
}

/* Questa funzione scrive una stringa
 * 
 * @param: const char *string --> stringa da scrivere
 * @return: nessuno
 */
void MostraStringa(const char *Stringa) {
    //Calcolo il numero dei caratteri nella stringa
    short int Lunghezza = strlen(Stringa);
    for (char i = 0; i < Lunghezza; i++) {
        //Scrivo la cifra meno significativa nel display[8] e cosi via
        ScriviDato(IndirizzoDisplay[8 - (Lunghezza - i)], FontCarattere[Stringa[i] - 32]);
    }
    for (char i = Lunghezza; i < 8; i++) {
        ScriviDato(IndirizzoDisplay[i - Lunghezza], 0x00);
    }
}

/* Questa funzione scrive un intero
 * 
 * @param: int Numero --> numero da scrivere (con o senza segno)
 * @return: nessuno
 */
void MostraIntero(const long Numero) {
    char buffer[8];
    //Converto il numero intero in una stringa
    sprintf(buffer, "%ld", Numero);
    //Scrivo la stringa, appena convertita, nei display
    MostraStringa(buffer);
}

/* Questa funzione cancella il display
 * 
 * @param: nessuno
 * @return: nessuno
 */
void DisplayPulisci(void) {
    for (char i = 0; i < 8; i++) {
        //Scrivo nel display[i] niente, quindi spengo il display
        ScriviDato(IndirizzoDisplay[i], 0x00);
    }
}

/* Questa funzione legge lo stato di tutti e 8 i pulsanti
 * 
 * @param: nessuno
 * @return: unsigned char ... --> il valore dei pulsanti (vedi tabella)
 * |0 0 0 0 0 0 0 0| --> nessun pulsante premuto
 * |0 0 0 0 0 0 0 1| --> premuto il pulsante 1
 * |0 0 0 0 0 0 1 0| --> premuto il pulsante 2
 *        ...
 * |1 0 0 0 0 0 0 0| --> premuto il pulsante 8
 * 
 * |0 0 0 0 0 0 1 1| --> premuto il pulsante 1 e 2
 * |0 0 1 0 0 1 0 1| --> premuto il pulsante 1, 3 e 6
 *        ...
 * |1 1 1 1 1 1 1 1| --> tutti i pulsanti premuti
 */
unsigned char LeggiPulsanti(void) {
    unsigned char Pulsanti = 0;
    STB = 0;
    //Comando necessario per leggere i pulsanti
    Scrivi1638(0x42);
    for (char i = 0; i < 4; i++) {
        Pulsanti |= Leggi1638() << i;
    }
    STB = 1;
    return Pulsanti;
}
#endif

#if (QYF_TEST == 1)
	
//MODIFICA APPORTATA NELLA LIBRERIA  
//NON SONO PIU' PRESENTI DELLE FUNZIONI COMUNI 

/* Questa funzione crea ritardi di  microsecondi
 * 
 * @param: nessuno
 * @return: nessuno
 */
void RitardoUSQYF(int Conta) {
    while (Conta > 0) {
        __delay_us(1);
        Conta--;
    }
}

/* Questa funzione scrive un byte sul pun DIO
 *
 * @param: unsigned char data --> byte da scrivere
 * @return: nessuno
 */
void Scrivi1638QYF(unsigned char Dato) {
    for (char i = 0; i < 8; i++) {
        DO = (Dato & 0X01);
        CLK = 0;
        Dato = Dato >> 1;
        RitardoUSQYF(2);
        CLK = 1;
    }
    RitardoUSQYF(20);
}

/* Questa funzione legge un byte dal pin DIO
 *  
 * @param: nessuno
 * @return: unsigned char ... --> byte letto
 */
unsigned char Leggi1638QYF(void) {
    unsigned char i;
    unsigned char Temporaneo = 0;
    DO = 1;
    for (i = 0; i < 8; i++) {
        Temporaneo >>= 1;
        CLK = 0;
        if (DI == 1)
            Temporaneo |= 0x80;
        CLK = 1;
    }
    return Temporaneo;
}

/* Questa funzione manda un comando al TM1638
 *
 * @param: unsigned char Comando --> comando da inviare
 * @return: nessuno
 */
void ScriviComandoQYF(unsigned char Comando) {
    STB = 0;
    Scrivi1638QYF(Comando);
    STB = 1;
}

/* Questa funzione scrive un byte in un determinato indirizzo
 * 
 * @param: unsigned char Dato --> byte da scrivere 
 *         unsigned char Indirizzo --> l'indirizzo nel quale scrivere il byte
 *
 * @return: nessuno
 */
void ScriviDatoQYF(unsigned char Dato, unsigned char Indirizzo) {
    //Funzione necessaria per inviare un dato (da datasheet)
    ScriviComandoQYF(0x44);
    STB = 0;
    Scrivi1638QYF(Dato);
    Scrivi1638QYF(Indirizzo);
    STB = 1;
}

/* Questa funzione resetta i TM1638
 * 
 * @param: nessuno
 * @return: nessuno
 */
void ResettaQYF(void) {
    //Imposta il TM1638 per funzionare in modalità auto-incremento
    ScriviComandoQYF(0x40);
    //Metto il pin STROBE a livello basso per inviare un dato
    STB = 0;
    //Seleziono il registro 0
    Scrivi1638QYF(0xC0);
    //Scrivo 0 nel registro 16 volte
    for (char i = 0; i < 16; i++) {
        Scrivi1638QYF(0x00);
    }
    //Metto il pin STROBE a livello alto per indicare che la trasmissione del dato è finita
    STB = 1;
}

/* Questa funzione setta i parametri inziali del TM1638 
 *
 * @param: char state --> display abilitato(1, ON) display disabilitato (0, OFF)
 *         char brightness --> luminosità (0...7)
 * @return: nessuno
 */
void ImpostaDisplayQYF(unsigned char Stato, unsigned char Luminosita) {
    unsigned char Comando = 0x80;
    if (Stato == 1)
        Comando = Comando | 0x08;
    if (Luminosita < 7)
        Comando = Comando | Luminosita;
    ScriviComandoQYF(Comando);
}

/* Questa funzione scrive una stringa
 * 
 * @param: const char *string --> stringa da scrivere
 * @return: nessuno
 */
void MostraStringaQYF(const char *Stringa) {
    //Calcolo il numero dei caratteri nella stringa
    short int Lunghezza = strlen(Stringa);
    char Display;
    for (char i = 0; i < 8; i++) {
        Display = 0x00;
        for (signed char j = (Lunghezza - 1); j >= 0; j--) {
            if(FontCarattere[Stringa[(Lunghezza - 1) - j] - 32] >> i & 0x01)
                Display |= IndirizzoDisplay[j];
        }
        ScriviDatoQYF(Segmenti[i], Display);
    }
}

/* Questa funzione scrive un intero
 * 
 * @param: int Numero --> numero da scrivere (con o senza segno)
 * @return: nessuno
 */
void MostraInteroQYF(const long Numero){
    char buffer[8];
    //Converto il numero intero in una stringa
    sprintf(buffer, "%ld", Numero);
    //Scrivo la stringa, appena convertita, nei display
    MostraStringaQYF(buffer);
}

/* Questa funzione cancella il display
 * 
 * @param: nessuno
 * @return: nessuno
 */
void DisplayPulisciQYF(void) {
    for (char i = 0; i < 8; i++) {
        //Scrivo nel display[i] niente, quindi spengo il display
    }
}

/* Questa funzione legge lo stato di tutti e 8 i pulsanti
 * 
 * @param: nessuno
 * @return: unsigned int ... --> il valore dei pulsanti (vedi tabella)
 * |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0| --> nessun pulsante premuto
 * |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1| --> premuto il pulsante 1
 * |0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0| --> premuto il pulsante 2
 *        ...
 * |0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0| --> premuto il pulsante 8
 * 
 * |0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1| --> premuto il pulsante 1 e 2
 * |0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 1| --> premuto il pulsante 1, 3 e 6
 *        ...
 * |1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1| --> tutti i pulsanti premuti
 */
unsigned int LeggiPulsantiQYF(void) {
    unsigned int Pulsanti = 0;
    STB = 0;
    //Comando necessario per leggere i pulsanti
    Scrivi1638QYF(0x42);
    for (int i = 0; i < 4; i++) {
        unsigned char Registrati = Leggi1638QYF();

        Registrati = (((Registrati & 0b1000000) >> 3 | (Registrati & 0b100)) >> 2) | (Registrati & 0b100000) | (Registrati & 0b10) << 3;

        Pulsanti |= ((Registrati & 0x000F) << (i << 1)) | (((Registrati & 0x00F0) << 4) << (i << 1));
    }
    STB = 1;
    return Pulsanti;
}
#endif