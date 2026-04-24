# Icy Tower Clone - Jump Physics Simulator

Edukacyjna gra platformowa 2D inspirowana klasycznym "Icy Tower", stworzona w C++ przy użyciu biblioteki SDL2. Projekt skupia się na proceduralnie generowanych platformach oraz w pełni konfigurowalnym na żywo systemie fizyki. Ruch gracza oparto na algorytmie śledzącym obecną i poprzednią pozycję (całkowanie podobne do Verleta). 

## Funkcjonalności
* **Fizyka i manipulacja skokiem:** Gra pozwala na żywo regulować docelową wysokość skoku oraz jego zasięg (czas do szczytu) za pomocą klawiszy, automatycznie przeliczając odpowiednią grawitację i prędkość początkową.
* **Mechanika platformowa:** Postać posiada zdolność podwójnego skoku. Wciśnięcie klawisza w dół przyspiesza opadanie, a puszczenie klawisza skoku w trakcie lotu sprawia, że postać opada szybciej.
* **Proceduralny poziom i kamera:** Rozgrywka toczy się na pionowej mapie ze stoma losowo wygenerowanymi platformami o różnych szerokościach i odstępach. Kamera płynnie podąża za graczem w górę ekranu.
* **Sterowanie:** Poruszanie się postacią za pomocą klawiszy A/D (lub strzałek) oraz skakanie przy użyciu W (lub Spacji / Strzałki w górę). Regulacja parametrów skoku odbywa się za pomocą klawiszy U/J (wysokość) oraz I/K (zasięg).

## Technologie
* **Język:** C++ (Standard 20) 
* **Biblioteki:** SDL2, SDL2_image 
* **Narzędzie budowania:** CMake
* **Wymagania:** Konieczność lokalnej instalacji i podlinkowania `SDL2` oraz `SDL2_image`.

*Data realizacji: Grudzień 2025*

---

# Icy Tower Clone - Jump Physics Simulator 

An educational 2D platformer inspired by the classic "Icy Tower", built in C++ using the SDL2 library. The project focuses on procedurally generated platforms and a highly customizable, real-time jump physics system. The character's movement is driven by tracking current and previous positions (Verlet-like integration). 

## Features
* **Live Physics Tuning:** The game allows real-time adjustment of the target jump height and jump distance (time to apex) via keyboard shortcuts. It automatically recalculates the resulting gravity and initial jump velocity based on these inputs.
* **Platforming Mechanics:** The character has a double-jump capability. Players can press the down key to accelerate falling, and releasing the jump key early actively reduces jump height.
* **Procedural Level & Camera:** The vertical level features a hundred randomly generated platforms with varying widths and gaps. A dynamic camera smoothly follows the player's ascent.
* **Controls:** Move using A/D or Arrow Keys, and jump with W, Space, or the Up Arrow. Adjust physics parameters on the fly using U/J for height and I/K for jump distance.

## Technologies 
* **Language:** C++ (Standard 20)
* **Libraries:** SDL2, SDL2_image 
* **Build Tool:** CMake
* **Requirements:** Local installation and linking of `SDL2` and `SDL2_image` are mandatory.

*Developed: December 2025*
