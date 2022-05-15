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

	/// �j �gyfel l�trehoz�sa
	/// @param nev - �gyf�l neve
	/// @param cim - �gyf�l c�me
	/// @param tel - �gyf�l telefonsz�ma
	/// @param cs - �gyf�l csomagj�nak neve
	void createnewC(String nev, String cim, String tel, String cs);

	/// Forgalom be�ll�t�sa
	/// @param perc - percek sz�ma
	/// @param sms - smsek sz�ma
	void setForg(int perc, int sms);

	/// Csomagv�laszt� egy kapott string alapj�n
	/// @param cs - Csomag neve
	void Csomagvalaszto(String cs);

	/// Fizetend� �sszeg, megh�vja az adott csomaghoz tartoz� d�jaz�st.
	/// @return - int �rt�k, mely a fizetendo osszeg
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
	/// �gyf�l adatainak ki�r�sa.
	void kiir(std::ostream& os);

	/// Csomag t�rl�se.
	void clearCsom() {
		delete csom;
	}
	virtual ~Ugyfel() {};
};
