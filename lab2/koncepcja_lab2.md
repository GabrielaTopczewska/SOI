# SOI - Lab2 - Szeregowanie procesów - Koncepcja wykonania 

Imię i nazwisko: *Gabriela Topczewska*  
Nr indeksu: *310961*  
Grupa: *środa, 8:15-10:00*  

## Cel laboratorium

Celem laboratorium jest zmodyfikowanie procedury szeregującej w taki sposób, aby procesy przydzielane były do dwóch grup **A**, **B** (gdzie proporcja ilości procesów w grupie A:B = 1:3), a procesy grupy A wykonywały się **X** razy częściej (wartość X powinna być modyfikowalna przez użytkownika), niż procesy grupy B.  
Przykładowo, przy kolejce procesów ***ABABBAB***, gdzie **X=2**, lista kolejno wykonywanych procesów będzie wyglądała następująco: ***(AA)B(AA)BB(AA)B***.

## Planowane rozwiązanie

1. Modyfikowacja jedynie procesów z grupy *USER*.
2. Procesy szeregowane w ramach pojedynczej kolejki.
3. Każdy proces z tej grupy powinien przypisaną mieć grupę priorytetu `pri_group`, określającą, czy proces należy do grupy A, czy B.
4. Grupa przypisywana będzie przy tworzeniu procesu, na podstawie _____________________.
5. Zmiana grupy priorytetowej będzie odbywała się za pomocą nowego wywołania systemowego `void set_pri_group(void)`.
6. Długość wykonywania procesu będzie różniła się w zależności od przypisanej grupy.
7. Długość wykonywania procesu będzie mogła zostać zmieniona za pomocą wywołania systemowego `int set_scheduler(int x)`.
8. `int set_scheduler(int x)` będzie ustalało procent kwantu czasuprzyznanego procesom grupy A.
9. Procesy grupy B otrzymywać będą odpowiednio (100 - `x`)% czasu.
10. Częścią rozwiązania powinien być również program testujący zaimplementowane zmiany systemowe (np. skrypt shellowy z programem w C ub inny).

## Pliki do modyfikacji

### Moduł kernel
- `proc.h` - dodanie pól informujących o grupie priorytetu `pri_group` i innych (jeszcze nieokreślonych), odnoszących się do czasu wykonania procesu,
- `proc.c` - modyfikacja funkcji `sched()`,
- `system.c` - dodanie procedur wykonujących wywołania jądra systemowego.

### Moduł MM
- `main.c` - implementacja wywołań systemowych,
- `proto.h` - dodanie prototypów nowo dodanych wywołań systemowych,
- `table.c` - dodanie pól odpowiadającym nowo dodanym wywołaniom systemowym.

### Moduł FS
- `table.c` - dodanie pól `no_sys` odpowiadających nowo dodanym wywołaniom systemowym.

### Inne
- `callnr.h` - dodanie informacji o nowych wywołaniach modułu MM (interfejs do wywołań jądra),
- `com.h` -  dodanie informacji o nowych wywołaniach jądra systemu.
