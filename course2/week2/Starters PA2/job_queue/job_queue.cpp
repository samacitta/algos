#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  // structure used for worker threads
  struct Worker {
      long long avail_start_time;
      int id;
      Worker() { };                      // default constructor
      Worker(long long x, int y) {       // constructor
          avail_start_time = x;
          id = y;
      }
  };

  // comparator used for min priority queue
  struct compare {
      bool operator()(const Worker& l, const Worker& r) {
          if (l.avail_start_time != r.avail_start_time)
              return l.avail_start_time > r.avail_start_time;
          else
              return l.id > r.id;
      }
  };

  // vectors used for storing output
  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    // initializer a priority queue containing all worker threads
    priority_queue<Worker, vector<Worker>, compare> pq;
    for (int i = 0; i < num_workers_ ; ++i) {
        pq.emplace(Worker(0, i));
    }

    // process jobs - read a job and process using next available Worker from
    // the priority queue
    for (int i = 0; i < jobs_.size(); ++i) {
        Worker next = pq.top();     // get next available worker
        pq.pop();                   // remove Worker from queue
        assigned_workers_[i] = next.id;
        start_times_[i] = next.avail_start_time;
        // place worker back on queue with new avail start time
        pq.emplace(Worker(next.avail_start_time+jobs_[i], next.id));
    }

    /*
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
    */
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
