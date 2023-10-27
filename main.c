//Librerías y archivos a usar.
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "hashmap.h"
#include "list.h"
#include "treemap.h"

// Estructura de una Palabra.
typedef struct {
    char palabra[101];
    int apariciones;
} Palabra;

// Estructura de un Libro.
typedef struct Libro {
    char nombreID[101];
    char titulo[101];
    int contadorPalabras;
    int contadorCaracteres;
    HashMap* contenido;
} Libro;

//Definición de funciones.
int lower_than_string(void *key1, void *key2);
void imprimirMenu();
void leerDato(char dato[101]);
int isStopWord(char *word);
void strtrim(char *str);
int cargarDocumentos(const char *carpeta, TreeMap *arbolLibros);
void imprimirLibros(TreeMap *arbolLibros);
void buscarLibrosPorPalabras(TreeMap *arbolLibros, char *palabras);
Libro *buscarLibroPorTitulo(TreeMap *arbolLibros, const char *titulo);
void mostrarPalabrasFrecuentes(Libro *libro);
void PalabrasPlusRelevant(Libro *libro);
void BuscarPorPalabra(TreeMap *arbolLibros, const char *palabra);

//arreglo de palabras que no almacenar.
char *stopWords[] = {
    "a", "about", "above", "across", "after", "again", "against", "all", "almost", "alone", "along", "already", "also", "although", "always", "among",
    "an", "and", "another", "any", "anybody", "anyone", "anything", "anywhere", "are", "area", "areas", "around", "as", "ask", "asked", "asking", "asks",
    "at", "away", "before", "behind", "being", "between", "but", "by", "could", "did", "do", "does", "down", "during", "each", "even", "ever",
    "every", "for", "from", "has", "have", "he", "her", "here", "herself", "him", "himself", "his", "how", "however", "i", "if", "in", "is",
    "it", "its", "itself", "just", "me", "more", "most", "mr", "mrs", "my", "myself", "no", "nobody", "non", "noone", "not", "of", "on", "one",
    "only", "or", "other", "others", "our", "out", "over", "said", "same", "she", "should", "so", "some", "such", "than", "that", "the", "their",
    "them", "then", "there", "these", "they", "this", "those", "though", "to", "too", "was", "we", "were", "what", "when", "where", "which",
    "who", "why", "will", "with", "you", "your", "yours"
};
//Función main.
int main(int argc, char *argv[]) {
  //Definición de opción del menu.
  int menu;
  //Creacion de arbol libros.
  TreeMap *arbolLibros = createTreeMap(lower_than_string);
  //Ciclo menu.
  do {
    
    imprimirMenu();
    printf("\n");
    printf("Ingrese una opción: ");
    scanf("%i", &menu);
    
    if (menu > 8 || menu < 0) {
      printf("Escriba un número válido\n");
      } else {
        switch (menu) {
          //Primera Función, carga de libros desde carpeta señalada.
          case 1: {
            char nombreCarpeta[101];
            getchar();
            printf("Ingrese nombre de la carpeta: ");
            leerDato(nombreCarpeta);
            cargarDocumentos(nombreCarpeta, arbolLibros);
            break;
          }
          //Segunda función, imprimir libros cargados en orden alfabetico, con su cantidad de caracteres y palabras.
          case 2: {
            getchar();
            printf("========================================\n");
            imprimirLibros(arbolLibros);
            printf("========================================\n");
            break;
          }
          //Tercera función, buscar libros por palabras en su titulo.
          case 3: {
            printf("========================================\n");
            char tituloBuscado[256];
            getchar();
            printf("Ingrese del nombre del libro a buscar: ");
            leerDato(tituloBuscado);
            tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0'; // Eliminar el carácter de nueva línea si está presente
            buscarLibrosPorPalabras(arbolLibros, tituloBuscado);
            printf("========================================\n");
            break;
          }
          //Cuarta función, muestra palabras más frecuentes en un libro.
          case 4: {
            char tituloBuscado[101];
            getchar();
            printf("Ingrese el título del libro cuyo contenido desea mostrar: ");
            leerDato(tituloBuscado);
            Pair *libro = searchTreeMap(arbolLibros, tituloBuscado);
            if (libro != NULL) {
            mostrarPalabrasFrecuentes(libro->value);  
            } else  printf("Libro no encontrado.\n");      
            free(libro);
            break;
          }
          //Quinta función, mostrar 10 palabras más relevantes de un libro.
          case 5:{
            getchar();
            printf("¿Desea ver las 10 palabras más relevantes?\n");
            printf("Ingrese el título del libro: ");
            char tituloBuscado[101];
            leerDato(tituloBuscado);
            Pair *libro = searchTreeMap(arbolLibros, tituloBuscado);
            if (libro != NULL) {
              PalabrasPlusRelevant(libro->value);  
            } else  printf("Libro no encontrado.\n");      
            free(libro);
            break;
          } 
          //Sexta función, buscar libros por palabras más relevantes.
          case 6:{
          /*getchar();
            printf("Ingrese la palabra que desea buscar en los libros: ");
            char palabraBuscada[101];
            leerDato(palabraBuscada);
            BuscarPorPalabra(arbolLibros, palabraBuscada);*/
            break;
          } 
          //Septima funcion, mostrar contexto de palabras de un libro.
          case 7:{
          /*getchar();
            printf("Ingrese el título del libro: ");
            char tituloBuscado[101];
            leerDato(tituloBuscado);
            printf("Ingrese la palabra que desea buscar en el libro: ");
            char palabraBuscada[101];
            leerDato(palabraBuscada);
            MostrarPalabraEnContexto(arbolLibros, tituloBuscado, palabraBuscada);*/
            break;
          }
        }
      }
    printf("\n");
  //Fin del ciclo pata el menu
  } while (menu != 8);
  printf("FIN DEL PROGRAMA\n");
  return 0;
  //FIN MAIN
}

