#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"bdd.h"
#include"displaycontact.h"
#include"searchcontact.h"
#include"addcontact.h"
#include"addinteraction.h"


QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    bdd  *bd;
    displayContact  *dc;
    searchContact *sc;
    addContact *ac;
    addInteraction *ai;
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void remplirList();

signals:
    void searchNb();//chercher le nombre de contact
    void selectid(string);
    void searchCbetween(QString,QString);
    void sendDateInter(string,QString,QString);
    void remplirL();

private slots:
    void on_actionAjouter_un_contact_triggered();
    void affichNb(int);//afficher le nb de contact
    void modifierListC();

    void on_listWidget_itemDoubleClicked();

    void on_actionRechercher_un_contact_triggered();

    void on_ajouter_clicked();

    void on_display_clicked();
    void displayInter(list<Interactions *>,Contact *);
    void displayError(string,Contact *);

    void on_todo_clicked();
    void displayIntertodo(list<Interactions *>,Contact *);
    void displayErrortodo(string,Contact *);
    void on_appliquer_clicked();
    void affichContacts(list<Contact*>);
    void noContact();
    void on_pushButton_clicked();
    void affichInter2date(list<Interactions *>,Contact *);
    void noInter(string,Contact *);
    void modiList(list<Contact *>);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
