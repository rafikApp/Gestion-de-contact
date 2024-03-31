#include "contact.h"
#include<iostream>
using namespace std;
/**
 * @brief Contact::Contact ->constructeur par defaut pour initialiser les attributs avec n'importe quelles valeurs
 */
Contact::Contact()
{

    this->setNom("NULL");
    this->setPrenom("NULL");
    this->setEntreprise("NULL");
    this->setMail("NULL");
    this->setTelephone("NULL");
    this->setPhoto("NULL");
    this->setDateE(ConvertDatem());
    this->setDateC(ConvertDatec());
    this->setDatemodi();
    this->setDatecreation();
//    this->dateC.setJour(6);
//    this->dateC.setAnnee(1254);
//    this->dateC.setMois(12);



}
/**
 * @brief Contact::Contact constructeur par valeur pour initialiser les attributs avec des valeurs présises
 * @param nom : la valeur a donner pour l'attribut nom de type string
 * @param pre : la valeur a donner pour l'attribut prénom de type string
 * @param entr : la valeur a donner pour l'attribut entreprise de type string
 * @param mail : la valeur a donner pour l'attribut email de type string
 * @param tele : la valeur a donner pour l'attribut telephone de type string
 * @param photo : la valeur a donner pour l'attribut photo qui sera un chemin vers la photo
 * @param date : la valeur a donner pour l'attribut date qui sera de type date
 */

Contact::Contact(const string &nom, const string &pre, const string &entr,const string &mail ,const string &tele,const string &photo, string &date,string &datee)
{
    this->setNom(nom);
    this->setPrenom(pre);
    this->setEntreprise(entr);
    this->setMail(mail);
    this->setTelephone(tele);
    this->setPhoto(photo);
    this->setDateC(date);
    this->dateE=datee;
}
/**
 * @brief Contact::~Contact destructeur de la classe par defaut pour libere l'espace memoire reserver dynamiquement
 */
Contact::~Contact()
{

}
/**
 * @brief Contact::getId
 * @return recuperer l'id du contact
 */
string Contact::getId()const
{
    return this->id;
}
/**
 * @brief Contact::getNom accesseur en lecture
 * @return récuperé le nom du contact
 */
string Contact::getNom() const
{
    return this->nom;
}

/**
 * @brief Contact::getPrenom  accesseur en lecture
 * @return récuperé le prénom du contact
 */
string Contact::getPrenom() const
{
    return prenom;
}
/**
 * @brief Contact::getEntreprise accesseur en lecture
 * @return récuperé l'entreprise du contact
 */
string Contact::getEntreprise() const
{
    return entreprise;
}
/**
 * @brief Contact::getMail accesseur en lecture
 * @return récuperé l'adresse mail du contact
 */
string Contact::getMail() const
{
    return mail;
}
/**
 * @brief Contact::getTelephone
 * @return récuperé le telephone du contact
 */
string Contact::getTelephone() const
{
    return telephone;
}
/**
 * @brief Contact::getPhoto accesseur en lecture
 * @return récuperé le chemin de la photo en string
 */
string Contact::getPhoto() const
{
    return photo;
}
/**
 * @brief Contact::getDateC accesseur en lecture
 * @return récuperé la date de creation du contact comme un objet de type date (classe Date )
 */
string Contact::getDateC() const
{
    return dateC;
}
/**
 * @brief Contact::getListeInter accesseur en lecture
 * @return récuperé la liste des interactions d'un contact (l'instance courante)
 */
list<Interactions> Contact::getListeInter() const
{
    return this->gestionInter.getList();
}
string Contact::getDateE() const
{
    return dateE;
}
/**
 * @brief Obtient la date de création de l'objet Contact.
 *
 * @return La structure sdateAuto représentant la date de création.
 */
struct sdateAuto Contact::getDatecretion()const
{
return this->dateCreation;
}
/**
 * @brief Contact::setNom accesseur en écriture
 * @param nom : modifier le nom par le parametre passer en parametre
 */
