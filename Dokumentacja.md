# Dokumentacja projektu

## 1. Opis działania projektu

Program realizuje założenia projektu poprzez utworzenie i wytrenowanie sieci neuronowej zdolnej do analizy obrazów oraz określania liczby znajdujących się na nich obiektów.

Opracowany model sztucznej inteligencji, po przeprowadzeniu procesu uczenia na odpowiednio przygotowanym zbiorze danych, potrafi rozpoznawać i zliczać linie występujące na obrazie. W aktualnej wersji programu możliwe jest określenie liczby linii w zakresie od 0 do 10.

Wykonana aplikacja spełnia przyjęte na początku projektu wymagania funkcjonalne, obejmujące:

* Wczytuje i przetwarza obrazy o rozdzielczości 640x480, 320x240 oraz 160x120.
* Trenuje sieć neuronową na podstawie wygenerowanych danych.
* Rozpoznaje i zlicza odcinki na obrazie.
* Filtruje wcześniej nałożony szum.
* Wyświetla wyniki z odpowiednią precyzją.
* Jest kompatybilny z systemami Windows 10 oraz Windows 11.
* Obsługuje obrazy do 5 MB.
* Posiada czytelny interface dla urzytkownika , który łatwo prowadzi go przez wszystkie procesy .

Działanie programu opiera się na poszczególnych, podzielonych segmentach, gdzie każdy z nich jest odpowiedzialny za inną funkcję. Cała struktura może zostać przedstawiona w jednym spójnym ciągu prezentującym się w następujący sposób:

[Podanie wymaganych danych] -> [Naprawa pliku poprzez usunięcie szumu] -> [Utworzenie Datasetu] -> [Trening sieci neuronowej] -> [Stworzenie modelu] -> [Testowanie AI]

Następujące opisy są powierzchowne i zostaną bardziej rozwinięte w podpunkcie „Opis działania kluczowych fragmentów”.

Podanie wymaganych danych – użytkownik jest proszony o podanie wymaganych informacji dla programu (ilość danych treningowych, rozdzielczość obrazu). Po wykonaniu tej czynności program zaczyna generować obrazy, które posłużą za dane treningowe dla sieci neuronowej. Wszystkie wygenerowane pliki zostaną zapisane w folderze „Dane dla AI\Dane wejściowe”.

Naprawa pliku poprzez usunięcie szumu – program otwiera po kolei każdy z plików i dokonuje naprawy poprzez redukcję niepożądanego „szumu”, który mógłby zakłócić proces uczenia. Niestety proces nie daje 100% skuteczności i podczas przeglądania plików można natknąć się na pojedynczy piksel, który odstaje od schematu, ale pojedyncze niedopatrzenia nie wpływają widocznie na ogół.

Utworzenie Datasetu - Po zakończeniu procesu generowania oraz naprawiania obrazów program przystępuje do tworzenia datasetu. Dataset stanowi zbiór danych wykorzystywanych podczas nauki sieci neuronowej i składa się z dwóch głównych elementów: obrazów treningowych oraz odpowiadających im etykiet zapisanych w pliku labels.csv. Każdy wygenerowany obraz otrzymuje informację o rzeczywistej liczbie linii znajdujących się na obrazie. Informacja ta zostaje zapisana w pliku CSV, dzięki czemu podczas treningu sieć neuronowa może porównać własną odpowiedź z poprawnym wynikiem. W wyniku działania tego mechanizmu program tworzy kompletny zestaw danych umożliwiający rozpoczęcie procesu nauki modelu.

Trening sieci neuronowej - Po przygotowaniu datasetu następuje etap nauki sieci neuronowej. Program odczytuje obrazy zapisane w folderze „Dane wejściowe”, a następnie przekształca je do postaci numerycznej umożliwiającej ich analizę przez model. W trakcie treningu wykorzystywana jest konwolucyjna sieć neuronowa (CNN), której zadaniem jest wyszukiwanie zależności pomiędzy wyglądem obrazu a liczbą znajdujących się na nim linii. Proces ten odbywa się wielokrotnie, a po każdej iteracji model stopniowo zwiększa swoją skuteczność. W celu poprawy jakości nauki część danych zostaje przeznaczona do walidacji. Pozwala to na bieżąco kontrolować postępy modelu oraz ograniczyć ryzyko błędnego dopasowania do danych treningowych. Końcowym rezultatem tego etapu jest wytrenowana sieć neuronowa posiadająca zdolność rozpoznawania liczby linii na wcześniej niewidzianych obrazach.

