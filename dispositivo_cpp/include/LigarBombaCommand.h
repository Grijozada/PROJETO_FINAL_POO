#ifndef LIGAR_BOMBA_COMMAND_H
#define LIGAR_BOMBA_COMMAND_H

#include "Comando.h"
#include "Bomba.h"

class LigarBombaCommand : public Comando
{
private:
    Bomba& bomba;

public:
    LigarBombaCommand(Bomba& bomba) : bomba(bomba) {}

    void executar() override
    {
        bomba.ligar();
    }
};

#endif