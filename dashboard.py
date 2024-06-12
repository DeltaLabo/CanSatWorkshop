import tkinter as tk
from tkinter import ttk
from tkinter import Scrollbar, Canvas
import customtkinter
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import serial
import threading
import struct

################################################################
#                                                              #
#              DEFINICIÓN DE VARIABLES GLOBALES                #
#                                                              #
################################################################

# Se crean las variables para almacenar datos
dataESP = []
# Datos del CANSAT1
dataVel1 = []
dataRot1 = []
dataAce1 = []
dataPos1 = []
dataOri1 = []
dataAlt1 = []
dataPre1 = []
dataTem1 = []
dataVol1 = []
dataCor1 = []
# Datos del CANSAT2
dataVel2 = []
dataRot2 = []
dataAce2 = []
dataPos2 = []
dataOri2 = []
dataAlt2 = []
dataPre2 = []
dataTem2 = []
dataVol2 = []
dataCor2 = []
# Datos del CANSAT3
dataVel3 = []
dataRot3 = []
dataAce3 = []
dataPos3 = []
dataOri3 = []
dataAlt3 = []
dataPre3 = []
dataTem3 = []
dataVol3 = []
dataCor3 = []
# Datos del CANSAT4
dataVel4 = []
dataRot4 = []
dataAce4 = []
dataPos4 = []
dataOri4 = []
dataAlt4 = []
dataPre4 = []
dataTem4 = []
dataVol4 = []
dataCor4 = []

################################################################
#                                                              #
#              FUNCIÓN DE COMUNICAIÓN UART                     #
#                                                              #
################################################################

def read_serial_data():
    if ser.in_waiting >= 100:  # Check if there's enough data for a full packet
        packet = ser.read_all()
        print("Datos recividos:")
        print(packet)
        if packet[0:4] == "CSWS".encode('ascii'):
            print("Datos cortados:")
            print(packet)
            process_serial_data(packet)
    root.after(100, read_serial_data)
        
            

def process_serial_data(packet):
    header = packet[:4].decode('ascii')
    sender = packet[4:6].decode('ascii')
    receiver = packet[6:8].decode('ascii')
    values = struct.unpack('10f', packet[8:48])
    tail = packet[96:100].decode('ascii')

    if (sender == 'M1' and header == 'CSWS'):  # Assuming sender '01' is CANSAT1
        dataVel1.append(values[0])
        dataRot1.append(values[1])
        dataAce1.append(values[2])
        dataPos1.append(values[3])
        dataOri1.append(values[4])
        dataAlt1.append(values[5])
        dataPre1.append(values[6])
        dataTem1.append(values[7])
        dataVol1.append(values[8])
        dataCor1.append(values[9])
        update_graphs1()
    
    if (sender == 'M2' and header == 'CSWS'):  # Assuming sender '01' is CANSAT1
        dataVel2.append(values[0])
        dataRot2.append(values[1])
        dataAce2.append(values[2])
        dataPos2.append(values[3])
        dataOri2.append(values[4])
        dataAlt2.append(values[5])
        dataPre2.append(values[6])
        dataTem2.append(values[7])
        dataVol2.append(values[8])
        dataCor2.append(values[9])
        update_graphs2()

    if (sender == 'M3' and header == 'CSWS'):  # Assuming sender '01' is CANSAT1
        dataVel3.append(values[0])
        dataRot3.append(values[1])
        dataAce3.append(values[2])
        dataPos3.append(values[3])
        dataOri3.append(values[4])
        dataAlt3.append(values[5])
        dataPre3.append(values[6])
        dataTem3.append(values[7])
        dataVol3.append(values[8])
        dataCor3.append(values[9])
        update_graphs3()

    if (sender == 'M4' and header == 'CSWS'):  # Assuming sender '01' is CANSAT1
        dataVel4.append(values[0])
        dataRot4.append(values[1])
        dataAce4.append(values[2])
        dataPos4.append(values[3])
        dataOri4.append(values[4])
        dataAlt4.append(values[5])
        dataPre4.append(values[6])
        dataTem4.append(values[7])
        dataVol4.append(values[8])
        dataCor4.append(values[9])
        update_graphs4()


################################################################
#                                                              #
#              FUNCIONES QUE ACTUALIZAN GRÁFICAS               #
#                                                              #
################################################################

