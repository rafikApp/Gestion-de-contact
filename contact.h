#ifndef CONTACT_H
#define CONTACT_H
#include<string>
#include<list>
#include "interactions.h"
#include"gestioninteraction.h"
#include "sdateAuto.h"
#include "date/date.h"
#include "date/chrono_io.h"

using namespace date;
using namespace std::chrono;
using day_point = std::chrono::time_point<std::chrono::system_clock, days>;

using namespace std;



 //l'explication de tout les membres de la classe ont etaient expliqué dans le cpp avec doxygene
class Contact
{
private:
    string nom;
    string prenom;
    string entreprise;
    string mail;
    string telephone;
    string photo;
    string dateC;
    string dateE;
    string id="";
    struct sdateAuto dateCreation;
    struct sdateAuto dateModi;
    GestionInteraction gestionInter;
   // list<Interactions> listeInter;

public:

    Contact();
    Contact(const string &,const string &,const string &,const string &,const string &,const string &, string &,string &);
    ~Contact();

    string getNom() const;
    string getPrenom() const;
    string getEntreprise() const;
    string getMail() const;
    string getTelephone() const;
    string getPhoto() const;
    string getDateC() const;
    string getDateE() const;
    string getId()const;
    struct sdateAuto getDatecretion() const;
    struct sdateAuto getDatemodi()const;
    list<Interactions> getListeInter() const;

    void setNom(const string &);
    void setPrenom(const string &);
    void setEntreprise(const string &);
    void setMail(const string &);
    void setTelephone(const string &);
    void setPhoto(const string &);
    void setDateC( const string &);
    void setDateE(const string &);
    void setDatecreation();
    void setDatemodi();
    void setId(const string&);

    void addInter(const Interactions &);
    void removeInter(const Interactions &);
    void editInter(const Interactions &, const string &);
    void editInterdt(const Interactions &,const todo&,const string&);
    void editInter(const Interactions &, const todo &,const string&);
    void removeTodofromInter(const Interactions &,const todo&);

    //fonction
    string ConvertDatec();
    string ConvertDatem();
    friend ostream & operator<<(ostream & ,const Contact &);
    bool operator==(const Contact &)const;

};

#endif // CONTACT_H
