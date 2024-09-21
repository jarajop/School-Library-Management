#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include "mainwindow.h"
#include "bookdialog.h"  // Ajoutez cette ligne
#include <QInputDialog>
#include "memberdialog.h"
#include "addloandialog.h"  // Inclure uniquement l'en-tête



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Gestion de Bibliothèque Scolaire");

    // Créer le widget central et la mise en page principale
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Barre latérale gauche
    QWidget *sidebar = createSidebar();
    mainLayout->addWidget(sidebar);

    // Zone de contenu à droite
    QWidget *contentArea = createContentArea();
    mainLayout->addWidget(contentArea);

    setCentralWidget(centralWidget);
}

QWidget* MainWindow::createSidebar()
{
    QWidget *sidebar = new QWidget;
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);

    QLabel *logoLabel = new QLabel("Librairie");
    logoLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white; background-color: #2c3e50; padding: 10px;");

    menuTree = new QTreeWidget;
    menuTree->setHeaderHidden(true);
    setupMenuTree();

    // Connecter le clic sur les éléments de l'arbre
    connect(menuTree, &QTreeWidget::itemClicked, this, &MainWindow::onMenuItemClicked);

    sidebarLayout->addWidget(logoLabel);
    sidebarLayout->addWidget(menuTree);

    sidebar->setStyleSheet("background-color: #34495e; color: white;");
    sidebar->setFixedWidth(200);

    return sidebar;
}


void MainWindow::setupMenuTree()
{
    QStringList categories = {"Gestion livres", "Gestion membres", "Gestion emprunts"};
    QStringList bookMemberActions = {"Ajouter", "Modifier", "Supprimer", "Rechercher"};
    QStringList loanActions = {"Ajouter nouveau emprunt"};

    menuTree->setStyleSheet("QTreeWidget { font-size: 17px; font-family: 'Arial'; color: white; }");

    for (const QString &category : categories) {
        QTreeWidgetItem *categoryItem = new QTreeWidgetItem(menuTree);
        categoryItem->setText(0, category);
        menuTree->addTopLevelItem(categoryItem);

        if (category == "Gestion emprunts") {
            for (const QString &action : loanActions) {
                QTreeWidgetItem *actionItem = new QTreeWidgetItem(categoryItem);
                actionItem->setText(0, action);
            }
        } else {
            for (const QString &action : bookMemberActions) {
                QTreeWidgetItem *actionItem = new QTreeWidgetItem(categoryItem);
                actionItem->setText(0, action);
            }
        }
    }
}
void MainWindow::onMenuItemClicked(QTreeWidgetItem *item, int column)
{
    if (!item->parent()) {
        item->setExpanded(!item->isExpanded());
    } else {
        QString action = item->text(0);
        QString category = item->parent()->text(0);

        if (category == "Gestion livres") {
            if (action == "Ajouter") onAddBook();
            else if (action == "Modifier") onModifyBook();
            else if (action == "Supprimer") onDeleteBook();
            else if (action == "Rechercher") onSearchBook();
        } else if (category == "Gestion membres") {
            if (action == "Ajouter") onAddMember();
            else if (action == "Modifier") updateMember();
            else if (action == "Supprimer") onDeleteMember();
            else if (action == "Rechercher") onSearchMember();
        } else if (category == "Gestion emprunts") {
            if (action == "Ajouter new emprunt") onAddLoan();
        }
    }
}

// Implémentez ces fonctions selon vos besoins
void MainWindow::onAddMember() {
    MemberDialog dialog(this, "Ajouter");

    if (dialog.exec() == QDialog::Accepted) {
        QString id = dialog.getId();
        QString name = dialog.getName();
        QString surname = dialog.getSurname();
        QString gender = dialog.getGender();
        QString email = dialog.getEmail();
        QString dateString = dialog.getRegistrationDate();
        QDate registrationDate = QDate::fromString(dateString, "yyyy-MM-dd");

        if (dbManager.addMember(id, name, surname, gender, email, registrationDate)) {
            QMessageBox::information(this, "Ajouterr un membre", "Le membre a été ajouté avec succès !");
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible d'ajouter le membre.");
        }
    }}

void MainWindow::updateMember()
{
    MemberDialog dialog(this, "Modifier");

    if (dialog.exec() == QDialog::Accepted) {
        QString id = dialog.getId();
        QString name = dialog.getName();
        QString surname = dialog.getSurname();
        QString gender = dialog.getGender();
        QString email = dialog.getEmail();
        QString dateString = dialog.getRegistrationDate();
        QDate registrationDate = QDate::fromString(dateString, "yyyy-MM-dd");

        if (dbManager.updateMember(id, name, surname, gender, email, registrationDate)) {
            QMessageBox::information(this, "Modifier un membre", "Le membre a été modifié avec succès !");
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de modifier le membre.");
        }
    }
}
void MainWindow::onDeleteMember() {
    QMessageBox::information(this, "Delete Member", "Function to delete a member.");
}

void MainWindow::onSearchMember() {
    QMessageBox::information(this, "Search Member", "Function to search a member.");
}


