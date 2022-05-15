#include <fstream>
#include <string.h>
#include "MobilSz.h"
#include "Tarolo.h"
#ifdef MEMTRACE
# include "memtrace.h"
#endif

//Ugyfel hozz�ad�sa a t�mbh�z
void Tarolo::hozzaad(Ugyfel u) {
	//�gyfelek sz�m�nak n�vel�se
	dbInc();
	//�j, nagyobb t�mb l�trehoz�sa
	Ugyfel* uj = new Ugyfel[db];
	//Adatok �tm�solas�sa amennyiben t�bb mind 1 �gyfel�nk van
	if (db > 1) {
		for (int i = 0; i < db - 1; ++i) {
			uj[i] = tomb[i];
		}
	}
	//�j �gyf�l behelyez�se a t�mbbe
	uj[db - 1] = u;
	//R�gi t�mb felszabad�t�sa
	if(db > 1)
        delete[] tomb;
	tomb = uj;
}


//Az ugyfel.txt f�jl adatainak sz�tbont�sa ";" karakterek ment�n �s beilleszt�se a t�mbbe.
void Tarolo::szetszedu(char* f) {
	//VS-nek nem tetszik a ar 0. eleme valami�rt
//#pragma warning(push)
//#pragma warning(disable: 6001)
	//�tmeneti �gyf�l l�trehoz�sa.
	Ugyfel u;
	//K�vetkez� token
	char* next_token;
	//Seg�d
	char* seg = strtok_s(f, ";", &next_token);
	//�tmeneti t�rol�, melynek elemei lesznek a sz�tbontott adatok
	//A txt-ben �gy szerepelnek az adatok: telefonsz�m;n�v;c�m;csomag;
	char* ar[4];
	int count = 0;
	while (seg != NULL) {
		ar[count++] = seg;
		seg = strtok_s(NULL, ";", &next_token);
	}
	//Ugyf�l l�trehoz�sa az adatok alapj�n
	//A txt elrendez�se miatt:
	//ar[0] : telefonsz�ma
	//ar[1] : n�v
	//ar[2] : c�m
	//ar[3] : csomag
	u.createnewC(ar[1], ar[2], ar[0], ar[3]);
	//Majd hozz�adjuk a t�mbh�z
	this->hozzaad(u);
//#pragma warning(pop)
}

//A forgalom.txt f�jl adatainak sz�tbont�sa ";" karakterek ment�n �s beilleszt�se a t�mbbe.
void Tarolo::szetszedf(char* f) {
	//VS-nek nem tetszik a ar 0. index� eleme valami�rt.
//#pragma warning(push)
//#pragma warning(disable: 6001)
	//K�vetkez� token
	char* next_token;
	//Seg�d
	char* seg = strtok_s(f, ";", &next_token);
	//A t�rol�, melynek elemei lesznek a sz�tbontott adatok
	//A txt-ben �gy szerepelnek az adatok: telefonsz�m;perc;sms;
	char* ar[3];
	//Sz�ml�l�, az indexhez
	int cnt = 0;
	while (seg != NULL) {
		ar[cnt++] = seg;
		seg = strtok_s(NULL, ";", &next_token);
	}
	//Percek sz�ma, intben
	int perc = atoi(ar[1]);
	//Smsek sz�ma intben
	int sms = atoi(ar[2]);
	//Megkeress�k a telefonsz�m alapj�n az �gyfelet
	//Ha benne van a t�mbben akkor be�ll�tijuk az adatait
	//Ha nincs akkor throw
	if (this->tEll(ar[0])) {
		int idx = this->search(ar[0]);
		this->setForgalom(idx, perc, sms);
	}
	else {
		throw "Nem l�tezik ilyen telefonsz�mmal �gyf�l";
	}
//#pragma warning(pop)
}

