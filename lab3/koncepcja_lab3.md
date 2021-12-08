# SOI 3 - Semafory

## Treść zadania

Są 3 bufory typu FIFO o długości N (najprawdopodobniej zaimplementowane z użyciem zewnętrznej biblioteki), do których liczby całkowite piszą dwaj producenci. Jeden z producentów używa buforów nr 1 i 2 i produkuje liczby nieparzyste, drugi używa buforów 2 i 3 i produkuje liczby parzyste. Producenci piszą do swoich buforów losowo (brak określonej kolejności, np. określone naprzemienne pisanie do bufora 1 i 2). Z każdego z buforów czyta oddzielny konsument (łącznie jest ich 3).
Z użyciem semaforów zabezpieczyć program przed:  
- czytaniem z bufora pustego,  
- pisaniem do bufora pełnego,  
- jednoczesnym pisaniem i czytaniem z tego samego bufora.  
  
Program zostanie najprawdopodobniej napisany w języku C++ w środowisku Linux Ubuntu.
