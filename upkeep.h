#ifndef UPKEEP_H
#define UPKEEP_H

class Upkeep
{
    char resource;
    int amount;
public:
    Upkeep();
    char getResource() { return resource; }
    int getAmount() { return amount; }
    void setResource(char res) { resource = res; }
    void setAmount(int am) { amount = am; }
};

#endif // UPKEEP_H
