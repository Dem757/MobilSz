#include <iostream>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	#define WINX
	#include <windows.h>
#endif

#include "MobilSz.h"
#include "Csomag.h"
#include "string5.h"
#include "Tarolo.h"
#ifdef MEMTRACE
    #include "memtrace.h"
#endif
#include "gtest_lite.h"


void menu(Tarolo* t) {
    //Karakter a men�pontok v�laszt�s�hoz
	char valasz;
	//String a telefonsz�m felv�telekhez
	String tel;
	//�gyf�l felv�tel�hez
	Ugyfel uj;
	do {
		std::cout << "K�rem v�lasszon az al�bbi men�pontok k�z�l a helyes sz�m be�r�s�val" << std::endl;
		std::cout << "1 - �j �gyf�l felv�tele" << std::endl;
		std::cout << "2 - �gyf�l keres�se" << std::endl;
		std::cout << "3 - Kil�p�s" << std::endl;
		std::cin >> valasz;
		switch (valasz)
		{
		case '1':
			uj = t->ugyfelf();
			t->hozzaad(uj);
			break;
		case '2':
			std::cout << "K�rem adja meg az �gyf�l telefonsz�m�t:" << std::endl;
			std::cin >> tel;
			//Amennyiben szerepel ki�rjuk
			if (t->tEll(tel)) {
				int idx = t->search(tel);
				t->kiir(idx, std::cout);
			}
			else {
				std::cout << "A megadott telefonsz�mmal nem rendelkezik �gyf�l!" << std::endl;
			}
			std::cout << '\n';
			break;
		case '3':
			break;
		default:
			std::cout << "Helytelen bemenet!" << std::endl;
			break;
		}
	} while (!(valasz == '3' || std::cin.eof()));
}

