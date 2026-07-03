import json
import os
import sqlite3
from pathlib import Path

import pandas as pd
import plotly.express as px
import streamlit as st
from streamlit_autorefresh import st_autorefresh

BASE_DIR = Path(__file__).resolve().parent.parent

CAMINHO_JSON = BASE_DIR / "dispositivo_cpp" / "dados_estacao.json"
CAMINHO_CSV = BASE_DIR / "supervisor_python" / "database" / "historico.csv"
CAMINHO_DB = BASE_DIR / "supervisor_python" / "database" / "historico.db"
CAMINHO_COMANDOS = BASE_DIR / "supervisor_python" / "database" / "historico_comandos.csv"

st.set_page_config(
    page_title="Mini-SCADA EB-161",
    page_icon="💧",
    layout="wide"
)

auto_update = st.sidebar.checkbox("Atualização automática", value=True)

if auto_update:
    st_autorefresh(interval=25000, key="refresh")

st.title("💧 Mini-SCADA EB-161")
st.caption(
    "Sistema supervisório para estação de bombeamento com sensores, bombas, alarmes, "
    "histórico em CSV/SQLite e registro de comandos."
)

if not os.path.exists(CAMINHO_JSON):
    st.error("Arquivo JSON ainda não foi gerado pelo dispositivo C++.")
    st.stop()

with open(CAMINHO_JSON, "r", encoding="utf-8") as arquivo:
    dados = json.load(arquivo)

CAMINHO_CSV.parent.mkdir(parents=True, exist_ok=True)

# =========================
# HISTÓRICO CSV
# =========================

df_novo = pd.DataFrame([dados])

if CAMINHO_CSV.exists():
    df_antigo = pd.read_csv(CAMINHO_CSV)
    df_historico = pd.concat([df_antigo, df_novo], ignore_index=True)
else:
    df_historico = df_novo

df_historico.to_csv(CAMINHO_CSV, index=False)

# =========================
# HISTÓRICO SQLITE
# =========================

