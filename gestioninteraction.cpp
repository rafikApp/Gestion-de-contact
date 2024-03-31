#include "gestioninteraction.h"


/**
 * @brief Constructeur par défaut de la classe GestionInteraction.
 */
GestionInteraction::GestionInteraction()
{

}
/**
 * @brief Obtient la liste des interactions.
 * @return Une liste d'Interactions.
 */
list<Interactions>  GestionInteraction::getList()const
{
    return this->ListInter;
}
/**
 * @brief Ajoute une interaction à la liste.
 * @param I L'interaction à ajouter.
 */
void GestionInteraction::addInter(const Interactions &I)
{
    this->ListInter.push_back(I);
}
/**
 * @brief Supprime une interaction de la liste.
 * @param i L'interaction à supprimer.
 */
void GestionInteraction ::  removeInter(const Interactions &i)
{
    auto it = ListInter.begin();
    bool found = false;
    while((it!=ListInter.end()) && (found == false))
    {
        if(*it == i)
        {
            found = true;
            it = ListInter.erase(it);
        }
        else
            ++it;
    }
}
/**
 * @brief Modifie le contenu d'une interaction.
 * @param l L'interaction à modifier.
 * @param c Le nouveau contenu.
 */
void GestionInteraction::editInter(const Interactions &l, const string &c)
{

    auto it = ListInter.begin();
    bool found = false;
    while((it!=ListInter.end()) && (found == false))
    {
        if(*it == l)
        {
            found = true;
            it->setContenu(c);

        }
        else
            ++it;
    }
}
/**
 * @brief Modifie une tâche d'une interaction avec une nouvelle tâche et une nouvelle date.
 * @param l L'interaction à modifier.
 * @param t La nouvelle tâche.
 * @param d La nouvelle date.
 */
void GestionInteraction::editInterdt(const Interactions &l,const todo &t,const string&d)
{
    auto it = ListInter.begin();
    bool found = false;
    while((it!=ListInter.end()) && (found == false))
    {
        if(*it == l)
        {
            found = true;
            it->editTodo(t,d);
        }
        else
            ++it;
    }
}

/**
 * @brief Modifie une tâche d'une interaction avec une nouvelle tâche et une nouvelle date.
 * @param l L'interaction à modifier.
 * @param t La nouvelle tâche.
 * @param d La nouvelle date de la tâche.
 */
void GestionInteraction::editInter(const Interactions &l, const todo &t, const string& d)
{
    auto it = ListInter.begin();
    bool found = false;
    while ((it != ListInter.end()) && (found == false))
    {
        if (*it == l)
        {
            found = true;
            it->editTodo(t, d);
        }
        else
            ++it;
    }
}

/**
 * @brief Supprime une tâche d'une interaction.
 * @param i L'interaction concernée.
 * @param t La tâche à supprimer.
 */
void GestionInteraction::removeTodofromInter(const Interactions &i,const todo& t)
{
    auto it = ListInter.begin();
    bool found = false;
    while((it!=ListInter.end()) && (found == false))
    {
        if(*it == i)
        {
            found = true;
            it->removeTodo(t);
        }
        else
            ++it;
    }
}
