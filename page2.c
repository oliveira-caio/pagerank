#include<stdio.h>
#include<math.h>

int main(){

  double V[3460], xzero[230], x[230], xnew[230], norm = 0.0, m = 0.15, temp;
  int C[3460], L[3460], i, j, s=2, t=1, u=1, k=0, aux=0, rank[230];
  
  for(i=1; i<=230; i++){ // este laço percorrerá as "linhas" da matriz de ligação, mas faremos com que apenas as entradas diferente de 0 sejam armazenadas
    if(i == (t*(t+1))/2){ // tal condição verifica se a linha é correspondente a um cacique, pois a lógica de preenchimento da linha dele é diferente a lógica dos índios
      for(j=1; j<=230; j++){ // este laço percorrerá as "colunas" da matriz de ligação, mas faremos com que apenas as entradas diferente de 0 sejam armazenadas

	if(u*(u+1)/2 < j && j < (u+1)*(u+2)/2){ // esta condição verifica se estamos nas colunas correspondentes aos índios do cacique e, se estiver, atribuirá o valor que cada um deles tem no vetor V e armazenará a linha e a coluna correspondente nos vetores L e C
	  V[k] = 1.0/u;
	  C[k] = j;
	  L[k] = i;
	  k++;
	  continue;
	}
	
	if(j == (s*(s+1)/2)){ // esta condição verifica se estamos numa coluna que representa um cacique
	  if(i == j){ // esta condição verifica se é o próprio cacique, caso em que a entrada da matriz é 0 e nada deve ser feito
	    s++;
	    continue;
	  } else { // aqui estamos analisando o caso em que as colunas são os outros caciques e colocaremos os valores correspondentes em V, C e L
	    V[k] = 1.0/(20+s-1);
	    C[k] = j;
	    L[k] = i;
	    k++;
	    s++;
	    continue;
	  }
	}
      }
      s=1; // esta variável serve para verificarmos as colunas que representam caciques e atribuirmos os valores corretamente pra cada um deles
      u++; // esta variável controla a quantidade de índios que cada cacique terá, observe que estamos usando tal u no primeiro if
    } else { // entraremos aqui caso a linha corresponda a um índio
      for(j=1; j<=230; j++){ // este laço percorrerá as "colunas" da matriz de ligação, mas faremos com que apenas as entradas diferente de 0 sejam armazenadas
	
	if(i == j){ // verifica se a posição corresponde a si mesmo, caso em que nada deve ser feito
	  continue;
	}

	if(j == t*(t+1)/2){ // condição que verifica se estamos na coluna correspondente ao cacique e, caso estejamos, atribuímos os valores necessários
	  V[k] = 1.0/(20+t-1);
	  C[k] = j;
	  L[k] = i;
	  k++;
	  continue;
	}

	if(t*(t+1)/2 < j && j < (t+1)*(t+2)/2){ // condição que verifica se estamos nas colunas correspondentes aos outros índios conectados ao mesmo cacique e, caso estejamos, atribuímos os valores necessários
	  V[k] = 1.0/t;
	  C[k] = j;
	  L[k] = i;
	  k++;
	  continue;
	}
      }

      aux++; // este contador serve para verificarmos a quantidade de linhas percorridas que representam os índios de cada cacique
      if(aux == t){ // se já tivermos percorrido todos os índios correspondentes a cada cacique, na próxima vez que entrarmos nesse "else", teremos que aumentar a quantidade de linhas que poderemos percorrer em um, pois a tribo aumenta em um
	t++;
	aux = 0;
      }
    }
  }
  
  for(i=0; i<230; i++){ // laço em que atribuímos os valores iniciais nos vetores que utilizaremos para realizar as iterações até chegarmos no resultado
    xzero[i] = 1.0/230.0;
    x[i] = 1.0/230.0;
    xnew[i] = 0.0;
    rank[i] = i+1; // vetor em que controlaremos o posicionamento das páginas na hora de fazer o rank
  }

  for(i=0; i<3460; i++){ // este laço e o próximo servem para obtermos a primeira iteração do processo, ou seja, estamos criando o vetor x_1 e iremos compará-los dentro do while que vem em seguida
    xnew[L[i]-1] += V[i]*x[C[i]-1]; // aqui estamos utilizando a fórmula dada e tivemos que fazer L[i]-1 e C[i]-1, pois as colunas e as linhas foram armazenadas como se começassem do 1, e não do 0, que é como o C utiliza
  }
  
  for(i=0; i<230; i++){
    xnew[i] = (1-m)*xnew[i] + m*xzero[i];
  }

  k=0;
  
  while(k == 0){ // como gostaríamos que o método acabe apenas quando a norma seja suficientemente pequena, criei este suposto laço infinito para realizarmos tantas iterações quanto necessário, mas que sabemos que acaba por conta do Teorema de Perron-Frobenius
    
    for(i=0; i<230; i++){ // calculamos a norma da diferença dos vetores
      norm = norm + sqrt((x[i]-xnew[i])*(x[i]-xnew[i]));
    }

    if(norm < 0.00001){ // verificamos se a norma é pequena o suficiente, como desejado
      break;
    }
    
    for(i=0; i<230; i++){ // aqui nós fazemos com que x_l vire x_{l+1} e zeramos x_{l+1} para que em seguida consigamos criar o vetor x_{l+2}
      x[i] = xnew[i];
      xnew[i] = 0;
    }
    
    for(i=0; i<3460; i++){ // este laço e o próximo criam o vetor x_{l+2}, como dito no comentário acima
      xnew[L[i]-1] += V[i]*x[C[i]-1];
    }

    for(i=0; i<230; i++){
      xnew[i] = (1-m)*xnew[i] + m*xzero[i];
    }
    
    norm = 0;
  }

  for(i=0; i<229; i++){ // aqui apenas iremos ordenar as páginas com maior relevância usando Bubble sort
    for(j=i+1; j<230; j++){
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

  for(i=0; i<20; i++){ // laço para printar os caciques mais relevantes
    printf("A pagina %d, correspondente ao cacique %.0f, tem importancia %f \n", rank[i], (-1+sqrt(1+8*rank[i]))/2, xnew[i]);
  }

  j=-1;
  for(i=20; j<19; i=i+20-j){ // laço para printar os índios mais relevantes
    printf("A pagina %d, correspondente ao índio %.0f, tem importancia %f \n", rank[i], 19.0-j, xnew[i]);
    j++;
  }

  return 0;
}
