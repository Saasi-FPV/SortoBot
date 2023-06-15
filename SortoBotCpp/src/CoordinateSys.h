#ifndef COORDINATESYS_H
#define COORDINATESYS_H

#include "Arduino.h"


class CoordinateSys{

  private:
    char selectedAx;

    int prevEncoderPos;

    int xAxAbs;
    int cAxAbs;
    int zAxAbs;




  public:

    CoordinateSys(){
      selectedAx = 'n'; //no ax = n

      prevEncoderPos = 0;
      
      xAxAbs = 0;
      cAxAbs = 0;
      zAxAbs = 0;
    }

    void selectAx(char in);
    void update(int in);
    int getAxAbs(char in);
    int getOrigAbs (char in);
    void addAxAbs(int in);
    void setAxAbs(int in);

};







#endif