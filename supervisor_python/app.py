import json
import os
import sqlite3
from datetime import datetime
from pathlib import Path

import pandas as pd
import streamlit as st

BASE_DIR = Path(__file__).resolve().parent.parent

CAMINHO_JSON = BASE_DIR / "dispositivo_cpp" / "dados_estacao.json"
CAMINHO_CSV = BASE_DIR / "supervisor_python" / "database" / "historico.csv"
CAMINHO_DB = BASE_DIR / "supervisor_python" / "database" / "historico.db"

st.set_page_config(page_title="Mini-SCADA EB-161", layout="wide")

st.title("Mini-SCADA - Estação de Bombeamento EB-161")

if not os.path.exists(CAMINHO_JSON):
    st.error("Arquivo JSON ainda não foi gerado pelo dispositivo C++.")
    st.stop()

with open(CAMINHO_JSON, "r", encoding="utf-8") as arquivo:
    dados = json.load(arquivo)

dados["timestamp"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

# Garante que a pasta database exista
CAMINHO_CSV.parent.mkdir(parents=True, exist_ok=True)

# Salvar histórico em CSV
df_novo = pd.DataFrame([dados])

if CAMINHO_CSV.exists():
    df_antigo = pd.read_csv(CAMINHO_CSV)
    df_historico = pd.concat([df_antigo, df_novo], ignore_index=True)
else:
    df_historico = df_novo

df_historico.to_csv(CAMINHO_CSV, index=False)

# Salvar histórico em SQLite
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

# Interface Streamlit
st.subheader("Leituras atuais")

col1, col2, col3 = st.columns(3)

col1.metric("Nível da água", f"{dados['nivel']} %")
col2.metric("Temperatura", f"{dados['temperatura']} °C")
col3.metric("Qualidade da água", f"{dados['qualidade_agua']} IQA")

st.subheader("Estado da bomba")

st.write("Bomba principal:", dados["bomba_principal"])

st.subheader("Alarmes")

alarmes = {
    "Nível baixo": dados["alarme_nivel_baixo"],
    "Temperatura alta": dados["alarme_temperatura_alta"],
    "Qualidade ruim": dados["alarme_qualidade_ruim"],
}

for nome, ativo in alarmes.items():
    if ativo:
        st.error(f"ALARME ATIVO: {nome}")
    else:
        st.success(f"Normal: {nome}")

st.subheader("Tabela de dados atual")

df = pd.DataFrame([dados])
st.dataframe(df)

st.subheader("Histórico em CSV")
st.dataframe(df_historico)

st.subheader("Histórico em SQLite")
st.dataframe(df_sqlite)