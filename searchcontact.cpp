#include "searchcontact.h"
#include "ui_searchcontact.h"

/**
 * @brief Constructeur de la classe searchContact.
 * @param parent Pointeur vers le widget parent (si disponible).
 * @note Ce constructeur initialise l'interface utilisateur de la fenêtre de recherche de contacts.
 */
searchContact::searchContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchContact)
{
    ui->setupUi(this);
    ui->dateEdit->setEnabled(false);
    ui->choixEdit->setEnabled(false);
    ui->chercher->setEnabled(false);
    ui->textEdit->setReadOnly(true);


}
/**
 * @brief Destructeur de la classe searchContact.
 * @note Libère la mémoire allouée pour l'interface utilisateur.
 */
searchContact::~searchContact()
{
    delete ui;
}
/**
 * @brief Action déclenchée lors du clic sur le bouton radio 2.
 * Active l'édition de date et la recherche selon le choix.
 * @note Active l'édition de date, désactive l'édition de choix,
 * et autorise la recherche pour le type de recherche 2.
 */
void searchContact::on_radioButton_2_clicked()
{
ui->choixEdit->setEnabled(false);
ui->dateEdit->setEnabled(true);
ui->chercher->setEnabled(true);
nbr=2;

}

/**
 * @brief Action déclenchée lors du clic sur le bouton radio.
 * Active l'édition de choix et désactive l'édition de date.
 * Désactive le bouton de recherche si l'édition de choix est vide.
 * Définit le type de recherche à 1.
 */
void searchContact::on_radioButton_clicked()
{
    ui->choixEdit->setEnabled(true);
    ui->dateEdit->setEnabled(false);
    if(ui->choixEdit->text().isEmpty())
         ui->chercher->setEnabled(false);

    nbr=1;
}

/**
 * @brief Action déclenchée lors du clic sur le bouton radio.
 * Active l'édition de choix et désactive l'édition de date.
 * Désactive le bouton de recherche si l'édition de choix est vide.
 * Définit le type de recherche à 3.
 */
void searchContact::on_radioButton_3_clicked()
{
    ui->choixEdit->setEnabled(true);
    ui->dateEdit->setEnabled(false);
    if(ui->choixEdit->text().isEmpty())
         ui->chercher->setEnabled(false);
    nbr=3;
}

/**
 * @brief Action déclenchée lors de la modification du texte dans l'édition de choix.
 * Active le bouton de recherche si le texte n'est pas vide, sinon le désactive.
 *
 * @param arg1 Le texte édité dans l'édition de choix.
 */

void searchContact::on_choixEdit_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())
         ui->chercher->setEnabled(true);
    else
        ui->chercher->setEnabled(false);
}

/**
 * @brief Action déclenchée lors du clic sur le bouton de recherche.
 * Efface le texte dans l'éditeur de texte, puis émet un signal de recherche
 * en fonction du type de recherche spécifié.
 * Si le type de recherche n'est pas égal à 2, émet un signal de recherche avec le texte de choix.
 * Si le type de recherche est égal à 2, émet un signal de recherche avec le texte de date.
 */
void searchContact::on_chercher_clicked()
{
    ui->textEdit->setText(" ");
    if(nbr!=2)
        emit searchByC(ui->choixEdit->text(),nbr);
    if(nbr==2)
        emit searchByC(ui->dateEdit->text(),nbr);
}
/**
 * @brief Affiche les détails d'un contact dans l'éditeur de texte.
 * @param c Un pointeur vers l'objet Contact à afficher.
 * Affiche les détails du contact (nom, prénom, entreprise, email, téléphone, date de création)
 * dans l'éditeur de texte.
 */
void searchContact::affichCc(Contact *c)
{
    ui->textEdit->append(QString::fromStdString("Nom: "+c->getNom()));
    ui->textEdit->append(QString::fromStdString("\nPrenom: "+c->getPrenom()));
    ui->textEdit->append(QString::fromStdString("\nEntreprise: "+c->getEntreprise()));
    ui->textEdit->append(QString::fromStdString("\nMail: "+c->getMail()));
    ui->textEdit->append(QString::fromStdString("\nTelephone: "+c->getTelephone()));
    ui->textEdit->append(QString::fromStdString("\nDate de creation: "+c->getDateC()));
}
/**
 * @brief Affiche une liste de contacts dans l'éditeur de texte.
 * @param l Liste des pointeurs vers des objets Contact à afficher.
 * Affiche les détails de chaque contact de la liste (nom, prénom, entreprise, email, téléphone, date de création)
 * dans l'éditeur de texte, en ajoutant un numéro de contact à chaque élément.
 */
void searchContact::affichlistC(list<Contact *> l)
{
    ui->textEdit->clear();
    unsigned j=1;
    QString s;
    for(Contact *i:l)
    {
        ui->textEdit->append(QString::fromStdString("\n    Contact N°: ")+s.setNum(j));

        affichCc(i);
        j++;
    }
}
/**
 * @brief Affiche un message d'erreur si aucun contact n'est trouvé.
 * Efface le contenu précédent de l'éditeur de texte, puis affiche un message indiquant
 * qu'aucun contact n'a été trouvé suite à une recherche.
 */
void searchContact::displayError()
{
ui->textEdit->setText(" ");
ui->textEdit->append(QString::fromStdString("Contact introuvable "));
}
