#ifndef NTREEPTR_H
#define NTREEPTR_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class PTR_NTree {
private:
    struct TreeNode {
        T dato;
        TreeNode** figli;
        int numero_figli;
        int livello;

        TreeNode(T value, int max_figli, int lvl) {
            dato = value;
            figli = new TreeNode*[max_figli]{};
            numero_figli = 0;
            livello = lvl;
        }

        ~TreeNode() {
            delete[] figli;
        }
    };

    TreeNode* root;
    int grado;

    void CancellaSottoalbero(TreeNode* nodo) {
        if (!nodo) return;
        for (int i = 0; i < nodo->numero_figli; i++) {
            CancellaSottoalbero(nodo->figli[i]);
        }
        // nodo = nullptr;
        if (isFoglia(nodo)) {
            TreeNode** travelerPTR;
            TreeNode* padre = getFather(nodo);
            travelerPTR = &padre;

            (*travelerPTR)->figli[getIndiceFiglio(padre, nodo)] = nullptr;

            delete nodo;
            nodo = nullptr;
            return;
        }
    }

    TreeNode* trovaPadre(TreeNode* nodo, TreeNode* target) {
        if (!nodo || nodo->numero_figli == 0) return nullptr;
        for (int i = 0; i < nodo->numero_figli; i++) {
            if (nodo->figli[i] == target) return nodo;
            TreeNode* trovato = trovaPadre(nodo->figli[i], target);
            if (trovato) return trovato;
        }
        return nullptr;
    }

    int getIndiceFiglio(TreeNode* padre, TreeNode* figlio) {
        if (!padre || !figlio) throw invalid_argument("Nodi nulli.");
        for (int i = 0; i < padre->numero_figli; i++) {
            if (padre->figli[i] == figlio) return i;
        }
        return -1; // Il nodo figlio non è stato trovato
    }

    void stampa(TreeNode* nodo, int livello) {
        if (!nodo) return;
        for (int i = 0; i < livello; i++) cout << "  "; // Indentazione
        cout << nodo->dato << endl;
        for (int i = 0; i < nodo->numero_figli; i++) {
            stampa(nodo->figli[i], livello + 1);
        }
    }

public:
    PTR_NTree(int num_max_figli) : root(nullptr), grado(num_max_figli) {}

    ~PTR_NTree() {
        CancellaSottoalbero(root);
    }

    bool alberoVuoto() {
        return root == nullptr;
    }

    void insRadice(T valore) {
        if (root) throw runtime_error("La radice esiste già.");
        root = new TreeNode(valore, grado, 0);
    }

    TreeNode* getRoot() {
        return root;
    }

    TreeNode* getFather(TreeNode* nodo) {
        if (!nodo || nodo == root) return nullptr;
        return trovaPadre(root, nodo);
    }

    bool isFoglia(TreeNode* nodo) {
        if (!nodo) throw invalid_argument("Nodo nullo.");
        return nodo->numero_figli == 0;
    }

    TreeNode* primoFiglio(TreeNode* nodo) {
        if (!nodo || nodo->numero_figli == 0) return nullptr;
        return nodo->figli[0];
    }

    TreeNode* ultimoFratello(TreeNode* nodo) {
        if (!nodo || !root) return nullptr;
        TreeNode* parent = nullptr;
        for (TreeNode* n = root; n; n = primoFiglio(n)) {
            for (int i = 0; i < n->numero_figli; i++) {
                if (n->figli[i] == nodo) {
                    parent = n;
                    break;
                }
            }
        }
        return parent ? parent->figli[parent->numero_figli - 1] : nullptr;
    }

    TreeNode* succFratello(TreeNode* nodo) {
        if (!nodo || !root) return nullptr;
        TreeNode* parent = nullptr;
        for (TreeNode* n = root; n; n = primoFiglio(n)) {
            for (int i = 0; i < n->numero_figli - 1; i++) {
                if (n->figli[i] == nodo) {
                    return n->figli[i + 1];
                }
            }
        }
        return nullptr;
    }

    void insPrimoSottoalbero(TreeNode* nodo, PTR_NTree<T>& sottoalbero) {
        if (!nodo || !sottoalbero.root) throw invalid_argument("Nodo o sottoalbero nullo.");
        if (nodo->numero_figli >= grado) throw runtime_error("Numero massimo di figli raggiunto.");
        for (int i = nodo->numero_figli; i > 0; i--) {
            nodo->figli[i] = nodo->figli[i - 1];
        }
        nodo->figli[0] = sottoalbero.root;
        nodo->numero_figli++;
        sottoalbero.root = nullptr;
    }

    void insSottoAlbero(TreeNode* nodo, PTR_NTree<T>& sottoalbero) {
        if (!nodo || !sottoalbero.root) throw invalid_argument("Nodo o sottoalbero nullo.");
        if (nodo->numero_figli >= grado) throw runtime_error("Numero massimo di figli raggiunto.");
        nodo->figli[nodo->numero_figli++] = sottoalbero.root;
        sottoalbero.root = nullptr;
    }

    void cancSottoAlbero(TreeNode* nodo) {
        if (!nodo) return;
        CancellaSottoalbero(nodo);
        // nodo = nullptr;
    }

    void stampaAlbero () {
        stampa(root, 0);
    }
};

#endif
