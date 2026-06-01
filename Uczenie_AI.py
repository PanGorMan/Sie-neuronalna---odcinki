import sys

print(sys.executable)


import tensorflow as tf
import numpy as np
from pathlib import Path

sciezka = Path("Folder operacyjny/Dataset/dataset.csv")

if not sciezka.exists():
    print("Nie znaleziono pliku")
    exit()

print("Plik znaleziony")

dataset_X = []
dataset_Y = []

with open(sciezka, "r") as plik:

    for linia in plik:

        dane = linia.strip().split(",")

        label = int(dane[0])

        piksele = []

        for x in dane[1:]:
            piksele.append(int(x))

        dataset_X.append(piksele)
        dataset_Y.append(label)

print("Pierwszy obraz:")
print(dataset_X[0][:20])

print("Pierwsza odpowiedź:")
print(dataset_Y[0])

X = np.array(dataset_X, dtype=np.float32)
print(X.shape)
Y = np.array(dataset_Y)

unique, counts = np.unique(Y, return_counts=True)

for u, c in zip(unique, counts):
    print("Klasa", u, ":", c)

print("Liczba próbek:", len(X))
print("Liczba pikseli:", len(X[0]))

model = tf.keras.Sequential([
    tf.keras.layers.Dense(64, activation='relu'),
    tf.keras.layers.Dense(32, activation='relu'),
    tf.keras.layers.Dense(11, activation='softmax')
])

model.compile(
    optimizer='adam',
    loss='sparse_categorical_crossentropy',
    metrics=['accuracy']
)

model.fit(X, Y, epochs=10 , validation_split=0.2)

model.save("Gotowe_AI/model.keras")

print("NAUKA ZAKONCZONA")
