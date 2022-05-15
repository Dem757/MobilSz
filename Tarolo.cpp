#include <fstream>
#include <string.h>
#include "MobilSz.h"
#include "Tarolo.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif

//Ugyfel hozzáadása a tömbhöz
void Tarolo::hozzaad(Ugyfel u) {
	//Ügyfelek számának növelése
	dbInc();
	//Új, nagyobb tömb létrehozása
	Ugyfel* uj = new Ugyfel[db];
	//Adatok átmásolasása amennyiben több mind 1 ügyfelünk van
	if (db > 1) {
		for (int i = 0; i < db - 1; ++i) {
			uj[i] = tomb[i];
		}
	}
	//Új ügyfél behelyezése a tömbbe
	uj[db - 1] = u;
	//Régi tömb felszabadítása
	if(db > 1)
        delete[] tomb;
	tomb = uj;
}


//Az ugyfel.txt fájl adatainak szétbontása ";" karakterek mentén és beillesztése a tömbbe.
void Tarolo::szetszedu(char* f) {
	//VS-nek nem tetszik a ar 0. eleme valamiért
//#pragma warning(push)
//#pragma warning(disable: 6001)
	//Átmeneti ügyfél létrehozása.
	Ugyfel u;
	//Következõ token
	char* next_token;
	//Segéd
	char* seg = strtok_s(f, ";", &next_token);
	//Átmeneti tároló, melynek elemei lesznek a szétbontott adatok
	//A txt-ben így szerepelnek az adatok: telefonszám;név;cím;csomag;
	char* ar[4];
	int count = 0;
	while (seg != NULL) {
		ar[count++] = seg;
		seg = strtok_s(NULL, ";", &next_token);
	}
	//Ugyfél létrehozása az adatok alapján
	//A txt elrendezése miatt:
	//ar[0] : telefonszáma
	//ar[1] : név
	//ar[2] : cím
	//ar[3] : csomag
	u.createnewC(ar[1], ar[2], ar[0], ar[3]);
	//Majd hozzáadjuk a tömbhöz
	this->hozzaad(u);
//#pragma warning(pop)
}

//A forgalom.txt fájl adatainak szétbontása ";" karakterek mentén és beillesztése a tömbbe.
void Tarolo::szetszedf(char* f) {
	//VS-nek nem tetszik a ar 0. indexû eleme valamiért.
//#pragma warning(push)
//#pragma warning(disable: 6001)
	//Következõ token
	char* next_token;
	//Segéd
	char* seg = strtok_s(f, ";", &next_token);
	//A tároló, melynek elemei lesznek a szétbontott adatok
	//A txt-ben így szerepelnek az adatok: telefonszám;perc;sms;
	char* ar[3];
	//Számláló, az indexhez
	int cnt = 0;
	while (seg != NULL) {
		ar[cnt++] = seg;
		seg = strtok_s(NULL, ";", &next_token);
	}
	//Percek száma, intben
	int perc = atoi(ar[1]);
	//Smsek száma intben
	int sms = atoi(ar[2]);
	//Megkeressük a telefonszám alapján az ügyfelet
	//Ha benne van a tömbben akkor beállítijuk az adatait
	//Ha nincs akkor throw
	if (this->tEll(ar[0])) {
		int idx = this->search(ar[0]);
		this->setForgalom(idx, perc, sms);
	}
	else {
		throw "Nem létezik ilyen telefonszámmal ügyfél";
	}
//#pragma warning(pop)
}

