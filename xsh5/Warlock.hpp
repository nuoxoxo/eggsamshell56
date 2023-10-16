#pragma once
#include "iostream"
#include "map"
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "Fwoosh.hpp"
#include "Dummy.hpp"
#include "SpellBook.hpp"
#include "TargetGenerator.hpp"

#define W Warlock
using namespace std;

class W {

string  _name, _title;
// map<string, ASpell *>   spells;
SpellBook   book;

W () {}
W (const W & wl) { *this = wl; (void) wl ; }
W & operator = (const W & wl) {
    (void) wl;
    return * this ;
}

public:

    void learnSpell ( ASpell * spell ) {
        // if (spell)
        //     spells[spell->getName()] = spell->clone() ;
        if (spell)
            book.learnSpell( spell );
    }
    void forgetSpell ( const string & spellname ) {
        // if (spells[spellname])
        //     delete spells[spellname];
        // spells.erase(spellname);
        book.forgetSpell( spellname );
    }
    void launchSpell ( const string & spellname, const ATarget & target ) {
        // if (spells[spellname])
        //     spells[spellname]->launch( target );
        ASpell * spell = book.createSpell( spellname );
        if (spell)
            spell->launch( target );
    }
/*
* learnSpell, takes a pointer to ASpell, that makes the Warlock learn a spell
* forgetSpell, takes a string corresponding a to a spell's name, and makes the
  Warlock forget it. If it's not a known spell, does nothing.
* launchSpell, takes a string (a spell name) and a reference to ATarget, that
  launches the spell on the selected target. If it's not a known spell, does
  nothing.
*/
    W (const string & n, const string & t): _name(n), _title(t) {
        cout << _name << ": This looks like another boring day.\n";
    }
    ~ W () {
        // map<string, ASpell *>::iterator it = spells.begin();
        // while (it != spells.end()) {
        //     delete it->second;
        //     ++it;
        // }
        // spells.clear();
        cout << _name << ": My job here is done!\n";
    }
    const string & getName () const { return _name ; }
    const string & getTitle () const { return _title ; }
    void introduce () const {
        cout << _name << ": I am " << _name << ", " << _title << "!\n";
    }
    void setTitle (const string & tt) {
        _title = tt;
    }
};
