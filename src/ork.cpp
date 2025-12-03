#include "../include/ork.h"

Ork::Ork(int x, int y, const std::string& name) 
    : NPC(OrkType, x, y, name) {}

void Ork::print() {
    std::cout << "Ork: " << name << " {" << x << ", " << y << "}" << std::endl;
}

void Ork::save(std::ostream& os) {
    os << "Ork ";
    NPC::save(os);
}

void Ork::accept(Visitor& v) {
    v.visit(*this);
}