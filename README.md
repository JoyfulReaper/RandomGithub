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

Usage:
=====
randomGithub [number of results 0-99]  
gtkRandomGithub [number of API requests]

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
