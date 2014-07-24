/*
 * RandomGithub: randomGithub.hpp
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
 * @file randomGithub.hpp
 * @author Kyle Givler
 */

#ifndef _RANDOM_GITHUB_H_
#define _RANDOM_GITHUB_H_

#include <string>
#include <sstream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "gitRepo.hpp"

struct github_ratelimit
{
  unsigned int limit;     // Request limit per hour
  unsigned int remaining; // Requests remaining
  unsigned int reset;     // Time until limit resets
  
  void load(std::istringstream &stream)
  {
    using boost::property_tree::ptree;
    ptree pt;
    read_json(stream, pt);
    
    limit = pt.get("rate.limit", 0);
    remaining = pt.get("rate.remaining", 0);
    reset = pt.get("rate.reset", 0);
    
    return;
  }
};

struct github_repos
{
  std::vector<int> id;
  std::vector<std::string> ownerLogin;       // Repo Owners login
  std::vector<std::string> ownerHtmlUrl;     // Repo Owners URL 
  std::vector<std::string> repoName;         // Repo name
  std::vector<std::string> repoFullName;     // Repo Full name
  std::vector<std::string> repoHtmlUrl;      // Repo URL 
  std::vector<std::string> repoDescription;  // Repo description
  
  void load(std::istringstream &stream)
  {
    using boost::property_tree::ptree;
    ptree pt;
    read_json(stream, pt);
    
    while (!pt.empty())
    {
      id.push_back(pt.get(".id", -1));
      ownerLogin.push_back(pt.get(".owner.login", "unknown"));
      ownerHtmlUrl.push_back(pt.get(".owner.html_url", "unknown"));
      repoName.push_back(pt.get(".name", "unknown"));
      repoFullName.push_back(pt.get(".full_name", "unknown"));
      repoHtmlUrl.push_back(pt.get(".html_url", "unknown"));
      repoDescription.push_back(pt.get(".description", "unknown"));
      pt.pop_front();
    }
    return;
  }
};

static const unsigned int MAX_SINCE = 23000000;
static const unsigned int MAX_REPOS = 99;

class RandomGithub
{
public:
  /**
   * Retreive rate limiting information from github 
   * @return struct contining rate limiting information
   */
  struct github_ratelimit github_getRateLimit();
  
  /**
   * Retreive information about github repos
   * @return struct containing information about repos retreived
   */
  struct github_repos github_getAllRepos(unsigned int since = 0);
  
  /**
   * @return Random number between min and max 
   */
  unsigned int getRandomNumber(unsigned int min, unsigned int max);
  
  std::vector<GitRepo> getRandomRepos(unsigned int num = 1, unsigned int requests = 1);
  
  std::string makeJSONRequest(const std::string url);
  std::string makeJSONRequest(const std::string url, std::string &headersOut);
  
private:
};

size_t reciveHeaders(char *buffer, size_t size, size_t nitems, std::string *buffer_in);
size_t reciveData(char *buffer, size_t size, size_t nmemb, std::string *buffer_in);

#endif