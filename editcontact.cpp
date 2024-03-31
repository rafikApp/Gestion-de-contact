#include "editcontact.h"
#include "ui_editcontact.h"
#include"QFileDialog"

/**
 * @brief Constructeur de la classe editContact.
 * @param parent Pointeur vers le widget parent (QWidget).
 */
editContact::editContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editContact)
{
    ui->setupUi(this);
}
/**
 * @brief Destructeur de la classe editContact.
 * Ne libère pas la mémoire de l'interface utilisateur ni de l'objet Contact.
 */
editContact::~editContact()
{

}
/**
 * @brief Affiche les détails d'un contact dans l'interface d'édition.
 * @param c Pointeur vers l'objet Contact à afficher.
 */
void editContact::affichCm(Contact *c)
{
    this->c=c;
    ui->nomEdit->setText(QString::fromStdString(c->getNom()));
    ui->prenomEdit->setText(QString::fromStdString(c->getPrenom()));
    ui->entrepriseEdit->setText(QString::fromStdString(c->getEntreprise()));
    ui->emailEdit->setText(QString::fromStdString(c->getMail()));
    ui->teleEdit->setText(QString::fromStdString(c->getTelephone()));

}
/**
 * @brief Gère l'événement du clic sur le bouton "Modifier".
 * Émet un signal avec les modifications apportées au contact.
 */
void editContact::on_modifier_clicked()
{


    if(clicked)
        emit sendE(ui->nomEdit->text(),ui->prenomEdit->text(),ui->entrepriseEdit->text(),ui->emailEdit->text(),ui->teleEdit->text(),nvpath);
    else
        emit sendE(ui->nomEdit->text(),ui->prenomEdit->text(),ui->entrepriseEdit->text(),ui->emailEdit->text(),ui->teleEdit->text(),QString::fromStdString(c->getPhoto()));
    this->close();

}

/**
 * @brief Gère l'événement du clic sur le bouton "Supprimer".
 * Émet un signal pour supprimer le contact.
 * Ferme la fenêtre d'édition.
 */
void editContact::on_supprimer_clicked()
{
    //this->close();
    emit suppriC();
    this->close();
}
/**
 * @brief Gère l'événement du clic sur le bouton "Photo".
 * Ouvre une fenêtre de dialogue pour sélectionner une photo.
 */

void editContact::on_photo_clicked()
{
    this -> nvpath =QFileDialog::getOpenFileName(this, "Photo", "//home");
    if(!nvpath.isEmpty())
        clicked=true;
    else
        clicked=false;
}

/**
 * @brief Gère l'événement du clic sur le bouton "Fermer".
 * Ferme la fenêtre d'édition.
 */
void editContact::on_pushButton_clicked()
{
    this->close();
}

