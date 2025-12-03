#include "../include/npc.h"
#include <cmath>

NPC::NPC(NpcType t, int _x, int _y, const std::string& _name) 
    : type(t), x(_x), y(_y), name(_name) {}

void NPC::attach(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NPC::notify(const std::string& message, bool is_kill_event) {
    for (auto& o : observers) {
        o->update(message);
    }
}

void NPC::save(std::ostream& os) {
    os << x << " " << y << " " << name << std::endl;
}

bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) {
    if (this == other.get()) return false;
    auto dist_sq = std::pow(x - other->x, 2) + std::pow(y - other->y, 2);
    return dist_sq <= std::pow(distance, 2);
}