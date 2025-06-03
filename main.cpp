#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, number;

    // Inicializa el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtiene el identificador del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtiene el número total de procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verifica que haya al menos 2 procesos
    if (size < 2) {
        if (rank == 0) {
            printf("Error: se requieren al menos 2 procesos para esta actividad.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Comunicación punto a punto
    if (rank == 0) {
        // Proceso 0: emisor
        number = 100;  // Valor a enviar
        printf("Proceso 0: enviando el número %d al proceso 1...\n", number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Proceso 0: envío completado.\n");
    } else if (rank == 1) {
        // Proceso 1: receptor
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso 1: recibió el número %d desde el proceso 0.\n", number);
    }

    // Finaliza el entorno MPI
    MPI_Finalize();

    return 0;
}
