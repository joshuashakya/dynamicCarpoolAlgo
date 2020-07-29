//
// Created by user on 29/07/2020.
//

#include <iostream>
#ifndef CARPOOL_POSITION_H
#define CARPOOL_POSITION_H

using namespace std;
class Position {
public:
    string name;
    string time_at_least;
    string time_at_most;
    int pickup;
    int delivery;
    Position(){

    }
    Position(string n,string t1,string t2,int pu,int del){
        name=n;
        time_at_least=t1;
        time_at_most=t2;
        pickup=pu;
        delivery=del;
    }
    void intialize_pos(string n,string t1,string t2,int pu,int del){
        name=n;
        time_at_least=t1;
        time_at_most=t2;
        pickup=pu;
        delivery=del;
    }
    void print_pos(){
        cout<<"the position is: "+name+" "+time_at_least+" "+time_at_most+" "+to_string(pickup)+" "+to_string(delivery);
    }
    string get_position_name(){
        return name;
    }

};


#endif //CARPOOL_POSITION_H
