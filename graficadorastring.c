#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int main() {
    //variable i para iterar en el texto de la funcion
    int i = 0;
    //variable auxiliar para convertir el coeficiente temporal y el exponente temporal en vacío
    char auxiliar[10] = "";
    //variable ecuation que guarda el string de la ecuacion
    char ecuation[100] = "";
    //variable coeficienteTemp que guarda el coeficiente en el momento de la posicion del ciclo
    char coeficienteTemp[20] = ""; 
    //variable exponenteTemp que guarda el exponente en el momento de la posicion del ciclo
    char exponenteTemp[20] = ""; 
    //variable coeficientes que es un array de coeficientes de la ecuación
    int coeficientes[20]; 
    //variable exponentes que es un array de exponentes de la ecuación
    int exponentes[20]; 
    //variable y que guarda los valores de y en un array de acuerdo a la ecuacion.
    double y[20];
    //variable coeficienteExponente que guerda en un array los arrays coeficientes y exponentes
    int coeficienteExponente[2][20];
    //variable x que servirá como condicional para saber si en las iteraciones pasamos por una x
    int x = 0;
    //variable nCoeficientes que guarda la posicion dentro del array de coeficientes para guardar el proximo coeficiente
    int nCoeficientes = 0;
    //variable nExponentes que guarda la posicion dentro del array de exponentes para guardar el proximo exponente
    int nExponentes = 0;
    //variable signo que servirá como condicional para saber si en las iteraciones pasamos por un signo
    int signo = 0;
    //variable parentesis que servirá como condicional para saber si ne las iteraciones pasamos por un paréntesis
    int parentesis = 0;
    printf("Ingrese la ecuacion a graficar: ");
    scanf("%s", &ecuation);
    //variable longitudEcuation para saber el número de carácteres de la ecuacion
    int longitudEcuation = strlen(ecuation);
    //variable longitudCoeficienteTemp para saber el número de carácteres del coeficienteTemp
    int longitudCoeficienteTemp = strlen(coeficienteTemp);
    //variable longitudExponenteTemp para saber el número de carácteres del exponenteTemp
    int longitudExponenteTemp = strlen(exponenteTemp);
    //variable inicioRango que guarda el inicio del dominio que el usuario requiera
    int inicioRango = 0;
    //variable finRango que guarda el final del dominio que el usuario requiera
    int finRango = 0;
    //varible saltos que guarda los intervalos que el usuario requiera
    int saltos = 0;
    //variable ecuationAuxiliar para convertir el caracter en el que estemos ubicados en string
    char ecuationAuxiliar[2];
    //Ciclo para evaluar obtener los coeficientes y exponentes de la ecuación
    while(i != longitudEcuation){
        ecuationAuxiliar[0] = ecuation[i];
        ecuationAuxiliar[1] ='\0';
        if(toupper(ecuation[i]) == 'X'){
            if(strcmp(coeficienteTemp, auxiliar) == 0 || strcmp(coeficienteTemp, "-") == 0) {
                strcat(coeficienteTemp, "1");
            }
            coeficientes[nCoeficientes] = atoi(coeficienteTemp);
            nCoeficientes++;
            strcpy(coeficienteTemp, auxiliar);
            x = 1;
        }else if(ecuation[i] == '-' && !x && !signo){
            strcat(coeficienteTemp, ecuationAuxiliar);
            signo = 1;
        }else if(ecuation[i] == '+' && !x && !signo){
            signo = 1;
        }else if(ecuation[i] == '('){
            parentesis = 1;
        }else if(ecuation[i] == ')'){
            parentesis = 0;
            signo = 0;
            x = 0;
            exponentes[nExponentes] = atoi(exponenteTemp);
            strcpy(exponenteTemp, auxiliar);
            nExponentes++;
        }else if( x && signo && !parentesis && ecuation[i] == '-'){
            strcat(coeficienteTemp, ecuationAuxiliar);
            if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "1");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
            strcpy(exponenteTemp, auxiliar);
            x = 0;
            signo = 1;
        }else if(x && signo && !parentesis && ecuation[i] == '+'){
            if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "1");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
            strcpy(exponenteTemp, auxiliar);
            x = 0;
            signo = 1;
        }else if(!x && signo && !parentesis && !(ecuation[i] == '+' || ecuation[i] == '-')){
            strcat(coeficienteTemp, ecuationAuxiliar);
            x = 0;
            signo = 1;
            strcpy(exponenteTemp, auxiliar);
        }else if(x && signo && parentesis && !(ecuation[i] == '+' || ecuation[i] == '-')){
            strcat(exponenteTemp, ecuationAuxiliar);
        }else if(x && signo && !parentesis && !(ecuation[i] == '+' || ecuation[i] == '-')){
            strcat(exponenteTemp, ecuationAuxiliar);
        }else if(x && signo && parentesis && ecuation[i] == '-'){
            strcat(exponenteTemp, ecuationAuxiliar);
        }else if(!x && !signo && !parentesis){
            strcat(coeficienteTemp, ecuationAuxiliar);
            strcpy(exponenteTemp, auxiliar);
            x = 0;
            signo = 1;
        }else if(x && !signo && !parentesis && ecuation[i] == '+'){
            x = 0;
            signo = 1;
            if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "1");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
            strcpy(exponenteTemp, auxiliar);
        }else if(x && !signo && !parentesis && ecuation[i] == '-'){
            x = 0;
            signo = 1;
            if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "1");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
            strcpy(exponenteTemp, auxiliar);
            strcat(coeficienteTemp, ecuationAuxiliar);
        }else if(!x && signo && !parentesis && ecuation[i] == '+'){
            if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "0");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
            strcpy(exponenteTemp, auxiliar);

            if(strcmp(coeficienteTemp, auxiliar) == 0 || strcmp(coeficienteTemp, "-") == 0) {
                strcat(coeficienteTemp, "1");
            }
            coeficientes[nCoeficientes] = atoi(coeficienteTemp);
            nCoeficientes++;
            strcpy(coeficienteTemp, auxiliar);
        }else if (x && !signo && !parentesis){
            strcat(exponenteTemp, ecuationAuxiliar);
        }else if(x && !signo && parentesis){
            strcat(exponenteTemp, ecuationAuxiliar);
        }else{
            if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "0");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
            strcpy(exponenteTemp, auxiliar);

            if(strcmp(coeficienteTemp, auxiliar) == 0 || strcmp(coeficienteTemp, "-") == 0) {
                strcat(coeficienteTemp, "1");
            }
            coeficientes[nCoeficientes] = atoi(coeficienteTemp);
            nCoeficientes++;
            strcpy(coeficienteTemp, auxiliar);
            strcat(coeficienteTemp, ecuationAuxiliar);
        }
        i++;
    }// fin ciclo

    //Revisamos si se quedó un coeficiente o un exponente en las variables temporales.
    if(strcmp(coeficienteTemp, auxiliar) == 0 && strcmp(exponenteTemp, auxiliar) == 0 && !x){}
    else{
    if(strcmp(coeficienteTemp, auxiliar) == 0){
        if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "1");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;
    }else{
        if(strcmp(exponenteTemp, auxiliar) == 0 || strcmp(exponenteTemp, "-") == 0) {
                strcat(exponenteTemp, "0");
            }
            exponentes[nExponentes] = atoi(exponenteTemp);
            nExponentes++;

        if(strcmp(coeficienteTemp, auxiliar) == 0 || strcmp(coeficienteTemp, "-") == 0) {
                strcat(coeficienteTemp, "0");
            }
            coeficientes[nCoeficientes] = atoi(coeficienteTemp);
            nCoeficientes++;
    }
    }

    for(int i=0; i<nCoeficientes; i++){
        coeficienteExponente[0][i]=coeficientes[i];
        coeficienteExponente[1][i]=exponentes[i];
    }
    //Imprimimos la tabla de coeficientes y exponentes

    printf("\n  Coeficiente   Potencia\n");
    printf("+------------+------------+\n");

    int k = 0;
    //Ciclo para imprimir la tabla
    for (int j = 0; j < nCoeficientes && k < nExponentes; j++) {
        printf("|%-12d|%-12d|\n", coeficienteExponente[0][j], coeficienteExponente[1][j]);
        k++;
        printf("+------------+------------+\n");
    }
    printf("\nDigite el inicio del dominio: ");
    scanf("%i", &inicioRango);
    printf("\nDigite el final del dominio: ");
    scanf("%i", &finRango);
    printf("\nDigite el intervalo: ");
    scanf("%i", &saltos);
    printf("\n     X     |     Y     \n");
    printf("+----------+-----------+\n");

    //variable counter para hayar el valor de Y en cada momento de X
    int counter = inicioRango;
    //vaeiable nOperar para conocer la cantidad de operaciones que se realizaron
    int nOperar = 0;
    //Inicio ciclo de operaciones
    while(counter <= finRango){
        double newY = 0;
        for(int i = 0; i<nCoeficientes ; i++){
            if(exponentes[i] < 0 && counter == 0){
                newY = NAN;
                break;
            }else{
                newY = newY + (coeficienteExponente[0][i]*pow(counter, coeficienteExponente[1][i]));
            }
            
        }
        y[nOperar] = newY;
        newY = 0;
        nOperar++;
        counter = counter + saltos;
    }
    //Ciclo para imprimir la tabla con los valores de X y Y
    for(int i = 0; i < nOperar; i++){
        if(isnan(y[i])){
            printf("|%-10d|    IND    |\n", inicioRango+(saltos*i));
        }else{
            printf("|%-10d|%-11.2f|\n", inicioRango+(saltos*i), y[i]);
        }
        
        printf("+----------+-----------+\n");
    }
