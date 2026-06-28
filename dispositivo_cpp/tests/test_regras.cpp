#include <cassert>
#include <iostream>

#include "../include/EstacaoBombeamento.h"
#include "../include/ControlePadrao.h"

int main()
{
    ControlePadrao controle;

    // ============================
    // Teste 1 - Nível baixo
    // ============================

    EstacaoBombeamento estacao1;
    estacao1.setEstrategia(&controle);

    estacao1.getSensorNivel().setValor(25);
    estacao1.getSensorTemperatura().setValor(35);
    estacao1.getSensorQualidadeAgua().setValor(90);

    estacao1.executarControle();

    assert(estacao1.getBombaPrincipal().estaLigada());
    assert(estacao1.getAlarmeNivelBaixo().estaAtivo());

    // ============================
    // Teste 2 - Temperatura alta
    // ============================

    EstacaoBombeamento estacao2;
    estacao2.setEstrategia(&controle);

    estacao2.getSensorNivel().setValor(50);
    estacao2.getSensorTemperatura().setValor(85);
    estacao2.getSensorQualidadeAgua().setValor(90);

    estacao2.executarControle();

    assert(estacao2.getBombaPrincipal().estaBloqueada());
    assert(estacao2.getAlarmeTemperaturaAlta().estaAtivo());

    // ============================
    // Teste 3 - Qualidade ruim
    // ============================

    EstacaoBombeamento estacao3;
    estacao3.setEstrategia(&controle);

    estacao3.getSensorNivel().setValor(50);
    estacao3.getSensorTemperatura().setValor(35);
    estacao3.getSensorQualidadeAgua().setValor(60);

    estacao3.executarControle();

    assert(estacao3.getAlarmeQualidadeRuim().estaAtivo());

    // ============================
    // Teste 4 - Nível alto
    // ============================

    EstacaoBombeamento estacao4;
    estacao4.setEstrategia(&controle);

    estacao4.getSensorNivel().setValor(95);
    estacao4.getBombaPrincipal().ligar();

    estacao4.executarControle();

    assert(!estacao4.getBombaPrincipal().estaLigada());

    // ============================
    // Teste 5 - Falha simulada
    // ============================

    EstacaoBombeamento estacao5;

    estacao5.getSensorNivel().setValor(40);
    estacao5.getSensorNivel().simularTravamento(10);

    estacao5.getSensorNivel().setValor(70);

    assert(estacao5.getSensorNivel().ler() == 40);

    std::cout << "==================================" << std::endl;
    std::cout << "Todos os testes executados com sucesso!" << std::endl;
    std::cout << "==================================" << std::endl;

    return 0;
}