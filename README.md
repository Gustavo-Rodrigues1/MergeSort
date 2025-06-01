# MergeSort
Utilização do algorítimo mergesort para organizar containers de um porto fictício, primeiramente terá uma lista de containers cadastrados e uma lista de containers selecionados dentre os cadastrados. Caso haja uma diferença de cnpj ou uma diferença percentual entre os pesos de 10% o containers será exibido no final, primeiramente os que possuem diferença no cnpj, e posteriormente os que possuem a diferença de peso da maior diferença percentual a menor sendo o critério de prioridade caso haja a mesma diferença percentual a ordem de cadastrado.

# 📥 Formato do Arquivo de Entrada
numeroDeContainersCadastrados
códigoDoContainer cnpj peso
códigoDoContainer cnpj peso
códigoDoContainer cnpj peso
...
numeroDeContainersSelecionados
códigoDoContainer cnpj peso
códigoDoContainer cnpj peso
códigoDoContainer cnpj peso
...

# 📤 Formato da Saída
codigoDoContainer:cnpjCadastrado<->cnpjSelecionado
codigoDoContainer:cnpjCadastrado<->cnpjSelecionado
codigoDoContainer:cnpjCadastrado<->cnpjSelecionado
...
codigoDoContainer:pesokg(diferençaPercentual%)
codigoDoContainer:pesokg(diferençaPercentual%)
codigoDoContainer:pesokg(diferençaPercentual%)
...
