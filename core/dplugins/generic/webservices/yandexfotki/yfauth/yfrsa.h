/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2010-11-14
 * Description : Yandex authentication module
 *
 * This is an Yandex implementation of RSA algorithm.
 * It differs from the standard RSA and incompatible with it.
 *
 * Based on code parts from pegwit program written by George Barwood.
 * This code is in the public domain; do with it what you wish.
 *
 * See links for more details:
 *  Author homepage
 *    www.george-barwood.pwp.blueyonder.co.uk/hp/
 *
 *  Getting token for Yandex.Fotki web service
 *    api.yandex.ru/fotki/doc/overview/authorization-token.xml
 *
 *  Yandex published source code
 *    download.yandex.ru/api-fotki/c-yamrsa.tar.gz
 *
 *  Yandex company web site
 *    https://company.yandex.com/
 *
 * Included by Roman Tsisyk <roman at tsisyk dot com>
 * All unneeded parts was commented out and can be removed
 *
 * ============================================================ */

#ifndef DIGIKAM_YF_RSA_H
#define DIGIKAM_YF_RSA_H

// C++ includes

#include <cstdlib> // std::size_t

namespace YFAuth
{
// VLONG.HPP ---------------------------------

class vlong // very long integer - can be used like long
{
public:

    // Standard arithmetic operators

    friend vlong operator +( const vlong& x, const vlong& y );
    friend vlong operator -( const vlong& x, const vlong& y );
    friend vlong operator *( const vlong& x, const vlong& y );
    friend vlong operator /( const vlong& x, const vlong& y );
    friend vlong operator %( const vlong& x, const vlong& y );
    vlong& operator +=( const vlong& x );
    vlong& operator -=( const vlong& x );

public:

    // Standard comparison operators

    friend inline int operator !=( const vlong& x, const vlong& y )
    {
        return (x.cf( y ) != 0);
    }

    friend inline int operator ==( const vlong& x, const vlong& y )
    {
        return (x.cf( y ) == 0);
    }

    friend inline int operator >=( const vlong& x, const vlong& y )
    {
        return (x.cf( y ) >= 0);
    }

    friend inline int operator <=( const vlong& x, const vlong& y )
    {
        return (x.cf( y ) <= 0);
    }

    friend inline int operator > ( const vlong& x, const vlong& y )
    {
        return (x.cf( y ) > 0);
    }

    friend inline int operator < ( const vlong& x, const vlong& y )
    {
        return (x.cf( y ) < 0);
    }

public:

    // Construction and conversion operations
    vlong(unsigned x = 0);  // krazy:exclude=explicit
    // copy constructor
    vlong(const vlong& x);
    ~vlong();

    operator unsigned ();
    vlong& operator =(const vlong& x);

    void     load( unsigned* a, unsigned n );         // load value, a[0] is lsw
    void     store( unsigned* a, unsigned n ) const;  // low level save, a[0] is lsw
    unsigned get_nunits() const;
    unsigned bits() const;

private:

    class vlong_value* value;
    int   negative;
    int   cf( const vlong& x ) const;
    void  docopy();

    friend class monty;
};

// RSA.HPP -------------------------------------------

class public_key
{
public:

    vlong m,e;
    vlong encrypt( const vlong& plain ); // Requires 0 <= plain < m
    void  MakeMe(const char*);
};

class private_key : public public_key
{
public:

    vlong p,q;
};

// ---------------------------------------------------

#define MAX_CRYPT_BITS 1024

class CCryptoProviderRSA
{
    class private_key prkface;

    void EncryptPortion(const char* pt, std::size_t, char* ct, std::size_t&);

public:

    CCryptoProviderRSA();
    virtual ~CCryptoProviderRSA();

    virtual void Encrypt(const char*, std::size_t, char*, std::size_t&);
    virtual void ImportPublicKey(const char*);
};

} // namespace YFAuth

#endif // DIGIKAM_YF_RSA_H
