class opMode {
public:
    String description;
    int maxIdlePeriod;

    opMode(String desc, int idle) : description(desc), maxIdlePeriod(idle) {}
};