#include "CoordinateSys.h"


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

  void CoordinateSys::addAxAbs(float in){
    
  }




