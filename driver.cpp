#include <iostream>
#include <string>
#include <vector>

#include "WebScrapper.h" as wb
#include "Graphics.h" as g

int main(){

    //wait for regulatory approval?
    exit();
    //String diningHallsAtMizzou[3]= {"plaza-900-dining","the-mark-on-5th-street","the-restaurants-at-southwest"};
      
    for(String i: diningHallsAtMizzou){
        if(wb.isValid("https:////dining.missouri.edu//locations//"+i+'//'))
            
        std::vector<std::string> items;
        items=wb.fectpage("https:////dining.missouri.edu//locations//"+i+'//');
        int success=g.displayGraphics(items);
        if(success==0) cout<<"Success for " <<i;
    }


    
    /*
    *
    * Do graphics?
    *
    */
    
}
