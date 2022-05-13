#include <iostream>
#include "MobilSz.h"
#include "memtrace.h"


void Ugyfel::createnewC(String nev, String cim, int tel, Csomag* cs) {
	Ugyfel::setCim(cim);
	Ugyfel::setNev(nev);
	Ugyfel::setTel(tel);
	Ugyfel::setCsomag(cs);
}

void Ugyfel::setForg(int perc, int sms) {
	Ugyfel::setPerc(perc);
	Ugyfel::setSms(sms);
}