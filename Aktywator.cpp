#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <windows.h>


using namespace std;
namespace fs = std::filesystem;


int main() {
    while (true) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    //system("py Generator_danych.py");

    int wybór ;

    cout << "--- WIELKA MASZYNA AI ---\n\n[1] generowanie obrazów AI\n[2] przegląd plików\n[3] Uczenie AI\n[4] Testowanie AI\n[5] Wyjście\n";

    cin >> wybór;

    if (wybór == 1) {
        int wariant_koloru = 0;
        int ilosc_kopii = 10;
        int width = 160;
        int height = 120;
        string folder_name;

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
            string command = "py \"Generator_danych.py\" " + std::to_string(wariant_koloru) + " " + std::to_string(ilosc_kopii) + " " + std::to_string(width) + " " + std::to_string(height) + " \"" + folder_name + "\"";
            system(command.c_str());
            
            std::string path = "Dane treningowe/" + folder_name + "/DANE " + folder_name + ".txt";
            ofstream plik(path);

            plik << "Nazwa Pakietu: " << folder_name << "\n";
            plik << "data utworzenia : " << width << "\n";
            plik << "ilosc kopii: " << ilosc_kopii << "\n";
            plik << "width: " << width << "\n";
            plik << "height: " << height << "\n";
            plik << "wariant_koloru: " << wariant_koloru << "\n";

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
                                while (std::getline(plik, linia)) {
                                    cout << "    " << linia << "\n";
                                }
                                plik.close();
                            } else {
                                cout << "    Błąd: Nie można otworzyć pliku\n";
                            }
                        }
                    }
                }
                cout << "\n";
            }
        }
    }
     else if (wybór == 3) {
        system("py Uczenie_AI.py");
    }
     else if (wybór == 4) {
        system("py Testowanie_AI.py");
    } 
      else if (wybór == 5) {
        break;
    }
     else {
        cout << "Nieprawidłowy wybór. Proszę wybrać opcję od 1 do 4.\n";
    }



    }
        return 0;
}