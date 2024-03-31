/**
 * @file mainwindow.h
 * @brief Définition de la classe MainWindow.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"bdd.h"
#include"QSqlQuery"
#include<QMessageBox>


/**
 * @brief Constructeur de la classe MainWindow.
 * @param parent Pointeur vers le widget parent.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bd =new bdd();
    remplirList();
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
}
/**
 * @brief Destructeur de la classe MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Remplit la liste des contacts.
 *        Connecte les signaux et les slots nécessaires pour obtenir et afficher la liste.
 */
void MainWindow::remplirList()
{
    connect(this,SIGNAL(searchNb()),bd,SLOT(trouverNb()));
    connect(bd,SIGNAL(sendNb(int)),this,SLOT(affichNb(int)));
    connect(this,SIGNAL(remplirL()),bd,SLOT(remplirList()));
    connect(bd,SIGNAL(remplirLbd(list<Contact *>)),this,SLOT(modiList(list<Contact *>)));
    emit searchNb();
    emit remplirL();
}
/**
 * @brief Met à jour la liste des contacts dans l'interface.
 * @param l Liste des contacts à afficher.
 */
void MainWindow::modiList(list<Contact *> l)
{
    ui->listWidget->clear();

    for (Contact *c : l)
    {
        ui->listWidget->addItem(QString::fromStdString(c->getId() + "-" + c->getNom() + " " + c->getPrenom()));
    }
}

/**
 * @brief Ouvre la fenêtre pour ajouter un nouveau contact.
 *        Connecte les signaux pour gérer l'ajout et la mise à jour de la liste.
 */
void MainWindow::on_actionAjouter_un_contact_triggered()
{
    ac = new addContact();
    ac->show();
    connect(ac, SIGNAL(enregistrerContact(Contact*)), bd, SLOT(ajoutContact(Contact*)));
    connect(ac, SIGNAL(modifierList()), this, SLOT(modifierListC())); // Mise à jour de la liste
}

/**
 * @brief Affiche le nombre total de contacts.
 * @param total Le nombre total de contacts à afficher.
 */
void MainWindow::affichNb(int total)
{
    ui->total->clear();
    ui->total->setText(QString::number(total));
}

/**
 * @brief Modifie la liste des contacts.
 *        Connecte les signaux pour trouver et afficher le nombre de contacts, puis met à jour la liste.
 */
void MainWindow::modifierListC()
{
    connect(this, SIGNAL(searchNb()), bd, SLOT(trouverNb()));
    connect(bd, SIGNAL(sendNb(int)), this, SLOT(affichNb(int)));
    ui->listWidget->clear();
    remplirList();
    emit searchNb();
}


/**
 * @brief Gère l'événement double-clic sur un élément de la liste des contacts.
 *        Ouvre une fenêtre pour afficher les détails du contact sélectionné et connecte les signaux pour la gestion des opérations sur le contact.
 */
void MainWindow::on_listWidget_itemDoubleClicked()
{
    dc = new displayContact();
    dc->show();
    connect(this, SIGNAL(selectid(string)), bd, SLOT(recupCid(string)));
    connect(bd, SIGNAL(sendC(Contact*)), dc, SLOT(affichC(Contact*)));

    connect(dc, SIGNAL(sendEbdd(QString, QString, QString, QString, QString, QString)), bd, SLOT(reciveE(QString, QString, QString, QString, QString, QString)));

    connect(dc, SIGNAL(deleteC()), bd, SLOT(deleteCbd()));
    connect(dc, SIGNAL(deleteC()), this, SLOT(modifierListC()));
    connect(dc, SIGNAL(modifierList()), this, SLOT(modifierListC())); // Mise à jour de la liste

    // Récupération de l'ID sélectionné
    string l = ui->listWidget->currentItem()->text().toStdString();
    string nv = "";
    bool veri = false;
    for (int i = 0; !veri; i++)
    {
        if (l[i] != '-')
        {
            nv += l[i];
        }
        else
        {
            veri = true;
        }
    }
    emit selectid(nv); // Envoie l'ID du contact sélectionné via un signal à la classe Base de Données
}



