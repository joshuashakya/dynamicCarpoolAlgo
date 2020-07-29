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
    Position(){

    }
    Position(string n,string t1,string t2){
        name=n;
        time_at_least=t1;
        time_at_most=t2;
    }
    void intialize_pos(string n,string t1,string t2){
        name=n;
        time_at_least=t1;
        time_at_most=t2;
    }
    void print_pos(){
        cout<<"the position is: "+name+" "+time_at_least+" "+time_at_most;
    }

};


#endif //CARPOOL_POSITION_H
