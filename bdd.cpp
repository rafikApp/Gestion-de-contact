/**
 * @file bdd.cpp
 * @brief Implémentation des fonctions de la classe bdd
 */
#include "bdd.h"
#include <QDebug>
#include <QSqlQuery>
#include<QSqlError>
#include<QDate>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

/**
 * @brief Constructeur de la classe bdd.
 * @param parent Pointeur vers l'objet parent (QObject).
 * Ce constructeur initialise une connexion à une base de données SQLite,
 * exporte les données au format JSON et établit une connexion entre signaux et slots.
 */

bdd::bdd(QObject *parent) : QObject{parent}
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home1/rr314702/Téléchargements/projetQtaf(1)/projetQt(2)/projetQt/bdd.sqlite");
    if(!db.open())
    {
        qDebug() << "Pas de connexion BDD !";
    }
    else
    {
        qDebug() << "Connexion BDD ok";
    }
    exportJson("/home3/ak859784/projetQt/DataExport.json");
    connect(this, SIGNAL(EditData()), this, SLOT(generatJson()));

}
/**
 * @brief Destructeur de l'objet bdd
 * @details Ferme la connexion à la base de données lorsqu'un objet bdd est détruit
 */
bdd::~bdd()
{
    db.close();
}
/**
 * @brief Remplit une liste de contacts avec les données de la base de données
 * @details Récupère les contacts depuis la base de données, les ajoute à une liste de contacts, puis émet un signal.
 */
void bdd::remplirList()
{
    list<Contact *> lc;
    QSqlQuery query;
       query.prepare("SELECT * from Contact");
       query.exec();
       while(query.next())
       {
           //recuperer l'id, nom et prenom de chaque contact du tableau Contact de la base de donnée
           QString id=QString(query.value(0).toString());
           QString nom=QString(query.value(1).toString());
           QString prenom=QString(query.value(2).toString());
           c=new Contact();
           c->setPrenom(prenom.toStdString());
           c->setNom(nom.toStdString());
           c->setId(id.toStdString());
           lc.push_back(c);

       }
       emit remplirLbd(lc);
}
/**
 * @brief Exporte les données de la base de données au format JSON dans un fichier spécifié
 * @param nomFichier Chemin du fichier où les données seront exportées au format JSON
 */
void bdd::exportJson(const QString &nomFichier)

{
    QJsonObject databaseObject;

    // Exporter le tableau Contact
    QJsonArray contactsArray;
    QSqlQuery contactQuery;
    contactQuery.prepare("SELECT * FROM Contact");
    if (contactQuery.exec()) {
        while (contactQuery.next()) {
            QJsonObject contactObject;
            contactObject["idC"] = contactQuery.value("idC").toInt();
            contactObject["nom"] = contactQuery.value("nom").toString();
            contactObject["prenom"] = contactQuery.value("prenom").toString();
            contactObject["email"] = contactQuery.value("email").toString();
            contactObject["entreprise"] = contactQuery.value("entreprise").toString();
            contactObject["dateC"] = contactQuery.value("dateC").toString();
            contactObject["dateM"] = contactQuery.value("dateM").toString();
            contactObject["photo"] = contactQuery.value("photo").toString();
            contactObject["telephone"] = contactQuery.value("telephone").toString();
            contactsArray.append(contactObject);
        }
        databaseObject["Contact"] = contactsArray;
    } else {
        qDebug() << "Erreur lors de l'exportation du tableau Contact : " << contactQuery.lastError().text();
        return;
    }


    // Exporter le tableau Interaction
    QJsonArray interactionsArray;
    QSqlQuery interactionQuery;
    interactionQuery.prepare("SELECT * FROM Interaction");
    if (interactionQuery.exec()) {
        while (interactionQuery.next()) {
            QJsonObject interactionObject;
            interactionObject["idI"] = interactionQuery.value("idI").toInt();
            interactionObject["idC"] = interactionQuery.value("idC").toInt();
            interactionObject["contenu"] = interactionQuery.value("contenu").toString();
            interactionObject["dateInteraction"] = interactionQuery.value("dateInteraction").toString();
            interactionsArray.append(interactionObject);
        }
        databaseObject["Interaction"] = interactionsArray;
    } else {
        qDebug() << "Erreur lors de l'exportation du tableau Interaction : " << interactionQuery.lastError().text();
        return;
    }

    // Exporter le tableau Todo
    QJsonArray todoArray;
    QSqlQuery todoQuery;
    todoQuery.prepare("SELECT * FROM Todo");
    if (todoQuery.exec()) {
        while (todoQuery.next()) {
            QJsonObject todoObject;
            todoObject["idT"] = todoQuery.value("idT").toInt();
            todoObject["idI"] = todoQuery.value("idI").toInt();
            todoObject["tache"] = todoQuery.value("tache").toString();
            todoObject["dateTodo"] = todoQuery.value("dateTodo").toString();
            todoArray.append(todoObject);
        }
        databaseObject["Todo"] = todoArray;
    } else {
        qDebug() << "Erreur lors de l'exportation du tableau Todo : " << todoQuery.lastError().text();
        return;
    }

    // Créer le document JSON
    QJsonDocument jsonDocument(databaseObject);

    // Ouvrir un fichier pour l'écriture
    QFile file(nomFichier);
    if (file.open(QIODevice::WriteOnly)) {
        // Écrire le document JSON dans le fichier
        file.write(jsonDocument.toJson());
        file.close();
        qDebug() << "Export JSON réussi.";
    } else {
        qDebug() << "Erreur lors de l'ouverture du fichier pour l'export JSON.";
    }
}
/**
 * @brief Génère le fichier JSON avec les données exportées
 */