int main()
{
#ifdef WINX
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif
	//El�sz�r ellen�r�zz�k, hogy megfelel�en m�k�dik-e a f�jl beolvas�s/�r�s.
	TEST(F�jl kezel�se, helytelen/nem l�tez� f�jl beolvas�s) {
		Tarolo tt;
		//El�sz�r az �gyf�l f�jl nev�t �rjuk be rosszul
		EXPECT_ANY_THROW(tt.fajlolv("ugy.txt", "forgalom.txt"));
		//Majd a forgalom f�jl nev�t.
		EXPECT_ANY_THROW(tt.fajlolv("ugyfel.txt", "for.txt"));
		//V�g�l mindkett�t.
		EXPECT_ANY_THROW(tt.fajlolv("uge.txt", "fff.txt"));
		//Helyesen be�rt f�jl nevekn�l nem v�runk
		EXPECT_NO_THROW(tt.fajlolv("ugyfel.txt", "forgalom.txt"));
	}END;
	TEST(F�jl kezel�se, helytelen / nem l�tez� f�jl �r�sa) {
		Tarolo tt;
		//�res t�mb eset�n v�runk throw
		EXPECT_ANY_THROW(tt.fajlir("ugyfel.txt", "forgalom.txt"));
		//Beolvassuk a f�jlokat, hogy legyen a t�mbbe
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		//El�sz�r az �gyf�l f�jl nev�t �rjuk be rosszul
		EXPECT_ANY_THROW(tt.fajlir("uggyfel.txt", "forgalom.txt"));
		//Majd a forgalom f�jl nev�t.
		EXPECT_ANY_THROW(tt.fajlir("ugyfel.txt", "forg.txt"));
		//V�g�l mindkett�t.
		EXPECT_ANY_THROW(tt.fajlir("uge.txt", "fogalom.txt"));
		//Helyesen be�rt adatokn�l nem v�runk
		EXPECT_NO_THROW(tt.fajlir("ugyfel.txt", "forgalom.txt"));
	}END;
	TEST(Getterek tesztelese, get testesetek) {
		Ugyfel u;
		u.createnewC("P�lda G�za", "Budapest Sch", "0620123456", "Alap");
		EXPECT_STREQ("P�lda G�za", u.getNev().c_str());
		EXPECT_STREQ("Budapest Sch", u.getCim().c_str());
		EXPECT_STREQ("0620123456", u.getTel().c_str());
		EXPECT_STREQ("Alap", u.getCsomag().c_str());
		u.clearCsom();
	}END;
	TEST(Dijazas az osztalyban, alap osztaly) {
		Ugyfel u;
		u.createnewC("P�lda G�za", "Budapest Sch", "0620123456", "Alap");
		u.setForg(65, 10);
		//25 Ft a tarifa
		EXPECT_EQ(1875, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Dijazas az oszalyban, smsmax osztaly) {
		Ugyfel u;
		u.createnewC("P�lda G�za", "Budapest Sch", "0620123456", "SMSMax");
		u.setForg(55, 30);
		//40 Ft tarifa
		EXPECT_EQ(3400, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Dijazas az osztalyban, mobinet osztaly) {
		Ugyfel u;
		u.createnewC("P�lda G�za", "Budapest Sch", "0620123456", "MobiNet");
		u.setForg(40, 50);
		//Alapvetoen 4050 lenne a 45 Ft-os tarifaval, viszont -10 db sms a csomag miatt, �gy -10*45
		EXPECT_EQ(3600, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Dijazas az osztalyban, mobinet keves sms) {
		Ugyfel u;
		u.createnewC("P�lda G�za", "Budapest Sch", "0620123456", "MobiNet");
		u.setForg(40, 5);
		//Mivel kevesebb smsmt k�ld�tt mint amennyi ingyenes csak a percek miatt kell fizetnie (40 perc*45 percd�j)
		EXPECT_EQ(1800, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Csomag be�ll�t�sa, rossz csomag teszt) {
		//�tmeneti �gyf�l
		Ugyfel u;
		EXPECT_ANY_THROW(u.Csomagvalaszto("Mobi"));
	}END;
	TEST(T�mb index, t�mb t�lindexel�se) {
		//A t�mbben szerepl� �gyfelek sz�ma.
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		int max = tt.getdb();
		//A benne l�v� �gyfelek sz�m�hoz k�pest egyel t�bbel pr�b�lkozunk.
		EXPECT_ANY_THROW(tt.kiir(max + 1, std::cout));
	}END;
	TEST(�gyf�l keres�s, nem szerepl� telefonsz�m) {
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		EXPECT_EQ(-1, tt.search("123"));
	}END
	TEST(�j �gyf�l felv�tele, m�r l�tez� telefonsz�m felv�tele) {
		//Egy, a sz�vegv�jlban szerepl� �gyf�l telefonsz�m�val pr�b�lkozunk.
		//Az �gyf�l adatai: 06207980108, Sipos Ern�, Budapest Zs�ka part 94, Alap, 11 perc 3 sms.
		//El�sz�r ellen�rizz�k, hogy t�nyleg szerepel-e a list�ban a megadott adatokkal.
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		int id = tt.search("06207980108");
		std::stringstream ss;
		tt.kiir(id, ss);
		EXPECT_STREQ("N�v: Sipos Ern�\nC�m: Budapest Zs�ka part 94\nTelefonsz�m: 06207980108\nCsomag: Alap\nBesz�lt percek: 11\nElk�ld�tt smsek: 3\nBefizetend� �sszeg: 350 JMF\n", ss.str().c_str());
		//Majd megh�vjuk azt a f�ggv�nyt ami ellen�rzi, hogy szerepel-e a megadott telefonsz�m a t�mbben, true-t v�runk mivel szerepel a list�ban.
		EXPECT_TRUE(tt.tEll("06207980108"));
	}END;
	TEST(Ki�r�s, egy beolvasott adat tesztel�se) {
		//Tesztelend� �gyf�l adatai: 06708115393, Hal�sz Mil�n, Kecskem�t Barna k�r�t 50, MobiNet, 2perc, 1 sms.
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		int id = tt.search("06708115393");
		std::stringstream ss;
		tt.kiir(id, ss);
		EXPECT_STREQ("N�v: Hal�sz Mil�n\nC�m: Kecskem�t Barna k�r�t 50\nTelefonsz�m: 06708115393\nCsomag: MobiNet\nBesz�lt percek: 2\nElk�ld�tt smsek: 1\nBefizetend� �sszeg: 90 JMF\n", ss.str().c_str());
	}END;
	//Amennyiben minden teszt helyesen lefutott indulhat a program
	//T�rol� l�trehoz�a
	Tarolo t;
	//F�jlok beolvas�sa
	t.fajlolv("ugyfel.txt", "forgalom.txt");
	//Men� ind�t�sa a l�trehozott t�rol�val
	menu(&t);
	//V�g�l ki�runk minden adatot a txtk-be
	t.fajlir("ugyfel.txt", "forgalom.txt");
	return 0;
}
