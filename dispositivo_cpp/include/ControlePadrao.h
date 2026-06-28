#ifndef CONTROLE_PADRAO_H
#define CONTROLE_PADRAO_H

#include "EstrategiaControle.h"

class ControlePadrao : public EstrategiaControle
{
public:
    void aplicar(EstacaoBombeamento& estacao) override;
};

#endif