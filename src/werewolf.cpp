#include "../include/werewolf.h"

Werewolf::Werewolf(int x, int y, const std::string& name) 
    : NPC(WerewolfType, x, y, name) {}

void Werewolf::print() {
    std::cout << "Werewolf: " << name << " {" << x << ", " << y << "}" << std::endl;
}

void Werewolf::save(std::ostream& os) {
    os << "Werewolf ";
    NPC::save(os);
}

void Werewolf::accept(Visitor& v) {
    v.visit(*this);
}