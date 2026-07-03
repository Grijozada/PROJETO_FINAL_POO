import json
import os
import sqlite3
from pathlib import Path

from streamlit_autorefresh import st_autorefresh
import pandas as pd
import streamlit as st

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

st.title("💧 Mini-SCADA - Estação de Bombeamento EB-161")
st.caption("Sistema supervisório para monitoramento de sensores, bombas, alarmes e histórico operacional.")

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
    st.dataframe(df_atual, use_container_width=True)

    st.subheader("Histórico em CSV")
    st.dataframe(df_historico, use_container_width=True)

    st.subheader("Histórico em SQLite")
    st.dataframe(df_sqlite, use_container_width=True)

with aba2:
    st.subheader("Gráfico histórico das variáveis")

    col_graf1, col_graf2 = st.columns(2)

    with col_graf1:
        st.write("Nível da água e Temperatura")
        grafico_1 = df_historico[["timestamp", "nivel", "temperatura"]].copy()
        grafico_1 = grafico_1.set_index("timestamp")
        st.line_chart(grafico_1)

    with col_graf2:
        st.write("Qualidade da água")
        grafico_2 = df_historico[["timestamp", "qualidade_agua"]].copy()
        grafico_2 = grafico_2.set_index("timestamp")
        st.line_chart(grafico_2)

with aba3:
    st.subheader("Lista de alarmes")

    alarmes = {
        "Nível baixo": dados["alarme_nivel_baixo"],
        "Temperatura alta": dados["alarme_temperatura_alta"],
        "Qualidade da água ruim": dados["alarme_qualidade_ruim"],
    }

    for nome, ativo in alarmes.items():
        if ativo:
            st.error(f"🔴 ALARME ATIVO: {nome}")
        else:
            st.success(f"🟢 Normal: {nome}")

with aba4:
    st.subheader("Histórico de comandos")

    st.dataframe(df_comandos, use_container_width=True)

    st.info(
        "Os comandos são registrados a partir do estado operacional gerado pelo dispositivo C++. "
        "Em uma versão futura, esses comandos poderiam ser enviados diretamente do supervisor para o dispositivo."
    )