#ifndef LISTA_H_
#define LISTA_H_

#include <iostream>
#include <memory>

namespace mof {
template <typename T> class node {
public:
  node(T dado);
  node();
  void setprox(std::shared_ptr<node<T>> prox);
  std::shared_ptr<node<T>> getprox() const;
  T getdado() const;
  T get_prox_dado() const;
  void desalloc();

private:
  T dado_;
  std::shared_ptr<node<T>> prox_;
};

template <typename T> class lista {
public:
  lista();
  void getlista() const;
  void getfirst() const;
  std::size_t busca(T dado) const;
  bool vazia();
  void push_back(T element);
  bool pop_back(T achado);
  void insert(T element, std::size_t position);

private:
  std::shared_ptr<node<T>> inicio;
};
} // namespace mof

#endif
