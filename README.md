# Alumnos

- Francisco Hermani		98223
- Martin Rosas Sommer	98535

Link GitHub: https://github.com/franhermani/taller-tp4

# Herramientas y dependencias a instalar

```
sudo apt-get install cmake
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libglib2.0-dev
sudo apt-get install libgtk2.0-dev
sudo apt-get install libgtkmm-3.0-dev
sudo apt-get install tiled
sudo apt-get install glade
```

# Comandos útiles - Consola

### Compilar el proyecto (directorio build)

```
bash make.sh
```

*NOTA: si se modifica algún archivo de código luego de haber ejecutado
make.sh, es necesario ir a build y ejecutar make manualmente (o ejecutar
clean.sh y make.sh nuevamente)*

### Limpiar el proyecto (directorio build)

```
bash clean.sh
```

### Verificar normas de codificación

```
bash execute.sh
```


### Generar archivo de supresión

Esto sirve para detectar los leaks que tiene la librería SDL y omitirlos
en nuestras ejecuciones, así podemos ver realmente qué leaks son nuestros.

Luego de compilar el proyecto, ejecutar dentro de la carpeta build:

```
valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --gen-suppressions=all --log-file=minimal.log ./client
```

Esto genera la salida normal de Valgrind y la almacena en el archivo *minimal.log*

Luego, ejecutar:

```
python3 ../parser.py minimal.log minimal.supp
```

Esto copia la salida anterior a un nuevo archivo. Ahora podemos ejecutar
Valgrind filtrando los logs obtenidos:

```
valgrind --leak-check=full --show-leak-kinds=all --suppressions=minimal.supp ./client
```
