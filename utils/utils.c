#include "utils.h"

int fixAngle(int a){
    if(a>359){
        a-=360;
    }
    if(a<0){
        a+=360;
    }
    return a;
}

float degToRad(int a)
{
    return a * M_PI / 180;
}