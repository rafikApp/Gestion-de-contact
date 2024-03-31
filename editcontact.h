#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <QWidget>
#include"contact.h"
namespace Ui {
class editContact;
}

class editContact : public QWidget
{
    Q_OBJECT

public:
    explicit editContact(QWidget *parent = nullptr);
    ~editContact();

signals:
    void sendE(QString,QString,QString,QString,QString,QString);
    void suppriC();
public slots:
    void affichCm(Contact *);
    void on_modifier_clicked();

    void on_supprimer_clicked();

private slots:
    void on_photo_clicked();

    void on_pushButton_clicked();

private:
    Ui::editContact *ui;
    Contact *c;
    QString nvpath;
    bool clicked=false;
};

#endif // EDITCONTACT_H
