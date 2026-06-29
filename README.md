# Mini-SCADA para Estação de Bombeamento – EB-161

## Programação Orientada a Objetos

**Professor:** Rafael Emerick

**Integrantes**

- Gustavo Grijó
- Victor

---

# Sobre o projeto

Este projeto consiste no desenvolvimento de um **Mini-SCADA** para monitoramento e controle de uma estação de bombeamento de água.

O sistema foi dividido em duas partes principais:

- **Dispositivo (C++)**: responsável pela simulação dos sensores, bombas, alarmes e regras de controle.
- **Supervisor (Python + Streamlit)**: responsável pela visualização das informações da estação, histórico das leituras e persistência dos dados.

A comunicação entre o dispositivo e o supervisor é realizada através de um arquivo JSON.

---

# Objetivos

O projeto tem como objetivo aplicar os principais conceitos de Programação Orientada a Objetos em um sistema de automação industrial.

Entre os conceitos utilizados estão:

- Herança
- Polimorfismo
- Encapsulamento
- Classes Abstratas
- Sobrescrita de métodos
- Padrões de Projeto

---

# Estrutura do Projeto

```
PROJETO_FINAL_POO
│
├── .github/
│   └── workflows/
│       └── ci.yml
│
├── dispositivo_cpp/
│   ├── include/
│   ├── src/
│   ├── tests/
│   └── dados_estacao.json
│
├── supervisor_python/
│   ├── database/
│   ├── assets/
│   └── app.py
│
├── README.md
├── AI_LOG.md
└── .gitignore
```

---

# Tecnologias Utilizadas

## Dispositivo

- C++
- Programação Orientada a Objetos

## Supervisor

- Python
- Streamlit
- Pandas
- SQLite

## Controle de versão

- Git
- GitHub
- GitHub Actions

---

# Sensores

O sistema possui quatro sensores:

- Sensor de Nível
- Sensor de Pressão
- Sensor de Temperatura
- Sensor de Qualidade da Água

Todos os sensores são derivados da classe abstrata **Sensor**, permitindo reutilização de código através da herança.

---

# Atuadores

O sistema possui:

- Bomba Principal
- Bomba Reserva

As bombas podem assumir diferentes estados:

- Ligada
- Desligada
- Bloqueada (modo manutenção)

---

# Regras de Controle

As principais regras implementadas são:

- Ligar a bomba principal quando o nível estiver baixo;
- Desligar as bombas quando o nível estiver alto;
- Bloquear as bombas quando a temperatura estiver acima do limite;
- Acionar alarmes quando a qualidade da água estiver inadequada.

---

# Alarmes

O sistema monitora três condições críticas:

- Nível baixo;
- Temperatura elevada;
- Baixa qualidade da água.

---

# Falha Simulada

Foi implementada uma falha no Sensor de Nível.

Quando ativada, o sensor permanece fornecendo a mesma leitura durante um número determinado de ciclos, simulando um sensor travado.

---

# Padrões de Projeto

## Strategy

Utilizado para separar as regras de controle da estação.

Classes:

- EstrategiaControle
- ControlePadrao

---

## Command

Utilizado para representar comandos do operador.

Comandos implementados:

- Ligar bomba
- Desligar bomba
- Resetar alarmes
- Modo manutenção

---

# Comunicação entre os módulos

O dispositivo gera um arquivo JSON contendo o estado atual da estação.

Exemplo:

```json
{
  "estacao": "EB-161",
  "nivel": 25,
  "temperatura": 35,
  "qualidade_agua": 90,
  "bomba_principal": "BLOQUEADA",
  "alarme_nivel_baixo": 1,
  "alarme_temperatura_alta": 0,
  "alarme_qualidade_ruim": 0
}
```

Este arquivo é utilizado pelo supervisor para atualização da interface.

---

# Supervisor (Streamlit)

O supervisor apresenta:

- Leituras atuais dos sensores;
- Estado das bombas;
- Lista de alarmes;
- Histórico das leituras;
- Armazenamento em CSV;
- Armazenamento em SQLite.

---

# Persistência dos Dados

Os dados da estação são armazenados de duas maneiras.

## CSV

Permite exportação simples para planilhas.

## SQLite

Permite armazenamento estruturado e consultas futuras.

---

# Testes

Foram implementados testes para validar:

- Acionamento da bomba principal;
- Desligamento das bombas;
- Bloqueio por temperatura;
- Acionamento dos alarmes;
- Funcionamento da falha simulada.

Os testes são executados automaticamente pelo GitHub Actions.

---

# Integração Contínua

O projeto utiliza **GitHub Actions** para:

- Compilar automaticamente o código C++;
- Executar os testes;
- Validar a integridade do projeto a cada atualização enviada ao repositório.

---

# Como Executar

## Dispositivo

Compilar:

```bash
g++ dispositivo_cpp/src/main.cpp dispositivo_cpp/src/Bomba.cpp dispositivo_cpp/src/Alarme.cpp dispositivo_cpp/src/EstacaoBombeamento.cpp dispositivo_cpp/src/ControlePadrao.cpp dispositivo_cpp/src/JsonExporter.cpp -o dispositivo_cpp/estacao.exe
```

Executar:

```bash
./dispositivo_cpp/estacao.exe
```

---

## Supervisor

Instalar dependências:

```bash
pip install streamlit pandas
```

Executar:

```bash
streamlit run supervisor_python/app.py
```

---

# Resultados Obtidos

Durante o desenvolvimento foi possível:

- Implementar um dispositivo em C++;
- Desenvolver um supervisor em Python;
- Integrar os módulos utilizando JSON;
- Armazenar histórico em CSV e SQLite;
- Aplicar padrões de projeto;
- Automatizar testes utilizando GitHub Actions.

---

# Melhorias Futuras

- Comunicação via TCP/IP.
- Dashboard em tempo real.
- Controle remoto das bombas.
- Banco de dados remoto.
- Interface gráfica mais elaborada.
- Autenticação de usuários.

---

# Licença

Projeto desenvolvido exclusivamente para fins acadêmicos na disciplina de Programação Orientada a Objetos.

---

## Autor

**Gustavo Grijó**  
Instituto Federal do Espírito Santo – IFES
