#include <iostream>
#include <memory>
#include <string>

// Implementation interface for devices(Bridge Interface)
// This defines the interface for the implementation hierarchy
class Device{
    public:
        virtual ~Device() = default;
        virtual void powerOn() = 0;
        virtual void powerOff() = 0;
        virtual int getVolume() const = 0;
        virtual int getChannel() const = 0;
        virtual void setVolume(int volume) = 0;
        virtual void setChannel(int channel) = 0;
        virtual bool isPowered() const = 0;
        virtual std::string getDeviceType() const = 0;
};
// concrete device implemnetations
class TV : public Device{
    private:
    bool powered;
    int vol = 50, channel = 1;
    public:
        void powerOn() override{
            powered = true;
            std::cout << "TV is on" << std::endl;
        }
        void powerOff() override{
            powered = false;
            std::cout << "TV is off" << std::endl;
        }
        void setVolume(int volume) override{
            vol = volume;
            std::cout << "TV volume is set to " << vol << std::endl;
        }
        void setChannel(int chan) override{
            channel = chan;
            std::cout << "TV channel is " << channel << std::endl;
        }
        std::string getDeviceType() const  { return "TV"; }
        int getVolume() const override { return vol; }
        int getChannel() const  override{ return channel; }
        bool isPowered() const override { return powered; }
};
class Radio : public Device{
    private:
    bool powered;
    int vol = 50, channel = 1;
    public:
        void powerOn() override{
            powered = true;
            std::cout << "Radio is on" << std::endl;
        }
        void powerOff() override{
            powered = false;
            std::cout << "Radio is off" << std::endl;
        }
        void setVolume(int volume) override{
            vol = volume;
            std::cout << "Radio volume is set to " << vol << std::endl;
        }
        void setChannel(int chan) override{
            channel = chan;
            std::cout << "Radio channel is " << channel << std::endl;
        }
        std::string getDeviceType() const  { return "Radio"; }
        int getVolume() const override { return vol; }
        int getChannel() const  override{ return channel; }
        bool isPowered() const override { return powered; }
};
// Abstraction - Remote Control  It's particularly useful when you want to avoid permanent binding between an abstraction and its implementation.
//Defines the abstraction's interface and maintains a reference to the implementor,separates an abstraction from its implementation
class Remote{
    protected:
        std::shared_ptr<Device> device;
    public:
        Remote(std::shared_ptr<Device> inputDevice) : device(inputDevice){}
        virtual ~Remote() = default;
        virtual void powerToggle(){
            if (device->isPowered()){
                device->powerOff();
                return;
            }
            device->powerOn();
            return;
        }
        virtual void volumeUp(){
            int cur = device->getVolume();
            device->setVolume(cur + 10);
        }
        virtual void volumeDown(){
            int cur = device->getVolume();
            device->setVolume(cur - 10);
        }
        virtual void channelUp(){
            int cur = device->getChannel();
            device->setChannel(cur + 1);
        }
        virtual void channelDown(){
            int cur = device->getChannel();
            device->setChannel(cur - 1);
        }
        std::string getDeviceInfo() const{
            return device->getDeviceType() + "- Power: " + (device->isPowered()? "ON" : "OFF") +
                ", Volume: " + std::to_string(device->getVolume()) + " , Channel" + 
                std::to_string(device->getChannel());
            }       

};
//Refined Abstraction: Extends the interface defined by Abstraction
class AdvancedRemote : public Remote{
    public:
        AdvancedRemote(std::shared_ptr<Device> inputDev): Remote(inputDev){}
        void mute() {
            device->setVolume(0);
            std::cout << "Device muted" << std::endl;
        }
        void setPreset(int channel, int volume) {
            if (!device->isPowered()) {
                device->powerOn();
            }
            device->setChannel(channel);
            device->setVolume(volume);
            std::cout << "Preset applied: Channel " << channel 
                    << ", Volume " << volume << std::endl;
        }
        void voiceControl(const std::string& command) {
            std::cout << "Voice command: \"" << command << "\"" << std::endl;
            
            if (command == "power on") {
                if (!device->isPowered()) device->powerOn();
            } else if (command == "power off") {
                if (device->isPowered()) device->powerOff();
            } else if (command == "louder") {
                volumeUp();
            } else if (command == "quieter") {
                volumeDown();
            } else {
                std::cout << "Voice command not recognized" << std::endl;
            }
        }
};
int main(){
     std::cout << "\n=== Remote Control Bridge Pattern Demo ===\n" << std::endl;
    
    // Create devices
    auto tv = std::make_shared<TV>();
    auto radio = std::make_shared<Radio>();
    
    // Create remote controls
    Remote basicRemote(tv);
    AdvancedRemote advancedRemote(radio);
    
    std::cout << "Using basic remote with TV:" << std::endl;
    std::cout << "Initial state: " << basicRemote.getDeviceInfo() << std::endl;
    
    basicRemote.powerToggle();
    basicRemote.volumeUp();
    basicRemote.channelUp();
    basicRemote.channelUp();
    std::cout << "After operations: " << basicRemote.getDeviceInfo() << std::endl;
    
    std::cout << "\nUsing advanced remote with Radio:" << std::endl;
    std::cout << "Initial state: " << advancedRemote.getDeviceInfo() << std::endl;
    
    advancedRemote.voiceControl("power on");
    advancedRemote.setPreset(107, 60);
    advancedRemote.voiceControl("louder");
    advancedRemote.mute();
    std::cout << "Final state: " << advancedRemote.getDeviceInfo() << std::endl;
    
    std::cout << "\nSwitching advanced remote to control TV:" << std::endl;
    AdvancedRemote tvAdvancedRemote(tv);
    tvAdvancedRemote.voiceControl("power on");
    tvAdvancedRemote.setPreset(25, 40);
    std::cout << "TV state: " << tvAdvancedRemote.getDeviceInfo() << std::endl;
    return 0;
}