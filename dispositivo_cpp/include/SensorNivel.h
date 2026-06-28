#ifndef SENSOR_NIVEL_H
#define SENSOR_NIVEL_H

#include "Sensor.h"

class SensorNivel : public Sensor
{
public:
    SensorNivel() : Sensor("NIVEL", "%") {}

    float ler() override
    {
        return valor;
    }
};

#endif