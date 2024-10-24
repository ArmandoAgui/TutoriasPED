#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Estructura para representar un trabajo de impresión
struct PrintJob {
    int jobId;
    string fileName;
    int numPages;
};

// Función para agregar un trabajo de impresión a la cola
void addPrintJob(queue<PrintJob>& printQueue, int jobId, string fileName, int numPages) {
    PrintJob newJob;
    newJob.jobId = jobId;       // Asignar directamente el ID del trabajo
    newJob.fileName = fileName; // Asignar el nombre del archivo
    newJob.numPages = numPages; // Asignar el número de páginas
    printQueue.push(newJob);
    cout << "Trabajo agregado a la cola: " << fileName << " con " << numPages << " páginas." << endl;
}

// Función para procesar trabajos de impresión
void processPrintJobs(queue<PrintJob>& printQueue) {
    if (printQueue.empty()) {
        cout << "No hay trabajos en la cola para procesar." << endl;
        return;
    }

    while (!printQueue.empty()) {
        PrintJob currentJob = printQueue.front();
        printQueue.pop();
        cout << "Procesando trabajo " << currentJob.jobId << ": " << currentJob.fileName << " (" << currentJob.numPages << " páginas)" << endl;
    }
    cout << "Todos los trabajos han sido procesados." << endl;
}

// Función para imprimir el contenido de la cola sin procesarlo
void showPrintQueue(const queue<PrintJob>& printQueue) {  // Cambié el nombre de la función a 'showPrintQueue'
    if (printQueue.empty()) {
        cout << "La cola de impresión está vacía." << endl;
        return;
    }

    cout << "\n=== Contenido de la Cola de Impresión ===" << endl;

    // Crear una copia temporal de la cola para no modificar la original
    queue<PrintJob> tempQueue = printQueue;
    
    while (!tempQueue.empty()) {
        PrintJob currentJob = tempQueue.front();
        cout << "Trabajo " << currentJob.jobId << ": " << currentJob.fileName << " (" << currentJob.numPages << " páginas)" << endl;
        tempQueue.pop();
    }
}

int main() {
    queue<PrintJob> printQueue;  // Cola para gestionar los trabajos de impresión
    int option, jobId = 1;
    string fileName;
    int numPages;

    do {
        cout << "\n=== Sistema de Cola de Impresión ===" << endl;
        cout << "1. Agregar trabajo de impresión" << endl;
        cout << "2. Procesar trabajos de impresión" << endl;
        cout << "3. Mostrar trabajos en cola" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Ingresa el nombre del archivo: ";
                cin >> fileName;
                cout << "Ingresa el número de páginas: ";
                cin >> numPages;
                addPrintJob(printQueue, jobId, fileName, numPages);
                jobId++;  // Incrementa el ID para cada nuevo trabajo
                break;
            case 2:
                processPrintJobs(printQueue);
                break;
            case 3:
                showPrintQueue(printQueue);  // Llamo la función 'showPrintQueue' en lugar de 'printQueue'
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Intenta de nuevo." << endl;
        }
    } while (option != 4);

    return 0;
}
