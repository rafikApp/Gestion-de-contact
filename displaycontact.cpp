#include "displaycontact.h"
#include "ui_displaycontact.h"

/**
 * @brief Constructeur de la classe displayContact.
 * @param parent Pointeur vers le widget parent (QWidget).
 */
displayContact::displayContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::displayContact)
{
    ui->setupUi(this);
}
/**
 * @brief Destructeur de la classe displayContact.
 * Libère la mémoire utilisée par l'interface utilisateur.
 */
displayContact::~displayContact()
{
    delete ui;
}
/**
 * @brief Affiche les détails d'un contact dans l'interface utilisateur.
 * @param c Pointeur vers l'objet Contact à afficher.
 */
void displayContact::affichC(Contact *c)
{
    ui->nom->setText(QString::fromStdString(c->getNom()));
    ui->prenom->setText(QString::fromStdString(c->getPrenom()));
    ui->email->setText(QString::fromStdString(c->getMail()));
    ui->entreprise->setText(QString::fromStdString(c->getEntreprise()));
    ui->telephone->setText(QString::fromStdString(c->getTelephone()));
    ui->dateC->setText(QString::fromStdString(c->getDateC()));
    ui->dateM->setText(QString::fromStdString(c->getDateE()));
    string img=c->getPhoto();
    QPixmap pixmap(img.c_str());
    QIcon ButtonIcon(pixmap);
    ui->photo->setIcon(ButtonIcon);
    ui->photo->setIconSize(pixmap.rect().size());
    dc=c;
}
/**
 * @brief Gère l'événement du clic sur le bouton "Modifier".
 * Ouvre la fenêtre pour éditer les détails du contact.
 * Émet des signaux pour établir une communication entre les fenêtres.
 */
void displayContact::on_modifier_clicked()
{
    ec=new editContact();
    ec->show();
    connect(this,SIGNAL(sendCedit(Contact *)),ec,SLOT(affichCm(Contact *)));//envoie du contact a editContact
    connect(ec,SIGNAL(sendE(QString,QString,QString,QString,QString,QString)),this,SLOT(reciveE(QString,QString,QString,QString,QString,QString)));
    connect(ec,SIGNAL(suppriC()),this,SLOT(deleteeC()));

    emit sendCedit(dc);

}
/**
 * @brief Gère la suppression du contact.
 * Émet un signal pour supprimer le contact actuel, ferme la fenêtre d'affichage
 * et émet un signal pour mettre à jour la liste des contacts.
 */
void displayContact::deleteeC()
{
    emit deleteC();
    this->close();
    emit modifierList();

}
/**
 * @brief Reçoit les détails édités d'un contact.
 * Émet un signal pour envoyer les modifications à la base de données.
 * @param nom Le nouveau nom du contact.
 * @param prenom Le nouveau prénom du contact.
 * @param entreprise La nouvelle entreprise du contact.
 * @param email Le nouvel email du contact.
 * @param telephone Le nouveau numéro de téléphone du contact.
 * @param photo La nouvelle photo du contact.
 */
void displayContact::reciveE(QString nom,QString prenom,QString entreprise,QString email,QString telephone,QString photo)
{
    emit sendEbdd(nom,prenom,entreprise,email,telephone,photo);
}
/**
 * @brief Gère l'événement du clic sur le bouton "Fermer".
 * Ferme la fenêtre d'affichage et émet un signal pour mettre à jour la liste des contacts.
 */
void displayContact::on_pushButton_clicked()
{
    this->close();
    emit modifierList();
}

