#pragma once
#include "MobilSz.h"
#include "memtrace.h"


class Tarolo : public Ugyfel {
	int db = 0;
	Ugyfel* tomb;
public:
	/// Ugyfel hozzáadása a tömbhöz
	/// param cig - Ugyfel adatai
	void hozzaad(Ugyfel cig) {
		Ugyfel* uj = new Ugyfel[++db];
		if (db > 1) {
			for (int i = 0; i < db-1; ++i) {
				uj[i] = tomb[i];
			}
		}
		uj[db - 1] = cig;
		delete[] tomb;
		tomb = uj;
	}
	void setForgalom(int idx, int perc, int sms) {
		tomb[idx].setForg(perc, sms);
	}
	int search(String t) {
		for (int i = 0; i < db; ++i){
			if (strcmp(t.c_str(), tomb[i].getTel().c_str()) == 0) {
				return i;
			}
		}
	}
	void kiir(int idx) {
		tomb[idx].kiir();
	}
	
	virtual ~Tarolo() { 
		for (int i = 0; i < db; ++i) {
			tomb[i].clearCsom();
		}
		delete[] tomb;
	}
};