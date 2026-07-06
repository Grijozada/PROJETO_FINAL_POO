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

    int ciclo = 0;

    while (true)
    {
        simulador.atualizar(estacao);

        // Simula uma falha no sensor de nível
        if (ciclo == 20)
        {
            std::cout << "\n===== FALHA SIMULADA =====" << std::endl;
            std::cout << "Sensor de nivel travado por 10 ciclos." << std::endl;

            estacao.getSensorNivel().simularTravamento(10);
        }

        estacao.executarControle();

        JsonExporter::salvar(estacao, "dispositivo_cpp/dados_estacao.json");

        ciclo++;

        Sleep(2000);
    }

    return 0;
}