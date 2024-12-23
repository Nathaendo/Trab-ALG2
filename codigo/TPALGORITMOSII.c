#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preenche_vetor(int vetor[]){
    for(int i = 1;i <= 1024;i++)          //VETOR[0] RESERVADO PARA O SENTINELA
        vetor[i] = rand()%2049;          //GERA NUMEROS ENTRE 0 E 2048
}

void selectionsort(int vetor[], int *comparacoes,int *trocas){
    int mnr_idx;
    int aux;
    for(int i = 1; i < 1024;i++){                //VAI DO PRIMEIRO ATÉ O PENULTIMO POIS O ULTIMO
        mnr_idx = i;                             //JA ESTARÁ ORDENADO QUANDO CHEGAR AO PENULTIMO
        for(int j = i+1;j<=1024;j++){
            (*comparacoes)++;                  
            if(vetor[j] < vetor[mnr_idx])
                mnr_idx = j;
        }
        if(mnr_idx != i)                        //NÃO CONTABILIZA A TROCA SE FOR
            (*trocas)++;                        //TROCADO O ELEMENTO POR ELE MESMO
        aux = vetor[i];
        vetor[i] = vetor[mnr_idx];
        vetor[mnr_idx] = aux;
    }
}
void shellsedgewick(int vetor[],int *comparacoes, int *trocas){
    int i,j,aux;
    int h = 1;
    while (h < 1024/ 3) {
        h = 3*h + 1;          // metodo de Sedgewick
    }                           //atual = triplo do proximo + 1
    while(h>0){                               //testa ate o espaçamento ser = 0
        for(i=h;i <= 1024;i++){
            aux= vetor[i];
            j = i;
            while(j>h-1 && aux <= vetor[j-h]){
                (*comparacoes)++;
                (*trocas)++;
                vetor[j] = vetor[j-h];
                j = j-h;
            }
            (*comparacoes)++;
            vetor[j] = aux;
        }
        h=h/3;
    }
}
void shellsorthibbard(int vetor[],int *comparacoes, int *trocas){
    int i,j,aux;
    int h = 1;
    while (h < 1024/ 3) {
        h = 2*h + 1;          // metodo de hibbard
    }                           //atual = dobro do proximo + 1
    while(h>0){                               //testa ate o espaçamento ser = 0
        for(i=h;i <= 1024;i++){
            aux= vetor[i];
            j = i;
            while(j>h-1 && aux <= vetor[j-h]){
                (*comparacoes)++;
                (*trocas)++;
                vetor[j] = vetor[j-h];
                j = j-h;
            }
            (*comparacoes)++;
            vetor[j] = aux;
        }
        h=h/2;
    }
}
int particionar_media(int vetor[],int inicio,int fim, int*comp,int *trocas){
    int aux;
    int pivo = (vetor[inicio]+vetor[fim]+vetor[(inicio+fim)/2])/3;; //define pivô como uma media de três valores, esse valor não pertence
    while(inicio<fim){     //                                       // necessariamente ao vetor, é apenas para comparar e separar o vetor em dois.
        while(inicio < fim && vetor[inicio]<=pivo){ //procura por elemento maior que opivo no começo
            (*comp)++;
            inicio++;
        }
        while(inicio<fim && vetor[fim] > pivo){
            (*comp)++;
            fim--;
        }
        aux = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = aux;
        (*trocas)++;
    }
    return inicio;   //posição do "meio" da partição
}
void quicksort_media(int vetor[],int ini,int fim,int *comp,int *trocas){
    if(ini < fim){
        int posmeio = particionar_media(vetor,ini,fim,comp,trocas);
        quicksort_media(vetor,ini,posmeio-1,comp,trocas); 
        quicksort_media(vetor,posmeio,fim,comp,trocas);
    }
}
int particionar_ult(int vetor[],int inicio,int fim, int*comp,int *trocas){
    int aux,idx_pivo;
    int pivo = vetor[fim];      //pivo igual ultimo elemento
    idx_pivo = inicio; 
    for(int i = inicio;i<fim;i++){
        (*comp)++;
        if(vetor[i]<=pivo){
            (*trocas)++;
            aux = vetor[i];
            vetor[i] = vetor[idx_pivo];
            vetor[idx_pivo] = aux;
            idx_pivo++;
        }
    }
    (*trocas)++;
    vetor[fim] = vetor[idx_pivo];       //alocar o pivo para a posilão correta
    vetor[idx_pivo] = pivo;
    return idx_pivo;   //posição do pivo
}
void quicksort_ult(int vetor[],int ini,int fim,int *comp,int *trocas){
    if(ini < fim){
        int pospivo = particionar_ult(vetor,ini,fim,comp,trocas);
        quicksort_ult(vetor,ini,pospivo-1,comp,trocas); 
        quicksort_ult(vetor,pospivo+1,fim,comp,trocas);
    }
}

