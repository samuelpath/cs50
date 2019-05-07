// Helper functions for music
// Instructions: https://docs.cs50.net/2018/x/psets/3/music/music.html

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

#define SEMITONES_IN_OCTAVE 12

int char_to_int(char c);
int get_semitones_due_to_accidental(char accidental);
int get_semitones_from_A(char basicNote);
int get_number_of_semitones_to_A4(string note);

/**
 * Converts a fraction formatted as X/Y to eighths
 * take as input as a string a fraction (e.g., 1/4)
 * return as an int a corresponding number of eigths (2, in this case, since 1/4 is equivalent to 2/8);
 */
int duration(string fraction)
{
    int finalDenominator = 8;

    int numerator = char_to_int(fraction[0]);
    int denominator = char_to_int(fraction[2]);

    int numeratorMultiplier = finalDenominator / denominator;

    return numerator * numeratorMultiplier;
}

/**
 * Calculates frequency (in Hz) of a note
 * take as input as a string a note formatted:
 *  as XY (e.g., A4) where X is any of A through G and Y is any of 0 through 8
 *  as XYZ (e.g., A#4), where X is any of A through G, Y is # or b, and Z is any of 0 through 8
 * return as an int the note’s corresponding frequency, rounded to the nearest integer
 */
int frequency(string note)
{
    int numberOfSemitonesToA4 = get_number_of_semitones_to_A4(note);

    double exponent = numberOfSemitonesToA4 / 12.0;
    double frequency = pow(2, exponent) * 440;

    return round(frequency);
}

/**
 * Determines whether a string represents a rest
 * return true if its input, a string, represents a rest in our machine-readable format, otherwise false.
 */
bool is_rest(string s)
{
    string userInputOnlyLineEnding = "";
    return strcmp(s, userInputOnlyLineEnding) == 0;
}

int char_to_int(char c)
{
    // subtracting the char '0' is a standard way of converting char to int
    return c - '0';
}

int get_number_of_semitones_to_A4(string note)
{
    char basicNote = note[0];
    int semitonesDueToAccidental = 0;
    int octave = 0;

    if (strlen(note) == 2)
    {
        octave = char_to_int(note[1]);
    }
    else if (strlen(note) == 3)
    {
        semitonesDueToAccidental = get_semitones_due_to_accidental(note[1]);
        octave = char_to_int(note[2]);
    }

    int octavesTo4 = octave - 4;
    int semitonesFromA = get_semitones_from_A(basicNote);

    return octavesTo4 * SEMITONES_IN_OCTAVE + semitonesFromA + semitonesDueToAccidental;
}

int get_semitones_due_to_accidental(char accidental)
{
    char sharp = '#';
    char flat = 'b';

    if (accidental == sharp)
    {
        return 1;
    }
    else if (accidental == flat)
    {
        return -1;
    }

    return 0;
}

int get_semitones_from_A(char basicNote)
{
    switch (basicNote)
    {
        case 'C':
            return -9;
        case 'D':
            return -7;
        case 'E':
            return -5;
        case 'F':
            return -4;
        case 'G':
            return -2;
        case 'A':
            return 0;
        case 'B':
            return 2;
    }
    return 0;
}