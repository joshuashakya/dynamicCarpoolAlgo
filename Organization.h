//
// Created by user on 26/07/2020.
//

#ifndef CARPOOL_ORGANIZATION_H
#define CARPOOL_ORGANIZATION_H
#include "Itinerary.h"

class Organization {

public:
    vector<Itinerary> itins;
    Organization(){

    }
    void create_itinerary(Itinerary i){
        itins.push_back(i);
    }
    bool is_empty(){

        if (itins.size()!=0){
            return true;
        }else{
            return false;
        }
    }


};


#endif //CARPOOL_ORGANIZATION_H