/**
 * @brief Ouvre une fenêtre de recherche de contact.
 *        Connecte les signaux pour rechercher et afficher les résultats de la recherche.
 */
void MainWindow::on_actionRechercher_un_contact_triggered()
{
    sc = new searchContact();
    sc->show();
    connect(sc, SIGNAL(searchByC(QString, int)), bd, SLOT(searchNameC(QString, int)));
    connect(bd, SIGNAL(findC(Contact*)), sc, SLOT(affichCc(Contact*)));
    connect(bd, SIGNAL(findlistC(list<Contact*>)), sc, SLOT(affichlistC(list<Contact*>)));
    connect(bd, SIGNAL(errorM()), sc, SLOT(displayError()));
}

/**
 * @brief Ouvre une fenêtre pour ajouter une interaction.
 *        Connecte les signaux pour insérer une nouvelle interaction et ses tâches associées.
 *        Récupère l'ID du contact sélectionné dans la QListWidget.
 * @note Assurez-vous qu'un contact est sélectionné dans la QListWidget avant d'appeler cette fonction.
 */
void MainWindow::on_ajouter_clicked()
{
    ai = new addInteraction();
    ai->show();
    connect(this, SIGNAL(selectid(string)), bd, SLOT(EditID(string)));
    connect(ai, SIGNAL(inter(Interactions*)), bd, SLOT(insertInter(Interactions*)));
    connect(ai, SIGNAL(sendlTodo(list<todo*>)), bd, SLOT(insertTodo(list<todo*>)));

    // Récupération de l'ID du contact sélectionné dans la QListWidget
    string l = ui->listWidget->currentItem()->text().toStdString();
    string id = "";
    bool ok = false;
    for (int i = 0; !ok; i++)
    {
        if (l[i] != '-')
        {
            id += l[i];
        }
        else
        {
            ok = true;
        }
    }
    emit selectid(id); // Envoie l'ID du contact sélectionné via un signal à la classe Base de Données
}


/**
 * @brief Affiche les interactions associées au contact sélectionné dans une fenêtre.
 *        Connecte les signaux pour récupérer les interactions et les afficher.
 * @note Assurez-vous qu'un contact est sélectionné dans la QListWidget avant d'appeler cette fonction.
 */
void MainWindow::on_display_clicked()
{
    connect(this,SIGNAL(selectid(string)),bd,SLOT(searchIDinter(string)));
    connect(bd,SIGNAL(sendCinter(list<Interactions *>,Contact *)),this,SLOT(displayInter(list<Interactions *>,Contact *)));
    connect(bd,SIGNAL(errorM(string,Contact *)),this,SLOT(displayError(string,Contact *)));
    string l=ui->listWidget->currentItem()->text().toStdString();
    string id="";
    bool ok=false;
    for(int i=0;!ok;i++)
    {
        if(l[i]!='-')
        {
            id+=l[i];
        }
        else
        {
            ok=true;
        }
    }
    emit selectid(id);//envoyer l'id du contact qui a été selectionné via un signal à la classe basedonnee
}
/**
 * @brief Affiche les interactions avec leurs tâches associées pour le contact sélectionné.
 *        Connecte les signaux pour récupérer les interactions et les tâches associées et les afficher.
 * @note Assurez-vous qu'un contact est sélectionné dans la QListWidget avant d'appeler cette fonction.
 */
void MainWindow::on_todo_clicked()
{
    connect(this,SIGNAL(selectid(string)),bd,SLOT(searchIDintertodo(string)));
    connect(bd,SIGNAL(sendCinter(list<Interactions *>,Contact *)),this,SLOT(displayIntertodo(list<Interactions *>,Contact *)));
    connect(bd,SIGNAL(errorM(string,Contact *)),this,SLOT(displayErrortodo(string,Contact *)));
    string l=ui->listWidget->currentItem()->text().toStdString();
    string id="";
    bool ok=false;
    for(int i=0;!ok;i++)
    {
        if(l[i]!='-')
        {
            id+=l[i];
        }
        else
        {
            ok=true;
        }
    }
    emit selectid(id);//envoyer l'id du contact qui a été selectionné via un signal à la classe basedonnee
}
/**
 * @brief Affiche les interactions avec leurs tâches associées pour le contact spécifié.
 *        Efface le contenu précédent de l'ui->textEdit et affiche les interactions et leurs tâches associées.
 * @param li Liste des interactions à afficher pour le contact.
 * @param ca Pointeur vers l'objet Contact dont les interactions sont affichées.
 * @note Assurez-vous que les paramètres li et ca ne sont pas nuls pour éviter tout comportement indéfini.
 */
