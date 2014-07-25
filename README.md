RandomGithub
============

Ridiculous way to find random githubs!  
Who needs a simple webscript to find random githubs? Not you! You need full fledged C++ program, and you have found it! This program uses the github API to present you whith a list of random repos with some information such as the owner and a short description.  

Be amazed by all the empty repos, forks with nothing changed, misuses of git, and shitty code you will find using this amazing program!  

There are two binary files:  
randomGithub (console version)  
and  
gtkRandomGithub (GTK version)  

use make to build. Uses a stupid handcoded make file, it requires pkg-config, and may require some tweaking for your setup. Also, if you don't want to build the GUI client (which is much more useful IMHO) you can just do 'make randomGithub'  

On the off chance you find this usefull, feel free to get me a book or something form my Amazon wishlist :) If you find this useful or fun feel free to get me something from my Amazon wishlist :) http://amzn.com/w/2Y6UMLRG23W6W

Usage:
=====
randomGithub [number of results 0-99]  
gtkRandomGithub [number of API requests]

Known Issues:
=============
There is an occasional crash due to not doing threading right.

TODO:
=====
Allow basic authentication to allow more than that standard limit of 50 requests per hour  

Dependencies
============
libcurl (http://curl.haxx.se/libcurl/)  
Boost (Headers only, ptree and json parser) (http://boost.org)  
gtkmm (http://www.gtkmm.org/en/) (For the GUI only)  

Contributors
============
Kyle Givler (JoyfulReaper) - Orignial Author
