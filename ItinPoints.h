//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINPOINTS_H
#define CARPOOL_ITINPOINTS_H
#include <iostream>

using namespace  std;
class ItinPoints {
    string location;
    string time_at_least;
    string time_at_most;
    int av_seats;
    int pu;
    int del;
    int req_no;
    ItinPoints();
    void set_new_point(string l, string tat,string tam,int as, int pickup,int deliv, int r_no){
        location=l;
        time_at_least=tat;
        time_at_most=tam;
        av_seats=as;
        pu=pickup;
        del=deliv;
        req_no=r_no;
    }


};


#endif //CARPOOL_ITINPOINTS_H
