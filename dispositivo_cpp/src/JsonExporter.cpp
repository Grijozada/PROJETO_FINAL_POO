#include "../include/JsonExporter.h"

#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

void JsonExporter::salvar(EstacaoBombeamento& estacao, const std::string& caminho)
{
    std::ofstream arquivo(caminho);

    // Gera timestamp atual
    std::time_t agora = std::time(nullptr);
    std::tm* tempoLocal = std::localtime(&agora);

    std::ostringstream timestamp;
    timestamp << std::put_time(tempoLocal, "%Y-%m-%d %H:%M:%S");

    arquivo << "{\n";
    arquivo << "  \"timestamp\": \"" << timestamp.str() << "\",\n";
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