#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define CYAN "\033[36m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc

float R1;
float R2;
float vIn;
float vOut;

bool hasCalculated = false;

string answer;
string scale;

// ---> AUDIO
void musicIntro()
{
    PlaySound(
        TEXT("audio/MM_vout_music_intro"),
        NULL,
        SND_ASYNC);
}

void audioProgress(int i)
{
    if (i < 1)
    {
        PlaySound(
            TEXT("audio/MM_vout_processing"),
            NULL,
            SND_ASYNC);
    }
}

void audioConfirm()
{
    PlaySound(
        TEXT("audio/MM_vout_nav_active"),
        NULL,
        SND_ASYNC);
}

// ---> MATH
float voltageDivider()
{
    vOut = (R2 / (R1 + R2)) * vIn;
    hasCalculated = true;
    return vOut;
}

float nearestValue(float in)
{
    // Issue: Trailing zeros
    float value = (int)(in * 1000 + .5);
    if (in < 1)
    {
        scale = "mV";
        return value; // mV
    }
    else
    {
        scale = "V";
        return (value / 1000); // V
    }
}

// ---> CIRCUIT
void circuitDescription()
{
    cout << CYAN << "Enter input voltage " << RESET << "(in volts): ";
    cin >> vIn;
    audioConfirm();
    cout << RED << "Enter value for Resistor #1 " << RESET << "(in ohms): ";
    cin >> R1;
    audioConfirm();
    cout << RED << "Enter value for Resistor #2 " << RESET << "(in ohms): ";
    cin >> R2;
    audioConfirm();
    sleep_for(600ms);
}

void circuitDetails()
{
    cout << endl;
    cout << "Circuit Details:" << endl;
    cout << "-----------------------------" << endl;
    sleep_for(300ms);
    cout << CYAN << "Input voltage (Vin) = " + to_string(nearestValue(vIn)) + " volts" << endl;
    sleep_for(300ms);
    cout << RED << "Resistor #1 (R1) = " + to_string((int)R1) + " ohms." << endl;
    sleep_for(300ms);
    cout << RED << "Resistor #2 (R2) = " + to_string((int)R2) + " ohms." << endl;
    sleep_for(300ms);
    cout << CYAN << "Output voltage (Vout) = " + to_string(nearestValue(vOut)) + " " + scale << RESET << endl;
    cout << "-----------------------------" << endl;
    cout << endl;
}

// ---> ASCII
void animation()
{
    char punc[7] = {':', ':', '.', '.', '.', '.', '.'};
    int i;
    for (i = 0; i < 7; i++)
    {
        audioProgress(i);
        sleep_for(150ms);
        cout << punc[i];
    }
    cout << endl;
}

// ---> MAIN
int main()
{
    if (hasCalculated == false)
    {
        musicIntro();
        cout << YELLOW << endl;
        cout << "  /-------------------------/" << endl;
        sleep_for(500ms);
        cout << " / V-OUT - Voltage Divider /" << endl;
        sleep_for(500ms);
        cout << "/-------------------------/" << endl;
        cout << RESET << endl;
        sleep_for(1s);
    }
    circuitDescription();
    voltageDivider();
    animation();
    cout << "Your output voltage is " << CYAN << to_string(nearestValue(vOut)) + " " + scale << RESET << endl;
    sleep_for(300ms);
    circuitDetails();
    cout << "Would you like to make another calculation? (yes/no) ";
    cin >> answer;
    audioConfirm();
    for (int i = 0; i < answer.length(); i++)
    {
        answer[i] = tolower(answer[i]);
    }
    if (answer == "yes")
    {
        main();
    }
    else
    {
        cout << endl;
        cout << YELLOW << "V-OUT exited. Goodbye." << RESET << endl;
    }
}
