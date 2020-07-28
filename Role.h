//
// Created by user on 27/07/2020.
//

#ifndef CARPOOL_ROLE_H
#define CARPOOL_ROLE_H

#include "Role.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

class Role {
public:
    string role_name;
    Role(){

    }
    Role(string r){
        role_name=r;
    }
    void print_role(){
        cout<<role_name;
    };
    void set_role(string r){
        role_name=r;

    }
};


#endif //CARPOOL_ROLE_H