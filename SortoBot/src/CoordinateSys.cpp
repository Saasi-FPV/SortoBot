#include "CoordinateSys.h"


  void CoordinateSys::selectAx(char in){
    selectedAx = in;
  }

  void CoordinateSys::update(int in){
    prevEncoderPos = in;
  }

  float CoordinateSys::getAxAbs(char in){
    switch(in){
      case 'x':
        return(xAxAbs);
      break;

      case 'c':
        return(cAxAbs);
      break;

      case 'z':
        return(zAxAbs);
      break;
    }
  }

  float CoordinateSys::getOrigAbs(char in){
    switch(in){
      case 'x':
        return(cos(cAxAbs)*xAxAbs);
      break;

      case 'y':
        return(sin(cAxAbs)*xAxAbs);
      break;

      case 'z':
        return(zAxAbs);
      break;
    }
  }

  void CoordinateSys::addAxAbs(int in){
    switch(selectedAx){
      case 'x':
        xAxAbs = prevEncoderPos - in;
      break;

      case 'c':
        cAxAbs = prevEncoderPos - in;
      break;

      case 'z':
        zAxAbs = prevEncoderPos - in;
      break;
    }
  }




