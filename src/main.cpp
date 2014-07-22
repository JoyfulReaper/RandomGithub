/*
 * RandomGithub: main.cpp
 * Copyright (C) 2014 Kyle Givler
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file main.cpp
 * @author Kyle Givler
 */

#include "randomGithub.hpp"
#include <iostream>

int main (int argc, char **argv)
{
  RandomGithub gh;
  std::string headers;
  std::string data = gh.makeJSONRequest("https://api.github.com/rate_limit", headers);
  
  std::cout << "Data: " << data << "\n\n";
  std::cout << "Headers: " << headers << "\n";
  return 0;
}