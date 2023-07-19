#include <iostream>
#include "../ch2/MyVector.h"

class Bitmap2{
    private:
        Rank* F;
        Rank N;
        Rank* T;
        Rank top;

    protected:
        inline bool valid(Rank r){return (0 <= r) && (r < top);}
        inline bool erased(Rank k){
            return valid(F[k]) && !(T[F[k]] + 1 + k);
        }
    
    public:
        Bitmap2(Rank n = 8){
            N = n;
            F = new Rank[N];
            T = new Rank[N];
            top = 0;
        }
        ~Bitmap2(){delete [] F; delete [] T;}

        inline void set(Rank k){
            if (test(k)) 
                return ;
            if(!erased(k)) F[k] = top ++;
            T[F[k]] = k;
        }
        inline void clear(Rank k){
            if(test(k)){
                T[F[k]] = -1-k;
            }
        }
        inline bool test(Rank k){
            return valid(F[k]) && (k == T[F[k]]);
        }
};