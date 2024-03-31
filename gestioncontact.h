#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H

#include "contact.h"
#include<list>
#include<string>
using namespace std;
 //l'explication de tout les membres de la classe ont etaient expliqué dans le cpp avec doxygene
class GestionContact
{
private:
    list<Contact> listeContact;
public:
    GestionContact();

    list<Contact> getlisteContact() const;

    void addContact(const Contact &);
    void removeContact(const Contact &);
    void editContact(const Contact & ,const string & ,const string & );
    void editContactInte(const Contact&,const Interactions&,const string &);
    void editContactInteTodo(const Contact&,const Interactions&,const todo&,const string &);
    void editContactInteTododt(const Contact&,const Interactions&,const todo&,const string &);
    string afficher();


    friend ostream & operator<<(ostream & ,const GestionContact &);

};

#endif // GESTIONCONTACT_H