//Imprimimos dos saltos de linea
printf("\n\n");
//Varianle pantalla que tendrá el espacio para imprimir el gráfico
char pantalla[25][100];
//funcion memset para inicializar todos los elementos del array pantalla en ' '
memset(pantalla, ' ', sizeof(pantalla));
//variable yMax que guardará el valor máximo de Y
double yMax = y[0];
//Ciclo para hayar yMax
for(int i = 0; i < nOperar; i++){
    if(y[i] > yMax){
        yMax = y[i];
    }
}
//variable yMin que guarda el valor minimo de Y
double yMin = yMax;
//Ciclo para hayar el valor minimo de Y
for(int i = 0; i < nOperar; i++){
    if(y[i] < yMin){
        yMin = y[i];
    }
}

//variable pixelX que guarda el valor hipotetico de un pixel escalado en X
double pixelX = (abs(inicioRango-finRango) == 0) ? 100 :  100.0/abs(inicioRango-finRango);
//variable pixelY que guarda el valor hipotetico de un pixel escalado en Y
double pixelY = (fabs(yMin-yMax) == 0) ? 24 :  24.0/fabs(yMin-yMax);
//variable ejeX que guarda el valor hipotetico del eje x
double ejeX = -yMin * pixelY;
//variable ejeY que guarda el valor hipotetico del eje y
double ejeY = -inicioRango * pixelX;
//variable ejesX que convierte en entero y redondeado la variable ejeX y trabajarlos en el array
int ejesX = (int) round(ejeX);
//variable ejesY que convierte en entero y redondeado la variable ejeY y trabajarlos en el array
int ejesY = (int) round(ejeY);

