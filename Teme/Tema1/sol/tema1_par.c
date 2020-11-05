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
int P;
int width, widthM, height, heightM;
int **result;
int **resultM;

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

// ruleaza algoritmul Julia
void run_julia(params *par, int **result, int width, int height)
{
	int w, h, i;

	for (w = 0; w < width; w++)
	{
		for (h = 0; h < height; h++)
		{
			int step = 0;
			complex z = {.a = w * par->resolution + par->x_min,
						 .b = h * par->resolution + par->y_min};

			while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par->iterations)
			{
				complex z_aux = {.a = z.a, .b = z.b};

				z.a = pow(z_aux.a, 2) - pow(z_aux.b, 2) + par->c_julia.a;
				z.b = 2 * z_aux.a * z_aux.b + par->c_julia.b;

				step++;
			}

			result[h][w] = step % 256;
		}
	}

	// transforma rezultatul din coordonate matematice in coordonate ecran
	for (i = 0; i < height / 2; i++)
	{
		int *aux = result[i];
		result[i] = result[height - i - 1];
		result[height - i - 1] = aux;
	}
}

// ruleaza algoritmul Mandelbrot
void run_mandelbrot(params *par, int **result, int width, int height)
{
	int w, h, i;

	for (w = 0; w < width; w++)
	{
		for (h = 0; h < height; h++)
		{
			complex c = {.a = w * par->resolution + par->x_min,
						 .b = h * par->resolution + par->y_min};
			complex z = {.a = 0, .b = 0};
			int step = 0;

			while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par->iterations)
			{
				complex z_aux = {.a = z.a, .b = z.b};

				z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + c.a;
				z.b = 2.0 * z_aux.a * z_aux.b + c.b;

				step++;
			}

			result[h][w] = step % 256;
		}
	}

	// transforma rezultatul din coordonate matematice in coordonate ecran
	for (i = 0; i < height / 2; i++)
	{
		int *aux = result[i];
		result[i] = result[height - i - 1];
		result[height - i - 1] = aux;
	}
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	//int start = thread_id * (double)N / P;
	//int end = fmin((thread_id + 1) * (double)N / P, N);
	run_julia(&par, result, width, height);

	run_mandelbrot(&par, result, width, height);

	printf("%f %d %d \n", par.c_julia.a, par.is_julia, par.iterations);
	write_output_file(out_filename_julia, result, width, height);

	printf("%f %d %d \n", parM.c_julia.a, parM.is_julia, parM.iterations);

	printf("%d\n", thread_id);
	write_output_file(out_filename_mandelbrot, resultM, widthM, heightM);

	pthread_exit(NULL);
}
/*
void *thread_function_Mad(void *arg)
{
	int thread_id = *(int *)arg;

	//int start = thread_id * (double)N / P;
	//int end = fmin((thread_id + 1) * (double)N / P, N);
	printf("%f %d %d \n", parM.c_julia.a, parM.is_julia, parM.iterations);

	printf("%d\n", thread_id);
	write_output_file(out_filename_mandelbrot, resultM, widthM, heightM);
	pthread_exit(NULL);
}
*/
int main(int argc, char *argv[])
{
	/*params par;
	int width, height;
	int **result;*/

	int r;

	void *status;
	int i;
	// se citesc argumentele programului
	get_args(argc, argv);

	pthread_t tid[P];
	int thread_id[P];

	read_input_file(in_filename_julia, &par);
	width = (par.x_max - par.x_min) / par.resolution;
	height = (par.y_max - par.y_min) / par.resolution;

	result = allocate_memory(width, height);

	//run_julia(&par, result, width, height);
	//	write_output_file(out_filename_julia, result, width, height);

	read_input_file(in_filename_mandelbrot, &parM);

	widthM = (parM.x_max - parM.x_min) / parM.resolution;
	heightM = (parM.y_max - parM.y_min) / parM.resolution;

	resultM = allocate_memory(widthM, heightM);
	//run_mandelbrot(&par, result, width, height);
	//write_output_file(out_filename_mandelbrot, resultM, widthM, heightM);

	//barrier init
	if (pthread_barrier_init(&barrier, NULL, P) != 0)
	{
		printf("Error can't initalize barrier");
		return 1;
	}

	// start thread
	//printf("%d ", P);
	for (i = 0; i < P; i++)
	{

		thread_id[i] = i;
		printf("%d ", thread_id[i]);
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
		//	pthread_create(&tid[i], NULL, thread_function_Mad, &thread_id[i]);
	}
	//printf("A iesit !!!1  %d\n ", P);
	// se asteapta thread-urile
	for (i = 0; i < P; i++)
	{
		//printf("A intrat !!!1  %ld\n ", i);

		r = pthread_join(tid[i], &status);
		//r = pthread_join(tid[i], &status);

		if (r)
		{
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}
	pthread_barrier_destroy(&barrier);

	free_memory(result, height);
	free_memory(resultM, heightM);

	pthread_exit(NULL);
	//pthread_mutex_destroy(&mutex);

	// Julia:
	// - se citesc parametrii de intrare
	// - se aloca tabloul cu rezultatul
	// - se ruleaza algoritmul
	// - se scrie rezultatul in fisierul de iesire
	// - se elibereaza memoria alocata
	/*	read_input_file(in_filename_julia, &par);

	width = (par.x_max - par.x_min) / par.resolution;
	height = (par.y_max - par.y_min) / par.resolution;

	result = allocate_memory(width, height);
	run_julia(&par, result, width, height);
	write_output_file(out_filename_julia, result, width, height);
	free_memory(result, height);

	// Mandelbrot:
	// - se citesc parametrii de intrare
	// - se aloca tabloul cu rezultatul
	// - se ruleaza algoritmul
	// - se scrie rezultatul in fisierul de iesire
	// - se elibereaza memoria alocata
	read_input_file(in_filename_mandelbrot, &par);

	width = (par.x_max - par.x_min) / par.resolution;
	height = (par.y_max - par.y_min) / par.resolution;

	result = allocate_memory(width, height);
	run_mandelbrot(&par, result, width, height);
	write_output_file(out_filename_mandelbrot, result, width, height);
	free_memory(result, height);
*/
	return 0;
}
