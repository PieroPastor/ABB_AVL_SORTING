/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AVL.h
 * Author: piero
 *
 * Created on 22 de noviembre de 2023, 09:26
 */

#ifndef AVL_H
#define AVL_H

template <typename T>
class AVL {
public:
    AVL();
    AVL(const AVL&);
    virtual ~AVL();
    void insertar(const T &);
    void mostrarEnOrden();
    void mostrarPreOrden();
    void mostrarPostOrden();
    void guardarEnOrden(T *, int);
    void guardarPreOrden(T *, int);
    void guardarPostOrden(T *, int);
private:
    class Nodo{
        public:
            Nodo(const T &);
            virtual ~Nodo();
        private:
            Nodo *hizq;
            int altura;
            Nodo *hder;
            class Datos{
                public:
                    Datos(const T &);
                    virtual ~Datos();
                private:
                    T valor;
                    Datos *sig;
                friend class Nodo;
                friend class AVL;
            };
            Datos *valor;
            void balancearHaciaIzquierda(class Nodo *&);
            void balancearHaciaDerecha(class Nodo *&);
            void balancearIzquierdaDeDerecha(class Nodo *&);
            void balancearDerechaDeIzquierda(class Nodo *&);
            int compararAlturas(const class Nodo *, const class Nodo *);
            int max(const class Nodo *, const class Nodo *);
            void apilar(const T &);
        friend class AVL;
    };
    Nodo *raiz;
    bool insertarRecursivo(Nodo *&, const T &);
    void mostrarEnOrdenRecursivo(const Nodo *);
    void mostrarPreOrdenRecursivo(const Nodo *);
    void mostrarPostOrdenRecursivo(const Nodo *);
    void guardarEnOrdenRecursivo(Nodo *, T *, int&, int);
    void guardarPreOrdenRecursivo(Nodo *, T *, int&, int);
    void guardarPostOrdenRecursivo(Nodo *, T *, int&, int);
};

/******************************************************************************/
template <typename T>
AVL<T>::AVL() {
    raiz = nullptr;
}

template <typename T>
AVL<T>::AVL(const AVL& orig) {
    this->raiz = new Nodo;
    this->raiz->hder = orig.raiz->hder;
    this->raiz->hizq = orig.raiz->hizq;
    this->raiz->valor = orig.raiz->valor;
}

template <typename T>
AVL<T>::~AVL() {
    delete raiz;
}
/******************************************************************************/
template <typename T>
AVL<T>::Nodo::Datos::Datos(const T &valor){
    this->valor = valor;
    sig = nullptr;
}

template <typename T>
AVL<T>::Nodo::Datos::~Datos(){
    if(sig != nullptr) delete sig;
}

template <typename T>
void AVL<T>::Nodo::apilar(const T &val){
    Datos *nuevo = new Datos(val);
    nuevo->sig = valor;
    valor = nuevo;
}
/******************************************************************************/
template <typename T>
AVL<T>::Nodo::Nodo(const T &valor){
    hizq = nullptr;
    hder = nullptr;
    altura = 1;
    this->valor = new Datos(valor);
}

template <typename T>
AVL<T>::Nodo::~Nodo(){
    if(valor != nullptr) delete valor;
}
/******************************************************************************/
template <typename T>
void AVL<T>::Nodo::balancearHaciaIzquierda(class Nodo *& parbol){
    /*Pasa el nodo actual a ser hijo izquierdo de su hijo derecho, y el nuevo 
      hijo derecho, del nodo actual, es el izquierdo de su hijo derecho, por
     último el hijo derecho del nodo actual toma el lugar del nodo actual*/
    Nodo *aux=parbol->hder;
    parbol->hder = aux->hizq;
    aux->hizq = parbol;
    parbol->altura = parbol->max(parbol->hizq, parbol->hder)+1;
    aux->altura = parbol->max(aux->hder, parbol)+1;
    parbol = aux;
}

