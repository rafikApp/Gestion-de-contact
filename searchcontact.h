#ifndef SEARCHCONTACT_H
#define SEARCHCONTACT_H

#include <QWidget>
#include"contact.h"

namespace Ui {
class searchContact;
}

class searchContact : public QWidget
{
    Q_OBJECT

public:
    explicit searchContact(QWidget *parent = nullptr);
    ~searchContact();
signals:
    void searchByC(QString,int);


private slots:
    void on_radioButton_2_clicked();

    void on_radioButton_clicked();
     void displayError();
    void on_radioButton_3_clicked();
    void on_choixEdit_textEdited(const QString &arg1);

    void on_chercher_clicked();
    void affichCc(Contact *);
    void affichlistC(list<Contact *>);
private:
    Ui::searchContact *ui;
    int nbr;
};

#endif // SEARCHCONTACT_H