//Ügyfél felvétele a felhasználótól.
Ugyfel Tarolo::ugyfelf() {
	//Egy átmeneti ügyfelet hozunk létre
	Ugyfel u;
	//Átmeneti tárolók az adatokhoz
	char nev[100];
	char tel[100];
	char cim[100];
	char csom[10];
	//Adatok beolvasása
	std::cout << "Kérem adja meg az ügyfél adatait!" << std::endl;
	std::cin.ignore();
	std::cout << "Ügyfél neve: ";
	std::cin.getline(nev, 100);
	std::cout << "Ügyfél telefonszáma: ";
	std::cin.getline(tel, 100);
	std::cout << "Ügyfél címe: ";
	std::cin.getline(cim, 100);
	std::cout << "Ügyfél csomagja: ";
	std::cin.getline(csom, 10);
	//A tEll hamisat ad vissza amennyiben nem szerepel a tömbben ilyen telefonszámmal már más.
	//Ha hamis létrehozunk egy ügyfelet és mivel új ügyfél ezért nincs még forgalma
	//Ha igaz akkor kivételt dobunk
	if (!this->tEll(tel)) {
		u.createnewC(nev, cim, tel, csom);
		u.setForg(0, 0);
	}
	else {
		throw "Már szerepel a megadott telefonszám";
	}
	//Végül visszaadjuk a létrehozott ügyfelet
	return u;
}

// Fájl beolvasása és eltárolása a tömbben.
void Tarolo::fajlolv(const char* u, const char* f) {
	//Ügyfeleket tartalmazó szövegfájl megnyitása olvasásra.
	std::ifstream dataa;
	dataa.open(u);
	//Átmeneti tároló az ügyfelekhez
	char buf[300];
	//Megnézzük, hogy sikerült-e megnyitni, ha nem akkor throw, ha igen akkor darabokra szedjük a beolvasott sort
	if (!dataa.is_open()) {
		throw "Ügyfél adatbázis hiányzik!";
	}
	else {
		while (dataa.getline(buf, 300)) {
			this->szetszedu(buf);
		}
	}
	//Átmeneti tároló a forgalomhoz
	char bb[100];
	//Forgalmat tartalmazó szövegfájl megnyitása olvasásra
	std::ifstream datab;
	datab.open(f);
	//Megnézzük, hogy sikerült-e megnyitni, ha nem akkor throw, ha igen akkor darabokra szedjük a beolvasott sort
	if (!datab.is_open()) {
		throw "Forgalom adatbázis hiányzik";
	}
	else {
		while (datab.getline(bb, 100)) {
			this->szetszedf(bb);
		}
	}
	//Fájlok bezárása
	datab.close();
	dataa.close();
}

// Fájlokba írás
void Tarolo::fajlir(const char* u, const char* f) {
	if (db == 0) {
        throw "Nincs adat";
	}
    else {
        //Szólunk ha nem a megfelelõ, a dokumentációban megadott névvel rendelkezõ fájlt akarnánk írni.
        if (strcmp(u, "ugyfel.txt") != 0)
            throw "Nem megfelelõ fájl olvasása.";
        if (strcmp(f, "forgalom.txt") != 0) {
            throw "Nem megfelelõ fájl olvasása.";
        }
        //ugyfel.txt megnyitása, írásra
        std::ofstream datu;
        //Ha nem sikerülne megnyitni a szövegféjlt
        datu.open(u);
        if (!datu.is_open())
		throw "Fájl megnyitása sikertelen.";
        //forgalom.txt megnyitása, írásra
        std::ofstream datf;
        datf.open(f);
        //Ha nem sikerülne megnyitni a szövegfájlt
        if (!datf.is_open())
            throw "Fájl megnyitása sikertelen.";
        //ugyfel.txt fájlba kiírjuk egyesével az adatokat a tömbbõl
        for (int i = 0; i < db; i++)
        {
            datu << tomb[i].getTel() << ";" << tomb[i].getNev() << ";" << tomb[i].getCim() << ";" << tomb[i].getCsomag() << ";" << "\n";
        }
        //és a forgalom.txt fájlba is kiírjuk õket
        for (int i = 0; i < db; ++i)
            datf << tomb[i].getTel() << ";" << tomb[i].getPerc() << ";" << tomb[i].getSms() << ";" << "\n";
        //Fájlok bezárása.
        datu.close();
        datf.close();
    }
}
