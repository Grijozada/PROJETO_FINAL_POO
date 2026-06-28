#include "../include/Alarme.h"

Alarme::Alarme(std::string codigo, std::string mensagem, std::string severidade)
{
    this->codigo = codigo;
    this->mensagem = mensagem;
    this->severidade = severidade;
    this->ativo = false;
}

void Alarme::ativar()
{
    ativo = true;
}

void Alarme::desativar()
{
    ativo = false;
}

bool Alarme::estaAtivo() const
{
    return ativo;
}

std::string Alarme::getCodigo() const
{
    return codigo;
}

std::string Alarme::getMensagem() const
{
    return mensagem;
}

std::string Alarme::getSeveridade() const
{
    return severidade;
}