#pragma once
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
    template <typename T> class lista {

    private:
        template <typename U> class node {
        public:
            node(U dado) : dado_(dado), prox_(nullptr) {}
            node() { prox_ = nullptr; }
            void setprox(std::shared_ptr<node<U>> prox) { prox_ = prox; }
            std::shared_ptr<node<U>> getprox() const { return prox_; }
            U getdado() const { return dado_; }
            U get_prox_dado() const { return prox_->getdado(); }
            void desalloc() { prox_.reset(); }

        private:
            U dado_;
            std::shared_ptr<node<U>> prox_;
        };
        template<typename Param, typename... Params>
        void construirLista(Param first) {
            push_back(first);
        }
        template<typename Param, typename... Params>
        void construirLista(Param first,Params... rest) {
            push_back(first);
            construirLista(rest...);
        }
        std::shared_ptr<node<T>> inicio;
        std::size_t tamanho;

    public:
        lista() : inicio(nullptr), tamanho(0) {}
        template<typename... Params>
        lista(Params... args) {
            construirLista(args...);
        }
        std::size_t size() const { return tamanho; }

        void getlista() const {
            std::shared_ptr<node<T>> it(inicio);
            while (it) {
                std::cout << it->getdado() << '\n';
                it = it->getprox();
            }
        }

        T at(std::size_t position) {
            if (position >= tamanho) {
                throw std::out_of_range("invalid position");
            }
            else {
                std::shared_ptr<node<T>> iterator{inicio};
                while (position) {
                    iterator = iterator->getprox();
                    position--;
                }
                return iterator->getdado();
            }
        }
        std::shared_ptr<node<T>> ptr_at(std::size_t position) {
            if (position >= tamanho)
                return nullptr;
            std::shared_ptr<node<T>> iterator{inicio};
            while (position) {
                iterator = iterator->getprox();
                position--;
            }
            return iterator;
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
            }
            catch (const std::bad_alloc& exept) {
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
            if (vazia() || typeid(achado).name() != typeid(T).name()) {
                return false;
            }
            if (inicio->getdado() == achado) {
                std::shared_ptr<node<T>> troca{inicio->getprox()};
                inicio.reset();
                inicio = troca;
                return true;
            }
            std::shared_ptr<node<T>> it{inicio};
            while (it) {
                if (it->getdado() == achado)
                    break;
                it = it->getprox();
            }
            std::shared_ptr<node<T>> anterior{inicio};
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
            }
            catch (const std::bad_alloc exept) {
                std::cerr
                    << "erro de alocacao de memoria para novo elemento. \n"
                    << "what():\t--" << exept.what() << "--\n"
                    << "tente excluir elementos ou liberar a memoria para prosseguir\n";
                return;
            }
            if (!position) {
                novo->setprox(inicio);
                inicio = std::move(novo);
                tamanho++;
                return;
            }
            std::shared_ptr<node<T>> it(inicio);
            for (std::size_t i{0}; i < position - 1; ++i) {
                it = it->getprox();
            }
            novo->setprox(it->getprox());
            it->setprox(novo);
            tamanho++;
            return;
        }
    };
} // namespace mof
#endif

