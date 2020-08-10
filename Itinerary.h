//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINERARY_H
#define CARPOOL_ITINERARY_H


#include <vector>
#include <algorithm>

#include "ItinPoints.h"
#include "Request.h"
#include "ODMatrix.h"

//using namespace std;

class Itinerary {
private:
    static int newUID;
//    const int uid;
public:
    std::vector<ItinPoints> itinpts;
    int satisfied_requests;
    vector<int> requests_satisfied;
    vector<ItinPoints> returnTrip;

    Itinerary(){

    }

    

 Itinerary(Itinerary const &it2)  {
        for(int i=0;i<it2.itinpts.size();i++){
            itinpts.push_back(it2.itinpts[i]);
        }

        for(int i=0; i<it2.returnTrip.size();i++){
            returnTrip.push_back(it2.returnTrip[i]);
        }

        for(int i=0;i<it2.requests_satisfied.size();i++){
            requests_satisfied.push_back(it2.requests_satisfied[i]);
        }

    }
    bool operator>(const Itinerary r) const
    {
//        if (requests_satisfied.size() != r.requests_satisfied.size())
            return requests_satisfied.size() >= r.requests_satisfied.size();

//        return requests_satisfied.size() > r.requests_satisfied.size();
    }

//    bool operator==(const Itinerary& r) const
//    {
//        if (requests_satisfied.size() != r.requests_satisfied.size())
//            return requests_satisfied.size() > r.requests_satisfied.size();
//
//        return requests_satisfied.size() > r.requests_satisfied.size();
//    }


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
        cout<<endl;
//        cout<<"Return trip size is ->"<<returnTrip.size()<<endl;
        if(returnTrip.size()!=0){
            cout<<"Return trip->";
            for(int i=0;i<returnTrip.size();i++){
                returnTrip[i].print_itpts();
            }
            cout<<endl;
        }

//        cout<<"id is "<<itineraryId<<endl;

    }
    bool operator< (const Itinerary &other) const {
        return requests_satisfied.size() < other.requests_satisfied.size();
    }
//    void setItineraryNumber(int no){
//        itinerary_no=no;
//    }

     int getRequestsSatisfied(){
        int i=requests_satisfied.size();
        return i;
    }
    float getTime(string stime){
        string h = stime.substr(0, stime.find(":"));
        stime.erase(0,  h.length()+1);
        string m = stime;
        float time = stof(h) * 60 + stof(m);

        return time;
    }

