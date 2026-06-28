#include "../include/Bomba.h"

Bomba::Bomba(std::string nome)
{
    this->nome = nome;
    this->ligada = false;
    this->bloqueada = false;
    this->status = "DESLIGADA";
}

void Bomba::ligar()
{
    if (!bloqueada)
    {
        ligada = true;
        status = "LIGADA";
    }
}

void Bomba::desligar()
{
    ligada = false;
    status = "DESLIGADA";
}

void Bomba::bloquear()
{
    bloqueada = true;
    ligada = false;
    status = "BLOQUEADA";
}

void Bomba::desbloquear()
{
    bloqueada = false;
    status = "DESLIGADA";
}

bool Bomba::estaLigada() const
{
    return ligada;
}

bool Bomba::estaBloqueada() const
{
    return bloqueada;
}

std::string Bomba::getNome() const
{
    return nome;
}

std::string Bomba::getStatus() const
{
    return status;
}