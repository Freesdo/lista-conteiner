## Primeira versão da lista que estou fazendo a partir de ponteiros inteligentes

para incluir a lista, basta incluir o lista.hpp e lista.cpp no seu diretório, crie um arquivo objeto de lista.cpp e inclua #include "lista.hpp" no cabeçalho do seu código

## Exemplo:

```g++ -o lista lista.cpp```

```c++
#include "lista.hpp"
```

## criar uma lista: 

para criar a lista, basta fazer:

```c++
mop::lista<T> MinhaLista;
```
os métodos disponíveis até então são de:

```c++
MinhaLista.push_back(T dado); <-> retorna void e adiciona um elemento no final da lista
MinhaLista.pop_back(T dado); <-> retorna um bool referente a se excluiu o elemento procurado (pop_back deveria ser o nome para excluir o último, no proximo commit eu arrumo)
MinhaLista.vazia(); <-> retorna um bool referente a se está vazia ou não 
MinhaLista.busca(T achado); <-> retorna um std::size_t da posição do valor procurado
MinhaLista.getlista(); <-> retorna void mas imprime toda a lista
```

# ainda está em fase de testes e implementações, estou fazendo isso como um passatempo e realmente sei que ninguém vai usar porque já existe <vector> ou outros tipos de contâiners mais práticos e fáceis
