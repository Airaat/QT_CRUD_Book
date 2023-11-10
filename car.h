#ifndef CAR_H
#define CAR_H
#include <string>
#include <vector>
#include <QList>
#include <QDataStream>

class Car
{
public:
    Car(const std::string &model = "Porsche", size_t year = 2013, size_t mileage = 37000,
        const std::string &body = "Coupe", const std::string &gearbox = "AT",
        const std::string &drive = "RWD", bool position = 0);

    void addCar(const Car &car);
    void removeCar(const Car &car);
    const QList<Car> &getCars() const;

    std::string getModel() const;
    size_t getYear() const;
    size_t getMileage() const;
    std::string getBody() const;
    std::string getGearbox() const;
    std::string getDrive() const;
    bool getPosition() const;

    void setModel(const std::string model);
    void setYear(const size_t year);
    void setMileage(const size_t mileage);
    void setBody(const std::string body);
    void setGearbox(const std::string gearbox);
    void setDrive(const std::string drive);
    void setPosition(const bool position);

    bool operator==(const Car &other) const;
    bool operator!=(const Car &other) const;
    friend QDataStream &operator<<(QDataStream &stream, const Car &car);
    friend QDataStream &operator>>(QDataStream &stream, Car &car);
private:
    std::string _model;
    size_t _year;
    size_t _mileage;
    std::string _body;
    std::string _gearbox;
    std::string _drive;
    bool _position;  // 0 - левый руль, 1 - правый руль

    QList<Car> cars;
};

#endif // CAR_H
