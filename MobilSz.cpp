#include <iostream>
#include <string.h>
#include "MobilSz.h"
#include "Csomag.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif

//Új ügyfel létrehozása
void Ugyfel::createnewC(String nev, String cim, String tel, String cs) {
	//Cím beállítása
	Ugyfel::setCim(cim);
	//Név beállítása
	Ugyfel::setNev(nev);
	//Telefonszám beállítsa
	Ugyfel::setTel(tel);
	//Csomag beállítása
	Ugyfel::Csomagvalaszto(cs);
}

// Forgalom beállítása
void Ugyfel::setForg(int perc, int sms) {
	//Beszélt percek beállítása
	Ugyfel::setPerc(perc);
	//Elküldött smsek beállítása
	Ugyfel::setSms(sms);
}

// Csomagválasztó egy kapott string alapján
void Ugyfel::Csomagvalaszto(String cs) {
	//Kapott szöveg alapján, azt összehasonlítva állítjuk be a csomagot
	//Amennyiban bõvíteni szeretnénk a csomagok számát akkor itt is meg kell adni egy újabb else if ágban
	if (strcmp("Alap", cs.c_str()) == 0) {
		this->setCsomag(new Alap());
	}
	else if (strcmp("MobiNet", cs.c_str()) == 0) {
		this->setCsomag(new MobiNet());
	}
	else if (strcmp("SMSMax", cs.c_str()) == 0) {
		this->setCsomag(new SMSMax());
	}
	//Ha valami baj lenne
	else {
		throw "Nem létezik ilyen csomag.";
	}
}

// Ügyfél adatainak kiírása.
void Ugyfel::kiir(std::ostream& os) {
	os << "Név: " << this->nev << "\n";
	os << "Cím: " << this->cim << "\n";
	os << "Telefonszám: " << this->tel << "\n";
	os << "Csomag: " << this->getCsomag() << "\n";
	os << "Beszélt percek: " << this->perc << "\n";
	os << "Elküldött smsek: " << this->sms << "\n";
	os << "Befizetendõ összeg: " << this->fizetendo() << " JMF" << "\n";
}

