#ifndef SENSOR_QUALIDADE_AGUA_H
#define SENSOR_QUALIDADE_AGUA_H

#include "Sensor.h"

class SensorQualidadeAgua : public Sensor
{
public:
    SensorQualidadeAgua() : Sensor("QUALIDADE_AGUA", "IQA") {}

    float ler() override
    {
        return valor;
    }
};

#endif