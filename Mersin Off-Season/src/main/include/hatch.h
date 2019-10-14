#include "Robot.h"
#include <iostream>

int Robot::getHatchPosition()
{
  int pos=hatchEncoder.Get();
  return pos;
}

double Robot::hatchPID()
{
  int pos=getHatchPosition();//anlık pozisyon
  //* olması gereken aralık(0-150) dışında ise yavaşça aralığa geri alma
  if(pos>160){ 
    return -0.2;
  }
  if(pos<0)
  {
    return 0.2;
  }
  double error=hatchRef-pos; 
  double d=error-lastError;//D'nin error'ünü hesaplama
  lastError=error;
 
  //* değer aralığında değil ise I hesaplamaması için kod
  if(abs(error)<=8 && abs(error)!=0){ 
    hErrorI+=error;
  }
  else{
    hErrorI=0;
  }

  //* integral sınırı
  if(hErrorI > 50/hatchI){
    hErrorI = 50/hatchI;
  }
  else if(hErrorI < -50/hatchI){
    hErrorI = -50/hatchI;
  }
  return error*hatchP+ hErrorI*hatchI + d*hatchD ;//P,I,D toplamı
}