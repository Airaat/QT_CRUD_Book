#include "editform.h"
#include "ui_editform.h"

EditForm::EditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditForm)
{
    ui->setupUi(this);
}

EditForm::~EditForm()
{
    delete ui;
}

void EditForm::on_OK_pushbutton_clicked()
{
//    int err = 0;
//    Car car = new Car();
//    car.setModel(ui->name_edit->text());
//    car.setYear(ui->year_edit->text());
//    car.setMileage(ui->mileage_edit->text());
//    car.setBody(ui->body_edit->currentText());
//    car.setGearbox(ui->gearbox_edit->currentText());
//    car.setDrive(ui->drive_edit->currentText());
//    car.setPosition(ui->position_edit->currentIndex());
}


void EditForm::on_Cancel_pushbutton_clicked()
{
    close();
}

