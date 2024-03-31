#ifndef GESTIONINTERACTION_H
#define GESTIONINTERACTION_H
#include"interactions.h"
#include<list>

class GestionInteraction
{
private:
list<Interactions >ListInter;



public:
    GestionInteraction();
    list<Interactions> getList()const;

    void addInter(const Interactions &);
    void removeInter(const Interactions &);
    void editInter(const Interactions &, const string &);
    void editInterdt(const Interactions &,const todo &,const string&);
    void editInter(const Interactions &, const todo &,const string&);
    void removeTodofromInter(const Interactions &,const todo&);
};

#endif // GESTIONINTERACTION_H