Stworzenie modelu - Po zakończeniu procesu treningu program zapisuje wytrenowaną sieć neuronową do pliku model.keras. Plik ten zawiera zarówno strukturę sieci neuronowej, jak i wszystkie parametry wyuczone podczas treningu. Dzięki temu nie ma potrzeby ponownego przeprowadzania procesu nauki przy każdym uruchomieniu programu. Podczas testowania model zostaje wczytany do pamięci komputera i wykorzystany do analizy nowych obrazów dostarczonych przez użytkownika. Na podstawie zdobytej wcześniej wiedzy sieć neuronowa określa najbardziej prawdopodobną liczbę linii znajdujących się na obrazie. Utworzony model stanowi finalny produkt procesu uczenia i jest najważniejszym elementem całego projektu.

Testowanie AI – użytkownik może przetestować utworzoną sieć neuronową poprzez umieszczenie wybranego pliku z obrazem w folderze „Miejsce na plik do testowania”. Obraz ten może zostać utworzony samodzielnie lub poprzez wbudowany w program generator i, jeżeli zostały zachowane wszystkie wymagane warunki (czytelny obraz, wymagana ilość linii oraz wystarczająco dobre przeszkolenie), sieć będzie mogła zidentyfikować oraz rozpoznać liczbę linii.


##  2.Opis działania kluczowych fragmentów

Wstępny opis znaczenia plików i folderów

Zanim zostaną opisane główne mechanizmy użyte w programie, należy omówić jego strukturę oraz znaczenie każdego elementu.

### Folder: Dane dla AI

W nim zostaną przechowane wszystkie utworzone dane, a za ich pomocą program będzie mógł stworzyć oraz wyszkolić działający model AI. Sam folder przechowuje: „Dane wejściowe” i „Dane wyjściowe”, a ich zastosowanie zostanie opisane w następnym podpunkcie.

Uwaga: W przypadku chęci lub potrzeby zachowania modelu istnieje możliwość skopiowania go z programu i użycia w przyszłości. Proces ten jest możliwy pod warunkiem, że folder posiada wymagane pliki oraz został zaimplementowany w odpowiednim miejscu.

### Folder: Dane wejściowe

Tutaj zostaną zachowane wygenerowane przez program obrazy zawierające linie, które posłużą za dane do nauki. Są to początkowe dane, od których zacznie się cały proces i po odpowiedniej obróbce będą mogły zostać użyte do utworzenia datasetów, a później samej sieci neuronowej.

### Folder: Dane wyjściowe

Jest to folder na finalne produkty, czyli dataset (labels.csv) oraz model AI.

### Plik: AI.py

Jest to plik operacyjny, który odpowiada za AI. Posiada on 3 funkcje do wyboru dla użytkownika, a każda odpowiada za kluczowy aspekt procesu.


Generowanie danych

Za nazwą „Generowanie danych” kryje się również proces przygotowania datasetu (pliku labels.csv) oraz sam proces nauki. Po podaniu wymaganych informacji program utworzy paczkę obrazów, oczyści je z niepożądanego szumu oraz zapisze do pliku CSV. Przygotowany w ten sposób dataset umożliwi naukę sieci neuronowych i utworzenie pliku modelu AI, który będzie już gotowy do testów. Cała procedura tworzenia danych, w zależności od ilości wygenerowanych zasobów do nauki, może zająć od kilkudziesięciu sekund do kilku minut. Kluczowe podczas tego procesu jest nieprzerywanie go, w przeciwnym wypadku będzie konieczny reset i tworzenie danych od nowa. Proces jest intuicyjny, wyświetla postęp aktualnej fazy oraz informuje o wczytywaniu się bibliotek.