# Función para actualizar la gráficas gráficas
def update_graphs1():

    axVel.clear()
    axVel.plot(range(len(dataVel1)), dataVel1)
    axVel.set_xlabel('Tiempo', fontsize=12)
    #axVel.set_ylabel('Velocidad (m/s)', fontsize=12)
    axVel.set_xticklabels([])
    axVel.set_title("Velocidad (m/s)", fontsize=12)

    axRot.clear()
    axRot.plot(range(len(dataRot1)), dataRot1)
    axRot.set_xlabel('Tiempo', fontsize=12)
    #axRot.set_ylabel('Rotación (z) (rad/s)', fontsize=12)
    axRot.set_xticks([])
    axRot.set_title("Rotación (z) (rad/s)", fontsize=12)

    axOri.clear()
    axOri.plot(range(len(dataOri1)), dataOri1)
    axOri.set_xlabel('Tiempo', fontsize=12)
    #axOri.set_ylabel('Yaw (°)', fontsize=12)
    axOri.set_xticks([])
    axOri.set_title("Yaw (°)", fontsize=12)

    axAcel.clear()
    axAcel.plot(range(len(dataAce1)), dataAce1)
    axAcel.set_xlabel('Tiempo', fontsize=12)
    #axAcel.set_ylabel('Aceleración (z) (m/s2)', fontsize=12)
    axAcel.set_xticks([])
    axAcel.set_title("Aceleración (z) (m/s2)", fontsize=12)

    axAlt.clear()
    axAlt.plot(range(len(dataAlt1)), dataAlt1)
    axAlt.set_xlabel('Tiempo', fontsize=12)
    #axAlt.set_ylabel('Altitud (msnm)', fontsize=12)
    axAlt.set_xticks([])
    axAlt.set_title("Altitud (msnm)", fontsize=12)

    axVol.clear()
    axVol.plot(range(len(dataVol1)), dataVol1)
    axVol.set_xlabel('Tiempo', fontsize=12)
    #axVol.set_ylabel('Voltaje (V)', fontsize=12)
    axVol.set_xticks([])
    axVol.set_title("Voltaje (V)", fontsize=12)

    axCor.clear()
    axCor.plot(range(len(dataCor1)), dataCor1)
    axCor.set_xlabel('Tiempo', fontsize=12)
    #axCor.set_ylabel('Corriente (mA)', fontsize=12)
    axCor.set_xticks([])
    axCor.set_title("Corriente (mA)", fontsize=12)

    axPre.clear()
    axPre.plot(range(len(dataPre1)), dataPre1)
    axPre.set_xlabel('Tiempo', fontsize=12)
    #axPre.set_ylabel('Presión', fontsize=12)
    axPre.set_xticks([])
    axPre.set_title("Presión", fontsize=12)

    axTemp.clear()
    axTemp.plot(range(len(dataTem1)), dataTem1)
    axTemp.set_xlabel('Tiempo', fontsize=12)
    #axTemp.set_ylabel('Temperatura', fontsize=12)
    axTemp.set_xticks([])
    axTemp.set_title("Temperatura", fontsize=12)

    axPos.clear()
    axPos.plot(range(len(dataPos1)), dataPos1)
    axPos.set_xlabel('Tiempo', fontsize=12)
    #axPos.set_ylabel('Latitud (°)', fontsize=12)
    axPos.set_xticks([])
    axPos.set_title("Latitud (°)", fontsize=12)

    axVel.set_ylim(-10.0, 10.0)
    axRot.set_ylim(-5.0, 5.0)
    axAcel.set_ylim(8.9, 9.3)
    axPos.set_ylim(-2.0, 2.0)
    axOri.set_ylim(-5.0, 5.0)
    axAlt.set_ylim(-10.0, 1400.0)
    axPre.set_ylim(80.0, 110.0)
    axTemp.set_ylim(20.0, 35.0)
    axVol.set_ylim(3.0, 4.3)
    axCor.set_ylim(-10.0, 500.0)

    canvasVel.draw()
    canvasOri.draw()
    canvasVol.draw()
    canvasAlt.draw()
    canvasCor.draw()
    canvasPos.draw()
    canvasPre.draw()
    canvasRot.draw()
    canvasTem.draw()
    canvasAcel.draw()

def update_graphs2():

    axVel2.clear()
    axVel2.plot(range(len(dataVel2)), dataVel2)
    axVel2.set_xlabel('Tiempo', fontsize=12)
    #axVel2.set_ylabel('Velocidad (m/s)', fontsize=12)
    axVel2.set_xticklabels([])
    axVel2.set_title("Velocidad (m/s)", fontsize=12)

    axRot2.clear()
    axRot2.plot(range(len(dataRot2)), dataRot2)
    axRot2.set_xlabel('Tiempo', fontsize=12)
    #axRot2.set_ylabel('Rotación (z) (rad/s)', fontsize=12)
    axRot2.set_xticks([])
    axRot2.set_title("Rotación (z) (rad/s)", fontsize=12)

    axOri2.clear()
    axOri2.plot(range(len(dataOri2)), dataOri2)
    axOri2.set_xlabel('Tiempo', fontsize=12)
    #axOri2.set_ylabel('Yaw (°)', fontsize=12)
    axOri2.set_xticks([])
    axOri2.set_title("Yaw (°)", fontsize=12)

    axAcel2.clear()
    axAcel2.plot(range(len(dataAce2)), dataAce2)
    axAcel2.set_xlabel('Tiempo', fontsize=12)
    #axAcel2.set_ylabel('Aceleración (z) (m/s2)', fontsize=12)
    axAcel2.set_xticks([])
    axAcel2.set_title("Aceleración (z) (m/s2)", fontsize=12)

    axAlt2.clear()
    axAlt2.plot(range(len(dataAlt2)), dataAlt2)
    axAlt2.set_xlabel('Tiempo', fontsize=12)
    #axAlt2.set_ylabel('Altitud (msnm)', fontsize=12)
    axAlt2.set_xticks([])
    axAlt2.set_title("Altitud (msnm)", fontsize=12)

    axVol2.clear()
    axVol2.plot(range(len(dataVol2)), dataVol2)
    axVol2.set_xlabel('Tiempo', fontsize=12)
    #axVol2.set_ylabel('Voltaje (V)', fontsize=12)
    axVol2.set_xticks([])
    axVol2.set_title("Voltaje (V)", fontsize=12)

    axCor2.clear()
    axCor2.plot(range(len(dataCor2)), dataCor2)
    axCor2.set_xlabel('Tiempo', fontsize=12)
    #axCor2.set_ylabel('Corriente (mA)', fontsize=12)
    axCor2.set_xticks([])
    axCor2.set_title("Corriente (mA)", fontsize=12)

    axPre2.clear()
    axPre2.plot(range(len(dataPre2)), dataPre2)
    axPre2.set_xlabel('Tiempo', fontsize=12)
    #axPre2.set_ylabel('Presión', fontsize=12)
    axPre2.set_xticks([])
    axPre2.set_title("Presión", fontsize=12)

    axTemp2.clear()
    axTemp2.plot(range(len(dataTem2)), dataTem2)
    axTemp2.set_xlabel('Tiempo', fontsize=12)
    #axTemp2.set_ylabel('Temperatura', fontsize=12)
    axTemp2.set_xticks([])
    axTemp2.set_title("Temperatura", fontsize=12)

    axPos2.clear()
    axPos2.plot(range(len(dataPos2)), dataPos2)
    axPos2.set_xlabel('Tiempo', fontsize=12)
    #axPos2.set_ylabel('Latitud (°)', fontsize=12)
    axPos2.set_xticks([])
    axPos2.set_title("Latitud (°)", fontsize=12)

    axVel2.set_ylim(-10.0, 10.0)
    axRot2.set_ylim(-5.0, 5.0)
    axAcel2.set_ylim(8.9, 9.3)
    axPos2.set_ylim(-2.0, 2.0)
    axOri2.set_ylim(-5.0, 5.0)
    axAlt2.set_ylim(-10.0, 1400.0)
    axPre2.set_ylim(80.0, 110.0)
    axTemp2.set_ylim(20.0, 35.0)
    axVol2.set_ylim(3.0, 4.3)
    axCor2.set_ylim(-10.0, 500.0)

    canvasVel2.draw()
    canvasOri2.draw()
    canvasVol2.draw()
    canvasAlt2.draw()
    canvasCor2.draw()
    canvasPos2.draw()
    canvasPre2.draw()
    canvasRot2.draw()
    canvasTem2.draw()
    canvasAcel2.draw()

