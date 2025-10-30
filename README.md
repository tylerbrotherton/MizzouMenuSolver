# MizzouMenuSolver

This is thought of and produced by Tyler Brotherton
This program scraps the Mizzou dining hall sites and displays the menu and times that the dining halls are open. If you go to Mizzou, and want to know what the dining halls are serving, this is the program for you. 
Currently the solution is to open 3 seperate tabs and click through boxes. I don't want to do that.

this repo is in C++. Don't like C++, sucks to suck. I'm going to try and use as much C convention as I can. 
However, this is only possible due to the object orientented abilities of the greatest programming langunge ever.
Additionally, C++ is the top 10 most popular programming langunges, but no professor teaches C++.
Mizzou goes directly from c->c#?

Yo, if Mizzou admin/professors is reading this, give me my research funding, plz?


This is how it works

Solution "happy path"
Loads Curl -> extract the data from the websites -> stores the relevent data -> closes Curl -> Load LMF -> display info/interactive chart -> delete data on local machine.


[Loads Curl -> extract the data from the websites -> stores the relevent data -> closes Curl] WebScrapper.cpp

 [Load LMF -> display info/interactive chart-> save the menu of the data-> delete data on local machine.] Graphs.cpp

 saving  the menu of the day
 [:date].txt   in DD/MM/YYYY format
