#include "car.h"

Car::Car(const std::string &model, size_t year, size_t mileage, const std::string &body, const std::string &gearbox, const std::string &drive, bool position) {
    this->_model = model;
    this->_year = year;
    this->_mileage = mileage;
    this->_body = body;
    this->_gearbox = gearbox;
    this->_drive = drive;
    this->_position = position;
}

std::string Car::getModel() const {
    return _model;
}

size_t Car::getYear() const{
    return _year;
}

size_t Car::getMileage() const{
    return _mileage;
}

std::string Car::getBody() const{
    return _body;
}

std::string Car::getGearbox() const{
    return _gearbox;
}

std::string Car::getDrive() const{
    return _drive;
}

bool Car::getPosition() const{
    return _position;
}

void Car::setModel(const std::string model) {
    this->_model = model;
}

void Car::setYear(const size_t year) {
    this->_year = year;
}

void Car::setMileage(const size_t mileage) {
    this->_mileage = mileage;
}

void Car::setBody(const std::string body) {
    this->_body = body;
}

void Car::setGearbox(const std::string gearbox) {
    this->_gearbox = gearbox;
}

void Car::setDrive(const std::string drive) {
    this->_drive = drive;
}

void Car::setPosition(const bool position) {
    this->_position = position;
}
