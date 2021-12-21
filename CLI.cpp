#include "CLI.h"

enum COMMAND {
    UPLOAD_CSV = 1,
    ALG_SETTINGS = 2,
    DETECT_ANOMALIES = 3,
    DISPLAY_RESULTS = 4,
    UPLOAD_AND_ANALYZE = 5,

};

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->detector = new HybridAnomalyDetector();
    this->inputFile = new ifstream("./input.txt");
    this->report = new vector<AnomalyReport>();
    vector<Command *> commands = {
        new uploadTS(dio, inputFile),
        new algSettings(dio, detector, inputFile),
        new detectAnomaly(dio, detector, &(this->report)),
        new displayResults(dio, &(this->report)),
        new uploadAndAnalyze(dio)
    };
    this->commands = commands;
}

void CLI::start(){
    while (true) {
        printMenu();
        string command;
        getline(*inputFile, command);
        int commandType = stoi(command);
        bool exit = false;
        switch(commandType) {
            case UPLOAD_CSV: {
                commands[UPLOAD_CSV - 1]->execute();
            } break;
            case ALG_SETTINGS: {
                commands[ALG_SETTINGS - 1]->execute();
            } break;
            case DETECT_ANOMALIES: {
                commands[DETECT_ANOMALIES - 1]->execute();
            } break;
            case DISPLAY_RESULTS: {
                commands[DISPLAY_RESULTS - 1]->execute();
            } break;
            case UPLOAD_AND_ANALYZE: {
                commands[UPLOAD_AND_ANALYZE - 1]->execute();
            } break;
            default:
                exit = true;
                break;
        }
        if (exit) {
            break;
        }
    }
}

void CLI::printMenu() {
    cout << "Welcome to the Anomaly Detection Server.\nPlease choose an option:\n"; 
    cout << "1. upload a time series csv file\n";
    cout << "2. algorithm settings\n";
    cout << "3. detect anomalies\n";
    cout << "4. display results\n";
    cout << "5. upload anomalies and analyze results\n";
    cout << "6. exit\n";
}

CLI::~CLI() {
}

