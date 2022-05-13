#pragma once
#include "string5.h"
#include "Csomag.h"
#include "memtrace.h"


class Ugyfel : public Csomag {
	String tel;
	String nev;
	String cim;
	int sms;
	int perc;
	Csomag* csom;
public:
	/// Új ügyfel létrehozása
	/// @param nev - Ügyfél neve
	/// @param cim - Ügyfél címe
	/// @param tel - Ügyfél telefonszáma
	/// @param cs - Ügyfél csomagja
	void createnewC(String nev, String cim, int tel, Csomag* cs);
	void setForg(int perc, int sms);
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
	void Csomagvalaszto(String cc) {
		if (strcmp("Alap", cc.c_str()) == 0) {
			this->setCsomag(new Alap());
		}
		else if (strcmp("MobiNet", cc.c_str()) == 0) {
			this->setCsomag(new MobiNet());
		}
		else if (strcmp("SMSMax", cc.c_str()) == 0) {
			this->setCsomag(new SMSMax());
		}
	}
	/// Fizetendõ összeg
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
		return  *this;
	}
	void kiir() {
		std::cout << "Név: " << this->nev << std::endl;
		std::cout << "Cím: " << this->cim << std::endl;
		std::cout << "Telefonszám: " << this->tel << std::endl;
		std::cout << "Csomag: " << this->getCsomag() << std::endl;
		std::cout << "Beszélt percek: " << this->perc << std::endl;
		std::cout << "Elküldött smsek: " << this->sms << std::endl;
	}
	void clearCsom() {
		delete csom;
	}
	virtual ~Ugyfel() {};
};