Testowanie danych

Jest to ostateczna faza programu, gdzie utworzona sieć zostanie sprawdzona pod względem swojej jakości. Po dodaniu do folderu „Miejsce na plik do testowania” wymaganego pliku z obrazem program użyje AI do zweryfikowania liczby linii na obrazie. Jeżeli plik został skopiowany oraz opisany w odpowiedni sposób, zostanie wypisana faktyczna liczba linii oraz liczba określona przez AI. Skuteczność weryfikacji jest uzależniona od ilości danych, na których model miał możliwość się uczyć, a zależność pomiędzy ilością danych a procentową skutecznością jest opisana w podpunkcie „Wyniki testów”.

Reset

Jest to najmniej skomplikowana, ale również ważna funkcja. Jej zadaniem jest resetowanie dotychczasowych danych celem zrobienia miejsca na nowe. Użytkownik może aktywować reset, jeżeli zakończy testy na aktualnym modelu lub w przypadku przerwania procesu nauki rozpocząć tworzenie od początku.

### Folder: Miejsce na plik do testowania

Tutaj zostanie umieszczony obraz, który przedstawi AI. Program uruchomi wyuczoną sieć neuronową, która zweryfikuje i określi liczbę linii na obrazku. Dla porównania zostanie określona również faktyczna liczba linii, aby użytkownik miał możliwość porównania wyników.

Uwaga! Aby nie zaburzyć działania weryfikacji, umieszczony obraz musi być takiej samej rozdzielczości jak ten, na którym uczyło się AI. Nie spowoduje to awarii programu, ale może przyczynić się do zaburzenia wyników testów.


## BIBLIOTEKI

### Biblioteka TensorFlow

TensorFlow jest biblioteką wykorzystywaną do tworzenia oraz trenowania sieci neuronowych. W projekcie została użyta do stworzenia konwolucyjnej sieci neuronowej (CNN), której zadaniem jest rozpoznawanie liczby linii znajdujących się na obrazie.

Przykład implementacji:

```clips
model = tf.keras.Sequential([



tf.keras.layers.Conv2D(16, (3,3), activation='relu', input_shape=(height, width, 1)), 
tf.keras.layers.MaxPooling2D(2,2), 

tf.keras.layers.Conv2D(32, (3,3), activation='relu'), 
tf.keras.layers.MaxPooling2D(2,2), 

tf.keras.layers.Conv2D(64, (3,3), activation='relu'), 
tf.keras.layers.MaxPooling2D(2,2),

tf.keras.layers.Flatten(), 
tf.keras.layers.Dense(64, activation='relu'), 
tf.keras.layers.Dense(10, activation='softmax')

])
```

Powyższy fragment tworzy strukturę sieci neuronowej odpowiedzialnej za analizę obrazów oraz klasyfikację liczby linii.

### Biblioteka NumPy

NumPy jest biblioteką służącą do przechowywania i przetwarzania danych numerycznych. W projekcie została wykorzystana do przechowywania obrazów w postaci macierzy oraz przygotowania ich do procesu uczenia.

Przykład implementacji:


```clips
pixels = np.array(data[4:], dtype=np.float32)
img = pixels.reshape((height, width))
img = img / 255.0 
```

### Biblioteka Pathlib

Pathlib umożliwia wygodne zarządzanie ścieżkami do plików i folderów niezależnie od lokalizacji programu.

Przykład implementacji:

```clips
folder = Path(__file__).resolve().parent / "Dane wejściowe"
folder.mkdir(parents=True, exist_ok=True)
```
W powyższym przykładzie program tworzy folder przeznaczony do przechowywania danych treningowych.

## Mechanizmy 

### Mechanizm treningu sieci neuronowej

Po przygotowaniu danych treningowych następuje proces uczenia sieci neuronowej.

Przykład implementacji:

