#include "../include/SimuladorSensores.h"
#include <cmath>

SimuladorSensores::SimuladorSensores()
{
    ciclo = 0;
}

void SimuladorSensores::atualizar(EstacaoBombeamento& estacao)
{
    float nivel = 50 + 35 * std::sin(ciclo * 0.25);
    float temperatura = 45 + 25 * std::sin(ciclo * 0.15);
    float qualidade = 85 - 20 * std::sin(ciclo * 0.18);

    estacao.getSensorNivel().setValor(nivel);
    estacao.getSensorTemperatura().setValor(temperatura);
    estacao.getSensorQualidadeAgua().setValor(qualidade);

    ciclo++;
}