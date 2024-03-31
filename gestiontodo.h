#ifndef GESTIONTODO_H
#define GESTIONTODO_H
#include"todo.h"
#include<list>
class GestionTodo
{
private:
    std::list<todo > listetodo;


public:
    GestionTodo();
    list<todo> getListe() const;

    void Addtodo(const todo &);
    void editTodo(const todo &,const string &);
    void editTododt(const todo & , const string&);
    void removeTodo(const todo&);
};

#endif // GESTIONTODO_H
