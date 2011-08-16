#ifndef STATE_NAME_8C8LYUEG
#define STATE_NAME_8C8LYUEG

#include <state.h>

class StateName : public Baukasten::Core::State {
public:
    StateName( Entity &parent, const std::string& );
    virtual ~StateName();

    const std::string getName() const;
    void setName( const std::string& );

private:
    std::string mUnitName;
};

class StateLevel : public Baukasten::Core::State {
public:
    StateLevel( Entity&, const int );
    virtual ~StateLevel();

    int getLevel() const;
    void levelUp();

private:
    int mLevel;
};

class StateExperience : public Baukasten::Core::State {
public:
    StateExperience( Entity &, const int );
    virtual ~StateExperience();

    int getExperience() const;

    void addExperience( int );

private:
    int mExperience;
};

#endif /* end of include guard: STATE_NAME_8C8LYUEG */
