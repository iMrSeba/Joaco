# Connect Four Game

## Descripción
Este programa implementa el juego Connect Four (Cuatro en línea) en la consola. Los jugadores pueden enfrentarse entre sí o jugar contra una inteligencia artificial que utiliza el algoritmo Minimax.

El menú principal te permite seleccionar diferentes opciones, como jugar contra la CPU, jugar contra otro jugador, ver las puntuaciones, etc.

## Decisiones de Diseño
### Estructura del Código
- `Funtions.h`: Contiene las declaraciones de funciones y las definiciones de variables globales.
- `Funtions.cpp`: Implementaciones de las funciones del juego.
- `GameVariables.h`: Define las variables y constantes del juego.
- `main.cpp`: Punto de entrada del programa.
- `PrintBoard`: Función para imprimir el tablero.
- `Odds`: Función que verifica si hay posibilidad de victoria en el siguiente movimiento.
- `CPUVictory`: Función que verifica si la CPU ha ganado.
- `PlayerVictory`: Función que verifica si el jugador ha ganado.
- `ApplyRoll`: Función para aplicar un movimiento al tablero.
- `Heuristic`: Función que calcula una heurística para evaluar el estado del tablero.
- `evaluateHumanConnection`: Función que evalúa la conexión del jugador humano.
- `Nodo`: Estructura que representa un nodo en el árbol de búsqueda del algoritmo Minimax.
- `childrens`: Puntero a un arreglo de punteros a nodos hijos.
- `moves`: Puntero a un arreglo de movimientos asociados a cada hijo.
- `num_children`: Número de hijos del nodo.
- `board`: Matriz que representa el tablero en ese nodo.
- `worth`: Valor asignado al nodo según la heurística.
- `level`: Nivel del nodo en el árbol.

### Algoritmo MiniMax con Poda Alfa-Beta
La inteligencia artificial de la CPU se basa en el algoritmo MiniMax con poda alfa-beta para tomar decisiones más eficientes. 
La función heurística asigna valores a los estados del tablero, y la poda alfa-beta mejora significativamente el rendimiento en comparación con la versión sin poda.

## Resultados de Pruebas
Se realizaron pruebas comparativas entre la implementación de MiniMax sin poda y con poda.
Los resultados indican una mejora sustancial en el rendimiento cuando se utiliza la poda alfa-beta, especialmente en niveles de dificultad más altos.


