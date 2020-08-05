//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINERARY_H
#define CARPOOL_ITINERARY_H


#include <vector>

#include "ItinPoints.h"
#include "Request.h"
#include "ODMatrix.h"

//using namespace std;

class Itinerary {
private:
    static int newUID;
    const int uid;
public:
    std::vector<ItinPoints> itinpts;
    int satisfied_requests;
    vector<int> requests_satisfied;

    Itinerary():uid(newUID++){

    }


//    Itinerary(Itinerary const &it_copy){
//
//        for(int i=0;i<it_copy.itinpts.size();i++){
//            itinpts.push_back(it_copy.itinpts[i]);
//        }
//    }
    void addPoint(ItinPoints ip){
        itinpts.push_back(ip);
    }
    void print_itin(){
        for(int i=0;i<itinpts.size();i++){
            itinpts[i].print_itpts();
        }
//        cout<<"id is "<<itineraryId<<endl;

    }
//    void setItineraryNumber(int no){
//        itinerary_no=no;
//    }

    float getTime(string stime){
        string h = stime.substr(0, stime.find(":"));
        stime.erase(0,  h.length()+1);
        string m = stime;
        float time = stof(h) * 60 + stof(m);

        return time;
    }

    int getID(){
        return uid;
    }

    bool satisfies(Request r, ODMatrix od){

        bool checked = false;
        map<string, int> dict = od.getDict();
        vector<vector<array <float, 2>>> matrix = od.getOD();

        int sP = dict.at(r.start.name);

        int dP = dict.at(r.dest.name);

        int itinSP = dict.at(itinpts.front().pos.name);

        int itinDP = dict.at(itinpts.back().pos.name);

        if(sP >= itinSP && dP <= itinDP){

            float itinST = getTime(itinpts.front().pos.time_at_least);
            float itinDT = getTime(itinpts.back().pos.time_at_least);
            float timeST = getTime(r.start.time_at_least);
            float timeDT = getTime(r.dest.time_at_least);

            if(timeST >= itinST && timeDT <= itinDT)
                return true;
        }

        return false;

    }

//    bool combine(Request r,ODMatrix od){
//        int total_passenger=0;
//        map<string, int> dict = od.getDict();
//        vector<vector<array <float, 2>>> matrix = od.getOD();
//        for(int i=0;i<this->itinpts.size();i++){
//            if(dict.at(this->itinpts[i].pos.name)<dict.at(r.start.name)) {
//                total_passenger = total_passenger + (this->itinpts[i].pos.pickup) + (this->itinpts[i].pos.delivery);
//            }
//        }
//        cout<<"Total passenger is"+total_passenger;
//
//    }
    void showSatisfiedRequests(){
        for(int i:requests_satisfied){
            cout<<"satisfied requests"<<i<<",";
        }
    }

<<<<<<< HEAD
    bool can_combine(Itinerary it,vector<Request> request_demand_list,ODMatrix od){
        map<string, int> dict = od.getDict();
        vector<vector<array <float, 2>>> matrix = od.getOD();

=======
    string converMinToTime(float timeInMin){
        int hr = (int) timeInMin/60;
        int min = (int) timeInMin%60;
        string time = to_string(hr)+":"+to_string(min);

        return time;
    }

    void validateTimeWindow(map<string, int> dict, ODMatrix od) {
        vector<vector<array <float ,2>>> matrix = od.getOD();

        for(int i=0; i<itinpts.size(); i++){
            if(i+1 <  itinpts.size()){
                int i0 = dict.at(itinpts[i].pos.name);
                int j0 = dict.at(itinpts[i+1].pos.name);

                string t0min = itinpts[i].pos.time_at_least;
                string t0max = itinpts[i].pos.time_at_most;
                string t1min = itinpts[i+1].pos.time_at_least;
                string t1max = itinpts[i+1].pos.time_at_most;

                float p0min = getTime(t0min);
                float p0max = getTime(t0max);
                float p1min = getTime(t1min);
                float p1max = getTime(t1max);


                if((p0max + matrix[i0][j0].at(0)) >= p1max){
                    p0max = p1max - matrix[i0][j0].at(0);
                    itinpts[i].pos.time_at_most = converMinToTime(p0max);
                }

                if((p0min + matrix[i0][j0].at(0)) >= p1min){
                    p1min = p0min + matrix[i0][j0].at(0);
                    itinpts[i+1].pos.time_at_least = converMinToTime(p1min);

                    p0max = p1max - matrix[i0][j0].at(0);
                    itinpts[i].pos.time_at_most = converMinToTime(p0max);
                }
                else if((p0max + matrix[i0][i0].at(0)) <= p0max){
                    p0max = p0max - matrix[i0][i0].at(0);
                    itinpts[i].pos.time_at_most = converMinToTime(p0max);

                    p0min = p0min + matrix[i0][i0].at(0);
                    itinpts[i].pos.time_at_least = converMinToTime(p0min);
                }

            }
        }
    }

    bool combine(Itinerary it,vector<Request> request_demand_list){
>>>>>>> df46aeed0bb0ab357ab6c58e560d3507810b0392
        bool can_change_veh=false;
        for(Request k:request_demand_list){
//            cout<<"value of k here "<<k.request_no<<endl;

            for(int request_id: requests_satisfied){
//                cout<<"value of req satisfied here "<<request_id<<endl;
                if(k.request_no==request_id){
//                    cout<<"match bho "<<endl;
                    if(k.modality_report==">1"){
                        can_change_veh=true;
                        cout<<"true"<<endl;
                    }
                    else{
                        cout<<"false"<<endl;
                        can_change_veh=false;
                        goto label;
                    }
                }
            }

        }
        label:

        for(int request_id: requests_satisfied){
            for(int request_id2:it.requests_satisfied){
                if(request_id==request_id2){
                    can_change_veh=false;
                }
            }
        }

        if(can_change_veh==true){
            vector<ItinPoints> testIt;
            Position previous;
            int count_of_people;
            for(int i=0;i<it.itinpts.size();i++){
                for(int j=0;j<itinpts.size();j++){
                    if(dict.at(it.itinpts[i].pos.name)<dict.at(itinpts[j].pos.name)){

                        cout<<previous.name;
                        cout<<"Number of people"<<count_of_people;
//                        if(previous.name!=(it.itinpts[i].pos.name)) {
                            if (getTime(previous.time_at_least) < getTime(it.itinpts[i].pos.time_at_least) &&
                                getTime(previous.time_at_most) < getTime(it.itinpts[i].pos.time_at_most) &&
                                getTime(it.itinpts[i].pos.time_at_least) <getTime(itinpts[j].pos.time_at_least) &&
                                getTime(it.itinpts[i].pos.time_at_most) < getTime(itinpts[j].pos.time_at_most)&& count_of_people<it.itinpts[i].av_seats) {
                                can_change_veh = true;
                            } else {
                                can_change_veh = false;

                            }
//                        }

                    }else{
                         previous=itinpts[j].pos;
                    }

                    count_of_people=count_of_people+itinpts[j].pos.pickup+itinpts[j].pos.delivery;
                }

            }
        }
        cout<<"This req modality report is:"<<can_change_veh<<endl;

        return can_change_veh;

    }

    Itinerary combine(Itinerary i1,Itinerary i2){

        Itinerary new_itinerary;
        for(int i=0;i<i1.itinpts.size();i++){
            new_itinerary.itinpts.push_back(i1.itinpts[i]);

        }
        for(int i=0;i<i1.itinpts.size();i++){
            new_itinerary.itinpts.push_back(i1.itinpts[i]);

        }

    }


};


#endif //CARPOOL_ITINERARY_H
