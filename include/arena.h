#pragma once
#include <vector>
#include <memory>
#include <string>
#include "npc.h"
#include "observer.h"

class Arena {
private:
    std::vector<std::shared_ptr<NPC>> npcs;

public:
    Arena() = default;
    
    // Добавление NPC
    void add_npc(std::shared_ptr<NPC> npc);
    
    void save(const std::string& filename);
    void load(const std::string& filename, std::shared_ptr<Observer> file_obs, std::shared_ptr<Observer> console_obs);
    
    void print();
    
    void fight(int distance);
};