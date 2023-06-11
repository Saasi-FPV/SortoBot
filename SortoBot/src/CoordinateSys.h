#ifndef COORDINATESYS_H
#define COORDINATESYS_H

#include "Arduino.h"


class CoordinateSys{

  private:
    float xOrigAbs;
    float yOrigAbs;
    float zOrigAbs;
    

    float xAxAbs;
    float cAxAbs;
    float zAxAbs;


  public:

    CoordinateSys(){
      xOrigAbs = 0;
      yOrigAbs = 0;
      zOrigAbs = 0;
      
      xAxAbs = 0;
      cAxAbs = 0;
      zAxAbs = 0;
    }

    float getAxAbs(char in);
    float getOrigAbs (char in);

    void addAxAbs(float in);



};







#endif