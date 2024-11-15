import pandas as pd
import matplotlib.pyplot as plt

dfAdc = pd.read_csv('./AdicaoDataSet.csv')
fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(dfAdc['Size'], dfAdc['arvoreBO1'], label='Binaria ordem 1')
ax.plot(dfAdc['Size'], dfAdc['arvoreBO5'], label='Binaria ordem 5')
ax.plot(dfAdc['Size'], dfAdc['arvoreBO10'], label='Binaria ordem 10')
ax.plot(dfAdc['Size'], dfAdc['arvoreAvl'], label='AVL')
ax.plot(dfAdc['Size'], dfAdc['arvoreRb'], label='Rubro Negra')

ax.set_title('Complexidade Algorítmica da operação com arvores')
ax.set_xlabel('Tamanho do Conjunto de Dados')
ax.set_ylabel('Esforço computacional (Comparações e Trocas)')
ax.legend()
plt.yscale('log')

#para visualizar no terminal vs code com extension python pack comente a linha plt.savefig('./sortChart.png') e descomente a 
#plt.show()
plt.savefig('./adicaoChart.png')