#include <mpi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void *thread_function_citire(void *arg)
{
    int thread_id = *(int *)arg;

    ifstream myFile;

    myFile.open("myFile.txt");
    string STRING;
    vector<string> values;
    string comedy_str = "comedy";
    string fantasy_str = "fantasy";
    string SF_str = "science-fiction";
    string horror_str = "horror";

    int horror = 0;
    int comedy = 0;
    int fantasy = 0;
    int SF = 0;

    int size_vec = 0;
    int size_string = 0;

    while (!myFile.eof()) // To get you all the lines.
    {
        getline(myFile, STRING); // Saves the line in STRING.
        //cout << STRING << thread_id << endl;
        switch (thread_id)
        {
        case 0:
            // cout << STRING << " " << thread_id << endl;

            if (STRING == comedy_str ||
                STRING == fantasy_str ||
                STRING == SF_str)
            {
                horror = 0;
                size_vec = values.size();
                cout << STRING << endl;
                MPI_Send(&size_vec, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                for (int i = 0; i < values.size(); i++)
                {
                    size_string = values[i].size();
                    MPI_Send(&size_string, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(values[i].c_str(), values[i].size(), MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD);
                }
            }

            printf("%s", STRING.c_str());
            if (!strcmp(STRING.c_str(), "horror"))
            {
                horror = 1;
                cout << horror << endl;
            }
            break;

        case 1:
            //cout << STRING << " " << thread_id << endl;

            if (STRING == horror_str ||
                STRING == fantasy_str ||
                STRING == SF_str)
            {
                comedy = 0;
                size_vec = values.size();
                MPI_Send(&size_vec, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                for (int i = 0; i < values.size(); i++)
                {
                    size_string = values[i].size();
                    MPI_Send(&size_string, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(values[i].c_str(), values[i].size(), MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD);
                }
            }
            else if (STRING == comedy_str)
            {
                comedy = 1;
            }
            break;

        case 2:
            //cout << STRING << " " << thread_id << endl;

            if (STRING == comedy_str ||
                STRING == horror_str ||
                STRING == SF_str)
            {
                fantasy = 0;
                size_vec = values.size();
                MPI_Send(&size_vec, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                for (int i = 0; i < values.size(); i++)
                {
                    size_string = values[i].size();
                    MPI_Send(&size_string, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(values[i].c_str(), values[i].size(), MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD);
                }
            }
            else if (STRING == fantasy_str)
            {
                fantasy = 1;
            }
            break;

        case 3:
            //cout << STRING << " " << thread_id << endl;

            if (STRING == comedy_str ||
                STRING == horror_str ||
                STRING == fantasy_str)
            {
                SF = 0;
                size_vec = values.size();
                MPI_Send(&size_vec, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                for (int i = 0; i < values.size(); i++)
                {
                    size_string = values[i].size();
                    MPI_Send(&size_string, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(values[i].c_str(), values[i].size(), MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD);
                }
            }
            else if (STRING == SF_str)
                SF = 1;
            break;
        default:
            break;
        }
        /*cout << "Val sf " << SF << endl;
        cout << "fantasy " << fantasy << endl;
        cout << "comedy " << comedy << endl;
        cout << "horror " << horror << endl;*/
        if (SF == 1 || fantasy == 1 || comedy == 1 || horror == 1)
        {
            cout << "Send to " << thread_id << endl;
            values.push_back(STRING);
            //cout << STRING << endl; // Prints our STRING.
        }
    }

    myFile.close();
    /*
        int start = thread_id * (double)N / P;
        int end = fmin((thread_id + 1) * (double)N / P, N);
        int i, k, aux, start_imp, start_par;
    */

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int rank;
    int nProcesses;
    int provided;
    int P = 4;

    MPI_Init_thread(&argc, (char ***)&argv, MPI_THREAD_MULTIPLE, &provided);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    printf("Hello from %i/%i\n", rank, nProcesses);
    //int *a = (int *)malloc(sizeof(int) * (nProcesses - 1));
    if (rank == 0)
    { // This code is run by a single process
        pthread_t tid[P];
        int thread_id[P];
        int i;
        for (i = 0; i < P; i++)
        {
            thread_id[i] = i;
            pthread_create(&tid[i], NULL, thread_function_citire, &thread_id[i]);
        }

        for (i = 0; i < P; i++)
        {
            pthread_join(tid[i], NULL);
        }
    }
    else
    {

        MPI_Status status;
        int size_vect;
        int size_string;

        vector<string> vect_string;

        MPI_Recv(&size_vect, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        for (int i = 0; i < size_vect; i++)
        {
            MPI_Recv(&size_string, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            char *str_main = (char *)malloc(sizeof(char) * size_string);

            MPI_Recv(&str_main, size_string, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
            vect_string.push_back(str_main);
            //cout << str_main << endl;
        }

        switch (rank)
        {
        case 1:
            for (int i = 0; i < vect_string.size(); i++)
            {
                cout << vect_string[i] << endl;
            }
            break;

        case 2:
            for (int i = 0; i < vect_string.size(); i++)
            {
                cout << vect_string[i] << endl;
            }
            break;

        case 3:
            for (int i = 0; i < vect_string.size(); i++)
            {
                cout << vect_string[i] << endl;
            }
            break;

        case 4:
            for (int i = 0; i < vect_string.size(); i++)
            {
                cout << vect_string[i] << endl;
            }
            break;
        default:
            break;
        }
    }

    MPI_Finalize();
    return 0;
}
