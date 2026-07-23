# Задача 3. TCP-сервер на Boost.Asio

## Цель

Приложение должно принимать задачи на вычисление по TCP, считать результат и возвращать его клиенту. Протокол — JSON через строку с `\n` в конце.

## Формат запроса и ответа

Запрос: `{"a": 5, "op": "+", "b": 3}\n`  
Ответ: `{"result": 8}\n`

## План изменений

### CMakeLists.txt

- Добавить `find_package(Boost REQUIRED)`
- Добавить `Boost::boost` в `target_link_libraries` для `calculator`
- Добавить `src/server.cpp` в `add_executable(calculator ...)`
- Добавить `src/server.cpp` в `add_executable(calculator_tests ...)`
- Добавить новый target `calculator_client` с `src/client.cpp`

### src/server.h

Объявить класс `Server` в namespace `calculator`:
- Конструктор принимает `io_context&`, порт и `atomic<bool>& running`
- Метод `run()` — цикл приёма подключений
- Поле `acceptor_` типа `tcp::acceptor`
- Поле `running_` — ссылка на флаг из `Application`

### src/server.cpp

Реализовать `run()`:
1. Принять подключение через `acceptor_.accept(socket)`
2. Прочитать строку до `\n` через `read_until`
3. Распарсить JSON: заполнить `Task` из полей `a`, `op`, `b`
4. Вызвать `Application::calculate(task)`
5. Сформировать JSON-ответ и отправить через `write`

### src/app.h

- Добавить `#include "server.h"` и `#include <boost/asio.hpp>`
- Добавить приватные поля:
  - `boost::asio::io_context io_`
  - `Server server_`
  - `std::thread serverThread_`
- Добавить публичный статический метод `static void calculate(Task& task)`

### src/app.cpp

- Вынести логику switch из `makeCalculate()` в `calculate(Task& task)`
- `makeCalculate()` теперь вызывает `calculate(task_)`
- В конструкторе инициализировать `server_(io_, 8080, running_)` и запустить `serverThread_`
- В деструкторе добавить `join()` для `serverThread_`
- В методе `run()` добавить проверку `argc < 2` — если аргументов нет, работать в режиме сервиса

### src/client.cpp

Тестовый клиент:
1. Подключиться к `127.0.0.1:8080`
2. Отправить JSON-запрос с `\n`
3. Прочитать ответ и вывести в stdout
