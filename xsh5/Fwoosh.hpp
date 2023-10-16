#include "ASpell.hpp"
class Fwoosh : public ASpell {
public:
  Fwoosh () : ASpell("Fwoosh", "fwooshed") {}
  ~ Fwoosh () {}
  virtual Fwoosh * clone () const { return new Fwoosh (); }
};

class Fireball : public ASpell {
public:
  Fireball () : ASpell("Fireball", "burnt to a crisp") {}
  ~ Fireball () {}
  virtual Fireball * clone () const { return new Fireball (); }
};

class Polymorph : public ASpell {
public:
  Polymorph () : ASpell("Polymorph", "turned into a critter") {}
  ~ Polymorph () {}
  virtual Polymorph * clone () const { return new Polymorph (); }
};
