#include<vector>
#include <iostream>
#ifndef M_PI // cmath oder numbers hatte nicht funktioniert, deshalb über diese Lösung erstmal PI definiert.
#define M_PI 3.14159265358979323846
#endif
class Formen
{
public:
    enum classID { idViereck, idDreieck, idKreis }; // Compiler macht die Unterscheidung intern
    virtual float area() = 0;
    virtual classID getClassID() = 0; // nimmt die enum IDs
    virtual std::string getClassName() {}; // für die Ausgabe

};

class Viereck : public Formen
{
public:
    float mWidth = 0;
    float mLength = 0;

    Viereck(float width, float length) {
        mWidth = width;
        mLength = length;

    }

    float area() override
    {
        return mWidth * mLength;
    }

    virtual std::string getClassName() override
    {
        return "Viereck";
    }
    virtual classID getClassID() override // überladen der geerbten virtuellen Funktion getClassID
    {
        return idViereck;
    }

};
class Dreieck : public Formen
{
public:
    // m für Membervariable, s für staticvariable, c für Konstante als Präfix
    // ist sinnvoll, weil die Schreibweise für Member in C++ sonst nicht erkennen, 
    // dass Klassenvariablen gemeint sind. Ist eine Möglichkeit, sonst this-> geht auch
    float mHeight = 0;
    float mLength = 0;

    Dreieck(float height, float length) {
        mHeight = height;
        mLength = length;
    }

    float area() override
    {

        return (mHeight * mLength) * 0.5;
    }

    virtual std::string getClassName() override // overloading der geerbten virtuellen Funktion getType
    {
        return "Dreieck";
    }
    virtual classID getClassID() override // overloading der geerbten virtuellen Funktion getType
    {
        return idViereck;
    }

};
class Kreis : public Formen
{
public:
    float mRadius = 0;
    Kreis(float radius) {
        mRadius = radius;
    }

    float area() override
    {
        return mRadius * mRadius * M_PI;
    }

    virtual std::string getClassName() override // overloading der geerbten virtuellen Funktion getClassName
    {
        return "Kreis";
    }
    virtual classID getClassID() override // overloading der geerbten virtuellen Funktion getClassID
    {
        return idKreis;
    }
};

int main()
{
    bool abbruch = false;

    std::vector <Formen*> formen = {}; // durch Pointer bei Formen kann der Compiler den benötigten Speicherbereich anlegen.
    // Formen* ptr_f;  // Wird auf dem Stack angelegt (Wenn "new" oder "malloc" verwendet wird, landet es auf dem heap)
    while (!abbruch) {
        int formauswahl = 0;
        std::cout << "Bitte fuer Dreieck 1 eingeben, fuer Viereck 2,  fuer Kreis 3, oder fuer Abbruch 0: " << std::endl;
        std::cin >> formauswahl; //(Dreieck, Viereck, Kreis?)
        switch (formauswahl) {
        case 1:
        {
            float length, height;
            std::cout << "Bitte Laenge der Grundlinie und Hoehe des Dreiecks eingeben:" << std::endl;
            std::cin >> length;
            std::cin >> height;
            formen.push_back(new Dreieck(height, length)); // wird auf dem Heap erstellt
            // Dreieck dreieck(height, length); // Lokales Objekt existiert nur bis }
            // formen.push_back(&dreieck);
            break;  // Lokal angelegtes objekt dreieck im Vector wird nach dem break wieder zerstört, 
            // dadurch zeigt der Pointer dann auf einen Zombie
        }

        case 2:
        {
            std::cout << "Bitte Laenge und Breite des Vierecks eingeben:" << std::endl;
            float width, length;
            std::cin >> width;
            std::cin >> length;
            formen.push_back(new Viereck(width, length));
            std::cout << "Formen Laenge: " << formen[0]->area() << std::endl;
            break;
        }
        case 3:
        {
            float radius;
            std::cout << "Bitte Radius des Kreises eingeben:" << std::endl;
            std::cin >> radius;
            formen.push_back(new Kreis(radius));
            break;
        }
        case 0:
        {
            abbruch = true;
            break;
        }

        /*default:
            break*/;
        };


    };

    float areaAllForms = 0;
    float dreieckflaeche_gesamt = 0;
    float viereckflaeche_gesamt = 0;
    float kreisflaeche_gesamt = 0;

    for (int i = 0; i < formen.size(); ++i) {
        areaAllForms += formen[i]->area();
        switch (formen[i]->getClassID()) {
        case Formen::idDreieck:
        {
            std::cout << "Dreiecktest" << std::endl;
        }
        case Formen::idViereck:
        {

        }
        case Formen::idKreis:
        {

        }
        }
        if (formen[i]->getClassName() == "Dreieck")
        {
            dreieckflaeche_gesamt += formen[i]->area();
        }
        // Todo: std::cout << "Gesamtflaeche Vierecke: " ;
        else if (formen[i]->getClassName() == "Viereck")
        {
            viereckflaeche_gesamt += formen[i]->area();
        }
        // Todo: std::cout << "Gesamtflaeche Kreis: " ;
        else if (formen[i]->getClassName() == "Kreis")
        {
            kreisflaeche_gesamt += formen[i]->area();
        }
        //std::cout << formen[i];
        //if( formen[i]->getType() == "Dreieck")
        //    dreieckflaeche_gesamt += Dreieck.area
        // best practice ist Zugriffsfunktion
        //std::cout << formen[i]->getClassName() << " " << formen[i]->area() << std::endl;

    }

    std::cout << "Gesamtflaeche Dreiecke: " << dreieckflaeche_gesamt << std::endl;
    std::cout << "Gesamtflaeche Vierecke: " << viereckflaeche_gesamt << std::endl;
    std::cout << "Gesamtflaeche Kreis: " << kreisflaeche_gesamt << std::endl;
    std::cout << "Die Gesamtflaeche aller eingegebenen Formen: " << areaAllForms << std::endl; //Ausgabe der Fläche insgesamt.

    // Einzelne Objekte, auf die der Vector zeigt, müssen hier noch per delete gelöscht werden, wenn sauber gearbeitet wird.
    // Todo: Objekte des Vectors am Ende löschen.
};