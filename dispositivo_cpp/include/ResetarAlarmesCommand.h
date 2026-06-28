#ifndef RESETAR_ALARMES_COMMAND_H
#define RESETAR_ALARMES_COMMAND_H

#include "Comando.h"
#include "EstacaoBombeamento.h"

class ResetarAlarmesCommand : public Comando
{
private:
    EstacaoBombeamento& estacao;

public:
    ResetarAlarmesCommand(EstacaoBombeamento& estacao) : estacao(estacao) {}

    void executar() override
    {
        estacao.getAlarmeNivelBaixo().desativar();
        estacao.getAlarmeTemperaturaAlta().desativar();
        estacao.getAlarmeQualidadeRuim().desativar();
    }
};

#endif