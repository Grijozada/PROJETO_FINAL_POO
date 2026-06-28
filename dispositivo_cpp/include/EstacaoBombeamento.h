#ifndef ESTACAO_BOMBEAMENTO_H
#define ESTACAO_BOMBEAMENTO_H

#include "SensorNivel.h"
#include "SensorPressao.h"
#include "SensorTemperatura.h"
#include "SensorQualidadeAgua.h"
#include "Bomba.h"
#include "Alarme.h"
#include "EstrategiaControle.h"

class EstacaoBombeamento
{
private:
    SensorNivel sensorNivel;
    SensorPressao sensorPressao;
    SensorTemperatura sensorTemperatura;
    SensorQualidadeAgua sensorQualidadeAgua;

    Bomba bombaPrincipal;
    Bomba bombaReserva;

    Alarme alarmeNivelBaixo;
    Alarme alarmeTemperaturaAlta;
    Alarme alarmeQualidadeRuim;

    EstrategiaControle* estrategia;

public:
    EstacaoBombeamento();

    void executarControle();

    SensorNivel& getSensorNivel();
    SensorPressao& getSensorPressao();
    SensorTemperatura& getSensorTemperatura();
    SensorQualidadeAgua& getSensorQualidadeAgua();

    Bomba& getBombaPrincipal();
    Bomba& getBombaReserva();

    Alarme& getAlarmeNivelBaixo();
    Alarme& getAlarmeTemperaturaAlta();
    Alarme& getAlarmeQualidadeRuim();

    void setEstrategia(EstrategiaControle* novaEstrategia);
};

#endif