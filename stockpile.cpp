#include "stockpile.h"

Stockpile::Stockpile() {
    food = 0;
    wood = 0;
    iron = 0;
    gold = 0;
}

int Stockpile::getFood()
{ return food; }

int Stockpile::getWood()
{ return wood; }

int Stockpile::getIron()
{ return iron; }

int Stockpile::getGold()
{ return gold; }

void Stockpile::setFood(int val) {
  food += val;
  if(food > 100)
     food = 100;
}

void Stockpile::setWood(int val) {
    wood += val;
    if(wood > 100)
       wood = 100;
}

void Stockpile::setIron(int val) {
    iron += val;
    if(iron > 100)
       iron = 100;
}

void Stockpile::setGold(int val) {
    gold += val;
    if(gold > 100)
       gold = 100;
}
