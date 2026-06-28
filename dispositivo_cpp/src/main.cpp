#include <iostream>
#include "../include/EstacaoBombeamento.h"
#include "../include/ControlePadrao.h"
#include "../include/LigarBombaCommand.h"
#include "../include/DesligarBombaCommand.h"
#include "../include/ResetarAlarmesCommand.h"
#include "../include/ModoManutencaoCommand.h"
#include <fstream>
#include "../include/JsonExporter.h"

int main()
{
    EstacaoBombeamento estacao;
    ControlePadrao controle;

    estacao.setEstrategia(&controle);

    estacao.getSensorNivel().setValor(25);
    estacao.getSensorTemperatura().setValor(35);
    estacao.getSensorQualidadeAgua().setValor(90);

    estacao.executarControle();

    std::cout << "Status da bomba principal: "
              << estacao.getBombaPrincipal().getStatus()
              << std::endl;

    std::cout << "Alarme de nivel baixo ativo? "
              << estacao.getAlarmeNivelBaixo().estaAtivo()
              << std::endl;

        DesligarBombaCommand comandoDesligar(estacao.getBombaPrincipal());
    comandoDesligar.executar();

    std::cout << "Status apos comando desligar: "
              << estacao.getBombaPrincipal().getStatus()
              << std::endl;

    ModoManutencaoCommand comandoManutencao(estacao);
    comandoManutencao.executar();

    std::cout << "Status apos modo manutencao: "
              << estacao.getBombaPrincipal().getStatus()
              << std::endl;
        JsonExporter::salvar(estacao, "dispositivo_cpp/dados_estacao.json");

    std::cout << "JSON gerado em dispositivo_cpp/dados_estacao.json" << std::endl;          
    return 0;

}