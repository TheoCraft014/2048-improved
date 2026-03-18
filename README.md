#Implementarea jocului 2048 folosind ncurses
#Constantinescu Theodor

    Jocul incepe cu alegerea dimensiunilor ecranului, unde exista optiunea
unui ecran de dimensiune mare sau mica.
Dupa aceea apare titlul, urmat de meniu ce are in adaos mai multe optiuni:

##Resume: 
    te intorci la jocul actual 

##Settings : 
    seteaza durata de asteptare inainte de mutarea automata

##Save: 
    salveaza in fisierul salvari.txt datele unui joc intr-un oneliner, 
asociindu-i si un ID. Toate jocurile sunt salvate in salvari.txt. Aceasta
include matricea scorul si starea jocului

##Load: 
    apare pe ecran in functie de ID jocurile salvate - pe care ulteror
le poti incarca.

##Quit: 
    iesire din joc

Am folosit mai multe biblioteci pentru sortarea a diferite functii utile 
in implementarea programului.

De asemenea, la fiecare mutare indiferent de directe am verificat validitatea
acestora prin intermediul a doua matrici ce copiaza valorile.

##Rulare:
- instalare fisiere
- rulare comanda: make run
- eliminarea executabilului si a fisierelor obiect: make clean

##Aceasta varianta de joc 2048 ofera functionalitati suplimentare:

- meniu interactiv
- salvare jocuri in fisier
- incarcare jocuri salvate
- setari pentru mutare automata (repede, mediu, incet)
- detectare win sau game over
- highscore ce al tuturor utilizatorilor
