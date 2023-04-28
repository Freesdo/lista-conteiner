#ifndef LISTA_H_
#define LISTA_H_

#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>

// adaptar esse tipo de estrutura para qualquer tipo utilizando um template,
// como um vector
namespace mof {
template <typename T> class node {
public:
  node(T dado) : dado_(dado), prox_(nullptr) {}
  node() { prox_ = nullptr; }
  void setprox(std::shared_ptr<node<T>> prox) { prox_ = prox; }
  std::shared_ptr<node<T>> getprox() const { return prox_; }
  T getdado() const { return dado_; }
  T get_prox_dado() const { return prox_->getdado(); }
  void desalloc() { prox_.reset(); }

private:
  T dado_;

  std::shared_ptr<node<T>> prox_;
};

template <typename T> class lista {
public:
  lista() : inicio(nullptr), tamanho(0) {}
  std::size_t size() const { return tamanho; }
  void getlista() const {
    std::shared_ptr<node<T>> it(inicio);
    while (it) {
      std::cout << it->getdado() << '\n';
      it = it->getprox();
    }
  }
  size_t busca(T dado) const {
    std::shared_ptr<node<T>> it = inicio;
    size_t count{};
    while (it->getdado() != dado) {
      count++;
      it = it->getprox();
    }
    return count;
  }
  bool vazia() const { return inicio ? false : true; }
  void push_back(T element) {
    if (typeid(element).name() != typeid(T).name()) {
      throw std::bad_cast();
      return;
    }
    std::shared_ptr<node<T>> novo;
    try {
      novo = std::make_shared<node<T>>(element);
    } catch (const std::bad_alloc &exept) {
      std::cerr << "erro ao alocar memoria para um novo elemento.\n what():\t"
                << "--" << exept.what() << "--\n"
                << "sugestao: exclua alguns elementos ou libere memoria para "
                   "prosseguir novamente\n";
      return;
    }
    if (vazia()) {
      inicio = std::move(novo);
    }
    std::shared_ptr<node<T>> it(inicio);
    while (it->getprox()) {
      it = it->getprox();
    }
    it->setprox(novo);
    tamanho++;
  }
  bool erase(T achado) {
    if (vazia()) {
      throw std::runtime_error("Lista vazia");
      return false;
    }
    if (inicio->getdado() == achado) {
      inicio.reset();
      return true;
    }
    std::shared_ptr<node<T>> it = inicio;
    while (it->getdado() != achado) {
      it = it->getprox();
    }
    std::shared_ptr<node<T>> anterior = inicio;
    while (anterior->getprox() != it) {
      anterior = anterior->getprox();
    }
    anterior->setprox(it->getprox());
    tamanho--;
    return true;
  }
  void insert(T element, std::size_t position) {
    if (typeid(T).name() != typeid(element).name()) {
      throw std::bad_cast();
      return;
    }
    if (vazia() || position > tamanho) {
      std::cerr << "nao foi possivel inserir o elemento na lista.\n--possiveis "
                   "causas: lista vazia ou posicao invalida--\n";
      throw std::out_of_range("posicao invalida");
      return;
    }
    std::shared_ptr<node<T>> novo;
    try {
      novo = std::make_shared<node<T>>(element);
    } catch (const std::bad_alloc exept) {
      std::cerr
          << "erro de alocacao de memoria para novo elemento. \n"
          << "what():\t--" << exept.what() << "--\n"
          << "tente excluir elementos ou liberar a memoria para prosseguir\n";
      return;
    }
    if (!position) {
      novo.setprox(inicio);
      inicio = std::move(novo);
      tamanho++;
      return;
    }
    std::shared_ptr<node<T>> it(inicio);
    for (std::size_t i{0}; i < position - 1; ++i) {
      it = it.getprox();
    }
    novo.setprox(it->getprox());
    it.setprox(novo);
    tamanho++;
    return;
  }

private:
  std::shared_ptr<node<T>> inicio;
  std::size_t tamanho;
};
} // namespace mof
#endif
