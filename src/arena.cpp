#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/combat_visitor.h"
#include <iostream>
#include <algorithm>
#include <fstream>

void Arena::add_npc(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}

void Arena::save(const std::string& filename) {
    std::ofstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Error: Could not open file for saving" << std::endl;
        return;
    }
    fs << npcs.size() << std::endl;
    for (auto& npc : npcs) {
        npc->save(fs);
    }
}

void Arena::load(const std::string& filename, std::shared_ptr<Observer> file_obs, std::shared_ptr<Observer> console_obs) {
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Error: Could not open file for loading" << std::endl;
        return;
    }
    
    // Очищаем текущую арену перед загрузкой
    npcs.clear();
    
    int count;
    if (fs >> count) {
        for (int i = 0; i < count; ++i) {
            auto npc = Factory::CreateNPC(fs);
            if (npc) {
                npc->attach(file_obs);
                npc->attach(console_obs);
                add_npc(npc);
            }
        }
    }
}

void Arena::print() {
    std::cout << "--- Arena Objects ---" << std::endl;
    for (auto& npc : npcs) {
        npc->print();
    }
}

void Arena::fight(int distance) {
    std::vector<std::shared_ptr<NPC>> dead_list;

    for (const auto& attacker : npcs) {
        for (const auto& defender : npcs) {
            if (attacker == defender) continue;
            
            if (attacker->is_close(defender, distance)) {
                // Создаем посетителя который защищает defender
                CombatVisitor v(defender);
                // attacker принимает посетителя
                attacker->accept(v);

                if (v.is_success()) {
                    // Атака успешна
                    defender->notify(attacker->name + " killed " + defender->name, true);
                    dead_list.push_back(defender);
                }
            }
        }
    }

    // Удаляем убитых
    if (dead_list.empty()) {
        std::cout << "No one died in this round." << std::endl;
    } else {
        // Удаляем дубликаты из списка мертвых
        std::sort(dead_list.begin(), dead_list.end());
        dead_list.erase(std::unique(dead_list.begin(), dead_list.end()), dead_list.end());

        for (auto& dead : dead_list) {
            npcs.erase(
                std::remove(npcs.begin(), npcs.end(), dead), 
                npcs.end()
            );
        }
        std::cout << "Battle ended. These Legends survived: " << npcs.size() << std::endl;
    }
}