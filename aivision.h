#ifndef AIVISION_H
#define AIVISION_H

#include "gridsquare.h"

class AIVision
{
    GridSquare* square;
    bool sqrVisible;

    Resource* resource;
    bool resVisible;

    //double dangerLevel;
public:
    AIVision(GridSquare* sqr);

   GridSquare* getSquare() { return square; }
   Resource* getResource() { return resource; }
   bool isSqrVisible() { return sqrVisible; }
   bool isResVisible() { return resVisible; }
   void setSqrVisible(bool visible) { sqrVisible = visible; if(visible) this->setResVisible(true); }
   void setResVisible(bool visible) { resVisible = visible; }
  /* double getDanger()  { return dangerLevel; }
   void setDanger(double danger) { dangerLevel = danger; }*/
};

#endif // AIVISION_H