def update_graphs3():

    axVel3.clear()
    axVel3.plot(range(len(dataVel3)), dataVel3)
    axVel3.set_xlabel('Tiempo', fontsize=12)
    #axVel3.set_ylabel('Velocidad (m/s)', fontsize=12)
    axVel3.set_xticklabels([])
    axVel3.set_title("Velocidad (m/s)", fontsize=12)

    axRot3.clear()
    axRot3.plot(range(len(dataRot3)), dataRot3)
    axRot3.set_xlabel('Tiempo', fontsize=12)
    #axRot3.set_ylabel('Rotación (z) (rad/s)', fontsize=12)
    axRot3.set_xticks([])
    axRot3.set_title("Rotación (z) (rad/s)", fontsize=12)

    axOri3.clear()
    axOri3.plot(range(len(dataOri3)), dataOri3)
    axOri3.set_xlabel('Tiempo', fontsize=12)
    #axOri3.set_ylabel('Yaw (°)', fontsize=12)
    axOri3.set_xticks([])
    axOri3.set_title("Yaw (°)", fontsize=12)

    axAcel3.clear()
    axAcel3.plot(range(len(dataAce3)), dataAce3)
    axAcel3.set_xlabel('Tiempo', fontsize=12)
    #axAcel3.set_ylabel('Aceleración (z) (m/s2)', fontsize=12)
    axAcel3.set_xticks([])
    axAcel3.set_title("Aceleración (z) (m/s2)", fontsize=12)

    axAlt3.clear()
    axAlt3.plot(range(len(dataAlt3)), dataAlt3)
    axAlt3.set_xlabel('Tiempo', fontsize=12)
    #axAlt3.set_ylabel('Altitud (msnm)', fontsize=12)
    axAlt3.set_xticks([])
    axAlt3.set_title("Altitud (msnm)", fontsize=12)

    axVol3.clear()
    axVol3.plot(range(len(dataVol3)), dataVol3)
    axVol3.set_xlabel('Tiempo', fontsize=12)
    #axVol3.set_ylabel('Voltaje (V)', fontsize=12)
    axVol3.set_xticks([])
    axVol3.set_title("Voltaje (V)", fontsize=12)

    axCor3.clear()
    axCor3.plot(range(len(dataCor3)), dataCor3)
    axCor3.set_xlabel('Tiempo', fontsize=12)
    #axCor3.set_ylabel('Corriente (mA)', fontsize=12)
    axCor3.set_xticks([])
    axCor3.set_title("Corriente (mA)", fontsize=12)

    axPre3.clear()
    axPre3.plot(range(len(dataPre3)), dataPre3)
    axPre3.set_xlabel('Tiempo', fontsize=12)
    #axPre3.set_ylabel('Presión', fontsize=12)
    axPre3.set_xticks([])
    axPre3.set_title("Presión", fontsize=12)

    axTemp3.clear()
    axTemp3.plot(range(len(dataTem3)), dataTem3)
    axTemp3.set_xlabel('Tiempo', fontsize=12)
    #axTemp3.set_ylabel('Temperatura', fontsize=12)
    axTemp3.set_xticks([])
    axTemp3.set_title("Temperatura", fontsize=12)

    axPos3.clear()
    axPos3.plot(range(len(dataPos3)), dataPos3)
    axPos3.set_xlabel('Tiempo', fontsize=12)
    #axPos3.set_ylabel('Latitud (°)', fontsize=12)
    axPos3.set_xticks([])
    axPos3.set_title("Latitud (°)", fontsize=12)

    axVel3.set_ylim(-10.0, 10.0)
    axRot3.set_ylim(-5.0, 5.0)
    axAcel3.set_ylim(8.9, 9.3)
    axPos3.set_ylim(-2.0, 2.0)
    axOri3.set_ylim(-5.0, 5.0)
    axAlt3.set_ylim(-10.0, 1400.0)
    axPre3.set_ylim(80.0, 110.0)
    axTemp3.set_ylim(20.0, 35.0)
    axVol3.set_ylim(3.0, 4.3)
    axCor3.set_ylim(-10.0, 500.0)

    canvasVel3.draw()
    canvasOri3.draw()
    canvasVol3.draw()
    canvasAlt3.draw()
    canvasCor3.draw()
    canvasPos3.draw()
    canvasPre3.draw()
    canvasRot3.draw()
    canvasTem3.draw()
    canvasAcel3.draw()

