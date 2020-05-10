#pragma once
#include<algorithm>
#include <fstream>
#include <iostream>
#include <regex>

#include<map>

template <class F>
bool ExtractWords(const char* name, F&& func);


class CWordStats {

public:
    CWordStats() = default;
    ~CWordStats() = default;
    void operator()(const char* name) {
        ExtractWords(name, *this);
    }

    void operator()(std::string& line) {

        std::cout << std::endl;
    }

    void operator()(const std::string& line, unsigned int lineNumber, unsigned int wordNumber, const std::string& word) {

        //transformation du mot en minuscule avant d'enregistrer le mot
         std::string Twords(word);
        auto low = [](char &c) {return std::tolower(c);};
        std::transform(Twords.begin(), Twords.end(), Twords.begin(), low);
        words[Twords]++;

    }




    void generateStopWordsList(const char* filename ) {
        std::ofstream stpWlist(filename);
        using name_freq = decltype(words)::value_type *;
        std::vector<name_freq> v;//on cree un std::vector de pointeurs vers les std::pair de notre map.

        for(auto &elt:words) v.push_back(&elt);

        std::sort(v.begin() , v.end() , [](name_freq m1, name_freq m2) {return m1->second > m2->second;});

        auto itE=(begin(v)+(v.size()/100));
        for (auto it=begin(v);it!=itE;++it)
            stpWlist << (*it)->first << " : " << (*it)->second << std::endl;
        for (auto it=(begin(v)+(v.size()/5));it!=end(v);++it)
            stpWlist << (*it)->first << " : " << (*it)->second << std::endl;

    }

private:
    std::map<std::string, unsigned int > words;

};


template <class F>
bool ExtractWords(const char* name, F&& func) {
    //std::cout << "fichier " << name << " ******** " << std::endl;
    std::ifstream file(name);
    if (!file.fail()) {

        std::regex regexp(R"#(\w[\w-]*)#");
        std::string line;
        unsigned int wordNumber = 0;
        unsigned int lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            auto lineBeg = std::sregex_iterator(line.begin(), line.end(), regexp);
            auto lineEnd = std::sregex_iterator();
            for (auto itr = lineBeg; itr != lineEnd; itr++) {
                func(line, lineNumber, wordNumber, itr->str());
            }
        }
    }
    else {
        std::cout << "error opening file " << std::endl;
        return false;
    }

    return true;

}

