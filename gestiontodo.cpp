#include "gestiontodo.h"

GestionTodo::GestionTodo()
{

}
/**
 * @brief Ajoute une tâche à la liste des tâches.
 * @param t La tâche à ajouter.
 */
void GestionTodo::Addtodo(const todo &t)
{
    listetodo.push_back(t);
}
/**
 * @brief Modifie le contenu d'une tâche dans la liste des tâches.
 * @param t La tâche à modifier.
 * @param c Le nouveau contenu de la tâche.
 */
void GestionTodo::editTodo(const todo &t,const string &c)
{
    auto it = listetodo.begin();
    bool found = false;
    while((it!=listetodo.end()) && (found == false))
    {
        if(*it == t)
        {
            found = true;
            it->setTache(c);
        }
        else
            ++it;
    }
}
/**
 * @brief Modifie la date d'une tâche dans la liste des tâches.
 * @param t La tâche à modifier.
 * @param c La nouvelle date de la tâche.
 */
void GestionTodo::editTododt(const todo &t , const string&c)
{
    auto it = listetodo.begin();
    bool found = false;
    while((it!=listetodo.end()) && (found == false))
    {
        if(*it == t)
        {
            found = true;
            it->setdateT(c);
        }
        else
            ++it;
    }
}
/**
 * @brief Supprime une tâche de la liste des tâches.
 * @param t La tâche à supprimer.
 */
void GestionTodo::removeTodo(const todo&t)
{
    auto it = listetodo.begin();
    bool found = false;
    while((it!=listetodo.end()) && (found == false))
    {
        if(*it == t)
        {
            found = true;
            it=listetodo.erase(it);
        }
        else
            ++it;
    }
}
/**
 * @brief Obtient la liste complète des tâches.
 * @return La liste des tâches.
 */
list<todo> GestionTodo::getListe()const
{
    return this->listetodo;
}