void Contact::setNom(const string &nom)
{
    this->nom=nom;
}
/**
 * @brief Contact::setId
 * @param id  modifier l'id du contact
 */
void Contact::setId(const string &id)
{
    this->id=id;
}
/**
 * @brief Contact::setPrenom accesseur en écriture
 * @param pre : modifier le prénom par le parametre passer en parametre
 */
void Contact::setPrenom(const string &pre)
{
    this->prenom=pre;
}
/**
 * @brief Contact::setEntreprise accesseur en écriture
 * @param entr : modifier l'entreprise par le parametre passer en parametre
 */
void Contact::setEntreprise(const string &entr)
{
    this->entreprise=entr;
}
/**
 * @brief Contact::setMail accesseur en écriture
 * @param mail : modifier m'adresse mail ( l'instance courante)
 */
void Contact::setMail(const string &mail)
{
    this->mail=mail;
}
/**
 * @brief Contact::setTelephone accesseur en écriture
 * @param tel : modifier le telephone du contact( l'instance courante)
 */
void Contact::setTelephone(const string &tel)
{
    this->telephone=tel;
}
/**
 * @brief Contact::setPhoto accesseur en écriture
 * @param photoo: modifier la photo  du contact  ( l'instance courante)
 */
void Contact::setPhoto(const string &photo)
{
    this->photo=photo;
}
/**
 * @brief Contact::setDateC accesseur en écriture
 * @param date : modifier la date de modification
 */
void Contact::setDateE(const string &d)
{
    this->dateE=d;
}
/**
 * @brief Contact::setDateC
 * @param date modifier la date de creation
 */
void Contact::setDateC( const string &date)
{
    this->dateC=date;
}
/**
 * @brief Définit la date de création pour l'objet Contact.
 *
 * Cette fonction utilise la date actuelle du système pour définir la date de création
 * de l'objet Contact. Elle extrait la date actuelle sous la forme d'un jour, d'un mois
 * et d'une année, puis les attribue à l'objet dateCreation de la classe Contact.
 *
 * Remarque : La fonction utilise des types de données spécifiques pour représenter la
 * date (day_point, year_month_day) qui doivent être définis dans une bibliothèque
 * tierce ou personnalisée.
 */
void Contact::setDatecreation()
{
    day_point dp = floor<days>(system_clock::now());
    auto ymd = year_month_day{dp};
    this ->dateCreation.jour = ymd.day();
    this -> dateCreation.mois = ymd.month();
    this -> dateCreation.annee = ymd.year();
}
/**
 * @brief Définit la date de modification pour l'objet Contact.
 *
 * Cette fonction utilise la date actuelle du système pour définir la date de modification
 * de l'objet Contact. Elle extrait la date actuelle sous la forme d'un jour, d'un mois
 * et d'une année, puis les attribue à l'objet dateModi de la classe Contact.
 *
 * Remarque : La fonction utilise des types de données spécifiques pour représenter la
 * date (day_point, year_month_day) qui doivent être définis dans une bibliothèque
 * tierce ou personnalisée.
 */
void Contact::setDatemodi()
{
    day_point dp = floor<days>(system_clock::now());
    auto ymd = year_month_day{dp};
    this ->dateModi.jour = ymd.day();
    this -> dateModi.mois = ymd.month();
    this -> dateModi.annee = ymd.year();
}
/**
 * @brief Contact::addInter methode permet d'ajouter une interaction dans la liste des interactions de ( l'instance courante)
 * @param I : l'interaction a ajouter
 */
void Contact::addInter(const Interactions &I)
{
    this->gestionInter.addInter(I);
}

/**
 * @brief Convertit la date de création de l'objet Contact en une chaîne de caractères au format JJ/MM/AAAA.
 *
 * @return La date de création formatée sous forme de chaîne de caractères (JJ/MM/AAAA).
 */