void bdd::generatJson()
{
    exportJson("/home3/ak859784/projetQt/DataExport.json");
}
/**
 * @brief Modifie l'identifiant (idC) de la classe bdd avec celui fourni en paramètre.
 * @param id La nouvelle valeur de l'identifiant (idC) sous forme de chaîne de caractères.
 */
void bdd::EditID(string id)
{
    this->idC = id;
}

/**
 * @brief Insère une interaction dans la table 'Interaction' de la base de données.
 * @param I Pointeur vers l'objet Interactions à insérer dans la base de données.
 * Cette fonction insère une nouvelle interaction avec ses attributs (idC, contenu, dateInteraction)
 * dans la table 'Interaction' de la base de données.
 * Elle émet un signal EditData après l'insertion.
 */
void bdd::insertInter(Interactions *I)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Interaction (idC, contenu, dateInteraction) VALUES ( :c, :t, :d)");
    query.bindValue(":c", QString::fromStdString(idC));
    query.bindValue(":t", QString::fromStdString(I->getContenu()));
    query.bindValue(":d", QString::fromStdString(I->getDate()));
    query.exec();

    QString inter = QString::fromStdString(I->getContenu());
    query.prepare("SELECT * from Interaction WHERE contenu='" + inter + "';");
    query.exec();
    while (query.next())
    {
        QString id = QString(query.value(0).toString());
        idI = id.toStdString();
    }
    emit EditData();
}

/**
 * @brief Insère une liste de tâches (todo) dans la table 'Todo' de la base de données.
 * @param l Liste contenant les pointeurs vers les objets todo à insérer dans la base de données.
 * Cette fonction insère chaque tâche (todo) avec ses attributs (idI, tache, dateTodo)
 * dans la table 'Todo' de la base de données.
 * Elle émet un signal EditData après chaque insertion.
 */
void bdd::insertTodo(list<todo *> l)
{
    QSqlQuery query;
    for (const todo* T : l) {
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO Todo (idI, tache, dateTodo) VALUES (:idI, :t, :d)");
        insertQuery.bindValue(":idI", std::stoi(idI));
        insertQuery.bindValue(":t", QString::fromStdString(T->getTache()));
        insertQuery.bindValue(":d", QString::fromStdString(T->getdateT()));

        if (insertQuery.exec()) {
            qDebug() << "Insertion avec succès à la table Todo.";
        } else {
            qDebug() << "Erreur lors de l'ajout de l'enregistrement à la table Todo:" << insertQuery.lastError().text();
        }
    }
    emit EditData();
}
/**
 * @brief Recherche les interactions entre deux dates pour un identifiant donné.
 *
 * Cette fonction effectue une recherche dans la base de données pour trouver les interactions associées à un identifiant spécifique
 * et comprises entre deux dates données. Elle émet un signal listInter2date contenant une liste d'objets Interactions si des
 * interactions sont trouvées. Dans le cas où aucune interaction n'est trouvée, elle émet un signal noInter avec un message explicatif
 * et les détails du Contact associé à l'identifiant.
 *
 * @param id L'identifiant à utiliser pour la recherche.
 * @param date1 La première date au format "jour/mois/année".
 * @param date2 La deuxième date au format "jour/mois/année".
 */
