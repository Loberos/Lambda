#include "pch.h"
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdlib.h>

using namespace System;
using namespace std;


// Declaracion de expresiones Lambda
void declararion() {
    //1    auto = caulquier variable
    auto f1 = [](int x, int y) {return x + y; };
    cout << f1(2, 3) << endl;
    //2    function <devuelve un entero> (recibe dos enteros)
    function<int(int, int)> f2 = [](int x, int y) {return x + y; };
    cout << f2(3, 4) << endl;
    //3     funcion que se ejecuta al ser creado
    auto cuadrado = [](int x) {return x * x;  }(5);
    cout << cuadrado << endl;
}

// Llamar a una funcion expresion lambda
void invocar() {
    int sum = [](int x, int y) { return x + y; }(5, 4);
    auto mul = [](int x, int y) {return x * y; };
    cout << "Sum(5,4)=> " << sum << endl;
    cout << "Mul(5,3)" << mul(5, 3) << endl;
}

//Expresiones Anidadas lambda 
void exprAnid() {
    int duplicarDosVeces = [](int x) { return ([](int y) {return y * 2; }(x) * 2);
    }(5);
    cout << "Duplicar dos veces 5  =>" << duplicarDosVeces << endl;
}

//Fuciones lambda de orden superior 
void ordenSuperior() {
    // -> tipo de dato que va a devolver la funcion lambda
    auto addtwointegers = [](int x)->function<int(int)> {
        //[=] acceso a la variable de entorno
        return [=](int y) {return x + y; };
    };
    // const - permite que no se pueda mmodificar las variables
    auto higherorder = [](const function<int(int)>& f, int z) {
        return f(z) * 2; };

    auto answer = higherorder(addtwointegers(7), 8);
    cout << answer << endl;
}

//Expresiones Lambda en un funcion 
void exprLamFun() {
    class Scale {
    private:
        int _scale;
        int n;
    public:
        explicit Scale(int scale) :_scale(scale) {}
        void ApplyScale(const vector<int>& vector)const {
            for_each(vector.begin(), vector.end(), [=](int x) { cout << n * _scale << endl; });
        };
    };
    vector<int>values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);
    Scale s(3);
    s.ApplyScale(values);
}

//Expresiones Lambda usando Template
template <class T>
void negate_all(vector<T>& vector) {
    for_each(vector.begin(), vector.end(), [](T& n) {n = -n; });
};
template <class T>
void print_all(vector<T>& vector) {
    for_each(vector.begin(), vector.end(), [](const T& n) {cout << n << endl; });
};
void mostrar() {
    vector<int >vector;
    vector.push_back(34);
    vector.push_back(-43);
    vector.push_back(56);
    print_all(vector);
    negate_all(vector);
    cout << "Despues Negate_all(): " << endl;
    print_all(vector);
}

//EXAMPLE 1
void ejem1() {
    int m = 0;
    int n = 0;
    [&m, n](int a)mutable {m = ++n + a; }(4);
    cout << "m=> " << m << endl;
    cout << "n=> " << n << endl;
}

//EXAMPLE 2
template <class T>
void imprimirArreglo(T a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++)
    {
        cout << (i ? ", " : "") << a[i];
    }
    cout << " ]\n";
}
void OrdenarArreglo() {
    vector<int>vector{ 44,11,77,55,88,66,33,22 };
    sort(vector.begin(), vector.end(),
        [&](const int left, const int right) {return left > right; });
    imprimirArreglo(vector, vector.size());
}

//EXAMPLE 3
void MultiploNumero() {
    vector<int>vector{ 1,2,3,4,5,6,7,8,9,10,11,12,20 };
    int multi = 5;
    size_t count = count_if(vector.begin(), vector.end(),
        [=](int num) {return !(num % multi); });
    cout << "Los multiplos de " << multi << "=> " << count << endl;
}

//EXAMPLE 4 
void contarParesEImpares() {
    vector<int >vector{ 1,2,3,4,5 };
    size_t count = count_if(vector.begin(), vector.end(),
        [](int numero)->bool {return numero % 2; });
    cout << "Numero pares: " << count << endl;

    count = count_if(vector.begin(), vector.end(),
        [](int numero)->bool {return !(numero % 2); });
    cout << "Numero impares: " << count << endl;
}

//EXAMPLE 5 
void factorial() {
    int arr[] = { 1,2,3,4,5 };
    auto factorial = [](int i, int j) {return i * j; };
    auto res = accumulate(arr, arr + 5, 1, factorial);
    cout << "5! = " << res << endl;
}

//EXAMPLE 6 
template <class T>
void imprimirArrgelo2(T* a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++)
    {
        cout << (i ? ", " : "") << a[i];
    }
    cout << " ]\n";
}
template <class T>
void intercambio(T* a, int n, bool (*mayorQue)(T, T)) {
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (mayorQue(a[i], a[j])) {
                T temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
}
template <class T>
void burbuja(T* a, int n, function<bool(T, T)>mayorQue) {
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (mayorQue(a[i], a[j + 1])) {
                T temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
}

//EXAMPLE 7
void mostrarExam56() {
    auto mayQ = [](float a, float b) {return a > b; };
    float a1[10], a2[10], a3[10], a4[10], a5[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        a1[i] = rand() % 100;
        a5[i] = a4[i] = a3[i] = a2[i] = a1[i];

    }
    cout << "Paso a paso intercambio\n";
    intercambio<float>(a1, 10, mayQ);
    cout << "Paso a paso burbuja\n";
    burbuja<float>(a2, 10, mayQ);
}
