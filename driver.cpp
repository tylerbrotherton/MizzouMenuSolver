#include <iostream>
#include <string>
#include <vector>

#include "WebScrapper.h"
#include "Graphics.h"

int main(){
    String diningHallsAtMizzou[3]= {"plaza-900-dining","the-mark-on-5th-street","the-restaurants-at-southwest"};

      
    for(String i: diningHallsAtMizzou)
        std::vector<std::string> items;
        items=fectpage("https:////dining.missouri.edu//locations//"+diningHallsAtMizzou.at(0)+'//');
        int success=displayGraphics(items);
        if(success==0) cout<<"Success for " <<i;
}
