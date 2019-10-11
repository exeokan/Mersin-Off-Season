#include "Robot.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265358979323846

void Robot::updateSerialData()
{
for(int i = 0; i < 12; i++)
    {
      serial.Read(&buffer[i],serial.GetBytesReceived()); 
    } 
    std::string dist{buffer},left,right;
    if(isdigit(dist[0]) ==  1)
    {
      left = dist.substr(0, 5);
      right= dist.substr(5, 5);
      distleft= std::stod(left);
      distright=std::stod(right);
      /*
               /___| ultrasonik sol
             /_ ___|
            /_  ___|  26 cm             
          / _ _ ___|   
        / _ _ _ ___|  ultrasonik sag
        sağ-sol cm

        x= (sağ-sol) karşı 
        (26 cm)   komşu

        x/26 = tan(açımız)
        atan2(x/26) = AÇIMIZ
      */
      aci = atan2(distright-distleft,26); //! 26 SANTIM DEĞİL DEĞİŞECEK!!!!!!!!!!!!!!1 >:c
    }
}