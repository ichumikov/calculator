# Консольный калькулятор

Калькулятор поддерживает следующие операции: сложение, вычитание, умножение, деление, возведение в степень, расчёт факториала.

Результаты вычислений сохраняются в PostgreSQL и кэшируются в памяти для быстрого повторного доступа.

## Зависимости

- PostgreSQL (libpq-dev)
- CMake >= 3.14

## Сборка

```bash
cmake -B build
cmake --build build
```

## Запуск

```bash
./build/calculator '{"a": 5, "op": "+", "b": 3}'
./build/calculator '{"a": 10, "op": "-", "b": 4}'
./build/calculator '{"a": 2, "op": "^", "b": 8}'
./build/calculator '{"a": 7, "op": "*", "b": 6}'
./build/calculator '{"a": 10, "op": "/", "b": 2}'
./build/calculator '{"a": 5, "op": "!", "b": 0}'
```

## Тесты

```bash
ctest --test-dir build
```
