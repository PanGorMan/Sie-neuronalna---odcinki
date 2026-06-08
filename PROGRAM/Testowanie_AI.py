import sys
print(sys.executable)


import tensorflow as tf
import numpy as np
from pathlib import Path

print ("\n\nTESTOWANIE AI \n\n")

folder_modeli = Path("Gotowe_AI")

modele = []

for plik in folder_modeli.iterdir():
    if plik.suffix == ".keras":
        modele.append(plik)

if len(modele) == 0:
    print("Brak modeli w folderze Gotowe_AI")
    exit()

print("\nDostępne modele:")

for i, model in enumerate(modele):
    print(f"[{i+1}] {model.name}")

wybor = int(input("\nWybierz model: "))

wybrany_model = modele[wybor - 1]

print("Załadowano:", wybrany_model.name)



model = tf.keras.models.load_model(wybrany_model)

folder_testowy = Path("Plik do testów")

pliki_pgm = []

for plik in folder_testowy.iterdir():
    if plik.suffix.lower() == ".pgm":
        pliki_pgm.append(plik)

if len(pliki_pgm) == 0:
    print("ERROR -- Nie znaleziono pliku .pgm")
    exit()

if len(pliki_pgm) > 1:
    print("ERROR -- W folderze znajduje się więcej niż jeden plik .pgm")
    exit()

plik_testowy = pliki_pgm[0]

nazwa = plik_testowy.stem

parts = nazwa.split("-")

faktyczna_liczba_linii = int(parts[1])

print("Testowany plik:", plik_testowy.name)

# Wczytanie obrazu

with open(plik_testowy, "r") as plik:
    dane = plik.read().split()

width = int(dane[1])
height = int(dane[2])

input_data = []

for x in dane[4:]:

    if int(x) == 255:
        input_data.append(1)
    else:
        input_data.append(0)

# Przygotowanie danych

X = np.array([input_data], dtype=np.float32)

X = 1 - X

X = X.reshape(-1, 120, 160, 1)

print(X.shape)

# Predykcja

wynik = model.predict(X)

odpowiedz = np.argmax(wynik)

print("\n======================")
print("WYNIK AI")
print("======================")
print("AI uważa że na obrazie jest:", odpowiedz + 1, "linii")
print("======================")
print("Faktyczna liczba linii:", faktyczna_liczba_linii)