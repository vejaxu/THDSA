class Visit{
    public:
        template <typename T>
        void operator()(T value){
            std::cout << value << "  ";
        }
};