//Función para comparar un string.
int lower_than_string(void *key1, void *key2) {
  char *k1 = (char *)key1;
  char *k2 = (char *)key2;
  return strcmp(k1, k2) < 0;
}

//Función para imprimir menu.
void imprimirMenu() {
  printf("Por favor ingrese el número de la función deseada\n");
  printf("1. Registrar carpeta libros\n");
  printf("2. Mostrar libros en orden por título\n");
  printf("3. Buscar Palabras en Titulo\n");
  printf("4. Palabras Con Mayor Frecuencia\n");
  printf("5. Palabras Más Relevantes\n");
  printf("6. Buscar Por Palabra (NO HABILITADA)\n");
  printf("7. Mostrar Palabra y Su Contexto (NO HABILITADA)\n");
  printf("8. Salir del programa\n");
}
//Función para leer datos
void leerDato(char cadena[101]) {
  scanf("%100[^\n]s", cadena);
  int largo = strlen(cadena);
  if (largo > 100) {
    printf("No se ha podido registrar\n");
  }
  getchar();
}
//Funcion para comparar palabra con listas de palabras (de parada) a no guardar.
int isStopWord(char *word) {
  int numStopWords = sizeof(stopWords) / sizeof(stopWords[0]);
  for (int i = 0; i < numStopWords; i++) {
    if (strcasecmp(stopWords[i], word) == 0) {
      return 1; // Es una palabra de parada
    }
  }
  return 0; // No es una palabra de parada
}

// Funcion para eliminar espacio al inicio y al final de un string
void strtrim(char *str) {
  int start = 0;
  while (isspace(str[start])) {
    start++;
  }
  int end = strlen(str) - 1;
  while (end > start && isspace(str[end])) {
    end--;
  }
  if (start > 0 || end < (int)strlen(str) - 1) {
    memmove(str, str + start, (end - start + 1));
    str[end - start + 1] = '\0';
  }
}

