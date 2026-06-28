#include "../include/EstacaoBombeamento.h"

EstacaoBombeamento::EstacaoBombeamento()
    : bombaPrincipal("Bomba Principal"),
      bombaReserva("Bomba Reserva"),
      alarmeNivelBaixo("ALM_NIVEL_BAIXO", "Nivel da agua abaixo do minimo", "ALTA"),
      alarmeTemperaturaAlta("ALM_TEMPERATURA_ALTA", "Temperatura da agua acima do limite", "MEDIA"),
      alarmeQualidadeRuim("ALM_QUALIDADE_RUIM", "Qualidade da agua inadequada", "ALTA"),
      estrategia(nullptr)
{
}

void EstacaoBombeamento::executarControle()
{
    if (estrategia != nullptr)
    {
        estrategia->aplicar(*this);
    }
}

void EstacaoBombeamento::setEstrategia(EstrategiaControle* novaEstrategia)
{
    estrategia = novaEstrategia;
}

SensorNivel& EstacaoBombeamento::getSensorNivel()
{
    return sensorNivel;
}

SensorPressao& EstacaoBombeamento::getSensorPressao()
{
    return sensorPressao;
}

SensorTemperatura& EstacaoBombeamento::getSensorTemperatura()
{
    return sensorTemperatura;
}

SensorQualidadeAgua& EstacaoBombeamento::getSensorQualidadeAgua()
{
    return sensorQualidadeAgua;
}

Bomba& EstacaoBombeamento::getBombaPrincipal()
{
    return bombaPrincipal;
}

Bomba& EstacaoBombeamento::getBombaReserva()
{
    return bombaReserva;
}

Alarme& EstacaoBombeamento::getAlarmeNivelBaixo()
{
    return alarmeNivelBaixo;
}

Alarme& EstacaoBombeamento::getAlarmeTemperaturaAlta()
{
    return alarmeTemperaturaAlta;
}

Alarme& EstacaoBombeamento::getAlarmeQualidadeRuim()
{
    return alarmeQualidadeRuim;
}
