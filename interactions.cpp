#include<iostream>
#include "interactions.h"
using namespace std;

/**
 * @brief Interactions::Interactions constructeur par defaut de la classe Intercation
 */
Interactions::Interactions()
{
    setContenu("null");
    setDate(ConvertDt());
    setDateI();
}
/**
 * @brief Interactions::Interactions constructeur par valeur de la classe
 * @param contenu : la valeur a donner au attribut
 * @param date : la valeur de la date a donner au l'attribut
 */
Interactions::Interactions(const string &contenu, const string &date)
{
    this->setContenu(contenu);
    this->setDate(date);
    this->setDateI();
}
/**
 * @brief Interactions::~Interactions destructeur par defaut de la classe
 */
Interactions::~Interactions()
{

}
/**
 * @brief Interactions::get contenu    accesseur en lecture
 * @return  l'attribut contenue
 */
string Interactions::getContenu() const
{
    return this->contenu;
}
/**
 * @brief Interactions::getDate  accesseur en lecture
 * @return la valeur de la date qui est de type date
 */
string Interactions::getDate() const
{
    return this->dateI;
}

/**
 * @brief Interactions::getListetodo  accesseur en lecture
 * @return la liste des todo de l'interaction (l'instance courante )
 */
list<todo> Interactions::getListetodo() const
{
    return this->gestionTodo.getListe();
}
/**
 * @brief Interactions::getId
 * @return recuperer l'id de l'interaction
 */
string Interactions::getId()
{
    return this->idI;
}
/**
 * @brief Interactions::setContenu  accesseur en ecriture
 * @param c : la valeur a donner pour l'attribuit contenu
 */
void Interactions::setContenu(const string &c)
{
    this->contenu=c;
}
/**
 * @brief Interactions::setDate  accesseur en ecriture
 * @param d : la valeur a donner pour l'attribuit date
 */
void Interactions::setDate(const string &d)
{
    this->dateI=d;
}
/**
 * @brief Interactions::setId
 * @param id modifier l'id de l'interaction
 */
void Interactions::setId(string id)
{
    this->idI=id;
}
/**
 * @brief Interactions::Addtodo methode pour ajouter un todo dans la liste des todo
 * @param T : todo a ajouter dans la liste
 */
void Interactions::Addtodo(const todo &T)
{
    this->gestionTodo.Addtodo(T);
}
/**
 * @brief operator << : operateur de flux surchargé pour afficher la la liste des interactions
 * @param os    : variable de type ostream qui dirige le flux de sortie
 * @param I : la liste des interactions a afficher
 * @return  flux de sortie
 */
ostream & operator<<(ostream &os ,const Interactions &I)
{
    os<<I.getContenu()<<"\t"<<I.getDate();
    return os;
}
/**
 * @brief Interactions::getGestionTodo
 * @return recuperer l'attribut gestionTodo
 */
GestionTodo Interactions::getGestionTodo()const
{
    return this->gestionTodo;
}

/**
 * @brief Interactions::operator == on compare deux interaction (l'instance courante avec une autre passer en parametre )
 * @param l interaction a comparer avec
 * @return un boolean suivant le resultat de la comparaison
 */
bool Interactions::operator==(const Interactions &l)const
{
    //bool t=false;
    if(this->getDate()==l.getDate())
        if(this->getContenu()==l.getContenu())
        {
            return true;
            }

    return false;
}
/**
 * @brief Interactions::editTodo modifier la tache d'un todo parmis les todos qui existent dans l'interaction courante
 * @param t : todo dont on va changer la tache
 * @param c :  la nouvelle tache a fair
 */
void Interactions::editTodo(const todo &t,const string &c)
{
    this->gestionTodo.editTodo(t,c);
}
/**
 * @brief Interactions::editTodo modifier la tache d'un todo parmis les todos qui existent dans l'interaction courante
 * @param t : todo dont on va changer la tache
 * @param c : la nouvelle date du todo t
 */
void Interactions::editTododt(const todo &t,const string &c)
{
    this->gestionTodo.editTododt(t,c);
}
/**
 * @brief Interactions::removeTodo methode pour supprimer un todo parmis les todos qui existent
 * @param t : le todo a supprimer
// */
void Interactions::removeTodo(const todo &t)
{
    this->gestionTodo.removeTodo(t);
}
/**
 * @brief Obtient la date de l'interaction.
 * @return La date de l'interaction au format sdateAuto.
 */
struct sdateAuto Interactions::getDateI()const
{
    return this->dateInter;
}
/**
 * @brief Initialise la date de l'interaction à la date actuelle du système.
 */
void Interactions::setDateI()
{
    day_point dp = floor<days>(system_clock::now());
    auto ymd = year_month_day{dp};
    this -> dateInter.jour = ymd.day();
    this -> dateInter.mois = ymd.month();
    this -> dateInter.annee = ymd.year();
}
/**
 * @brief Convertit la date de l'interaction au format string (jour/mois/année).
 * @return La date de l'interaction sous forme de chaîne de caractères.
 */
string Interactions::ConvertDt()
{
    return to_string(this->dateInter.jour.operator unsigned int())+"/"+to_string(this->dateInter.mois.operator unsigned int())+"/"+to_string(this->dateInter.annee.operator int());

}