string Contact::ConvertDatec()
{
     return to_string(this->dateCreation.jour.operator unsigned int())+"/"+to_string(this->dateCreation.mois.operator unsigned int())+"/"+to_string(this->dateCreation.annee.operator int());
}
/**
 * @brief Convertit la date de modification de l'objet Contact en une chaîne de caractères au format JJ/MM/AAAA.
 *
 * @return La date de modification formatée sous forme de chaîne de caractères (JJ/MM/AAAA).
 */
string Contact::ConvertDatem()
{
     return to_string(this->dateModi.jour.operator unsigned int())+"/"+to_string(this->dateModi.mois.operator unsigned int())+"/"+to_string(this->dateModi.annee.operator int());
}
/**
 * @brief operator << operateur de flux surchargé pour affiche un conatct
 * @param os variable de type ostream qui dirige le flux de sortie
 * @param C le contact qu'on va affiche
 * @return on retourne le flux de sortie
 */
ostream & operator<<(ostream &os ,const Contact &C)
{

    os<<C.getNom()<<" "<<C.getPrenom()<<"\n"<<C.getEntreprise()<<"\n"<<C.getMail()<<"\n"<<C.getTelephone()<<"\n"<<C.getPhoto()<<"\n"<<C.getDateC();
    return os;
}
/**
 * @brief Contact::operator == on compare deux contact (l'instance courante avec un autre passer en parametre )
 * @param C contact passer en parametre a comparer
 * @return boolean suivant le resultat de la comparaison
 */
bool Contact::operator==(const Contact &C) const
{
    if(getNom()==C.getNom())
        if(getPrenom()==C.getPrenom())
            if(getEntreprise()==C.getEntreprise())
                if(getDateC()==C.getDateC())
                    if(getMail()==C.getMail())
                        if(getPhoto()==C.getPhoto())
                            if(getTelephone()==C.getTelephone())
                                if(getListeInter()==C.getListeInter())
                                    return true;
    return false;
}
/**
 * @brief Contact::removeInter supprimer un interaction parmis les interactions du contact (l'instance courante )
 * @param i : interaction a supprimé
 */
void Contact ::  removeInter(const Interactions &i)
{
    this->gestionInter.removeInter(i);
}
/**
 * @brief Contact::editInter modifier le contenue d'une interaction parmis
 * @param l : l'interaction qu'il faut modifier
 * @param c :la nouvelle valeur du  contenu a mettre
 */
void Contact::editInter(const Interactions &l, const string &c)
{
    this->gestionInter.editInter(l,c);
}
/**
 * @brief Contact::editInter modifier la date d'un todo d'une interaction parmis les interactions du contact (l'instance courante)
 * @param l : l'interaction dont appartient la todo
 * @param t : todo qui conteint la date a changé  et la tache
 * @param d :  la nouvelle date
 */
void Contact::editInterdt(const Interactions &l,const todo &t,const string&d)
{
    this->gestionInter.editInterdt(l,t,d);
}
/**
 * @brief Contact::editInter modifier la tache d'un todo d'une interaction parmis les interactions du contact (l'instance courante)
 * @param l : l'interaction dont appartient la todo
 * @param t : todo qui conteint la date et la tache  a changé
 * @param d : la nouvelle tache
 */
void Contact::editInter(const Interactions &l, const todo &t,const string&d)
{
this->gestionInter.editInter(l,t,d);
}
/**
 * @brief Contact::removeTodofromInter supprimer un todo d'une interaction parmis les interactions d'un contact (on fait l'appel de removetodo qui supprime un todo )
 * @param i : interaction qui contient le todo qu'il faut supprimer
 * @param t : todo qu'il faut supprimer^
 */
void Contact::removeTodofromInter(const Interactions &i,const todo& t)
{
    this->gestionInter.removeTodofromInter(i,t);
}

