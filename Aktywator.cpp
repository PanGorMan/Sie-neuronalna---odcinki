#include <iostream>
#include <iomanip>
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
    int progress = 0; // wartość dla wizualizacj
    int wszystkie_pliki = 0;
    int wariant_koloru = 0;
    int ilosc_kopii = 1000;
    int width = 160;
    int height = 120;
    string folder_name;
    string sciezka ;

    cout << "\n--- WIELKA MASZYNA AI ---\n\n[1] generowanie obrazów AI\n[2] przegląd plików\n[3] Uczenie AI\n[4] Testowanie AI\n[5] Reset\n[6] Wyjście\n";

    cin >> wybór;
    if (wybór == 1) {
        cout << "\nGenerowanie obrazów\n";

        while (true){
        if (wybór == 1){
        cout << "Wariant koloru (1 - czarno-białe 2 - kolorowe):\n ";
        cin >> wariant_koloru;
        if(wariant_koloru == 1){
            cout << "\nWybrano-biały wariant\n "; wybór++ ;
        }else if(wariant_koloru == 2){
            cout << "\nWybrano-biały wariant (bo na kolorowym jeszcze nie operujemy)\n "; wybór++ ;
        }else{
            cout << "\nNie prawidłowa odpowiedź\n ";
        }}
        if (wybór == 2){
        cout << "Ilość kopii (min 1000 , max 10000): \n";
        cin >> ilosc_kopii;
        if(ilosc_kopii <= 999){
            cout << "\nZa mała liczba kopii - AI potrzebuje więcej danych\n ";
        }else if(ilosc_kopii > 10000){
            cout << "\nZa duża liczba kopii - Liczba przewyższa zakres\n ";
        }else { wybór++ ;
        }}
        if (wybór == 3){
        cout << "Szerokość obrazu : 1 - 640x480, 2 - 320x240 ,3 - 160x120\n";
        cin >> width;

        if(width == 1){
            cout << "\nWybrano-biały wariant 640x480\n ";width = 640; height = 480; wybór++ ;
        }else if(width == 2){
            cout << "\nWybrano-biały wariant 320x240\n ";width = 320; height = 240; wybór++ ;
        }else if(width == 3){
            cout << "\nWybrano-biały wariant 160x120\n "; width = 160; height = 120;wybór++ ;
        }else{
            cout << "\nNieprawidłowy wybór rozdzielczości\n ";
        }}

        if (wybór == 4){
        cout << "jak nazwać folder z zestawem danych ? (np. 'DANE1')\n"; // sprawdzenie czy już taki folder istnieje
        cin >> folder_name;
        string sciezka = "Dane treningowe/" + folder_name;
                if (fs::exists(sciezka)) {
            cout << "ERROR -- taki folder juz istnieje!\n\n";
        }
        else {
            cout << "Nazwa zaakceptowana\n";
            wybór++;
        }}

        if (wybór == 5){
        cout << "czy wygenerować obraz ? (1 - tak, 0 - nie)\n";
        cin >> wybór;
        if (wybór == 0){
            cout << "\nGenerowanie obrazów zostało anulowane.\n";break;
        }
        else if (wybór == 1) {

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

            cout << "\n Tworzenie danych zakończone sukcesem.\n";break;

        } else {
            cout << "\nGenerowanie obrazów zostało anulowane.\n"; wybór = 4 ;
        }}

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

    sciezka = "Folder operacyjny/Obrazy";

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
    // ma się wpienić jak nie ma takiego folderu


    cout << "\nKopiowanie danych do Folderu operacyjnego...";

    string source_path = "Dane treningowe/" + folder_name;
    string dest_path = "Folder operacyjny/Obrazy";

    filesystem::create_directories(dest_path);


for (const auto& entry : filesystem::directory_iterator(source_path)) {
    if (entry.is_regular_file()) {
        string filename = entry.path().filename().string();

        if (filename.size() >= 4 &&
            filename.substr(filename.size() - 4) == ".pgm") {

            filesystem::path dest_file =
                filesystem::path(dest_path) / filename;

            progress++;

            if (progress % 10 == 0) { // aktualizacja wizualizacji co 10 plików
                cout << "\rProgress: " << progress << " files copied";
                cout.flush();
            }

            try {
                filesystem::copy(
                    entry.path(),
                    dest_file,
                    filesystem::copy_options::overwrite_existing
                );

            } catch (const filesystem::filesystem_error& e) {
                cout << "Błąd podczas kopiowania " << filename
                     << ": " << e.what() << "\n";
            }
        }
    }
}
    progress = 0; 
    cout << "  Gotowe\n";
    cout << "Naprawianie pliku...\n";

    //---------------------

    fs::path folder = "Folder operacyjny/Obrazy";

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

                if (x > 0 && x + 1 < width && mapa[y][x-1] == 255 && mapa[y][x] == 0 && mapa[y][x+1] == 255) {
                    mapa[y][x] = 255;
                }

                if (y > 0 && y + 1 < height && mapa[y-1][x] == 255 && mapa[y][x] == 0 && mapa[y+1][x] == 255) {
                    mapa[y][x] = 255;
                }
            }
        }

        // łączenie linii -- do poprawki

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width; x++) {

                if (x > 0 && x + 1 < width && mapa[y][x-1] == 0 && mapa[y][x] == 255 && mapa[y][x+1] == 0) {
                    mapa[y][x] = 0;
                }

                if (y > 0 && y + 1 < height && mapa[y-1][x] == 0 && mapa[y][x] == 255 && mapa[y+1][x] == 0) {
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

        
            progress++;

            if (progress % 10 == 0) { // aktualizacja wizualizacji co 10 plików
                cout << "\rProgress: " << progress << " files naprawione";
                cout.flush();
            }
        


    }

    cout << "  Gotowe\n";
    
    cout << "Trenowanie AI...\n";

    vector<vector<int>> dataset_X;
    vector<int> dataset_Y;

    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        cout << "ERROR -- Nie znaleziono folderu\n";
        return 0;
    }

    // utworzenie dataset.csv
    ofstream csv("Folder operacyjny/Dataset/dataset.csv");

    if (!csv.is_open()) {
        cout << "ERROR -- Nie mozna utworzyc dataset.csv\n";
        return 0;
    }

    for (const auto& entry : fs::directory_iterator(folder)) {

        if (!entry.is_regular_file())
            continue;

        ifstream plik(entry.path());

        if (!plik.is_open()) {
            cout << "ERROR -- Nie mozna otworzyc pliku\n";
            continue;
        }

        vector<string> dane;
        string temp;

        while (plik >> temp) {
            dane.push_back(temp);
        }

        // pobieranie labela z nazwy pliku

        string filename = entry.path().filename().string();

        vector<string> parts;
        string temp2;

        stringstream ss(filename);

        while (getline(ss, temp2, '-')) {
            parts.push_back(temp2);
        }

        int liczba_linii_narysowanych = stoi(parts[1]);

        plik.close();

        int width = stoi(dane[1]);
        int height = stoi(dane[2]);

        vector<int> Lista_znakow;

        int index = 4;

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width; x++) {

                if (stoi(dane[index]) == 255)
                    Lista_znakow.push_back(1);
                else
                    Lista_znakow.push_back(0);

                index++;
            }
        }

        // dodanie do datasetu

        dataset_X.push_back(Lista_znakow);
        dataset_Y.push_back(liczba_linii_narysowanych);

        // zapis do CSV

        csv << liczba_linii_narysowanych;

        for (int pixel : Lista_znakow) {
            csv << "," << pixel;
        }

        csv << "\n";

        cout << "Dodano obraz: " << filename << "\n";
    }

    // zamknięcie pliku CSV
    csv.close();

    cout << "\n";
    cout << "Gotowy dataset AI\n";

    cout << "Liczba probek: " << dataset_X.size() << "\n";

    system("python Uczenie_AI.py");



    }
     else if (wybór == 4) {
        system("python Testowanie_AI.py");

    } 
    else if (wybór == 5) {

    sciezka = "Dane treningowe";
    if (fs::exists(sciezka)) {
    for (const auto& entry : fs::directory_iterator(sciezka)) {
        fs::remove_all(entry.path());
    }
    cout << "Dane treningowe wykasowane\n";
    }
        sciezka = "Folder operacyjny/Dataset";
    if (fs::exists(sciezka)) {
    for (const auto& entry : fs::directory_iterator(sciezka)) {
        fs::remove_all(entry.path());
    }
    }
    sciezka = "Folder operacyjny/Obrazy";
    if (fs::exists(sciezka)) {
    for (const auto& entry : fs::directory_iterator(sciezka)) {
        fs::remove_all(entry.path());
    }
    cout << "Folder operacykny wykasowany\n";
    }
    sciezka = "Gotowe_AI";
    if (fs::exists(sciezka)) {
    for (const auto& entry : fs::directory_iterator(sciezka)) {
        fs::remove_all(entry.path());
    }
    cout << "Pliki z AI usunięte\n";
    }


    }

    else if (wybór == 6) {
        break;
    }
     else {
        cout << "Nieprawidłowy wybór. Proszę wybrać opcję od 1 do 5.\n";
    }


    }
        return 0;
}