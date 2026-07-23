# Задача 4. Сборка deb-пакета

## Цель

Собрать `.deb` пакет, который устанавливает бинарник и systemd unit-файл в нужные директории системы.

## Что должен содержать пакет

| Файл | Путь установки |
|------|----------------|
| `calculator` (бинарник) | `/usr/bin/calculator` |
| `calculator.service` | `/lib/systemd/system/calculator.service` |

## План изменений

### CMakeLists.txt

Добавить в конец файла:

```cmake
# Отключить установку GTest в пакет
set(INSTALL_GTEST OFF)

# Правила установки
install(TARGETS calculator DESTINATION bin)
install(FILES src/systemd/calculator.service
        DESTINATION lib/systemd/system)

# Настройки CPack
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "calculator")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Igor Chumikov")

include(CPack)
```

## Сборка пакета

```bash
cmake -B build -S .
cmake --build build
cd build && cpack
```

Результат: файл `calculator-1.0.0-Linux.deb`

## Проверка содержимого

```bash
dpkg-deb -c calculator-1.0.0-Linux.deb
```
