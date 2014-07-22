/**
 * This file is to help me learn libcurl and boost property_tree
 * Ignore it, it's nothing special
 */

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

struct sTest
{
  int remaining;
  void load (std::istringstream &stream);
};

int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);
int headerWriter(char *data, size_t size, size_t nitems, std::string *buffer_in);

int main(void)
{ 
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;
  
  curl_slist_append(headers, "Accept: application/json");
  curl_slist_append(headers, "Content-Type: application/json");
  curl_slist_append(headers, "charsets: utf-8");
  curl = curl_easy_init();
  
  std::string theData;
  std::string theHeader;
  
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerWriter);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&theHeader);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "JoyfulReaper");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/rate_limit");
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&theData);
    
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      std::cout << curl_easy_strerror(res) << std::endl;
    
    std::cout << "Recived: \n" << theData << "\n\n";
    std::cout << "Recived: \n" << theHeader << "\n\n";
    
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    
    sTest st;
    std::istringstream ss(theData);
    st.load(ss);
    
    std::cout << "Our ptree claims we have: " << st.remaining << " requests left." << std::endl;
  }
  
  return 0;
}

int headerWriter(char *data, size_t size, size_t nitems, std::string *buffer_in)
{
  if(buffer_in != NULL)
  {
    buffer_in->append(data, size * nitems);
    return size * nitems;
  }
  return 0;
}

int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{
  if(buffer_in != NULL)
  {
    buffer_in->append(data, size * nmemb);
    return size * nmemb;
  }
  return 0;
}

void sTest::load(std::istringstream &stream)
{
  using boost::property_tree::ptree;
  ptree pt;
  read_json(stream, pt);
  remaining = pt.get("resources.core.remaining", 0);
}