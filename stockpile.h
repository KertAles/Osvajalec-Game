#ifndef STOCKPILE_H
#define STOCKPILE_H

class Stockpile
{
    int food;
    int wood;
    int iron;
    int gold;
public:
    Stockpile();

    int getFood();
    int getWood();
    int getIron();
    int getGold();

    void setFood(int val);
    void setWood(int val);
    void setIron(int val);
    void setGold(int val);

/*signals:

public slots:*/
};

#endif // STOCKPILE_H
