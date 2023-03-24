#include <mega2560.h>
#include <delay.h>
#include <display4_ard_logo.h>

/*
//DDRAM
Zeile 1: 0x00-0x09
Zeile 2: 0x40-0x49
Zeile 3: 0x0A-0x13
Zeile 4: 0x4A-0x53
*/

//Anzeigetexte
#define T_H                 0
#define T_rtest             1
#define T_Start             2
#define T_BeiTon            3
#define T_Taste             4
#define T_nochmal           5
#define T_12345             6
#define T_Feinstaub         7
#define T_daten             8
#define T_g                  9
#define T_m                  10
#define T_hoch3             11
//#define                   12
#define Z_oe           0x94
#define Z_Pfeilnu      0x00
#define Z_my           0x01

//Festlegung der Texte die auf dem Display angezeigt werden sollen
flash char const Display_Text0[] = {"H."};
flash char const Display_Text1[] = {"rtest."};
flash char const Display_Text2[] = {"Start."};
flash char const Display_Text3[] = {"Bei Ton."};
flash char const Display_Text4[] = {"Taste>."};
flash char const Display_Text5[] = {"<nochmal."};
flash char const Display_Text6[] = {"12345 Hz."};
flash char const Display_Text7[] = {"Feinstaub-."};
flash char const Display_Text8[] = {"daten:."};
flash char const Display_Text9[] = {"g."};
flash char const Display_Text10[] = {"m."};
flash char const Display_Text11[] = {"³."};
flash char const Display_Text12[] = {""};

//Sonderzeichen Pfeil nach unten
char const pfeilnu[] =  {0x04, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04, 0x00};
char const my[] =       {0x00, 0x00, 0x09, 0x09, 0x09, 0x0E, 0x08, 0x08};

//Zeiger
flash char const *ptr_hilfe;                //Hilfszeiger
flash char const *ptr_text[] = {Display_Text0, Display_Text1, Display_Text2, Display_Text3,
								Display_Text4, Display_Text5, Display_Text6, Display_Text7, Display_Text8, Display_Text9,
								Display_Text10, Display_Text11, Display_Text12
							   };
//Zeiger auf Texte (Anfangsadressen)

//Globale Variablen//

//Methodenprototypen//
void port_init(void);                        //Portinitialisierung
void display_text(int text_nr);             //Text an Display senden
void sonderzeichen(void);                  //Sonderzeichen in das CGRAM schreiben

void Feinstaubdaten(void);

//Hauptprogramm//
void main(void)
{
	port_init();                                 //Ports initialisieren
	lcd_init();                               //Anzeige initialisieren
	sonderzeichen();                          //Sonderzeichen in das CGRAM schreiben
	/*
	  write_instr(0x01);                        //Display lï¿œschen
	  display_pos(0x00);                        //Cursor auf Position 0x00
	  display_text(T_H);                        //Anzeige "H"
	  write_char(Z_oe);                         //Schreibe Zeichen ö
	  display_text(T_rtest);                    //Anzeige "rtest"
	  write_instr(0x0C);                        //Cursor aus
	*/
	while(1)
		{

		Feinstaubdaten();

		display_pos(0x0A);
		write_char(Z_my);
		display_text(T_g);
		write_char(0x2F);
		display_text(T_m);
		display_text(T_hoch3);
		display_pos(0x4B);
		write_char(Z_Pfeilnu);
		write_instr(0x0C);


		delay_ms(5000);


		delay_ms(5000);


		delay_ms(5000);

		}

	/*

	while(1)                                  //Wiederhole endlos
	{
	  write_instr(0x01);                      //Display lï¿œschen
	  display_pos(0x00);                      //Cursor auf Position 0x00
	  display_text(T_Start);                  //Anzeige "Start"
	  display_pos(0x44);                      //Cursor auf Position 0x44
	  write_char(Z_Pfeilnu);                  //Schreibe Zeichen "Pfeil nach unten"
	  write_instr(0x0C);                      //Cursor aus

	  delay_ms(5000);

	  write_instr(0x01);                      //Display lï¿œschen
	  display_pos(0x00);                      //Cursor auf Position 0x00
	  display_text(T_BeiTon);                 //Anzeige "Bei Ton"
	  display_pos(0x42);                      //Cursor auf Position 0x42
	  display_text(T_Taste);                  //Anzeige "Taste"
	  write_instr(0x0C);                      //Cursor aus

	  delay_ms(5000);

	  write_instr(0x01);                      //Display lï¿œschen
	  display_pos(0x00);                      //Cursor auf Position 0x00
	  display_text(T_12345);                  //Frequenz-Zeichenketten-Dummy schreiben
	  display_pos(0x40);                      //Cursor auf Position 0x40
	  display_text(T_nochmal);                //Anzeige "nochmal"
	  write_instr(0x0C);                      //Cursor aus

	  delay_ms(5000);
	}
	*/
}


//Text-const
void Feinstaubdaten(void)
{
	write_instr(0x01);
	display_pos(0x00);
	display_text(T_Feinstaub);
	display_pos(0x40);
	display_text(T_daten);
	write_instr(0x0C);

}




//Methoden
void sonderzeichen(void)
{
	int i, k;

	write_instr(0x40);                      //CGRAM auf 0 stellen
	for (i = 0; i <= 7; i++)                //Zeilen 0...7
		{
		//write_char(my[i]);                    //Zeilen 0...7 des Sonderzeichen an das CGRAM senden
		write_char(pfeilnu[i]);
		}

	for (k = 0; k <= 7; k++)                //Zeilen 0...7
		{
		//write_char(pfeilnu[k]);             //Zeilen 0...7 des Sonderzeichen an das CGRAM senden
		write_char(my[k]);             //Zeilen 0...7 des Sonderzeichen an das CGRAM senden
		}

}

void display_text(int text_nr)
{
	unsigned char tab;                      //Lokale Zï¿œhlvariable tab deklarieren/

	ptr_hilfe = ptr_text[text_nr];          //Text-Zeiger auf Anfangsadresse von Display_Texttext_nr
	//setzen und Adresse an Hilfe-Zeiger ï¿œbergeben
	tab = 0;
	while ( *(ptr_hilfe + tab) != '.' )     //Wiederhole solange der Hilfe-Zeiger nicht auf dem
		{
		//Zeichen "." steht

		write_char(*(ptr_hilfe + tab));     //Zeichen an der Position des Hilfe-Zeigers an die Anzeige
		tab++;                              //senden Adresse des Hilfezeigers umn 1 erhï¿œhen
		}
}

void port_init(void)
{
	DDRA = 0xFF;                      //PA0 und PA1 sind Ausgï¿œnge
	DDRB = 0xFF;                      //PB0...PB4 sind Ausgï¿œnge
}

