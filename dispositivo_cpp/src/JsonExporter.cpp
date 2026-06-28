#include "../include/JsonExporter.h"
#include <fstream>

void JsonExporter::salvar(EstacaoBombeamento& estacao, const std::string& caminho)
{
    std::ofstream arquivo(caminho);

    arquivo << "{\n";
    arquivo << "  \"estacao\": \"EB-161\",\n";
    arquivo << "  \"nivel\": " << estacao.getSensorNivel().ler() << ",\n";
    arquivo << "  \"temperatura\": " << estacao.getSensorTemperatura().ler() << ",\n";
    arquivo << "  \"qualidade_agua\": " << estacao.getSensorQualidadeAgua().ler() << ",\n";
    arquivo << "  \"bomba_principal\": \"" << estacao.getBombaPrincipal().getStatus() << "\",\n";
    arquivo << "  \"alarme_nivel_baixo\": " << estacao.getAlarmeNivelBaixo().estaAtivo() << ",\n";
    arquivo << "  \"alarme_temperatura_alta\": " << estacao.getAlarmeTemperaturaAlta().estaAtivo() << ",\n";
    arquivo << "  \"alarme_qualidade_ruim\": " << estacao.getAlarmeQualidadeRuim().estaAtivo() << "\n";
    arquivo << "}\n";

    arquivo.close();
}