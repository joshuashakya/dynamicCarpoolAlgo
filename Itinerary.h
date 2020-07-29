//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINERARY_H
#define CARPOOL_ITINERARY_H


#include <vector>
#include "ItinPoints.h"

class Itinerary {
public:
    std::vector<ItinPoints> itinpts;
    int satisfied_requests;

    Itinerary(){

    }
    void addPoint(ItinPoints ip){
        itinpts.push_back(ip);
    }
    void print_itin(){
        for(int i=0;i<itinpts.size();i++){
            itinpts[i].print_itpts();
        }
        cout<<endl;

    }


};


#endif //CARPOOL_ITINERARY_H
