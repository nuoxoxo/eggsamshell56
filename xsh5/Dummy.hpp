#include "ATarget.hpp"
class Dummy : public ATarget {
public:
  Dummy () : ATarget ("Target Practice Dummy") {}
  ~ Dummy () {}
  virtual Dummy * clone () const { return new Dummy (); }
};

class BrickWall : public ATarget {
public:
  BrickWall () : ATarget ("Inconspicuous Red-brick Wall") {}
  ~ BrickWall () {}
  virtual BrickWall * clone () const { return new BrickWall (); }
};
