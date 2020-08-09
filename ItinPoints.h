//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINPOINTS_H
#define CARPOOL_ITINPOINTS_H
#include <iostream>
#include <sstream>
#include "Position.h"

using namespace  std;
class ItinPoints {
public:
    Position pos;
    int av_seats;
    int req_no;
    ItinPoints(){

    }
    ItinPoints(Position p,int as, int r_no){
        pos=p;
        av_seats=as;
        req_no=r_no;
    }
    void set_new_point(Position p,int as, int r_no){
        pos=p;
        av_seats=as;
        req_no=r_no;
    }
    void print_itpts(){
        pos.print_pos();
        cout<<","+to_string(av_seats)+","+to_string(req_no);
    }
    Position get_position(){
        return pos;
    }


};


#endif //CARPOOL_ITINPOINTS_H
