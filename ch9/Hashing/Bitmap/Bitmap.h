#include <iostream>
#include <string.h>
#include "../ch2/MyVector.h"


class Bitmap{
    private:
        char* M; //存放空间
        int N;

    protected:
        void init(int n){M = new char[N = (n + 7) / 8]; memset(M, 0, N);}
    public:
        Bitmap(int n = 8){init(n);}
        Bitmap(char* file, int n = 8){
            init(n);
            FILE* fp = fopen(file, "r");
            fread(M, sizeof(char), N, fp);
            fclose(fp);
        }
        ~Bitmap(){delete [] M; M = NULL;}

        void set(int k){expand(k); M[k >> 3] |= (0x80 >> (k & 0x07));}
        void clear(int k){expand(k); M[k >> 3] &= ~ (0x80 >> (k & 0x07));}
        bool test(int k){expand(k); return M[k >> 3] & (0x80 >> (k & 0x07));}

        void dump(char* file){
            FILE* fp = fopen(file, "w");
            fwrite(M, sizeof(char), N, fp);
            fclose(fp);
        }

        char* bit2string(int n){
            expand(n - 1);
            char* s = new char[n + 1];
            s[n] = '\0';
            for(int i = 0; i < n; i ++){
                s[i] = test(i) ? '1' : '0';
            }
            return s;
        }

        void expand(int k){
            if (k < 8 * N) return;
            int oldN = N;
            char* oldM = M;
            init(2 * k);
            memcpy_s(M, N, oldM, oldN);
            delete [] oldM;
        }
};