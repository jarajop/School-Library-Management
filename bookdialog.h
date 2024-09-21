#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>


class BookDialog : public QDialog
{
    Q_OBJECT

public:
    QString getId() const { return idEdit->text(); }
    QString getTitle() const { return titleEdit->text(); }
    QString getAuthor() const { return authorEdit->text(); }
    QString getGenre() const { return genreEdit->text(); }
    QDate getAddDate() const { return addDateEdit->date(); }
    explicit BookDialog(QWidget *parent = nullptr, const QString &mode = "Ajouter");
    ~BookDialog();

private slots:
    void onSave();

private:
    QLineEdit *idEdit;
    QLineEdit *titleEdit;
    QLineEdit *authorEdit;
    QLineEdit *genreEdit;
    QDateEdit *addDateEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QString mode;
};

#endif // BOOKDIALOG_H
