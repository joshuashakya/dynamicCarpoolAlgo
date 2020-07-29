//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINPOINTS_H
#define CARPOOL_ITINPOINTS_H
#include <iostream>
#include "Position.h"

using namespace  std;
class ItinPoints {
    Position pos;
    int av_seats;
    int req_no;
    ItinPoints();
    void set_new_point(Position p,int as, int pickup,int deliv, int r_no){
        pos=p;
        av_seats=as;
        req_no=r_no;
    }


};


#endif //CARPOOL_ITINPOINTS_H
