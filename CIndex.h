#pragma once
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

class CIndex{
public:
    CIndex(const char *wordList = nullptr);
    ~CIndex();
    CIndex(const CIndex& )= delete;
    CIndex& operator=(const CIndex& )= delete;
    void operator()(const char* filename);
    void operator()(const std::string& line, unsigned int lineNumber, unsigned int wordNumber, const std::string& word);
    void calculate();//tri des listes des documents.
    bool PrintDocs(const std::string& word);//Afichage des documents contenant le mot entré en parametre

private:
    struct SDoc{
        SDoc(const char* file):name(file){};
        std::string name;
        std::unordered_map<std::string, unsigned int> DocWords;

    };
    friend double coefficient(SDoc* d , const std::string& word , unsigned int nbDocs ){//calcul du coefficient sur lequel s'effectue le tri des documents
        return d->DocWords[word]/nbDocs;
    }

private:
    std::unordered_set<std::string > Set;// notre StopwordList
    std::vector<SDoc*> Docs;//vecteur contenant des pointenants vers les documents
    std::unordered_map<std::string, std::vector<SDoc*> > RevIndex;//index renversé
    SDoc *curDoc;//document courant

};

