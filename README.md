# QR-итерации — нахождение собственных значений

Учебный проект по курсу численных методов. Реализует QR-итерационный алгоритм нахождения собственных значений и собственных векторов вещественных матриц на C++20.

## Описание алгоритма

Реализован полный пайплайн:

1. **Модифицированная ортогонализация Грамма-Шмидта** — численно устойчивый вариант классического алгоритма, снижающий накопление ошибок с плавающей точкой
2. **QR-разложение** — разложение матрицы $A$ на ортогональную $Q$ и верхнетреугольную $R$
3. **QR-итерация** — многократное применение $A \leftarrow RQ$
4. **Критерий сходимости** — итерация останавливается, когда все внедиагональные элементы, поделенные на сумму диагональных $< 10^{-12}$
5. **PCA-пайплайн** — вычисление ковариационной матрицы, проекция данных, анализ долей дисперсии

## Формат входного файла

Программа читает матрицу из текстового файла в рабочей директории. Первая строка — размер матрицы $n$, далее $n \times n$ значений построчно:

```
4
4.0  3.0  0.0  0.0
3.0  4.0  0.0  0.0
0.0  0.0  2.0 -1.0
0.0  0.0 -1.0  2.0
```

Вывод — отсортированные собственные значения и соответствующие им собственные векторы.

## Структура проекта

```
.
│── main.cpp
│── qr.cpp
│── qr.hpp            
│── matrix_op.cpp
│── matrix_op.hpp
│── csv_parcer.cpp 
│── csv_parcer.hpp
└──
```

## Численные детали

- Допуск сходимости: $\varepsilon = 10^{-12}$ (задаётся константой `CONVERGENCE`)
- Максимальное число итераций: 10000
- Собственные значения сортируются по возрастанию модуля

## Запуск программы
Для запуска программы необходимо рядом с выходным файлом (.exe, .out) добавить коварицаонную и центрированную матрицу в формате .csv и указать их отностильный путь в main.cpp
### Пример
```cpp
 auto C = read_csv(data_dir + "/a.csv", 4, 4);
 auto B = read_csv(data_dir + "/b.csv", 30, 4);
```

---

# QR Iteration — Eigenvalue Decomposition

Numerical methods course project. Implements the QR iteration algorithm for finding eigenvalues and eigenvectors of real matrices in C++20.

## Algorithm Overview

The implementation covers the full pipeline:

1. **Modified Gram-Schmidt orthogonalization** — numerically stable variant of classical Gram-Schmidt, reduces floating-point error accumulation
2. **QR decomposition** — factorizes matrix $A$ into orthogonal $Q$ and upper triangular $R$
3. **QR iteration** — repeatedly applies $A \leftarrow RQ$/
4. **Convergence criterion** — iteration stops when all subdiagonal elements devided by sum of diagonal elements $< 10^{-12}$
5. **PCA pipeline** — covariance matrix computation, data projection, explained variance analysis

## Input File Format

The program reads the matrix from a text file in the working directory. First line is matrix size $n$, then $n \times n$ values row by row:

```
4
4.0  3.0  0.0  0.0
3.0  4.0  0.0  0.0
0.0  0.0  2.0 -1.0
0.0  0.0 -1.0  2.0
```

Output — sorted eigenvalues and the corresponding eigenvectors.

## Project Structure

```
.
│── main.cpp
│── qr.cpp
│── qr.hpp            
│── matrix_op.cpp
│── matrix_op.hpp
│── csv_parcer.cpp 
│── csv_parcer.hpp
└──
```

## Numerical Details

- Convergence tolerance: $\varepsilon = 10^{-12}$ (configurable via `CONVERGENCE` constant)
- Maximum iterations: 10000
- Eigenvalues are sorted in descending order by absolute value
