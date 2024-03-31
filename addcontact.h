#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QWidget>
#include"contact.h"
namespace Ui {
class addContact;
}

class addContact : public QWidget
{
     QString path;
    Q_OBJECT

public:
    explicit addContact(QWidget *parent = nullptr);
    ~addContact();



signals:
     void enregistrerContact(Contact *);
     void modifierList();

private slots:
    void on_parcourir_clicked();

    void on_valider_clicked();

    void on_Annuler_clicked();

private:
    Ui::addContact *ui;
};

#endif // ADDCONTACT_H