void bdd::search2DInter(string id,QString date1,QString date2)
{
    idC=id;
    list<Interactions *>li;
    QString s=QString::fromStdString(idC);
    bool ok=false;

    // Convertir les chaînes de date en objets QDate
    QDate dateF = QDate::fromString(date1, "d/MM/yyyy");
    QDate dateL = QDate::fromString(date2, "d/MM/yyyy");
    // Formatage des dates dans le format attendu par la base de données (à adapter si nécessaire)
    QString dateDebutStr = dateF.toString("d/MM/yyyy");
    QString dateFinStr = dateL.toString("d/MM/yyyy");


    QSqlQuery query;
    //selection interaction
    query.prepare("SELECT * FROM Interaction WHERE  idC = :id  AND dateInteraction BETWEEN :dateDebutStr AND :dateFinStr;");
    query.bindValue(":id", s);
    query.bindValue(":dateDebutStr", dateDebutStr);
    query.bindValue(":dateFinStr", dateFinStr);
    if(query.exec())
    {

        while(query.next())
        {
            QString in=QString(query.value(2).toString());
            QString din=QString(query.value(3).toString());
            QString id=QString(query.value(0).toString());
            I=new Interactions(in.toStdString(),din.toStdString());
            I->setId(id.toStdString());
            li.push_back(I);
            ok=true;
        }
    }
    else
    {
        qDebug() << "Erreur lors de la recherche  : " << query.lastError().text();
    }

    //selectionner Contact
    query.prepare("SELECT * from Contact WHERE idC="+s+";");
    query.exec();
    while(query.next())
    {
        QString n=QString(query.value(1).toString());
        QString p=QString(query.value(2).toString());
        c=new Contact();
        c->setNom(n.toStdString());
        c->setPrenom(p.toStdString());
    }
    if(ok)
        emit listInter2date(li,c);
    else
        emit noInter("Aucune Interaction cree entre ces deux dates  ",c);
}
/**
 * @brief Recherche les interactions et les tâches associées à un identifiant donné.
 *
 * Cette fonction effectue une recherche dans la base de données pour trouver les interactions et les tâches associées à un identifiant spécifique.
 * Elle sélectionne d'abord toutes les interactions liées à l'identifiant, puis pour chaque interaction trouvée, elle récupère les tâches
 * associées à cette interaction. Elle émet un signal sendCinter contenant la liste des interactions avec leurs tâches si des données sont trouvées,
 * sinon elle émet un signal errorM avec un message explicatif et les détails du Contact associé à l'identifiant.
 *
 * @param i L'identifiant à utiliser pour la recherche.
 */
