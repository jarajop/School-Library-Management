#pragma once

#ifndef ADDLOANDIALOG_H
#define ADDLOANDIALOG_H
#include <QDialog>
#include <QLineEdit>     // Inclusion nécessaire pour QLineEdit
#include <QDateEdit>     // Inclusion nécessaire pour QDateEdit
#include <QPushButton>   // Inclusion nécessaire pour QPushButton
#include <QTextEdit>



class AddLoanDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddLoanDialog(QWidget *parent = nullptr);
    virtual ~AddLoanDialog();  // Déclaration du destructeur

    // Méthodes pour récupérer les données du formulaire, comme les ID du livre et du membre
    QString getBookId() const;
    QString getMemberId() const;

public slots:
    void onIssue(); // Ajoutez cette ligne


private:
    QLineEdit *idEdit;
    QLineEdit *memberIdEdit;
    QLineEdit *bookIdEdit;
    QDateEdit *loanDateEdit;
    QDateEdit *expectedReturnDateEdit;
    QDateEdit *actualReturnDateEdit;
    QTextEdit *noteEdit;
    QPushButton *issueButton;
    QPushButton *cancelButton;
};

#endif // ADDLOANDIALOG_H
