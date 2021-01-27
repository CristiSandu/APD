#include "helpers.h"

void send_message(int destination_id, void *message, int message_len, int type)
{
    /* Handle integer messaes */
    if (type == INT_MESSAGE) {
        int *payload = (int*) message;
        MPI_Send(payload, 1, MPI_INT, destination_id, 0, MPI_COMM_WORLD);
    }

    /* Handle string messsages */
    if (type == STRING_MESSAGE) {
        char *payload = (char *)message;

        /* Send payload length then payload */
        MPI_Send(&message_len, 1, MPI_INT, destination_id, 0, MPI_COMM_WORLD);
        MPI_Send(payload, message_len, MPI_CHAR, destination_id, 0, MPI_COMM_WORLD);
    }
}

int receive_message(int source_id, void *message, int message_len, int type)
{
    MPI_Status status;

    /* Handle int messages */
    if (type == INT_MESSAGE) {
        int payload_len;
        MPI_Recv(&payload_len, 1, MPI_INT, source_id, 0, MPI_COMM_WORLD, &status);
        message = NULL;
        return payload_len;
    }

    /* Handle string messages */
    if (type = STRING_MESSAGE) {
        MPI_Recv(message, message_len, MPI_CHAR, source_id, 0, MPI_COMM_WORLD, &status);
        return message_len;
    }
}

int get_paragraph(string &paragraph, ifstream &file, int &paragraph_id)
{
    int number_of_lines = 0;
    string line = "";
    paragraph = "";

    do {
        getline (file, line);
        paragraph += line + "\n";
        number_of_lines ++;
    } while (!line.empty() && !file.eof());

    paragraph[paragraph.length() - 1] = '\0';

    if(number_of_lines != 1 && number_of_lines != 0)
        number_of_lines --;


    return number_of_lines;
}

void handle_master(char *input_file)
{
    string in_file_name(input_file);
    fstream in_file;
    in_file.open(in_file_name);

    string line = "";
    string packet = "";
    vector<string> packets;
    getline (in_file, line);
    int lines_num = stoi(line);

    for (int i = 1; i <= lines_num; i++) {
        getline (in_file, line);
        packet += line + "\n";
    }

    int num_packets = break_in_chunks(packets, packet, lines_num / 3 + 1);

    for (int i = 0; i < 3; i++) {
        //cout << packets[i] << endl;
        send_message(i + 1, (void*)packets[i].c_str(), packets[i].length() + 1, STRING_MESSAGE);
    }
    int break_sig = -1;
    for (int i = MAPPER1; i <= MAPPER3; i++)
        send_message(i, &break_sig, 1, INT_MESSAGE);

    in_file.close();
    /* Store in sliding window and print in correct order */
    // pthread_mutex_lock(&lock);
    // sliding_window[paragraph_id] = make_pair(paragraph_type, processed_paragraph);
    // while(sliding_window.find(last_printed) != sliding_window.end()) {
    //    out_file << sliding_window[last_printed].first << "\n" << sliding_window[last_printed].second << "\n";
    //    free(sliding_window[last_printed].second);
    //    sliding_window.erase(last_printed);
    //    last_printed++;
    //}
    //pthread_mutex_unlock(&lock);

    //int length = 5;
    //string message = "hello";
    //send_message(WORKER, (void*)message.c_str(), length, STRING_MESSAGE);
}

void handle_worker(int worker_type)
{
    if (worker_type >= MAPPER1 && worker_type <= MAPPER3) {
        while (true) {
            int length = receive_message(MASTER, NULL, 1, INT_MESSAGE);

            if (length == -1) {
                int break_sig = -1;
                for (int i = REDUCER1; i <= REDUCER2; i++)
                    send_message(i, &break_sig, 1, INT_MESSAGE);
                break;
            };

            char message[length];
            length = receive_message(MASTER, message, length, STRING_MESSAGE);
            string payload(message);

            int vowels = 0;
            int not_vowels = 0;
            for (auto chr : payload) {
                if(is_vowel(chr)) {
                    vowels++;
                }
                else if(isalnum(chr)){
                    not_vowels++;
                }
            }

            cout << payload;
            cout << "Vowels: " << vowels << endl;
            cout << "Not_Vowels: " << not_vowels << endl << endl;

            send_message(REDUCER1, &vowels, 1, INT_MESSAGE);
            send_message(REDUCER2, &not_vowels, 1, INT_MESSAGE);
        }   
    }

    if (worker_type == REDUCER1) {
        int vowels = 0;
        while (true) {
            int recv1 = receive_message(MAPPER1, NULL, 1, INT_MESSAGE);
            int recv2 = receive_message(MAPPER2, NULL, 1, INT_MESSAGE);
            int recv3 = receive_message(MAPPER3, NULL, 1, INT_MESSAGE);

            if (recv1 == -1 && recv2 == -1 && recv3 == -1) {
                cout << "Vowels: " << vowels << endl;
                break;
            }
            if(recv1 != -1)
                vowels += recv1;
            
            if(recv2 != -1)
                vowels += recv2;
                
            if(recv3 != -1)
                vowels += recv3;
        }
    }

    if (worker_type == REDUCER2) {
       int not_vowels = 0;
        while (true) {
            int recv1 = receive_message(MAPPER1, NULL, 1, INT_MESSAGE);
            int recv2 = receive_message(MAPPER2, NULL, 1, INT_MESSAGE);
            int recv3 = receive_message(MAPPER3, NULL, 1, INT_MESSAGE);

            if (recv1 == -1 && recv2 == -1 && recv3 == -1) {
                cout << "Not_Vowels: " << not_vowels << endl;
                break;
            }
            if(recv1 != -1)
                not_vowels += recv1;
            
            if(recv2 != -1)
                not_vowels += recv2;
                
            if(recv3 != -1)
                not_vowels += recv3;
        }
    }
}

int break_in_chunks(vector<string>& chunks, string &paragraph, int chunk_size)
{
    string chunk = "";
    string line;
    stringstream check1(paragraph);
    int count = 0;

    while(true) {
        getline(check1, line, '\n');

        if(check1.eof()) {
            chunk += line;
            chunks.push_back(chunk);
            break;
        } else {
            count++;
            chunk += line + "\n";
            if (count == chunk_size) {
                chunks.push_back(chunk);
                chunk = "";
                count = 0;
            }
        }
    }

    return chunks.size();
}

bool is_vowel(char letter)
{
    if (letter == 'a' || letter == 'e' || letter == 'i' ||
            letter == 'o' || letter == 'u')
        return true;

    if (letter == 'A' || letter == 'E' || letter == 'I' ||
            letter == 'O' || letter == 'U')
        return true;

    return false;
}
