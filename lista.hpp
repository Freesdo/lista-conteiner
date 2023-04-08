#ifndef LISTAS_H_
#define LISTAS_H_

#include <iostream>
#include <memory>
#include <string>

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
  lista() : inicio(nullptr) {}
  void getlista() const {
    std::shared_ptr<node<T>> it(inicio);
    while (it) {
      std::cout << it->getdado() << '\n';
      it = it->getprox();
    }
  }
  void getfirst() const {
    std::cout << inicio->getdado();
  } // estou usando para testes.
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
    std::shared_ptr<node<T>> novo{std::make_shared<node<T>>(element)};
    if (vazia()) {
      inicio = std::move(novo);
    }
    std::shared_ptr<node<T>> it(inicio);
    while (it->getprox()) {
      it = it->getprox();
    }
    it->setprox(novo);
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
    return true;
  }
  void insert(size_t position); // a implementar ainda

private:
  std::shared_ptr<node<T>> inicio;
};
} // namespace mof
#endif
