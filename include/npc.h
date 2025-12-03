#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "visitor.h"
#include "observer.h"

struct NPC;

// Типы NPC для упрощения фабрики
enum NpcType {
    Unknown = 0,
    OrkType = 1,
    WillianType = 2,
    WerewolfType = 3
};

struct NPC : public std::enable_shared_from_this<NPC> {
    NpcType type;
    int x{0};
    int y{0};
    std::string name;
    std::vector<std::shared_ptr<Observer>> observers;

    NPC(NpcType t, int _x, int _y, const std::string& _name);
    virtual ~NPC() = default;

    // Паттерн Visitor
    virtual void accept(Visitor& v) = 0;

    // Поддержка Observer
    void attach(std::shared_ptr<Observer> observer);
    void notify(const std::string& message, bool is_kill_event = false);

    // Общие методы
    virtual void print() = 0;
    virtual void save(std::ostream& os);
    
    // Проверка расстояния
    bool is_close(const std::shared_ptr<NPC>& other, size_t distance);
    
    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
};