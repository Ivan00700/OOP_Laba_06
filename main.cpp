#include <iostream>
#include <memory>
#include "include/arena.h"
#include "include/factory.h"
#include "include/file_observer.h"
#include "include/console_observer.h"

int main() {
    Arena arena;
    
    // Создаем наблюдателей один раз
    auto file_obs = std::make_shared<FileObserver>("log.txt");
    auto console_obs = std::make_shared<ConsoleObserver>();

    std::cout << "Balagur Fate 3 - Dungeon Editor" << std::endl;
    std::cout << "Commands: add, save, load, list, fight, exit" << std::endl;

    while (true) {
        std::string cmd;
        std::cout << "> ";
        std::cin >> cmd;

        if (cmd == "exit") break;

        if (cmd == "add") {
            try {
                std::string type, name;
                int x, y;
                std::cout << "Type (Ork, Willian, Werewolf): "; std::cin >> type;
                std::cout << "X (0-500): "; std::cin >> x;
                std::cout << "Y (0-500): "; std::cin >> y;
                std::cout << "Name: "; std::cin >> name;
                
                auto npc = Factory::CreateNPC(type, name, x, y);
                npc->attach(file_obs);
                npc->attach(console_obs);
                
                arena.add_npc(npc);
                std::cout << "Added successfully." << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        } 
        else if (cmd == "save") {
            std::string filename;
            std::cout << "Filename: "; std::cin >> filename;
            arena.save(filename);
            std::cout << "Saved." << std::endl;
        } 
        else if (cmd == "load") {
            std::string filename;
            std::cout << "Filename: "; std::cin >> filename;
            arena.load(filename, file_obs, console_obs);
            std::cout << "Loaded." << std::endl;
        } 
        else if (cmd == "list") {
            arena.print();
        } 
        else if (cmd == "fight") {
            int dist;
            std::cout << "Fight distance: "; std::cin >> dist;
            arena.fight(dist);
        }
        else {
            std::cout << "Unknown command." << std::endl;
        }
    }
    return 0;
}