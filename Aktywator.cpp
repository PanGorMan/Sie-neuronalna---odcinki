#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>



using namespace std;
namespace fs = std::filesystem;


int main() {
    while (true) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int wybór ;

    int wariant_koloru = 0;
    int ilosc_kopii = 10;
    int width = 160;
    int height = 120;
    string folder_name;

    cout << "--- WIELKA MASZYNA AI ---\n\n[1] generowanie obrazów AI\n[2] przegląd plików\n[3] Uczenie AI\n[4] Testowanie AI\n[5] Wyjście\n";

    cin >> wybór;
    if (wybór == 1) {

        cout << "Generowanie obrazów\n";
        cout << "Wariant koloru (0 - czarno/białe 1 - kolorowe):\n ";
        cin >> wariant_koloru;
        cout << "Ilość kopii (min 1000 , max 10000): \n";
        cin >> ilosc_kopii;
        cout << "Szerokość obrazu : 1 - 640x480, 2 - 320x240 ,3 - 160x120\n";
        cin >> width;
        cout << "jak nazwać folder z zestawem danych ? (np. 'DANE1')\n";
        cin >> folder_name;
        if(width == 1) {
            width = 640; height = 480;
        } else if (width == 2) {
            width = 320; height = 240;
        } else if (width == 3) {
            width = 160; height = 120;
        } else {
            cout << "Nieprawidłowy wybór rozdzielczości. Ustawiono domyślną rozdzielczość 160x120.\n";
            width = 160; height = 120;
        }
        cout << "czy wygenerować obraz teraz ? (1 - tak, 0 - nie)\n";
        wybór = 0 ;
        cin >> wybór;
        if (wybór == 1) {
            string command = "py \"Generator_danych.py\" " + to_string(wariant_koloru) + " " + to_string(ilosc_kopii) + " " + to_string(width) + " " + to_string(height) + " \"" + folder_name + "\"";
            system(command.c_str());
            
            string path = "Dane treningowe/" + folder_name + "/DANE " + folder_name + ".txt";
            ofstream plik(path);

            plik << "Nazwa Pakietu: " << folder_name << "\n";
            plik << "data utworzenia : " << width << "\n";
            plik << "ilosc kopii: " << ilosc_kopii << "\n";
            plik << "width: " << width << "\n";
            plik << "height: " << height << "\n";
            plik << "wariant_koloru: " << wariant_koloru << "\n";

            cout << "\n Tworzenie danych zakończone sukcesem.\n";
        } else {
            cout << "Generowanie obrazów zostało anulowane.\n";
        }

    }
     else if (wybór == 2) {
        cout << "Foldery w katalogu 'Dane treningowe':\n\n";
        string sciezka = "Dane treningowe";
        for (const auto& entry : fs::directory_iterator(sciezka)) {
            if (entry.is_directory()) {
                cout << "Folder: " << entry.path().filename() << "\n";
                
                for (const auto& file : fs::directory_iterator(entry.path())) {
                    if (file.is_regular_file()) {
                        string filename = file.path().filename().string();
                        
                        if (filename.substr(0, 4) == "DANE" && filename.find(".txt") != string::npos) {
                            cout << "  Plik: " << filename << "\n";
                            cout << "  Zawartość:\n";
                            
                            ifstream plik(file.path());
                            if (plik.is_open()) {
                                string linia;
                                while (getline(plik, linia)) {
                                    cout << "    " << linia << "\n";
                                }
                                plik.close();
                            } else {
                                cout << "ERROR!!!: Nie można otworzyć pliku\n";
                            }
                        }
                    }
                }
                cout << "\n";
            }
        }
    }

else if (wybór == 3) {

    string sciezka = "Folder operacyjny";

    if (fs::is_empty(sciezka)) {
        cout << "Folder jest pusty \n";
    } else {
        cout << "UWAGA - Folder NIE jest pusty , proszę wybrać opcje:\n 1 - usuń zawartość foldera (jeżeli chcesz wgrać inny pakiet) \n 2 - pozostaw zawartość foldera (AI będzie się uczyć na istniejących danych)\n";
        cin >> wybór;

        if(wybór == 1){

            cout << "Kasowanie zawartości foldera...\n";

            if (fs::exists(sciezka)) {
                for (const auto& entry : fs::directory_iterator(sciezka)) {
                    fs::remove_all(entry.path());
                }
                cout << " Gotowe\n";
            }

        } else if (wybór == 2){

            cout << "PLIKI ZOSTAŁY ZACHOWANE \n";
        }
    }

    sciezka = "Dane treningowe";

    cout << "Wybierz pakiet danych:\n";

    for (const auto& entry : fs::directory_iterator(sciezka)) {
        if (entry.is_directory()) {
            cout << "Folder: " << entry.path().filename() << "\n";

            cout << "\n";
        }
    }

    cout << "podaj pakiet na którym chcesz trenować AI (Jeżeli nie masz żadnego musisz wygenerować):\n";

    folder_name = "";
    cin >> folder_name;

    cout << "Kopiowanie danych do Folderu operacyjnego...";

    // kopiowanie do Folderu operacyjnego
    string source_path = "Dane treningowe/" + folder_name;
    string dest_path = "Folder operacyjny";

    filesystem::create_directories(dest_path);

    for (const auto& entry : filesystem::directory_iterator(source_path)) {

        if (entry.is_regular_file()) {

            string filename = entry.path().filename().string();

            if (filename.size() >= 4 &&
                filename.substr(filename.size() - 4) == ".pgm") {

                filesystem::path dest_file =
                    filesystem::path(dest_path) / filename;

                try {
                    filesystem::copy(
                        entry.path(),
                        dest_file,
                        filesystem::copy_options::overwrite_existing
                    );

                } catch (const filesystem::filesystem_error& e) {

                    cout << "Błąd podczas kopiowania "
                         << filename
                         << ": "
                         << e.what()
                         << "\n";
                }
            }
        }
    }

    cout << "  Gotowe\n";

    cout << "Naprawianie pliku...\n";

    //---------------------

    fs::path folder = "Folder operacyjny";

    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        cout << "Nie znaleziono folderu\n";
        return 0;
    }

    for (const auto& entry : fs::directory_iterator(folder)) {

        if (!entry.is_regular_file())
            continue;

        ifstream plik(entry.path());

        if (!plik.is_open()) {
            cout << "Nie można otworzyć pliku\n";
            continue;
        }

        vector<string> dane;
        string temp;

        while (plik >> temp) {
            dane.push_back(temp);
        }

        plik.close();

        width = stoi(dane[1]);
        height = stoi(dane[2]);

        vector<vector<int>> mapa;
        int index = 4;

        for (int y = 0; y < height; y++) {

            vector<int> linia;

            for (int x = 0; x < width; x++) {

                linia.push_back(stoi(dane[index]));
                index++;
            }

            mapa.push_back(linia);
        }

        // operacje na mapie
        // usuwanie szumów

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width; x++) {

                if (x > 0 && x + 1 < width &&
                    mapa[y][x-1] == 255 &&
                    mapa[y][x] == 0 &&
                    mapa[y][x+1] == 255) {

                    mapa[y][x] = 255;
                }

                if (y > 0 && y + 1 < height &&
                    mapa[y-1][x] == 255 &&
                    mapa[y][x] == 0 &&
                    mapa[y+1][x] == 255) {

                    mapa[y][x] = 255;
                }
            }
        }

        // łączenie linii -- do poprawki

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width; x++) {

                if (x > 0 && x + 1 < width &&
                    mapa[y][x-1] == 0 &&
                    mapa[y][x] == 255 &&
                    mapa[y][x+1] == 0) {

                    mapa[y][x] = 0;
                }

                if (y > 0 && y + 1 < height &&
                    mapa[y-1][x] == 0 &&
                    mapa[y][x] == 255 &&
                    mapa[y+1][x] == 0) {

                    mapa[y][x] = 0;
                }
            }
        }

        //----------------------

        ofstream zapis(entry.path());

        if (!zapis.is_open()) {
            cout << "Nie mozna zapisac pliku\n";
            continue;
        }

        zapis << "P2\n";
        zapis << width << " " << height << "\n";
        zapis << "255\n";

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width; x++) {
                zapis << mapa[y][x] << " ";
            }

            zapis << "\n";
        }

        zapis.close();
    }

    cout << "  Gotowe\n";
    
        //--------------------
        //miejsce na trenowanie AI
        
        //---------------------

    }
     else if (wybór == 4) {
    } 
      else if (wybór == 5) {
        break;
    }
     else {
        cout << "Nieprawidłowy wybór. Proszę wybrać opcję od 1 do 5.\n";
    }



    }
        return 0;
}