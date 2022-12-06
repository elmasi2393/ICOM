#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>

using namespace std;


using Transaction = int;

struct Block_data
{
    static const unsigned N = 32;
    Block_data(unsigned pcrc) : prevCRC(pcrc) {}
    unsigned prevCRC;      // checksum del bloque previo, 0 si es el primer bloque
    Transaction transactions[N] = { 0 }; // transacciones del bloque
};

struct Block
{
    Block(unsigned crc) : data(crc), pNext(nullptr) {}
    Block_data data;			// bloque de datos
    Block* pNext;	      // siguiente bloque en la cadena
    void print() const{
        cout << " Transacciones" << endl;
        for(unsigned int i = 0; i <data.N; i++) cout << data.transactions[i] << endl;
    }
};

unsigned genCRC(const Block_data* pBlockData);

class BlockChain
{
public:
    // Crea una nueva cadena de bloques y la inicializa como vac�a
    BlockChain(){
        firstBlock = new Block(0);      //Creamos un bloque
        currBlock = firstBlock;         //Guardamos la referencia al siguiente
        currTransacIdx = 0;
    }

    // destruye una cadena de bloques liberando todos
    // los recursos asociados
    ~BlockChain(){
        Block * p = firstBlock;
        while(p != nullptr){
            Block *p2 = p;
            p = p->pNext;
            delete p2;
        }
    }

    // Agrega una nueva transacci�n a la cadena
    void addTransaction(Transaction t){
        currTransacIdx++;

        if(currTransacIdx == currBlock->data.N){    //Si el bloque esta lleno, creo uno nuevo
            Block * n = new Block(genCRC(&currBlock->data));
            currBlock->pNext = n;   //Cambio las referencias del nuevo al siguiente
            n->data.transactions[0] = t;
            currBlock = n;
            currTransacIdx = 0; //Fijo las transacciones a 1
            
        }else{
            currBlock->data.transactions[currTransacIdx] = t;   //Si no esta lleno, agregamos la nueva transaccion
        }
    }

    // funci�n que devuelve verdadero o falso indicando la validez de la cadena
    bool chainValid(){
        Block* p = firstBlock;
        while(p->pNext != nullptr){
            if(p->pNext->data.prevCRC != genCRC(&p->data))  //Si los CRC son diferentes, la blockchai no es valida
            	return false;
            p = p->pNext;
        }
        return true;
    }
    void print(){
        Block * p = firstBlock;
        while(p != nullptr){
            cout << "Block" << endl;
            p->print();
            p = p->pNext;
        }
    }

private:
    Block* firstBlock;		   // primer bloque de la cadena
    Block* currBlock;	       // bloque en generaci�n
    unsigned currTransacIdx;   // �ndice de transacci�n dentro de currBlock
};


static unsigned crc32_for_byte(unsigned int  r)
{
    for (int j = 0; j < 8; ++j)
        r = (r & 1 ? 0 : (unsigned )0xEDB88320L) ^ r >> 1;
    return r ^ (unsigned )0xFF000000L;
}

static void crc32(const void* data, size_t n_bytes, unsigned * crc)
{
    static unsigned   table[0x100];
    if (!table[0])
        for (size_t i = 0; i < 0x100; ++i)
            table[i] = crc32_for_byte(i);
    for (size_t i = 0; i < n_bytes; ++i)
        *crc = table[(unsigned char)*crc ^ ((unsigned char*)data)[i]] ^ *crc >> 8;
}

unsigned  genCRC(const Block_data* pBlockData)
{
    unsigned  crc = 0;
    crc32(pBlockData, sizeof(Block_data), &crc);
    return crc;
}


int main()
{
    srand((unsigned ) time(NULL));
    BlockChain bc;
    int count = 10000;
    while (count--)
        bc.addTransaction(rand());
    bc.print();

    if(bc.chainValid())
    	cout << "OK" << endl;
    assert(bc.chainValid());

    return 0;

}
