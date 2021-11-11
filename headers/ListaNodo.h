#ifndef NODO_H
#define NODO_H

template <class T>
class ListaNodo{
private:
  T dato;
  ListaNodo<T> *siguiente;

public:

  T getDato(){
    return dato;
  }

  void setDato(T d){
    dato = d;
  }

  ListaNodo<T> *getSiguiente(){
    return siguiente;
  }

  void setSiguiente(ListaNodo<T> *siguiente){
    this->siguiente = siguiente;
  }

};

#endif //NODO_H