void bdd::searchIDintertodo(string i)
{
    idC=i;
    bool ok=false;
    bool ok2=false;
    tache=new todo();
    list<Interactions *> li;
    QString s=QString::fromStdString(idC);
    QSqlQuery query;
    //selection interaction
    query.prepare("SELECT * from Interaction WHERE idC="+s+";");
    query.exec();
    while(query.next())
    {
        QString in=QString(query.value(2).toString());
        QString din=QString(query.value(3).toString());
        QString id=QString(query.value(0).toString());
        I=new Interactions(in.toStdString(),din.toStdString());
        I->setId(id.toStdString());

        li.push_back(I);
        ok=true;
    }
    //selectionner Contact
    query.prepare("SELECT * from Contact WHERE idC="+s+";");
    query.exec();
    while(query.next())
    {
        QString n=QString(query.value(1).toString());
        QString p=QString(query.value(2).toString());
        c=new Contact();
    c->setNom(n.toStdString());
    c->setPrenom(p.toStdString());
    }

    //selectionner les taches
    for( Interactions *inter:li)
    {
        QString k=QString::fromStdString(inter->getId());
        query.prepare("SELECT * from Todo WHERE idI="+k+";");
        query.exec();
        while(query.next())
        {
            QString contenu=QString(query.value(2).toString());
            QString date=QString(query.value(3).toString());
            tache->setdateT(date.toStdString());
            tache->setTache(contenu.toStdString());
            inter->Addtodo(*tache);
           // qDebug() << "tache : " << tache->getTache().c_str() << ", Date : " << tache->getdateT().c_str();
            ok2=true;
        }
    }
    if(ok & ok2)
        emit sendCinter(li,c);
    else
        emit errorM("//Ce contact n'a aucune tache à faire.",c);
}
/**
 * @brief Recherche des contacts créés entre deux dates spécifiques.
 *
 * Cette fonction recherche les contacts dont la date de création est comprise entre deux dates données.
 * Elle convertit d'abord les chaînes de date en objets QDate pour formater les dates dans le format attendu par la base de données.
 * Ensuite, elle exécute une requête SQL pour récupérer les contacts créés entre les dates spécifiées.
 * Si des contacts sont trouvés, elle les ajoute à une liste de contacts et émet un signal sendLc contenant cette liste.
 * Si aucun contact n'est trouvé, elle émet un signal noContact pour indiquer qu'aucun contact n'a été créé entre ces dates.
 *
 * @param date1 La première date de recherche au format "d/MM/yyyy".
 * @param date2 La deuxième date de recherche au format "d/MM/yyyy".
 */
void bdd::searchCbetween(QString date1,QString date2)
{
    QSqlQuery query;
    list<Contact*>l;
    bool ok=false;
    // Convertir les chaînes de date en objets QDate
    QDate dateF = QDate::fromString(date1, "d/MM/yyyy");
    QDate dateL = QDate::fromString(date2, "d/MM/yyyy");

    // Formatage des dates dans le format attendu par la base de données (à adapter si nécessaire)
    QString dateDebutStr = dateF.toString("d/MM/yyyy");
    QString dateFinStr = dateL.toString("d/MM/yyyy");
    query.prepare("SELECT * FROM Contact WHERE dateC BETWEEN :dateDebut AND :dateFin");
    query.bindValue(":dateDebut", dateDebutStr);
    query.bindValue(":dateFin", dateFinStr);
    if (query.exec())
    {

        while (query.next())
        {
            QString n=QString(query.value(1).toString());
            QString p=QString(query.value(2).toString());
            c=new Contact();
            c->setNom(n.toStdString());
            c->setPrenom(p.toStdString());
            l.push_back(c);
            ok=true;
        }

    }
    else
    {
        qDebug() << "Erreur lors de la recherche  : " << query.lastError().text();
    }
    if(ok)
        emit sendLc(l);
    else
        emit noContact();


}
/**
 * @brief Recherche des interactions pour un contact spécifique.
 *
 * Cette fonction recherche les interactions associées à un contact donné, identifié par son identifiant.
 * Elle exécute d'abord une requête SQL pour sélectionner les interactions de ce contact.
 * Si des interactions sont trouvées, elle les ajoute à une liste d'interactions.
 * Ensuite, elle sélectionne les informations du contact correspondant à partir de la base de données.
 * Si des interactions sont trouvées pour ce contact, elle émet un signal sendCinter contenant la liste d'interactions et les informations du contact.
 * Si aucune interaction n'est trouvée, elle émet un signal errorM pour indiquer qu'aucune interaction n'a été enregistrée pour ce contact.
 *
 * @param i L'identifiant du contact pour lequel on recherche les interactions.
 */
