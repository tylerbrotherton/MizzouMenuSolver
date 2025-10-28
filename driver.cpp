#include <iostream>
#include <string>
#include <vector>

#include "WebScrapper.h"
#include "Graphics.h"

int main(){
    std::vector<std::string> diningHallsAtMizzou;
    diningHallsAtMizzou.append("plaza-900-dining")

      
  
    std::vector<std::string> items;
    items=fectpage("https:////dining.missouri.edu//locations//"+diningHallsAtMizzou.at(0)+'//');
    int displayGraphicsReturn=displayGraphics(items);
      
}
