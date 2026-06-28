#ifndef ALARME_H
#define ALARME_H

#include <string>

class Alarme
{
private:
    std::string codigo;
    std::string mensagem;
    std::string severidade;
    bool ativo;

public:
    Alarme(std::string codigo, std::string mensagem, std::string severidade);

    void ativar();
    void desativar();

    bool estaAtivo() const;

    std::string getCodigo() const;
    std::string getMensagem() const;
    std::string getSeveridade() const;
};

#endif