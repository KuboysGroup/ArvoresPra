import pandas as pd
import matplotlib.pyplot as plt

# Carregar os dados do CSV
df = pd.read_csv("resultado.csv")

# Agrupar e calcular a média do custo de operação por estrutura, operação e quantidade de parâmetros
agrupado = df.groupby(['Nome Arvore', 'Nome Operacao', 'Quantidade Parametros'])['Custo Operacao'].mean().reset_index()

# Filtrar os dados por operação
insercao = agrupado[agrupado['Nome Operacao'] == 'Insercao']
remocao = agrupado[agrupado['Nome Operacao'] == 'Remocao']

# Função para gerar o gráfico
def plotar_grafico(dados, operacao, titulo, arquivo_saida):
    plt.figure(figsize=(10, 6))
    for arvore in dados['Nome Arvore'].unique():
        dados_arvore = dados[dados['Nome Arvore'] == arvore]
        plt.plot(dados_arvore['Quantidade Parametros'], dados_arvore['Custo Operacao'], label=arvore)
    
    plt.title(titulo)
    plt.xlabel('Quantidade de Parâmetros')
    plt.ylabel('Média do Custo de Operação')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(arquivo_saida)
    plt.show()

# Gerar os gráficos
plotar_grafico(insercao, 'Insercao', 'Custo de Operação - Inserção', 'grafico_insercao.png')
plotar_grafico(remocao, 'Remocao', 'Custo de Operação - Remoção', 'grafico_remocao.png')
