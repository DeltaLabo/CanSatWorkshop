# Instrucciones para ejecutar la visualización 3D del CanSat

* Correr `ground_station.ino` (está en la carpeta principal del repositorio) en el ground station.
* Asegurarse que el ground esté conectado como se indica en `ground_station/pins.h`, y alimentado mediante un cable USB-C
desde una computadora.
* Correr `3dmodel.ino` en el ESP32-C3 del CanSat. Instalar todas las librerías que no sean encontradas.
* Escribir el puerto COM del ground station en `3dmodel.py`.
* Correr `3dmodel.py` en Python.
* Abrir `3dmodel.html` en un navegador.