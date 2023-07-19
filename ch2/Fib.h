typedef int Rank;
class Fib{
    private:
        Rank f, g; //f = fib(k-1), g = fib(k)
    public:
        Fib(Rank n){
            f = 1;
            g = 0;
             while(g < n)
                next();
        }
        Rank get() {return g;} //获取当前fib项
        Rank next() {g += f; f = g - f; return g;} //转至下一项
        Rank prev() {f = g - f; g -= f; return g;} //转至上一项
};