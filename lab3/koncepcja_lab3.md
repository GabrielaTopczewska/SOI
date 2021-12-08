# SOI 3 - Semafory

## Treść zadania

Są 3 bufory typu FIFO o długości N (najprawdopodobniej zaimplementowane z użyciem zewnętrznej biblioteki), do których liczby całkowite piszą dwaj producenci. Jeden z producentów używa buforów nr 1 i 2 i produkuje liczby nieparzyste, drugi używa buforów 2 i 3 i produkuje liczby parzyste. Producenci piszą do swoich buforów losowo (brak określonej kolejności, np. określone naprzemienne pisanie do bufora 1 i 2). Z każdego z buforów czyta oddzielny konsument (łącznie jest ich 3).  
  
Z użyciem semaforów zabezpieczyć program przed:  
- czytaniem z bufora pustego,  
- pisaniem do bufora pełnego,  
- jednoczesnym pisaniem i czytaniem z tego samego bufora.  
  
## Planowane rozwiązanie

1. Uruchomienie 5 procesów w systemie (2 producenci, 3 konsumenci).
2. Producenci odpowiedzialni za wytworzenie danych typu `int` (odpowiednio nieparzystych lub parzystych) oraz umieszanie ich w odpowiednich buforach.
3. Konsumenci odpowiedzialni za wyjmowanie danych z kolejki i wyświetlanie (printowanie) informacji o nadawcy danej oraz (niepewna, ale możliwa opcja) o czasie jej odbioru.
4. Nadawca danej rozpoznawalny po podzielności danej przez 2 (parzystość).
5. Brak aktywnego oczekiwania.

Program zostanie najprawdopodobniej napisany w języku C w środowisku Linux Ubuntu z użyciem bibliotek `semaphore.h` i `pthreads.h`.