def update_graphs4():

    axVel4.clear()
    axVel4.bar(range(len(dataVel4)), dataVel4)
    axVel4.set_xlabel('Tiempo', fontsize=12)
    #axVel4.set_ylabel('Velocidad (m/s)', fontsize=12)
    axVel4.set_xticklabels([])
    axVel4.set_title("Velocidad (m/s)", fontsize=12)

    axRot4.clear()
    axRot4.plot(range(len(dataRot4)), dataRot4)
    axRot4.set_xlabel('Tiempo', fontsize=12)
    #axRot4.set_ylabel('Rotación (z) (rad/s)', fontsize=12)
    axRot4.set_xticks([])
    axRot4.set_title("Rotación (z) (rad/s)", fontsize=12)

    axOri4.clear()
    axOri4.plot(range(len(dataOri4)), dataOri4)
    axOri4.set_xlabel('Tiempo', fontsize=12)
    #axOri4.set_ylabel('Yaw (°)', fontsize=12)
    axOri4.set_xticks([])
    axOri4.set_title("Yaw (°)", fontsize=12)

    axAcel4.clear()
    axAcel4.plot(range(len(dataAce4)), dataAce4)
    axAcel4.set_xlabel('Tiempo', fontsize=12)
    #axAcel4.set_ylabel('Aceleración (z) (m/s2)', fontsize=12)
    axAcel4.set_xticks([])
    axAcel4.set_title("Aceleración (z) (m/s2)", fontsize=12)

    axAlt4.clear()
    axAlt4.plot(range(len(dataAlt4)), dataAlt4)
    axAlt4.set_xlabel('Tiempo', fontsize=12)
    #axAlt4.set_ylabel('Altitud (msnm)', fontsize=12)
    axAlt4.set_xticks([])
    axAlt4.set_title("Altitud (msnm)", fontsize=12)

    axVol4.clear()
    axVol4.plot(range(len(dataVol4)), dataVol4)
    axVol4.set_xlabel('Tiempo', fontsize=12)
    #axVol4.set_ylabel('Voltaje (V)', fontsize=12)
    axVol4.set_xticks([])
    axVol4.set_title("Voltaje (V)", fontsize=12)

    axCor4.clear()
    axCor4.plot(range(len(dataCor4)), dataCor4)
    axCor4.set_xlabel('Tiempo', fontsize=12)
    #axCor4.set_ylabel('Corriente (mA)', fontsize=12)
    axCor4.set_xticks([])
    axCor4.set_title("Corriente (mA)", fontsize=12)

    axPre4.clear()
    axPre4.plot(range(len(dataPre4)), dataPre4)
    axPre4.set_xlabel('Tiempo', fontsize=12)
    #axPre4.set_ylabel('Presión', fontsize=12)
    axPre4.set_xticks([])
    axPre4.set_title("Presión", fontsize=12)

    axTemp4.clear()
    axTemp4.plot(range(len(dataTem4)), dataTem4)
    axTemp4.set_xlabel('Tiempo', fontsize=12)
    #axTemp4.set_ylabel('Temperatura', fontsize=12)
    axTemp4.set_xticks([])
    axTemp4.set_title("Temperatura", fontsize=12)

    axPos4.clear()
    axPos4.plot(range(len(dataPos4)), dataPos4)
    axPos4.set_xlabel('Tiempo', fontsize=12)
    #axPos4.set_ylabel('Latitud (°)', fontsize=12)
    axPos4.set_xticks([])
    axPos4.set_title("Latitud (°)", fontsize=12)

    axVel4.set_ylim(-10.0, 10.0)
    axRot4.set_ylim(-5.0, 5.0)
    axAcel4.set_ylim(8.9, 9.3)
    axPos4.set_ylim(-2.0, 2.0)
    axOri4.set_ylim(-5.0, 5.0)
    axAlt4.set_ylim(-10.0, 1400.0)
    axPre4.set_ylim(80.0, 110.0)
    axTemp4.set_ylim(20.0, 35.0)
    axVol4.set_ylim(3.0, 4.3)
    axCor4.set_ylim(-10.0, 500.0)

    canvasVel4.draw()
    canvasOri4.draw()
    canvasVol4.draw()
    canvasAlt4.draw()
    canvasCor4.draw()
    canvasPos4.draw()
    canvasPre4.draw()
    canvasRot4.draw()
    canvasTem4.draw()
    canvasAcel4.draw()

################################################################
#                                                              #
#           SE CREA LA ESTRUCTURA DE LA INTERFAZ               #
#                                                              #
################################################################

# Inicializar ventana
root = customtkinter.CTk()
root.title("Monitor de CanSats")
root.geometry("1250x800")

# Crear frames
frame = customtkinter.CTkScrollableFrame(root, orientation="vertical", label_text="MONITOREO DE CANSATS")
frame.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")
frame.grid_rowconfigure(0, weight=1)
frame.grid_columnconfigure(0, weight=1)

# CAN_SAT 1
frame_CAN_SAT_1 = customtkinter.CTkScrollableFrame(frame, orientation="horizontal", label_text="CANSAT 1")
frame_CAN_SAT_1.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")
frame_CAN_SAT_1.grid_rowconfigure(0, weight=1)
frame_CAN_SAT_1.grid_columnconfigure(0, weight=1)