//Función para revisar si hay que eliminar un caracter no alfanumerico o espacio.
int hayQueEliminar(char c) {
  // Verificar si el carácter no es una letra ni un espacio en blanco
  return !(isalpha(c) || isspace(c));
}
//Funcion para elimina caracteres no alfanumericos y espacios.
char* quitar_caracteres(char* string) {
  int i, j;
  for (i = 0; string[i] != '\0'; i++) {
    if (hayQueEliminar(string[i])) {
      for (j = i; string[j] != '\0'; j++) {
        string[j] = string[j + 1];
      }
      i--; // Retroceder un paso para volver a verificar el nuevo carácter en la misma posición
    }
  }
  return string;
}

//Función para cargar libros desde una carpeta
int cargarDocumentos(const char *carpeta, TreeMap *arbolLibros) {
  int filecount = 0; // Contador de archivos procesados
  printf("========================================\n");
  printf("Cargando documentos...\n");

  DIR *dir;
  struct dirent *entry;
  dir = opendir(carpeta);

  if (dir == NULL) {
    printf("No se pudo abrir la carpeta.\n");
    return 0;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt") != NULL) {
      // Construir la ruta completa del archivo
      char nombreArchivo[256];
      sprintf(nombreArchivo, "%s/%s", carpeta, entry->d_name);

      // Abrir el archivo
      FILE *archivo = fopen(nombreArchivo, "r");
      if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        continue;
      }

      // Crear una estructura Libro para almacenar la información del libro
      Libro *nuevoLibro = (Libro *)malloc(sizeof(Libro));
      if (nuevoLibro == NULL) {
        printf("Error al asignar memoria para el libro.\n");
        return 0;
      }

      // Inicializar campos del Libro
      nuevoLibro->contenido = createMap(100);
      nuevoLibro->contadorPalabras = 0;
      nuevoLibro->contadorCaracteres = 0;

      // Obtener el ID del libro desde el nombre del archivo
      char id[101];
      snprintf(id, sizeof(id), "%s", entry->d_name);
      char *dot = strrchr(id, '.');
      if (dot != NULL) {
        *dot = '\0'; // Elimina la extensión .txt
      }
      snprintf(nuevoLibro->nombreID, sizeof(nuevoLibro->nombreID), "%s", id);
      
      char linea[1024];
      char titulo[101] = "";

      while (fgets(linea, sizeof(linea), archivo)) {
        if (strncmp(linea, "Title:", 6) == 0) {
          // Leer y almacenar el título del libro
          snprintf(titulo, sizeof(titulo), "%s", linea + 7);
          if (strlen(titulo) > 0) {
            strtrim(titulo);
            snprintf(nuevoLibro->titulo, sizeof(nuevoLibro->titulo), "%s", titulo);
          }
        }

        if (strstr(linea, "* END OF") != NULL && strstr(linea, "PROJECT GUTENBERG EBOOK") != NULL) {
          break; // Salir del bucle si encuentra una variante de la marca de fin
        }

        // Contar los caracteres y procesar las palabras en cada línea
        nuevoLibro->contadorCaracteres += strlen(linea);
        char *palabra = strtok(linea, " ");

        while (palabra != NULL) {
        strtrim(palabra);
        palabra = quitar_caracteres(palabra);

        // Convertir la palabra a minúsculas
        for (int i = 0; palabra[i]; i++) {
          palabra[i] = tolower(palabra[i]);
        }

        if (palabra[0] && isalpha(palabra[0]) && !isStopWord(palabra)) {
          // Verificar si la palabra ya existe en el mapa del libro
          Pair *aux = searchMap(nuevoLibro->contenido, palabra);
          if (aux != NULL) {
            // La palabra ya existe, incrementar el contador de apariciones
            Palabra *palabraExistente = (Palabra *)aux->value;
            palabraExistente->apariciones++;
          } else {
            // La palabra no existe, crear una nueva entrada en el mapa
            Palabra *nuevaPalabra = (Palabra *)malloc(sizeof(Palabra));
            if (nuevaPalabra == NULL) {
              printf("Error al asignar memoria para la palabra.\n");
              return 0;
            }
            stpcpy(nuevaPalabra->palabra, palabra);
            nuevaPalabra->apariciones = 1;
            insertMap(nuevoLibro->contenido, palabra, nuevaPalabra);
            nuevoLibro->contadorPalabras++;
          }
        }
        palabra = strtok(NULL, " ");
      }
    }
    // Cerrar el archivo
    fclose(archivo);
    filecount++;
    printf("Procesando archivo %d\n", filecount);
    // Insertar el Libro en el TreeMap
    insertTreeMap(arbolLibros, nuevoLibro->titulo, nuevoLibro);
    }
  }

  // Cerrar el directorio
  closedir(dir);
  printf("Se han logrado cargar los documentos!!\n");
  printf("========================================\n");
  return 1;
}

