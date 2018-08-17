// Helper functions for music
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

double notes(char note, int freq);
double accidentals(char accidental, double freq);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = fraction[0] - '0';
    int den = fraction[2] - '0';

    int numerator = ((8 / den) * num);
    return numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char b_note[4]; // assign chars from string
    b_note[0] = note[0];
    b_note[1] = note[1];
    b_note[2] = note[2];
    b_note[3] = '\0';

    int freq = 440; // base frequency

    if (b_note[1] != '#' && b_note[1] != 'b') // no accidentals
    {
        if (atoi(&note[1]) == 4) // octave 4
        {
            double f = notes(b_note[0], freq);
            freq = round(f);
            return freq;
        }

        else if (atoi(&b_note[1]) < 4) // octave lower than 4
        {
            for (int i = 4; i >= 0; i--)
            {
                if (i != atoi(&b_note[1])) //determine right base frequency
                {
                    freq /= 2;
                }
                else
                {
                    double f = notes(b_note[0], freq);
                    freq = round(f);
                    return freq;
                }
            }
        }

        else if (atoi(&b_note[1]) > 4) // octave lower than 4
        {
            for (int i = 4; i <= 8; i++)
            {
                if (i != atoi(&b_note[1])) //determine right base frequency
                {
                    freq *= 2;
                }
                else
                {
                    double f = notes(b_note[0], freq);
                    freq = round(f);
                    return freq;
                }
            }
        }
    }

    else if (b_note[1] == '#' || b_note[1] == 'b') // with accidentals
    {
        if (atoi(&b_note[2]) == 4) // octave 4
        {
            double f = notes(b_note[0], freq);
            f = accidentals(b_note[1], f);
            freq = round(f);
            return freq;
        }

        else if (atoi(&b_note[2]) < 4) // octave lower than 4
        {
            for (int i = 4; i >= 0; i--)
            {
                if (i != atoi(&b_note[2])) //determine right base frequency
                {
                    freq /= 2;
                }
                else
                {
                    double f = notes(b_note[0], freq);
                    f = accidentals(b_note[1], f);
                    freq = round(f);
                    return freq;
                }
            }
        }

        else if (atoi(&b_note[2]) > 4) // octave higher than 4
        {
            for (int i = 4; i <= 8; i++)
            {
                if (i != atoi(&note[2])) //determine right base frequency
                {
                    freq *= 2;
                }
                else
                {
                    double f = notes(b_note[0], freq);
                    f = accidentals(b_note[1], f);
                    freq = round(f);
                    return freq;
                }
            }
        }
    }
    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // if string s represents a rest return true, otherwise return false
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double notes(char note, int freq) // adjust frequency for notes
{
    double i = 0;

    switch (note)
    {
        case 'A':
            i = freq;
            break;
        case 'B':
            i = pow(2.0, (2.0 / 12.0)) * freq;
            break;
        case 'C':
            i = pow(2.0, (3.0 / 12.0)) * (freq / 2);
            break;
        case 'D':
            i = pow(2.0, (5.0 / 12.0)) * (freq / 2);
            break;
        case 'E':
            i = pow(2.0, (7.0 / 12.0)) * (freq / 2);
            break;
        case 'F':
            i = pow(2.0, (8.0 / 12.0)) * (freq / 2);
            break;
        case 'G':
            i = pow(2.0, (10.0 / 12.0)) * (freq / 2);
            break;
    }
    return i;
}

double accidentals(char accidental, double freq) // adjust frequency for accidental
{
    double i = 0;

    switch (accidental)
    {
        case '#':
            i = freq * pow(2.0, (1.0 / 12.0));
            break;
        case 'b':
            i = freq / pow(2.0, (1.0 / 12.0));
            break;
    }
    return i;
}