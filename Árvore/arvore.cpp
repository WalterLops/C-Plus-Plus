#include <iostream>

using namespace std;

struct No
{
    int info;
    No *esquerda;
    No *direita;
};

struct Arvore {

    No *raiz;

    void criar ();
    No *Inserir (No* no_atual, int info);
    void Pre_Ordem (No *no_atual);
    void Em_Ordem (No *no_atual);
    void Pos_Ordem (No *no_atual);
    bool Pesquisar (No *no_atual, int info);
    No *Excluir (No *no_atual, int info);
    int Altura (No *no_atual);
    No *Del_Arvore(No *no_atual);

};

//Criar a árvore
void Arvore :: criar (){
    
    raiz = NULL;
}

//______________________________Inserir na arvore______________________________________
No * Arvore ::Inserir (No* no_atual, int info){
    //Arvore vazia
    if (no_atual == NULL){        
        no_atual = new No;
        no_atual -> info = info;
        no_atual -> esquerda = NULL;
        no_atual -> direita = NULL;
    }
    //info menor que o pai
    else if (no_atual ->info > info){
        no_atual -> esquerda = Inserir(no_atual -> esquerda, info);
    }
    //info maior que o pai
    else if (no_atual -> info < info){
        no_atual->direita = Inserir (no_atual->direita, info);
    }
    return no_atual;
}

//______________________________Impressão______________________________________

//Percurso em pré ordem
void Arvore :: Pre_Ordem (No *no_atual){
    //enquanto no_atual for diferente de NULL
    if (no_atual != NULL){
        cout <<no_atual -> info<<" ";
        Pre_Ordem (no_atual -> esquerda);
        Pre_Ordem (no_atual -> direita);
    }
}

//Percurso em ordem
void Arvore :: Em_Ordem (No *no_atual){
    //enquanto no_atual for diferente de NULL continuará imprimindo
    if (no_atual != NULL){
        Em_Ordem (no_atual -> esquerda);
        cout <<no_atual -> info<<" ";
        Em_Ordem (no_atual -> direita);
    }

}

//Percurso Pós Ordem
void Arvore :: Pos_Ordem (No *no_atual){
    //Enquanto no_atual não for NULL
    if (no_atual != NULL){
        Pos_Ordem (no_atual -> esquerda);
        Pos_Ordem (no_atual -> direita);
        cout <<no_atual -> info<<" ";
    }
}

//______________________________Pesquisar______________________________________

bool Arvore :: Pesquisar (No *no_atual, int info){
    //se não existir a informação na árvore
    if (no_atual == NULL){
        return false;
    }
    //se a inforrmação for encontrada
    else if (info == no_atual -> info){
        return true;
    }
    //decidir qual direção seguir
    else {

        //se informação menor que o pai, vai pra sequerda
        if (info < no_atual->info)
        {
            return Pesquisar(no_atual->esquerda, info);
        }
        //se não vai pra direita
        else if (info > no_atual->info)
        {
            return Pesquisar(no_atual->direita, info);
        }
    }  
      

}

//______________________________Excluir______________________________________

No *Arvore :: Excluir (No *no_atual, int info){
    //no temporário
    No *no_temp;

    //Se o no_atual é vazio, o nó não foi encontrado
    if(no_atual == NULL){
        return no_atual;
    }

    //rotas de escape: sub-árvore direita e esquerda
    //se a informação for maior: vai excluir rec a direita
    else if (info > no_atual -> info){
        no_atual-> direita = Excluir (no_atual -> direita, info);
        return no_atual;
    }
    //se a informação for menor: vai excluir rec a esquerda
    else if (info < no_atual -> info){
        no_atual -> esquerda = Excluir (no_atual -> esquerda, info);
        return no_atual;
    }

    else {
        //caso1
        //no encontrado é no folha
        if (no_atual -> esquerda == NULL and no_atual -> direita == NULL){
            delete no_atual;
            return NULL;
        }

        //caso 2: tem apenas 1 filho
        //no encontrado tem filho a esquerda
        else if (no_atual -> direita == NULL){
            no_temp = no_atual -> esquerda;
            delete no_atual;
            return no_temp;
        }
        //no encontrado tem filho a direita
        else if (no_atual -> esquerda == NULL){
            no_temp = no_atual -> direita;
            delete no_atual;
            return no_temp;
        }

        //caso 3: no encontrado tem dois filhos
        else {
            //balanceando a árvore com valor maior do que a raiz atual

            //recebendo a sub-árvore a direita para encontra  o menor valor que deixará a árvore balanceada
            no_temp = no_atual -> direita;

            //encontrado o menor valor da sub-árvore a direita
            while (no_temp -> esquerda != NULL){
                no_temp = no_temp -> esquerda;
            }

            //substituindo o valor na árvore
            no_atual -> info = no_temp -> info;

            //pesquisando e excluindo a origem do valor atribuído na linha anterior
            no_atual -> direita = Excluir (no_atual -> direita, no_temp -> info);

            //atualizando o no pai
            return no_atual;
        }
    }

}