//    int getID(){
//        return uid;
//    }

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



    string converMinToTime(float timeInMin){
        int hr = (int) timeInMin/60;
        int min = (int) timeInMin%60;
        string hour = to_string(hr);
        string minute = to_string(min);
        if(minute.length() == 1)
            minute = "0"+minute;
        string time = hour+":"+minute;

        return time;
    }

    void validateTimeWindow2(map<string, int> dict, ODMatrix od) {
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

    void validateTimeWindow(map<string, int> dict, ODMatrix od){
        vector<vector<array <float ,2>>> matrix = od.getOD();

        for(int i=0; i<itinpts.size(); i++){
            if(i+1 < itinpts.size()){
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

                float min = p1min - p0min;
                float max = p1max - p0max;

                if(min < matrix[i0][j0].at(0)){
                    p1min = p0min + matrix[i0][j0].at(0);
                    itinpts[i+1].pos.time_at_least = converMinToTime(p1min);
                }

                if(max < matrix[i0][j0].at(0)){
                    p1max = p0max + matrix[i0][j0].at(0);
                    itinpts[i+1].pos.time_at_most = converMinToTime(p1max);
                }

            }
        }
    }

    bool can_combine(Itinerary it,vector<Request> request_demand_list,ODMatrix od){
        map<string, int> dict = od.getDict();
        vector<vector<array <float, 2>>> matrix = od.getOD();

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
            int count_of_people=0;
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
//        cout<<"This req modality report is:"<<can_change_veh<<endl;

        return can_change_veh;

    }
    vector<ItinPoints> sortAscending(vector<ItinPoints> itin,  map<string, int> dict){
        sort( itin.begin( ), itin.end( ), [dict]( auto& lhs, auto& rhs )
        {
            return  dict.at(lhs.pos.name)< dict.at(rhs.pos.name);
        });

        return itin;
    }

     Itinerary combine(Itinerary i1,Itinerary i2,ODMatrix od){
         map<string, int> dict = od.getDict();
         vector<vector<array <float, 2>>> matrix = od.getOD();

//        cout<<"i2 size is "<<i2.itinpts.size();
        vector<ItinPoints> vecPoints;

        Itinerary new_itinerary;
        for(int i=0;i<i1.itinpts.size();i++){
            vecPoints.push_back(i1.itinpts[i]);

        }
        for(int i=0;i<i2.itinpts.size();i++){
            vecPoints.push_back(i2.itinpts[i]);

        }
        vecPoints=sortAscending(vecPoints,dict);
        for(int i=0;i<vecPoints.size();i++){
            new_itinerary.addPoint(vecPoints[i]);
        }

        return new_itinerary;


    }
    Request getRequestFromId(int id, vector<Request> request_demand_list){
        for(Request r:request_demand_list){
            if(r.request_no==id){
                return r;
            }
        }

    }

    bool ret_trip_poss(Itinerary it,vector<Request> request_demand_validated,ODMatrix od){
        map<string, int> dict = od.getDict();
        vector<vector<array <float, 2>>> matrix = od.getOD();
    bool return_trip=false;
        int total_person=0;
        Position st_pos;
        Position dest_pos;
    for(int i:requests_satisfied){
        total_person=0;
        if(getRequestFromId(i,request_demand_validated).return_trip==true){
            return_trip=true;
            st_pos=(getRequestFromId(i,request_demand_validated)).dest;
            dest_pos=(getRequestFromId(i,request_demand_validated)).start;



        }
    }
    if (return_trip==true){
        cout<<"Pritinging"<<endl;

        cout<<st_pos.name;
        cout<<it.itinpts[0].pos.name;
        cout<<endl;

        cout<<dest_pos.name<<endl;
        cout<<it.itinpts[it.itinpts.size()-1].pos.name<<endl;

        if(dict.at(st_pos.name)<=dict.at(it.itinpts[0].pos.name) && dict.at(dest_pos.name)>=dict.at(it.itinpts[it.itinpts.size()-1].pos.name)){

            return_trip=true;
        }
        else{
            return_trip=false;
        }

    }


    cout<<"The return trip is "<<return_trip<<endl;

    return return_trip;


    }
    void addToReturnTrip(vector<ItinPoints> itpts){
        for(int i=0;i<itpts.size();i++){
//            cout<<"added to return trip"<<endl;
            returnTrip.push_back(itpts[i]);
        }
    }

    int getReturnSize(){
        return returnTrip.size();
    }

    Itinerary createReturnTrip(Itinerary it, vector<Request> request_demand_validated){
        Itinerary new_it(*this);
        Position st_pos;
        Position dest_pos;
        for(int i:requests_satisfied){
            if(getRequestFromId(i,request_demand_validated).return_trip==true){
                st_pos=(getRequestFromId(i,request_demand_validated)).dest;
                dest_pos=(getRequestFromId(i,request_demand_validated)).start;

            }
        }

//        new_it.addToReturnTrip(it.itinpts);

        for(int i=0;i<it.itinpts.size();i++){
//            cout<<"added to return trip"<<endl;
            new_it.returnTrip.push_back(it.itinpts[i]);
        }


        bool start_pos_bool=false;
        bool dest_pos_bool=false;
        for(int i=0;i<new_it.returnTrip.size();i++){
            if(new_it.returnTrip[i].pos.name==dest_pos.name){
                dest_pos_bool=true;
            }
            if(new_it.returnTrip[i].pos.name==dest_pos.name){
                start_pos_bool=true;
            }

        }
        if(start_pos_bool!=true){
            new_it.returnTrip.push_back(ItinPoints(st_pos,0,0));
        }
        if(dest_pos_bool!=true){
            new_it.returnTrip.push_back(ItinPoints(dest_pos,0,0));
        }

        for(int i=0;i<requests_satisfied.size();i++){
            new_it.requests_satisfied.push_back(requests_satisfied[i]);
        }
        for(int i=0;i<it.requests_satisfied.size();i++){
            new_it.requests_satisfied.push_back(it.requests_satisfied[i]);
        }
        return new_it;
    }



};


#endif //CARPOOL_ITINERARY_H
