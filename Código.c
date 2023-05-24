#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define M 10
#define N 10

int show_menu(int option){

  printf("\n\nGerenciamento de Conjuntos\n\n\n");
  printf("Menu\n\n");
  printf("1 - Criar um novo conjunto vazio\n2 - Inserir dados em um conjunto\n3 - Remover um conjunto\n4 - Fazer a uniao entre dois conjuntos\n5 - Fazer a interseccao entre dois conjuntos\n6 - Mostrar um conjunto\n7 - Mostrar todos os conjuntos\n8 - Fazer busca por um valor\n9 - Sair do programa\n");
  printf("\nEscolha uma opção: ");
  scanf("%i",&option);
  return option;
}

void insert_data_conj(int a, int conj[][N], int cont) {
  if (a < 0 || a >= cont) {
    printf("\nConjunto inexistente!\n");
    return;
  }
  
  printf("\nDigite o(s) número(s) em sequência. Digite 0 quando acabar: ");
  
  int i, j, b, found;
  int num_values = 0; // Contador para valores já inseridos
  
  for (i = 0; i < N; i++) {
    scanf("%d", &b);
    
    if (b == 0) {
      break;
    }
    
    num_values++;
    
    if (num_values > N) {
      printf("\nErro: quantidade de valores excede o tamanho máximo do conjunto.\n");
      // Descarta os valores restantes sem adicioná-los ao conjunto
      while (b != 0) {
        scanf("%d", &b);
      }
      break;
    }
    
    found = 0;
    
    //Verifica se o valor já está no conjunto
    for (j = 0; j < N; j++) {
      if (conj[a][j] == b) {
        found = 1;
        printf("\nErro: valor %d já inserido no conjunto. Não sendo possível adicioná-lo novamente.\n", b);
        break;
      }
      
      if (conj[a][j] == 0) {//Adiciona o valor e retorna mensagem de sucesso se o valor digitado não estava no conjunto
        conj[a][j] = b;
        printf("\nValor %d inserido no conjunto.\n", b);
        break;
      }
    }
    
    if (!found && j == N) {
      printf("\nErro: conjunto cheio. Valor %i não foi adicionado.\n",b);
      break;
    }
  }
}
void delete_conj(int conj[M][N], int* cont){
 int i, j, a;

  printf("\nDigite o indice do conjunto que deseja remover (0 a %d): ", *cont-1);
  scanf("%d", &a);

  if (a < 0 || a >= *cont) { 
    printf("\nIndice invalido!\n");
  }

  // Zera a linha do conjunto a ser removido
  for (j = 0; j < N; j++) {
    conj[a][j] = 0;
  }

  // Move os conjuntos abaixo do conjunto removido para cima
  for (i = a; i < M-1; i++){
    for (j = 0; j < N; j++){
      conj[i][j] = conj[i+1][j];
    }
  }
  // Zera a última linha
  for (j = 0; j < N; j++) {
    conj[M-1][j] = 0;
  }
  (*cont)--; 

  printf("\nConjunto removido com sucesso!\n");
}
void unity_conj(int A, int B, int mat[][N], int* cont) {
  int tamA = 0, tamB = 0;
    
    // Encontra o tamanho de cada conjunto
    for (int i = 0; i < N; i++) {
        if (mat[A][i] != 0) {
            tamA++;
        }
        if (mat[B][i] != 0) {
            tamB++;
        }
    }
    
    // Verifica se há espaço na matriz para adicionar a união
    if (*cont >= M) {
        printf("\nNão há espaço disponível na matriz!\n");
        return;
    }
    
    // Verifica se algum dos conjuntos é nulo
    if (tamA == 0 || tamB == 0) {
        printf("\nUm dos conjuntos é nulo!\n");
        return;
    }
    
    // Cria um vetor para armazenar a união
    int temp[tamA+tamB];
    int index = 0;
    
    // Adiciona os valores do menor conjunto
    for (int i = 0; i < N; i++) {
        if (mat[A][i] != 0) {
            temp[index] = mat[A][i];
            index++;
        }
    }
        
    // Adiciona os valores do maior conjunto, verificando se já foram adicionados
    for (int i = 0; i < N; i++) {
        if (mat[B][i] != 0) {
            int j;
            for (j = 0; j < index; j++) {
                if (temp[j] == mat[B][i]) {
                    break;
                }
            }
            if (j == index) {
                temp[index] = mat[B][i];
                index++;
            }
        }
    }
    
    // Verifica se há espaço suficiente na linha da matriz para a união
    if (index > N) {
        printf("\nNão há espaço suficiente na linha da matriz!\n");
        return;
    }
    
    // Adiciona a união na linha da matriz e incrementa o contador
    for (int i = 0; i < index; i++) {
        mat[*cont][i] = temp[i]; 
    }
  printf("\nUnião dos conjuntos %i e %i realizada com sucesso.", A,B);
    (*cont)++;
}
void interseccao_conj(int A, int B, int conj[][N], int* cont){
  int tamA = 0, tamB = 0; // inicializa as variáveis tamA e tamB

  // Encontra o tamanho de cada conjunto
  for (int i = 0; i < N; i++) {
    if (conj[A][i] != 0) {
      tamA++;
    }
    if (conj[B][i] != 0) {
      tamB++;
    }
  }

  if (tamA == 0 || tamB == 0) { // verifica se algum dos conjuntos é vazio
    printf("\nUm dos conjuntos é vazio,não sendo possivel realizar a intersecção!\n");
    return;
  }

  // Cria um vetor temporário para armazenar a interseção
  int temp[tamA+tamB];
  int index = 0;

  // Encontra os valores em comum entre os conjuntos
    for (int i = 0; i < N; i++) {
        if (conj[A][i] != 0) {
            for (int j = 0; j < N; j++) {
                if (conj[B][j] != 0 && conj[A][i] == conj[B][j]) {
                    temp[index] = conj[A][i];
                    index++;
                    break;
                }
            }
        }
    }

  if (index == 0) { // verifica se não há valores em comum
    printf("\nNão há valores em comum entre os conjuntos!\n");
    return;
  }

  // Verifica se há espaço suficiente na linha da matriz para a interseção
  if (index > N) {
    printf("\nNão há espaço suficiente na linha da matriz!\n");
    return;
  }

  // Adiciona a interseção na linha da matriz e incrementa o contador
  for (int i = 0; i < index; i++) {
    conj[*cont][i] = temp[i];
  }
  printf("\nIntersecção dos conjuntos %i e %i realizada com sucesso.\n", A, B);
  (*cont)++;
}
void search_value(int a,int conj[M][N],int cont){

   if (cont == 0) {
      printf("\nNão há conjuntos criados");
    return;
    }
 int i,j,found=0;
  printf("\nConjuntos que contem o valor %i\n\n", a);
    for (i = 0; i <= cont; i++) {
      for (j = 0; conj[i][j] != 0; j++) {
          if (conj[i][j] == a) {
          	found=1;
            printf("Conjunto %i\n\n", i);
            break;
          }
      }
    }if(found!=1){
    	printf("Não há conjunto com o valor %i",a);
	}
    
}
void show_conj_unit(int conj[][N],int a,int cont){
  int j;
      for(j=0; conj[a][j] != 0; j++){
        if(a > M-1 || cont == 0 || a >= cont){
          printf("\nConjunto não encontrado, favor verificar se foi criado");
          break;
        }
        if(conj[a][j] == 0  && a < cont){
          printf("\nCojunto vazio");
          break;
        }
        printf("%i\t",conj[a][j]);
    }
}
void show_conj_comp(int conj[M][N],int *cont){
  int i,j;
  printf("\nTemos %i conjuntos:\n",*cont);
  
  for(i = 0; i < *cont; i++){
    if(conj[i][0] != 0){
      printf("Conjunto %i = ",i);
      for(j = 1; conj[i][j-1] != 0; j++){
          printf("%i ",conj[i][j-1]);  
        }printf("\n"); 
    }else{
      printf("Conjunto %i = vazio",i);
      }
  }
}
int main() {
  setlocale(LC_ALL, "Portuguese");
  int option=0,conj[M][N],i=0,j=0,a=0,cont=0,b=0,c=0,z;
  for(i = 0; i < M; i++){
    for(j = 0; j < N; j++){
      conj[i][j]=0;
    }
  }

  while(option != 9){
    option=show_menu(option);
    switch(option){
      case 1:
          if(cont <= M){
          printf("\nConjunto criado com sucesso");
            cont++;
          }
          else{
            printf("\nConjunto não criado. Capacidade de conjuntos possiveis de criação já atendida, exclua outro conjunto para criar um novo");
          }
        break;
      case 2:
        printf("Digite o numero do conjunto que deseja inserir os dados: ");
        scanf("%i",&a);
        insert_data_conj(a,conj,cont);
        while ((z = getchar()) != '\n' && z != EOF) {}//Limpar buffer de entrada para não passar valores digitados alem do limite
        break;
      case 3:
          delete_conj(conj,&cont);
          while ((z = getchar()) != '\n' && z != EOF) {}
        break;
      case 4:
        printf("Digite o indice dos conjuntos que deseja fazer a união: ");
        scanf("%i %i",&b,&c);
        unity_conj(b,c,conj,&cont);
        while ((z = getchar()) != '\n' && z != EOF) {}
        break;
      case 5:
        printf("Digite o indice dos conjuntos que deseja fazer a intersecção: ");
        scanf("%i %i",&b,&c);
        interseccao_conj(b,c,conj,&cont);
        while ((z = getchar()) != '\n' && z != EOF) {}
        break;
      case 6:
          printf("\nDigite o numero do conjunto que deseja ser mostrado: ");
          scanf("%i",&a);
          show_conj_unit(conj,a,cont);
          while ((z = getchar()) != '\n' && z != EOF) {}
          break;
      case 7:
        show_conj_comp(conj,&cont);
        while ((z = getchar()) != '\n' && z != EOF) {}
        break;
      case 8:
         printf("Digite o numero que deseja encontrar: ");
        scanf("%i",&a);
        search_value(a,conj,cont);
        while ((z = getchar()) != '\n' && z != EOF) {}
        break;
      case 9:
        printf("Programa finalizado com sucesso.Agradecemos por utilizar nossos serviços!\n");
        while ((z = getchar()) != '\n' && z != EOF) {}
        break;
      default:
        printf("\nErro: Digite um numero que esteja no menu");
  }
  }
}
