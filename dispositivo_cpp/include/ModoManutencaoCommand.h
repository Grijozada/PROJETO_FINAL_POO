#ifndef MODO_MANUTENCAO_COMMAND_H
#define MODO_MANUTENCAO_COMMAND_H

#include "Comando.h"
#include "EstacaoBombeamento.h"

class ModoManutencaoCommand : public Comando
{
private:
    EstacaoBombeamento& estacao;

public:
    ModoManutencaoCommand(EstacaoBombeamento& estacao) : estacao(estacao) {}

    void executar() override
    {
        estacao.getBombaPrincipal().bloquear();
        estacao.getBombaReserva().bloquear();
    }
};

#endif