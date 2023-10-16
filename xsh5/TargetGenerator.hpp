#pragma once
#include "ATarget.hpp"
#include "map"
#define TG TargetGenerator 

using namespace std;

class TG {

TG (const TG & s) { (void) s; }
TG & operator = (const TG & s) {
  (void) s;
  return *this;
}
map<string, ATarget *> tars;

public:
  TG () {}
  ~ TG () {}
  void learnTargetType(ATarget* tar) {
    if (tar)
      tars[tar->getType()] = tar->clone();
  }
  void forgetTargetType(const string & tp) {
    if (tars[tp])
      delete tars[tp];
    tars.erase(tp);
  }
  ATarget* createTarget(const string & tp) {
    if (tars[tp])
      return tars[tp];
    return NULL ;
  }

/*
* void learnTargetType(ATarget*), teaches a target to the generator
* void forgetTargetType(const string &), that makes the generator forget a
  target type if it's known
* ATarget* createTarget(const string &), that creates a target of the
  specified type
*/
};
