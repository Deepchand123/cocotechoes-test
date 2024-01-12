#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;

// Class to represent a task
class Task {
public:
    int progress;
    int endDate;
    Task(): progress(0), endDate(0) {}
};

// Class to represent a job
class Job {
public:
    string title;
    vector<Task> tasks;
    Job(const string& t) : title(t) {}
};
int generateRandomNumber(int min, int max) {
    return rand() % (max - min) + min;
}

void generateRandomTasks(Job& job) {
    int numTasks = generateRandomNumber(10, 20); 
    job.tasks.resize(numTasks);

    for (Task& task : job.tasks) {
        task.progress = generateRandomNumber(0, 100);
        task.endDate = generateRandomNumber(1, 30); // Assuming a month
    }
}

double calculateOverallProgress(const Job& job) {
    if (job.tasks.empty()) {
        return 0.0;
    }
    double totalProgress = 0.0;
    for (const Task& task : job.tasks) {
        totalProgress += task.progress;
    }

    return totalProgress / job.tasks.size();
}

bool compareJobs(const Job& job1, const Job& job2) {
    if (job1.tasks.empty() || job2.tasks.empty()) {
        return false;
    }

    return make_pair(job1.tasks.back().endDate, calculateOverallProgress(job1))
        < make_pair(job2.tasks.back().endDate, calculateOverallProgress(job2));
}

int main(){
    int numJobs=10;
    vector<Job>jobs;

    for (int i=1; i<=numJobs; i++){
        Job job("Job " + to_string(i));
        generateRandomTasks(job);
        jobs.push_back(job);
    }

    sort(jobs.begin(), jobs.end(), compareJobs);

    for (Job& job:jobs){
        cout<<"Job Title: "<<job.title<<"\t Number of Tasks: "<<job.tasks.size()
                  << "\t Expected End Date: "<<job.tasks.back().endDate
                  << "\t Overall Progress: "<<calculateOverallProgress(job)<<"%" <<endl;
    }

    return 0;
}
