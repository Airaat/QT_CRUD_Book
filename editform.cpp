#include "editform.h"
#include "ui_editform.h"

EditForm::EditForm(QWidget *parent) :
    QWidget(parent/*, Qt::FramelessWindowHint*/),
    ui(new Ui::EditForm)
{
    ui->setupUi(this);

    connect(ui->btn_ok, &QPushButton::clicked, this, &EditForm::Confirm);
    connect(ui->btn_cancel, &QPushButton::clicked, this, &EditForm::Decline);

    _rowindex = -1;
    clearWidget();
}

EditForm::~EditForm()
{
    delete ui;
}

void EditForm::Confirm()
{
    int err = 0;
    Car car;
    QString modelText = ui->edit_name->text();
    QString yearText = ui->edit_year->text();
    QString mileageText = ui->edit_milage->text();
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

    car.setBody(ui->edit_body->currentText().toStdString());
    car.setGearbox(ui->edit_gearbox->currentText().toStdString());
    car.setDrive(ui->edit_drive->currentText().toStdString());
    car.setPosition(ui->edit_position->currentIndex());

    if(!err){
        emit addNewRecordRequested(car, _rowindex);
        close();
        clearWidget();
    }
}

void EditForm::Decline()
{
    close();
    clearWidget();
}

void EditForm::clearWidget(){
    ui->edit_name->clear();
    ui->edit_year->clear();
    ui->edit_milage->clear();
    ui->edit_body->setCurrentIndex(-1);
    ui->edit_gearbox->setCurrentIndex(-1);
    ui->edit_drive->setCurrentIndex(-1);
    ui->edit_position->setCurrentIndex(-1);
}

void EditForm::setData(const QString &name, const QString &year, const QString &mileage,
                       const QString &body, const QString &gearbox, const QString &drive,
                       const QString &position){
    ui->edit_name->setText(name);
    ui->edit_year->setText(year);
    ui->edit_milage->setText(mileage);
    int bodyIndex = ui->edit_body->findText(body);
    if (bodyIndex >= 0) {
        ui->edit_body->setCurrentIndex(bodyIndex);
    }

    int gearboxIndex = ui->edit_gearbox->findText(gearbox);
    if (gearboxIndex >= 0) {
        ui->edit_gearbox->setCurrentIndex(gearboxIndex);
    }

    int driveIndex = ui->edit_drive->findText(drive);
    if (driveIndex >= 0) {
        ui->edit_drive->setCurrentIndex(driveIndex);
    }
    ui->edit_position->setCurrentText(position);
}
