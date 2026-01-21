# Automenu for the Things
### by Marcel Sauder 2026

Automenu ist ein kleines, deterministisches Menüsystem für Terminal- und Embedded-Umgebungen.

Im Zentrum steht ein plattformunabhängiger Core, der als Zustandsmaschine arbeitet. Der Core verarbeitet Eingabeereignisse und stellt den aktuellen Menüzustand sowie ausgelöste Aktionen bereit. Darstellung, Eingabe, IO und Konfigurationsformate liegen bewusst ausserhalb des Cores und werden über Adapter umgesetzt.

Das Projekt ist so aufgebaut, dass der Core testbar, vorhersagbar und unabhängig von der Zielplattform bleibt.

## Eigenschaften

Automenu bietet einen klar getrennten Menü-Core ohne Abhängigkeiten von Terminal, Hardware oder Betriebssystem. Submenüs werden unterstützt, Aktionen werden über eindeutige Kennungen ausgelöst. Navigation ist sowohl über Cursorbewegung als auch über direkte Indexauswahl möglich. Der Core enthält keine IO Logik, kein Rendering und keinen Parser.

## Projektstruktur

include/core.h  
Öffentliche Core API

src/core/core.c  
Implementierung des Menü-Cores

src/core/core_test.c  
Verifikationstest für den Core (Phase A)

src/menu.c  
Definition der Menü-Datenstrukturen

src/terminal.c  
Minimaler Terminal-Adapter (Phase B)

## Build

Minimaler Build ohne Buildsystem für den Terminal-Adapter:

cc -Iinclude src/core/core.c src/menu.c src/terminal.c -o automenu

## Start

./automenu

## Bedienung im Terminal

w bewegt den Cursor nach oben  
s bewegt den Cursor nach unten  
Enter selektiert den aktuellen Menüpunkt  
1 bis 9 selektieren Menüpunkte direkt  
q beendet das Programm

Aufgrund der zeilenweisen Terminaleingabe werden w und s jeweils mit Enter bestätigt.

## Core Verifikation

Der Core wurde unabhängig vom Terminal-Adapter getestet.

Build und Ausführung des Verifikationstests:

cc -Iinclude src/core/core.c src/menu.c src/core/core_test.c -o core_test  
./core_test

Der Test bestätigt korrektes Laden der Menüs, Navigation, Submenüwechsel, Aktionsauslösung und deterministisches Verhalten.

## Architektur

Der Core ist eine reine Zustandsmaschine. Er enthält keine Annahmen über Eingabegeräte, Darstellung oder Plattformen. Alle plattformspezifischen Aspekte werden ausschliesslich in Adaptern umgesetzt.

Details zur Architektur sind in ARCHITECTURE.md dokumentiert.

## Konfiguration

Menüs werden dem Core als Datenstrukturen übergeben. Externe Konfigurationsformate und Parser sind nicht Teil von Version v0.1.0.

Die Spezifikation des Konfigurationsmodells befindet sich in CONFIGURATION.md.

## Projektstatus

Der Core ist stabil, die Architektur ist eingefroren, der Terminal-Adapter ist funktionsfähig. Der aktuelle Stand entspricht Version v0.1.0.

Der detaillierte Status ist in STATUS.md dokumentiert.

## Lizenz

Siehe LICENSE.
