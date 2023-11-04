#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <mainwindow.h>
#include <car.h>

namespace Ui {
class EditForm;
}

class MainWindow;
class EditForm : public QWidget
{
    Q_OBJECT

public:
    void setData(const QString &name,const QString &year,const QString &mileage,const QString &body,
                 const QString &gearbox, const QString &drive,const QString &position);
    explicit EditForm(QWidget *parent = nullptr);
    ~EditForm();

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

    void clear_widget();
private:
    Ui::EditForm *ui;

signals:
    void addNewRecordRequested(const Car &obj);
};

#endif // EDITFORM_H
