#ifndef STATE_H
#define STATE_H

class State
{
private:
    double time;
    double maxTime;
    bool isStart;

public:
    State(double max_time);
    
    bool update(double delta);
    bool is_start();

    void reset();

};

#endif // STATE_H