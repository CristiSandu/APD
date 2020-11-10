/*
 * APD - Tema 1
 * Octombrie 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

char *in_filename_julia;
char *in_filename_mandelbrot;
char *out_filename_julia;
char *out_filename_mandelbrot;
// am definit global variabilele folosite de cei 2 algoritmi
int P;
int width, widthM, height, heightM;
int **result;
int **resultM;

// am definit bariera
pthread_barrier_t barrier;

// structura pentru un numar complex
typedef struct _complex
{
	double a;
	double b;
} complex;

// structura pentru parametrii unei rulari
typedef struct _params
{
	int is_julia, iterations;
	double x_min, x_max, y_min, y_max, resolution;
	complex c_julia;
} params;

params par, parM;

// citeste argumentele programului
void get_args(int argc, char **argv)
{
	if (argc < 6)
	{
		printf("Numar insuficient de parametri:\n\t"
			   "./tema1_par fisier_intrare_julia fisier_iesire_julia "
			   "fisier_intrare_mandelbrot fisier_iesire_mandelbrot <p>\n");
		exit(1);
	}

	in_filename_julia = argv[1];
	out_filename_julia = argv[2];
	in_filename_mandelbrot = argv[3];
	out_filename_mandelbrot = argv[4];
	P = atoi(argv[5]);
}

// citeste fisierul de intrare
void read_input_file(char *in_filename, params *par)
{
	FILE *file = fopen(in_filename, "r");
	if (file == NULL)
	{
		printf("Eroare la deschiderea fisierului de intrare!\n");
		exit(1);
	}

	fscanf(file, "%d", &par->is_julia);
	fscanf(file, "%lf %lf %lf %lf",
		   &par->x_min, &par->x_max, &par->y_min, &par->y_max);
	fscanf(file, "%lf", &par->resolution);
	fscanf(file, "%d", &par->iterations);

	if (par->is_julia)
	{
		fscanf(file, "%lf %lf", &par->c_julia.a, &par->c_julia.b);
	}

	fclose(file);
}

// scrie rezultatul in fisierul de iesire
void write_output_file(char *out_filename, int **result, int width, int height)
{
	int i, j;

	FILE *file = fopen(out_filename, "w");
	if (file == NULL)
	{
		printf("Eroare la deschiderea fisierului de iesire!\n");
		return;
	}

	fprintf(file, "P2\n%d %d\n255\n", width, height);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fprintf(file, "%d ", result[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

// aloca memorie pentru rezultat
int **allocate_memory(int width, int height)
{
	int **result;
	int i;

	result = malloc(height * sizeof(int *));
	if (result == NULL)
	{
		printf("Eroare la malloc!\n");
		exit(1);
	}

	for (i = 0; i < height; i++)
	{
		result[i] = malloc(width * sizeof(int));
		if (result[i] == NULL)
		{
			printf("Eroare la malloc!\n");
			exit(1);
		}
	}

	return result;
}

// elibereaza memoria alocata
void free_memory(int **result, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(result[i]);
	}
	free(result);
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	// implementare algoritm Julia
	//-------------------------------------------------------------------------------------------------
	//calculare parametri de paralelizare pentru algoritmul Julia
	int start = thread_id * (double)width / P;
	int end = fmin((thread_id + 1) * (double)width / P, width);

	int w, h, i, step;
	int *aux;

	//paralelizez primul for dupa start si end
	for (w = start; w < end; w++)
	{
		for (h = 0; h < height; h++)
		{
			step = 0;
			complex z = {.a = w * par.resolution + par.x_min,
						 .b = h * par.resolution + par.y_min};

			while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par.iterations)
			{
				complex z_aux = {.a = z.a, .b = z.b};

				z.a = pow(z_aux.a, 2) - pow(z_aux.b, 2) + par.c_julia.a;
				z.b = 2 * z_aux.a * z_aux.b + par.c_julia.b;

				step++;
			}

			result[h][w] = step % 256;
		}
	}

	//astept ca toate thredurile sa termine de calculat algoritmul
	pthread_barrier_wait(&barrier);

	// calculez parametrii dupa care se face transformarea in coordonate de timp ecran
	int start_tran = thread_id * (double)(height / 2) / P;
	int end_tran = fmin((thread_id + 1) * (double)(height / 2) / P, (height / 2));

	// transforma rezultatul din coordonate matematice in coordonate ecran
	for (i = start_tran; i < end_tran; i++)
	{
		aux = result[i];
		result[i] = result[height - i - 1];
		result[height - i - 1] = aux;
	}

	//astept ca toate thredurile sa termine transformarea in coordonate de tip ecran
	pthread_barrier_wait(&barrier);

	// scriu cu un singur thread in fisier
	if (thread_id == 0)
	{
		write_output_file(out_filename_julia, result, width, height);
	}

	// implementare algoritm Mandelbrot
	//-------------------------------------------------------------------------------------------------
	//calculare parametri de paralelizare pentru algoritmul Julia
	int startM = thread_id * (double)widthM / P;
	int endM = fmin((thread_id + 1) * (double)widthM / P, widthM);

	//paralelizez primul for dupa startM si endM
	for (w = startM; w < endM; w++)
	{
		for (h = 0; h < heightM; h++)
		{
			complex c = {.a = w * parM.resolution + parM.x_min,
						 .b = h * parM.resolution + parM.y_min};
			complex z = {.a = 0, .b = 0};
			step = 0;

			while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < parM.iterations)
			{
				complex z_aux = {.a = z.a, .b = z.b};

				z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + c.a;
				z.b = 2.0 * z_aux.a * z_aux.b + c.b;

				step++;
			}

			resultM[h][w] = step % 256;
		}
	}

	//astept ca toate thredurile sa termine de calculat algoritmul
	pthread_barrier_wait(&barrier);

	// calculez parametrii dupa care se face transformarea in coordonate de timp ecran
	int startM_tran = thread_id * (double)(heightM / 2) / P;
	int endM_tran = fmin((thread_id + 1) * (double)(heightM / 2) / P, (heightM / 2));

	// transforma rezultatul din coordonate matematice in coordonate ecran
	for (i = startM_tran; i < endM_tran; i++)
	{
		aux = resultM[i];
		resultM[i] = resultM[heightM - i - 1];
		resultM[heightM - i - 1] = aux;
	}

	//astept ca toate thredurile sa termine transformarea in coordonate de tip ecran
	pthread_barrier_wait(&barrier);

	// scriu cu un singur thread in fisier
	if (thread_id == 0)
	{
		write_output_file(out_filename_mandelbrot, resultM, widthM, heightM);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int r;
	void *status;
	int i;
	// se citesc argumentele programului
	get_args(argc, argv);

	pthread_t tid[P];
	int thread_id[P];

	// - se citesc parametrii de intrare
	read_input_file(in_filename_julia, &par);

	// - se calculeaza width si height
	width = (par.x_max - par.x_min) / par.resolution;
	height = (par.y_max - par.y_min) / par.resolution;

	// - se aloca memorie pentru primul algoritm
	result = allocate_memory(width, height);

	// - se citesc parametrii de intrare
	read_input_file(in_filename_mandelbrot, &parM);

	// - se calculeaza widthM si heightM
	widthM = (parM.x_max - parM.x_min) / parM.resolution;
	heightM = (parM.y_max - parM.y_min) / parM.resolution;

	// - se aloca memorie pentru primul algoritm
	resultM = allocate_memory(widthM, heightM);

	//barrier init
	if (pthread_barrier_init(&barrier, NULL, P) != 0)
	{
		printf("Error can't initalize barrier");
		return 1;
	}

	for (i = 0; i < P; i++)
	{
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	for (i = 0; i < P; i++)
	{
		r = pthread_join(tid[i], &status);

		if (r)
		{
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}
	// se distruge bariera
	pthread_barrier_destroy(&barrier);

	// - se elibereaza memoria alocata
	free_memory(result, height);
	free_memory(resultM, heightM);

	pthread_exit(NULL);

	return 0;
}
