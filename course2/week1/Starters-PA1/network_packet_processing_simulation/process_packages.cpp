#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        buff_size(size),
        finish_time()
    {}

    Response Process(const Request &request) {
        // write your code here
        // first, remove items from queue that have finished processing
        // by the time the current request arrives
        while (!finish_time.empty()) {
            if (finish_time.front() <= request.arrival_time)
                finish_time.pop();
            else
                break;
        }

        // if space available in queue, add new request
        if (finish_time.size() < buff_size) {
            int new_finish_time, new_start_time;
            if (finish_time.empty()) {
                new_start_time = request.arrival_time;
            } else {
                new_start_time = finish_time.back();
            }
            new_finish_time = new_start_time + request.process_time;
            finish_time.push(new_finish_time);
            return Response(false, new_start_time);
        } else {    // no space, drop request
            return Response(true, -1);
        }
    }
private:
    int buff_size;
    std::queue <int> finish_time;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
