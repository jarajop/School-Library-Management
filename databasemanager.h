#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool openDatabase();
    bool createTables();

    // Méthodes pour les livres
    bool addBook(const QString &id, const QString &title, const QString &author, const QString &genre, const QDate &addDate);
    bool updateBook(const QString &id, const QString &title, const QString &author, const QString &genre, const QDate &addDate);
    bool deleteBook(const QString &id);

    // Méthodes pour les membres
    bool addMember(const QString &id, const QString &name, const QString &surname, const QString &gender, const QString &email, const QDate &registrationDate);
    bool updateMember(const QString &id, const QString &name, const QString &surname, const QString &gender, const QString &email, const QDate &registrationDate);
    bool deleteMember(const QString &id);

    // Méthodes pour les emprunts
    bool addLoan(const QString &id, const QString &memberId, const QString &bookId, const QDate &loanDate, const QDate &expectedReturnDate);
    bool updateLoan(const QString &id, const QString &memberId, const QString &bookId, const QDate &loanDate, const QDate &expectedReturnDate, const QDate &actualReturnDate);
    bool deleteLoan(const QString &id);

private:
    QSqlDatabase m_database;
};

#endif // DATABASEMANAGER_H
