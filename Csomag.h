#pragma once
#include "string5.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif

/// Csomag oszt�ly

class Csomag {
	int percdij;	//Besz�lt percek d�ja
	int smsdij;		//Elk�d�tt smsek d�ja
public:
	/// D�jaz�s sz�m�t�sa
	/// @param pd - besz�lt percek sz�ma
	/// @param sms - elk�ld�tt smsek sz�ma
	/// @return - int d�j �rt�ke
	virtual int dijazas(int pd, int sms) {
		return (pd * this->percdij) + (sms * this->smsdij);
	}
	int getPercdij() { return percdij; }
	int getSmsdij() { return smsdij; }
	void setSmsdij(int sd) { smsdij = sd; }
	void setPercdij(int pd) { percdij = pd; }
	//Ha esetleg valahol hiba cs�szna a rendszerbe �s nem rendelkezik csomaggal.
	virtual String getCsomag() { return "Nincs csomag"; }
	virtual ~Csomag() {};
};

class Alap : public Csomag {
public:
	/// Alap konstruktor
	/// Percd�j �s smsd�j be�ll�t�sa
	Alap() {
		setSmsdij(25);
		setPercdij(25);
	}
	virtual String getCsomag() { return "Alap"; }
};

class MobiNet : public Csomag {
	int ingyensms;		//Ingyenesen k�ldhet� smsek sz�ma
public:
	/// MobiNet konstruktor
	/// Ingyen smsek �s percd�j �s smsd�j be�ll�t�sa.
	MobiNet() {
		ingyensms = 10;
		setSmsdij(45);
		setPercdij(45);
	}
	/// D�jaz�s sz�m�t�sa ingyen smsekkel egy�tt
	/// @param pd - besz�lt percek sz�ma
	/// @param sms - elk�ld�tt smsek sz�ma
	/// @return - int d�j �rt�ke
	virtual int dijazas(int pd, int sms) {
		//Ha kevesebb smst k�ld�tt mint amennyi ingyenes akkor csak a percek miatt kell fizetnie.
		if (ingyensms > sms)
			return pd * this->getPercdij();
		else
			return pd * this->getPercdij() + (sms-ingyensms) * this->getSmsdij();
	}
	virtual String getCsomag() { return "MobiNet"; }
};

class SMSMax : public Csomag {
public:
	SMSMax() {
		setSmsdij(40);
		setPercdij(40);
	}
	virtual String getCsomag() { return "SMSMax"; }
};
