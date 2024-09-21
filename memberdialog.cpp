#include "memberdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

MemberDialog::MemberDialog(QWidget *parent, const QString &mode)
    : QDialog(parent), mode(mode)
{
    setWindowTitle(mode + " un membre");
    setFixedSize(400, 350);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new QLabel("ID:"));
    idEdit = new QLineEdit(this);
    mainLayout->addWidget(idEdit);

    mainLayout->addWidget(new QLabel("Nom:"));
    nameEdit = new QLineEdit(this);
    mainLayout->addWidget(nameEdit);

    mainLayout->addWidget(new QLabel("Prénom:"));
    surnameEdit = new QLineEdit(this);
    mainLayout->addWidget(surnameEdit);

    mainLayout->addWidget(new QLabel("Sexe:"));
    genderComboBox = new QComboBox(this);
    genderComboBox->addItems({"Homme", "Femme", "Autre"});
    mainLayout->addWidget(genderComboBox);

    mainLayout->addWidget(new QLabel("Email:"));
    emailEdit = new QLineEdit(this);
    mainLayout->addWidget(emailEdit);

    mainLayout->addWidget(new QLabel("Date d'inscription:"));
    registrationDateEdit = new QDateEdit(this);
    registrationDateEdit->setDate(QDate::currentDate());
    mainLayout->addWidget(registrationDateEdit);

    saveButton = new QPushButton(mode, this);
    cancelButton = new QPushButton("Annuler", this);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);

    connect(saveButton, &QPushButton::clicked, this, &MemberDialog::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}


MemberDialog::~MemberDialog()
{
    // Nettoyage si nécessaire
}

QString MemberDialog::getId()
{
    return idEdit->text();
}

QString MemberDialog::getName()
{
    return nameEdit->text();
}

QString MemberDialog::getSurname()
{
    return surnameEdit->text();
}

QString MemberDialog::getGender()
{
    return genderComboBox->currentText();
}

QString MemberDialog::getEmail()
{
    return emailEdit->text();
}

QString MemberDialog::getRegistrationDate()
{
    return registrationDateEdit->date().toString("yyyy-MM-dd");
}

void MemberDialog::onSave()
{
    // Ici, vous ajouteriez la logique pour sauvegarder les données du membre
    QMessageBox::information(this, mode + " un membre", "Membre " + mode.toLower() + " avec succès !");
    accept();
}

