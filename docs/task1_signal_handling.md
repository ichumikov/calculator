# Задача 1. Обработка системных сигналов

## Цель

Приложение должно корректно завершать работу при получении сигнала SIGTERM.

## План изменений

### src/app.h

- Добавить `#include <atomic>` и `#include <thread>`
- Добавить приватные поля:
  - `std::atomic<bool> running_{true}` — флаг работы приложения
  - `std::thread signalThread_` — поток для ожидания сигнала
- Добавить приватный метод `void runSignalHandler()`

### src/app.cpp

- Добавить `#include <csignal>` и `#include <pthread.h>`
- В конструкторе `Application()`:
  - Заблокировать SIGTERM в главном потоке через `pthread_sigmask(SIG_BLOCK, ...)`
  - Запустить `signalThread_` — поток, который будет ждать сигнал
- В деструкторе `~Application()`:
  - Дождаться завершения `signalThread_` через `join()`
- Реализовать `runSignalHandler()`:
  - Ждать SIGTERM через `sigwait()`
  - При получении установить `running_ = false`

## Почему именно так

- `pthread_sigmask` блокирует сигнал во всех потоках, кроме `signalThread_`
- `sigwait` приостанавливает поток до прихода сигнала — без polling
- `std::atomic<bool>` гарантирует видимость изменения флага между потоками
