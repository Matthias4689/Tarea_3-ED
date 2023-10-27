# Buscador de documentos

## Descripción

El denominado "Buscador de Documentos," tiene como objetivo la creación de una aplicación para la gestión y búsqueda de documentos en el contexto del proyecto Gutenberg. Esta aplicación proporcionará a los usuarios la capacidad de explorar una amplia variedad de libros gratuitos y legales disponibles en el proyecto Gutenberg. 

## Cómo compilar y ejecutar

0. Descargar Carpeta con libros a cargar (Se puede ocupar como ejemplo para ejecutar la app) 
  
    ```
    https://drive.google.com/drive/folders/1KwQn19aMauyN1tsbX9PPo-u_xqSXHLO8
    ```

1. Clonar el repositorio:

    ```
    git clone <https://github.com/Matthias4689/Tarea_3-ED.git>

    ```

2. Navegar al directorio del proyecto:

    ```
    cd Tarea_3-ED

    ```

3. Compilar el código:

    ```
    gcc main.c hashmap.c list.c treemap.c -o buscador

    ```

4. Ejecutar la aplicación:

    ```
    ./buscador

    ```


## Funcionalidades

### Funcionando correctamente:

- Cargar documentos: Permite cargar archivos de texto o una carpeta de documentos.
- Mostrar documentos ordenados: Lista libros ordenados por título con detalles de palabras y caracteres.
- Buscar un libro por título: Busca libros por palabras clave en el título.
- Palabras con mayor frecuencia: Muestra las 10 palabras más frecuentes en un libro.
- Palabras más relevantes: Identifica las 10 palabras más relevantes en un libro.

### Problemas conocidos:

- Funciones 6 y 7 no sirven
    - 6: Buscar por palabra: Encuentra libros que contienen una palabra y los ordena por relevancia.
    - 7: Mostrar palabra en contexto: Muestra ocurrencias de una palabra en el contexto de un libro.
- se duplican palabras al guardarlas en el mapa en la función 1.

### A mejorar:

- Agregar una funcion que muestre un resumen del libro.
- Dividir los libros por categorias
- Colocar calificacion a cada libro

## Contribuciones

### Javier Donetch:

- Desarrollo de funciones:
    - Funciones palabras
    - leerDato
    - cargarDocumentos
    - imprimirLibros
  
- Diseño inicial de la interfaz de usuario.
  
- Depuración codigo.
  
- **Auto-evaluación**: 3 (Aporte excelente)

### Matias Romero:

- Desarrollo de funciones:
  - buscarLibroPorTitulo
  - mostrarPalabrasFrecuentes
  - PalabrasPlusRelevant
  
- Documentación y depuración del código.
  
- Redacción del README.
  
- **Auto-evaluación**: 3 (Aporte excelente)



