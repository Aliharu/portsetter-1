#include <cstring>
#include <iostream>
#include <string>
#include <regex>
 
int main() 
{
    // char input[100] = "es_US.UTF-8";
    // char *token = std::strtok(input, "_");
    // while (token != NULL) {
    //     std::cout << token << '\n';
    //     token = std::strtok(NULL, " ");
    // }
    
    // std::regex("meow", std::regex::icase)
    
    // regex_search example
    // error out on invalid SYNTAX, don't worry about a valid VALUE e.g. 
        // es is good because country and format are optional
        // en_FR is good because format is optional
        // en.UTF-8 is good because country is optional
        // en_NZ.UTF-8 is good
        // zz_ZZ.UTF-8 is good syntax, the fact that there's no language zz or country ZZ is not important. They could appear after your program is released.
        // e1 is bad syntax, no number
        // english is bad syntax, only 2 letter language
        // en_USA is bad syntax, only 2 letter country
        // EN is bad syntax, only lowercase language
        // en_us is bad syntax, only uppercase country
        //use regEx to parse out the language without the country or format

    std::string lines[] = {
        "er",
        "er_FR",
        "en.UTF-8",
        "en_NZ.UTF-8",
        "zz_ZZ.UTF-8",
        "e1",
        "english",
        "en_USA",
        "EN",
        "en_us"
    };
 
    std::regex re("^([a-z]{2})(_[A-Z]{2})?(.UTF-8)?$");
    std::smatch match;
    // simple match
    for (const auto &line : lines) {
       // std::cout << line << ": " << std::boolalpha
       //           << std::regex_search(line, regex) << '\n';
       std::cout << line << ": ";
      if(std::regex_search(line.begin(), line.end(), match, re)){
        std::cout << match[1] << std::endl;
      }
    else{
        std::cout << "Has bad format" << std::endl;
    }
    }   
    std::cout << '\n';
}