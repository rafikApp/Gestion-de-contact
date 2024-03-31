#ifndef TODO_H
#define TODO_H
#include<string>


#include "sdateAuto.h"
#include "date/date.h"
#include "date/chrono_io.h"

using namespace date;
using namespace std::chrono;
using day_point = std::chrono::time_point<std::chrono::system_clock, days>;



using namespace std ;
 //l'explication de tout les membres de la classe ont etaient expliqué dans le cpp avec doxygene

class todo
{
private:
    string tache;
    string limite;
    struct sdateAuto date;

public:
    todo();
    todo(const string &, string &);
    ~todo();

    string getTache() const;
    string getdateT()const;
    struct sdateAuto getDate() const;
    void setTache(const string &);
    void setdateT(const string &);
    void setDate();

    string ConvertDate();
    friend ostream & operator<<(ostream & ,const todo &);
    bool operator==(const todo &)const;
};

#endif // TODO_H
