#ifndef JSON_EXPORTER_H
#define JSON_EXPORTER_H

#include <string>
#include "EstacaoBombeamento.h"

class JsonExporter
{
public:
    static void salvar(EstacaoBombeamento& estacao, const std::string& caminho);
};

#endif