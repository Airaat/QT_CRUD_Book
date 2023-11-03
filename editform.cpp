#include "editform.h"
#include "ui_editform.h"

EditForm::EditForm(QWidget *parent) :
//    QWidget(parent, Qt::FramelessWindowHint),
    QWidget(parent),
    ui(new Ui::EditForm)
{
    ui->setupUi(this);
}

EditForm::~EditForm()
{
    delete ui;
}

void EditForm::on_btn_ok_clicked()
{
    int err = 0;
    Car car;
    QString modelText = ui->name_edit->text();
    QString yearText = ui->year_edit->text();
    QString mileageText = ui->mileage_edit->text();
    if(modelText.isEmpty()){
        err = 1;
    } else {
        car.setModel(modelText.toStdString());
    }
    if(yearText.isEmpty()){
        err = 1;
    } else {
        car.setYear(yearText.toUInt());
    }
    if(mileageText.isEmpty()){
        err = 1;
    } else {
        car.setMileage(mileageText.toUInt());
    }

    car.setBody(ui->body_edit->currentText().toStdString());
    car.setGearbox(ui->gearbox_edit->currentText().toStdString());
    car.setDrive(ui->drive_edit->currentText().toStdString());
    car.setPosition(ui->position_edit->currentIndex());

    if(!err){
        emit addNewRecordRequested(car);
        close();
    }
}

void EditForm::on_btn_cancel_clicked()
{
    close();
}
