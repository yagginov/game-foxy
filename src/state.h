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

    double get_current_time() const;
    double get_max_time() const;

    void reset();

};

#endif // STATE_H