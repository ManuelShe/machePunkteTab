Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de

Beschreibung:
Dies ist ein Programm zur Erstellung einer Punktetabelle. In jedem Ordner in dem die Abgaben liegen, muss eine Datei korrektur.log liegen, welches Daten ueber das aktuelle Uebungsblatt enthaelt. Dabei sollte sich korrektur.log an bestimmte Vorgaben halten. Bonuspunkte fuer das Uebungsblatt gibt es ab 50 Prozent der Gesamtpunktzahl.
Die Ausgabe der Punktetabelle wird in die Datei korrektur.log angehaengt. Außerdem werden alle (wie folgend beschriebene) Kommentare des Korrektors ebenfalls angehaengt.
 
Alle Kommentare des Korrektors sollten im Quellcode oder in txt-Dateien mit "//#" beginnen.
Punktabzug (hier als Beispiel 1,5 Punkte Abzug): "//#(- 1.5 ) Kommentar"
 
Hier ein Beispiel wie der Inhalt der Datei korrektur.log aussehen koennte (* fuer Bonusaufgaben): 
Korrektur Log
Uebungsblatt 3    Bonuspunkte 1     Gesamtpunktzahl 24
------------------------------------------------------
Aufgaben:
6 7 8 9* -

maximale_Punkte:
9 9 6 6 - 
