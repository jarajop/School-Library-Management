#include "addloandialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

AddLoanDialog::AddLoanDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Ajouter un nouvel emprunt");
    setFixedSize(400, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Champs du formulaire
    mainLayout->addWidget(new QLabel("ID:"));
    idEdit = new QLineEdit(this);
    mainLayout->addWidget(idEdit);

    mainLayout->addWidget(new QLabel("ID Membre:"));
    memberIdEdit = new QLineEdit(this);
    mainLayout->addWidget(memberIdEdit);

    mainLayout->addWidget(new QLabel("ID Livre:"));
    bookIdEdit = new QLineEdit(this);
    mainLayout->addWidget(bookIdEdit);

    mainLayout->addWidget(new QLabel("Date d'emprunt:"));
    loanDateEdit = new QDateEdit(this);
    mainLayout->addWidget(loanDateEdit);

    mainLayout->addWidget(new QLabel("Date de retour prévue:"));
    expectedReturnDateEdit = new QDateEdit(this);
    mainLayout->addWidget(expectedReturnDateEdit);

    mainLayout->addWidget(new QLabel("Date de retour réelle:"));
    actualReturnDateEdit = new QDateEdit(this);
    mainLayout->addWidget(actualReturnDateEdit);

    mainLayout->addWidget(new QLabel("Note:"));
    noteEdit = new QTextEdit(this);
    mainLayout->addWidget(noteEdit);

    // Boutons
    issueButton = new QPushButton("Emprunter", this);
    cancelButton = new QPushButton("Annuler", this);
    mainLayout->addWidget(issueButton);
    mainLayout->addWidget(cancelButton);

    connect(issueButton, &QPushButton::clicked, this, &AddLoanDialog::onIssue);
    connect(cancelButton, &QPushButton::clicked, this, &AddLoanDialog::reject);
}

void AddLoanDialog::onIssue()
{
    QMessageBox::information(this, "Emprunt", "Emprunt enregistré avec succès !");
    accept();
}

AddLoanDialog::~AddLoanDialog() {
    // Libère les ressources si nécessaire
}
