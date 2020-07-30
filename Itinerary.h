//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINERARY_H
#define CARPOOL_ITINERARY_H


#include <vector>
#include "ItinPoints.h"
#include "Request.h"

class Itinerary {
public:
    std::vector<ItinPoints> itinpts;
    int satisfied_requests;

    Itinerary(){

    }
    Itinerary(Itinerary const &it_copy){
        for(int i=0;i<it_copy.itinpts.size();i++){
            itinpts.push_back(it_copy.itinpts[i]);
        }
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
    bool satisfies(Request r){

    }


};


#endif //CARPOOL_ITINERARY_H
