#ifndef SENSOR_PRESSAO_H
#define SENSOR_PRESSAO_H

#include "Sensor.h"

class SensorPressao : public Sensor
{
public:
    SensorPressao() : Sensor("PRESSAO", "bar") {}

    float ler() override
    {
        return valor;
    }
};

#endif
