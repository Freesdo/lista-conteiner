#include "lista.hpp"
#include <iostream>
#include <memory>

template <typename T>
mof::node<T>::node(T dado) : dado_(dado), prox_(nullptr) {}
template <typename T> mof::node<T>::node() { prox_ = nullptr; }
template <typename T>
void mof::node<T>::setprox(std::shared_ptr<node<T>> prox) {
  prox_ = prox;
}
template <typename T> T mof::node<T>::getdado() const { return dado_; }
template <typename T> T mof::node<T>::get_prox_dado() const {
  return prox_->getdado();
}
template <typename T> void mof::node<T>::desalloc() { prox_.reset(); }

template <typename T> mof::lista<T>::lista() : inicio(nullptr) {}
template <typename T> void mof::lista<T>::getlista() const {
  std::shared_ptr<node<T>> it(inicio);
  while (it) {
    std::cout << it->getdado() << '\n';
    it = it->getprox();
  }
}
template <typename T> void mof::lista<T>::getfirst() const {
  std::cout << inicio->getdado();
} // ese método estou utilizando para testes, no final do projeto, irei excluir
template <typename T> std::size_t mof::lista<T>::busca(T dado) const {
  std::shared_ptr<node<T>> it = inicio;
  std::size_t count{};
  while (it->getdado() != dado) {
    count++;
    it = it->getprox();
  }
  return count;
}
template <typename T> bool mof::lista<T>::vazia() {
  return inicio ? false : true;
}
template <typename T> void mof::lista<T>::push_back(T element) {
  std::shared_ptr<node<T>> novo{std::make_shared<node<T>>(element)};
  if (vazia()) {
    inicio = std::move(novo);
    return;
  }
  std::shared_ptr<node<T>> it(inicio);
  while (it->getprox()) {
    it = it->getprox();
  }
  it->setprox(novo);
}

template <typename T> bool mof::lista<T>::pop_back(T achado) {
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
template <typename T>
void mof::lista<T>::insert(T element, std::size_t position) {}
