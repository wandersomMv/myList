#ifndef LIST_H
#define LIST_H
#include<bits/stdc++.h>
#include<no.h>
template<class type>
class List;
template<class type>
class iterato // iterator para ajudar a percorer a lista
{
private:
    friend class List<type>;
    no<type> *atual;
public:
    bool operator !=(no<type> * cmp){
        return atual!=cmp;
    }
    void operator=(no<type> *pt){
        atual=pt;
    }
    void operator=(iterato &pt){
        atual=pt.atual;
    }
    type operator*(){
        return atual->dado;
    }
    bool operator==(no<type> *cmp){
        return cmp==atual;
    }
    void operator++(){
        atual = atual->next;
    }
    void operator+(int index){
        for(int i =0;i<index;i++)atual = atual->next;
    }
    void operator--(){
        atual=atual->previous;
    }
    iterato(no<type> *at){atual=at;}
    iterato(){atual=NULL;}

};
template<class type>
class List{
private:
    no<type> *begin; // inicio da lista
    no<type> *end; // final da lista
    int amount; // quantidade
public:
    typedef iterato<type> iterator;
    type pop_backType();
    type front()const{return begin->dado;}
    type back()const{return end->dado;}
    void push_back(type &dado);///Insere elemento no final da lista
    void push_front( type & dado);// insere elemento no começo da lista
    no<type> *Begin(){return begin;}// retorna o começo da lista
    no<type> *End(){return end;}//retorna o final da lista
    type &operator[](int index); // para inseriri um elemento em uma posição
    int size()const{return amount;}// tamanho da lista
    bool empty(){return amount==0;}// verificar se a lisra é vazia
    void pop_back();//retirar do final
    void pop_front();/// retirar do inicio
    no<type> *seach(iterator &it);//procucar com iterator
    bool seach(const type &value); // procurar com valor
    void insert(iterator &it,type); // inserir em uma possição dada
    void clear();
    List();
    ~List();
};
template<class type>
type List<type>::pop_backType(){
    if(!amount)throw std::string("Lista vazia!\n");
    no<type> *aux=end;
    end = aux->previous;
    end->next=NULL;
    type dado;
    amount--;
    no<type>::desmontaNo(aux,&dado);
    return dado;
}
template<class type>
void List<type>::insert(iterator &it, type d){
    try{
        no<type> *pt=no<type>::montano(&d);
        amount++;
        if(it.atual==begin){ // caso seja o inicio  faz se um push_front , insere na frente
            pt->next = begin;
            begin->previous = pt;
            begin = pt;
            return;
        }
        if(it.atual==end){ // caso seja o final iserir no final
            pt->previous=end;
            end->next = pt;
            end = pt;
            return;
        }
        pt->next = it.atual->next; //inserir o elemento na posicao que o iterator passou
        pt->previous = it.atual;
        it.atual->next = pt;
        pt->next->previous = pt;
    }catch(std::bad_alloc & erro){
        throw erro;
    }catch(...){
        throw std::string("Erro desconhecido!\n");
    }
}
template<class type>
void List<type>::clear(){
    no<type> *aux ;
    type aux1;
    while(begin){
        aux = begin;
        begin = aux->next;
        no<type>::desmontaNo(aux,&aux1);
        amount--;
    }
}
template <class type>
List<type>::~List() {//destrutor
    clear();
}
template<class type>
bool List<type>::seach(const type &value){
    int i;
    no<type> *aux=begin;
    for(i=0;i<amount&&aux->dado!=value;aux=aux->next,i++);
    return i<amount;
}

template <class type>
no<type> *List<type>::seach(iterator &it){ // proxurar um elemento na lista e retornar o iterator , caso não ache retorna NULL
    int i;
    no<type> *aux=begin;
    for(i =0;i<amount&&aux!=it.atual;i++,aux->next);
    if(i>= amount)return NULL;
    return aux;
}
template<class type>
void List<type>::pop_front(){
    if(!amount)throw std::string("Lista vazia!\n");
    no<type> *aux=begin;
    begin = aux->next;
    begin->previous=NULL;
    type dado;
    amount--;
    no<type>::desmontaNo(aux,&dado);

}
template<class type>
void List<type>::pop_back(){
    if(!amount)throw std::string("Lista vazia!\n");
    no<type> *aux=end;
    end = aux->previous;
    end->next=NULL;
    type dado;
    amount--;
    no<type>::desmontaNo(aux,&dado);
}

template <class type>
type &List<type>::operator [](int index)
{
    if(index<0||index>amount)throw std::string("Posição invalida!\n");
    no<type> *aux=begin;
    for(int i=0;i<index;i++)
        aux=aux->next;
    return aux->dado;
}
template<class type>
List<type>::List() // contrutor para começar com a lista vazia , apontando o final e o começo para null
{
    begin = NULL;//começado a lista vazia , apontando para nulo
    end = NULL;
    amount = 0;
}
template<class type>
void List<type>::push_back(type &dado) // inserir novo elemento no final da lista
{
    try{
        no<type> * novo = no<type>::montano(&dado);
        if(!amount){// se a lista não conter nehum elemento
            begin=novo;
            end=novo;  // inicio e começo aponta para o elemento
        }
        else{//chegou aqui existe um ou mais elementos

            end->next =novo;//fazendo o ultimo apontar para o novo ultimo
            novo->previous = end; // fazendo o novo ultimo apontar para o final antingo
            end = novo; // colocando o final para apontar para o elemento que entrou
        }
        amount++;//incrementando a quantidade de elementos
    }catch(std::bad_alloc &erro){
        throw erro;
    }
    catch(...){
        throw std::string("Erro desconhecido!\n");
    }

}
template<class type>
void List<type>::push_front(type &dado)//inserir elemento no inicio da lista
{
    try{
        no<type> * novo = no<type>::montano(&dado);
        if(!amount){//a lista não possui nenhum elemento quantidade =0
            begin = novo;
            end = novo;
        }
        else{//chegou aqui quer dizer que possui pelo menos um elemento
            begin->previous = novo;//o anterior da lista aponta para o novo elemento
            novo->next = begin;// o proximo do novo elemento aponta para o inicio da lista
            begin = novo;// begin recebe o novo inicio
        }
        amount++;
    }catch(std::bad_alloc &erro){
        throw erro;
    }catch(...){
        throw std::string("Erro desconhecido!\n");
    }
}




#endif // LIST_H
