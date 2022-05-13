#pragma once
#include "MobilSz.h"
#include "string5.h"
#include "memtrace.h"

class Csomag {
	int percdij;
	int smsdij;
public:
	/// Díjazás számítása
	/// @param pd - beszélt percek száma
	/// @param sms - elküldött smsek száma
	/// @return - int díj értéke
	virtual int dijazas(int pd, int sms) {
		return (pd * this->percdij) + (sms * this->smsdij);
	}
	int getPercdij() { return percdij; }
	int getSmsdij() { return smsdij; }
	void setSmsdij(int sd) { smsdij = sd; }
	void setPercdij(int pd) { percdij = pd; }
	virtual String getCsomag() { return "Nincs csomag"; }
	virtual ~Csomag() {};
};

class Alap : public Csomag {
public:
	Alap() {
		setSmsdij(25);
		setPercdij(25);
	}
	virtual String getCsomag() { return "Alap"; }
};

class MobiNet : public Csomag {
	int ingyensms = 10;
public:
	MobiNet() {
		setSmsdij(45);
		setPercdij(45);
	}
	/// Díjazás számítása ingyen smsekkel együtt
	/// @param pd - beszélt percek száma
	/// @param sms - elküldött smsek száma
	/// @return - int díj értéke
	virtual int dijazas(int pd, int sms) {
		//Ha kevesebb smst küldött mint amennyi ingyenes akkor csak a percek miatt kell fizetnie.
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