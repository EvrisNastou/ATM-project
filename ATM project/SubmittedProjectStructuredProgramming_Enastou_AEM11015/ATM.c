/*
Copyright (C) 2022, 2023 Euripides Nastou
This file is part of ATM Application.
ATM Application is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.
ATM Application is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with ATM
Application. If not, see <https://www.gnu.org/licenses/>.
*/
#include "ATM.h"
int main()
{
    int choice;

    //printf("1953942-Διαχειρηστής\n");
    printf("ATM\n");
    printf("Πατήστε έναν αριθμό για συνέχεια:");
    scanf("%i", &choice);
    system("CLS");
    if(choice==1953942)admin();
    else
    {
        setupDataBase();
        login();
    }
    return 0;
}