void bdd::searchIDinter(string i)
{
    idC=i;
    bool ok=false;
    list<Interactions *> li;
    QString s=QString::fromStdString(idC);
    QSqlQuery query;
    //selection interaction
    query.prepare("SELECT * from Interaction WHERE idC="+s+";");
    query.exec();
    while(query.next())
    {
        QString in=QString(query.value(2).toString());
        QString din=QString(query.value(3).toString());
        I=new Interactions(in.toStdString(),din.toStdString());
        li.push_back(I);
        ok=true;
    }


    //selectionner Contact
    query.prepare("SELECT * from Contact WHERE idC="+s+";");
    query.exec();
    while(query.next())
    {
        QString n=QString(query.value(1).toString());
        QString p=QString(query.value(2).toString());
        c=new Contact();
    c->setNom(n.toStdString());
    c->setPrenom(p.toStdString());
    }
    if(ok)
        emit sendCinter(li,c);
    else
        emit errorM("//Ce contact n'a aucune interaction.",c);
}
/**
 * @brief Ajoute un nouveau contact à la base de données.
 *
 * Cette fonction prend un objet Contact en paramètre et insère ses informations dans la table Contact de la base de données.
 * Elle utilise une requête SQL pour insérer les valeurs du contact dans les colonnes correspondantes de la table Contact.
 * Si l'insertion est réussie, elle émet un signal EditData pour informer la mise à jour des données.
 *
 * @param c Un pointeur vers l'objet Contact à ajouter à la base de données.
 */
void bdd::ajoutContact(Contact *c)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Contact (nom, prenom, email, entreprise, dateC, dateM, photo, telephone) "
                  "VALUES (:n, :p, :m, :e, :dc, :dm, :ph, :t)");
    query.bindValue(":n", QString::fromStdString(c->getNom()));
    query.bindValue(":p", QString::fromStdString(c->getPrenom()));
    query.bindValue(":m", QString::fromStdString(c->getMail()));
    query.bindValue(":e", QString::fromStdString(c->getEntreprise()));
    query.bindValue(":dc", QString::fromStdString(c->ConvertDatec()));
    query.bindValue(":dm", QString::fromStdString(c->ConvertDatem()));
    query.bindValue(":ph", QString::fromStdString(c->getPhoto()));
    query.bindValue(":t", QString::fromStdString(c->getTelephone()));

    try {
        if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
        } else {
            qDebug() << "Requête exécutée avec succès !";
            // Procéder avec les opérations post-requête si nécessaire
        }
    } catch (const std::exception &e) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << e.what();
        // Gérer l'erreur de manière appropriée, comme enregistrement dans un fichier de log ou affichage d'un message d'erreur
    } catch (...) {
        qDebug() << "Erreur inattendue lors de l'exécution de la requête.";
        // Gérer toute autre erreur non prévue
    }

    emit EditData();

}
/**
 * @brief Trouve le nombre d'entrées dans la table "Contact" de la base de données.
 *
 * Cette fonction exécute une requête SQL pour compter le nombre d'entrées présentes dans la table "Contact".
 * Elle récupère le résultat de la requête pour obtenir le nombre d'entrées et l'assigne à une variable entière.
 * Ensuite, elle émet un signal "sendNb" contenant ce nombre d'entrées pour informer les parties intéressées.
 */
void bdd::trouverNb()
{
    int nb=0; // Déclaration d'une variable entière pour stocker le nombre d'entrées

    QSqlQuery query; // Création d'une requête SQL
    query.prepare("SELECT COUNT (*) from Contact"); // Préparation de la requête pour compter les entrées dans la table "Contact"
    query.exec(); // Exécution de la requête

    // Vérification s'il y a un résultat à la requête
    if(query.next())
    {
        nb = query.value(0).toInt(); // Récupération du nombre d'entrées depuis la première colonne du résultat
    }

    emit sendNb(nb); // Émission du nombre d'entrées via un signal nommé "NB"
}
/**
 * @brief Recherche des contacts en fonction du nom, de l'entreprise ou de la date de création.
 *
 * Cette fonction effectue une recherche dans la table "Contact" de la base de données en fonction du nom, de l'entreprise
 * ou de la date de création. Selon la valeur de "nbr", elle utilise différents critères de recherche et exécute la requête SQL
 * appropriée pour récupérer les informations des contacts correspondants. Les informations récupérées sont ensuite utilisées pour créer
 * des objets de type Contact, qui sont stockés dans une liste. Si des contacts correspondants sont trouvés, ils sont émis via un
 * signal nommé "findlistC". Sinon, un signal "errorM" est émis pour indiquer l'absence de résultats.
 *
 * @param choix    La valeur de recherche (nom, entreprise ou date de création).
 * @param nbr      Le code numérique indiquant le critère de recherche (1 pour le nom, 2 pour l'entreprise, 3 pour la date de création).
 */
