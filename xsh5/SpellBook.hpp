#pragma once
#include "ASpell.hpp"
#include "map"
#define SB SpellBook 

using namespace std;

class SB {

SB (const SB & s) { (void) s; }
SB & operator = (const SB & s) {
  (void) s;
  return *this;
}
map<string, ASpell *> spells;

public:

  SB () {}
  ~ SB () {}

  void learnSpell(ASpell * spell) {
    if (spell)
      spells[spell->getName()] = spell->clone();
  }

  void forgetSpell(const string & spellname) {
    if (spells[spellname])
      delete spells[spellname];
    spells.erase( spellname );
  }

  ASpell* createSpell(const string & spellname) {
    if (spells[spellname])
      return spells[spellname];
    return NULL;
  }
/*
* void learnSpell(ASpell*), that COPIES a spell in the book
* void forgetSpell(const string &), that deletes a spell from the book, except
  if it isn't there
* ASpell* createSpell(const string &), that receives a string corresponding to
  the name of a spell, creates it, and returns it.
*/
};