int buscaseq(int vetor[],int *comp,int chave){   //retorna o idx da chave caso exista e 0 caso não
    for(int i = 1024; i > 0;i--){
        (*comp)++;
        if(vetor[i] == chave)
            return i;
    }
    return 0;
}

int busca_bin(int vetor[],int ini,int fim,int *comp,int chave){
    if(ini>fim)
        return 0;                                 //não possui
    int meio = (ini+fim)/2;
    (*comp)++;
    if(vetor[meio] == chave)                              //achou
        return meio;
    if(vetor[meio] > chave){
        return busca_bin(vetor,ini,meio-1,comp,chave);   //pode estar na esq do vetor
    }
    return busca_bin(vetor,meio+1,fim,comp,chave);            //pode estar na dir do vetor
}
double raiz(double num){
    if(num == 0)
        return 0;
    double erro = 0.0001;    //precisão da aproximação;
    double estimativa = num;
    while(1){                   //metódo de newton
        double nova_estimativa = 0.5*(estimativa + num/estimativa);
        if(estimativa - nova_estimativa < erro){
            break;
        }
        estimativa = nova_estimativa;
    }
    return estimativa;
}

double desvio(int media,int elementos[]){
    double soma = 0;
    for(int i = 0;i<1000;i++){
        soma += (elementos[i]-media)*(elementos[i]-media);
    }
    soma = soma/1000;
    return raiz(soma);
}
int soma(int vetor[]){
    int soma = 0;
    for(int i = 0;i<1000;i++){
        soma+= vetor[i];
    }
    return soma;
}
void resultados(int comps[],int trocas[]){
    int compstotal,trocastotal,mediacomp,mediatrocas;
    double desviocomp,desviotrocas;
    compstotal = soma(comps);
    printf("Comparação Total: %d\n",compstotal);
    mediacomp = compstotal/1000;
    printf("Comparação Média: %d\n",mediacomp);
    desviocomp = desvio(mediacomp,comps);
    printf("Comparação Desvio: %f\n",desviocomp);
    trocastotal = soma(trocas);
    printf("Trocas Total: %d\n",trocastotal);
    mediatrocas = trocastotal/1000;
    printf("Trocas Média: %d\n",mediatrocas);
    desviotrocas = desvio(mediatrocas,trocas);
    printf("Trocas Desvio: %f\n",desviotrocas);

}
int escolhachave(){
    int vdd = 1;
    while(vdd){
        printf("Chave Aleatoria: 1\n");
        printf("Escolha a Chave: 2\n");
        int chave;
        scanf("%d",&chave);
        switch (chave){
            case 1:
                chave = rand()%2049;
                vdd = 0;
                break;
            case 2:
                while(1){
                    printf("DIGITE A CHAVE[0,2048]: ");
                    scanf("%d",&chave);
                    vdd = 0;
                    if(chave>-1 && chave<2049)
                        break;
                    printf("Chave Inválida\n");
                }
                break;
            default:
                printf("NUM INVALIDO\n");
        }
    }
}
void imprime_vetor(int vetor[]){  //imprime primeiros 100 elementos;
    printf("100 primeiros elementos da lista:");
    for(int i = 1; i <= 100;i++){
        if(i==1)
            printf("[%d", vetor[i]);
        else if(i == 100)
            printf(" %d]", vetor[i]);
        else
            printf(" %d",vetor[i]);
    }
    printf("\n");
}
void testemil(){
    int vetor[1025];   //0 reservado para sentinela;
    int trocas[1000];
    int comps[1000];
    int entrada,chave,dntcare,verdade = 1;
    while(verdade){
        printf("\nMil Testes \n");
        printf("Selection Sort: 1\n");
        printf("Shell Sort Sedgewick: 2\n");
        printf("Shell Sort Hibbard: 3\n");
        printf("Quick Sort Média: 4\n");
        printf("Quick Sort Último: 5\n");
        printf("Busca Sequencial: 6\n");
        printf("Busca Binária: 7\n");
        printf("TESTAR TODOS: 8\n");
        printf("Sair: Qualquer número diferente\n");
        printf("SELECIONE O TESTE: ");
        scanf("%d",&entrada);
        switch (entrada){
            case 1:
            printf("\nSelection Sort\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    selectionsort(vetor,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                break;
            case 2:
                printf("\nShell Sort Sedgewick\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    shellsedgewick(vetor,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                break;
            case 3:
                printf("\nShell Sort Hibbard\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    shellsorthibbard(vetor,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                break;
            case 4:
                printf("\nQuick Sort Média\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    quicksort_media(vetor,1,1024,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                break;
            case 5:
                printf("\nQuick Sort Último\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    quicksort_ult(vetor,1,1024,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                break;
            case 6:
                chave = escolhachave();
                printf("\nBusca Sequencial\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    buscaseq(vetor,&comps[i],chave);
                }
                resultados(comps,trocas);
                break;
            case 7:
                chave = escolhachave();
                printf("\nBusca Binária\n");                       //chave aleatoria ou escolhida;
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    quicksort_media(vetor,1,1024,&dntcare,&dntcare);  //necessário ordenar o vetor;
                    busca_bin(vetor,1,1024,&comps[i],chave);
                }
                resultados(comps,trocas);
                break;
            case 8:
                chave = escolhachave();
                printf("\nSelection Sort\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    selectionsort(vetor,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                printf("\nShell Sort Sedgewick\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    shellsedgewick(vetor,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                printf("\nShell Sort Hibbard\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    shellsorthibbard(vetor,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                printf("\nQuick Sort Média\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    quicksort_media(vetor,1,1024,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                printf("\nQuick Sort Último\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    quicksort_ult(vetor,1,1024,&comps[i],&trocas[i]);
                }
                resultados(comps,trocas);
                printf("\nBusca Sequencial\n");
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    buscaseq(vetor,&comps[i],chave);
                }
                resultados(comps,trocas);
                printf("\nBusca Binária\n");                       //chave aleatoria ou escolhida;
                for(int i = 0;i< 1000;i++){
                    preenche_vetor(vetor);
                    comps[i] = trocas[i] = 0;
                    quicksort_media(vetor,1,1024,&dntcare,&dntcare);  //necessário ordenar o vetor;
                    busca_bin(vetor,1,1024,&comps[i],chave);
                }
                resultados(comps,trocas);
                break;
            default:
                verdade = 0;
            }
            if(verdade){
                printf("Quer continuar no mil testes?\nSIM: 1\nNAO: 0\n");
                scanf("%d", &verdade);
        }
    }
}
void menutestesimples(){
    int vetor[1025];
    int entrada,chave,dntcare,resulbusca,comp,troca,verdade = 1;
    while(verdade){
        printf("\nTeste Simples \n");
        printf("Selection Sort: 1\n");
        printf("Shell Sort Sedgewick: 2\n");
        printf("Shell Sort Hibbard: 3\n");
        printf("Quick Sort Média: 4\n");
        printf("Quick Sort Último: 5\n");
        printf("Busca Sequencial: 6\n");
        printf("Busca Binária: 7\n");
        printf("Sair: Qualquer número diferente\n");
        printf("SELECIONE O TESTE: ");
        scanf("%d",&entrada);
        switch (entrada){
            case 1:
                comp = troca = 0;
                preenche_vetor(vetor);
                printf("\nSelection Sort\n");
                printf("Primeiros 100 elementos desordenados:\n");
                imprime_vetor(vetor);
                selectionsort(vetor,&comp,&troca);
                printf("Primeiros 100 elementos ordenados:\n");
                imprime_vetor(vetor);
                printf("Comparações: %d\n",comp);
                printf("Trocas: %d\n",troca);
                break;
            case 2:
                comp = troca = 0;
                preenche_vetor(vetor);
                printf("\nShell Sort Sedgewick\n");
                printf("Primeiros 100 elementos desordenados:\n");
                imprime_vetor(vetor);
                shellsedgewick(vetor,&comp,&troca);
                printf("Primeiros 100 elementos ordenados:\n");
                imprime_vetor(vetor);
                printf("Comparações: %d\n",comp);
                printf("Trocas: %d\n",troca);
                break;
            case 3:
                comp = troca = 0;
                preenche_vetor(vetor);
                printf("\nShell Sort Hibbard\n");
                printf("Primeiros 100 elementos desordenados:\n");
                imprime_vetor(vetor);
                shellsorthibbard(vetor,&comp,&troca);
                printf("Primeiros 100 elementos ordenados:\n");
                imprime_vetor(vetor);
                printf("Comparações: %d\n",comp);
                printf("Trocas: %d\n",troca);
                break;
            case 4:
                comp = troca = 0;
                preenche_vetor(vetor);
                printf("\nQuick Sort Média\n");
                printf("Primeiros 100 elementos desordenados:\n");
                imprime_vetor(vetor);
                quicksort_media(vetor,1,1024,&comp,&troca);
                printf("Primeiros 100 elementos ordenados:\n");
                imprime_vetor(vetor);
                printf("Comparações: %d\n",comp);
                printf("Trocas: %d\n",troca);
                break;
            case 5:
                comp = troca = 0;
                preenche_vetor(vetor);
                printf("\nQuick Sort Último\n");
                printf("Primeiros 100 elementos desordenados:\n");
                imprime_vetor(vetor);
                quicksort_ult(vetor,1,1024,&comp,&troca);
                printf("Primeiros 100 elementos ordenados:\n");
                imprime_vetor(vetor);
                printf("Comparações: %d\n",comp);
                printf("Trocas: %d\n",troca);
                break;
            case 6:
                comp = 0;
                printf("\nBusca Sequencial\n");
                preenche_vetor(vetor);
                chave = escolhachave();
                printf("CHAVE: %d\n",chave);
                resulbusca = buscaseq(vetor,&comp,chave);
                if(resulbusca)
                    printf("Está no índex: %d\n",resulbusca);
                else
                    printf("Chave não está no vetor\n");
                printf("Comparações: %d\n",comp);
                break;
            case 7:
                comp = 0;
                printf("\nBusca Binária\n");
                preenche_vetor(vetor);
                chave = escolhachave();
                printf("CHAVE: %d\n",chave);
                quicksort_media(vetor,1,1024,&dntcare,&dntcare);
                resulbusca = busca_bin(vetor,1,1024,&comp,chave);
                if(resulbusca)
                    printf("Está no índex: %d\n",resulbusca);
                else
                    printf("Chave não está no vetor\n");
                printf("Comparações: %d\n",comp);
                break;
            default:
                verdade = 0;
            }
        if(verdade){
                printf("Quer continuar no teste simples?\nSIM: 1\nNAO: 0\n");
                scanf("%d", &verdade);
        }        

    }
}
void menu_principal(){
int entrada,verdade = 1;
while(verdade){
    printf("\nTPALGORITMOSII");
    printf("\nMenu Principal \n");
    printf("Teste Simples: 1\n");
    printf("Testar mil vezes: 2\n");
    printf("Encerrar: Qualquer outro número\n");
    scanf("%d",&entrada);
    switch (entrada){
        case 1:
            menutestesimples();
            break;
        case 2:
            testemil();
            break;
        default:
            verdade = 0;
    }
    }
}
int main(){
    srand(time(NULL));
    menu_principal();
    return 0;
}
