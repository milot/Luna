#include <string>
#include <iostream>
#include "Luna.h"

int main(void)
{
    Luna::Script *script = new Luna::Script("player.lua");
    int posX = script->getInteger("player.pos.x");
    std::cout << "X: " << posX;

}
