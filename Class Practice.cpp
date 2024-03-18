#include<vector>
#include <iostream>
#ifndef M_PI // cmath oder numbers hatte nicht funktioniert, deshalb über diese Lösung erstmal PI definiert.
#define M_PI 3.14159265358979323846
#endif
class Formen
{
public:
    virtual float area() = 0;

};

class Viereck : public Formen
{
public:
    float width = 0;
    float length = 0;

    Viereck(float width, float length) {
        this->width = width;
        this->length = length;
    }

     float area() override
    {
        return this->width * this->length;
    }

};
class Dreieck : public Formen
{
public:
    float height = 0;
    float length = 0;

    Dreieck(float height, float length) {
        this->height = height;
        this->length = length;
    }

    float area() override
    {

        return (this->height * this->length) * 0.5;
    }

};
class Kreis : public Formen
{
public:
    float radius = 0;
    Kreis(float radius) {
        this->radius = radius;
    }

    float area() override
    {
        return this->radius * this->radius * M_PI;
    }
};

int main()
{
    bool abbruch = false;
    std::vector <Formen*> formen={};
    // Formen* ptr_f;  // Wird auf dem Stack angelegt (Wenn "new" oder "malloc" verwendet wird, landet es auf dem heap)
    while (!abbruch) {
        int formauswahl = 0;
        std::cout << "Bitte fuer Dreieck 1 eingeben, fuer Viereck 2,  fuer Kreis 3, oder fuer Abbrauch 0: " << std::endl;
        std::cin >> formauswahl; //(Dreieck, Viereck, Kreis?)
        switch (formauswahl) {
        case 1:
        {
            float length, height;
            std::cout << "Bitte Laenge der Grundlinie und Hoehe des Dreiecks eingeben:" << std::endl;
            std::cin >> length;
            std::cin >> height;
            Dreieck dreieck(height, length);
            formen.push_back(&dreieck);
            break;
        }

        case 2:
        {
            std::cout << "Bitte Laenge und Breite des Vierecks eingeben:" << std::endl;
            float width, length;
            std::cin >> width;
            std::cin >> length;
            Viereck vierEck(width, length);
            formen.push_back(&vierEck);
            std::cout << "Formen Laenge: " << formen[0]->area() << std::endl;
            break;
        }
        case 3:
        {
            float radius;
            std::cout << "Bitte Radius des Kreises eingeben:" << std::endl;
            std::cin >> radius;
            Kreis kreis(radius);
            formen.push_back(&kreis);
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
    for (int i = 0; i < formen.size(); ++i) {
        areaAllForms += formen[i]->area();
        //std::cout << formen[i];
        //Ausgabe der Flächen je Körper wäre noch gut.
        
    }
    std::cout << "Die Gesamtfläche aller eingegebenen Formen: " << areaAllForms << std::endl; //Ausgabe der Fläche insgesamt.
};