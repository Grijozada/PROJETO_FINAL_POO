#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor
{
protected:
    std::string tag;
    float valor;
    std::string unidade;
    std::string status;

public:
    Sensor(std::string tag, std::string unidade)
        : tag(tag), valor(0.0), unidade(unidade), status("NORMAL") {}

    virtual ~Sensor() {}

    virtual float ler() = 0;

    std::string getTag() const
    {
        return tag;
    }

    float getValor() const
    {
        return valor;
    }

    std::string getUnidade() const
    {
        return unidade;
    }

    std::string getStatus() const
    {
        return status;
    }

    void setValor(float novoValor)
    {
        valor = novoValor;
    }

    void setStatus(std::string novoStatus)
    {
        status = novoStatus;
    }
};

#endif