//Condicional y ciclo para guardar en el array pantalla la posición del eje y y los valores donde irá los números del eje y
if(ejesY >= 0 && ejesY <= 99){
    for(int i = 0; i <25; i++){
    pantalla[i][ejesY] = 179;
    }
    //variable nY que guarda el valor a trabajar para imprimir los números del eje y
    double nY = abs(yMin-yMax)/5;
    for(int i = 0; i<6; i++){
        //variable placeY que guarda la posicion donde irá el elemento en el eje Y
        int placeY = (int) 24.0-round(pixelY*(yMin+nY*i)+ejeX);
        //variable cadena que guarda el numero a trabajar en string
        char cadena[12] = "";
        sprintf(cadena, "%.2f", yMin+nY*i);
        //variable longitud cadena que guarda la cantidad de caracteres de la variable cadena
        int longitudCadena = strlen(cadena);
        if(placeY != 24 - ejesX ){
        if(ejesY < 5){
            for(int j=0; j<longitudCadena; j++){
                pantalla[placeY][ejesY+5+j] = cadena[j];
            }
        }else if(ejesY > 95){
            for(int j=0; j<longitudCadena; j++){
                pantalla[placeY][ejesY-7+j] = cadena[j];
            }
        }else{
            for(int j=0; j<longitudCadena; j++){
                pantalla[placeY][ejesY-3+j] = cadena[j];
            }
        }
        }
    }
}

//Condicional y ciclo para guardar en el array pantalla la posición del eje x y los valores donde irá los números del eje x
if(ejesX >= 0 && ejesX <= 23){
    for(int i = 0; i <100; i++){
    pantalla[23-ejesX][i] = 196;
   }
for (int i = 0; i < nOperar; i++) {
    //variable cadena que guardará el número a convertir en string
    char cadena[12] = "";  
    //variable placeX que guardará el valor dentro del array en X
    int placeX = (int) round(pixelX * (inicioRango + saltos * i) + ejeY);
    
    if (placeX < 0) {
        placeX = 0;
    } else if (placeX > 99) {
        placeX = 99;
    }

    sprintf(cadena, "%d", inicioRango + (saltos * i));
    
    //Variable longCadena que guarda la longitud de la variale cadena
    int longCadena = strlen(cadena);

    for (int j = 0; j < longCadena && (placeX + j-2) < 100; j++) {
        if(i == nOperar-1){
            pantalla[24 - ejesX][placeX + j-2] = cadena[j];
        }else{
            pantalla[24 - ejesX][placeX + j] = cadena[j];
        }
    }
}
    }


//Ciclo que guarda en el array pantalla las posiciones donde irá la letra X en el gráfico
for(int i = 0; i<nOperar; i++){
    if(!isnan(y[i])){
    //variable placeX que guarda el valor de la posicion en X del elemento
    int placeX = (int) round(pixelX*(inicioRango+saltos*i)+ejeY);
    //variable placeY que guarda el valor de la posicion en Y del elemento
    int placeY = (int) 24.0-round(pixelY*y[i]+ejeX);
    if(placeX < 0){
        placeX = 0;
    }else if(placeX > 99){
        placeX = 99;
    }
    if(placeY < 0){
        placeY = 0;
    }else if(placeY > 23){
        placeY = 23;
    }
    pantalla[placeY][placeX] = 'X';
    }
    
}

//Ciclo para imprimir el gráfico
for(int i = 0; i<25; i++){
    for(int j = 0; j<100; j++){
        if(!pantalla[i][j]){
            printf(" ");
        }else{
            printf("%c", pantalla[i][j]);
        }
    }
    printf("\n");
}

    return 0;
}