```clips
model.fit( X, labels, epochs=10, batch_size=16, validation_split=0.2 )
```
Podczas treningu sieć analizuje przygotowane obrazy oraz odpowiadające im etykiety, stopniowo poprawiając skuteczność rozpoznawania liczby linii.

## Fragmenty kodu źródłowego – kluczowe sekcje implementacji z komentarzami wyjaśniającymi logikę biznesową

### Generowanie liczby linii na obrazie

```python
ilosc_linii = random.randint(1, 10)
```

Powyższy fragment odpowiada za losowanie liczby linii, które zostaną umieszczone na generowanym obrazie. Dzięki temu możliwe jest automatyczne tworzenie zróżnicowanych danych treningowych wykorzystywanych podczas nauki sieci neuronowej.

---

### Rysowanie linii na obrazie

```python
if kierunek == 3 and x + j < width:
    draw_line(x + j, y)
```

Kod odpowiada za rysowanie poziomej linii na obrazie. Analogiczne fragmenty programu realizują pozostałe kierunki rysowania. Dzięki temu generowane obrazy zawierają różne układy linii, co zwiększa jakość danych treningowych.

---

### Usuwanie zakłóceń z obrazu

```python
if (
    x > 0 and x + 1 < width and
    mapa[y][x - 1] == 255 and
    mapa[y][x] == 0 and
    mapa[y][x + 1] == 255
):
    mapa[y][x] = 255
```

Mechanizm ten odpowiada za eliminowanie pojedynczych pikseli szumu. Jeżeli czarny piksel znajduje się pomiędzy dwoma białymi pikselami, zostaje uznany za zakłócenie i usunięty.

Pozwala to przygotować bardziej czytelne dane dla sieci neuronowej.

---

### Tworzenie sieci neuronowej

```python
tf.keras.layers.Conv2D(16,(3,3),activation='relu')
```

Jest to pierwsza warstwa konwolucyjnej sieci neuronowej. Jej zadaniem jest wykrywanie charakterystycznych elementów obrazu, takich jak linie, krawędzie oraz skupiska pikseli.

Mechanizm ten stanowi podstawę procesu rozpoznawania obiektów przez AI.

---

### Proces nauki modelu

```python
model.fit(X,labels,epochs=10,batch_size=16,validation_split=0.2)
```

Fragment rozpoczyna proces uczenia sieci neuronowej. Program analizuje obrazy treningowe oraz odpowiadające im etykiety i stopniowo dostosowuje parametry modelu w celu poprawy skuteczności rozpoznawania liczby linii.

---

### Testowanie wytrenowanego modelu

```python
prediction = model.predict(img)

wynik = np.argmax(prediction)
wynik += 1
```

Po zakończeniu nauki model analizuje nowy obraz i określa najbardziej prawdopodobną liczbę linii. Otrzymany wynik jest następnie prezentowany użytkownikowi.

## 3.Instrukcja instalacji oraz korzystania z programu

### Instrukcja środowiska w Visual Studio Code

Do uruchomienia programu wymagany jest interpreter języka Python. W przypadku korzystania z Visual Studio Code konieczne będzie również zainstalowanie odpowiednich rozszerzeń oraz bibliotek. Poniżej przedstawiono listę wymaganych elementów wraz z instrukcją ich instalacji.

- Instalacja rozszerzeń

    Aby Visual Studio Code mogło poprawnie obsługiwać oraz uruchamiać pliki z rozszerzeniem .py, należy zainstalować następujące rozszerzenia:

    Python
    Pylance
    Python Debugger
    Python Environments

    W przypadku zagubienia , można również aktywować zakładkę srkutem (Ctrl + Shift + X).

- Pobranie interpretera dla Pythona

    Interpreter Python można pobrać z oficjalnej strony internetowej projektu. Zalecaną wersją jest Python 3.11.9. Po pobraniu odpowiedniej wersji należy uruchomić instalator i przeprowadzić standardowy proces instalacji.

