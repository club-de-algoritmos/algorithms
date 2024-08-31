import os
import re
from collections import defaultdict

def formatear_nombre(archivo):
    nombre_formateado = re.sub(r'([a-z])([A-Z])', r'\1 \2', os.path.splitext(archivo)[0])
    return nombre_formateado

def guardar_lista_archivos_ordenada(carpeta_raiz, archivo_salida, orden_carpetas):
    archivos_por_carpeta = defaultdict(list)
    
    # Recorre la carpeta raíz y agrupa los archivos por su carpeta principal
    for directorio_raiz, subdirectorios, archivos in os.walk(carpeta_raiz):
        archivos_cpp_py = [archivo for archivo in archivos if archivo.endswith('.cpp') or archivo.endswith('.py')]
        if archivos_cpp_py:
            carpeta_principal = os.path.relpath(directorio_raiz, carpeta_raiz).split(os.sep)[0]
            for archivo in archivos_cpp_py:
                ruta_relativa = os.path.relpath(os.path.join(directorio_raiz, archivo), carpeta_raiz)
                archivos_por_carpeta[carpeta_principal].append((ruta_relativa, formatear_nombre(archivo)))

    # Ordena los archivos dentro de cada carpeta principal
    for carpeta in archivos_por_carpeta:
        archivos_por_carpeta[carpeta].sort()

    # Escribe los archivos ordenados en el archivo de salida
    with open(archivo_salida, 'w') as salida:
        salida.write("# Contenido\n")
        for carpeta in orden_carpetas:
            if carpeta in archivos_por_carpeta:
                salida.write(f'\n[{carpeta}]\n')
                for ruta_relativa, nombre_formateado in archivos_por_carpeta[carpeta]:
                    if nombre_formateado in ignorar: continue
                    if nombre_formateado in correcciones:
                        nombre_formateado = correcciones[nombre_formateado]
                    salida.write(f'{ruta_relativa}\t{nombre_formateado}\n')

# Ejemplo de uso
carpeta_raiz = '../'
archivo_salida = 'contents.txt'

# Define el orden específico de las carpetas
orden_carpetas = [
    "Templates", 
    "DataStructure", 
    "NumberTheory",
    "Combinatorial",
    "Numerical", 
    "DP",
    "Graphs",
    "Strings", 
    "Geometry",
    "Extras"
]

ignorar = [
    "template_tests"
]

correcciones = {
    "templatecpp": "Template C++",
    "templatemax": "Template Max",
    "templatepy" : "Template Python",
    "Fenwick Tree2D": "Fenwick Tree 2D",
    "Segment Tree2D": "Segment Tree 2D",
    "DSURollback": "DSU Rollback"
    }

guardar_lista_archivos_ordenada(carpeta_raiz, archivo_salida, orden_carpetas)