void MainWindow::onAddBook() {
    BookDialog dialog(this, "Ajouter");
    if (dialog.exec() == QDialog::Accepted) {
        if (dbManager.addBook(dialog.getId(), dialog.getTitle(), dialog.getAuthor(), dialog.getGenre(), dialog.getAddDate())) {
            QMessageBox::information(this, "Ajouter un livre", "Livre ajouté avec succès !");
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible d'ajouter le livre.");
        }
    }
}

void MainWindow::onModifyBook()
{
    BookDialog dialog(this, "Modifier");
    dialog.exec();
}
void MainWindow::onDeleteBook()
{
    bool ok;
    QString bookId = QInputDialog::getText(this, "Supprimer un livre",
                                           "Entrez l'ID du livre à supprimer :", QLineEdit::Normal,
                                           "", &ok);
    if (ok && !bookId.isEmpty())
    {
        // Ici, vous pourriez vérifier si l'ID existe dans votre base de données
        // Pour l'instant, nous allons simplement afficher un message de confirmation

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Supprimer un livre",
                                      "Êtes-vous sûr de vouloir supprimer le livre avec l'ID : " + bookId + " ?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Ici, vous ajouteriez le code pour supprimer réellement le livre de votre base de données
            QMessageBox::information(this, "Supprimer un livre", "Livre avec l'ID " + bookId + " supprimé avec succès !");
        }
    }
    else if (ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de livre valide.");
    }
}
void MainWindow::onSearchBook()
{
    bool ok;
    QString searchTerm = QInputDialog::getText(this, "Rechercher un livre",
                                               "Entrez le titre ou l'ID du livre :", QLineEdit::Normal,
                                               "", &ok);
    if (ok && !searchTerm.isEmpty()) {
        QMessageBox::information(this, "Rechercher un livre", "Recherche effectuée pour : " + searchTerm);
    }
}


void MainWindow::onAddLoan() {
    AddLoanDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Emprunt", "Emprunt ajouté avec succès !");
    }
}


QWidget* MainWindow::createContentArea()
{
    QWidget *contentArea = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(contentArea);

    // Message de bienvenue
    QLabel *welcomeLabel = new QLabel("Bienvenue dans la gestion de la bibliothèque !");
    contentLayout->addWidget(welcomeLabel);

    // Zone de statistiques
    QWidget *statsWidget = createStatsWidget();
    contentLayout->addWidget(statsWidget);

    // Zone des derniers livres
    QLabel *latestBooksLabel = new QLabel("Les livres à la lune");
    QWidget *booksWidget = createLatestBooksWidget();

    contentLayout->addWidget(latestBooksLabel);
    contentLayout->addWidget(booksWidget);

    contentLayout->addStretch();

    return contentArea;
}
QWidget* MainWindow::createStatsWidget()
{
    QWidget *statsWidget = new QWidget;
    QHBoxLayout *statsLayout = new QHBoxLayout(statsWidget);

    QStringList stats = {"Ouvrages", "Livres plus Empruntés", "Livres en Retard"};
    QStringList colors = {"#e67e22", "#27ae60", "#8e44ad"};
    QStringList values = {"8", "4", "7"};

    for (int i = 0; i < stats.size(); ++i) {
        QFrame *statBox = new QFrame;
        statBox->setFrameShape(QFrame::Box);
        statBox->setStyleSheet("background-color: " + colors[i] + "; color: white; font-size: 18px;");

        QVBoxLayout *boxLayout = new QVBoxLayout(statBox);
        boxLayout->addWidget(new QLabel(stats[i]));
        boxLayout->addWidget(new QLabel(values[i]), 0, Qt::AlignCenter);

        statsLayout->addWidget(statBox);
    }

    return statsWidget;
}

QWidget *MainWindow::createLatestBooksWidget() {
    QWidget *booksWidget = new QWidget;
    QGridLayout *booksLayout = new QGridLayout(booksWidget);

    // Tableau d'exemple pour les noms de fichiers d'images
    QStringList bookImages = {
        "img1.jpg", "img2.jpg", "img3.png", "img4.jpg", "img5.jpg",
        "img6.jpg", "img7.jpg", "img8.jpg", "img9.jpg", "img10.jpg"
    };

    // Ajoutez les couvertures de livres réelles
    int row = 0;
    int col = 0;
    for (const QString &imageFile : bookImages) {
        QLabel *bookCover = new QLabel;
        bookCover->setFixedSize(100, 150);

        // Charger l'image depuis les ressources
        QPixmap pixmap(":/images/" + imageFile);
        bookCover->setPixmap(pixmap.scaled(bookCover->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Style pour la bordure
        bookCover->setStyleSheet("border: 1px solid #95a5a6;");

        // Ajouter le livre au layout
        booksLayout->addWidget(bookCover, row, col);

        // Passer à la colonne suivante
        col++;
        if (col >= 5) { // Si 5 images sont ajoutées, passer à la ligne suivante
            col = 0;
            row++;
        }
    }

    return booksWidget;
}




MainWindow::~MainWindow() {
    // Code de nettoyage si nécessaire
}