template <typename T>
void AVL<T>::Nodo::balancearHaciaDerecha(class Nodo *& parbol){
    /*Pasa el nodo actual a ser hijo derecho de su hijo izquierdo, y el nuevo 
      hijo izquierdo, del nodo actual, es el derecho de su hijo izquierdo, por
     último el hijo izquierdo del nodo actual toma el lugar del nodo actual*/
    Nodo *aux=parbol->hizq;
    parbol->hizq = aux->hder;
    aux->hder = parbol;
    parbol->altura = parbol->max(parbol->hizq, parbol->hder)+1;
    aux->altura = parbol->max(aux->hizq, parbol)+1;
    parbol = aux;
}

template <typename T>
void AVL<T>::Nodo::balancearIzquierdaDeDerecha(class Nodo *& parbol){
    /*Balancea hacia la derecha a su hijo derecho con el hijo izquierdo de su
    hijo derecho*/
    parbol->balancearHaciaDerecha(parbol->hder);
    //Balance hacia la derecha con su nuevo hijo derecho
    parbol->balancearHaciaIzquierda(parbol);
}
            
template <typename T>
void AVL<T>::Nodo::balancearDerechaDeIzquierda(class Nodo *& parbol){
    /*Balancea hacia la izquierda a su hijo izquierdo con el hijo derecho de su
    hijo izquierdo*/
    parbol->balancearHaciaIzquierda(parbol->hizq);
    //Balance hacia la derecha con su nuevo hijo izquierdo
    parbol->balancearHaciaDerecha(parbol);
}

template <typename T>
int AVL<T>::Nodo::compararAlturas(const class Nodo *hijo1, const class Nodo *hijo2){
    //No hay altura de ningun hijo
    if(hijo1 == nullptr and hijo2 == nullptr) return 0;
    //Retorna únicamente al hijo1
    else if(hijo1 != nullptr and hijo2 == nullptr) return hijo1->altura; 
    //Retorna únicamente al hijo2 pero en negativo para indicar la dirección
    else if(hijo1 == nullptr and hijo2 != nullptr) return -1 * (hijo2->altura);
    //Retorna la resta entre la altura de los dos hijos
    else return (hijo1->altura) - (hijo2->altura);
}

template <typename T>
int AVL<T>::Nodo::max(const class Nodo *hijo1, const class Nodo *hijo2){
    //No hay altura, de ningun hijo
    if(hijo1 == nullptr and hijo2 == nullptr) return 0; 
    //El hijo1 tiene más altura
    else if(hijo1 != nullptr and hijo2 == nullptr) return hijo1->altura; 
    //El hijo2 tiene más altura
    else if(hijo1 == nullptr and hijo2 != nullptr) return hijo2->altura;
    //Retorna la mayor altura
    else return (hijo1->altura > hijo2->altura)? hijo1->altura:hijo2->altura;
}
/******************************************************************************/
template <typename T>
bool AVL<T>::insertarRecursivo(AVL::Nodo *&raiz, const T &valor){
    bool flag;
    if(raiz == nullptr){
        //Si es dato nuevo crea un nuevo nodo y retorna que sí creció el ABB
        raiz = new Nodo(valor);
        return true;
    }
    if(raiz->valor->valor == valor){
        //Si es repetido, se apila en el nodo y retorna que no creció el ABB
        raiz->apilar(valor); 
        return false;
    }
    if(raiz->valor->valor < valor) flag = insertarRecursivo(raiz->hder, valor);
    else if(raiz->valor->valor > valor) flag = insertarRecursivo(raiz->hizq, valor);
    
    if(flag) raiz->altura = raiz->max(raiz->hizq, raiz->hder) + 1; //Actualiza la altura
    //Si creció el árbol y el hijo derecho es mayor por más de un nivel al hijo izquierdo entra
    if(flag and raiz->compararAlturas(raiz->hizq, raiz->hder) < -1){
        if(valor > raiz->hder->valor->valor) raiz->balancearHaciaIzquierda(raiz); //Es más grande de largo hacia la derecha
        else raiz->balancearIzquierdaDeDerecha(raiz); //Es más grande, pero luego de uno a la derecha, se va a la izquierda
    }
    //Si creció el árbol y el hijo izquierdo es mayor por más de un nivel al hijo derecho entra
    else if(flag and raiz->compararAlturas(raiz->hizq, raiz->hder) > 1){
        if(valor < raiz->hizq->valor->valor) raiz->balancearHaciaDerecha(raiz); //Es más grande de largo hacia la izquierda
        else raiz->balancearDerechaDeIzquierda(raiz); //Es más grande, pero luego de uno a la izquierda, se va a la derecha
    }
    return flag; //Retorna la bandera que indica el crecimiento del árbol
}