void MainWindow::displayIntertodo(list<Interactions *> li,Contact *ca)
{
    ui->textEdit->clear();
    ui->textEdit->setText(QString::fromStdString("Contact :"+ca->getNom()+" "+ca->getPrenom()+""));
    for(Interactions *i:li)
    {
        ui->textEdit->append(QString::fromStdString("Interaction: "));
        ui->textEdit->append(QString::fromStdString("\t"+i->getContenu()+ " date :"+i->getDate()));
        ui->textEdit->append(QString::fromStdString("Les taches:"));
        for(todo t:i->getListetodo())
        {

            ui->textEdit->append(QString::fromStdString("\t"+t.getTache()+" "+t.getdateT()));
        }
        ui->textEdit->append(QString::fromStdString("\n"));
    }

}
/**
 * @brief Affiche un message d'erreur relatif aux interactions pour un contact spécifié.
 *        Efface le contenu précédent de ui->textEdit et affiche le message d'erreur avec le nom du contact.
 * @param s Message d'erreur à afficher.
 * @param c Pointeur vers l'objet Contact concerné par l'erreur.
 * @note Assurez-vous que le paramètre c n'est pas nul pour éviter tout comportement indéfini.
 */
void MainWindow::displayErrortodo(string s,Contact *c)
{
    ui->textEdit->clear();
    ui->textEdit->setText(QString::fromStdString("Contact :"+c->getNom()+" "+c->getPrenom()));
    ui->textEdit->append(QString::fromStdString(s));
}
/**
 * @brief Affiche les interactions pour un contact spécifié.
 *        Efface le contenu précédent de ui->textEdit et affiche les interactions du contact.
 * @param li Liste des interactions à afficher pour le contact.
 * @param c Pointeur vers l'objet Contact dont les interactions sont affichées.
 * @note Assurez-vous que les paramètres li et c ne sont pas nuls pour éviter tout comportement indéfini.
 */
void MainWindow::displayInter(list<Interactions *>li,Contact *c)
{
    ui->textEdit->clear();
    ui->textEdit->append(QString::fromStdString("Contact: "+c->getNom()+" "+c->getPrenom()));
    for(auto &i : li)
    {
        ui->textEdit->append(QString::fromStdString(i->getContenu()+" "+i->getDate()));
    }
}
/**
 * @brief Affiche un message d'erreur relatif à un contact spécifié.
 *        Efface le contenu précédent de ui->textEdit et affiche le nom du contact avec le message d'erreur.
 * @param s Message d'erreur à afficher.
 * @param c Pointeur vers l'objet Contact concerné par l'erreur.
 * @note Assurez-vous que le paramètre c n'est pas nul pour éviter tout comportement indéfini.
 */
void MainWindow::displayError(string s,Contact *c)
{
    ui->textEdit->clear();
    ui->textEdit->append(QString::fromStdString("Contact: "+c->getNom()+" "+c->getPrenom()));
    ui->textEdit->append(QString::fromStdString(s));
}


/**
 * @brief Déclenché lors du clic sur le bouton "Appliquer".
 *        Établit une connexion pour rechercher les contacts entre deux dates spécifiées.
 *        Connecte les signaux searchCbetween, sendLc et noContact aux slots correspondants de la classe bd.
 *        Émet le signal searchCbetween avec les dates récupérées des champs dateEdit et dateEdit_2.
 * @note Assurez-vous que les champs dateEdit et dateEdit_2 contiennent des dates valides pour une recherche appropriée.
 */
