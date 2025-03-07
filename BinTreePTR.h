#ifndef BINTREEPTR_H
#define BINTREEPTR_H

#include <iostream>
#include <stdexcept>
#include "PTRStack.h"
#include "PTRQueue.h"
using namespace std;

template <class T>
class BinTree {
private:
    struct BinTreeNode
    {
        T data;
        BinTreeNode *left;
        BinTreeNode *right;

        explicit BinTreeNode (T value) {
            data = value;
            left = nullptr;
            right = nullptr;
        }

		BinTreeNode () {
			data = T{};
			left = nullptr;
			right = nullptr;
		}
    };

    BinTreeNode *root;

    BinTreeNode* getFatherRecursive(BinTreeNode* parent, BinTreeNode* currentNode) {
        if (!parent) return nullptr; // Caso base: nodo nullo

        // Se il nodo corrente è figlio del nodo attuale, ritorna il nodo attuale
        if (getLeft(parent) == currentNode || getRight(parent) == currentNode) {
            return parent;
        }

        // Ricerca ricorsiva nei sottoalberi sinistro e destro
        getFatherRecursive(getLeft(parent), currentNode);
        getFatherRecursive(getRight(parent), currentNode);
    }

	void printInOrder(const BinTreeNode* currentNode) const {
		if (!currentNode) return;  // Caso base: nodo nullo (fine ricorsione)
		printInOrder(currentNode->left);  // Visita il sottoalbero sinistro
		std::cout << currentNode->data << " ";  // Stampa il valore del nodo corrente
		printInOrder(currentNode->right);  // Visita il sottoalbero destro
	}

public:
    explicit BinTree(T value) : root(new BinTreeNode(value)) {};    //costruttore della radice col valore
    BinTree() : root(nullptr) {};                                   //costruttore vuoto
    ~BinTree() {
        deleteSubBinTree(root);
        delete root;
    }
	void printTree () const {
		printInOrder(this->root);
		std::cout << "\n" << std::endl;
	}

	//funzioni booleane
    bool isEmptyTree() {return this->root == nullptr;};
    bool isEmptyDx(const BinTreeNode* currentNode) {return currentNode->right == nullptr;};
    bool isEmptySx(const BinTreeNode* currentNode) {return currentNode->left == nullptr;};
	bool isEmptyNode(const BinTreeNode* currentNode) {return isEmptyDx(currentNode) &&
														isEmptySx(currentNode);};

	// Metodo per impostare il valore di un nodo (se il nodo creato dovesse essere un nodo vuoto)
    void setNodeData(BinTreeNode *currentNode, T value) {
        if (!currentNode) throw std::invalid_argument("Nodo nullo.");
        currentNode->data = value;
    }
	T readNodeData(BinTreeNode *currentNode) const {return currentNode->data;};	//legge il valore del
																				//nodo corrente
    BinTreeNode* getLeft (BinTreeNode* currentNode) {return currentNode->left;};
    BinTreeNode* getRight (BinTreeNode* currentNode) {return currentNode->right;};
	BinTreeNode* getRoot() const {return this->root;};	//ritorna un puntatore alla root
														//questa funzione mi permette di accedere
														//in tempo O(1) alla root dell'albero intero
    BinTreeNode* getFather(BinTreeNode* currentNode) {
        if (!root || root == currentNode || !currentNode) return nullptr; // La radice non ha un padre

        return getFatherRecursive(root, currentNode);
    }

    //funzioni di inserimento
    BinTreeNode* insertFather(BinTreeNode* currentNode) {	//inserisce un padre con valore "vuoto"
															//al nodo corrente di input
        if (!currentNode)
            throw std::invalid_argument("Puntatore nullo fornito.");
        if (currentNode == root) {
            BinTreeNode* newRoot = new BinTreeNode(T{}); // Creazione di un nuovo nodo con valore di default
            newRoot->left = currentNode;
            return newRoot;
        }
        else {
            return currentNode;
        }
    }

    BinTreeNode* insertChildDx(BinTreeNode* currentNode) {	//le due funzioni di inserimento del
															//figlio destro e sinistro creano
															//un nodo figlio con valore default
															//Serve la funzione di scrittura del
															//nodo per scrivere il valore di esso
		if (!currentNode)
			throw std::invalid_argument("Puntatore nullo");
		else if (!isEmptyDx(currentNode)) {
			return insertChildDx(currentNode->right);	//ricorsività nel caso in cui il nodo destro del nodo
														//corrente dovesse essere vuoto
		}
		BinTreeNode* newChildNode = new BinTreeNode();	//nodo vuoto di default
		currentNode->right = newChildNode;	//il puntatore destro del current node punta al nodo
											//appena creato
		return newChildNode;	//ritorniamo il puntatore creato
	}

