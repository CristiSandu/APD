#ifndef HELPERS_H
#define HELPERS_H

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <pthread.h>

using namespace std;

#define MASTER_THREADS_COUNT 4

enum MPI_NODES {
    MASTER,
    MAPPER1,
    MAPPER2,
    MAPPER3,
    REDUCER1,
    REDUCER2,
};

enum MESSAGE_TYPES {
    INT_MESSAGE,
    STRING_MESSAGE
};

extern map<int, pair<string, char*>> sliding_window;
extern int last_printed;
extern ofstream out_file;
extern pthread_mutex_t lock;
extern pthread_barrier_t barrier;
extern int cores;
extern vector<string>chunks;

void send_message(int destination_id, void *message, int message_len, int type);
int receive_message(int source_id, void *message, int message_len, int type);

void handle_master(char *input_file);
void handle_worker(int worker_type);

int get_paragraph(string &paragraph, ifstream &file, int &paragraph_id);
int break_in_chunks(vector<string>& chunks, string &paragraph, int chunk_size);
bool is_vowel(char letter);

#endif