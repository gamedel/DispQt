Программа была написана в Visual Studio 2022 при использовании QT 6.6.1 + c++ (6.6.1_msvc2019_64).

При написании программы поставлены и выполнены следующие задачи:

1. Запрос списка сотрудников из источника "https://jsonplaceholder.typicode.com/users" в виде Json и вывод списка в программе
2. Автоматическое кэширование элементов локально (SQLite)
3. Возможность просмотра элемента api на отдельное странице/диалоге
4. Возможность добавить свой комментарий к элементу, который не будет удалятся при обновлении кеша
По технологиям: интерфейс на QML, логика на С++, архитектура MV* (MVC/MVP/MVVI)

![База сотрудников](https://github.com/gamedel/DispQt/assets/77504587/adaeb67b-528c-4a2d-be21-f50f6f409a21)

Инструкция:
При первом запуске программы будет создана таблица для кэша и появится файл "cache.db". Для того чтобы получить и записать туда первые данные нужно нажать на кнопку "Получить список"(1).
Программа отправит Get запрос на адрес "https://jsonplaceholder.typicode.com/users", откуда получит Json список сотрудников.
После получения Json программа сохранит данные в файл "cache.db" (находится в папке с проектом) и отобразит сотрудников в виде списка, как показано на рисунке выше.
Кнопка "Комментировать" (2) открывает окно и позволяет добавить комментарий для данного сотрудника, после нажатия на кнопку Ок, комментарий будет сохранен локально в файл "cache.db" (при получении списка по кнопке (1) комментарий не будет перезаписываться).
Кнопка " ! " (3) открывает окно для редактирования имени сотрудника, также при нажатии на Ок сохраняет изменение локально, но при получении списка сотрудников по кнопке (1) перезаписывается, чтобы показать, что комментарии остаются неизменными.
Кнопка "Подробнее" (4) открывает окно с информацией по сотруднику, здесь можно посмотреть на его почту и оставленный нами комментарий.