// Función para imprimir libros en orden alfabético.
void imprimirLibros(TreeMap *arbolLibros) {
    // Verifica si el TreeMap o su raíz son nulos.
    if (arbolLibros == NULL || arbolLibros->root == NULL) {
        printf("Error con carga de archivos.\n");
        return;
    }

    int fileCount = 0; // Contador de archivos
    Pair *currentPair = firstTreeMap(arbolLibros);

    // Si no hay libros en el TreeMap, muestra un mensaje y sale de la función.
    if (currentPair == NULL) {
        printf("No hay libros para mostrar.\n");
        return;
    }

    printf("Los títulos ordenados alfabéticamente:\n");

    // Recorre el TreeMap para mostrar información de cada libro.
    while (currentPair != NULL) {
        Libro *libro = (Libro *)currentPair->value;

        printf("Título: %s\n", currentPair->key); // Utiliza la clave como título
        printf("ID: %s\n", libro->nombreID);
        printf("Número de palabras: %d\n", libro->contadorPalabras);
        printf("Número de caracteres: %d\n", libro->contadorCaracteres);
        fileCount++;
        printf("Total de archivos procesados: %d\n", fileCount);
        printf("\n");

        currentPair = nextTreeMap(arbolLibros);
    }
}

// Función para buscar un libro por título.
Libro *buscarLibroPorTitulo(TreeMap *arbolLibros, const char *titulo) {
    // Busca el libro en el TreeMap por su título y devuelve el libro si se encuentra.
    Pair *pair = searchTreeMap(arbolLibros, (void *)titulo);
    if (pair != NULL) {
        return (Libro *)pair->value;
    }
    return NULL;
}

// Función para buscar libros por palabras clave.
void buscarLibrosPorPalabras(TreeMap *arbolLibros, char *palabras) {
    char *palabra = strtok(palabras, " ");

    if (palabra == NULL) {
        printf("Por favor, ingresa al menos una palabra para buscar.\n");
        return;
    }

    List *resultados = createList();

    // Inicializa una lista de resultados con todos los títulos de los libros en el TreeMap.
    for (Pair *pair = firstTreeMap(arbolLibros); pair; pair = nextTreeMap(arbolLibros)) {
        pushBack(resultados, pair->key);
    }

    // Itera sobre las palabras clave para refinar la búsqueda.
    while (palabra != NULL) {
        List *resultadosActuales = createList();

        // Busca libros cuyos títulos contienen la palabra clave actual y agrega los títulos a la lista de resultados actuales.
        for (void *current = firstList(resultados); current; current = nextList(resultados)) {
            char *titulo = (char *)current;
            Libro *libro = buscarLibroPorTitulo(arbolLibros, titulo);

            if (libro != NULL && strstr(libro->titulo, palabra)) {
                pushBack(resultadosActuales, titulo);
            }
        }

        // Limpia la lista de resultados anterior y actualiza con la nueva lista de resultados.
        cleanList(resultados);
        resultados = resultadosActuales;

        palabra = strtok(NULL, " ");
    }

    // Muestra los libros encontrados que contienen todas las palabras clave.
    if (firstList(resultados) == NULL) {
        printf("No se encontraron libros que contengan todas las palabras proporcionadas.\n");
    } else {
        printf("Libros que contienen todas las palabras:\n");
        for (void *current = firstList(resultados); current; current = nextList(resultados)) {
            char *titulo = (char *)current;
            printf("Título: %s\n", titulo);
        }
    }

    // Limpia y libera la memoria de la lista de resultados.
    cleanList(resultados);
    free(resultados);
}


