# Alumnos

- Francisco Hermani		98223
- Martin Rosas Sommer	98535

Link GitHub: https://github.com/franhermani/taller-tp4

# Herramientas y dependencias a instalar

```
sudo apt-get install cmake
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install tiled
```

# Comandos útiles - Consola

### Instalación

Clonar el repositorio actual:
```
git clone https://github.com/franhermani/taller-tp4
```

En la carpeta donde se clonó el repositorio ejecutar:
```
bash install.sh
```

### Compilar el proyecto (directorio build)

En la carpeta donde se clonó el repositorio ejecutar:
```
bash make.sh
```

*NOTA: si se modifica algún archivo de código luego de haber ejecutado
make.sh, es necesario ir a build y ejecutar make manualmente (o ejecutar
clean.sh y make.sh nuevamente)*

### Limpiar el proyecto (directorio build)

En la carpeta donde se clonó el repositorio ejecutar:
```
bash clean.sh
```

### Ejecutar el servidor

En la carpeta build ejecutar:
```
./server ../server/config/config.json
```

### Ejecutar el cliente

En la carpeta build ejecutar:
```
./client localhost 8080
```

### Verificar normas de codificación

En la carpeta donde se clonó el repositorio ejecutar:
```
bash execute.sh
```