conexao = sqlite3.connect(CAMINHO_DB)
cursor = conexao.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS historico (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    estacao TEXT,
    nivel REAL,
    temperatura REAL,
    qualidade_agua REAL,
    bomba_principal TEXT,
    alarme_nivel_baixo INTEGER,
    alarme_temperatura_alta INTEGER,
    alarme_qualidade_ruim INTEGER,
    timestamp TEXT
)
""")

cursor.execute("""
INSERT INTO historico (
    estacao,
    nivel,
    temperatura,
    qualidade_agua,
    bomba_principal,
    alarme_nivel_baixo,
    alarme_temperatura_alta,
    alarme_qualidade_ruim,
    timestamp
)
VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
""", (
    dados["estacao"],
    dados["nivel"],
    dados["temperatura"],
    dados["qualidade_agua"],
    dados["bomba_principal"],
    int(dados["alarme_nivel_baixo"]),
    int(dados["alarme_temperatura_alta"]),
    int(dados["alarme_qualidade_ruim"]),
    dados["timestamp"]
))

conexao.commit()
df_sqlite = pd.read_sql_query("SELECT * FROM historico", conexao)
conexao.close()

# =========================
# HISTÓRICO DE COMANDOS
# =========================

comando_atual = "Atualização automática do supervisor"

if dados["bomba_principal"] == "LIGADA":
    comando_atual = "Controle automático: ligar bomba principal"
elif dados["bomba_principal"] == "DESLIGADA":
    comando_atual = "Controle automático: desligar bomba principal"
elif dados["bomba_principal"] == "BLOQUEADA":
    comando_atual = "Comando: modo manutenção / bloqueio da bomba"

registro_comando = {
    "timestamp": dados["timestamp"],
    "comando": comando_atual,
    "origem": "Supervisor / Dispositivo C++",
    "status_bomba": dados["bomba_principal"]
}

df_comando_novo = pd.DataFrame([registro_comando])

if CAMINHO_COMANDOS.exists():
    df_comandos_antigo = pd.read_csv(CAMINHO_COMANDOS)
    df_comandos = pd.concat([df_comandos_antigo, df_comando_novo], ignore_index=True)
else:
    df_comandos = df_comando_novo

df_comandos.to_csv(CAMINHO_COMANDOS, index=False)

# =========================
# SIDEBAR
# =========================

st.sidebar.header("📌 Informações da Estação")
st.sidebar.write(f"**Estação:** {dados['estacao']}")
st.sidebar.write("**ID da dupla:** 161")
st.sidebar.write("**Comunicação:** JSON")
st.sidebar.write("**Persistência:** CSV + SQLite")
st.sidebar.write(f"**Última leitura:** {dados['timestamp']}")

st.sidebar.header("⚙️ Limites de controle")
st.sidebar.write("Nível baixo: < 31%")
st.sidebar.write("Nível alto: > 86%")
st.sidebar.write("Temperatura alta: > 80°C")
st.sidebar.write("Qualidade ruim: < 70 IQA")

# =========================
# CARDS PRINCIPAIS
# =========================

st.subheader("📊 Leituras atuais")

col1, col2, col3, col4 = st.columns(4)

col1.metric("Nível da água", f"{dados['nivel']} %")
col2.metric("Temperatura", f"{dados['temperatura']} °C")
col3.metric("Qualidade da água", f"{dados['qualidade_agua']} IQA")
col4.metric("Bomba principal", dados["bomba_principal"])

# =========================
# RESUMO OPERACIONAL
# =========================

alarmes_ativos = (
    int(dados["alarme_nivel_baixo"])
    + int(dados["alarme_temperatura_alta"])
    + int(dados["alarme_qualidade_ruim"])
)

st.subheader("🏭 Resumo operacional")

r1, r2, r3 = st.columns(3)

r1.metric("Alarmes ativos", alarmes_ativos)
r2.metric("Registros CSV", len(df_historico))
r3.metric("Registros SQLite", len(df_sqlite))

# =========================
# ABAS
# =========================

aba1, aba2, aba3, aba4 = st.tabs([
    "📋 Leituras",
    "📈 Gráficos",
    "🚨 Alarmes",
    "🕹️ Comandos"
])

with aba1:
    st.subheader("Tabela de leituras atuais")
    df_atual = pd.DataFrame([dados])
    st.dataframe(df_atual, width="stretch")

    st.subheader("Histórico em CSV")
    st.dataframe(df_historico.tail(100), width="stretch")

    st.subheader("Histórico em SQLite")
    st.dataframe(df_sqlite.tail(100), width="stretch")

with aba2:
    st.subheader("📈 Histórico das variáveis da estação")

    df_grafico = df_historico.copy()
    df_grafico["timestamp"] = pd.to_datetime(df_grafico["timestamp"], errors="coerce")
    df_grafico = df_grafico.dropna(subset=["timestamp"])

    if len(df_grafico) < 2:
        st.warning("Ainda há poucos dados para formar gráficos.")
    else:
        fig1 = px.line(
            df_grafico,
            x="timestamp",
            y=["nivel", "temperatura"],
            title="Nível da água e temperatura ao longo do tempo",
            labels={
                "timestamp": "Horário",
                "value": "Valor",
                "variable": "Variável"
            }
        )
        st.plotly_chart(fig1, width="stretch")

        fig2 = px.line(
            df_grafico,
            x="timestamp",
            y="qualidade_agua",
            title="Qualidade da água ao longo do tempo",
            labels={
                "timestamp": "Horário",
                "qualidade_agua": "Qualidade da água (IQA)"
            }
        )
        st.plotly_chart(fig2, width="stretch")

with aba3:
    st.subheader("Lista de alarmes")

    alarmes = [
        {
            "alarme": "Nível baixo",
            "ativo": int(dados["alarme_nivel_baixo"]),
            "prioridade": "Alta"
        },
        {
            "alarme": "Temperatura alta",
            "ativo": int(dados["alarme_temperatura_alta"]),
            "prioridade": "Média"
        },
        {
            "alarme": "Qualidade da água ruim",
            "ativo": int(dados["alarme_qualidade_ruim"]),
            "prioridade": "Alta"
        }
    ]

    for alarme in alarmes:
        if alarme["ativo"]:
            st.error(f"🔴 ALARME ATIVO: {alarme['alarme']} | Prioridade: {alarme['prioridade']}")
        else:
            st.success(f"🟢 Normal: {alarme['alarme']}")

    st.dataframe(pd.DataFrame(alarmes), width="stretch")

with aba4:
    st.subheader("Histórico de comandos")

    st.dataframe(df_comandos.tail(100), width="stretch")

    st.info(
        "Os comandos são registrados a partir do estado operacional gerado pelo dispositivo C++. "
        "Em uma aplicação industrial real, esses comandos poderiam ser enviados diretamente "
        "do supervisor para o controlador."
    )

st.caption(
    "Projeto acadêmico de Programação Orientada a Objetos | Professor Rafael Emerick | "
    "Gustavo Grijó e Victor"
)