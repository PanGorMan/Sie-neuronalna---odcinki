import argparse
import random
from datetime import date
from pathlib import Path

# folder docelowy
folder_glowny = Path(__file__).resolve().parent / "Dane treningowe"
folder_glowny.mkdir(parents=True, exist_ok=True)

#======================================
# wartości domyślne lub przekazane z C++
ilosc_kopii = 10
width, height = 160, 120
progress = 0
#======================================

parser = argparse.ArgumentParser(description="Generator danych obrazów AI")
parser.add_argument("ilosc_kopii", nargs="?", type=int, default=ilosc_kopii, help="Ilość kopii do wygenerowania")
parser.add_argument("width", nargs="?", type=int, default=width, help="Szerokość obrazu")
parser.add_argument("height", nargs="?", type=int, default=height, help="Wysokość obrazu")
parser.add_argument("folder_name", nargs="?", type=str, default=None, help="Nazwa folderu")
args = parser.parse_args()

ilosc_kopii = args.ilosc_kopii
width = args.width
height = args.height
folder_name = args.folder_name if args.folder_name else f"{date.today().year}-{date.today().month}-{date.today().day}"
folder = folder_glowny / folder_name
folder.mkdir(parents=True, exist_ok=True)


#======================

prob = 0.02
thickness = 3

for plik_nr in range(1, ilosc_kopii + 1):

    ilosc_linii = random.randint(1, 10)
    nazwa_pliku = f"{plik_nr}-{ilosc_linii}-{date.today().year}-{date.today().month}-{date.today().day}_plik-{plik_nr}.pgm"

    # --- obraz w pamięci ---
    image = []
    for y in range(height):
        row = []
        for x in range(width):
            if random.random() < prob:
                row.append("0")
            else:
                row.append("255")
        image.append(row)

    # --- rysowanie grubych pikseli ---
    def draw_line(x, y):
        half = thickness // 2
        for dy in range(-half, half + 1):
            for dx in range(-half, half + 1):
                ny = y + dy
                nx = x + dx
                if 0 <= ny < height and 0 <= nx < width:
                    image[ny][nx] = "0"

    # --- rysowanie linii ---
    for _ in range(ilosc_linii):
        kierunek = random.randint(1, 8)
        x = random.randint(0, width - 1)
        y = random.randint(0, height - 1)
        dlugosc = random.randint(20, 50)

        for j in range(dlugosc):

            if kierunek == 1 and y - j >= 0:  # góra
                draw_line(x, y - j)

            elif kierunek == 2 and y - j >= 0 and x + j < width:  # góra-prawo
                draw_line(x + j, y - j)

            elif kierunek == 3 and x + j < width:  # prawo
                draw_line(x + j, y)

            elif kierunek == 4 and y + j < height and x + j < width:  # dół-prawo
                draw_line(x + j, y + j)

            elif kierunek == 5 and y + j < height:  # dół
                draw_line(x, y + j)

            elif kierunek == 6 and y + j < height and x - j >= 0:  # dół-lewo
                draw_line(x - j, y + j)

            elif kierunek == 7 and x - j >= 0:  # lewo
                draw_line(x - j, y)

            elif kierunek == 8 and y - j >= 0 and x - j >= 0:  # góra-lewo
                draw_line(x - j, y - j)

    # --- obraz w pamięci ---
    for y in range(height):
        for x in range(width):
            if image[y][x] != "0":  # nie ruszaj linii
                if random.random() < prob:
                    image[y][x] = "255"

                    
    # --- zapis ---
    file_path = folder / nazwa_pliku
    with open(file_path, "w") as f:
        f.write("P2\n")
        f.write(f"{width} {height}\n")
        f.write("255\n")
        for row in image:
            f.write(" ".join(row) + "\n")

    progress += 1

    if progress % 10 == 0:
        print(f"\rWygenerowano: {progress}/{ilosc_kopii} obrazów", end="", flush=True)