//�gyf�l felv�tele a felhaszn�l�t�l.
Ugyfel Tarolo::ugyfelf() {
	//Egy �tmeneti �gyfelet hozunk l�tre
	Ugyfel u;
	//�tmeneti t�rol�k az adatokhoz
	char nev[100];
	char tel[100];
	char cim[100];
	char csom[10];
	//Adatok beolvas�sa
	std::cout << "K�rem adja meg az �gyf�l adatait!" << std::endl;
	std::cin.ignore();
	std::cout << "�gyf�l neve: ";
	std::cin.getline(nev, 100);
	std::cout << "�gyf�l telefonsz�ma: ";
	std::cin.getline(tel, 100);
	std::cout << "�gyf�l c�me: ";
	std::cin.getline(cim, 100);
	std::cout << "�gyf�l csomagja: ";
	std::cin.getline(csom, 10);
	//A tEll hamisat ad vissza amennyiben nem szerepel a t�mbben ilyen telefonsz�mmal m�r m�s.
	//Ha hamis l�trehozunk egy �gyfelet �s mivel �j �gyf�l ez�rt nincs m�g forgalma
	//Ha igaz akkor kiv�telt dobunk
	if (!this->tEll(tel)) {
		u.createnewC(nev, cim, tel, csom);
		u.setForg(0, 0);
	}
	else {
		throw "M�r szerepel a megadott telefonsz�m";
	}
	//V�g�l visszaadjuk a l�trehozott �gyfelet
	return u;
}

// F�jl beolvas�sa �s elt�rol�sa a t�mbben.
void Tarolo::fajlolv(const char* u, const char* f) {
	//�gyfeleket tartalmaz� sz�vegf�jl megnyit�sa olvas�sra.
	std::ifstream dataa;
	dataa.open(u);
	//�tmeneti t�rol� az �gyfelekhez
	char buf[300];
	//Megn�zz�k, hogy siker�lt-e megnyitni, ha nem akkor throw, ha igen akkor darabokra szedj�k a beolvasott sort
	if (!dataa.is_open()) {
		throw "�gyf�l adatb�zis hi�nyzik!";
	}
	else {
		while (dataa.getline(buf, 300)) {
			this->szetszedu(buf);
		}
	}
	//�tmeneti t�rol� a forgalomhoz
	char bb[100];
	//Forgalmat tartalmaz� sz�vegf�jl megnyit�sa olvas�sra
	std::ifstream datab;
	datab.open(f);
	//Megn�zz�k, hogy siker�lt-e megnyitni, ha nem akkor throw, ha igen akkor darabokra szedj�k a beolvasott sort
	if (!datab.is_open()) {
		throw "Forgalom adatb�zis hi�nyzik";
	}
	else {
		while (datab.getline(bb, 100)) {
			this->szetszedf(bb);
		}
	}
	//F�jlok bez�r�sa
	datab.close();
	dataa.close();
}

// F�jlokba �r�s
void Tarolo::fajlir(const char* u, const char* f) {
	if (db == 0) {
        throw "Nincs adat";
	}
    else {
        //Sz�lunk ha nem a megfelel�, a dokument�ci�ban megadott n�vvel rendelkez� f�jlt akarn�nk �rni.
        if (strcmp(u, "ugyfel.txt") != 0)
            throw "Nem megfelel� f�jl olvas�sa.";
        if (strcmp(f, "forgalom.txt") != 0) {
            throw "Nem megfelel� f�jl olvas�sa.";
        }
        //ugyfel.txt megnyit�sa, �r�sra
        std::ofstream datu;
        //Ha nem siker�lne megnyitni a sz�vegf�jlt
        datu.open(u);
        if (!datu.is_open())
		throw "F�jl megnyit�sa sikertelen.";
        //forgalom.txt megnyit�sa, �r�sra
        std::ofstream datf;
        datf.open(f);
        //Ha nem siker�lne megnyitni a sz�vegf�jlt
        if (!datf.is_open())
            throw "F�jl megnyit�sa sikertelen.";
        //ugyfel.txt f�jlba ki�rjuk egyes�vel az adatokat a t�mbb�l
        for (int i = 0; i < db; i++)
        {
            datu << tomb[i].getTel() << ";" << tomb[i].getNev() << ";" << tomb[i].getCim() << ";" << tomb[i].getCsomag() << ";" << "\n";
        }
        //�s a forgalom.txt f�jlba is ki�rjuk �ket
        for (int i = 0; i < db; ++i)
            datf << tomb[i].getTel() << ";" << tomb[i].getPerc() << ";" << tomb[i].getSms() << ";" << "\n";
        //F�jlok bez�r�sa.
        datu.close();
        datf.close();
    }
}
