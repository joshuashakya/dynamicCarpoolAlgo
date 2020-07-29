//
// Created by user on 26/07/2020.
//

#ifndef CARPOOL_REQUEST_H
#define CARPOOL_REQUEST_H

#include "ODMatrix.h"

#include <sstream>
#include <vector>
#include <map>
#include <array>
#include "Role.h"
#include "Position.h"

using namespace std;


class Request {
public :
    string request;
    bool validated;
    Role r;
    Position start;
    Position dest;
    vector<Position> via;
    bool return_trip;
    vector<string> time_windows;
    bool start_as_driver;

    map<string, int> dict;
    Request(string request_string){
        request=request_string;
        validated = false;
        r.set_role("");
        start.intialize_pos("","","",0,0);
        dest.intialize_pos("","","",0,0);
        start_as_driver=false;

    }
    void printrequest(){
        cout<<request<<endl;
 }
 void findtw(){
        int x=0;
        int y=0;
     stringstream ss(request);
     string tws;
     while (ss.good()) {
         string substr;
         y++;
         getline(ss, substr, ',');
         if(substr.find(':') != std::string::npos){

          if(x==0){
              x=x+1;
              tws=substr;
          }else{
              tws=tws+","+substr;
              x=0;
              time_windows.push_back(tws);
              tws="";
          }
         }
     }

     cout<<"The size is"<<y<<endl;
     for (size_t i = 0; i < time_windows.size(); i++)
         cout << time_windows[i] << endl;



 }


 float getTime(string stime){
     string h = stime.substr(0, stime.find(":"));
     stime.erase(0,  h.length()+1);
     string m = stime;
     float time = stof(h) * 60 + stof(m);

     return time;
    }

void validateRequestTw(ODMatrix od){

        int x=0;
         int y=0;
         float p1min, p1max, p2min, p2max = 0;
         int mati, matj = 0;
         stringstream ss(request);
         string tws;
         vector<string> requestSub;
         vector<string> times;

         while (ss.good()) {
            string substr;
            y++;
            getline(ss, substr, ',');
             requestSub.push_back(substr);
            if(substr.find(':') != std::string::npos){
               times.push_back(substr);
                if(x==0){
                    x=x+1;
                    tws=substr;
                }else{
                    tws=tws+","+substr;
                    x=0;
                    time_windows.push_back(tws);
                    tws="";
                }
            }
         }
         start.intialize_pos(requestSub[1],requestSub[2],requestSub[3],stoi(requestSub[4]),stoi(requestSub[5]));
         start.print_pos();

         if(requestSub[requestSub.size()-1]=="1"){
             return_trip=true;
         }else{
             return_trip=false;
         }
         if(return_trip==false) {
             r.set_role(requestSub[requestSub.size() - 4]);
             if(requestSub[requestSub.size() - 3]=="1"){
                 start_as_driver=true;
             }
             dest.intialize_pos(requestSub[requestSub.size() - 9],requestSub[requestSub.size() - 8],requestSub[requestSub.size() - 7],stoi(requestSub[requestSub.size() - 6]),stoi((requestSub[requestSub.size() - 5])));
         }else{
             r.set_role(requestSub[requestSub.size()-8]);
             if(requestSub[requestSub.size() - 7]=="1"){
                 start_as_driver=true;
             }

             dest.intialize_pos(requestSub[requestSub.size() - 13],requestSub[requestSub.size() - 12],requestSub[requestSub.size() - 11],stoi(requestSub[requestSub.size() - 10]),stoi(requestSub[requestSub.size() - 9]));
         }
         dest.print_pos();
    cout<<"start as a driver isssssssss:"+to_string(start_as_driver);
         for(int i=6;i<requestSub.size()-9;i=i+5){
             if(requestSub[i]!=dest.get_position_name()){
                 via.push_back(Position(requestSub[i],requestSub[i+1],requestSub[i+2],stoi(requestSub[i+3]),stoi(requestSub[i+4])));
             }

         }
         for(int i=0;i<via.size();i++){
             via[i].print_pos();
         }
//         cout<<endl<<"role is:";
//         r.print_role();
//         cout<<endl;


        map<string, int> dict = od.getDict();
        vector<vector<array <float ,2>>> matrix = od.getOD();

//        cout <<"dict items are: "<<endl;
//        for (auto& t : dict)
//            std::cout << t.first << " "
//                      << t.second << "\n";

        for(int i=1; i<requestSub.size(); i+=5){
//            cout<<"curr string at "<<i<< " => "<< requestSub[i]<<endl;
            if(i+5 < requestSub.size()){
                if(dict.find(requestSub[i+5]) != dict.end()){
//                    cout<<requestSub[i+5]<< " found "<<endl;
                    mati = dict.at(requestSub[i]);
                    matj = dict.at(requestSub[i+5]);

                    string t1min = requestSub[i+1];
                    string t1max = requestSub[i+2];
                    string t2min = requestSub[i+6];
                    string t2max = requestSub[i+7];



                    p1min = getTime(t1min);
                    p1max = getTime(t1max);
                    p2min = getTime(t2min);
                    p2max = getTime(t2max);
                    float min = p2min - p1min;
                    float max = p2max - p1min;



//                    cout<<"i, j => "<<mati<<", "<<matj<<endl;
//                    cout<<"time from "<<requestSub[i]<<" to "<<requestSub[i+5]<<" is "<<
//                        matrix[mati][matj].at(0)<<endl;

                    if(min >= matrix[mati][matj].at(0) && max >= matrix[mati][matj].at(0)){
                        validated = true;
                        cout<<"its valid"<<endl;
                    }else{
                        validated = false;
                        cout<<"its not valid"<<endl;
                    }

//                    cout<<"time difference between these places as given are (in minutes) min => "<<
//                        p2min-p1min<<" and max => "<<p2max-p1max<<endl;
                }
                else{
//                    cout<<requestSub[i+5]<<" not found "<<endl;
                }
            }
        }





//        if ( dict.find("montbeliard") == dict.end() ) {
//            // not found
//            cout<<"montbeliard not found"<<endl;
//        } else {
//            // found
//
//            cout<<"montbeliard found"<<endl;
//        }

//     cout<<"The size is"<<y<<endl;
//     for (size_t i = 0; i < time_windows.size(); i++)
//         cout << time_windows[i] << endl;


 }


};


#endif //CARPOOL_REQUEST_H