# CAN_SAT 2
frame_CAN_SAT_2 = customtkinter.CTkScrollableFrame(frame, orientation="horizontal", label_text="CANSAT 2")
frame_CAN_SAT_2.grid(row=2, column=0, padx=10, pady=10, sticky="nsew")
frame_CAN_SAT_2.grid_rowconfigure(0, weight=1)
frame_CAN_SAT_2.grid_columnconfigure(0, weight=1)

# CAN_SAT 3
frame_CAN_SAT_3 = customtkinter.CTkScrollableFrame(frame, orientation="horizontal", label_text="CANSAT 3")
frame_CAN_SAT_3.grid(row=3, column=0, padx=10, pady=10, sticky="nsew")
frame_CAN_SAT_3.grid_rowconfigure(0, weight=1)
frame_CAN_SAT_3.grid_columnconfigure(0, weight=1)

# CAN_SAT 4
frame_CAN_SAT_4 = customtkinter.CTkScrollableFrame(frame, orientation="horizontal", label_text="CANSAT 4")
frame_CAN_SAT_4.grid(row=4, column=0, padx=10, pady=10, sticky="nsew")
frame_CAN_SAT_4.grid_rowconfigure(0, weight=1)
frame_CAN_SAT_4.grid_columnconfigure(0, weight=1)

# RESIZE
root.grid_rowconfigure(0, weight=1)
root.grid_columnconfigure(0, weight=1)

################################################################
#                                                              #
#     SE CREAN LAS GRÁFICAS Y SE MANDAN A ACTUALIZAR           #
#                                                              #
################################################################

