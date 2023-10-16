#pragma once 
#include "iostream"

#include "ATarget.hpp"
#define ASP ASpell
using namespace std;

class ATarget ;
class ASpell {

string  _name, _effects;

public:
    ASP () {}
    ASP (const ASP & s) { *this = s ; }
    ASP & operator = (const ASP & s) {
        _name = s._name;
        _effects = s._effects;
        return *this ;
    }
    ASP (const string & n, const string & e) : _name(n), _effects(e) {;;}
    virtual ~ ASP () {}
    const string & getName () const { return _name; }
    const string & getEffects () const { return _effects; }
    virtual ASP * clone () const = 0;
    void launch(const ATarget &) const ;
};


