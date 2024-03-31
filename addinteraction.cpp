/**
 * @file addinteraction.h
 * @brief Déclaration de la classe addInteraction
 */

#include "addinteraction.h"
#include "ui_addinteraction.h"
#include<QRegularExpression>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include<QDebug>
#include<QMessageBox>
#include<QDate>

/**
 * @brief Constructeur de la classe addInteraction
 * @param parent Widget parent
 */
addInteraction::addInteraction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addInteraction)
{
    ui->setupUi(this);
    ui->save->setEnabled(false);
    ui->textEdit->setPlaceholderText("@todo todo @date dd/mm/yyyy");
}

/**
 * @brief Destructeur de la classe addInteraction
 * Libère la mémoire utilisée par l'interface utilisateur
 */
addInteraction::~addInteraction()
{
    delete ui;
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Nouveau"
 * Réinitialise les champs pour une nouvelle interaction
 */
void addInteraction::on_pushButton_3_clicked()
{
    ui->interactionEdit->clear();
    ui->addtodo->setEnabled(false);
    ui->label_2->clear();
    ui->interactionEdit->setEnabled(true);
    ui->label_2->setEnabled(true);
    ui->textEdit->setEnabled(false);
    ui->label_3->clear();
    ui->label_4->clear();
   // emit inter(i);
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Enregistrer"
 * Enregistre une nouvelle interaction
 */
void addInteraction::on_save_clicked()
{
    i = new Interactions();
    i->setContenu(ui->interactionEdit->text().toStdString());
    i->setDate(i->ConvertDt());
    emit inter(i);
    ui->save->setEnabled(false);
    ui->label_2->setText("Interaction ajoutée avec succès");
    ui->interactionEdit->setEnabled(false);
    ui->textEdit->setEnabled(true);
    ui->label_3->setText("Veuillez entrer les tâches de cette interaction");
}

/**
 * @brief Slot déclenché lors de la modification du texte dans l'éditeur d'interaction
 * Active ou désactive le bouton "Enregistrer" en fonction de la présence de texte
 * @param arg1 Texte modifié
 */
void addInteraction::on_interactionEdit_textEdited(const QString &arg1)
{
    if (!arg1.isEmpty())
         ui->save->setEnabled(true);
    else
        ui->save->setEnabled(false);
}

/**
 * @brief Slot déclenché lors du changement de texte dans l'éditeur de texte
 * Active ou désactive le bouton "Ajouter une tâche" en fonction du contenu de l'éditeur de texte
 */
void addInteraction::on_textEdit_textChanged()
{
    ui->label_4->clear();

    if (ui->textEdit->toPlainText().isEmpty()) {
            ui->addtodo->setEnabled(false);
        } else {
            ui->addtodo->setEnabled(true);
        }
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Annuler"
 * Ferme la fenêtre d'ajout d'interaction
 */
void addInteraction::on_pushButton_2_clicked()
{
    this->close();
}

/**
 * @brief Slot déclenché lors du clic sur le bouton "Ajouter une tâche"
 * Ajoute une nouvelle tâche extraite du texte et l'envoie
 */
void addInteraction::on_addtodo_clicked()
{
    ui->label_4->clear();
    bool ok=false;
    QString content = ui->textEdit->toPlainText();
    QRegularExpression todoRegex("^@todo (.+?)(?:\\s+@date (.*))?$");
    QRegularExpression dateRegex("^\\d{2}/\\d{2}/\\d{4}$");
    list<todo*> listeTaches;
    QTextStream stream(&content);
    todo* tache;
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (!line.trimmed().startsWith("@todo"))
        {
            continue;
        }
        QRegularExpressionMatch match = todoRegex.match(line);
        if (match.hasMatch())
        {
            tache = new todo();
            QString contenu = match.captured(1);
            QString date = match.captured(2).trimmed();
            if (!date.isEmpty() && !dateRegex.match(date).hasMatch())
            {
                 date = QString::fromStdString(tache->ConvertDate());
            }
            if (date.isEmpty())
            {
                date = QString::fromStdString(tache->ConvertDate());
            }

            tache->setTache(contenu.toStdString());
            tache->setdateT(date.toStdString());
            listeTaches.push_back(tache);
            ok=true;
        }
    }
    emit sendlTodo(listeTaches);
    ui->textEdit->clear();
    if(ok)
         ui->label_4->setText("Tâche ajoutée avec succès");
}
