
# Instrucciones para Compilar y Ejecutar un Programa en C++ desde Visual Studio Code

1. **Abrir la Terminal:**
   - En Visual Studio Code, abre la terminal presionando `` Ctrl + ` `` o navegando a `Terminal > New Terminal` en el menú superior.

2. **Navegar a la Carpeta del Proyecto:**
   - Asegúrate de que estás en la carpeta donde se encuentra el archivo que deseas compilar. 
   - Puedes verificar tu ubicación actual con el comando `pwd` (en Linux/Mac) o `cd` (en Windows). 
   - Si necesitas cambiar de directorio, usa `cd nombre_de_la_carpeta`.

   **Ejemplo:**
   ```bash
   cd RepasoFunda
   ```

3. **Compilar el Archivo C++:**
   - Utiliza el siguiente comando para compilar tu archivo y generar un archivo ejecutable:

   ```bash
   g++ -o nombre_ejecutable nombre_archivo.cc
   ```

   **Ejemplo:**
   ```bash
   g++ -o array_example array_example.cc
   ```

   - Este comando crea un archivo ejecutable llamado `array_example` a partir del código fuente `array_example.cc`.

4. **Ejecutar el Programa:**
   - Si la compilación fue exitosa y no hubo errores, ejecuta el programa con el siguiente comando:

   ```bash
   ./nombre_ejecutable
   ```

   **Ejemplo:**
   ```bash
   ./array_example
   ```

   - Esto correrá el programa y mostrará la salida en la terminal.
