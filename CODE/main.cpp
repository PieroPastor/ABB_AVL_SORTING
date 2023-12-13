/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: piero
 *
 * Created on 22 de noviembre de 2023, 09:25
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "AVL.h"
#include "AVLSorting.h"

int main(int argc, char** argv) {
    int arr[10]={3, 1, 8, 6, 9, 1, 4, 6, 2, 0};
    AVLsort<int>(arr, 10);
    for(int i=0; i < 10; i++) cout << arr[i] << " ";
    /*0 1 1 2 3 4 6 6 8 9*/
    return 0;
}

