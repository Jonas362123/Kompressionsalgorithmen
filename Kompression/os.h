namespace os {
    enum class system {
        win,
        lin 
    };


    system sys = system::lin;


    static system get_system() {
        return sys;
    }
}