- Instalacja Bibliotek

    Po poprawnym zainstalowaniu języka Python należy otworzyć konsolę Windows PowerShell i wykonać kolejno poniższe polecenia:

    ```clips
    pip install tensorflow

    pip install numpy
    ```

    Po zakończeniu instalacji bibliotek należy wskazać interpreter używany przez Visual Studio Code. Zalecane jest wykonanie tej czynności w następujący sposób :

    1. Uruchom Visual Studio Code.
    2. Użyj kombinacji klawiszy Ctrl + Shift + P. Powinno to otworzyć okno poleceń u góry ekranu.
    3. Wpisz polecenie: Python: Select Interpreter.
    4. Wybierz interpreter Python 3.11.9.

   Jeżeli wszystkie kroki zostały wykonane poprawnie, środowisko będzie gotowe do pracy z projektem. Program nie wymaga dodatkowej aktywacji ani konfiguracji. Po zainstalowaniu wymaganych komponentów jest gotowy do użycia.

    (tutaj opis instalacji Pythona na komputerze)

### Instrukcja obsługi programu

1. Uruchomienie programu

    Uruchom Aktywator.cpp.

2. Wprowadzenie danych

    Po uruchomienu programu należy wybrać opcje [1] , wypełnić wymagane informacje i zapisać paczkę danych. W przypadku wątpliwości czy paczka została odpowiednio zapisana można skorzysać z opcji [2] przegląd plików .


3. Proces uczenia

  Po uruchomieniu funkcji [3] Uczenie AI wybrany pakiet danych zostanie skopiowany do folderu operacyjnego. Następnie obrazy zostaną oczyszczone z niepożądanego szumu oraz zapisane do zbioru danych dataset.csv. Po przygotowaniu zbioru rozpocznie się proces uczenia sieci neuronowej. Po jego zakończeniu program poprosi o podanie nazwy modelu i zapisze go w folderze „Gotowe_AI”.

4. Testowanie modelu

    Wybrany model można przetestować na wcześniej przygotowanym obrazie w formacie .pgm, umieszczonym w folderze „Plik do testów”. Program wczyta wskazany plik, przeprowadzi analizę obrazu i wyświetli przewidywaną przez AI liczbę linii oraz rzeczywistą wartość odczytaną z nazwy pliku.

    Uwaga! Jeżeli użytkownik chce zresetować program, usunąć wybrane dane lub pozbyć się niepotrzebnych plików, może skorzystać z funkcji [5] Reset, która umożliwia usunięcie wybranych elementów projektu.
5. Zakończenie
    
   Po zakończeniu pracy program można zamknąć za pomocą opcji [6] Wyjście.

### Dodatkowe oprogramowanie użyte podczas tworzenia programu

W trakcie pracy z programem tworzone są pliki w kilku różnych formatach. Aby wygodnie przeglądać ich zawartość, warto zainstalować oprogramowanie obsługujące te typy plików.

Format .pgm
IrfanView (zalecane)
GIMP
Adobe Photoshop

Format .csv

Visual Studio Code (zalecane)
Microsoft Excel
LibreOffice Calc

Format .keras 

Visual Studio Code
PyCharm 
Anaconda / Jupyter Notebook
Google Colaboratory

Programy oznaczone jako „zalecane” były wykorzystywane podczas tworzenia oraz testowania projektu. Programy operujące na foramcie .keras nie są wymagane do funkcjonowania programu gdyż nie będzie potrzeby otwierania plików z tyym formatem .


##  4.Testy jakości utworzonych modeli

Po utworzeniu i wytrenowaniu modeli przeprowadzono testy mające na celu ocenę skuteczności działania sieci neuronowej. Każdy model został poddany serii 100 prób z wykorzystaniem wcześniej wygenerowanych obrazów testowych. Celem eksperymentu było sprawdzenie wpływu liczby obrazów treningowych oraz ich rozdzielczości na jakość rozpoznawania liczby odcinków znajdujących się na obrazie.

Uzyskane wyniki przedstawiono w poniższych tabelach.

Rozdzielczość - 640x480

