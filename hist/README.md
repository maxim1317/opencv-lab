# Histogram

```bash
hist [PATH_TO_IMAGE] 
```

## Что это?

Это учебный проект №1 - построение гистограммы изображения (Ч/Б или цветного)  

## Как запустить?

### Зависимости

- __OpenCV__ >=_3.4.0_
- __CMake__ >=_3.13_

_Linux_:
- __build-essential__ (_Ubuntu/Debian_)

### Установка и запуск

Команды указаны для _Linux_. Если вы запускаете на _Windows_, у вас, скорее всего, есть мышка.

1. __Подготовка__

Создайте и перейдите папку _build_
```bash
mkdir build
cd build
```

2. __Сборка__

Запустите _CMake_
```bash
cmake ../
```

3. __Запуск__ 

_Linux_:
```bash
./hist [PATH_TO_IMAGE] 
```
_Windows_:
```bash
hist.exe [PATH_TO_IMAGE] 
```

## Структура

__src/__
- [hist.cpp](src/hist.cpp) - Основной файл проекта, тут код для гистограммы и main()
- __src/headers/__
    - [hist.h](src/headers/hist.h) - Хедер с прототипами и инклюдами
    - [misc.cpp](src/headers/misc.cpp) - Файл с побочными функциями (экспорт данных для гнуплота и вывод формата изображения)

