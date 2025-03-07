#ifndef BST_H
#define BST_H

#include <iostream>
#include <stdexcept>
using namespace std;

class BST {
    private:
        struct Node
        {
            Node* right;
            Node* left;
            int value;

            //costruttore del nodo con un valore iniziale
            explicit Node (int val) {
                right = nullptr;
                left = nullptr;
                value = val;
            }

            //costruttore del nodo vuoto
            Node () {
                right = nullptr;
                left = nullptr;
                value = int{};      //valore di default per il tipo di dato int
            }
        };

        //main node
        Node* root;

        //get functions
        const int getValue (Node *currentNode) {return currentNode->value;};
        Node* getRight (Node *currentNode) {return currentNode->right;};
        Node* getLeft (Node *currentNode) {return currentNode->right;};

        //set functions
        void setValue (int val, Node* currentNode) {currentNode->value = val;};
        void setRight (Node* nodeToSet, Node* currentNode) {currentNode->right = nodeToSet;};
        void setLeft (Node* nodeToSet, Node* currentNode) {currentNode->left= nodeToSet;};

        // Ricerca del nodo
        Node* searchNode(Node* currentNode, int key) {
            if (!currentNode || currentNode->value == key) {
                return currentNode;
            }
            if (key < currentNode->value) {
                return searchNode(currentNode->left, key);  //la ricerca prosegue a sinistra
            }
            return searchNode(currentNode->right, key); //altrimenti prosegue comunque a destra
        }

        // Trova il nodo minimo partendo da un nodo dato
        Node* findMin(Node* currentNode) {
            while (currentNode && currentNode->left) {  //mentre esistono sia il nodo, sia il suo ramo sinistro...
                currentNode = currentNode->left;        //... scorriamo i nodi a sinistra
            }
            return currentNode;                         //fin quando non ci sono più sottonodi sinistri e quindi
                                                        //ritorniamo il nodo a cui siamo arrivati
        }

        // Trova il nodo massimo partendo da un nodo dato
        Node* findMax(Node* currentNode) {
            while (currentNode && currentNode->right) { //stessa cosa, ma cercando il massimo, ovviamente verso destra
                currentNode = currentNode->right;
            }
            return currentNode;
        }

        public:
            explicit BST(int rootVal) : root(new Node(rootVal)) {};     //costruttore con un valore iniziale
            BST() : root(nullptr) {};                                   //costruttore vuoto
            ~BST() {};
            Node* getRoot () {return root;};
            void setRoot (Node* nodeToSet) {root = nodeToSet;};

            //boolean functions
            bool isBSTempty () {return root == nullptr;};
            bool isRightempty (Node* currentNode) {return currentNode->right == nullptr;};
            bool isLeftempty (Node* currentNode) {return currentNode->left == nullptr;};

            //insert function
            Node* insertValue (Node* currentNode, int value) {
                if (!currentNode) {
                    return new Node(value);
                }
                if (value >= currentNode->value) {
                    // se è vuoto, creiamo un nodo a destra e ci mettiamo il valore
                    // altrimenti, passiamo al nodo successivo
                    if (isRightempty(currentNode)) {
                        Node *nodeToInsert = new Node(value);
                        setRight(nodeToInsert, currentNode);
                    }
                    else {
                        //setRoot(root->right);
                        return insertValue(currentNode->right, value);
                    }
                }
                else {
                    // se è vuoto, creiamo un nodo a sinistra e ci mettiamo il valore
                    // altrimenti, passiamo al nodo successivo

                    if (isLeftempty(currentNode)) {
                        Node *nodeToInsert = new Node(value);
                        setLeft(nodeToInsert, currentNode);
                    }
                    else {
                        //setRoot(root->left);
                        return insertValue(currentNode->left, value);
                    }
                }
                return root;
            }

            // funzione di ricerca richiamabile dalla classe
            bool search(int key) {
                return searchNode(root, key) != nullptr;    //ritorna vero se esiste il nodo ricercato dalla root
                                                            //tramite la chiave (CHIAVE = VALUE) }
            }
            // funzione di ricerca che restituisce un nodo
            Node* searchAndGetNode(int key) {
                return searchNode(root, key);
            }

            // ricerca del successore
            int findSuccessor(int key) {
                Node* current = searchNode(root, key);  //check se esiste il nodo con il valore
                if (!current) {
                    throw std::invalid_argument("Chiave non trovata");
                }

                if (current->right) {
                    return findMin(current->right)->value;  //se esiste il nodo destro, ritorna il valore
                                                            //minimo di esso => una volta passati al nodo
                                                            //destro del current, la funzione va costantemente
                                                            //a sinistra fino a quando non trova una voglia
                                                            //il CURRENT è il valore MINIMO, mentre il CURRENT->RIGHT
                                                            //è il valore MASSIMO entro i quali si può trovare il
                                                            //successore di current
                }

                Node* successor = nullptr;
                Node* ancestor = root;
                while (ancestor != current) {               //ancestor e successor si muovono FINCHE' l'ancestor
                                                            //non arriva al nodo con la chiave trovata in
                                                            //precedenza
                    if (key < ancestor->value) {
                        successor = ancestor;               //il successor si muove SOLO SE la chiave è MINORE
                                                            //del valore dell'ancestor (avviene il contrario coi
                                                            //predecessori) e va al nodo precedentemente
                                                            //puntato dall'ancestor
                        ancestor = ancestor->left;          //QUI l'ancestor, infatti, si sposta a sinistra
                                                            //(al contrario coi predecessori) e il successor
                                                            //prende il suo posto
                    } else {
                        ancestor = ancestor->right;
                    }
                }
                if (successor) {
                    return successor->value;    //qui ritorniamo il successor
                }
                throw std::invalid_argument("Successore non trovato");
            }

            // ricerca del predecessore
            int findPredecessor(int key) {
                Node* current = searchNode(root, key);
                if (!current) {
                    throw std::invalid_argument("Chiave non trovata");
                }

                if (current->left) {
                    return findMax(current->left)->value;
                }

                Node* predecessor = nullptr;
                Node* ancestor = root;
                while (ancestor != current) {
                    if (key > ancestor->value) {
                        predecessor = ancestor;
                        ancestor = ancestor->right;
                    } else {
                        ancestor = ancestor->left;
                    }
                }
                if (predecessor) {
                    return predecessor->value;
                }
                throw std::invalid_argument("Predecessore non trovato");
            }

	        Node* deleteSubBinTree (Node* currentNode) {	//la funzione ha il compito di
                                                    //eliminare un sottoalbero a partire da
                                                    //un nodo di esso senza eliminare
                                                    //il nodo di input

		        if (!currentNode) {	//check se il nodo di input è nullo
			        this->printInOrder(getRoot());	//stampa l'albero (debug)
			        throw std::invalid_argument("nodo nullo fornito");
		        }

		        Node** travelerPointer = &currentNode;	//creiamo un DOPPIO PUNTATORE a currentNode
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

            // Funzione per stampare i valori dell'albero (in ordine)
            void printInOrder(Node* node) {
                if (node == nullptr) return;
                printInOrder(node->left);
                std::cout << node->value << " ";
                printInOrder(node->right);
            }
};

#endif
