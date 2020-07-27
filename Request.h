//
// Created by user on 26/07/2020.
//

#ifndef CARPOOL_REQUEST_H
#define CARPOOL_REQUEST_H

#include <sstream>

using namespace std;
class Request {
public :
    string request;
    vector<string> time_windows;
    Request(string request_string){
        request=request_string;
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

 void validateRequestTw(){

    }


};


#endif //CARPOOL_REQUEST_H
