#include <iostream>
#include <string.h>
#include "MobilSz.h"
#include "Csomag.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif

//�j �gyfel l�trehoz�sa
void Ugyfel::createnewC(String nev, String cim, String tel, String cs) {
	//C�m be�ll�t�sa
	Ugyfel::setCim(cim);
	//N�v be�ll�t�sa
	Ugyfel::setNev(nev);
	//Telefonsz�m be�ll�tsa
	Ugyfel::setTel(tel);
	//Csomag be�ll�t�sa
	Ugyfel::Csomagvalaszto(cs);
}

// Forgalom be�ll�t�sa
void Ugyfel::setForg(int perc, int sms) {
	//Besz�lt percek be�ll�t�sa
	Ugyfel::setPerc(perc);
	//Elk�ld�tt smsek be�ll�t�sa
	Ugyfel::setSms(sms);
}

// Csomagv�laszt� egy kapott string alapj�n
void Ugyfel::Csomagvalaszto(String cs) {
	//Kapott sz�veg alapj�n, azt �sszehasonl�tva �ll�tjuk be a csomagot
	//Amennyiban b�v�teni szeretn�nk a csomagok sz�m�t akkor itt is meg kell adni egy �jabb else if �gban
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
		throw "Nem l�tezik ilyen csomag.";
	}
}

// �gyf�l adatainak ki�r�sa.
void Ugyfel::kiir(std::ostream& os) {
	os << "N�v: " << this->nev << "\n";
	os << "C�m: " << this->cim << "\n";
	os << "Telefonsz�m: " << this->tel << "\n";
	os << "Csomag: " << this->getCsomag() << "\n";
	os << "Besz�lt percek: " << this->perc << "\n";
	os << "Elk�ld�tt smsek: " << this->sms << "\n";
	os << "Befizetend� �sszeg: " << this->fizetendo() << " JMF" << "\n";
}

