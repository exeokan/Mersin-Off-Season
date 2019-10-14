#include "Robot.h"
#include <math.h>
#include <iostream>


void Robot::updateSerialData()
{
  for(int i = 0; i < 12; i++)//Arduinodan veri alma
  {
    serial.Read(&buffer[i],serial.GetBytesReceived()); 
  } 
  std::string dist{buffer},left,right;
  if(isdigit(dist[0]) ==  1)
  {
    left = dist.substr(0, 5);//string'i sol ve sag stringlere aktarma
    right= dist.substr(5, 5);
    distleft= std::stod(left)-14;//stringleri double'a çevirme
    distright=std::stod(right)-14;
    /*
              /___| ultrasonik sol
            /_ ___|
          /_  ___|  44 cm             
        / _ _ ___|   
      / _ _ _ ___|  ultrasonik sag
      sağ-sol cm

      x= (sağ-sol) karşı 
      (44 cm)   komşu

      x/44 = tan(açımız)
      atan2(x/44) = AÇIMIZ
    */
    aci = atan2(distright-distleft,44); //! takıldıktan sonra tekrar ölçülecek
  }
}