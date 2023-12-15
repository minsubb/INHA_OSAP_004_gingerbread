/*
The MIT License

Copyright (c) <2023> <Minsub Kim, Jiwon Park, Jeonghui Han>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
