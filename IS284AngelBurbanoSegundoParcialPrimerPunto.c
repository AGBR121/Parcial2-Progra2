/*
- Fecha de publicación: 1/10/2024
- Hora de publicación: 8:05pm
- Versión del código: 3
- Autor: Ing(c) Burbano Rodriguez Angel Gabriel
- Nombre del lenguaje utilizado: C
- Versión del lenguaje utilizado: C11
- Versión del compilador utilizado: GCC 6.3.0
- Versión del S.O: Windows 10 Pro Versión 22H2
- Presentado a: Doctor Ricardo Moreno Laverde
- Universidad Tecnológica de Pereira
- Programa de Ingeniería de Sistemas y Computación
- Asignatura IS284 Programación II
- Descripción del programa: Este programa es una graficadora usando solo string
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int listOfCoefficientsAndExponents[2][20] = {{0}};
char screen[25][100] = {{}};
int coefficients[20] = {0};
int exponents[20] = {0};
char equation[100];
int numberOfVariables = 0;
int domainStart = 0;
int endOfDomain = 0;
int interval = 0;
double yValues[100] = {0};
int numberOfTerms = 0;

//Inicializa toda la pantalla con espacios vacíos
void InitScreen() {
    memset(screen, ' ', sizeof(screen));
}

void readEquation() {
    printf("Ingrese la ecuacion a graficar: ");
    scanf("%s", equation);
}

void readLimits(){
    printf("\nDigite el inicio del dominio: ");
    scanf("%i", &domainStart);
    printf("\nDigite el final del dominio: ");
    scanf("%i", &endOfDomain);
    printf("\nDigite el intervalo: ");
    scanf("%i", &interval);
}

void ParseEquation() {
    unsigned int letterPosition = 0;
    char temporalCoefficient[20] = "";
    char temporalExponent[20] = "";
    unsigned int coefficientPosition = 0;
    unsigned int exponentPosition = 0;
    unsigned int findX = 0;
    unsigned int findSign = 0;
    unsigned int findParenthesis = 0;
    unsigned int equationSize = strlen(equation);
    unsigned int temporalCoefficientSize = 0;
    unsigned int temporalExponentSize = 0;
    char actualChar[2] = "";

    //Se revisa caracter por caracter y analiza si es coeficiente o exponente
    while(letterPosition != equationSize) {
        actualChar[0] = equation[letterPosition];
        actualChar[1] = '\0';
        if(toupper(equation[letterPosition]) == 'X') {
            if(strcmp(temporalCoefficient, "") == 0 || strcmp(temporalCoefficient, "-") == 0){
                strcat(temporalCoefficient, "1");
            }
            coefficients[temporalCoefficientSize] = atoi(temporalCoefficient);
            temporalCoefficientSize++;
            strcpy(temporalCoefficient, "");
            findX = 1;
        }else if(equation[letterPosition] == '-' && !findX && !findSign){
            strcat(temporalCoefficient, actualChar);
            findSign = 1;
        }else if(equation[letterPosition] == '+' && !findX && !findSign){
            findSign = 1;
        }else if(equation[letterPosition] == '('){
            findParenthesis = 1;
        }else if(equation[letterPosition] == ')'){
            findParenthesis = 0;
            findSign = 0;
            findX = 0;
            exponents[temporalExponentSize] = atoi(temporalExponent);
            temporalExponentSize++;
        }else if(findX && findSign && !findParenthesis && ( equation[letterPosition] == '-' || equation[letterPosition] == '+')){
            if(equation[letterPosition] == '-'){
                strcat(temporalCoefficient, actualChar);
            }
            if(strcmp(temporalExponent, "")==0 || strcmp(temporalExponent, "-")==0){
                strcat(temporalExponent, "1");
            }
            exponents[temporalExponentSize] = atoi(temporalExponent);
            temporalExponentSize++;
            strcpy(temporalExponent, "");
            findX = 0;
            findSign = 1;
        }else if(!findX && findSign && !findParenthesis && !(equation[letterPosition] == '+' || equation[letterPosition] == '-')){
            strcat(temporalCoefficient, actualChar);
            findX = 0;
            findSign = 1;
            strcpy(temporalExponent, "");
        }else if(findX && findSign && equation[letterPosition] != '+'){
            strcat(temporalExponent, actualChar);
        }else if(!findX && !findSign && !findParenthesis){
            strcat(temporalCoefficient, actualChar);
            findX = 0;
            findSign = 1;
        }else if(findX && !findSign && !findParenthesis && (equation[letterPosition] == '+' || equation[letterPosition] == '-')){
            findX = 0;
            findSign = 1;
            if(strcmp(temporalExponent, "")==0 || strcmp(temporalExponent, "-")==0){
                strcat(temporalExponent, "1");
            }
            exponents[temporalExponentSize] = atoi(temporalExponent);
            temporalExponentSize++;
            strcpy(temporalExponent, "");
            if(equation[letterPosition] == '-'){
                strcat(temporalCoefficient, "-");
            }
        }else if(!findX && findSign && !findParenthesis && equation[letterPosition] == '+'){
            if(strcmp(temporalExponent, "") == 0 || strcmp(temporalExponent, "-") == 0 ){
                strcat(temporalExponent, "0");
            }
            exponents[temporalExponentSize] = atoi(temporalExponent);
            temporalExponentSize++;
            strcpy(temporalExponent, "");

            if(strcmp(temporalCoefficient, "") == 0 || strcmp(temporalCoefficient, "-") == 0 ){
                strcat(temporalCoefficient, "1");
            }
            coefficients[temporalCoefficientSize] = atoi(temporalCoefficient);
            temporalCoefficientSize++;
            strcpy(temporalCoefficient, "");
        }else if(findX && !findSign){
            strcat(temporalExponent, actualChar);
        }else{
            if(strcmp(temporalExponent, "") == 0 || strcmp(temporalExponent, "-") == 0 ){
                strcat(temporalExponent, "0");
            }
            exponents[temporalExponentSize] = atoi(temporalExponent);
            temporalExponentSize++;
            strcpy(temporalExponent, "");

            if(strcmp(temporalCoefficient, "") == 0 || strcmp(temporalCoefficient, "-") == 0 ){
                strcat(temporalCoefficient, "1");
            }
            coefficients[temporalCoefficientSize] = atoi(temporalCoefficient);
            temporalCoefficientSize++;
            strcpy(temporalCoefficient, "");
            strcat(temporalCoefficient, actualChar);

        }
        letterPosition++;
    }

    //Revisamos si qurdó algún número coeficiente sin agregar
    if(strcmp(temporalCoefficient, "") == 0){
        if(strcmp(temporalExponent, "") == 0 || strcmp(temporalExponent, "-") == 0 ){
            strcat(temporalExponent, "1");
        }
        exponents[temporalExponentSize] = atoi(temporalExponent);
        temporalExponentSize++;
    }else{
        if(strcmp(temporalExponent, "") == 0 || strcmp(temporalExponent, "-") == 0 ){
            strcat(temporalExponent, "0");
        }
        exponents[temporalExponentSize] = atoi(temporalExponent);
        temporalExponentSize++;

        if(strcmp(temporalCoefficient, "") == 0 || strcmp(temporalCoefficient, "-") == 0 ){
            strcat(temporalCoefficient, "0");
        }
        coefficients[temporalCoefficientSize] = atoi(temporalCoefficient);
        temporalCoefficientSize++;

    }
    numberOfTerms = temporalCoefficientSize;
}

//Los valores de coeficientes y exponentes van en una sola matriz (obligatorio en el parcial)
void SaveCoefficientsExponents(){
    for(int arrayPosition = 0; arrayPosition < numberOfTerms; arrayPosition++ ){
        listOfCoefficientsAndExponents[0][arrayPosition] = coefficients[arrayPosition];
        listOfCoefficientsAndExponents[1][arrayPosition] = exponents[arrayPosition];
    }
}

void EvaluateYValues() {
    int xValue = domainStart;
    int numberOfOperation = 0;
    while (xValue <= endOfDomain) {
        double yValue = 0;
        for (int operationsPosition = 0; operationsPosition < numberOfTerms; operationsPosition++) {
            // Evitar 0 a potencia negativa
            if (exponents[operationsPosition] < 0 && xValue == 0) {
                yValue = NAN;
                break;
            }
            yValue += listOfCoefficientsAndExponents[0][operationsPosition] * pow(xValue, listOfCoefficientsAndExponents[1][operationsPosition]);

        }

        yValues[numberOfOperation] = yValue;
        numberOfOperation++;
        xValue += interval;
        numberOfVariables++;
    }
}

void PrintTableOfCoefficientsAndExponentss(){
    printf("\n  Coeficiente   Potencia\n");
    printf("+------------+------------+\n");
    for(int counter = 0; counter < numberOfTerms; counter++){
        printf("|%-12d|%-12d|\n", listOfCoefficientsAndExponents[0][counter], listOfCoefficientsAndExponents[1][counter]);
        printf("+------------+------------+\n");
    }
}

void PrintTableOfValues(){
    printf("\n     X     |     Y     \n");
    printf("+----------+-----------+\n");
    for(int counter = 0; counter < numberOfVariables; counter++){
        if(isnan(yValues[counter])){
            printf("|%-10d|    IND    |\n", domainStart+(interval*counter));
        }else{
            printf("|%-10d|%-11.2f|\n", domainStart+(interval*counter), yValues[counter]);
        }
        printf("+----------+-----------+\n");
    }
    printf("\n\n");
}

double FindHighestValueOfY(){
    double yMax = yValues[0];
    for(int counter = 0; counter < numberOfVariables; counter++){
        if(yValues[counter] > yMax){
            yMax = yValues[counter];
        }
    }
    return yMax;
}

double FindLowestValueOfY(){
    double yMin = FindHighestValueOfY();
    for(int counter = 0; counter < numberOfVariables; counter++){
        if(yValues[counter] < yMin){
            yMin = yValues[counter];
        }
    }
    return yMin;
}


// Función para dibujar los ejes y graficar los puntos en la pantalla
void DrawAxesAndPoints(double yMin, double yMax) {
    // Escala en X (para convertir valores reales en posiciones de pantalla)
    double pixelX = (abs(domainStart - endOfDomain) == 0) ? 100 : 100.0 / abs(domainStart - endOfDomain);

    // Escala en Y (para convertir valores reales en posiciones de pantalla)
    double pixelY = (fabs(yMin - yMax) == 0) ? 24 : 24.0 / fabs(yMin - yMax);

    // Posición del eje X en la pantalla (en coordenadas de la matriz)
    double axisX = -yMin * pixelY;

    // Posición del eje Y en la pantalla (en coordenadas de la matriz)
    double axisY = -domainStart * pixelX;

    // Conversión de los ejes a enteros
    int axisXInt = (int) round(axisX);
    int axisYInt = (int) round(axisY);

    // --- DIBUJAR EJE Y ---
    if (axisYInt >= 0 && axisYInt <= 99) {
        for (int rowIndex = 0; rowIndex < 25; rowIndex++) {
            screen[rowIndex][axisYInt] = '|';
        }

        // Calcular marcas de escala en el eje Y
        double stepY = fabs(yMin - yMax) / 5.0;
        for (int markIndex = 0; markIndex < 6; markIndex++) {
            int placeY = (int) (24.0 - round(pixelY * (yMin + stepY * markIndex) + axisX));
            char label[12] = "";
            sprintf(label, "%.2f", yMin + stepY * markIndex);
            int labelLength = strlen(label);

            // Evitar que las etiquetas se dibujen sobre el eje X
            if (placeY != 24 - axisXInt) {
                if (axisYInt < 5) { // Cuando el eje Y está muy a la izquierda
                    for (int labelIndex = 0; labelIndex < labelLength; labelIndex++) {
                        screen[placeY][axisYInt + 5 + labelIndex] = label[labelIndex];
                    }
                } else if (axisYInt > 95) { // Cuando el eje Y está muy a la derecha
                    for (int labelIndex = 0; labelIndex < labelLength; labelIndex++) {
                        screen[placeY][axisYInt - 7 + labelIndex] = label[labelIndex];
                    }
                } else { // Cuando el eje Y está en el centro
                    for (int labelIndex = 0; labelIndex < labelLength; labelIndex++) {
                        screen[placeY][axisYInt - 3 + labelIndex] = label[labelIndex];
                    }
                }
            }
        }
    }

    // --- DIBUJAR EJE X ---
    if (axisXInt >= 0 && axisXInt <= 23) {
        for (int columnIndex = 0; columnIndex < 100; columnIndex++) {
            screen[23 - axisXInt][columnIndex] = '-';
        }

        // Colocar etiquetas en el eje X
        for (int pointIndex = 0; pointIndex < numberOfVariables; pointIndex++) {
            char label[12] = "";
            int placeX = (int) round(pixelX * (domainStart + interval * pointIndex) + axisY);

            if (placeX < 0) {
                placeX = 0;
            } else if (placeX > 99) {
                placeX = 99;
            }

            sprintf(label, "%d", domainStart + (interval * pointIndex));
            int labelLength = strlen(label);

            for (int labelIndex = 0; labelIndex < labelLength && (placeX + labelIndex - 2) < 100; labelIndex++) {
                if (pointIndex == numberOfVariables - 1) {
                    screen[24 - axisXInt][placeX + labelIndex - 2] = label[labelIndex];
                } else {
                    screen[24 - axisXInt][placeX + labelIndex] = label[labelIndex];
                }
            }
        }
    }

    // --- GRAFICAR PUNTOS DE LA FUNCIÓN ---
    for (int pointIndex = 0; pointIndex < numberOfVariables; pointIndex++) {
        if (!isnan(yValues[pointIndex])) {
            int placeX = (int) round(pixelX * (domainStart + interval * pointIndex) + axisY);
            int placeY = (int) (24.0 - round(pixelY * yValues[pointIndex] + axisX));

            if (placeX < 0) {
                placeX = 0;
            } else if (placeX > 99) {
                placeX = 99;
            }
            if (placeY < 0) {
                placeY = 0;
            } else if (placeY > 23) {
                placeY = 23;
            }
            screen[placeY][placeX] = 'X';
        }
    }
}

void DrawGraph() {
    for(int yAxis = 0; yAxis<25; yAxis++){
        for(int xAxis = 0; xAxis<100; xAxis++){
            if(!screen[yAxis][xAxis]){
                printf(" ");
            }else{
                printf("%c", screen[yAxis][xAxis]);
            }
        }
        printf("\n");
    }
}

void Graph(){
    InitScreen();
    readEquation();
    ParseEquation();
    SaveCoefficientsExponents();
    PrintTableOfCoefficientsAndExponentss();
    readLimits();
    EvaluateYValues();
    PrintTableOfValues();
    double yMin = FindLowestValueOfY();
    double yMax = FindHighestValueOfY();
    DrawAxesAndPoints(yMin, yMax);
    DrawGraph();
}

int main() {
    Graph();
    return 0;
}
