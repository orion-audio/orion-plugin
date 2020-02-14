#include <string>

class Note
{
public:
    Note()
    {
        pitch = 60;
        velocity = 100;
        startTime = 0;
        endTime = 1;

    }

    Note(int p, int v, double start, double end)
    {
        pitch = p;
        velocity = v;
        startTime = start;
        endTime = end;
    }

    std::string toString()
    {
        std::string s("");
        s+="{\n\tpitch: " + std::to_string(pitch) + "\n";
        s+="\tvelocity: " + std::to_string(velocity) + "\n";
        s+="\tstart_time: " + std::to_string(startTime) + "\n";
        s+="\tend_time: " + std::to_string(endTime) + "\n}\n";

        return s;
    }


    int pitch;
    int velocity;

    int startTime;
    int endTime;

};
