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
 * Usage:
 * $ randomGithub [num results]
 */

/**
 * @file main.cpp
 * @author Kyle Givler
 */

#include "randomGithub.hpp"
#include <iostream>
#include <cstdlib>

int main (int argc, char **argv)
{
  //   std::string headers;
  //   std::string data = gh.makeJSONRequest("https://api.github.com/rate_limit", headers);
  //   
  //   std::cout << "Raw input: \n";
  //   std::cout << "Data: " << data << "\n\n";
  //   std::cout << "Headers: " << headers << "\n";
  
  std::cout << "Please wait, finding random repos just for you!\n\n";
  
  RandomGithub gh;
  unsigned int num;
  if(argc == 2)
    num = strtol(argv[1], NULL, 10);
  if (!num)
    num = 5;

  auto repos = gh.getRandomRepos(num);
  
  if(repos.size() == 0)
  {
    std::cout << "No repos found! \"since\" is probably too large!\n";
  }
  
  for(auto &repo : repos)
  {
    std::cout << "ID: " << repo.getRepoId() << std::endl;
    std::cout << "Owner: " << repo.getOwnerLogin() << std::endl;
    std::cout << "Owner's GitHub: " << repo.getOwnerHtmlUrl() << std::endl;
    std::cout << "Repo name: " << repo.getRepoName() << std::endl;
    std::cout << "Repo Description: " << repo.getRepoDescription() << std::endl;
    std::cout << "Repo URL: " << repo.getRepoHtmlUrl() << std::endl;
    std::cout << std::endl;
  }
  
  github_ratelimit rl = gh.github_getRateLimit();
  std::cout << "GitHub rate limiting information: \n";
  std::cout << "Limit: " << rl.limit << std::endl;
  std::cout << "API Requests Remaining: " << rl.remaining << std::endl;
  std::cout << "Reset: " << rl.reset << std::endl << std::endl;
  
  
  
  return 0;
}