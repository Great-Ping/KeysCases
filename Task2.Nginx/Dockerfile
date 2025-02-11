FROM ubuntu:20.04

RUN apt-get update && \
    #Компиляторы
    apt-get install -y make gcc && \
    #Зависимости nginx
    apt-get install -y libpcre3-dev zlib1g-dev && \
    #Гит
    apt-get install -y git

#3.1. Выполнить загрузку файлов исходных текстов веб-сервера nginx;
WORKDIR /home 
RUN git clone https://github.com/nginx/nginx.git

#3.2. Выполнить компиляцию загруженных файлов исходных текстов nginx;
WORKDIR /home/nginx
RUN ./auto/configure && \
    make && \
    make install

#3.3. Запустить скомпилированный веб-сервер
ENTRYPOINT ["/usr/local/nginx/sbin/nginx"]  