#include <iostream>
#include <windows.h>

#include "../include/EstacaoBombeamento.h"
#include "../include/ControlePadrao.h"
#include "../include/JsonExporter.h"
#include "../include/SimuladorSensores.h"

int main()
{
    EstacaoBombeamento estacao;
    ControlePadrao controle;
    SimuladorSensores simulador;

    estacao.setEstrategia(&controle);

    while (true)
    {
        simulador.atualizar(estacao);

        estacao.executarControle();

        JsonExporter::salvar(estacao, "dispositivo_cpp/dados_estacao.json");

        Sleep(2000);
    }

    return 0;
}