void MainWindow::on_appliquer_clicked()
{
    connect(this,SIGNAL(searchCbetween(QString,QString)),bd,SLOT(searchCbetween(QString,QString)));
    connect(bd,SIGNAL(sendLc(list<Contact*>)),this,SLOT(affichContacts(list<Contact*>)));
    connect(bd,SIGNAL(noContact()),this,SLOT(noContact()));
    QString date1=ui->dateEdit->text();
    QString date2=ui->dateEdit_2->text();
    emit searchCbetween(date1,date2);
}
/**
 * @brief Affiche une liste de contacts dans le widget textEdit_2.
 * @param l Liste de pointeurs vers des objets Contact à afficher.
 * @note Efface le contenu actuel du widget textEdit_2 avant d'afficher la liste.
 */
void MainWindow::affichContacts(list <Contact *>l)
{
    ui->textEdit_2->clear();
    for(Contact *c:l)
    {
        ui->textEdit_2->append(QString::fromStdString("Contact : "+c->getNom()+" "+c->getPrenom()));
    }

}
/**
 * @brief Affiche un message d'absence de contact dans le widget textEdit_2.
 * @note Efface le contenu actuel du widget textEdit_2 et affiche un message indiquant l'absence de contacts correspondant à la recherche.
 */
void MainWindow::noContact()
{
    ui->textEdit_2->clear();
    ui->textEdit_2->setText(QString::fromStdString("Aucun contact ne correspond à cette recherche"));
}



/**
 * @brief Déclenché lorsqu'un utilisateur clique sur le bouton pushButton.
 * Effectue une recherche d'interactions entre deux dates pour un contact sélectionné.
 * Connecte les signaux et les slots pour effectuer la recherche et afficher les résultats ou les erreurs.
 * @note Utilise l'ID du contact sélectionné pour envoyer les dates de recherche via un signal à la classe base de données.
 */
void MainWindow::on_pushButton_clicked()
{
    connect(this,SIGNAL(sendDateInter(string,QString,QString)),bd,SLOT(search2DInter(string,QString,QString)));
    connect(bd,SIGNAL(listInter2date(list<Interactions*>,Contact *)),this,SLOT(affichInter2date(list<Interactions *>,Contact *)));
    connect(bd,SIGNAL(noInter(string,Contact *)),this,SLOT(noInter(string,Contact *)));
    string l=ui->listWidget->currentItem()->text().toStdString();
    string id="";
    bool ok=false;
    for(int i=0;!ok;i++)
    {
        if(l[i]!='-')
        {
            id+=l[i];
        }
        else
        {
            ok=true;
        }
    }
    emit sendDateInter(id,ui->dateEdit->text(),ui->dateEdit_2->text());//envoyer l'id du contact qui a été selectionné via un signal à la classe basedonnee

}
/**
 * @brief Affiche les interactions d'un contact entre deux dates dans l'interface utilisateur.
 * Efface le contenu actuel et affiche les interactions de manière formatée.
 * @param li Liste des pointeurs vers les objets d'interactions pour un contact donné.
 * @param c Pointeur vers l'objet Contact pour lequel les interactions sont affichées.
 * @note Cette fonction affiche les interactions d'un contact spécifique entre deux dates dans un QTextEdit.
 */
void MainWindow::affichInter2date(list<Interactions *>li,Contact *c)
{
    ui->textEdit_2->clear();
    ui->textEdit_2->append(QString::fromStdString("Contact: "+c->getNom()+" "+c->getPrenom()));
    for(Interactions *i:li)
    {
        ui->textEdit_2->append(QString::fromStdString("Interaction : "+i->getContenu()+" "+i->getDate()));
    }
}
/**
 * @brief Affiche un message lorsque aucune interaction n'est trouvée pour un contact entre deux dates.
 * Efface le contenu actuel du QTextEdit et affiche un message spécifiant l'absence d'interactions.
 * @param s Chaîne de caractères décrivant l'erreur ou l'absence d'interactions pour le contact.
 * @param c Pointeur vers l'objet Contact concerné par la recherche.
 * @note Cette fonction affiche un message dans un QTextEdit lorsque aucune interaction n'est trouvée pour un contact donné entre deux dates.
 */
void MainWindow::noInter(string s,Contact *c)
{
    ui->textEdit_2->clear();
    ui->textEdit_2->append(QString::fromStdString("Contact: "+c->getNom()+" "+c->getPrenom()));
    ui->textEdit_2->append(QString::fromStdString(s));
}
