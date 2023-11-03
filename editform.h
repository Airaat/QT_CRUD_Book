#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <car.h>
#include <mainwindow.h>

namespace Ui {
class EditForm;
}

class EditForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditForm(QWidget *parent = nullptr);
    ~EditForm();

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::EditForm *ui;

signals:
    void addNewRecordRequested(const Car &obj);
};

#endif // EDITFORM_H
