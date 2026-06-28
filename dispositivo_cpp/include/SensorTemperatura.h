#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "Sensor.h"

class SensorTemperatura : public Sensor
{
public:
    SensorTemperatura() : Sensor("TEMPERATURA", "C") {}

    float ler() override
    {
        return valor;
    }
};

#endif