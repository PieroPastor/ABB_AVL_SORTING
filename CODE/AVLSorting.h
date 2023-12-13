/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   AVLSorting.h
 * Author: piero
 *
 * Created on 13 de diciembre de 2023, 10:54
 */

#ifndef AVLSORTING_H
#define AVLSORTING_H

#include "AVL.h"

template <typename T>
void AVLsort(T *arr, int n){
    AVL<T> avl;
    //Recorrido con insercion log(n) = n*log(n)
    for(int i=0; i < n; i++) avl.insertar(arr[i]);
    //Recorrido de todo el ABB = n
    avl.guardarEnOrden(arr, n);
    /* O(n) = 
     * Mejor caso:       n * log(n)
     * Caso promedio:    n * log(n)
     * Peor caso:        n * log(n)
    */
}

#endif /* AVLSORTING_H */

