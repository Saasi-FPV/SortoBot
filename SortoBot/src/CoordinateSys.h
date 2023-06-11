#ifndef COORDINATESYS_H
#define COORDINATESYS_H

#include "Arduino.h"


class CoordinateSys{

  private:
    char selectedAx;

    int prevEncoderPos;

    float xAxAbs;
    float cAxAbs;
    float zAxAbs;


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
    float getAxAbs(char in);
    float getOrigAbs (char in);
    void addAxAbs(int in);



};







#endif