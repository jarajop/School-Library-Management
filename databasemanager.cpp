#include "databasemanager.h"
#include <QDate>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "mainwindow.h"
#include "memberdialog.h"
#include <QDialog>
#include <QMessageBox>

DatabaseManager::DatabaseManager()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("library.db");
}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen())
        m_database.close();
}

bool DatabaseManager::openDatabase() {
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("library.db");

    if (!m_database.open()) {
        qDebug() << "Erreur : impossible d'ouvrir la base de données :" << m_database.lastError().text();
        return false;
    }
    qDebug() << "Base de données ouverte avec succès.";
    return true;
}


bool DatabaseManager::createTables()
{
    QSqlQuery query;

    // Création de la table Books
    if (!query.exec("CREATE TABLE IF NOT EXISTS Books "
                    "(id TEXT PRIMARY KEY, "
                    "title TEXT, "
                    "author TEXT, "
                    "genre TEXT, "
                    "addDate DATE)")) {
        qDebug() << "Error creating Books table:" << query.lastError();
        return false;
    }

    // Création de la table Members
    if (!query.exec("CREATE TABLE IF NOT EXISTS Members "
                    "(id TEXT PRIMARY KEY, "
                    "name TEXT, "
                    "surname TEXT, "
                    "gender TEXT, "
                    "email TEXT, "
                    "registrationDate DATE)")) {
        qDebug() << "Error creating Members table:" << query.lastError();
        return false;
    }

    // Création de la table Loans
    if (!query.exec("CREATE TABLE IF NOT EXISTS Loans "
                    "(id TEXT PRIMARY KEY, "
                    "memberId TEXT, "
                    "bookId TEXT, "
                    "loanDate DATE, "
                    "expectedReturnDate DATE, "
                    "actualReturnDate DATE, "
                    "FOREIGN KEY(memberId) REFERENCES Members(id), "
                    "FOREIGN KEY(bookId) REFERENCES Books(id))")) {
        qDebug() << "Error creating Loans table:" << query.lastError();
        return false;
    }

    return true;
}

// Implémentation des méthodes pour les livres
bool DatabaseManager::addBook(const QString &id, const QString &title, const QString &author, const QString &genre, const QDate &addDate) {
    QSqlQuery query;
    query.prepare("INSERT INTO Books (id, title, author, genre, addDate) VALUES (:id, :title, :author, :genre, :addDate)");
    query.bindValue(":id", id);
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":genre", genre);
    query.bindValue(":addDate", addDate);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du livre :" << query.lastError().text();  // Affiche l'erreur SQL
        return false;
    }
    return true;
}


bool DatabaseManager::updateBook(const QString &id, const QString &title, const QString &author, const QString &genre, const QDate &addDate)
{
    QSqlQuery query;
    query.prepare("UPDATE Books SET title = :title, author = :author, genre = :genre, addDate = :addDate "
                  "WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":genre", genre);
    query.bindValue(":addDate", addDate);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification du livre:" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::deleteBook(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Books WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error lors de la suppression du livre:" << query.lastError();
        return false;
    }
    return true;
}

// Ajouter un membre (similaire à addBook)
bool DatabaseManager::addMember(const QString &id, const QString &name, const QString &surname, const QString &gender, const QString &email, const QDate &registrationDate)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Members (id, name, surname, gender, email, registrationDate) "
                  "VALUES (:id, :name, :surname, :gender, :email, :registrationDate)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":registrationDate", registrationDate);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du membre :" << query.lastError();
        return false;
    }
    return true;
}

// Supprimer un membre (similaire à deleteBook)
bool DatabaseManager::deleteMember(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Members WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du membre :" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::updateMember(const QString &id, const QString &name, const QString &surname, const QString &gender, const QString &email, const QDate &registrationDate)
{
    QSqlQuery query;
    query.prepare("UPDATE Members SET name = :name, surname = :surname, gender = :gender, email = :email, registrationDate = :registrationDate WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":registrationDate", registrationDate);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du membre :" << query.lastError();
        return false;
    }
    return true;
}





// Modifier un membre (similaire à updateBook)

