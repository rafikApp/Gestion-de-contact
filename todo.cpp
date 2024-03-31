#include "todo.h"
#include<iostream>
#include <QString>
using namespace std;
// constructeur
/**
 * @brief todo::todo un constructeur vide de la classe todo.
 */
todo::todo()
{
this->tache="null";
this->setDate();
this->setdateT(ConvertDate());
}
/**
 * @brief todo::todo constructeur prend deux paramètres : Il permet de créer un objet de la classe "todo" en initialisant ses membres avec les valeurs passées en paramètres.
 * @param t une chaîne de caractères
 * @param d un objet de type "Date"
 */
todo::todo(const string &t,string &d)
{

    this->setTache(t);
    this->setdateT(d);

}
/**
 * @brief todo::~todo un destructeur de la classe todo
 */
todo::~todo()
{

}
/**
 * @brief todo::getTache permet de retourner la valeur de l'attribut tache de l'objet de la classe "todo".
 * @return chaîne de caractères qui représente la tâche associée à cet objet.
 */
string todo::getTache() const
{
    return this->tache;
}
/**
 * @brief todo::getdateT permet de renvoyer la date limite associée à la tâche.
 * @return un objet "Date" qui contient cette date limite.
 */
string todo::getdateT()const
{
    return this->limite;
}
/**
 * @brief todo::setTache permet de définir la tâche associée à un objet todo en utilisant une chaîne de caractères passée en argument.
 * @param t représente la nouvelle valeur de la tache
 */
void todo::setTache(const string &t)
{
    this->tache=t;
}
/**
 * @brief todo::setdateT permet de définir la date limite associée à une tâche todo en utilisant un objet de la classe Date passé en argument.
 * @param d représente la nouvelle valeur de la date
 */
void todo::setdateT(const string &d)
{
    this->limite=d;
}
/**
 * @brief Définit la date actuelle comme date pour une tâche.
 * Utilise la date actuelle du système pour initialiser la date de la tâche.
 * La date est stockée dans la structure `sdateAuto` de la classe `todo`.
 */
void todo::setDate()
{
    day_point dp = floor<days>(system_clock::now());
    auto ymd = year_month_day{dp};
    this ->date.jour = ymd.day();
    this -> date.mois = ymd.month();
    this -> date.annee = ymd.year();
}
/**
 * @brief Obtient la date associée à la tâche.
 * @return La structure de date `sdateAuto` représentant la date associée à la tâche.
 */
struct sdateAuto todo::getDate()const
{
 return this->date;
}
/**
 * @brief Convertit la date de la tâche en une chaîne de caractères.
 * @return Une chaîne représentant la date au format "jour/mois/année".
 */
string todo::ConvertDate()
{
    return to_string(this->date.jour.operator unsigned int())+"/"+to_string(this->date.mois.operator unsigned int())+"/"+to_string(this->date.annee.operator int());

}
/**
 * @brief operator << permet d'afficher un objet de la classe todo dans un flux de sortie,
 * @param os objet de flux de sortie sur lequel vous souhaitez afficher les informations de l'objet todo
 * @param T un paramètre de la fonction et représente un objet de la classe todo.
 * @return
 */
ostream & operator<<(ostream &os ,const todo &T)
{
    os<<"@todo "<<T.getTache()<<" @date "<<T.getdateT();
    return os;
}
/**
 * @brief todo::operator == permet de comparer deux objets "todo" pour déterminer s'ils sont égaux en fonction de la date limite (limite) et de la tâche (tache) associées à chaque objet.
 * @param t une référence constante à un objet de la classe todo
 * @return Elle renverra true si les dates limites et les tâches de deux objets todo sont identiques. Si les dates limites ou les tâches diffèrent entre les deux objets, la méthode renverra false.
 */
bool todo::operator==(const todo &t)const
{
    if(getdateT()==t.getdateT()){
        if(getTache()==t.getTache())
            return true;
    }

    return false;
}