| Ilość obrazów | błędy| Skuteczność |
| ------------- |---:| ----------: |
| 1000          | 52 |        48 % |
| 2000          | 44 |        56 % |
| 5000          | 31 |        69 % |
| 10000         | 22 |        78 % |
| 15000         | 18 |        82 % |
| 20000         | 15 |        85 % |


Rozdzielczość - 320x240 :

| Ilość obrazów | błędy| Skuteczność |
| ------------- |---:| ----------: |
| 1000          | 58 |        42 % |
| 2000          | 49 |        51 % |
| 5000          | 39 |        61 % |
| 10000         | 31 |        69 % |
| 15000         | 26 |        74 % |
| 20000         | 22 |        78 % |


Rozdzielczość - 160x120 : 

| Ilość obrazów | błędy| Skuteczność |
| ------------- |---:| ----------: |
| 1000          | 63 |        37 % |
| 2000          | 56 |        44 % |
| 5000          | 47 |        53 % |
| 10000         | 39 |        61 % |
| 15000         | 35 |        65 % |
| 20000         | 31 |        69 % |


Wnioski : Eksperyment wykazał iż rozdzielczość i ilość obrzów urzytuch do nauki AI ma znaczenie na skuteczność rozpoznawania liości linii. We wszystkich badanych przypadkach zwiększenie liczby obrazów treningowych prowadziło do poprawy wyników klasyfikacji. Największy wzrost skuteczności zaobserwowano pomiędzy modelami uczonymi na 1000 a 10000 obrazów.
Analiza wyników wskazuje również, że modele trenowane na obrazach o wyższej rozdzielczości osiągały lepsze rezultaty niż modele wykorzystujące obrazy o mniejszych wymiarach. Różnice pomiędzy poszczególnymi rozdzielczościami wynosiły od kilku do kilkunastu punktów procentowych skuteczności.
Najlepsze wyniki uzyskano dla rozdzielczości 640×480 oraz zbioru treningowego liczącego 20000 obrazów, gdzie skuteczność modelu osiągnęła poziom 85%. Pozwala to stwierdzić, że zwiększenie ilości danych treningowych oraz zastosowanie obrazów o większej rozdzielczości pozytywnie wpływa na zdolność sieci neuronowej do poprawnego rozpoznawania liczby odcinków na obrazie.

 Winika z tego fakt iż AI lepiej radzi siobie z plikami o większej rozdzielczości .



##  5.Bibliografia

- Jerzy Grębosz, Opus magnum C++. Programowanie w języku C++. Wydanie III poprawione

- Mark Lutz, Python. Wprowadzenie. Wydanie V, Helion.
- Aurélien Géron, Hands-On Machine Learning with Scikit-Learn, Keras, and TensorFlow, O'Reilly Media, 2022.
- Jason Brownlee, Deep Learning for Computer Vision, Machine Learning Mastery.
- Stuart Russell, Peter Norvig, Wprowadzenie do sztucznej inteligencji.

##  6.Netografia

https://pl.wikipedia.org/wiki/Uczenie_maszynowe

https://www.w3schools.com/python/python_ml_getting_started.asp (sekcja o uczeniu maszynowym)

https://keras.io/api/

https://impicode.pl/blog/jak-stworzyc-siec-neuronowa/

https://docs.python.org/3/

https://realpython.com/python-pathlib/

https://www.python.org/downloads/

https://www.tensorflow.org/

https://www.tensorflow.org/tutorials/images/cnn?hl=pl

https://www.geeksforgeeks.org/python/python-programming-language-tutorial/

https://code.visualstudio.com/docs/python/python-tutorial

https://www.tensorflow.org/api_docs

https://www.reddit.com/ (korzystałem z wielu różnych forów i konwersacji dlatego zostawiam tylko link do platformy)

Użyte AI podczas tworzenia tego programu :

- Chat GPT , wersja Go
- github copilot

## Spis treści :

1. Opis działania projektu
2. Opis działania kluczowych fragmentów
3. Instrukcja instalacji oraz korzystania z programu
4. Testy jakości utworzonych modeli
5. Bibliografia
6. Netografia