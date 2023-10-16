#pragma once 
#include "iostream"

#include "ASpell.hpp"
#define AT ATarget
using namespace std;

class ASpell ;
class AT {

string  _type;

public:
    AT () {}
    AT (const AT & s) { *this = s ; }
    AT & operator = (const AT & s) {
        _type = s._type;
        return *this ;
    }
    AT (const string & n) : _type(n) {}
    virtual ~ AT () {}
    const string & getType () const { return _type; }
    virtual AT * clone () const = 0;
    void getHitBySpell(const ASpell &) const ;
};

#include "ASpell.hpp" // double incl. spell