//______________________________Altura______________________________________
int Arvore :: Altura (No *no_atual){
    int esquerda, direita;
    esquerda = direita = 0;
    
    if (no_atual != NULL){
        no_atual = no_atual -> esquerda;
        esquerda++;
    }

    while (no_atual != NULL){
        no_atual = no_atual -> direita;
        direita++;
    }

    if (esquerda > direita){
        return esquerda;
     }
     else{
         return direita;
     } 
    
}

No *Arvore ::Del_Arvore(No *no_atual)
{

    if (no_atual == NULL)
    {
        return no_atual;
    }
    if (no_atual->direita != NULL)
    {
        no_atual->direita = Del_Arvore(no_atual->direita);
        return no_atual;
    }
    //se a IDrmação for menor: vai excluir rec a esquerda
    else if (no_atual->esquerda != NULL)
    {
        no_atual->esquerda = Del_Arvore(no_atual->esquerda);
        return no_atual;
    }

    if (no_atual->esquerda == NULL and no_atual->direita == NULL)
    {
        delete no_atual;
        return NULL;
    }
    return no_atual;


}


//______________________________Função principal______________________________________
int main (){

    Arvore arvore;
    arvore.criar ();
    int menu;
    int no_valor;
        arvore.raiz = arvore.Inserir (arvore.raiz, 5);
        arvore.raiz = arvore.Inserir (arvore.raiz, 3);
        arvore.raiz = arvore.Inserir (arvore.raiz, 1);
        arvore.raiz = arvore.Inserir (arvore.raiz, 4);
        arvore.raiz = arvore.Inserir (arvore.raiz, 7);
    do{
        cout <<"\n\nMenu Arvore. Escolha uma opcao"<<endl;
        cout <<"---|1: Inserir novo no"<<endl;
        cout <<"---|2: Pesquisar"<<endl;
        cout <<"---|3: Excluir no"<<endl;
        cout <<"---|4: Imprimir em pre-ordem, em ordem, pos-ordem"<<endl;
        cout <<"---|5: Altura da arvore"<<endl;
        cout <<"---|6: Limpar frame"<<endl;
        cout <<"---|7: Deletar arvore"<<endl;
        cout <<"---|0: Finalizar"<<endl;

        cout <<"Opcao: ";cin >> menu;
        

        switch (menu)
        {
        case 1:
            cout <<"Digite os valores e pra terminar digite '0': "<<endl;
            do{
                cin >> no_valor;
                if(no_valor != 0) {
                    arvore.raiz = arvore.Inserir (arvore.raiz, no_valor);
                }
                
            }while (no_valor != 0);
            break;

        case 2:
            cout <<"Digite um valor: "; cin >> no_valor;
            if (arvore.Pesquisar (arvore.raiz, no_valor) == 1){
                cout<<"O valor digitado esta contido na arvore"<<endl;
            }
            else{
                cout<<"O valor digitado nao esta contido na arvore"<<endl;
            }
            break;
        case 3: //função excluir
            cout <<"Digite o valor a ser excluido: "; cin >> no_valor;
            arvore.raiz = arvore.Excluir (arvore.raiz, no_valor);
            cout <<"Valor excluido"<<endl;
            break;
        case 4:
            cout <<"\nImprimindo em pre-ordem"<<endl;
            arvore.Pre_Ordem (arvore.raiz);
            cout <<"\nImprimindo em ordem"<<endl;
            arvore.Em_Ordem (arvore.raiz);
            cout <<"\nImprimindo em pos-ordem"<<endl;
            arvore.Pos_Ordem (arvore.raiz);
            break;
        case 5:
            cout<<"\nA altura da arvore e: "<<arvore.Altura(arvore.raiz)<<endl;
            break;
        case 6:
            system("cls");
            break;
        case 7:
            while (arvore.raiz != NULL)
            {
                arvore.raiz = arvore.Del_Arvore(arvore.raiz);
            }
            break;
        default:
            break;
        }

    }while (menu !=0 );
    
return 0;
}
