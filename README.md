# Alumnos

- Francisco Hermani		98223
- Martin Rosas Sommer	98535

Link GitHub: https://github.com/franhermani/taller-tp4

# Herramientas y dependencias a instalar

```
sudo apt-get install cmake
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install tiled
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

### Ejecutar el servidor

```
cd build
./server ../server/config/config.json
```

### Ejecutar el cliente

```
cd build
./client localhost 8080
```

### Verificar normas de codificación

```
bash execute.sh
```
