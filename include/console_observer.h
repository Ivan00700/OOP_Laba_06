#pragma once
#include "observer.h"
#include <iostream>

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "[Console Log]: " << message << std::endl;
    }
};