#include "CoordinateSys.h"


void CoordinateSys::selectAx(char in){
  selectedAx = in;
}

void CoordinateSys::update(int in){
  prevEncoderPos = in;
}

int CoordinateSys::getAxAbs(char in){
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

int CoordinateSys::getOrigAbs(char in){
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
      xAxAbs = xAxAbs + (in - prevEncoderPos);
    break;

    case 'c':
      cAxAbs = cAxAbs + (in - prevEncoderPos);
    break;

    case 'z':
      zAxAbs = zAxAbs + (in - prevEncoderPos);
    break;
  }
}

void CoordinateSys::setAxAbs(int in){
  switch(selectedAx){
    case 'x':
      xAxAbs = in;
    break;

    case 'c':
      cAxAbs = in;
    break;

    case 'z':
      zAxAbs = in;
    break;
  }
}




