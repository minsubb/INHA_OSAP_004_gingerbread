#include "AVLTree.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        AVLTree avlTree;
        int q;
        cin >> q;
        while (q--) {
            string command;
            cin >> command;

            if (command == "empty") {
                avlTree.Empty();
                continue;
            }
            if (command == "size") {
                avlTree.Size();
                continue;
            }

            int x;
            cin >> x;
            if (command == "minimum") {
                avlTree.Minimum(x);
                continue;
            }
            if (command == "maximum") {
                avlTree.Maximum(x);
                continue;
            }
            if (command == "find") {
                avlTree.Find(x);
                continue;
            }
            if (command == "insert") {
                avlTree.Insert(x);
                continue;
            }
            if (command == "rank") {
                avlTree.Rank(x);
                continue;
            }
            if (command == "erase") {
                avlTree.Erase(x);
                continue;
            }
        }
    }

    return 0;
}
