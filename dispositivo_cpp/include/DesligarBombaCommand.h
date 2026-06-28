#ifndef DESLIGAR_BOMBA_COMMAND_H
#define DESLIGAR_BOMBA_COMMAND_H

#include "Comando.h"
#include "Bomba.h"

class DesligarBombaCommand : public Comando
{
private:
    Bomba& bomba;

public:
    DesligarBombaCommand(Bomba& bomba) : bomba(bomba) {}

    void executar() override
    {
        bomba.desligar();
    }
};

#endif