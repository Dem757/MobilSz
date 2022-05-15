#pragma once
#include "string5.h"
#include "Csomag.h"
#ifdef MEMTRACE
    #include "memtrace.h"
#endif


class Ugyfel : public Csomag {
	String tel;
	String nev;
	String cim;
	int sms;
	int perc;
	Csomag* csom;
public:
	String getNev() { return nev; }
	String getTel() { return tel; }
	String getCim() { return cim; }
	int getSms() { return sms; }
	int getPerc() { return perc; }
	String getCsomag() { return csom->getCsomag(); }

	void setNev(String n) { nev = n; }
	void setTel(String t) { tel = t; }
	void setCim(String c) { cim = c; }
	void setSms(int s) { sms = s; }
	void setPerc(int p) { perc = p; }
	void setCsomag(Csomag* cs) { csom = cs; }

	/// Új ügyfel létrehozása
	/// @param nev - Ügyfél neve
	/// @param cim - Ügyfél címe
	/// @param tel - Ügyfél telefonszáma
	/// @param cs - Ügyfél csomagjának neve
	void createnewC(String nev, String cim, String tel, String cs);

	/// Forgalom beállítása
	/// @param perc - percek száma
	/// @param sms - smsek száma
	void setForg(int perc, int sms);

	/// Csomagválasztó egy kapott string alapján
	/// @param cs - Csomag neve
	void Csomagvalaszto(String cs);

	/// Fizetendõ összeg, meghívja az adott csomaghoz tartozó díjazást.
	/// @return - int érték, mely a fizetendo osszeg
	int fizetendo() {
		return csom->dijazas(perc, sms);
	}

	Ugyfel& operator=(const Ugyfel& u) {
		if (this == &u) {
			return *this;
		}
		this->setCim(u.cim);
		this->setNev(u.nev);
		this->setTel(u.tel);
		this->setCsomag(u.csom);
		this->setPerc(u.perc);
		this->setSms(u.sms);
		return *this;
	}
	/// Ügyfél adatainak kiírása.
	void kiir(std::ostream& os);

	/// Csomag törlése.
	void clearCsom() {
		delete csom;
	}
	virtual ~Ugyfel() {};
};