void bdd::searchNameC(QString choix,int nbr)
{
    bool verif=false;
    QSqlQuery query;
    string s=choix.toStdString();
    list<Contact *> lc;
    if(nbr==1)
    {
        query.prepare("SELECT * from Contact WHERE nom='"+choix+"';");
        query.exec();
        while(query.next())
        {
            QString n= QString(query.value(1).toString());
            QString p= QString(query.value(2).toString());
            QString e= QString(query.value(4).toString());
            QString m= QString(query.value(3).toString());
            QString t= QString(query.value(8).toString());
            QString ph= QString(query.value(7).toString());
            QString dc= QString(query.value(5).toString());
            QString de= QString(query.value(6).toString());

            c=new Contact();
            c->setNom(n.toStdString());
            c->setPrenom(p.toStdString());
            c->setEntreprise(e.toStdString());
            c->setMail(m.toStdString());
            c->setTelephone(t.toStdString());
            c->setPhoto(ph.toStdString());
            c->setDateC(dc.toStdString());
            c->setDateE(de.toStdString());

            //c= new Contact(ln.toStdString(), fn.toStdString(), e.toStdString(), m.toStdString(), t.toStdString(), ph.toStdString(), dc.toStdString(), de.toStdString());
            verif=true;
            lc.push_back(c);

        }
    }
    else if(nbr==3)
    {
        query.prepare("SELECT * from Contact WHERE entreprise='"+choix+"';");
        query.exec();
        while(query.next())
        {
            QString n= QString(query.value(1).toString());
            QString p= QString(query.value(2).toString());
            QString e= QString(query.value(4).toString());
            QString m= QString(query.value(3).toString());
            QString t= QString(query.value(8).toString());
            QString ph= QString(query.value(7).toString());
            QString dc= QString(query.value(5).toString());
            QString de= QString(query.value(6).toString());

            c=new Contact();
            c->setNom(n.toStdString());
            c->setPrenom(p.toStdString());
            c->setEntreprise(e.toStdString());
            c->setMail(m.toStdString());
            c->setTelephone(t.toStdString());
            c->setPhoto(ph.toStdString());
            c->setDateC(dc.toStdString());
            c->setDateE(de.toStdString());

            //c= new Contact(ln.toStdString(), fn.toStdString(), e.toStdString(), m.toStdString(), t.toStdString(), ph.toStdString(), dc.toStdString(), de.toStdString());
            verif=true;
            lc.push_back(c);
        }
    }
    else
    {
        query.prepare("SELECT * from Contact WHERE dateC='"+choix+"';");
        query.exec();
        while(query.next())
        {
            QString n= QString(query.value(1).toString());
            QString p= QString(query.value(2).toString());
            QString e= QString(query.value(4).toString());
            QString m= QString(query.value(3).toString());
            QString t= QString(query.value(8).toString());
            QString ph= QString(query.value(7).toString());
            QString dc= QString(query.value(5).toString());
            QString de= QString(query.value(6).toString());

            c=new Contact();
            c->setNom(n.toStdString());
            c->setPrenom(p.toStdString());
            c->setEntreprise(e.toStdString());
            c->setMail(m.toStdString());
            c->setTelephone(t.toStdString());
            c->setPhoto(ph.toStdString());
            c->setDateC(dc.toStdString());
            c->setDateE(de.toStdString());

            //c= new Contact(ln.toStdString(), fn.toStdString(), e.toStdString(), m.toStdString(), t.toStdString(), ph.toStdString(), dc.toStdString(), de.toStdString());
            verif=true;
            lc.push_back(c);
        }
    }
    if(verif)
            emit findlistC(lc);
    else
        emit errorM();



}
/**
 * @brief Récupère les informations d'un contact à partir de son identifiant.
 *
 * Cette fonction effectue une requête dans la table "Contact" de la base de données pour récupérer les informations d'un contact
 * spécifique identifié par son identifiant unique `idC`. Elle récupère les détails du contact (nom, prénom, email, entreprise, etc.)
 * et crée un objet de type Contact avec ces informations. Si le contact est trouvé dans la base de données, les informations sont stockées
 * dans l'objet Contact, puis émises via un signal nommé "sendC". Sinon, aucun signal n'est émis.
 *
 * @param i L'identifiant du contact à récupérer.
 */
