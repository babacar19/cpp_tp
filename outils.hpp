
#ifndef TP7_OUTILS_HPP
#define TP7_OUTILS_HPP

#include <fstream>
#include <iostream>
#include <regex>

template <class F>
void ExtractWords(const char* name , F&& func);


class CWordStats{

public:
    CWordStats()= default;
    ~CWordStats()= default;
    void operator()(const char* name){
        ExtractWords(name , *this);
    }

    void operator()(std::string& line){

        std::cout << std::endl;
    }

    void operator()(const std::string& line, unsigned int lineNumber, unsigned int wordNumber,const std::string& word ){
        static std::map<std::string, unsigned int> map;
        map[word]++;
    }

    /



};


template <class F>
void ExtractWords(const char* name , F&& func){
    std::cout << "fichier " <<name <<"*********************************************************************" <<  std::endl;
    std::ifstream file(name);
    if(file){

        std::regex regexp(R"#(\w[\w-éè]*)#");//par contre le 'é' et 'è' ne s'affiche tjrs pas (os linux)
        std::string line;
        unsigned int wordNumber = 0;
        unsigned int lineNumber = 0;
        while(std::getline(file,line)){
            lineNumber++;
            auto lineBeg = std::sregex_iterator(line.begin() , line.end() , regexp);
            auto lineEnd = std::sregex_iterator();
            for(auto itr = lineBeg; itr != lineEnd; itr++){
                func(line , lineNumber, wordNumber, itr->str());
            }
        }
    }
    else{
        std::cout << "error opening file " << std::endl;
    }

}



#endif //TP7_OUTILS_HPP
