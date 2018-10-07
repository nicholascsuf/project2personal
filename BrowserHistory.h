#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
    BrowserHistory();

    void visitSite(Webpage newSite);
    string back();
    string forward();

    void readHistory(string fileName);

    string getUrl();
    size_t getNavSize();
    list<Webpage> getSitesVisited();

private:
    list<Webpage> navHistory;
    list<Webpage>::iterator navPos;
    list<Webpage> sitesVisited;
    int numSites;


};


void BrowserHistory::readHistory(string fileName) {
    string temp;
    int newTime;
    Webpage newSite;
    ifstream inFile(fileName.c_str());



    while(inFile >> temp) {
        if(temp == "new") {
            inFile >> temp >> newTime;
            newSite = Webpage(temp, time_t(newTime));
            visitSite(newSite);
        } else if(temp == "back") {
            back();
        } else if(temp == "forward") {
            forward();
        } else {
            throw logic_error("invalid command");
        }
    }
}


void BrowserHistory::visitSite(Webpage newSite)
{
 navHistory.insert(navPos, newSite);
++navPos;
//numSites++;
sitesVisited.insert(navPos, newSite);


}

 BrowserHistory::BrowserHistory()
{
navPos = navHistory.begin();

}

size_t BrowserHistory::getNavSize(){

return navHistory.size();
}

string BrowserHistory::getUrl(){

 string result = "";

if(!navHistory.empty())
{
result = navPos->getUrl();
}
else
{
    throw invalid_argument("Empty list");

}
return result;
}

list<Webpage> BrowserHistory::getSitesVisited(){

return sitesVisited;
}

string BrowserHistory::back(){
string result;

    if(!navHistory.empty())
    {
    navPos = --navPos;
     result = navPos->getUrl();
    // visitSite (*navPos);
    }

return result;


}
string BrowserHistory::forward(){
navPos = navPos++;
return navPos->getUrl();


}
