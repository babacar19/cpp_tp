#include<algorithm>
#include <fstream>
#include <regex>
#include "CIndex.h"
#include "CWordStats.hpp"



using namespace std;

//constructeur de CIndex
CIndex::CIndex(const char *wordList) {
    ifstream file(wordList);
    if(file.fail())
        exit(1);
    else{
        string line;
        while (getline(file, line)) {
            auto pos=line.find(' ');
            if (pos!=string::npos)
                Set.insert(line.substr(0,pos));

        }
    }
}

//surcharge operateur () pour initialiser les docs et appeler la methode ExtractWords
void CIndex::operator()(const char* filename) {

    SDoc* doc = new SDoc(filename);
    curDoc = doc;
    Docs.push_back(doc);
    ExtractWords(filename,*this);
}

//destructeur CIndex
CIndex::~CIndex() {
    for(auto& doc:Docs)
        delete doc;
}

//surcharge de l'operateur () pour la creation de index renverse
void CIndex::operator()(const std::string &line, unsigned int lineNumber, unsigned int wordNumber, const std::string &word) {

    string strL(word);
    auto low = [](char c) { return tolower(c); };
    transform(strL.begin(), strL.end(), strL.begin() , low);

    curDoc->DocWords[strL]++;

    auto search = RevIndex.find(strL);
    if(search == RevIndex.end()){
        RevIndex[strL] = vector<SDoc*>() ;
        RevIndex[strL].push_back(curDoc);

    } else{
        int in = 0;
        for(auto & d : RevIndex[strL])
            if (d == curDoc)
                in = 1;
            if(in == 0)
                RevIndex[strL].push_back(curDoc);
    }

}

void CIndex::calculate() {
    //tri des listes des documents à l'aide de std::sort et d'une fonction lambda
    unsigned int nbDocs;
    for(const auto &word: Set){
        nbDocs = RevIndex[word].size();
        sort(RevIndex[word].begin() , RevIndex[word].end() , [word , nbDocs](SDoc* d1 , SDoc* d2 ) { return coefficient(d1,word,nbDocs) > coefficient(d2,word,nbDocs) ;});

    }

}


bool CIndex::PrintDocs(const std::string &word) {
    this->calculate();//on trie d'abord les documents en utilisant le coefficient pertinent
    auto search = RevIndex.find(word);//verification de la presence du mot dans notre stopwordlist
    if(search == RevIndex.end()){
        std::cout << word << "not found " << "\n";
        return false;
    } else{
        for(const auto doc : search->second)
            std::cout << doc->name << "\n";
    }

    return true;
}

