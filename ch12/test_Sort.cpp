#include "quickSort.h"
#include "selection.h"
#include "../Visit.h"

int main(){
    Visit visit;
    Vector<int> V = Vector<int>();
    for (Rank r = 0; r < 10; r++)
        V.insert(r, rand()%1000);
    V.traverse(visit);
    std::cout << std::endl;
    V.quickSort(0, V.size());
    V.traverse(visit);
    std::cout << std::endl;

    Vector<int> selectVector = Vector<int>();
    selectVector.insert(3);
    selectVector.insert(3);
    selectVector.insert(3);
    selectVector.insert(3);
    selectVector.insert(4);
    selectVector.insert(5);
    selectVector.insert(6);
    selectVector.traverse(visit);
    std::cout << std::endl;
    int majCandidate;
    majCandidate = majEleCandidate(selectVector);
    std::cout << majCandidate << ' ' <<  majority(selectVector, majCandidate) << std::endl;

}