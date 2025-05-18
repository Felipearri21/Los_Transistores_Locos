// Archivo: Color.h
#pragma once

class Color {
public:
    unsigned char R, G, B;

    Color();                             // Constructor por defecto
    Color(unsigned char r, unsigned char g, unsigned char b); // Constructor con parámetros

    void set_Color(unsigned char r, unsigned char g, unsigned char b);
    void implement_Color() const;
};
