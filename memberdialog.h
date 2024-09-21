#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class MemberDialog : public QDialog
{
    Q_OBJECT

public:
    QString getId();
    QString getName();
    QString getGender();
    QString getEmail();
    QString getSurname();
    QString getRegistrationDate();



    explicit MemberDialog(QWidget *parent = nullptr, const QString &mode = "Ajouter");
    ~MemberDialog();

private slots:
    void onSave();

private:
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QComboBox *genderComboBox;
    QLineEdit *emailEdit;
    QDateEdit *registrationDateEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QString mode;
};

#endif // MEMBERDIALOG_H
