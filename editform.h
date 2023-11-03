#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <car.h>

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
    void on_OK_pushbutton_clicked();

    void on_Cancel_pushbutton_clicked();

private:
    Ui::EditForm *ui;
};

#endif // EDITFORM_H
