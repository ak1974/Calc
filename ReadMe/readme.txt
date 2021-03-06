
--- РЕШЕНИЕ ---

Пояснения к тестовому заданию СТЦ.

ТЗ (калькулятор) выполнено в среде Qt Creator  4.5.2 с библиотекой 5.9.5 в ОС Ubuntu MATE.
За образец взят калькулятор данной ОС. Интерфейс реализован на QML с использованием QtQuick 2.

Описание файлов и классов:

main.qml – интерфейс программы

SafeQueue – класс потоконезависимой очереди для QueueRequests и QueueResults. Независимость реализована через QMutex + QMutexLocker. Здесь минимально необходимый набор функций: добавление, удаление и размер.

quItem – структура  - логическая единица запроса на вычисление, набор которых, хранится в очередях.

CalcDispatcher – основной классик. Здесь осуществляется приём сигналов от интерфейса, создание очередей, 
запуск потоков, отправка сигналов от потоков в интерфейс для отображения результата и лога. 

Computer – классик, который работает внутри потока.  Здесь собраны функции добавления и извлечения элементов для обработки, формирования запросов  и отображения результатов. По сути, здесь собраны функции работы с очередями, поэтому классик один, но работает в двух режимах в зависимости от потока для которого создан.
Т.е. для потока 1 (по ТЗ) устанавливается режим работы REQUEST и вызывается соответствующий набор функций. А для потока 2 (из ТЗ) соответственно свой режим - RESULT.

libcalcLib.so – библиотека с  1 функцией doIt, которая непосредственно осуществляет вычисление и выдаёт ошибки деления на 0 или неизвестной операции.

Работа происходит следующим образом:

При старте программы, в диспетчере создаются два объекта-работника с указанием режима работы и передачей ссылок на очереди QueueRequests и QueueResults, затем отправляются каждый в свой поток.
Сигналы с текстом  элемента  главной формы, проключенные через main.cpp,  приходят в calcDispatcher. Здесь заполняется структура элемента вычисления quItem, а также формируется и отправляется назад «изображение» вводимого примера. Кнопка «=» отправляет сигнал с элементом в поток 2 для формирования очереди запросов. Здесь проверяется корректность заполнения полей с выдачей сигнала ошибки  (если она есть) или элемент добавляется в очередь.  Извлечение элементов из очереди результатов и отправка сигнала на отображение происходит в цикле.
Поток 2, так же в цикле, извлекает элементы на обработку, вычисляет результат или ошибку, пишет в элемент и перекладывает в очередь результатов. Далее происходит ожидание (секунд) в зависимости от значения установленного пользователем и т.д.

Не реализовано, как не влияющее на основной функционал программы: подсветка лога, сохранение размеров окна. Нет «.» для ввода дробных чисел (думаю – не принципиально для испытания).

Реализована обработка логических ошибок (операция, вместо числа или неполное выражение),  управление задержкой потока 1 со стороны интерфейса, отображение размера очередей (каждый раз, при изменении емитится сигнал). Однако, по условию ТЗ для потока 2 нет задержки, поэтому очередь результатов почти всегда =0 (её моментально обрабатывает поток 2, после того как поток 1 добавил туда решение)
Ведётся отображение лога ошибок и введённых выражений. Имеется защита от «тырканья» - операция перезаписывается, а числа увеличиваются.  Имеется раздражающая особенность: если вычисление происходит с задержкой, то результат приходит с опозданием и если пользователь начал вводить новое выражение, то приходится затирать введенное только что условие для показа результата. На данный момент это работает вот так, впрочем, возможны разные варианты решения проблемы. 

