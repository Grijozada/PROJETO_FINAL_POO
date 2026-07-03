#include <iostream>
#include <windows.h>
#include <cmath>

#include "../include/EstacaoBombeamento.h"
#include "../include/ControlePadrao.h"
#include "../include/JsonExporter.h"

int main()
{
    ControlePadrao controle;

    int ciclo = 0;

    while (true)
    {
        EstacaoBombeamento estacao;
        estacao.setEstrategia(&controle);

        float nivel = 50 + 35 * std::sin(ciclo * 0.25);
        float temperatura = 45 + 25 * std::sin(ciclo * 0.15);
        float qualidade = 85 - 20 * std::sin(ciclo * 0.18);

        estacao.getSensorNivel().setValor(nivel);
        estacao.getSensorTemperatura().setValor(temperatura);
        estacao.getSensorQualidadeAgua().setValor(qualidade);

        estacao.executarControle();

        JsonExporter::salvar(estacao, "dispositivo_cpp/dados_estacao.json");

        ciclo++;

        Sleep(2000);
    }

    return 0;
}