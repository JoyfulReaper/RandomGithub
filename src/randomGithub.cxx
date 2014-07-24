/*
 * RandomGithub: randomGithub.cxx
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
 * @file randomGithub.cxx
 * @author Kyle Givler
 */

#include <curl/curl.h>
#include <random>
#include <chrono>
#include <algorithm>
#include "randomGithub.hpp"

struct github_ratelimit RandomGithub::github_getRateLimit()
{
  github_ratelimit rl;
  
  std::istringstream ss(makeJSONRequest("https://api.github.com/rate_limit"));
  rl.load(ss);
  
  return rl;
}

struct github_repos RandomGithub::github_getAllRepos(unsigned int since)
{
  if(since > MAX_SINCE)
  {
    throw("since is too large");
  }
  
  github_repos gr;
  
  std::istringstream ss(makeJSONRequest("https://api.github.com/repositories?since=" + std::to_string(since)));
  gr.load(ss);
  
  return gr;
}

unsigned int RandomGithub::getRandomNumber(unsigned int min, unsigned int max)
{
  size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> dist(min, max);
  
  return ( dist(gen) );
}

std::vector<GitRepo> RandomGithub::getRandomRepos(unsigned int num, unsigned int requests)
{
  if(num > MAX_REPOS)
    num = MAX_REPOS;
  
  std::vector<GitRepo> repos;
  
  for(size_t i = 0; i < requests; i++)
  {
    unsigned int since = RandomGithub::getRandomNumber(0, MAX_SINCE);
    github_repos gr = github_getAllRepos(since);
    
    
    for(size_t i = 0; i < gr.id.size(); i++)
    {
      if(gr.id[i] != -1)
      {
	GitRepo repo;
	repo.setRepoId(gr.id[i]);
	repo.setOwnerLogin(gr.ownerLogin[i]);
	repo.setOwnerHtmlUrl(gr.ownerHtmlUrl[i]);
	repo.setRepoName(gr.repoName[i]);
	repo.setRepoFullName(gr.repoFullName[i]);
	repo.setRepoHtmlUrl(gr.repoHtmlUrl[i]);
	repo.setRepoDescription(gr.repoDescription[i]);
	repos.push_back(repo);
      }
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (repos.begin(), repos.end(), std::default_random_engine(seed));
  }
  
  while(repos.size() > num + 1)
  {
    repos.pop_back();
  }
  
  return repos;
}

std::string RandomGithub::makeJSONRequest(const std::string url)
{
  std::string ignore;
  return makeJSONRequest(url, ignore);
}

std::string RandomGithub::makeJSONRequest(const std::string url, std::string &headersOut)
{
  CURL *curl = NULL;
  CURLcode res = CURLE_OK;
  struct curl_slist *headers = NULL;
  
  std::string dataBuffer;
  std::string headerBuffer;
  
  curl = curl_easy_init();
  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, "charsets: utf-8");
  
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, reciveHeaders);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&headerBuffer);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "JoyfulReaper");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, reciveData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&dataBuffer);
  } else {
    std::cerr << curl_easy_strerror(res) << std::endl;
    throw("Something went wrong, curl is null!\n");
  }
  
  res = curl_easy_perform(curl);
  
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);
  
  if(res != CURLE_OK)
  {
    std::cerr << curl_easy_strerror(res) << std::endl;
    throw("Something went wrong :(\n");
  }
  
  headersOut = headerBuffer;
  return dataBuffer;
}

size_t reciveData(char *buffer, size_t size, size_t nmemb, std::string *buffer_in)
{
  if(buffer_in != NULL)
  {
    buffer_in->append(buffer, size * nmemb);
    return size * nmemb;
  }
  return 0;
}

size_t reciveHeaders(char *buffer, size_t size, size_t nitems, std::string *buffer_in)
{
  if(buffer_in != NULL)
  {
    buffer_in->append(buffer, size * nitems);
    return size * nitems;
  }
  return 0;
}