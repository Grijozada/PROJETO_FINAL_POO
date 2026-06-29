# AI_LOG – Registro de Uso de Inteligência Artificial

**Projeto:** Mini-SCADA para Estação de Bombeamento EB-161  
**Disciplina:** Programação Orientada a Objetos  
**Professor:** Rafael Emerick  

**Integrantes:**
- Gustavo Grijó
- Victor

---

# Objetivo

Este documento registra a utilização de ferramentas de Inteligência Artificial durante o desenvolvimento do projeto, indicando como elas auxiliaram na compreensão dos conceitos, na implementação das funcionalidades e na resolução de problemas encontrados ao longo do trabalho.

---

# Registro de uso da IA

| Data | Ferramenta | Solicitação | Aproveitado no projeto | Ajustes realizados |
|------|------------|-------------|-------------------------|--------------------|
| **21/06/2026** | ChatGPT | Análise do enunciado e organização dos requisitos | Estrutura inicial do projeto e checklist de requisitos | Organização adaptada à proposta da dupla |
| **21/06/2026** | ChatGPT | Sugestão de arquitetura do projeto | Separação entre dispositivo C++ e supervisor Python | Estrutura reorganizada conforme necessidade |
| **22/06/2026** | ChatGPT | Modelagem das classes principais | Classes Sensor, Bomba, Alarme e Estação de Bombeamento | Nomes e atributos revisados pela dupla |
| **22/06/2026** | ChatGPT | Explicação sobre herança, polimorfismo e encapsulamento | Implementação da hierarquia de sensores | Adequações para atender aos requisitos da disciplina |
| **23/06/2026** | ChatGPT | Implementação do padrão Strategy | Classe EstratégiaControle e ControlePadrao | Pequenos ajustes durante os testes |
| **23/06/2026** | ChatGPT | Implementação do padrão Command | Comandos de ligar, desligar, manutenção e reset de alarmes | Código adaptado para a estrutura do projeto |
| **24/06/2026** | ChatGPT | Implementação da falha simulada | Sensor de nível travado por determinado número de ciclos | Ajustes durante a compilação |
| **24/06/2026** | ChatGPT | Exportação das informações em JSON | Classe JsonExporter e arquivo de comunicação | Correção de erros relacionados ao uso de const |
| **25/06/2026** | ChatGPT | Desenvolvimento do supervisor em Streamlit | Interface inicial com leituras, bombas e alarmes | Interface reorganizada pela dupla |
| **25/06/2026** | ChatGPT | Persistência dos dados | Armazenamento em CSV e SQLite | Ajustes nos caminhos dos arquivos |
| **26/06/2026** | ChatGPT | Implementação dos testes automatizados | Testes das regras principais do sistema | Correção de erros encontrados durante a execução |
| **26/06/2026** | ChatGPT | Configuração do GitHub Actions | Workflow de compilação e testes automáticos | Correções após falhas de integração |
| **27/06/2026** | ChatGPT | Revisão da documentação | README, organização do repositório e AI_LOG | Revisão final antes da entrega |

---

# Como a IA foi utilizada

Durante o desenvolvimento do projeto, a Inteligência Artificial foi utilizada como ferramenta de apoio para:

- compreender os requisitos do trabalho;
- esclarecer conceitos de Programação Orientada a Objetos;
- auxiliar na modelagem das classes;
- sugerir estruturas de código;
- explicar mensagens de erro de compilação;
- auxiliar na implementação dos padrões Strategy e Command;
- orientar a integração entre C++ e Python;
- auxiliar na configuração do GitHub Actions;
- apoiar a elaboração da documentação.

Todo o código sugerido foi analisado, testado e adaptado pela dupla antes de ser incorporado ao projeto.

---

# Decisões técnicas

Durante o desenvolvimento foram adotadas as seguintes decisões:

- Utilização de C++ para simulação do dispositivo.
- Utilização de Python com Streamlit para o supervisor.
- Comunicação entre os módulos utilizando JSON.
- Persistência dos dados em CSV e SQLite.
- Utilização do padrão Strategy para as regras de controle.
- Utilização do padrão Command para os comandos do operador.
- Utilização do GitHub Actions para integração contínua.

---

# Limitações

Atualmente o sistema apresenta algumas limitações:

- Comunicação realizada por arquivo JSON, sem comunicação em rede.
- Interface do supervisor simplificada para fins acadêmicos.
- Simulação dos sensores, sem conexão com dispositivos físicos.

---

# Conclusão

A Inteligência Artificial foi utilizada exclusivamente como ferramenta de apoio ao desenvolvimento, contribuindo para a compreensão dos conceitos, organização do projeto e resolução de problemas encontrados durante a implementação.

Todo o código foi revisado, compilado, testado e ajustado pela dupla antes de sua utilização, garantindo o entendimento das soluções implementadas e o atendimento aos requisitos da disciplina.
