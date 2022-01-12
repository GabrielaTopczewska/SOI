# SOI - Lab 6 - System plików - Koncepcja wykonania

Imię i nazwisko: *Gabriela Topczewska*  
Nr indeksu: *310961*  
Grupa: *środa, 8:15-10:00*  

## Cel laboratorium

Celem laboratorium jest zaimplementowanie programu realizującego proste funkcje systemu plików. System plików należy zorganizować w dużym pliku o zadanej wielkości, który będzie "wirtualnym dyskiem". Program powinien tworzyć dysk wirtualny, oraz dokonywać zapisów i odczytów w celu zrealizowania podstawowych operacji na dysku, związanych z zarządzaniem katalogiem, alokacją plików oraz utrzymywaniem unikalności nazw.Ma być to program z jednopoziomowym katalogiem. Nie trzeba realizować funkcji otwierania pliku ani czytania/pisania fragmentów pliku. Nie trzeba realizować funkcji związanych z współbieżnym dostępem. Zakłada się dostęp sekwencyjny i wyłączny do wirtualnego dysku.

## Planowane rozwiązanie

1. System jako ciągły obszar pamięci, składający się z 3 rodzajów bloków:
    - superblok,
    - inode,
    - datablok,
2. Tylko jeden *superblok*, znajdujący się na samym początku systemu plików.
3. Superblok zawierający podstawowe informacje o systemie: magic number (oznaczenie, że dany blok jest superblokiem), liczba inodów, liczba databloków, początek inodów, początek databloków.
4. *Inody* odpowiadające kolejnym plikom (1 inode => 1 plik).
5. Inody przechowujące nazwę przechowywanego pliku (ograniczoną do 256 znaków), rozmiar pliku oraz offset do niego, ewentualnie na tym etapie nieokreślone jeszcze flagi, które możliwe że okażą się użyteczne podczas implementacji programu.
5. *Databloki* zawierające dane przechowywanych w systemie plików, zrealizowane jako tablica typu char o rozmiarze 2048.
6. Możliwość wykonywania operacji na plikach/systemie określonych w instrukcji dostępnej pod adresem [t6.txt](https://www.ia.pw.edu.pl/~tkruk/edu/soi/lab/t6.txt).
7. Testowanie systemu z użyciem stworzonych plików testowych, na których sprawdzane będą operacje dostępne w zaimplementowanym rozwiązaniu.
8. Ponieważ nie jest to wymaganiem, system zaimplementowany poza systemem Minix.
9. Program w języku C++.
