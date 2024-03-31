#ifndef BDD_H
#define BDD_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include"contact.h"
#include"todo.h"

class bdd : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;
    Contact *c;
    Interactions *I;
    string idC="";
    string idI="";
    todo *tache;



public:
    explicit bdd(QObject *parent = nullptr);
    ~bdd();
    void exportJson(const QString &);


signals:
    void sendNb(int);//envoyer le nombre de contact a la mainwindow
    void sendC(Contact *);
    void findC(Contact *);
    void errorM();
    void sendCinter(list<Interactions *>,Contact *);
    void errorM(string,Contact *);
    void findlistC(list<Contact *>);
    void sendLc(list<Contact*>);
    void noContact();
    void EditData();
    void listInter2date(list<Interactions*>l,Contact *);
    void noInter(string,Contact *);
    void remplirLbd(list<Contact *>);
    //void modifierList();


public slots:
    void ajoutContact(Contact *);//ajouter un nouveau contact dans la base de donne
    void trouverNb();//recuperer le nombre de contact de la base de la donnee
    void recupCid(string );//recuperer le contact par id
    void reciveE(QString,QString,QString,QString,QString,QString);
    void deleteCbd();
    void searchNameC(QString,int);
    void EditID(string);
    void insertInter(Interactions *);
    void insertTodo(list<todo *>);
    void searchIDinter(string);
    void searchIDintertodo(string);
    void searchCbetween(QString,QString);
    void generatJson();
    void search2DInter(string,QString,QString);
    void remplirList();
    //void envoyerContact(Contact *);
};

#endif // BDD_H
