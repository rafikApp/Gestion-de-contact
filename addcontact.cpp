#include "addcontact.h"
#include "ui_addcontact.h"
#include"QFileDialog"
#include"QMessageBox"

/**
 * @brief addContact::addContact constructeur de la classe
 * @param parent :  pour spécifier le widget parent (dans une structure d'arborescence de widgets)
 */
addContact::addContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addContact)
{
    ui->setupUi(this);
    ui->teleEdit->setPlaceholderText("0612141536");
}


/**
 * @brief Destructeur de la classe addContact
 * Libère la mémoire utilisée par l'interface utilisateur
 */
addContact::~addContact() {
    delete ui;
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Parcourir"
 * Ouvre une boîte de dialogue pour sélectionner une photo
 */
void addContact::on_parcourir_clicked() {
    this->path = QFileDialog::getOpenFileName(this, "Photo", "//home");
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Valider"
 * Valide et enregistre un nouveau contact
 */
void addContact::on_valider_clicked() {
    if ((ui->nomEdit->text() != "") && (ui->prenomEdit->text() != "") &&
        (ui->emailEdit->text() != "") && (ui->entrepriseEdit->text() != "") &&
        (ui->teleEdit->text() != "") && (this->path.toStdString() != "")) {

        QRegExp regex("\\d+");
        QString Telephone = ui->teleEdit->text();

        if (Telephone.contains(regex) && Telephone.length() == 10) {
            Contact *c = new Contact();
            c->setNom((ui->nomEdit->text()).toStdString());
            c->setPrenom((ui->prenomEdit->text()).toStdString());
            c->setEntreprise((ui->entrepriseEdit->text()).toStdString());
            c->setMail((ui->emailEdit->text()).toStdString());
            c->setPhoto(this->path.toStdString());
            c->setTelephone((ui->teleEdit->text()).toStdString());
            // c->setDatecreation();
            // c->setDatemodi();
            emit enregistrerContact(c);
            emit modifierList();
            this->close();
        } else {
            QMessageBox::warning(this, "Attention", "Numéro de téléphone invalide.");
        }

    } else {
        QMessageBox messageBox;
        messageBox.setText("Il faut remplir tous les champs");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setWindowTitle("Warning");
        messageBox.exec();
    }
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Annuler"
 * Ferme la fenêtre d'ajout de contact
 */
void addContact::on_Annuler_clicked() {
    this->close();
}

