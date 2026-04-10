import random
from datetime import date
from pathlib import Path

folder = Path(__file__).resolve().parent / "Dane treningowe"
folder.mkdir(parents=True, exist_ok=True)

for i in range(1, 10):
    nazwa_pliku = f"{date.today().year}-{date.today().month}-{date.today().day}_plik-{i}.pgm"

    width, height = 160, 120
    prob = 0.05
    ilosc_linii = 10
    kierunek = 1 
    thickness = 3  # Grubość linii

    # Tworzymy obraz w pamięci
    image = []
    for y in range(height):
        row = []
        for x in range(width):
            if random.random() < prob:
                row.append("0")
            else:
                row.append("255")
        image.append(row)

    # Funkcja do rysowania grubych linii
    def draw_line(x, y, thickness):
        half = thickness // 2
        for dy in range(-half, half + 1):
            for dx in range(-half, half + 1):
                ny = y + dy
                nx = x + dx
                if 0 <= ny < height and 0 <= nx < width:
                    image[ny][nx] = "0"

    # Rysowanie linii 
    for _ in range(ilosc_linii):

        kierunek = random.randint(1, 8)
        x = random.randint(0, width-1)
        y = random.randint(0, height-1)
        dlugosc = random.randint(20, 50)
    
        if kierunek == 1: # GÓRA
            for i in range(dlugosc):
                if y - i >= 0:
                    draw_line(x, y - i, thickness)
        if kierunek == 2: # GÓRA-PRAWO
                for i in range(dlugosc):
                    if y - i >= 0 and x + i < width:
                        draw_line(x + i, y - i, thickness)
        if kierunek == 3: # PRAWO
                for i in range(dlugosc):
                    if x + i < width:
                        draw_line(x + i, y, thickness)
        if kierunek == 4: # PRAWO-DÓŁ
                for i in range(dlugosc):
                    if y + i < height and x + i < width:
                        draw_line(x + i, y + i, thickness)
        if kierunek == 5: # DOŁ
                for i in range(dlugosc):
                    if y + i < height:
                        draw_line(x, y + i, thickness)
        if kierunek == 6: # DÓŁ-LEWO
                for i in range(dlugosc):
                    if y + i < height and x - i >= 0:
                        draw_line(x - i, y + i, thickness)
        if kierunek == 7: # LEWO
                for i in range(dlugosc):
                    if x - i >= 0:
                        draw_line(x - i, y, thickness)
        if kierunek == 8: # LEWO-GÓRA
                for i in range(dlugosc):
                    if y - i >= 0 and x - i >= 0:
                        draw_line(x - i, y - i, thickness)


    prob = 0.05
    image = []
    for y in range(height):
        row = []
        for x in range(width):
            if random.random() < prob:
                row.append("1")
            else:
                row.append("255")
        image.append(row)



    # Zapisywanie pliku PGM
    file_path = folder / nazwa_pliku
    with open(file_path, 'w') as f:
        f.write("P2\n")
        f.write(f"{width} {height}\n")
        f.write("255\n")
        for row in image:
            f.write(" ".join(row) + "\n")
    
    print(f"Zapisano: {file_path}")
