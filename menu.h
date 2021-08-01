#include "setup_routine.h"
#pragma once
void cascadeJoystickUpdateY()
{
    if (yPosition >= 600)
    {
        updateDelayForSettingValues = 200;
        if (yPosition >= 800)
        {
            updateDelayForSettingValues = 100;
            if (yPosition >= 1000)
            {
                updateDelayForSettingValues = 50;
            }
        }
        switch (menuNumber)
        {
        case 0:
            wireLength++;
            break;
        case 1:
            leftIsolationRemove++;
            break;
        case 2:
            rightIsolationRemove++;
            break;
        case 3:
            wiresNumber++;
            break;
        case 4:
            wireDiameter += 0.05;
            if (wireDiameter >= 3)
                wireDiameter = 3;
            break;
        default:
            printOnLCD("ERROR", "FATAL ERROR");
            break;
        }
    }
    else if (yPosition <= 400)
    {
        updateDelayForSettingValues = 200;
        if (yPosition <= 200)
        {
            updateDelayForSettingValues = 100;
            if (yPosition <= 50)
            {
                updateDelayForSettingValues = 50;
            }
        }
        switch (menuNumber)
        {
        case 0:
            wireLength--;
            if (wireLength <= 0)
                wireLength = 0;
            break;
        case 1:
            leftIsolationRemove--;
            if (leftIsolationRemove <= 0)
                leftIsolationRemove = 0;
            break;
        case 2:
            rightIsolationRemove--;
            if (rightIsolationRemove <= 0)
                rightIsolationRemove = 0;
            break;
        case 3:
            wiresNumber--;
            if (wiresNumber <= 0)
                wiresNumber = 0;
            break;
        case 4:
            wireDiameter -= 0.05;
            if (wireDiameter <= 0)
                wireDiameter = 0;
            break;
        default:
            printOnLCD("ERROR", "FATAL ERROR");
            break;
        }
    }
    delay(updateDelayForSettingValues);
    menuSwitch = 1;
}
void JoystickUpdateX()
{
    if (xPosition >= 800)
    {
        menuNumber++;
        delay(500);
        if (menuNumber >= numberOfDifferentMenus)
            menuNumber = numberOfDifferentMenus;
        else
            menuSwitch = 1;
    }
    else if (xPosition <= 100)
    {
        menuNumber--;
        delay(500);
        if (menuNumber <= 0)
            menuNumber = 0;
        else
             menuSwitch = 1;
    }
    else if (!SW_state && menuNumber == numberOfDifferentMenus)
        cycleStart = 1;
}
void joystickRoutine()
{
    xPosition = analogRead(VRx);
    yPosition = analogRead(VRy);
    SW_state = digitalRead(SW);
    cascadeJoystickUpdateY();
    JoystickUpdateX();
}

void switchMenu()
{
    switch (menuNumber)
    {
    case 0:
        printOnLCD("Podaj dlugosc", "kabla(cm) " + String(wireLength));
        break;
    case 1:
        printOnLCD("Odizolowanie", "lewa(mm) " + String(leftIsolationRemove));
        break;
    case 2:
        printOnLCD("Odizolowanie", "prawa(mm) " + String(rightIsolationRemove));
        break;
    case 3:
        printOnLCD("Ilosc sztuk", "kabla " + String(wiresNumber));
        break;
    case 4:
        printOnLCD("Grubosc kabla", "Wartosc :" + String(wireDiameter));
        break;
    case 5:
        printOnLCD("Kliknij, aby", "wykonac ..." + String(wiresNumber));
        break;
    default:
        // statements
        break;
    }
    menuSwitch = 0;
}
void printMenu()
{
    if (menuSwitch)
    {
        switchMenu();
    }
}