    BinTreeNode* insertChildSx(BinTreeNode* currentNode) {  //le due funzioni di inserimento del
															//figlio destro e sinistro creano
															//un nodo figlio con valore default
															//Serve la funzione di scrittura del
															//nodo per scrivere il valore di esso

		if (!currentNode)
			throw std::invalid_argument("Puntatore nullo");
		else if (!isEmptySx(currentNode)) {
			return insertChildSx(currentNode->left);	//ricorsività col nodo sinistro
		}

		BinTreeNode* newChildNode = new BinTreeNode();
		currentNode->left = newChildNode;
		return newChildNode;
	}

	BinTree uniteTrees(BinTree& T1, BinTree& T2) {
		// Crea un nuovo albero con una radice vuota
		BinTree<T> unionTree(T{});

		// Controlla se gli alberi T1 e T2 non sono vuoti
		if (!T1.isEmptyTree() && !T2.isEmptyTree()) {

			// Collega T1 come sottoalbero sinistro e T2 come sottoalbero destro
			unionTree.root->left = T1.root;
			unionTree.root->right = T2.root;

		} else {
			throw std::invalid_argument("Entrambi gli alberi devono essere non vuoti per l'unione.");
		}

		return unionTree;
	}

	BinTreeNode* deleteSubBinTree (BinTreeNode* currentNode) {	//la funzione ha il compito di
																 //eliminare un sottoalbero a partire da
																 //un nodo di esso senza eliminare
																 //il nodo di input

		if (!currentNode) {	//check se il nodo di input è nullo
			this->printTree();	//stampa l'albero (debug)
			throw std::invalid_argument("nodo nullo fornito");
		}

		BinTreeNode** travelerPointer = &currentNode;	//creiamo un DOPPIO PUNTATORE a currentNode
														//il cui VALORE corrisponde al currentNode
														//e che PUNTA all'indirizzo del currentNode

		while ((*travelerPointer)->left || (*travelerPointer)->right) {	//ECCO COME EVITARE IL SEG. FAULT:
																		//al posto di checkare i sottoalberi
																		//del valore del travelerPointer
																		//(ovvero il currentNode) con un IF,
																		//usiamo le leggi di De Morgan e un
																		//ciclo while, che si ripeterà
																		//fin quando entrambi i nodi left
																		//e right del travelerPointer non
																		//saranno nulli
			if ((*travelerPointer)->left) {	//se il nodo non-nullo dovesse essere il sinistro,
											//il trav.ptr punterà all'INDIRIZZO DI MEMORIA DEL
											//CAMPO left DEL PROPRIO VALORE
											// (è l'unico modo per farlo scalare in giù a sinistra di
											// una posizione, dato che si tratta di un doppio puntatore)
				travelerPointer = &(*travelerPointer)->left;
			}

			else if ((*travelerPointer)->right) {	//medesima cosa con il campo right
													// (ma tanto li checka entrambi perché poi
													// operiamo la ricorsione)
				travelerPointer = &(*travelerPointer)->right;
			}
		}

		/* === FINE DEL WHILE ==
		 * a questo punto il travelerPointer è
		 * - senza nodi figli
		 * - esistente e con un valore
		 */

		if (*travelerPointer == currentNode)	//se il valore del trav.ptr dovesse essere uguale al
												//currentNode iniziale, allora il codice si ferma,
												//poiché avremmo eliminato tutti i sottoalberi
												//al di sotto di currentNode
			return currentNode;

		else {	//ALTRIMENTI, eliminiamo IL VALORE di travelerPointer, per poi settarlo a
				//nullptr in modo tale da evitare dangling points

			delete *travelerPointer;
			*travelerPointer = nullptr;
			return deleteSubBinTree(currentNode);	//chiamata ricorsiva della funzione sul currentNode (non modificato)
		}
	}

    BinTreeNode* bfs(T valore) const {
        if (!root) return nullptr; // Albero vuoto

        PTR_Queue<BinTreeNode*> coda; // Usa la coda implementata nel file
        coda.pushTail(root);

        while (!coda.isEmptyCoda()) {
            BinTreeNode* nodo = coda.readHead();
            coda.deleteHead();

            if (nodo->data == valore) return nodo;

            if (nodo->left) coda.pushTail(nodo->left);
            if (nodo->right) coda.pushTail(nodo->right);
            //cout << coda.readHead() << endl;
            //cout << coda.readTail() << endl;
        }

        return nullptr; // Nodo non trovato
    }

    BinTreeNode* dfs(T valore) const {
        if (!root) return nullptr; // Albero vuoto

        PTR_Stack<BinTreeNode*> pila; // Usa lo stack implementato nel file
        pila.pushStack(root);

        while (!pila.isEmptyStack()) {
            BinTreeNode* nodo = pila.readStack();
            pila.popStack();

            if (nodo->data == valore) return nodo;

            if (nodo->right) pila.pushStack(nodo->right);
            if (nodo->left) pila.pushStack(nodo->left);
        }

        return nullptr; // Nodo non trovato
    }
};

#endif
