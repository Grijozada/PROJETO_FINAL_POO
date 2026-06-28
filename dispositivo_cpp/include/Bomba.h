#ifndef BOMBA_H
#define BOMBA_H

#include <string>

class Bomba
{
private:
    std::string nome;
    bool ligada;
    bool bloqueada;
    std::string status;

public:
    Bomba(std::string nome);

    void ligar();
    void desligar();
    void bloquear();
    void desbloquear();

    bool estaLigada() const;
    bool estaBloqueada() const;

    std::string getNome() const;
    std::string getStatus() const;
};

#endif