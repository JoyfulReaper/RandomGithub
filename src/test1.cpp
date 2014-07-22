#include <curl/curl.h>
#include <iostream>

int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);

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
  
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "JoyfulReaper");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/rate_limit");
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&theData);
    
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      std::cout << curl_easy_strerror(res) << std::endl;
    
    std::cout << theData << std::endl;
    
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
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