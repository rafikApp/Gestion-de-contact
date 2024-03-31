#ifndef DISPLAYCONTACT_H
#define DISPLAYCONTACT_H

#include <QWidget>
#include"contact.h"
#include"editcontact.h"
namespace Ui {
class displayContact;
}

class displayContact : public QWidget
{
    Q_OBJECT

public:
    explicit displayContact(QWidget *parent = nullptr);
    ~displayContact();

public slots:
    void affichC(Contact *);
    void on_modifier_clicked();
    void on_pushButton_clicked();
    void reciveE(QString,QString,QString,QString,QString,QString);
    void deleteeC();


signals:
    void sendCedit(Contact *);
    void sendEbdd(QString,QString,QString,QString,QString,QString);
    void deleteC();
    void modifierList();
private:
    Ui::displayContact *ui;
    Contact *dc;
    editContact *ec;
};

#endif // DISPLAYCONTACT_H
