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
    //Karakter a menüpontok választásához
	char valasz;
	//String a telefonszám felvételekhez
	String tel;
	//Ügyfél felvételéhez
	Ugyfel uj;
	do {
		std::cout << "Kérem válasszon az alábbi menüpontok közül a helyes szám beírásával" << std::endl;
		std::cout << "1 - Új ügyfél felvétele" << std::endl;
		std::cout << "2 - Ügyfél keresése" << std::endl;
		std::cout << "3 - Kilépés" << std::endl;
		std::cin >> valasz;
		switch (valasz)
		{
		case '1':
			uj = t->ugyfelf();
			t->hozzaad(uj);
			break;
		case '2':
			std::cout << "Kérem adja meg az ügyfél telefonszámát:" << std::endl;
			std::cin >> tel;
			//Amennyiben szerepel kiírjuk
			if (t->tEll(tel)) {
				int idx = t->search(tel);
				t->kiir(idx, std::cout);
			}
			else {
				std::cout << "A megadott telefonszámmal nem rendelkezik ügyfél!" << std::endl;
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
	//Elõször ellenõrízzük, hogy megfelelõen mûködik-e a fájl beolvasás/írás.
	TEST(Fájl kezelése, helytelen/nem létezõ fájl beolvasás) {
		Tarolo tt;
		//Elõször az ügyfél fájl nevét írjuk be rosszul
		EXPECT_ANY_THROW(tt.fajlolv("ugy.txt", "forgalom.txt"));
		//Majd a forgalom fájl nevét.
		EXPECT_ANY_THROW(tt.fajlolv("ugyfel.txt", "for.txt"));
		//Végül mindkettõt.
		EXPECT_ANY_THROW(tt.fajlolv("uge.txt", "fff.txt"));
		//Helyesen beírt fájl neveknél nem várunk
		EXPECT_NO_THROW(tt.fajlolv("ugyfel.txt", "forgalom.txt"));
	}END;
	TEST(Fájl kezelése, helytelen / nem létezõ fájl írása) {
		Tarolo tt;
		//Üres tömb esetén várunk throw
		EXPECT_ANY_THROW(tt.fajlir("ugyfel.txt", "forgalom.txt"));
		//Beolvassuk a fájlokat, hogy legyen a tömbbe
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		//Elõször az ügyfél fájl nevét írjuk be rosszul
		EXPECT_ANY_THROW(tt.fajlir("uggyfel.txt", "forgalom.txt"));
		//Majd a forgalom fájl nevét.
		EXPECT_ANY_THROW(tt.fajlir("ugyfel.txt", "forg.txt"));
		//Végül mindkettõt.
		EXPECT_ANY_THROW(tt.fajlir("uge.txt", "fogalom.txt"));
		//Helyesen beírt adatoknál nem várunk
		EXPECT_NO_THROW(tt.fajlir("ugyfel.txt", "forgalom.txt"));
	}END;
	TEST(Getterek tesztelese, get testesetek) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", "0620123456", "Alap");
		EXPECT_STREQ("Példa Géza", u.getNev().c_str());
		EXPECT_STREQ("Budapest Sch", u.getCim().c_str());
		EXPECT_STREQ("0620123456", u.getTel().c_str());
		EXPECT_STREQ("Alap", u.getCsomag().c_str());
		u.clearCsom();
	}END;
	TEST(Dijazas az osztalyban, alap osztaly) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", "0620123456", "Alap");
		u.setForg(65, 10);
		//25 Ft a tarifa
		EXPECT_EQ(1875, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Dijazas az oszalyban, smsmax osztaly) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", "0620123456", "SMSMax");
		u.setForg(55, 30);
		//40 Ft tarifa
		EXPECT_EQ(3400, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Dijazas az osztalyban, mobinet osztaly) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", "0620123456", "MobiNet");
		u.setForg(40, 50);
		//Alapvetoen 4050 lenne a 45 Ft-os tarifaval, viszont -10 db sms a csomag miatt, így -10*45
		EXPECT_EQ(3600, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Dijazas az osztalyban, mobinet keves sms) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", "0620123456", "MobiNet");
		u.setForg(40, 5);
		//Mivel kevesebb smsmt küldött mint amennyi ingyenes csak a percek miatt kell fizetnie (40 perc*45 percdíj)
		EXPECT_EQ(1800, u.fizetendo());
		u.clearCsom();
	}END;
	TEST(Csomag beállítása, rossz csomag teszt) {
		//Átmeneti ügyfél
		Ugyfel u;
		EXPECT_ANY_THROW(u.Csomagvalaszto("Mobi"));
	}END;
	TEST(Tömb index, tömb túlindexelése) {
		//A tömbben szereplõ ügyfelek száma.
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		int max = tt.getdb();
		//A benne lévõ ügyfelek számához képest egyel többel próbálkozunk.
		EXPECT_ANY_THROW(tt.kiir(max + 1, std::cout));
	}END;
	TEST(Ügyfél keresés, nem szereplõ telefonszám) {
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		EXPECT_EQ(-1, tt.search("123"));
	}END
	TEST(Új ügyfél felvétele, már létezõ telefonszám felvétele) {
		//Egy, a szövegvájlban szereplõ ügyfél telefonszámával próbálkozunk.
		//Az ügyfél adatai: 06207980108, Sipos Ernõ, Budapest Zsóka part 94, Alap, 11 perc 3 sms.
		//Elõször ellenõrizzük, hogy tényleg szerepel-e a listában a megadott adatokkal.
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		int id = tt.search("06207980108");
		std::stringstream ss;
		tt.kiir(id, ss);
		EXPECT_STREQ("Név: Sipos Ernõ\nCím: Budapest Zsóka part 94\nTelefonszám: 06207980108\nCsomag: Alap\nBeszélt percek: 11\nElküldött smsek: 3\nBefizetendõ összeg: 350 JMF\n", ss.str().c_str());
		//Majd meghívjuk azt a függvényt ami ellenõrzi, hogy szerepel-e a megadott telefonszám a tömbben, true-t várunk mivel szerepel a listában.
		EXPECT_TRUE(tt.tEll("06207980108"));
	}END;
	TEST(Kiírás, egy beolvasott adat tesztelése) {
		//Tesztelendõ ügyfél adatai: 06708115393, Halász Milán, Kecskemét Barna körút 50, MobiNet, 2perc, 1 sms.
		Tarolo tt;
		tt.fajlolv("ugyfel.txt", "forgalom.txt");
		int id = tt.search("06708115393");
		std::stringstream ss;
		tt.kiir(id, ss);
		EXPECT_STREQ("Név: Halász Milán\nCím: Kecskemét Barna körút 50\nTelefonszám: 06708115393\nCsomag: MobiNet\nBeszélt percek: 2\nElküldött smsek: 1\nBefizetendõ összeg: 90 JMF\n", ss.str().c_str());
	}END;
	//Amennyiben minden teszt helyesen lefutott indulhat a program
	//Tároló létrehozáa
	Tarolo t;
	//Fájlok beolvasása
	t.fajlolv("ugyfel.txt", "forgalom.txt");
	//Menü indítása a létrehozott tárolóval
	menu(&t);
	//Végül kiírunk minden adatot a txtk-be
	t.fajlir("ugyfel.txt", "forgalom.txt");
	return 0;
}
