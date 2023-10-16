#include "ATarget.hpp"
void ATarget::getHitBySpell (const ASpell & s) const {
    cout << _type << " has been " << s.getEffects() << "!\n";
}
