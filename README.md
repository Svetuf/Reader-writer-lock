# Reader-writer-lock

Writer изменяет значение переменной. Первый writer ее увеличивает, второй - уменьшает.
Reader считывает значение переменной.

В консоль выводится информация работы потоков. Для потоков writer отмечается начало и конец работы, чтобы увидеть что в течение 100 милисекунд (на столько поток 
замораживается в lock'e) никто другой доступ к переменной не имеет. Также у каждого лога выводится значение clock() чтобы следить в какие время кто обращался.
