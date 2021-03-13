/* 
 * File:   TM1638pic.h
 *
 */

#include <stdio.h>
#include <string.h>

// E' obbligatorio effetturare la scelta tra la LEDKEY board e la QYF board
#define LEDKEY_TEST 1	// Con 1 abilito la libreria per la LEDKEY board
#define QYF_TEST    0	// Con 1 abilito la libreria per la QYF board
/* Con 0 disabilito la libreria per la board in questione.
 * N.B. Una delle due board deve essere SEMPRE disabilitata.
 */

#if (LEDKEY_TEST == 1)
void RitardoUS(int Conta);
void Scrivi1638( unsigned char Dato);
unsigned char Leggi1638(void);
void ScriviComando(unsigned char Comando);
void ScriviDato(unsigned char Indirizzo,unsigned char Dato);
void Resetta(void);
void ImpostaDisplay(unsigned char Stato,unsigned char Luminosita);
void LedSettaggioSingolo(char Led, char Stato);
void LedSettaggio(char Led);
void LedPulisci(void);
void MostraCarattere( unsigned char Numero,unsigned char Posizione);
void MostraStringa(const char *Stringa);
void MostraIntero(const long Numero);
void DisplayPulisci(void);
unsigned char LeggiPulsanti(void);
#endif

#if (QYF_TEST == 1)
void RitardoUSQYF(int Conta);
void Scrivi1638QYF(unsigned char Dato);
unsigned char Leggi1638QYF(void);
void ScriviComandoQYF(unsigned char Comando);
void ScriviDatoQYF(unsigned char Dato,unsigned char Indirizzo);
void ResettaQYF(void);
void ImpostaDisplayQYF(char Stato, char Luminosita);
void MostraStringaQYF(const char *Stringa);
void MostraInteroQYF(const long Numero);
void DisplayPulisciQYF(void);
unsigned int LeggiPulsantiQYF(void);
#endif
