 #include <HardwareSerial.h>
 //#include "dataset.h"
#include "metodosKNN.h"
#include <math.h>
//--------------------Calculo distancia euclidiana entre 2 puntos--------------
double distanciaEuclidiana(double pt1[], double pt2[]){
  int i;
  double suma=0;
  for(i=0; i<CO;i++){
    suma= pow(pt1[i] - pt2[i],2)+suma;
  }
  return sqrt(suma);
}

//---------------Calculo de distancia Euclidiana entre un punto y la base de datos
void todasDistEuclid(double pt1[],double aux[], double atributos[][CO]){
  int i=0;
  double pt2[]= {0,0};

  for(i=0;i<FI;i++){
    pt2[0] = atributos[i][0]; 
    pt2[1] =atributos[i][1];

    aux[i] = distanciaEuclidiana(pt1,pt2);
  }
}

//----ORDENAMIENTO DE LAS DISTANCIAS DE MENOR A MAYOR
void ordena(double datos[], int clases[],int clasesNo[]){
  int i=1, j=1,f=1, temp[2];
  //crear una copia de las clases originales
  for(i=0;i<FI;i++){
    clases[i]=clasesNo[i];
  }
  //ordenar
  for(i=1;(i<=FI)&&f;i++){
    f=0;
    for(j=0;j<(FI-1);j++){
      if(datos[j+1] < datos[j]){ //orden descendente >, ascendente <
        temp[0] = datos[j]; temp[1] =clases[j];
        datos[j]= datos[j+1]; clases[j] = clases [j+1];
        datos[j+1]=temp[0]; clases[j+1] = temp[1];
        f=1;
        
      }
    }
  }
}
//-------------------EXTRAER LOS N PRIMEROS------------------------------------
void extraeKPrimeros(double datos[], double kPrimeros[], int clases[], int kClases[], int k){
  for(int i=0; i<k;i++){
    kPrimeros[i]= datos[i];
    kClases[i] = clases[i];
  }
}
//-----------------CALCULO DE LA MODA: CLASE MAS FRECUENTE---------------------
int claseMasFrecuente(int clases[],int k){
  int cont=0, cont2=0, pos =0, num=0, i=0;
  int frec[k], mayor=0, posmayor=0, aux[k];
  //inicializar el contador de frecuencias
  for(i=0;i<k;i++){
    frec[k]=0; 
  }
  // comprobar las repeticiones de cada numero
  for(cont=0; cont<k;cont++){
    num= clases[cont];
    pos=cont;
    for(cont2=0;cont2<k;cont2++){
      if(clases[cont2] ==num){
        aux[pos]++;
      }
    } 
  }
  mayor=aux[0];
  posmayor=0;

  for(cont=0; cont<k;cont++){
    if(aux[cont] > mayor){
      posmayor=cont;
      mayor=aux[cont];
    }
  }
  return clases[posmayor]; 
}

//------------CALCULA LA CLASE CONJUNTO DE ATRIBUTOS USANDO KNN----------------
int clasificaKNN(double datos[][CO],int clasesNum[], double dato[], int k){
  double aux2[FI], kPrimeros[k];
  int clases[FI];
  int kClases[k];

  todasDistEuclid(dato,aux2,datos);
  ordena(aux2, clases, clasesNum);
  extraeKPrimeros(aux2, kPrimeros, clases, kClases, k);

  //calculo de la moda
   int cont=0, cont2=0, pos =0, num=0, i=0;
  int frec[k], mayor=0, posmayor=0, aux[k];
  //inicializar el contador de frecuencias
  
  for(i=0;i<k;i++){
    frec[k]=0; 
  }
  // comprobar las repeticiones de cada numero
  for(cont=0; cont<k;cont++){
    num= clases[cont];
    pos=cont;
    for(cont2=0;cont2<k;cont2++){
      if(clases[cont2] ==num){
        aux[pos]++;
      }
    } 
  }
  mayor=aux[0];
  posmayor=0;

  for(cont=0; cont<k;cont++){
    if(aux[cont] > mayor){
      posmayor=cont;
      mayor=aux[cont];
    }
  }
  return clases[posmayor]; 
}
