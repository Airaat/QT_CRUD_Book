#include "car.h"

Car::Car(const std::string &model, size_t year, size_t mileage, const std::string &body, const std::string &gearbox, const std::string &drive, bool position) {
    _model = model;
    _year = year;
    _mileage = mileage;
    _body = body;
    _gearbox = gearbox;
    _drive = drive;
    _position = position;
}

std::string Car::getModel() const { return _model; }
size_t Car::getYear() const{ return _year; }
size_t Car::getMileage() const{ return _mileage; }
std::string Car::getBody() const{ return _body; }
std::string Car::getGearbox() const{ return _gearbox; }
std::string Car::getDrive() const{ return _drive; }
bool Car::getPosition() const{ return _position; }

void Car::setModel(const std::string model) { _model = model; }
void Car::setYear(const size_t year) { _year = year; }
void Car::setMileage(const size_t mileage) { _mileage = mileage; }
void Car::setBody(const std::string body) { _body = body; }
void Car::setGearbox(const std::string gearbox) { _gearbox = gearbox; }
void Car::setDrive(const std::string drive) { _drive = drive; }
void Car::setPosition(const bool position) { _position = position; }

void Car::addCar(const Car &car){ cars.append(car); }
void Car::removeCar(const Car &car){ cars.removeOne(car); }
const QList<Car> &Car::getCars() const{ return cars; }

bool Car::operator==(const Car &other) const {
    return _model == other._model &&
           _year == other._year &&
           _mileage == other._mileage &&
           _body == other._body &&
           _gearbox == other._gearbox &&
           _drive == other._drive &&
           _position == other._position;
}

bool Car::operator!=(const Car &other) const {
    return !(*this == other);
}

QDataStream &operator<<(QDataStream &stream, const Car &car) {
    QString position = (car._position) ? "R" : "L";
    stream << QString::fromStdString(car._model)
           << QString::number(car._year)
           << QString::number(car._mileage)
           << QString::fromStdString(car._body)
           << QString::fromStdString(car._gearbox)
           << QString::fromStdString(car._drive)
           << position;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Car &car) {
    QString model;
    QString year;
    QString mileage;
    QString body;
    QString gearbox;
    QString drive;
    QString position;
    stream >> model >> year >> mileage >> body >> gearbox >> drive >> position;
    car._model = model.toStdString();
    car._year = year.toUInt();
    car._mileage = mileage.toUInt();
    car._body = body.toStdString();
    car._gearbox = gearbox.toStdString();
    car._drive = drive.toStdString();
    car._position = position.toInt();
    return stream;
}


