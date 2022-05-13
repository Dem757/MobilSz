#ifndef STRING_H
#define STRING_H
/**
 * \file string2_kesz.h
 *
 * Ez a fájl tartalmazza a
 *   - String osztály deklarációját
 *   - az inline függvényeket. Ha valamit inline-ként akar megvalósítani,
 *     akkor azt ebbe a fájlba írja! Tipikusan a rövid kódokat szokás
 *     inline-két megvalósítani (pl: c_str).
 *     Más függvényeket ill. definíciókat ne írjon a .h fájlba!
 *
 * A C-ben megírt (string1.c) függvények most tagfüggvényekké váltak, és
 *   eltűnt az első paraméterük (s0) (ebből lett a this).
 * A nevük is megváltozott, mert most már az összetartozást, és a
 *   paraméterek típusára való utalást már nem a név hordozza, hanem az osztály.
 * A createString... alakú függvényekből konstruktorok keletkeztek.
 * A disposeString destruktorrá alakült át.
 * Egyes műveletvégző függvényekből pedig operátor függvény lett.
 */


#include <iostream>

#ifndef MEMTRACE
#endif // MEMTRACE

/**
 * A String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 */
class String {
    char *pData;         /// pointer az adatra
    size_t len;    /// hossz lezáró nulla nélkül
public:

	size_t size() const { return len; }


    /// Default konstruktor:
    String() :pData(0), len(0) {}

    /// C-stringet ad vissza
    const char* c_str() const { if (pData) return pData; else return "";}

    /// Konstruktor: egy char karakterből (createStrFromChar)
    String(char ch);

    /// Konstruktor: egy nullával lezárt char sorozatból (createStringFromCharStr)
    String(const char *p);

    /// MÁSOLÓ konstruktor, ami a createStringFromString-ből keletkezett
    /// @param s1 - String, amiből létrehozzuk az új String-et
    String(const String& s1);

    /// Destruktor (disposeString)
    ~String() { delete[] pData; }

  /// Egyéb tagfüggvények:
    /// Kiírunk egy Stringet (debug célokra) (ez kész)
    /// Elötte kiírunk egy tetszőleges szöveget.
    /// @param txt - nullával lezárt szövegre mutató pointer
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << std::endl;
    }

  /// Operátorok:
    /// Értékadó operátor is kell !
    /// @param rhs_s - jobboldali String
    /// @return baoldali (módosított) string (referenciája)
    String& operator=(const String& rhs_s);

String& operator+=(const String& rhs_s) {
    *this = *this + rhs_s;
    return *this;
}

    /// Két Stringet összefűz (concatString)
    /// @param rhs_s - jobboldali String
    /// @return új String, ami tartalmazza a két stringet egmás után
    String operator+(const String& rhs_s) const ;

    /// Sztrinhez karaktert összefűz (concatString)
    /// @param rhs_c - jobboldali karakter
    /// @return új String, ami tartalmazza a két sztringet egymás után
    String operator+(char rhs_c) const { return *this + String(rhs_c);}

    /// A string egy megadott indexű elemének REFERENCIÁJÁVAL tér vissza.
    /// charAtString-ből keletkezett, de ezt bal oldalon is lehet használni
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    char& operator[](unsigned int idx);

    /// A string egy megadott indexű elemének REFERENCIÁJÁVAL tér vissza.
    /// charAtString-ből keletkezett. Konstans stringre alkalmazható.
    /// Indexelési hiba esetén const char* kivételt dob (assert helyett).
    /// @param idx - karakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    const char& operator[](unsigned int idx) const;

    void erase() { *this = ""; }
};

/// Globális függvények:
/// kiír az ostream-re (printString)
/// Nem célszerű using-ot használni, mert ez egy include file. Így ki kell írni az std::-t
/// @param os - ostream típusú objektum
/// @param s0 - String, amit kiírunk
/// @return os
/// Vigyázat nem tagfüggvény! Nem is tűnik el az s0 !
/// Nem kell, hogy barát legyen, mert a c_str() segít
std::ostream& operator<<(std::ostream& os, const String& s0);

/// Beolvas az istream-ről egy szót egy string-be.
/// @param is - istream típusú objektum
/// @param s0 - String, amibe beolvas
/// @return is
/// Vigyázat nem tagfüggvény! Nem is tűnik el az s0 !
/// Nem kell, hogy barát legyen mert van Str + ch
std::istream& operator>>(std::istream& is, String& s0);

/// String operator+(char ch, const String& str);
/// Vagy inline, vagy nem itt a helye!
/// Nem kell, hogy barát legyen mert tudunk chr-ből str-be konvertálni
/// két str pedig összeadható
inline String operator+(char ch, const String& str) { return String(ch) + str; }

#endif

