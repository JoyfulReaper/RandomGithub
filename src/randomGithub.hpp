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
#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

struct github_ratelimit
{
  unsigned int limit;
  unsigned int remaining;
  unsigned int reset;
  
  void load(std::istringstream &stream)
  {
    using boost::property_tree::ptree;
    ptree pt;
    read_json(stream, pt);
    
    limit = pt.get("rate.limit", 0);
    remaining = pt.get("rate.remaining", 0);
    reset = pt.get("rate.reset", 0);
  }
};

struct github_repo
{
  unsigned int id;
  std::string ownerLogin;
  std::string ownerHtmlUrl;
  std::string repoName;
  std::string repoFullName;
  std::string repoHtmlUrl;
  std::string repoDescription;
  
  void load(const std::string &filename)
  {
    using boost::property_tree::ptree;
    ptree pt;
    read_json("test.json", pt);
    
    std::cout << pt.get<std::string>(".id") << "\n";
    
    while (!pt.empty())
    {
      std::cout << pt.get<std::string>(".id") << "\n";
      pt.pop_front();
    }
  }
};

static const unsigned int MAX_REPOS = 23000000;

class RandomGithub
{
public:
  struct github_ratelimit github_getRateLimit();
  struct github_repo github_getAllRepos();
  
  std::string makeJSONRequest(const std::string url);
  std::string makeJSONRequest(const std::string url, std::string &headersOut);
  
private:
};

size_t reciveHeaders(char *buffer, size_t size, size_t nitems, std::string *buffer_in);
size_t reciveData(char *buffer, size_t size, size_t nmemb, std::string *buffer_in);

#endif