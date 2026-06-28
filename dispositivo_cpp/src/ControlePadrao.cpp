#include "../include/ControlePadrao.h"
#include "../include/EstacaoBombeamento.h"

void ControlePadrao::aplicar(EstacaoBombeamento& estacao)
{
    float nivel = estacao.getSensorNivel().ler();
    float temperatura = estacao.getSensorTemperatura().ler();
    float qualidade = estacao.getSensorQualidadeAgua().ler();

    // Regra 1: nível baixo liga a bomba principal
    if (nivel < 31)
    {
        estacao.getBombaPrincipal().ligar();
        estacao.getAlarmeNivelBaixo().ativar();
    }

    // Regra 2: nível alto desliga as bombas
    if (nivel > 86)
    {
        estacao.getBombaPrincipal().desligar();
        estacao.getBombaReserva().desligar();
        estacao.getAlarmeNivelBaixo().desativar();
    }

    // Regra 3: temperatura alta bloqueia as bombas
    if (temperatura > 80)
    {
        estacao.getBombaPrincipal().bloquear();
        estacao.getBombaReserva().bloquear();
        estacao.getAlarmeTemperaturaAlta().ativar();
    }

    // Regra 4: qualidade ruim ativa alarme
    if (qualidade < 70)
    {
        estacao.getAlarmeQualidadeRuim().ativar();
    }
}