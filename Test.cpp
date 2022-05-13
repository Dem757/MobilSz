#include <iostream>
#include <fstream>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#include "MobilSz.h"
#include "Csomag.h"
#include "string5.h"
#include "Tarolo.h"
#include "gtest_lite.h"
#include "memtrace.h"



Ugyfel szetszedu(char* f) {
	#pragma warning(push)
	#pragma warning(disable: 6001)
	Ugyfel u;
	char* next_token;
	char* seg = strtok_s(f, ";", &next_token);
	char* ar[4];
	int count = 0;
	while (seg != NULL) {
		ar[count++] = seg;
		seg = strtok_s(NULL, ";", &next_token);
	}
	u.setTel(ar[0]);
	u.setNev(ar[1]);
	u.setCim(ar[2]);
	u.Csomagvalaszto(ar[3]);
	#pragma warning(pop)
	return u;
}

Ugyfel szetszedf(char* f) {
	#pragma warning(push)
	#pragma warning(disable: 6001)
	Ugyfel u;
	char* next_token;
	char* seg = strtok_s(f, ";", &next_token);
	char* ar[3];
	int cnt = 0;
	while (seg != NULL) {
		ar[cnt++] = seg;
		seg = strtok_s(NULL, ";", &next_token);
	}
	u.setTel(ar[0]);
	u.setPerc(atoi(ar[1]));
	u.setSms(atoi(ar[2]));
	#pragma warning(pop)
	return u;
}

int main()
{
#ifdef _WIN32
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif
	std::ifstream dataa;
	dataa.open("ugyfel2.txt");
	char buf[300];
	Tarolo t;
	if (!dataa.is_open()) {
		throw "Fasz";
	}
	else {
		while (dataa.getline(buf, 300)) {
			Ugyfel u = szetszedu(buf);
			t.hozzaad(u);
		}
	}
	char bb[100];
	std::ifstream datab;
	datab.open("forgalom.txt");
	if (!datab.is_open()) {
		throw "Big kuki";
	}
	else {
		while (datab.getline(bb, 300)) {
			Ugyfel b = szetszedf(bb);
			int idx = t.search(b.getTel().c_str());
			t.setForgalom(idx, b.getPerc(), b.getSms());
		}
	}
	/*TEST(Getterek tesztelese, get testesetek) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", 0620123456, new Alap());
		EXPECT_STREQ("Példa Géza", u.getNev().c_str());
		EXPECT_STREQ("Budapest Sch", u.getCim().c_str());
		EXPECT_EQ(0620123456, u.getTel());
		EXPECT_STREQ("Alap", u.getCsomag().c_str());
	}END
		TEST(Dijazas az osztalyban, alap osztaly) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", 0620123456, new Alap());
		u.setPerc(65);
		u.setSms(10);
		//25 Ft a tarifa
		EXPECT_EQ(1875, u.fizetendo());
	}END
		TEST(Dijazas az oszalyban, smsmax osztaly) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", 0620123456, new SMSMax());
		u.setPerc(55);
		u.setSms(30);
		//40 Ft tarifa
		EXPECT_EQ(3400, u.fizetendo());
	}END
		TEST(Dijazas az osztalyban, mobinet osztaly) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", 0620123456, new MobiNet());
		u.setPerc(40);
		u.setSms(50);
		//Alapvetoen 4050 lenne a 45 Ft-os tarifaval, viszont -10 db sms a csomag miatt, így -10*45
		EXPECT_EQ(3600, u.fizetendo());
	}END
		TEST(Dijazas az osztalyban, mobinet keves sms) {
		Ugyfel u;
		u.createnewC("Példa Géza", "Budapest Sch", 0620123456, new MobiNet());
		u.setPerc(40);
		u.setSms(5);
		//Mivel kevesebb smsmt küldött mint amennyi ingyenes csak a percek miatt kell fizetnie (40 perc*45 percdíj)
		EXPECT_EQ(1800, u.fizetendo());
	}END*/
	dataa.close();
	datab.close();
	return 0;
}