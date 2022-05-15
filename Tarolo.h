#pragma once
#include <string.h>
#include "MobilSz.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif


class Tarolo : public Ugyfel {
	int db;				///�gyfelek sz�ma
	Ugyfel* tomb;		///�gyfeleket t�rol� t�mb
public:
	Tarolo() {
		db = 0;
	}

	/// �gyfelek sz�m�nak n�vel�se.
	void dbInc() {
		db++;
	}

	int getdb() { return db; }
	/// Ugyfel hozz�ad�sa a t�mbh�z
	/// @param u - Ugyfel adatai
	void hozzaad(Ugyfel u);

	/// Forgalom be�ll�t�sa, megh�vja az Ugyfel f�gv�ny�t.
	/// @param idx - a t�mb elem�nek indexe
	/// @param perc - a be�ll�tand� percek sz�ma
	/// @param sms - a be�ll�tand� smsek sz�ma
	void setForgalom(int idx, int perc, int sms) {
		if (idx > db || idx < 0)
			throw "T�l/alul indexel�s";
		else
			tomb[idx].setForg(perc, sms);
	}

	/// �gyf�l keres�se a t�mbben
	/// @param t - �gyf�l telefonsz�ma
	/// @return - int �rt�k, az adott �gyf�l indexe a t�mbben
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

	/// �gyf�l adatainak ki�r�sa, megh�vja az �gyf�l f�ggv�ny�t
	/// @param idx - �gyf�l indexe a t�mbben
	void kiir(int idx, std::ostream& os) {
		if (idx > db || idx < 0)
			throw "T�l/alul indexel�s";
		else
			tomb[idx].kiir(os);
	}

	/// Az ugyfel.txt f�jl adatainak sz�tbont�sa ";" karakterek ment�n �s beilleszt�se a t�mbbe.
	/// @param f - egy sort tartalmaz a f�jlb�l
	void szetszedu(char* f);

	/// A forgalom.txt f�jl adatainak sz�tbont�sa ";" karakterek ment�n �s beilleszt�se a t�mbbe.
	/// @param f - egy sort tartalmaz a f�jlb�l
	/// @return - egy Ugyfel, be�ll�tott tele
	void szetszedf(char* f);

	/// �gyf�l felv�tele a felhaszn�l�t�l.
	/// @return - egy �gyf�l, el�re be�ll�tott adatokkal
	Ugyfel ugyfelf();

	/// F�jl beolvas�sa �s elt�rol�sa a t�mbben.
	/// @param u - az �gyfeleket tartalmaz� sz�vegf�jl neve
	/// @param f - a forgalmat tartalmaz� sz�vegf�jl neve
	void fajlolv(const char* u, const char* f);

	/// F�jlokba �r�s
	/// @param u - �gyf�l
	void fajlir(const char* u, const char* f);

	virtual ~Tarolo() {
		for (int i = 0; i < db; ++i) {
			tomb[i].clearCsom();
		}
		delete[] tomb;
	}
};
