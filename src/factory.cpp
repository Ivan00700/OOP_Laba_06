#include "../include/factory.h"
#include "../include/ork.h"
#include "../include/willian.h"
#include "../include/werewolf.h"
#include <fstream>

std::shared_ptr<NPC> Factory::CreateNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::runtime_error("Coordinates out of range (0-500)");
    }
    
    if (type == "Ork" || type == "ork") return std::make_shared<Ork>(x, y, name);
    if (type == "Willian" || type == "willian") return std::make_shared<Willian>(x, y, name);
    if (type == "Werewolf" || type == "werewolf") return std::make_shared<Werewolf>(x, y, name);
    
    throw std::runtime_error("Unknown NPC type");
}

std::shared_ptr<NPC> Factory::CreateNPC(std::istream& is) {
    std::string type, name;
    int x, y;
    if (is >> type >> x >> y >> name) {
        return CreateNPC(type, name, x, y);
    }
    return nullptr;
}