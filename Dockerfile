# Dockerfile
# docker build -t entorno-dev .

# linux:
    # docker run -it --rm -v $(pwd):/workspace entorno-dev sh

# Windows:
    # docker run -it --rm -v "${PWD}:/workspace" entorno-dev sh

# Saltos de línea: LF() dos2unix
# Saltos de línea: CRLF(windows) unix2dos

# Imagen base equivalente a ubuntu/bionic64
FROM ubuntu:18.04

# Evita interacciones durante instalación
ENV DEBIAN_FRONTEND=noninteractive

# Actualiza el sistema e instala herramientas necesarias
RUN apt-get update && \
    apt-get install -y nasm gcc php make curl dos2unix && \
    nasm --version && \
    gcc --version && \
    php --version && \
    make --version && \
    curl --version && \
    zsh --version && \
    echo "Entorno de desarrollo configurado con nasm, gcc, php, make, curl y zsh instalados."

# Directorio de trabajo
WORKDIR /workspace

# Copia todos los archivos al contenedor (equivalente al synced_folder)
COPY . /workspace
