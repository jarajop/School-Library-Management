#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QTextEdit>
#include <QTreeWidget>
#include <QLabel>
#include <QFrame>
#include <QTreeWidgetItem>
#include <QDialog>
#include <QMessageBox>
#include "bookdialog.h"
#include "databasemanager.h"  // Inclure DatabaseManager
#include "ui_mainwindow.h"
#include "addloandialog.h"  // Inclure ici





class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;  // Déclaration de l'interface générée par Qt Designer
    DatabaseManager dbManager;  // Ajouter l'objet dbManager
    QWidget* createStatsWidget();  // Déclaration de la fonction
    QWidget* createSidebar();
    QWidget* createContentArea();
    QWidget* createLatestBooksWidget();
    QLabel *labelNbOuvrages;  // Déclaration du QLabel pour afficher le nombre d'ouvrages



    void setupMenuTree();
    void bookAdded();  // Signal émis après l'ajout d'un livre


private slots:
    void onMenuItemClicked(QTreeWidgetItem *item, int column);


    // Gestion des livres
    void onAddBook();
    void onModifyBook();
    void onDeleteBook();
    void onSearchBook();


    // Gestion des membres
    void onAddMember();
    void updateMember();
    void onDeleteMember();
    void onSearchMember();

    // Gestion des emprunts
    void onAddLoan();


private:
    QTreeWidget *menuTree;
    QWidget *statsWidget;  // Widget pour afficher les statistiques

};



#endif // MAINWINDOW_H