void bdd::recupCid(string i)
{
    idC=i;
    QString s=QString::fromStdString(idC);
    QSqlQuery query;
    query.prepare("SELECT * from Contact WHERE idC="+s+";");
    query.exec();
    while(query.next())
    {
        QString n= QString(query.value(1).toString());
        QString p= QString(query.value(2).toString());
        QString m= QString(query.value(3).toString());
        QString e= QString(query.value(4).toString());
        QString dc= QString(query.value(5).toString());
        QString dm= QString(query.value(6).toString());
        QString ph= QString(query.value(7).toString());
        QString t= QString(query.value(8).toString());
        c= new Contact();
        c->setNom(n.toStdString());
        c->setPrenom(p.toStdString());
        c->setMail(m.toStdString());
        c->setEntreprise(e.toStdString());
        c->setDateC(dc.toStdString());
        c->setDateE(dm.toStdString());
        c->setTelephone(t.toStdString());
        c->setPhoto(ph.toStdString());

    }
    emit sendC(c);
}
/**
 * @brief Met à jour les informations d'un contact dans la base de données.
 *
 * Cette fonction met à jour les informations d'un contact dans la table "Contact" de la base de données.
 * Elle reçoit de nouveaux détails pour le contact (nom, prénom, email, entreprise, etc.) et effectue
 * une requête SQL pour mettre à jour ces informations pour le contact spécifié par son identifiant unique `idC`.
 * Si la mise à jour est réussie, un signal nommé "EditData" est émis pour indiquer la fin de l'édition des données.
 *
 * @param n Le nouveau nom du contact.
 * @param pr Le nouveau prénom du contact.
 * @param E Le nouvel email du contact.
 * @param m Le nouvel email du contact.
 * @param tele Le nouveau numéro de téléphone du contact.
 * @param photo Le nouveau chemin vers la photo du contact.
 */
void bdd::reciveE(QString n,QString pr,QString E,QString m,QString tele,QString photo)
{
    c=new Contact();
    QString s=QString::fromStdString(idC);
    QSqlQuery query;
    string ph=photo.toStdString();
    query.prepare("UPDATE Contact SET nom=:n,prenom=:pr,email=:m,entreprise=:e,dateM=:mdf,telephone=:tele,photo=:p WHERE idC="+s+";");
    query.bindValue(":n",n);
    query.bindValue(":pr",pr);
    query.bindValue(":e", E);
    query.bindValue(":tele", tele);
    query.bindValue(":m", m);
    query.bindValue(":p", photo);
    query.bindValue(":mdf", QString::fromStdString(c->ConvertDatem()));
    query.exec();
    recupCid(idC);
    emit EditData();

}
/**
 * @brief Supprime un contact de la base de données avec ses interactions associées.
 *
 * Cette fonction supprime un contact et toutes ses interactions associées de la base de données.
 * Elle effectue deux requêtes SQL pour supprimer toutes les entrées correspondant au contact spécifié
 * par son identifiant unique `idC` dans les tables "Contact" et "Interaction". Après la suppression
 * réussie, un signal nommé "EditData" est émis pour indiquer la fin de la suppression des données.
 */
void bdd::deleteCbd()
{

    QString s=QString::fromStdString(idC);
    QSqlQuery query;

    query.prepare(("DELETE FROM Contact WHERE idC="+s+";"));
    query.exec();
    query.prepare(("DELETE FROM Interaction WHERE idC="+s+";"));
    query.exec();
    emit EditData();

}
