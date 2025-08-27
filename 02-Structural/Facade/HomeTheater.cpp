#include<iostream>
#include<string>
#include<memory>

// complex subsystem classes
class DVDPlayer{
    public:
        void on(){
            std::cout << "DVD player is ON" << std::endl;
        }
        void off(){
            std::cout << "DVD player is OFF" << std::endl;
        }
        void play(){
            std::cout << "DVD player is playing" << std::endl;
        }
        void stop(){
            std::cout << "DVD player stopped" << std::endl;
        }
        void eject(){
            std::cout << "Ejecct DVD" << std::endl;
        }
};
class Lights{
    private:
        int brightness = 10;
    public:
        void dim(int level){
            brightness = level;
            std::cout << "Lights dimmed to : " << brightness <<  "%" << std::endl;
        }
        void on(){
            std::cout << "Lights are turned ON (100%)" << std::endl;
        }
        void off(){
            std::cout << "Lights OFF" << std::endl;
        }
};
class Screen {
public:
    void down() {
        std::cout << "Theater screen is DOWN" << std::endl;
    }
    
    void up() {
        std::cout << "Theater screen is UP" << std::endl;
    }
};
// FACADE class - SIMPLE interface to the complex subsys
class HomeTheaterFacade{
    private:
        std::unique_ptr<DVDPlayer> dvdPlayer;
        std::unique_ptr<Screen> screen;
        std::unique_ptr<Lights> lights;
    public:
        HomeTheaterFacade(){
            // initialize all subsys
            dvdPlayer = std::make_unique<DVDPlayer>();
            screen = std::make_unique<Screen>();
            lights = std::make_unique<Lights>();
        }
        // simple interface method 
        void watchMovie(const std::string& movie){
            std::cout << "\n=== Getting ready to watch movie: " << movie << " ===" << std::endl;
            
            lights->dim(10);
            screen->down();
            dvdPlayer->on();
        }
        void endMovie(){
            std::cout << "\n=== Shutting down movie theater ===" << std::endl;
            
            screen->up();
            dvdPlayer->eject();
            dvdPlayer->off();
            lights->off(); 
        }
        // Additional convenience methods
        void pauseMovie() {
            std::cout << "\n=== Pausing movie ===" << std::endl;
            dvdPlayer->stop();
            lights->dim(50);
        }
        void resumeMovie() {
            std::cout << "\n=== Resuming movie ===" << std::endl;
            lights->dim(10);
            // In real implementation, DVD player would resume from pause
            std::cout << "Movie resumed" << std::endl;
        }
        Lights* getLights() { return lights.get(); }
};
int main() {
    std::cout << "=== Home Theater Facade Pattern Demo ===\n" << std::endl;
    
    // Using the facade - simple and clean
    HomeTheaterFacade homeTheater;
    
    // One simple method call handles all the complexity
    homeTheater.watchMovie("The Avengers");
    
    std::cout << "\n--- Later during the movie ---" << std::endl;
    homeTheater.pauseMovie();
    
    std::cout << "\n--- Bathroom break over ---" << std::endl;
    homeTheater.resumeMovie();
    
    std::cout << "\n--- Movie finished ---" << std::endl;
    homeTheater.endMovie();
    
    // Demonstrate direct access to subsystems if needed
    std::cout << "\n=== Adjusting just the lights ===" << std::endl;
    homeTheater.getLights()->dim(30);

    std::cout << "\n=== Demo completed ===" << std::endl;
    
    return 0;
}