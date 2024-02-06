namespace os {
    enum class system {
        win,
        lin 
    };


    system sys = system::win;


    static system get_system() {
        return sys;
    }
}