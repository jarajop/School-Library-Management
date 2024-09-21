#include "bookdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

BookDialog::BookDialog(QWidget *parent, const QString &mode)
    : QDialog(parent), mode(mode)
{
    setWindowTitle(mode + " un livre");
    setFixedSize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new QLabel("ID:"));
    idEdit = new QLineEdit(this);
    mainLayout->addWidget(idEdit);

    mainLayout->addWidget(new QLabel("Titre:"));
    titleEdit = new QLineEdit(this);
    mainLayout->addWidget(titleEdit);

    mainLayout->addWidget(new QLabel("Auteur:"));
    authorEdit = new QLineEdit(this);
    mainLayout->addWidget(authorEdit);

    mainLayout->addWidget(new QLabel("Genre:"));
    genreEdit = new QLineEdit(this);
    mainLayout->addWidget(genreEdit);

    mainLayout->addWidget(new QLabel("Date d'ajout:"));
    addDateEdit = new QDateEdit(this);
    addDateEdit->setDate(QDate::currentDate());
    mainLayout->addWidget(addDateEdit);

    saveButton = new QPushButton(mode, this);
    cancelButton = new QPushButton("Annuler", this);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);

    connect(saveButton, &QPushButton::clicked, this, &BookDialog::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void BookDialog::onSave()
{
    // Ici, vous ajouteriez la logique pour sauvegarder les données du livre
    QMessageBox::information(this, mode + " un livre", "Livre " + mode.toLower() + " avec succès !");
    accept();
}

BookDialog::~BookDialog() {
    // Libère les ressources si nécessaire
}
