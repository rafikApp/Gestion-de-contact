#include "gestioncontact.h"

/**
 * @brief GestionContact::GestionContact constructeur par defaut
 */
GestionContact::GestionContact()
{

}
/**
 * @brief GestionContact::getlisteContact accesseur en lecture
 * @return la liste des contacts
 */
list<Contact> GestionContact::getlisteContact() const
{
    return this->listeContact;
}
/**
 * @brief GestionContact::addContact methode pour ajouter un contact dans la liste des contacts
 * @param C : le contact a ajouter dans la liste
 */
void GestionContact::addContact(const Contact &C)
{
    this->listeContact.push_back(C);
}
/**
 * @brief GestionContact::removeContact : methode pour supprimer un contact dans la liste des contacts
 * @param C le conatxct a supprimer
 */
void GestionContact::removeContact(const Contact &C)
{
    for (auto it = listeContact.begin(); it != listeContact.end(); )
    if ( it->getNom() == C.getNom() && it->getPrenom() == C.getPrenom() )
    {
    it = listeContact.erase(it);
    }
    else
    ++it;
}
/**
 * @brief GestionContact::afficher methode d'affichage uytiliser dans la classe mainwindow pour afficher dans un textedit
 * @return la liste des noms et prenoms des contacts
 */
string GestionContact::afficher()
{
    string s="";
        for(auto it=listeContact.begin();it!=listeContact.end();)
        {
            s=s+it->getNom()+" "+it->getPrenom()+"\n";
            it++;
        }
        return s;
}
/**
 * @brief GestionContact::editContact modifier les attributs d'un contact
 * @param C : le contact a modifier
 * @param modif : l'attribut a modifier
 * @param nvmodif :  la nouvelle valeur pour l'attribut
 */
void GestionContact::editContact(const Contact &C,const string &modif,const string &nvmodif)
{
    for (auto it =this->listeContact.begin(); it !=this->listeContact.end(); )
    {
    if ( it->getNom() == C.getNom() && it->getPrenom() == C.getPrenom() )
    {
        if(modif=="entreprise")
        {
            it->setEntreprise(nvmodif);
        }
        if(modif=="mail")
        {
            it->setMail(nvmodif);
        }
        if(modif=="telephone")
        {
            it->setTelephone(nvmodif);
        }
        if(modif=="photo")
        {
            it->setPhoto(nvmodif);
        }
    }
    ++it;
    }
}
/**
 * @brief operator << :operateur de flux surchargé pour afficher la la liste des contacts
 * @param os : variable de type ostream qui dirige le flux de sortie
 * @param Gc : la liste des contacts a afficher
 * @return :  flux de sortie
 */
ostream & operator<<(ostream &os ,const GestionContact &Gc)
{
        for (auto it = Gc.listeContact.begin(); it != Gc.listeContact.end(); )
        {
            os<<*it;
            it++;
        }
        return os;

}
/**
 * @brief GestionContact::editContactInte : modifier une interaction parmis les interactions d'un contact parmis les contacts qui existent
 * @param c : le contact dont ca interaction sera  modifier
 * @param i : l'interaction a modifier
 * @param contenu : la nouvelle valeur a donne pour le contenu de l'interaction a modifier
 */
void GestionContact::editContactInte(const Contact& c,const Interactions& i,const string & contenu)
{
    auto it = listeContact.begin();
    bool found = false;
    while((it!=listeContact.end()) && (found == false))
    {
        if(*it == c)
        {
            found = true;
            it->editInter(i,contenu);
        }
        else
            ++it;
    }
}
/**
 * @brief GestionContact::editContactInteTodo modifier un todo d'une interaction d'un contact parmis les contacts qui existent
 * @param c : le contact dont le todo sera modifier
 * @param i : l'interaction dont le todo sera modifier
 * @param todo : le todo qui sera modifier
 * @param tache : la nouvelle valeur de la tache du todo modifier
 */
void GestionContact::editContactInteTodo(const Contact& c,const Interactions& i,const todo& todo,const string & tache)
{
    auto it = listeContact.begin();
    bool found = false;
    while((it!=listeContact.end()) && (found == false))
    {
        if(*it == c)
        {
            found = true;
            it->editInter(i,todo,tache);
        }
        else
            ++it;
    }
}
/**
 * @brief GestionContact::editContactInteTodo modifier un todo d'une interaction d'un contact parmis les contacts qui existent
 * @param c : le contact dont le todo sera modifier
 * @param i l'interaction dont le todo sera modifier
 * @param todo : le todo qui sera modifier
 * @param d  : la nouvelle valeur de la date du todo modifier
 */
void GestionContact::editContactInteTododt(const Contact& c,const Interactions& i,const todo& todo,const string & d)
{
    auto it = listeContact.begin();
    bool found = false;
    while((it!=listeContact.end()) && (found == false))
    {
        if(*it == c)
        {
            found = true;
            it->editInter(i,todo,d);
        }
        else
            ++it;
    }
}



