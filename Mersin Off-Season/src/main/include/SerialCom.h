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
      //std::cout<<distleft<<"sag= "<<distright<<std::endl;
      /*
               /___| ultrasonik sol
             /_ ___|
            /_  ___|  45 cm             
          / _ _ ___|   
        / _ _ _ ___|  ultrasonik sag
        sağ-sol cm

        x= (sağ-sol) karşı 
        (45 cm)   komşu

        x/45 = tan(açımız)
        atan2(x/45) = AÇIMIZ
      */
      aci = atan2(distright-distleft,45); //! takıldıktan sonra tekrar ölçülecek
    }
}