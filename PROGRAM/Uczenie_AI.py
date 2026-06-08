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

        label = int(dane[0]) - 1

        piksele = []

        for x in dane[1:]:
            piksele.append(int(x))

        dataset_X.append(piksele)
        dataset_Y.append(label)


X = np.array(dataset_X, dtype=np.float32)
Y = np.array(dataset_Y)

# tło=1, linia=0 -> zamieniamy na bardziej naturalne
X = 1 - X

# zamiana listy 19200 pikseli na obraz 120x160
X = X.reshape(-1, 120, 160, 1)

unique, counts = np.unique(Y, return_counts=True)

model = tf.keras.Sequential([

    tf.keras.layers.Conv2D(16,(3,3),activation='relu',input_shape=(120,160,1)),

    tf.keras.layers.MaxPooling2D((2,2)),

    tf.keras.layers.Conv2D(32,(3,3),activation='relu'),

    tf.keras.layers.MaxPooling2D((2,2)),

    tf.keras.layers.Flatten(),

    tf.keras.layers.Dense(64,activation='relu'),

    tf.keras.layers.Dense(10, activation='softmax')
])

model.compile(
    optimizer='adam',
    loss='sparse_categorical_crossentropy',
    metrics=['accuracy']
)

model.fit(X,Y,epochs=20,batch_size=32,validation_split=0.2,verbose=1)

loss, accuracy = model.evaluate(X, Y, verbose=0)

print("Dokladnosc treningowa:", accuracy)

nazwa_modelu = input("Podaj nazwę modelu: ")

if not nazwa_modelu.endswith(".keras"):
    nazwa_modelu += ".keras"

model.save(f"Gotowe_AI/{nazwa_modelu}")

print(f"Model zapisano jako: {nazwa_modelu}")

print("NAUKA ZAKONCZONA")
