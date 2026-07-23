# Задача 2. Конфигурация systemd

## Цель

Приложение должно запускаться, останавливаться и перезапускаться через команды systemd.

## План изменений

### src/systemd/calculator.service

Создать unit-файл для systemd со следующим содержимым:

```ini
[Unit]
Description=Calculator Service

[Service]
ExecStart=/usr/bin/calculator
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

### Описание секций

- `[Unit]` — описание сервиса
- `[Service]` — команда запуска и политика перезапуска
  - `ExecStart` — путь к бинарнику после установки deb-пакета
  - `Restart=on-failure` — автоматический перезапуск при аварийном завершении
- `[Install]` — при каком target активируется сервис
  - `multi-user.target` — стандартный многопользовательский режим Linux

## Команды управления сервисом

```bash
sudo systemctl start calculator    # запустить
sudo systemctl stop calculator     # остановить
sudo systemctl restart calculator  # перезапустить
sudo systemctl status calculator   # проверить статус
sudo systemctl enable calculator   # включить автозапуск
```
