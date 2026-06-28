#ifndef ESTRATEGIA_CONTROLE_H
#define ESTRATEGIA_CONTROLE_H

class EstacaoBombeamento;

class EstrategiaControle
{
public:
    virtual ~EstrategiaControle() {}

    virtual void aplicar(EstacaoBombeamento& estacao) = 0;
};

#endif