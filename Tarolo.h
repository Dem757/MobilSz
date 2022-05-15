#pragma once
#include <string.h>
#include "MobilSz.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif


class Tarolo : public Ugyfel {
	int db;				///Ügyfelek száma
	Ugyfel* tomb;		///Ügyfeleket tároló tömb
public:
	Tarolo() {
		db = 0;
	}

	/// Ügyfelek számának növelése.
	void dbInc() {
		db++;
	}

	int getdb() { return db; }
	/// Ugyfel hozzáadása a tömbhöz
	/// @param u - Ugyfel adatai
	void hozzaad(Ugyfel u);

	/// Forgalom beállítása, meghívja az Ugyfel fügvényét.
	/// @param idx - a tömb elemének indexe
	/// @param perc - a beállítandó percek száma
	/// @param sms - a beállítandó smsek száma
	void setForgalom(int idx, int perc, int sms) {
		if (idx > db || idx < 0)
			throw "Túl/alul indexelés";
		else
			tomb[idx].setForg(perc, sms);
	}

	/// Ügyfél keresése a tömbben
	/// @param t - Ügyfél telefonszáma
	/// @return - int érték, az adott ügyfél indexe a tömbben
	int search(String t) {
		for (int i = 0; i < db; ++i) {
			if (strcmp(t.c_str(), tomb[i].getTel().c_str()) == 0) {
				return i;
			}
		}
		return -1;
	}

	bool tEll(String t) {
		if (this->search(t) >= 0)
			return true;
		else
			return false;
	}

	/// Ügyfél adatainak kiírása, meghívja az Ügyfél függvényét
	/// @param idx - Ügyfél indexe a tömbben
	void kiir(int idx, std::ostream& os) {
		if (idx > db || idx < 0)
			throw "Túl/alul indexelés";
		else
			tomb[idx].kiir(os);
	}

	/// Az ugyfel.txt fájl adatainak szétbontása ";" karakterek mentén és beillesztése a tömbbe.
	/// @param f - egy sort tartalmaz a fájlból
	void szetszedu(char* f);

	/// A forgalom.txt fájl adatainak szétbontása ";" karakterek mentén és beillesztése a tömbbe.
	/// @param f - egy sort tartalmaz a fájlból
	/// @return - egy Ugyfel, beállított tele
	void szetszedf(char* f);

	/// Ügyfél felvétele a felhasználótól.
	/// @return - egy ügyfél, elõre beállított adatokkal
	Ugyfel ugyfelf();

	/// Fájl beolvasása és eltárolása a tömbben.
	/// @param u - az ügyfeleket tartalmazó szövegfájl neve
	/// @param f - a forgalmat tartalmazó szövegfájl neve
	void fajlolv(const char* u, const char* f);

	/// Fájlokba írás
	/// @param u - ügyfél
	void fajlir(const char* u, const char* f);

	virtual ~Tarolo() {
		for (int i = 0; i < db; ++i) {
			tomb[i].clearCsom();
		}
		delete[] tomb;
	}
};