//Función para mostrar palabras más frecuentes de un libro
void mostrarPalabrasFrecuentes(Libro *libro) {
    if (libro != NULL) {
        printf("Palabras más frecuentes en el libro '%s':\n", libro->titulo);
      
        int maxPalabras = 10;  // Mostrar las 10 palabras más frecuentes
        Palabra palabras[maxPalabras];

        // Inicializar las palabras y sus apariciones
        for (int i = 0; i < maxPalabras; i++) {
            strcpy(palabras[i].palabra, "");
            palabras[i].apariciones = 0;
        }

        Pair *current = firstMap(libro->contenido);

        // Calcular las apariciones de las palabras
        while (current != NULL) {
            Palabra *palabra = current->value;

            for (int i = 0; i < maxPalabras; i++) {
                if (palabra->apariciones > palabras[i].apariciones) {
                    // Desplazar las palabras menos frecuentes hacia abajo
                    for (int j = maxPalabras - 1; j > i; j--) {
                        strcpy(palabras[j].palabra, palabras[j - 1].palabra);
                        palabras[j].apariciones = palabras[j - 1].apariciones;
                    }

                    // Almacenar la nueva palabra y sus apariciones
                    strcpy(palabras[i].palabra, palabra->palabra);
                    palabras[i].apariciones = palabra->apariciones;
                    break;
                }
            }

            current = nextMap(libro->contenido);
        }

        // Mostrar las palabras más frecuentes y sus apariciones
        for (int i = 0; i < maxPalabras; i++) {
            if (palabras[i].apariciones > 0) {
                printf("Palabra: %s, Apariciones: %d\n", palabras[i].palabra, palabras[i].apariciones);
            }
        }
      // Liberar la memoria de la estructura
      for (int i = 0; i < maxPalabras; i++) {
          strcpy(palabras[i].palabra, "");
            palabras[i].apariciones = 0;
      }
    } else {
        printf("Libro no encontrado.\n");
    }
}

//Funcion para mostrar palabras más relevantes de un libro.
void PalabrasPlusRelevant(Libro *libro) {
    if (libro != NULL) {
        // Calcular el número de documentos que tienen la palabra p
        HashMap *documentosConPalabra = createMap(100);

        for (Pair *pair = firstMap(libro->contenido); pair; pair = nextMap(libro->contenido)) {
            char *palabra = (char *)pair->key;
            insertMap(documentosConPalabra, palabra, NULL);
        }

        // Calcular las 10 palabras más relevantes
        Palabra palabrasRelevantes[10];
        for (int i = 0; i < 10; i++) {
            palabrasRelevantes[i].apariciones = 0;    // Inicializar apariciones
        }

        for (Pair *pair = firstMap(libro->contenido); pair; pair = nextMap(libro->contenido)) {
            Palabra *palabra = pair->value;

            for (int i = 0; i < 10; i++) {
                if (palabra->apariciones > palabrasRelevantes[i].apariciones) {
                    // Insertar la palabra en la posición i y desplazar las demás
                    for (int k = 9; k > i; k--) {
                        strcpy(palabrasRelevantes[k].palabra, palabrasRelevantes[k - 1].palabra);
                        palabrasRelevantes[k].apariciones = palabrasRelevantes[k - 1].apariciones;
                    }
                    strcpy(palabrasRelevantes[i].palabra, palabra->palabra);
                    palabrasRelevantes[i].apariciones = palabra->apariciones;
                    break;
                }
            }
        }

        printf("Las 10 palabras con más apariciones en el libro '%s' son:\n", libro->titulo);
        for (int i = 0; i < 10; i++) {
            if (palabrasRelevantes[i].apariciones > 0) {
                printf("%d. Palabra: %s, Apariciones: %d\n", i + 1, palabrasRelevantes[i].palabra, palabrasRelevantes[i].apariciones);
            }
        }
    } else {
        printf("Libro no encontrado.\n");
    }
}
