#include<stdio.h>
#include<math.h>

int main(){

  double A[8][8], xzero[8], x[8], xnew[8], m = 0.15, temp;
  int i, j, k = 0, rank[8], aux;
  
  for(i=0; i<8; i++){ // neste laço iremos criar os vetores iniciais e preencheremos a matriz de ligação toda com 0
    for(j=0; j<8; j++){
      A[i][j] = 0;
    }
    xzero[i] = 0.125;
    x[i] = 0.125;
    xnew[i] = 0;
    rank[i] = i+1; // aqui criamos um vetor para conseguirmos rankear as páginas no final
  }

  // como a matriz é pequena, os valores foram colocados na mão
  A[0][7] = 0.5;
  A[1][0] = 0.5;
  A[2][0] = 0.5;
  A[2][1] = 0.5;
  A[2][7] = 0.5;
  A[3][1] = 0.5;
  A[4][3] = 0.5;
  A[5][2] = 0.5;
  A[5][3] = 0.5;
  A[5][4] = 1.0;
  A[6][2] = 0.5;
  A[6][5] = 1.0;
  A[7][6] = 1.0;

  for(i=0; i<8; i++){ // este laço serve para obtermos a primeira iteração do processo, ou seja, estamos criando o vetor x_1 e iremos compará-los dentro do while que vem em seguida
    for(j=0; j<8; j++){
      xnew[i] += A[i][j]*x[j];
    }
    xnew[i] = (1-m)*xnew[i] + m*xzero[i];
  }

  
  while(k == 0){ // como gostaríamos que o método acabe apenas quando a norma seja suficientemente pequena, criei este suposto laço infinito para realizarmos tantas iterações quanto necessário, mas que sabemos que acaba por conta do Teorema de Perron-Frobenius

    if(sqrt((x[0]-xnew[0])*(x[0]-xnew[0]))
       + sqrt((x[1]-xnew[1])*(x[1]-xnew[1]))
       + sqrt((x[2]-xnew[2])*(x[2]-xnew[2]))
       + sqrt((x[3]-xnew[3])*(x[3]-xnew[3]))
       + sqrt((x[4]-xnew[4])*(x[4]-xnew[4]))
       + sqrt((x[5]-xnew[5])*(x[5]-xnew[5]))
       + sqrt((x[6]-xnew[6])*(x[6]-xnew[6]))
       + sqrt((x[7]-xnew[7])*(x[7]-xnew[7])) < 0.00001){ // verificamos se a norma da diferença entre x_l e x_{l+1} é pequena o suficiente, como desejado
      break;
    }
   
    for(i=0; i<8; i++){ // aqui nós fazemos com que x_l vire x_{l+1} e zeramos x_{l+1} para que em seguida consigamos criar o vetor x_{l+2}
      x[i] = xnew[i];
      xnew[i] = 0;
    }
    
    for(i=0; i<8; i++){ // este laço cria o vetor x_{l+2}, como dito no comentário acima
      for(j=0; j<8; j++){
	xnew[i] += A[i][j]*x[j];
      }
      xnew[i] = (1-m)*xnew[i] + m*xzero[i];
    }
  }

  for(i=0; i<7; i++){ // aqui apenas iremos ordenar as páginas com maior relevância usando Bubble sort
    for(j=i+1; j<8; j++){
      if(xnew[j] > xnew[i]){
	temp = xnew[i];
	xnew[i] = xnew[j];
	xnew[j] = temp;
	aux = rank[i];
	rank[i] = rank[j];
	rank[j] = aux;
      }
    }
  }

  for(i=0; i<8; i++){ // laço usado para printar o ranking com as paginas mais relevantes
    printf("A pagina %d tem importancia %f \n", rank[i], xnew[i]);
  }

  return 0;
}
