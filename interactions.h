#ifndef INTERACTIONS_H
#define INTERACTIONS_H
#include<string>
#include<list>
#include "todo.h"
#include "sdateAuto.h"
#include"date/date.h"
#include"gestiontodo.h"
using namespace std;
 //l'explication de tout les membres de la classe ont etaient expliqué dans le cpp avec doxygene

using namespace date;
using namespace std::chrono;
using day_point = std::chrono::time_point<std::chrono::system_clock, days>;
using namespace std;


class Interactions
{
private:
    string contenu;
    string dateI;
    string idI;
    struct sdateAuto dateInter;
    GestionTodo gestionTodo;
    //list<todo> listetodo;

public:
    Interactions();
    Interactions(const string &, const string &);
    ~Interactions();

    string getContenu() const;
    string getDate() const;
    struct sdateAuto getDateI()const;
    list<todo> getListetodo() const;
    GestionTodo getGestionTodo()const;
    string getId();

    void setContenu(const string &);
    void setDate(const string &);
    void setDateI();
    void setId(string);

    void Addtodo(const todo &);
    void editTodo(const todo &,const string &);
    void editTododt(const todo & , const string&);
    void removeTodo(const todo&);
    string ConvertDt();
    friend ostream & operator<<(ostream & ,const Interactions &);
    bool operator==(const Interactions &)const;
};

#endif // INTERACTIONS_H
