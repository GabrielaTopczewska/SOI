# SOI - Lab2 - Szeregowanie procesów - Koncepcja wykonania 

Imię i nazwisko: *Gabriela Topczewska*  
Nr indeksu: *310961*  
Grupa: *środa, 8:15-10:00*  

## Cel laboratorium

Celem laboratorium jest zmodyfikowanie procedury szeregującej w taki sposób, aby procesy przydzielane były do dwóch grup **A**, **B** (gdzie proporcja ilości procesów w grupie A:B = 1:3), a procesy grupy B wykonywały się **X** razy dłużej (wartość X powinna być modyfikowalna przez użytkownika), niż procesy grupy A, zanim zostaną przesunięte na koniec kolejki.  
Przykładowo, przy kolejce procesów ***ABABBAB***, gdzie **X=2**, lista kolejno wykonywanych procesów będzie wyglądała następująco: ***A(BBB)A(BBB)(BBB)A(BBB)*** - gdy proces A przydzielony ma 1 kwant czasu, proces B przydzielone ma 2 kwanty czasu.

## Planowane rozwiązanie

1. Modyfikacja jedynie procesów z grupy *USER*.
2. Procesy szeregowane w ramach pojedynczej kolejki.
3. Każdy proces powinien mieć przypisaną grupę priorytetu `pri_group`, określającą, czy należy on do grupy A, czy B.
4. Grupa przypisywana przy tworzeniu procesu, na podstawie zadanej proporcji ilości procesów A:procesów B oraz liczby wszystkich procesów w kolejce.
5. Zmiana grupy priorytetowej za pomocą nowego wywołania systemowego `void set_pri_group(void)`.
6. Długość wykonywania procesu różniąca się w zależności od przypisanej grupy.
7. Długość wykonywania procesu możliwa do zmiany za pomocą wywołania systemowego `int set_scheduler(int x)`.
8. `int set_scheduler(int x)` ustalająca procent kwantu czasu przyznanego procesom grupy A.
9. Procesy grupy B otrzymujące odpowiednio (100 - `x`)% czasu.
10. Częścią rozwiązania powinien być również program testujący zaimplementowane zmiany systemowe (np. skrypt shellowy z programem w C ub inny).

## Pliki do modyfikacji

### Moduł kernel
- `proc.h` - dodanie pól informujących o grupie priorytetu `pri_group` i innych (jeszcze nieokreślonych), odnoszących się do czasu wykonania procesu,
- `proc.c` - modyfikacja funkcji `sched()`,
- `system.c` - modyfikacja funkcji `fork()`, by ustawiała ona odpowiednie grupy priorytetowe, dodanie procedur wykonujących wywołania jądra systemowego.

### Moduł MM
- `main.c` - implementacja wywołań systemowych,
- `proto.h` - dodanie prototypów nowo dodanych wywołań systemowych,
- `table.c` - dodanie pól odpowiadającym nowo dodanym wywołaniom systemowym.

### Moduł FS
- `table.c` - dodanie pól `no_sys` odpowiadających nowo dodanym wywołaniom systemowym.

### Inne
- `callnr.h` - dodanie informacji o nowych wywołaniach modułu MM (interfejs do wywołań jądra),
- `com.h` -  dodanie informacji o nowych wywołaniach jądra systemu.

## Program testujący

Zadaniem programu testującego jest sprawdzenie poprawności działania zaimplementowanego rozwiązania. W tym celu przyjmować on będzie od użytkownika parametr będący procentem długości wykonania procesów z grupy A, który będzie ustawiany w systemie za pomocą zaimplementowanych wywołań systemowych. Następnie dokonywany będzie pomiar czasu, w jakim wykonują się procesy z obu grup priorytetowych. Zwracany wynik liczbowy - do użytkownika należy ocena, czy wyniki mieszczą się w dopuszczalnych ramach błędu.
