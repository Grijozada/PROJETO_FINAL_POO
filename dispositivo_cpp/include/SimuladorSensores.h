#ifndef SIMULADOR_SENSORES_H
#define SIMULADOR_SENSORES_H

#include "EstacaoBombeamento.h"

class SimuladorSensores
{
private:
    int ciclo;

public:
    SimuladorSensores();

    void atualizar(EstacaoBombeamento& estacao);
};

#endif