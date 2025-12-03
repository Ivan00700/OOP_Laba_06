#include "../include/willian.h"

Willian::Willian(int x, int y, const std::string& name) 
    : NPC(WillianType, x, y, name) {}

void Willian::print() {
    std::cout << "Willian: " << name << " {" << x << ", " << y << "}" << std::endl;
}

void Willian::save(std::ostream& os) {
    os << "Willian ";
    NPC::save(os);
}

void Willian::accept(Visitor& v) {
    v.visit(*this);
}