########################## CANSAT1 #############################
# Se crea la gráfica de Monitorio de Velocidad (m/s)
figVelocity1 = Figure(figsize=(6, 4), dpi=100)
axVel = figVelocity1.add_subplot(111)
axVel.set_xlabel('Tiempo')
#axVel.set_ylabel('Velocidad (m/s)')
axVel.set_ylim(-10.0, 10.0)
canvasVel = FigureCanvasTkAgg(figVelocity1, master=frame_CAN_SAT_1)
canvasVel.get_tk_widget().grid(row = 0, column = 0, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Rotación (z) (rad/s)
figRotation1 = Figure(figsize=(6, 4), dpi=100)
axRot = figRotation1.add_subplot(111)
axRot.set_xlabel('Tiempo')
#axRot.set_ylabel('Rotación (z) (rad/s)')
axRot.set_ylim(-5.0, 5.0)
canvasRot = FigureCanvasTkAgg(figRotation1, master=frame_CAN_SAT_1)
canvasRot.get_tk_widget().grid(row = 0, column = 1, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Aceleracion
figAceleration1 = Figure(figsize=(6, 4), dpi=100)
axAcel = figAceleration1.add_subplot(111)
axAcel.set_xlabel('Tiempo')
axAcel.set_ylabel('Aceleración (z) (m/s2)')
#axAcel.set_ylim(8.9, 9.3)
canvasAcel = FigureCanvasTkAgg(figAceleration1, master=frame_CAN_SAT_1)
canvasAcel.get_tk_widget().grid(row = 0, column = 2, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Posicion
figPosicion1 = Figure(figsize=(6, 4), dpi=100)
axPos = figPosicion1.add_subplot(111)
axPos.set_xlabel('Tiempo')
#axPos.set_ylabel('Latitud (°)')
axPos.set_ylim(-2.0, 2.0)
canvasPos = FigureCanvasTkAgg(figPosicion1, master=frame_CAN_SAT_1)
canvasPos.get_tk_widget().grid(row = 0, column = 3, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Orientacion
figOrientacion1 = Figure(figsize=(6, 4), dpi=100)
axOri = figOrientacion1.add_subplot(111)
axOri.set_xlabel('Tiempo')
#axOri.set_ylabel('Yaw (°)')
axOri.set_ylim(-5.0, 5.0)
canvasOri = FigureCanvasTkAgg(figOrientacion1, master=frame_CAN_SAT_1)
canvasOri.get_tk_widget().grid(row = 0, column = 4, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Altitud (msnm)
figAltitude1 = Figure(figsize=(6, 4), dpi=100)
axAlt = figAltitude1.add_subplot(111)
axAlt.set_xlabel('Tiempo')
#axAlt.set_ylabel('Altitud (msnm)')
axAlt.set_ylim(-10.0, 1400.0)
canvasAlt = FigureCanvasTkAgg(figAltitude1, master=frame_CAN_SAT_1)
canvasAlt.get_tk_widget().grid(row = 0, column = 5, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Presion
figPresión1 = Figure(figsize=(6, 4), dpi=100)
axPre = figPresión1.add_subplot(111)
axPre.set_xlabel('Tiempo')
#axPre.set_ylabel('Aceleración (z) (m/s2)')
axPre.set_ylim(80.0, 110.0)
canvasPre = FigureCanvasTkAgg(figPresión1, master=frame_CAN_SAT_1)
canvasPre.get_tk_widget().grid(row = 0, column = 6, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Temperatura
figTemp1 = Figure(figsize=(6, 4), dpi=100)
axTemp = figTemp1.add_subplot(111)
axTemp.set_xlabel('Tiempo')
#axTemp.set_ylabel('Temperatura')
axTemp.set_ylim(20.0, 35.0)
canvasTem = FigureCanvasTkAgg(figTemp1, master=frame_CAN_SAT_1)
canvasTem.get_tk_widget().grid(row = 0, column = 7, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Voltaje (V)
figVoltaje1 = Figure(figsize=(6, 4), dpi=100)
axVol = figVoltaje1.add_subplot(111)
axVol.set_xlabel('Tiempo')
#axVol.set_ylabel('Voltaje (V)')
axVol.set_ylim(3.0, 4.3)
canvasVol = FigureCanvasTkAgg(figVoltaje1, master=frame_CAN_SAT_1)
canvasVol.get_tk_widget().grid(row = 0, column = 8, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Corriente (mA)
figCorriente1 = Figure(figsize=(6, 4), dpi=100)
axCor = figCorriente1.add_subplot(111)
axCor.set_xlabel('Tiempo')
#axCor.set_ylabel('Corriente (mA)')
axCor.set_ylim(-10.0, 500.0)
canvasCor = FigureCanvasTkAgg(figCorriente1, master=frame_CAN_SAT_1)
canvasCor.get_tk_widget().grid(row = 0, column = 9, padx = 2, pady = 2)

########################## CANSAT2 #############################
# Se crea la gráfica de Monitorio de Velocidad (m/s)
figVelocity2 = Figure(figsize=(6, 4), dpi=100)
axVel2 = figVelocity2.add_subplot(111)
axVel2.set_xlabel('Tiempo')
#axVel2.set_ylabel('Velocidad (m/s)')
axVel2.set_ylim(-10.0, 10.0)
canvasVel2 = FigureCanvasTkAgg(figVelocity2, master=frame_CAN_SAT_2)
canvasVel2.get_tk_widget().grid(row = 0, column = 0, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de ↑ (z) (rad/s)
figRotation2 = Figure(figsize=(6, 4), dpi=100)
axRot2 = figRotation2.add_subplot(111)
axRot2.set_xlabel('Tiempo')
#axRot2.set_ylabel('Rotación (z) (rad/s)')
axRot2.set_ylim(-5.0, 5.0)
canvasRot2 = FigureCanvasTkAgg(figRotation2, master=frame_CAN_SAT_2)
canvasRot2.get_tk_widget().grid(row = 0, column = 1, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Aceleracion
figAceleration2 = Figure(figsize=(6, 4), dpi=100)
axAcel2 = figAceleration2.add_subplot(111)
axAcel2.set_xlabel('Tiempo')
#axAcel2.set_ylabel('Aceleración (z) (m/s2)')
axAcel2.set_ylim(8.9, 9.3)
canvasAcel2 = FigureCanvasTkAgg(figAceleration2, master=frame_CAN_SAT_2)
canvasAcel2.get_tk_widget().grid(row = 0, column = 2, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Posicion
figPosicion2 = Figure(figsize=(6, 4), dpi=100)
axPos2 = figPosicion2.add_subplot(111)
axPos2.set_xlabel('Tiempo')
#axPos2.set_ylabel('Latitud (°)')
axPos2.set_ylim(-2.0, 2.0)
canvasPos2 = FigureCanvasTkAgg(figPosicion2, master=frame_CAN_SAT_2)
canvasPos2.get_tk_widget().grid(row = 0, column = 3, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Orientacion
figOrientacion2 = Figure(figsize=(6, 4), dpi=100)
axOri2 = figOrientacion2.add_subplot(111)
axOri2.set_xlabel('Tiempo')
#axOri2.set_ylabel('Yaw (°)')
axOri2.set_ylim(-5.0, 5.0)
canvasOri2 = FigureCanvasTkAgg(figOrientacion2, master=frame_CAN_SAT_2)
canvasOri2.get_tk_widget().grid(row = 0, column = 4, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Altitud (msnm)
figAltitude2 = Figure(figsize=(6, 4), dpi=100)
axAlt2 = figAltitude2.add_subplot(111)
axAlt2.set_xlabel('Tiempo')
#axAlt2.set_ylabel('Altitud (msnm)')
axAlt2.set_ylim(-10.0, 1400.0)
canvasAlt2 = FigureCanvasTkAgg(figAltitude2, master=frame_CAN_SAT_2)
canvasAlt2.get_tk_widget().grid(row = 0, column = 5, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Presion
figPresión2 = Figure(figsize=(6, 4), dpi=100)
axPre2 = figPresión2.add_subplot(111)
axPre2.set_xlabel('Tiempo')
#axPre2.set_ylabel('Aceleración (z) (m/s2)')
axPre2.set_ylim(80.0, 110.0)
canvasPre2 = FigureCanvasTkAgg(figPresión2, master=frame_CAN_SAT_2)
canvasPre2.get_tk_widget().grid(row = 0, column = 6, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Temperatura
figTemp2 = Figure(figsize=(6, 4), dpi=100)
axTemp2 = figTemp2.add_subplot(111)
axTemp2.set_xlabel('Tiempo')
#axTemp2.set_ylabel('Temperatura')
axTemp2.set_ylim(20.0, 35.0)
canvasTem2 = FigureCanvasTkAgg(figTemp2, master=frame_CAN_SAT_2)
canvasTem2.get_tk_widget().grid(row = 0, column = 7, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Voltaje (V)
figVoltaje2 = Figure(figsize=(6, 4), dpi=100)
axVol2 = figVoltaje2.add_subplot(111)
axVol2.set_xlabel('Tiempo')
#axVol2.set_ylabel('Voltaje (V)')
axVol2.set_ylim(3.0, 4.3)
canvasVol2 = FigureCanvasTkAgg(figVoltaje2, master=frame_CAN_SAT_2)
canvasVol2.get_tk_widget().grid(row = 0, column = 8, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Corriente (mA)
figCorriente2 = Figure(figsize=(6, 4), dpi=100)
axCor2 = figCorriente2.add_subplot(111)
axCor2.set_xlabel('Tiempo')
#axCor2.set_ylabel('Corriente (mA)')
axCor2.set_ylim(-10.0, 500.0)
canvasCor2 = FigureCanvasTkAgg(figCorriente2, master=frame_CAN_SAT_2)
canvasCor2.get_tk_widget().grid(row = 0, column = 9, padx = 2, pady = 2)

########################## CANSAT3 #############################
# Se crea la gráfica de Monitorio de Velocidad (m/s)
figVelocity3 = Figure(figsize=(6, 4), dpi=100)
axVel3 = figVelocity3.add_subplot(111)
axVel3.set_xlabel('Tiempo')
#axVel3.set_ylabel('Velocidad (m/s)')
axVel3.set_ylim(-10.0, 10.0)
canvasVel3 = FigureCanvasTkAgg(figVelocity3, master=frame_CAN_SAT_3)
canvasVel3.get_tk_widget().grid(row = 0, column = 0, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Rotación (z) (rad/s)
figRotation3 = Figure(figsize=(6, 4), dpi=100)
axRot3 = figRotation3.add_subplot(111)
axRot3.set_xlabel('Tiempo')
#axRot3.set_ylabel('Rotación (z) (rad/s)')
axRot3.set_ylim(-5.0, 5.0)
canvasRot3 = FigureCanvasTkAgg(figRotation3, master=frame_CAN_SAT_3)
canvasRot3.get_tk_widget().grid(row = 0, column = 1, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Aceleracion
figAceleration3 = Figure(figsize=(6, 4), dpi=100)
axAcel3 = figAceleration3.add_subplot(111)
axAcel3.set_xlabel('Tiempo')
#axAcel3.set_ylabel('Aceleración (z) (m/s2)')
axAcel3.set_ylim(8.9, 9.3)
canvasAcel3 = FigureCanvasTkAgg(figAceleration3, master=frame_CAN_SAT_3)
canvasAcel3.get_tk_widget().grid(row = 0, column = 2, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Posicion
figPosicion3 = Figure(figsize=(6, 4), dpi=100)
axPos3 = figPosicion3.add_subplot(111)
axPos3.set_xlabel('Tiempo')
#axPos3.set_ylabel('Latitud (°)')
axPos3.set_ylim(-2.0, 2.0)
canvasPos3 = FigureCanvasTkAgg(figPosicion3, master=frame_CAN_SAT_3)
canvasPos3.get_tk_widget().grid(row = 0, column = 3, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Orientacion
figOrientacion3 = Figure(figsize=(6, 4), dpi=100)
axOri3 = figOrientacion3.add_subplot(111)
axOri3.set_xlabel('Tiempo')
#axOri3.set_ylabel('Yaw (°)')
axOri3.set_ylim(-5.0, 5.0)
canvasOri3 = FigureCanvasTkAgg(figOrientacion3, master=frame_CAN_SAT_3)
canvasOri3.get_tk_widget().grid(row = 0, column = 4, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Altitud (msnm)
figAltitude3 = Figure(figsize=(6, 4), dpi=100)
axAlt3 = figAltitude3.add_subplot(111)
axAlt3.set_xlabel('Tiempo')
#axAlt3.set_ylabel('Altitud (msnm)')
axAlt3.set_ylim(-10.0, 1400.0)
canvasAlt3 = FigureCanvasTkAgg(figAltitude3, master=frame_CAN_SAT_3)
canvasAlt3.get_tk_widget().grid(row = 0, column = 5, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Presion
figPresión3 = Figure(figsize=(6, 4), dpi=100)
axPre3 = figPresión3.add_subplot(111)
axPre3.set_xlabel('Tiempo')
#axPre3.set_ylabel('Aceleración (z) (m/s2)')
axPre3.set_ylim(80.0, 110.0)
canvasPre3 = FigureCanvasTkAgg(figPresión3, master=frame_CAN_SAT_3)
canvasPre3.get_tk_widget().grid(row = 0, column = 6, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Temperatura
figTemp3 = Figure(figsize=(6, 4), dpi=100)
axTemp3 = figTemp3.add_subplot(111)
axTemp3.set_xlabel('Tiempo')
#axTemp3.set_ylabel('Temperatura')
axTemp3.set_ylim(20.0, 35.0)
canvasTem3 = FigureCanvasTkAgg(figTemp3, master=frame_CAN_SAT_3)
canvasTem3.get_tk_widget().grid(row = 0, column = 7, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Voltaje (V)
figVoltaje3 = Figure(figsize=(6, 4), dpi=100)
axVol3 = figVoltaje3.add_subplot(111)
axVol3.set_xlabel('Tiempo')
#axVol3.set_ylabel('Voltaje (V)')
axVol3.set_ylim(3.0, 4.3)
canvasVol3 = FigureCanvasTkAgg(figVoltaje3, master=frame_CAN_SAT_3)
canvasVol3.get_tk_widget().grid(row = 0, column = 8, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Corriente (mA)
figCorriente3 = Figure(figsize=(6, 4), dpi=100)
axCor3 = figCorriente3.add_subplot(111)
axCor3.set_xlabel('Tiempo')
#axCor3.set_ylabel('Corriente (mA)')
axCor3.set_ylim(-10.0, 500.0)
canvasCor3 = FigureCanvasTkAgg(figCorriente3, master=frame_CAN_SAT_3)
canvasCor3.get_tk_widget().grid(row = 0, column = 9, padx = 2, pady = 2)

########################## CANSAT4 #############################
# Se crea la gráfica de Monitorio de Velocidad (m/s)
figVelocity4 = Figure(figsize=(6, 4), dpi=100)
axVel4 = figVelocity4.add_subplot(111)
axVel4.set_xlabel('Tiempo')
#axVel4.set_ylabel('Velocidad (m/s)')
axVel4.set_ylim(-10.0, 10.0)
canvasVel4 = FigureCanvasTkAgg(figVelocity4, master=frame_CAN_SAT_4)
canvasVel4.get_tk_widget().grid(row = 0, column = 0, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Rotación (z) (rad/s)
figRotation4 = Figure(figsize=(6, 4), dpi=100)
axRot4 = figRotation4.add_subplot(111)
axRot4.set_xlabel('Tiempo')
#axRot4.set_ylabel('Rotación (z) (rad/s)')
axRot4.set_ylim(-5.0, 5.0)
canvasRot4 = FigureCanvasTkAgg(figRotation4, master=frame_CAN_SAT_4)
canvasRot4.get_tk_widget().grid(row = 0, column = 1, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Aceleracion
figAceleration4 = Figure(figsize=(6, 4), dpi=100)
axAcel4 = figAceleration4.add_subplot(111)
axAcel4.set_xlabel('Tiempo')
#axAcel4.set_ylabel('Aceleración (z) (m/s2)')
axAcel4.set_ylim(8.9, 9.3)
canvasAcel4 = FigureCanvasTkAgg(figAceleration4, master=frame_CAN_SAT_4)
canvasAcel4.get_tk_widget().grid(row = 0, column = 2, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Posicion
figPosicion4 = Figure(figsize=(6, 4), dpi=100)
axPos4 = figPosicion4.add_subplot(111)
axPos4.set_xlabel('Tiempo')
#axPos4.set_ylabel('Latitud (°)')
axPos4.set_ylim(-2.0, 2.0)
canvasPos4 = FigureCanvasTkAgg(figPosicion4, master=frame_CAN_SAT_4)
canvasPos4.get_tk_widget().grid(row = 0, column = 3, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Orientacion
figOrientacion4 = Figure(figsize=(6, 4), dpi=100)
axOri4 = figOrientacion4.add_subplot(111)
axOri4.set_xlabel('Tiempo')
#axOri4.set_ylabel('Yaw (°)')
axOri4.set_ylim(-5.0, 5.0)
canvasOri4 = FigureCanvasTkAgg(figOrientacion4, master=frame_CAN_SAT_4)
canvasOri4.get_tk_widget().grid(row = 0, column = 4, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Altitud (msnm)
figAltitude4 = Figure(figsize=(6, 4), dpi=100)
axAlt4 = figAltitude4.add_subplot(111)
axAlt4.set_xlabel('Tiempo')
#axAlt4.set_ylabel('Altitud (msnm)')
axAlt4.set_ylim(-10.0, 1400.0)
canvasAlt4 = FigureCanvasTkAgg(figAltitude4, master=frame_CAN_SAT_4)
canvasAlt4.get_tk_widget().grid(row = 0, column = 5, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Presion
figPresión4 = Figure(figsize=(6, 4), dpi=100)
axPre4 = figPresión4.add_subplot(111)
axPre4.set_xlabel('Tiempo')
#axPre4.set_ylabel('Aceleración (z) (m/s2)')
axPre4.set_ylim(80.0, 110.0)
canvasPre4 = FigureCanvasTkAgg(figPresión4, master=frame_CAN_SAT_4)
canvasPre4.get_tk_widget().grid(row = 0, column = 6, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Temperatura
figTemp4 = Figure(figsize=(6, 4), dpi=100)
axTemp4 = figTemp4.add_subplot(111)
axTemp4.set_xlabel('Tiempo')
#axTemp4.set_ylabel('Temperatura')
axTemp4.set_ylim(20.0, 35.0)
canvasTem4 = FigureCanvasTkAgg(figTemp4, master=frame_CAN_SAT_4)
canvasTem4.get_tk_widget().grid(row = 0, column = 7, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Voltaje (V)
figVoltaje4 = Figure(figsize=(6, 4), dpi=100)
axVol4 = figVoltaje4.add_subplot(111)
axVol4.set_xlabel('Tiempo')
#axVol4.set_ylabel('Voltaje (V)')
axVol4.set_ylim(3.0, 4.3)
canvasVol4 = FigureCanvasTkAgg(figVoltaje4, master=frame_CAN_SAT_4)
canvasVol4.get_tk_widget().grid(row = 0, column = 8, padx = 2, pady = 2)

# Se crea la gráfica de Monitoreo de Corriente (mA)
figCorriente4 = Figure(figsize=(6, 4), dpi=100)
axCor4 = figCorriente4.add_subplot(111)
axCor4.set_xlabel('Tiempo')
#axCor4.set_ylabel('Corriente (mA)')
axCor4.set_ylim(-10.0, 500.0)
canvasCor4 = FigureCanvasTkAgg(figCorriente4, master=frame_CAN_SAT_4)
canvasCor4.get_tk_widget().grid(row = 0, column = 9, padx = 2, pady = 2)

# Configurar la comunicación serial
ser = serial.Serial('COM37', 115200, timeout=1)  # Ajusta el puerto y la velocidad según sea necesario

# Se mandan a actualizar las datas
update_graphs1()
update_graphs2()
update_graphs3()
update_graphs4()

################################################################
#                                                              #
#           SE INICIALIZA LA INTERFAZ GRÁFICA                  #
#                                                              #
################################################################

# Crear y empezar el hilo para leer datos seriales
read_serial_data()

root.mainloop()
