#ifndef SENSOR_NIVEL_H
#define SENSOR_NIVEL_H

#include "Sensor.h"

class SensorNivel : public Sensor
{
private:
    bool travado;
    int ciclosTravado;
    float valorTravado;

public:
    SensorNivel()
        : Sensor("NIVEL", "%"), travado(false), ciclosTravado(0), valorTravado(0) {}

    void simularTravamento(int ciclos)
    {
        travado = true;
        ciclosTravado = ciclos;
        valorTravado = valor;
        status = "TRAVADO";
    }

    float ler() override
    {
        if (travado && ciclosTravado > 0)
        {
            ciclosTravado--;

            if (ciclosTravado == 0)
            {
                travado = false;
                status = "NORMAL";
            }

            return valorTravado;
        }

        return valor;
    }

    bool estaTravado() const
    {
        return travado;
    }
};

#endif