template <typename T>
void AVL<T>::insertar(const T &valor){
    insertarRecursivo(raiz, valor);
}

template <typename T>
void AVL<T>::mostrarEnOrdenRecursivo(const Nodo* raiz){
    if(raiz == nullptr) return;
    mostrarEnOrdenRecursivo(raiz->hizq);
    class AVL<T>::Nodo::Datos *p;
    p = raiz->valor;
    while(p){
        cout << p->valor << " ";
        p = p->sig;
    }
    mostrarEnOrdenRecursivo(raiz->hder);
}

template <typename T>
void AVL<T>::mostrarEnOrden(){
    mostrarEnOrdenRecursivo(raiz);
}

template <typename T>
void AVL<T>::mostrarPreOrdenRecursivo(const Nodo* raiz){
    if(raiz == nullptr) return;
    class AVL<T>::Nodo::Datos *p;
    p = raiz->valor;
    while(p){
        cout << p->valor << " ";
        p = p->sig;
    }
    mostrarPreOrdenRecursivo(raiz->hizq);
    mostrarPreOrdenRecursivo(raiz->hder);
}

template <typename T>
void AVL<T>::mostrarPreOrden(){
    mostrarPreOrdenRecursivo(raiz);
}

template <typename T>
void AVL<T>::mostrarPostOrdenRecursivo(const Nodo *raiz){
    if(raiz == nullptr) return;
    mostrarPostOrdenRecursivo(raiz->hizq);
    mostrarPostOrdenRecursivo(raiz->hder);
    class AVL<T>::Nodo::Datos *p;
    p = raiz->valor;
    while(p){
        cout << p->valor << " ";
        p = p->sig;
    }
}

template <typename T>
void AVL<T>::mostrarPostOrden(){
    mostrarPostOrdenRecursivo(raiz);
}

template <typename T>
void AVL<T>::guardarEnOrdenRecursivo(Nodo* raiz, T* arr, int &i, int n){
    if(raiz == nullptr or i >= n) return;
    guardarEnOrdenRecursivo(raiz->hizq, arr, i, n);
    class AVL<T>::Nodo::Datos *p;
    p = raiz->valor;
    while(p){
        if(i == n) return;
        arr[i++] = p->valor;
        p = p->sig;
    }
    guardarEnOrdenRecursivo(raiz->hder, arr, i, n);
}

template <typename T>
void AVL<T>::guardarEnOrden(T *arr, int n){
    int i=0;
    guardarEnOrdenRecursivo(raiz, arr, i, n);
}

template <typename T>
void AVL<T>::guardarPreOrdenRecursivo(Nodo *raiz, T *arr, int &i, int n){
    if(raiz == nullptr or i >= n) return;
    class AVL<T>::Nodo::Datos *p;
    p = raiz->valor;
    while(p){
        if(i == n) return;
        arr[i++] = p->valor;
        p = p->sig;
    }
    guardarPreOrdenRecursivo(raiz->hizq, arr, i, n);
    guardarPreOrdenRecursivo(raiz->hder, arr, i, n);
}

template <typename T>
void AVL<T>::guardarPreOrden(T *arr, int n){
    int i=0;
    guardarPreOrdenRecursivo(raiz, arr, i, n);
}

template <typename T>
void AVL<T>::guardarPostOrdenRecursivo(Nodo *raiz, T *arr, int &i, int n){
    if(raiz == nullptr or i >= n) return;
    guardarPostOrdenRecursivo(raiz->hizq, arr, i, n);
    guardarPostOrdenRecursivo(raiz->hder, arr, i, n);
    class AVL<T>::Nodo::Datos *p;
    p = raiz->valor;
    while(p){
        if(i == n) return;
        arr[i++] = p->valor;
        p = p->sig;
    }
}

template <typename T>
void AVL<T>::guardarPostOrden(T *arr, int n){
    int i=0;
    guardarPostOrdenRecursivo(raiz, arr, i, n);
}

#endif /* AVL_H */

